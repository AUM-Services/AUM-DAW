//Written by Eric Dee.

/* docs.gl */

#include "Graphics.h"

namespace AUMGraphics {

    IAUMGraphicsOutput::IAUMGraphicsOutput(string name) : AUMWorkstationItem() {
        this->Name = name;
        const int enumSize = 4;
        string enumStrings[enumSize] = { "AUM_GRAPHICS_SUCCESS", "GLFW", "GLFW_WINDOW", "GLEW" };
        this->Errors = AUMGraphicsErrorEnum("Graphics readouts", enumStrings, enumSize);
        const int enum2Size = 1;
        string enum2Strings[enumSize] = { "INITIALIZATION" };
        this->ErrorTypes = AUMGraphicsErrorTypeEnum("Graphics readout types", enum2Strings, enum2Size);
        this->ShaderCompiler = Shader();
        this->ShaderCompiler.ReadShaderFile("Add-Ins/Shaders/Default.shader");
        this->BuildGraphicsOutput();
    };

    IAUMGraphicsOutput::~IAUMGraphicsOutput() {
        delete this->graphicalOutput;
    }

    /////////////////////////////
    ////                     ////
    //// Class functionality ////
    ////                     ////
    /////////////////////////////

    int IAUMGraphicsOutput::Run() {

        if (this->IsAvailable)
        {
            glfwMakeContextCurrent(this->graphicalOutput);

            //Fragment shaders are also called pixel shaders. They are called upon an exponential amount of times compared to vertex shaders.
        Buffering:
            auto AssignBuffer = []() {
                unsigned int buffer;
                //Assigns a number/buffer page number also called a shader onto the unsigned buffer int.
                glGenBuffers(1, &buffer);
                //Assigns the buffer block to the buffer define for frontal context
                glBindBuffer(GL_ARRAY_BUFFER, buffer);
                float positions[] = {
                    //X    //Y ---- Has to be given the layout
                    -0.5f, -0.5f,
                     0.5f, -0.5f,
                     0.5f,  0.5f,
                    -0.5f,  0.5f,
                };
                glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

                unsigned int indices[] =
                { 0, 1, 2, 3, 0, 2 };
                unsigned int ibo;
                glGenBuffers(1, &ibo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);
            };

            AssignBuffer();

            /*Size = elements per vertex for this. Stride is the total byte value of the struct/array to get to the next item/block.*/
            /*Offset at the end is used if you want to use actual structs to hold different vertext values.*/
            //Enable the array at index:
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        Shader:
            GLuint shader = this->ShaderCompiler.CreateShader();
            glUseProgram(this->ShaderCompiler.CreateShader());

        Writing:
            /*Loop until the user closes the window*/
            while (!glfwWindowShouldClose(this->graphicalOutput))
            {
                this->DrawItem(this->graphicalOutput);
            }
            glDeleteProgram(shader);
            glfwTerminate();
            this->IsAvailable = false;
        }

        return 0;
    }

    ////////////////////////
    ////                ////
    //// Helper methods ////
    ////                ////
    ////////////////////////

    //Initializers:

    void IAUMGraphicsOutput::BuildGraphicsOutput() {
    StartMessage:
        AUMPluginInfo("----------------Graphics update----------------");
        AUMPluginTrace("OpenGL:");
        AUMPluginTrace("{0} is building.", this->Name);

    Startup:
        try {
            this->graphicalOutput = nullptr;
            this->InitializeGLFW();
            this->InitializeGLEW();
        }
        catch (AUMGraphicsErrorEnum::AUMEnum errorCatch)
        {
            string error = this->Errors.Map[errorCatch];
            string errorType = this->ErrorTypes.Map[this->ErrorTypes.INITIALIZATION];
            AUMAPIError("{0} failed during {1}.", error, errorType);
        }
    }

    /// <summary>
    /// Initializes an instance of a GLFW window.
    /// </summary>
    /// <returns>The new GLFW window</returns>
    void IAUMGraphicsOutput::InitializeGLFW() {
        if (!glfwInit())
        {
            throw this->Errors.GLFW;
        }
        else {
            AUMPluginTrace("GLFW initialized.");
        }
        /*Create a windowed mode window and its OpenGL context*/
        this->graphicalOutput = glfwCreateWindow(640, 480, "GLFW Init", NULL, NULL);
        if (!this->graphicalOutput)
        {
            glfwTerminate();
            throw this->Errors.GLFW_WINDOW;
        }
        else {
            AUMPluginTrace("Window using GLFW initialized.");
            glfwMakeContextCurrent(this->graphicalOutput);
            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MAJOR_VERSION, &minor);
            AUMPluginInfo("GL version: {0}.{1}.", major, minor);
        }
    }

    /// <summary>
    /// Initializes the GLEW functionality.
    /// </summary>
    /// <returns>void</returns>
    void IAUMGraphicsOutput::InitializeGLEW() const {
        if (glewInit() != GLEW_OK)
        {
            throw this->Errors.GLEW;
        }
        else {
            AUMPluginTrace("Glew initialized.");
        }
    }

    /// <summary>
    /// Draws an item that is input into it.
    /// </summary>
    /// <param name="graphicalItem">The GLFWwindow object to draw.</param>
    void IAUMGraphicsOutput::DrawItem(GLFWwindow* graphicalItem) const {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        /*Swap front and back buffers*/
        glfwSwapBuffers(graphicalItem);
        /*Poll for and process events*/
        glfwPollEvents();
    }

}