// Written by Eric Dee

#include "Runtime.h"

namespace VisualAPI {
    
    int GUI::Run() {

        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "GLFW Init", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
    }
}

namespace Runtime {

    class VisualFunctionality : public AUMWorkstationFactory {
    public:
        AUMWorkstationItem* CreateFunctionality() override;
    };

    AUMWorkstationItem* VisualFunctionality::CreateFunctionality() {
        VisualAPI::GUI visualAPI = VisualAPI::GUI("GLFW GUI");
        AUMPluginInfo("Welcome to AUM API. Attempting to connect {0}.", visualAPI.Name);

        return &visualAPI;
    }
}

AUMWorkstationItem* AUMWorkstation::AUMWorkstationInitMain()
{
    using namespace Runtime; using namespace VisualAPI;
    VisualFunctionality visualAPI = VisualFunctionality();
    AUMWorkstationItem* pluginGUI = visualAPI.CreateFunctionality();
    return pluginGUI;
}