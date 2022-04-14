//Written by Eric Dee.

/* docs.gl */

#include "AUM-Ono-API-Graphics.h"

namespace AUM_Ono_API_Graphics {

    IAUMOnoAPIGraphics::IAUMOnoAPIGraphics
        (string name) : AUMWorkstationItem()
    {
        this->Name = name;
        this->ShaderCompiler = AUMOnoAPIGraphicsShader();
        this->BuildGraphicsOutput();
        this->DynamicShader = this->ShaderCompiler.CreateShader("Add-Ins/Shaders/Default.shader");
        this->SetupVertexArray();
    };

    IAUMOnoAPIGraphics::~IAUMOnoAPIGraphics
    ()
    {
        if (this->graphicalOutput)
        {
            glfwTerminate();
        };
    }

    /////////////////////////////
    ////                     ////
    //// Class functionality ////
    ////                     ////
    /////////////////////////////

    int IAUMOnoAPIGraphics::Run
        ()
    {
        if (this->IsAvailable)
        {
            _AssertGL_(glfwMakeContextCurrent(this->graphicalOutput));

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

            /* Says to use the vao information bound to the vertex array as first arg with the buffer as second arg. */
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

        Shader:
            glUseProgram(this->DynamicShader);
            this->DynamicallyUpdateShaderColor(.51, .51, .81, 0.81);

        Writing:
            float green = 0.0f;
            float colorIncrement = 0.01f;
            /*Loop until the user closes the window*/
            while (!glfwWindowShouldClose(this->graphicalOutput))
            {
                this->DynamicallyUpdateShaderColor(.51, green, .81, 0.81);
                _AssertGL_(this->DrawBuffer());
                if (green <= 0.0f || green >= 1.0f) { colorIncrement *= -1; }
                green -= colorIncrement;
            }

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
                return 0;
            }
        }
    }

    ////////////////////////
    ////                ////
    //// Helper methods ////
    ////                ////
    ////////////////////////

    /// <summary>
    /// Initializes GLFW, and GLEW.
    /// </summary>
    void IAUMOnoAPIGraphics::BuildGraphicsOutput
        ()
    {
        AUMWorkstationItemInfo("----------------Graphics update----------------");
        AUMWorkstationItemTrace("OpenGL:");
        AUMWorkstationItemTrace("{0} is building.", this->Name);

        try {
            this->graphicalOutput = nullptr;
            this->InitializeGLFW();
            this->InitializeGLEW();
        }
        catch (AUMOnoAPIGraphicsError errorCatch)
        {
            _Graphics.PrintInitilizationError(errorCatch);
        }
    }

    /// <summary>
    /// Initializes an instance of a GLFW window.
    /// </summary>
    /// <returns>The new GLFW window</returns>
    void IAUMOnoAPIGraphics::InitializeGLFW
        ()
    {
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
        this->graphicalOutput = glfwCreateWindow(640, 480, "GLFW Init", NULL, NULL);
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
    /// Initializes the GLEW functionality.
    /// </summary>
    /// <returns>void</returns>
    void IAUMOnoAPIGraphics::InitializeGLEW
        () const
    {
        if (glewInit() != GLEW_OK)
        {
            throw _Graphics.Catch.Errors.GLEW;
        }
        else {
            AUMWorkstationItemTrace("Glew initialized.");
        }
    }

    // Views:

    /// <summary>
    /// Updates the shader specific to this class.
    /// </summary>
    /// <param name="red">The red level.</param>
    /// <param name="green">The green level.</param>
    /// <param name="blue">The blue level.</param>
    /// <param name="alpha">The alpha level.</param>
    void IAUMOnoAPIGraphics::DynamicallyUpdateShaderColor
        (float red, float green, float blue, float alpha) const
    {
        try 
        {
            int currentGLLocation = glGetUniformLocation(this->DynamicShader, "UNIFORM_COLOR");
            _Test_(currentGLLocation != -1, _Graphics.Catch);
            _TestGL_(glUniform4f(currentGLLocation, red, green, blue, alpha))
            if (_Graphics.Catch.ValidateAndReset())
            {
                throw _Graphics.Catch.Errors.SHADER;
            }
        }
        catch (AUMOnoAPIGraphicsError errorCatch) {
            _Graphics.PrintUpdateError(errorCatch);
            glUseProgram(this->DynamicShader);
            int currentGLLocation = glGetUniformLocation(this->DynamicShader, "UNIFORM_COLOR");
            _Assert_(currentGLLocation != -1);
            _AssertGL_(glUniform4f(currentGLLocation, red, green, blue, alpha));
        }
    }

    /// <summary>
    /// Draws an item that is input into it.
    /// </summary>
    /// <param name="graphicalItem">The GLFWwindow object to draw.</param>
    void IAUMOnoAPIGraphics::DrawBuffer
        ()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(this->DynamicShader);

        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayObject);
        this->IndexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }

    //////////////////////////
    ////                  ////
    //// GL error getters ////
    ////                  ////
    //////////////////////////

    /// <summary>
    /// Cleans out the error backlog from OpenGL.
    /// </summary>
    void IAUMOnoAPIGraphics::CleanGLErrors
        () const
    {
        while (glGetError() != GL_NO_ERROR);
    }

    /// <summary>
    /// Prints held errors while retrieving them from OpenGL.
    /// </summary>
    void IAUMOnoAPIGraphics::GetGLErrors
        () const
    {
        while (GLenum error = glGetError())
        {
            AUMWorkstationItemError("OpenGL had this error: {0}", error);
        }
    }

    /// <summary>
    /// Wrapped/Decorated event that uses an assert defined from the APIValidator class to throw debug errors if a gl error is found,
    /// and tell you where the error happened.
    /// </summary>
    /// <param name="file">The file name.</param>
    /// <param name="function">The function being called.</param>
    /// <param name="line">The line of code it is being called from.</param>
    /// <returns>Success or fail.</returns>
    bool IAUMOnoAPIGraphics::ListenForGLErrorEvent
        (const char* file, const char* function, int line) const
    {
        while (GLenum error = glGetError())
        {
            AUMWorkstationItemError("OpenGL had this error: {0} from file {1}, calling function {2}, on line {3}", error, file, function, line);
            return false;
        }
        return true;
    }

    /// <summary>
    /// Sets up references for a vertex array.
    /// </summary>
    void IAUMOnoAPIGraphics::SetupVertexArray
        () 
    {
        _TestGL_(glGenVertexArrays(1, &this->vertexArrayObject));
        _TestGL_(glBindVertexArray(this->vertexArrayObject));
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
                AUMWorkstationError("glEnableVertexAttribArray failed in {0}.", this->Name);
            }
        }
    }

    /// <summary>
    /// Event call to ensure that all the needed items are broken down.
    /// </summary>
    void IAUMOnoAPIGraphics::Shutdown
        ()
    {
        glDeleteBuffers(1, this->IndexBuffer.GetAddress());
        glDeleteBuffers(1, this->VertexBuffer.GetAddress());
        this->IsAvailable = false;
    }

}