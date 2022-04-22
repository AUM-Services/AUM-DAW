//Written by Eric Dee.

/* docs.gl */

#include "AUM-Ono-API-Graphics.h"

namespace AUM_Ono_API_Graphics {

/********************************************************************************************************/
    ////              ////
    //// Construction ////
    ////              ////
    //////////////////////

    IAUMOnoAPIGraphics::Oscillator IAUMOnoAPIGraphics::oscillator_staticMember;

    IAUMOnoAPIGraphics::IAUMOnoAPIGraphics
    
        (string name) : AUMWorkstationItem() {
        this->Name = name;
        this->width = 1296;
        this->height = 1296;
        this->shaderCompiler = AUMOnoAPIGraphicsShaderCompiler();
        this->BuildTheGraphicsOutput();
        this->SetupTheVertexArrayObject();
    };

    IAUMOnoAPIGraphics::~IAUMOnoAPIGraphics
    
        () {
        if (this->graphicalOutput)
        {
            glfwTerminate();
        };
    }

/********************************************************************************************************/
    ////               ////
    //// Main function ////
    ////               ////
    ///////////////////////

    int IAUMOnoAPIGraphics::Run

        // At a more complete stage, separate function generators from unit tests
        // by making this into a base class.
        // Make an enum for run types.
        () {
        if (this->IsAvailable)
        {
            _AssertGL_(glfwMakeContextCurrent(this->graphicalOutput));
          
#ifdef AUM_WORKSTATION_RUN_CASE
            
            bool overrideToTest = false;
            int runCase = overrideToTest? 0 : AUM_WORKSTATION_RUN_CASE;
            bool start = true;

            switch (runCase)
            {
                case 1:
                    if (this->IsRunning)
                    {
                        goto Runtime;
                    }
                    else if (start) {
                        this->IsRunning = true;
                        this->SetAndUseTheDynamicShader("Add-Ins/Shaders/2d.shader");
                        start = false;
                        return 1;
                    }
                Runtime:
                    if (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->CheckForNewEvents();
                        this->UpdateContext();
                        this->UpdateTheShaderColor();
                        _AssertGL_(this->DrawBuffer());
                        this->RotateGreen();
                        return 1;
                    }
                    else {
                        this->IsRunning = false;
                    }
                    break;

                default:
                    if (this->IsRunning)
                    {
                        goto RuntimeTests;
                    }
                    else {
                        this->SetAndUseTheDynamicShader("Add-Ins/Shaders/Default.shader");
                        this->SetupATestingBuffer();
                        _Graphics.VertexBuffer.Bind();
                        this->indexBuffer.Bind();
                        this->shaderColors.ColorIncrement_ = 0.01f;
                    }
                RuntimeTests:
                    if (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->IsRunning = true;
                        this->UpdateTheShaderColor();
                        _AssertGL_(this->DrawTheTestingBuffer());
                        this->RotateGreen();
                        return 1;
                    }
                    else {
                        this->IsRunning = false;
                    }
                    break;
            }
#endif
            Exit:
            _TestGL_(glDeleteProgram(this->dynamicShader));
            if (_Graphics.Catch.ValidateAndReset())
            {
                AUMWorkstationItemCritical("glDeleteProgram failed in {0}.", this->Name);
                this->Shutdown();
                throw _Graphics.Catch.Errors.AUM_WORKSTATION_ITEM_ERROR;
            }
            else {
                this->Shutdown();
                return _Graphics.Catch.Errors.AUM_WORKSTATION_NULL;
            }
        }
    }

/********************************************************************************************************/
    ////                ////
    //// Build methods  ////
    ////                ////
    ////////////////////////

    /// <summary>
    /// Initializes an instance of a GLFW window.
    /// </summary>
    /// <returns>The new GLFW window instance.</returns>
    void IAUMOnoAPIGraphics::InitializeGLFW

        () {
        if (!glfwInit())
        {
            throw _Graphics.Catch.Errors.GLFW;
        }
        else {
            AUMWorkstationItemTrace("GLFW initialized.");
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        this->graphicalOutput = glfwCreateWindow(this->width, this->height, "GLFW Init", NULL, NULL);
        if (!this->graphicalOutput)
        {
            glfwTerminate();
            throw _Graphics.Catch.Errors.GLFW_WINDOW;
        }
        else {
            AUMWorkstationItemTrace("Window using GLFW initialized.");
            glfwMakeContextCurrent(this->graphicalOutput);
            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MAJOR_VERSION, &minor);
            AUMWorkstationItemInfo("GL version: {0}.{1}.", major, minor);
        }
    }

    /// <summary>
    /// Initializes GLEW.
    /// </summary>
    /// <returns>void.</returns>
    void IAUMOnoAPIGraphics::InitializeGLEW
    
