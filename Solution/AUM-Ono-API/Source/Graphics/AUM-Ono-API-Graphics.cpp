//Written by Eric Dee.

/* docs.gl */

#include "AUM-Ono-API-Graphics.h"

#define RUN_CASE 1;

namespace AUM_Ono_API_Graphics {

    IAUMOnoAPIGraphics::IAUMOnoAPIGraphics
    
    (string name) : AUMWorkstationItem() {
        this->Name = name;
        this->ShaderCompiler = AUMOnoAPIGraphicsShader();
        this->BuildGraphicsOutput();
        this->SetupTheVertexArrayObject();
    };

    IAUMOnoAPIGraphics::~IAUMOnoAPIGraphics
    
    () {
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

        // Make an enum for run types

    () {
        if (this->IsAvailable)
        {
            _AssertGL_(glfwMakeContextCurrent(this->graphicalOutput));

            float green = 0.0f;
            float colorIncrement = 0.01f;

#ifdef RUN_CASE
            int CASE = RUN_CASE
            switch (CASE)
            {
                case 1:
                    this->DynamicShader = this->ShaderCompiler.CreateShader("Add-Ins/Shaders/2d.shader");
                    glUseProgram(this->DynamicShader);
                    while (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->UpdateTheShaderColor(.51, green, .81, 0.81);
                        _AssertGL_(this->DrawASineWave());
                        if (green <= 0.0f || green >= 1.0f) { colorIncrement *= -1; }
                        green -= colorIncrement;
                    }
                    break;
                default:
                    this->DynamicShader = this->ShaderCompiler.CreateShader("Add-Ins/Shaders/Default.shader");
                    glUseProgram(this->DynamicShader);
                    this->SetupATestingBuffer();
                    while (!glfwWindowShouldClose(this->graphicalOutput))
                    {
                        this->UpdateTheShaderColor(.51, green, .81, 0.81);
                        _AssertGL_(this->DrawTheTestingBuffer());
                        if (green <= 0.0f || green >= 1.0f) { colorIncrement *= -1; }
                        green -= colorIncrement;
                    }
                    break;
            }
#endif // RUN_CASE

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////
    ////                ////
    //// Helper methods ////
    ////                ////
    ////////////////////////


    /// <summary>
    /// Initializes an instance of a GLFW window.
    /// </summary>
    /// <returns>The new GLFW window</returns>
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
    /// Initializes GLFW, and GLEW.
    /// </summary>
    void IAUMOnoAPIGraphics::BuildGraphicsOutput

    () {
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
    /// Sets up references for a vertex array.
    /// </summary>
    void IAUMOnoAPIGraphics::SetupTheVertexArrayObject

    () {
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
                AUMWorkstationItemError("glEnableVertexAttribArray failed in {0}.", this->Name);
            }
        }
    }

    /// <summary>
    /// Updates the shader specific to this class.
    /// </summary>
    /// <param name="red">The red level.</param>
    /// <param name="green">The green level.</param>
    /// <param name="blue">The blue level.</param>
    /// <param name="alpha">The alpha level.</param>
    void IAUMOnoAPIGraphics::UpdateTheShaderColor

    (float red, float green, float blue, float alpha) const {
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
    /// Event call to ensure that all the needed items are broken down.
    /// </summary>
    void IAUMOnoAPIGraphics::Shutdown

    () {
        glDeleteBuffers(1, this->IndexBuffer.GetAddress());
        glDeleteBuffers(1, this->VertexBuffer.GetAddress());
        this->IsAvailable = false;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////
    ////                         ////
    //// Wave function generator ////
    ////                         ////
    /////////////////////////////////

    void IAUMOnoAPIGraphics::DrawASineWave

    // https://en.wikibooks.org/wiki/OpenGL_Programming/Scientific_OpenGL_Tutorial_01

    () {
        struct point {
            GLfloat x;
            GLfloat y;
        };

        point graph[2000];

        // Get y height using an inconsistent value (AKA frequency).
        for (int i = 0; i < 2000; i++)
        {
            float x = (i - 1000.0f) / 100.0f;
            graph[i].x = x;
            graph[i].y = sin(x * 16);
        }

        this->VertexBuffer = AUMOnoAPIGraphicsVertexBuffer(sizeof graph, graph);
        this->VertexBuffer.Bind();

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

        glDrawArrays(GL_LINE_STRIP, 0, 2000);
        
        glDisableVertexAttribArray(shaderAttribute);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }


/////////////////////////////////////////////////////////////////////////////////////////////////////////


    //////////////////////
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

        ///* Says to use the vao information bound to the vertex array as first arg
        //with the buffer as second arg. */
        //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    Shader:
        glUseProgram(this->DynamicShader);
        this->UpdateTheShaderColor(.51, .51, .81, 0.81);
    }

    /// <summary>
    /// Draws an item that is input into it.
    /// </summary>
    /// <param name="graphicalItem">The GLFWwindow object to draw.</param>
    void IAUMOnoAPIGraphics::DrawTheTestingBuffer

    () {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(this->DynamicShader);

        glBindBuffer(GL_ARRAY_BUFFER, this->vertexArrayObject);
        this->IndexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(this->graphicalOutput);
        glfwPollEvents();
    }

}