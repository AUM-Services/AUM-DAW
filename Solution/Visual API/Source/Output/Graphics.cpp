//Written by Eric Dee.

/* docs.gl */

#include "Graphics.h"

namespace AUMGraphics {

    int IAUMGraphicsOutput::Run() const {

    StartMessage:
        AUMPluginTrace("----------------Plugin update----------------");
        AUMPluginTrace("OpenGL:");
        AUMPluginDebug("{0} is running.", this->Name);

    Initialize:
        GLFWwindow* window = nullptr;
        try {
            window = this->InitializeGLFW();
            this->InitializeGLEW();
        }
        catch (string errorType)
        {
            cout << "Error type: " << errorType << endl;
            return 0;
        }

    // Fragment shaders are also called pixel shaders. They are called upon an exponential amount of times compared to vertex shaders.
    Buffering:
        auto AssignBuffer = []() {
            unsigned int buffer;
            // Assigns a number/buffer page number also called a shader onto the unsigned buffer int.
            glGenBuffers(1, &buffer);
            // Assigns the buffer block to the buffer define for frontal context
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            float positions[6] = {
                //X    //Y ---- Has to be given the layout
                -0.5f, -0.5f,
                -0.0f,  0.5f,
                 0.5f, -0.5f
            };
            glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
        };
        AssignBuffer();

        /*Size = elements per vertex for this. Stride is the total byte value of the struct/array to get to the next item/block.*/
        /*Offset at the end is used if you want to use actual structs to hold different vertext values.*/
        // Enable the array at index:
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    Writing:
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
        glfwTerminate();
        return 0;
    }


    /// <summary>
    /// Initializes an instance of a GLFW window.
    /// </summary>
    /// <returns>The new GLFW window</returns>
    GLFWwindow* IAUMGraphicsOutput::InitializeGLFW() const {
        GLFWwindow* newWindow = nullptr;
        if (!glfwInit())
        {
            AUMPluginCritical("GLFW could not initialize.");
            throw (string)"GLFW Error.";
        }
        else {
            AUMPluginDebug("GLFW initialized.");
        }
        /* Create a windowed mode window and its OpenGL context */
        newWindow = glfwCreateWindow(640, 480, "GLFW Init", NULL, NULL);
        if (!newWindow)
        {
            AUMPluginCritical("The window in GLFW could not initialize.");
            glfwTerminate();
            throw "GLFW window error";
        }
        else {
            AUMPluginDebug("Window using GLFW initialized.");
            glfwMakeContextCurrent(newWindow);
            GLint major, minor;
            glGetIntegerv(GL_MAJOR_VERSION, &major);
            glGetIntegerv(GL_MAJOR_VERSION, &minor);
            AUMPluginDebug("GL version: {0}.{1}.", major, minor);
        }
        return newWindow;
    }

    /// <summary>
    /// Initializes the GLEW functionality.
    /// </summary>
    /// <returns>void</returns>
    void IAUMGraphicsOutput::InitializeGLEW() const {
        if (glewInit() != GLEW_OK)
        {
            AUMPluginError("Glew could not init.");
        }
        else {
            AUMPluginDebug("Glew initialized.");
        }
    }
}