        () const {
        if (glewInit() != GLEW_OK)
        {
            throw _Graphics.Catch.Errors.GLEW;
        }
        else {
            AUMWorkstationItemTrace("Glew initialized.");
        }
    }

    /// <summary>
    /// Initialize all the hardware functions here.
    /// </summary>
    void IAUMOnoAPIGraphics::SetTheCallbacks

        () {
        glfwSetKeyCallback(this->graphicalOutput, this->KeyEvent_KeyHandler);
    }

    /// <summary>
    /// Initializes GLFW, and GLEW.
    /// </summary>
    void IAUMOnoAPIGraphics::BuildTheGraphicsOutput

        () {
        AUMWorkstationItemInfo("----------------Graphics update----------------");
        AUMWorkstationItemTrace("OpenGL:");
        AUMWorkstationItemTrace("{0} is building.", this->Name);

        try {
            this->graphicalOutput = nullptr;
            this->InitializeGLFW();
            this->InitializeGLEW();
            this->SetTheCallbacks();
        }
        catch (AUMOnoAPIGraphicsError errorCatch)
        {
            _Graphics.PrintInitilizationError(errorCatch);
        }
    }

    /// <summary>
    /// Sets up references for the vertex array attached to this class.
    /// </summary>
    void IAUMOnoAPIGraphics::SetupTheVertexArrayObject

        () {
        _TestGL_(glGenVertexArrays(1, &this->defaultVertexArray));
        _TestGL_(glBindVertexArray(this->defaultVertexArray));
        if (_Graphics.Catch.ValidateAndReset())
        {
            AUMWorkstationItemCritical("OpenGL failed to instantiate a VAO in {0}.", this->Name);
            this->Shutdown();
            throw _Graphics.Catch.Errors.AUM_WORKSTATION_ITEM_ERROR;
        }
        else {
            _TestGL_(glEnableVertexAttribArray(0));
            if (_Graphics.Catch.ValidateAndReset())
            {
                AUMWorkstationItemError("glEnableVertexAttribArray failed in {0}.", this->Name);
            }
        }
    }

/********************************************************************************************************/
    ////                  ////
    //// Reliant methods  ////
    ////                  ////
    //////////////////////////

    void IAUMOnoAPIGraphics::SetAndUseTheDynamicShader

        (const string filePath) {
        this->shaderCompiler.UnbindThisUniformLocation();
        this->dynamicShader = this->shaderCompiler.BuildVertexAndFragmentShaders(filePath);
        this->shaderCompiler.UseShader(this->dynamicShader);
        this->shaderCompiler.SetUniformLocation(this->dynamicShader, "UNIFORM_COLOR");
        _Graphics.CurrentShader = this->dynamicShader;
    }

    /// <summary>
    /// Updates the shader attached to this class.
    /// </summary>
    /// <param name="red">The red level.</param>
    /// <param name="green">The green level.</param>
    /// <param name="blue">The blue level.</param>
    /// <param name="alpha">The alpha level.</param>
    void IAUMOnoAPIGraphics::UpdateTheShaderColor

        () {
        try 
        {
            _Test_(this->shaderCompiler.GetUniformLocation() != -1, _Graphics.Catch);
            _TestGL_(
                this->shaderCompiler.SetUniform4f(
                    this->shaderColors.Red_,
                    this->shaderColors.Green_,
                    this->shaderColors.Blue_,
                    this->shaderColors.Alpha_
                )
            );
            if (_Graphics.Catch.ValidateAndReset())
            {
                AUMWorkstationItemError("Shader error. The next lines will have more details.");
                AUMWorkstationItemWarn("Attempting to use the {0}->DynamicShader instead.", this->Name);
                throw _Graphics.Catch.Errors.SHADER_CAUGHT_INTERNALLY;
            }
        }
        catch (AUMOnoAPIGraphicsError errorCatch) {
            _Graphics.PrintUpdateError(errorCatch);
            this->shaderCompiler.UseShader(this->dynamicShader);
            int currentGLLocation = glGetUniformLocation(this->dynamicShader, "UNIFORM_COLOR");
            _Assert_(currentGLLocation != -1);
            _AssertGL_(
                this->shaderCompiler.SetUniform4f(
                    this->shaderColors.Red_,
                    this->shaderColors.Green_,
                    this->shaderColors.Blue_,
                    this->shaderColors.Alpha_
                )
            );
            AUMWorkstationItemDebug(
                "Successfully replaced the broken shader with the {0}->DynamicShader.", this->Name);
        }
    }

    /// <summary>
    /// Helper method to change the green level incrementally.
    /// </summary>
    void IAUMOnoAPIGraphics::RotateGreen
    
