//Written by Eric Dee.

/* docs.gl */

#include "Graphics.h"

namespace AUMGraphics {

    IAUMGraphicsOutput::IAUMGraphicsOutput
        (string name) : AUMWorkstationItem()
    {
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
        this->DynamicShader = this->ShaderCompiler.CreateShader();
        glUseProgram(this->DynamicShader);
    };

    IAUMGraphicsOutput::~IAUMGraphicsOutput
        ()
    {
        delete this->graphicalOutput;
    }

    /////////////////////////////
    ////                     ////
    //// Class functionality ////
    ////                     ////
    /////////////////////////////

    int IAUMGraphicsOutput::Run
        ()
    {
        if (this->IsAvailable)
        {
            _AssertGLErrorFree_(glfwMakeContextCurrent(this->graphicalOutput));

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

            _AssertGLErrorFree_(AssignBuffer());

            /*Size = elements per vertex for this. Stride is the total byte value of the struct/array to get to the next item/block.*/
            /*Offset at the end is used if you want to use actual structs to hold different vertext values.*/
            //Enable the array at index:
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        Shader:
            this->DynamicallyUpdateShaderColor(.51, .51, .81, 0.81);

        Writing:
            float green = 0.0f;
            float colorIncrement = 0.01f;
            /*Loop until the user closes the window*/
            while (!glfwWindowShouldClose(this->graphicalOutput))
            {
                this->DynamicallyUpdateShaderColor(.51, green, .81, 0.81);
                _AssertGLErrorFree_(this->DrawItem(this->graphicalOutput));
                if (green <= 0.0f) { colorIncrement = colorIncrement * -1; }
                if (green >= 1.0f) { colorIncrement = colorIncrement * -1; }
                green -= colorIncrement;
            }

        Exit:

            _AssertGLErrorFree_(glDeleteProgram(this->DynamicShader));

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

    void IAUMGraphicsOutput::BuildGraphicsOutput
        ()
    {
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
    void IAUMGraphicsOutput::InitializeGLFW
        ()
    {
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
    void IAUMGraphicsOutput::InitializeGLEW
        () const
    {
        if (glewInit() != GLEW_OK)
        {
            throw this->Errors.GLEW;
        }
        else {
            AUMPluginTrace("Glew initialized.");
        }
    }

    /// <summary>
    /// Updates the shader specific to this class.
    /// </summary>
    /// <param name="red">The red level.</param>
    /// <param name="green">The green level.</param>
    /// <param name="blue">The blue level.</param>
    /// <param name="alpha">The alpha level.</param>
    void IAUMGraphicsOutput::DynamicallyUpdateShaderColor
        (float red, float green, float blue, float alpha) const
    {
        int currentGLLocation = glGetUniformLocation(this->DynamicShader, "UNIFORM_COLOR");
        _Assert_(currentGLLocation != -1);
        _AssertGLErrorFree_(glUniform4f(currentGLLocation, red, green, blue, alpha));
    }

    /// <summary>
    /// Draws an item that is input into it.
    /// </summary>
    /// <param name="graphicalItem">The GLFWwindow object to draw.</param>
    void IAUMGraphicsOutput::DrawItem
        (GLFWwindow* graphicalItem) const
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        /*Swap front and back buffers*/
        glfwSwapBuffers(graphicalItem);
        /*Poll for and process events*/
        glfwPollEvents();
    }

    /// <summary>
    /// Cleans out the error backlog from OpenGL.
    /// </summary>
    void IAUMGraphicsOutput::CleanGLErrors
        () const
    {
        while (glGetError() != GL_NO_ERROR);
    }

    /// <summary>
    /// Prints held errors while retrieving them from OpenGL.
    /// </summary>
    void IAUMGraphicsOutput::GetGLErrors
        () const
    {
        while (GLenum error = glGetError())
        {
            AUMAPIError("OpenGL had this error: {0}", error);
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
    bool IAUMGraphicsOutput::ListenForGLErrorEvent
        (const char* file, const char* function, int line) const
    {
        while (GLenum error = glGetError())
        {
            AUMAPIError("OpenGL had this error: {0} from file {1}, calling function {2}, on line {3}", error, file, function, line);
            return false;
        }
        return true;
    }

}