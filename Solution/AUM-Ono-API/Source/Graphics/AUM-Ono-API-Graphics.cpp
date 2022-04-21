//Written by Eric Dee.

/* docs.gl */

#include "AUM-Ono-API-Graphics.h"

namespace AUM_Ono_API_Graphics {

/********************************************************************************************************/
    ////              ////
    //// Construction ////
    ////              ////
    //////////////////////

    IAUMOnoAPIGraphics::Oscillator IAUMOnoAPIGraphics::Oscillator_staticMember;

    IAUMOnoAPIGraphics::IAUMOnoAPIGraphics
    
        (string name) : AUMWorkstationItem() {
        this->Name = name;
        this->Width = 1296;
        this->Height = 1296;
        this->ShaderCompiler = AUMOnoAPIGraphicsShaderCompiler();
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

            switch (runCase)
            {
                case 1:
                    if (this->IsRunning)
                    {
                        goto FunctionGeneratorRuntime;
                    }
                    else {
                        this->SetAndUseTheDynamicShader("Add-Ins/Shaders/2d.shader");
                    }
                    FunctionGeneratorRuntime:
                    if (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->IsRunning = true;
                        this->UpdateTheShaderColor();
                        _AssertGL_(this->DrawASineWave());
                        this->RotateGreen();
                        return 1;
                    }
                    this->IsRunning = false;
                    break;

                default:
                    if (this->IsRunning)
                    {
                        goto TestingRuntime;
                    }
                    else {
                        this->SetAndUseTheDynamicShader("Add-Ins/Shaders/Default.shader");
                        this->SetupATestingBuffer();
                        this->VertexBuffer.Bind();
                        this->IndexBuffer.Bind();
                        this->ShaderColors.ColorIncrement_ = 0.01f;
                    }
                    TestingRuntime:
                    if (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->IsRunning = true;
                        this->UpdateTheShaderColor();
                        _AssertGL_(this->DrawTheTestingBuffer());
                        this->RotateGreen();
                        return 1;
                    }
                    this->IsRunning = false;
                    break;
            }
#endif
            Exit:
            _TestGL_(glDeleteProgram(this->DynamicShader));
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
        this->graphicalOutput = glfwCreateWindow(this->Width, this->Height, "GLFW Init", NULL, NULL);
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
        this->ShaderCompiler.UnbindThisUniformLocation();
        this->DynamicShader = this->ShaderCompiler.BuildVertexAndFragmentShaders(filePath);
        this->ShaderCompiler.UseShader(this->DynamicShader);
        this->ShaderCompiler.SetUniformLocation(this->DynamicShader, "UNIFORM_COLOR");
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
            _Test_(this->ShaderCompiler.GetUniformLocation() != -1, _Graphics.Catch);
            _TestGL_(
                this->ShaderCompiler.SetUniform4f(
                    this->ShaderColors.Red_,
                    this->ShaderColors.Green_,
                    this->ShaderColors.Blue_,
                    this->ShaderColors.Alpha_
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
            this->ShaderCompiler.UseShader(this->DynamicShader);
            int currentGLLocation = glGetUniformLocation(this->DynamicShader, "UNIFORM_COLOR");
            _Assert_(currentGLLocation != -1);
            _AssertGL_(
                this->ShaderCompiler.SetUniform4f(
                    this->ShaderColors.Red_,
                    this->ShaderColors.Green_,
                    this->ShaderColors.Blue_,
                    this->ShaderColors.Alpha_
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
        if (this->ShaderColors.Green_ <= 0.0f || this->ShaderColors.Green_ >= 1.0f)
        {
            this->ShaderColors.ColorIncrement_ *= -1;
        }
        this->ShaderColors.Green_ -= this->ShaderColors.ColorIncrement_;
    }

    /// <summary>
    /// Event call to ensure that all the used items are broken down.
    /// </summary>
    void IAUMOnoAPIGraphics::Shutdown

        () {
        glDeleteVertexArrays(1, &this->defaultVertexArray);
        glDeleteVertexArrays(1, this->VertexBuffer.GetAddress());
        glDeleteBuffers(1, this->IndexBuffer.GetAddress());
        glDeleteBuffers(1, this->VertexBuffer.GetAddress());
        this->IsRunning = false;
        this->IsAvailable = false;
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
        if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        {
            Oscillator_staticMember.Resolution_ = 1;
        }
        if (key == GLFW_KEY_E && action == GLFW_PRESS)
        {
            Oscillator_staticMember.Resolution_ = 2;
        }
        if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
        {
            Oscillator_staticMember.Frequency_ -= 16.0f;
        }
        if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
        {
            Oscillator_staticMember.Frequency_ += 16.0f;
        }
    }

    float IAUMOnoAPIGraphics::CheckAndGetFrequency
        
        () {
        this->frequency = Oscillator_staticMember.Frequency_;
        return this->frequency;
    }

    int IAUMOnoAPIGraphics::CheckAndGetResolution

    () {
        this->resolution = Oscillator_staticMember.Resolution_;
        return this->resolution;
    }

/********************************************************************************************************/
#define AUM_DAW_SAMPLE_RATE_44100 44100
#define AUM_DAW_SAMPLE_RATE_88200 88200
    ////                         ////
    //// Wave function generator ////
    ////                         ////
    /////////////////////////////////

    float IAUMOnoAPIGraphics::GetSineData
        
        (float i, float frequency, float sampleRate) {
        return (float)(sin(2 * M_PI * frequency * i) / sampleRate);
    }

    void IAUMOnoAPIGraphics::UseFFOZZSamplerateAndBufferTheWave

        () {

        struct point {
            float x;
            float y;
        };

        const int sampleRate = AUM_DAW_SAMPLE_RATE_44100;
        point graph[sampleRate];

        float frequency;
        float amplitude = sampleRate/4;

        frequency = this->CheckAndGetFrequency();
        int index;
        for (float i = 0; i < sampleRate; i++)
        {
            int index = (int)i;
            graph[index].x = -.5 + (i/sampleRate) * resolution;
            graph[index].y = amplitude *this->GetSineData(
                graph[index].x, frequency, sampleRate
            );
        }
        this->VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(sizeof graph, graph);
        this->VertexBuffer.Bind();
    }

    void IAUMOnoAPIGraphics::UseEETZZSamplerateAndBufferTheWave

        () {

        struct point {
            float x;
            float y;
        };

        const int sampleRate = AUM_DAW_SAMPLE_RATE_88200;
        point graph[sampleRate];

        float frequency;
        float amplitude = sampleRate/4;

        frequency = this->CheckAndGetFrequency()/2;
        int index;
        for (float i = 0; i < sampleRate; i++)
        {
            int index = (int)i;
            graph[index].x = -1 + (i/sampleRate) * resolution;
            graph[index].y = amplitude *this->GetSineData(
                graph[index].x, frequency, sampleRate
            );
        }
        this->VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(sizeof graph, graph);
        this->VertexBuffer.Bind();
    }

    void IAUMOnoAPIGraphics::DrawASineWave

        /* While running: */
        /* Use - or + to change the frequency, and q or e to change the resolution */

        () {

        const float windowWidth = (float)this->Width;
        const float windowHeight = (float)this->Height;

        int sampleRate;
        int xSectionCount = this->CheckAndGetResolution();
        
        switch (xSectionCount)
        {
            case 1:
                this->UseFFOZZSamplerateAndBufferTheWave();
                sampleRate = AUM_DAW_SAMPLE_RATE_44100;
                break;
            case 2:
                this->UseEETZZSamplerateAndBufferTheWave();
                sampleRate = AUM_DAW_SAMPLE_RATE_88200;
                break;
        }

        const char* attributeName = "coord2d";
        GLint shaderAttribute = glGetAttribLocation(this->DynamicShader, attributeName);
        
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
        
        glDisableVertexAttribArray(shaderAttribute);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }

/********************************************************************************************************/
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

        this->VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(4 * 2 * sizeof(float), positions);
        this->IndexBuffer = AUMOnoAPIGraphicsIndexBuffer(6, indices);

        AUMOnoAPIGraphicsVertexArray va;
        AUMOnoAPIGraphicsVertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddToBuffer(this->VertexBuffer, layout);
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