        () {
        if (this->shaderColors.Green_ <= 0.0f || this->shaderColors.Green_ >= 1.0f)
        {
            this->shaderColors.ColorIncrement_ *= -1;
        }
        this->shaderColors.Green_ -= this->shaderColors.ColorIncrement_;
    }

    /// <summary>
    /// Event call to ensure that all the used items are broken down.
    /// </summary>
    void IAUMOnoAPIGraphics::Shutdown

        () {
        glDeleteVertexArrays(1, &this->defaultVertexArray);
        glDeleteVertexArrays(1, _Graphics.VertexBuffer.GetAddress());
        glDeleteBuffers(1, this->indexBuffer.GetAddress());
        glDeleteBuffers(1, _Graphics.VertexBuffer.GetAddress());
        this->IsRunning = false;
        this->IsAvailable = false;
    }

    void IAUMOnoAPIGraphics::UpdateContext

        () {
        _AssertGL_(glfwMakeContextCurrent(this->graphicalOutput));
        _Graphics.CurrentOutput = this->graphicalOutput;
    }

    /// <summary>
    /// Changes frequency up or down based on which key is pressed.
    /// </summary>
    /// <param name="window">The GLFW window to focus.</param>
    /// <param name="key">The key value.</param>
    /// <param name="scancode">The key scancode.</param>
    /// <param name="action">The present action on the scancode.</param>
    /// <param name="mods">Any decorators tied to the read.</param>
    void IAUMOnoAPIGraphics::KeyEvent_KeyHandler
    
        (GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        {
            oscillator_staticMember.Resolution_ = 1;
        }
        if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        {
            oscillator_staticMember.Resolution_ = 2;
        }
        if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
        {
            oscillator_staticMember.Frequency_ -= 16.0f;
        }
        if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
        {
            oscillator_staticMember.Frequency_ += 16.0f;
        }
    }

    float IAUMOnoAPIGraphics::CheckAndGetFrequency
        
        () {
        if (_Graphics.Frequency != oscillator_staticMember.Frequency_)
        {
            _Graphics.FrequencyShouldRebind = true;
            _Graphics.Frequency = oscillator_staticMember.Frequency_;
        }
        return _Graphics.Frequency;
    }

    int IAUMOnoAPIGraphics::CheckAndGetResolution

        () {
        if (_Graphics.Resolution != oscillator_staticMember.Resolution_)
        {
            _Graphics.Resolution = oscillator_staticMember.Resolution_;
            _Graphics.ResolutionShouldRebind = true;
        }
        return _Graphics.Resolution;
    }

    void IAUMOnoAPIGraphics::CheckForNewEvents

        () {
        this->CheckAndGetResolution();
        this->CheckAndGetFrequency();
    }

/**********************************************************************************************/
    ////                    ////
    //// Production runtime ////
    ////                    ////
    ////////////////////////////

    void IAUMOnoAPIGraphics::DrawBuffer
        
        () {
        int sampleRate;

        switch (_Graphics.Resolution)
        {
        case 1:
            sampleRate = 44100;
            break;
        case 2:
            sampleRate = 88200;
            break;
        }

        const char* attributeName = "coord2d";
        GLint shaderAttribute = glGetAttribLocation(this->dynamicShader, attributeName);

        if (shaderAttribute == -1) {
            AUMWorkstationItemError("Could not bind attribute {0} in {1}.", attributeName, this->Name);
            throw _Graphics.Catch.Errors.SHADER;
        }
        else {
            glEnableVertexAttribArray(shaderAttribute);
        }

        glVertexAttribPointer(
            shaderAttribute,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            0
        );

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_POINTS, 0, sampleRate);

        //glDisableVertexAttribArray(shaderAttribute);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }

/**********************************************************************************************/
    ////              ////
    //// Unit Testing ////
    ////              ////
    //////////////////////

    void IAUMOnoAPIGraphics::SetupATestingBuffer

        () {
    Buffering:
        float positions[] = {
            //X    //Y
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };
        unsigned int indices[] =
        { 0, 1, 2, 3, 0, 2 };

        _Graphics.VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(4 * 2 * sizeof(float), positions);
        this->indexBuffer = AUMOnoAPIGraphicsIndexBuffer(6, indices);

        AUMOnoAPIGraphicsVertexArray va;
        AUMOnoAPIGraphicsVertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddToBuffer(_Graphics.VertexBuffer, layout);
        // Binds the array details and the index buffer at once.
    }

    /// <summary>
    /// Draws an item that is input into it.
    /// </summary>
    /// <param name="graphicalItem">The GLFWwindow object to draw.</param>
    void IAUMOnoAPIGraphics::DrawTheTestingBuffer

        () {
        glClear(GL_COLOR_BUFFER_BIT);

        // Intended to draw from the indicies
        // And update (bind) them or the vertex outside when needed (Wave tables).

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }

}