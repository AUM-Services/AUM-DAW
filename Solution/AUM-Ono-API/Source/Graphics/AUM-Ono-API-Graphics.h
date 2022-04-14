//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ITEM_H
#include <Workstation/AUM-Workstation-Item.h>
using namespace AUM_Workstation_Item;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
#endif

#ifndef AUM_ONO_API_GRAPHICS_SHADER_H
#include "AUM-Ono-Api-Graphics-Shader.h"
#define AUM_ONO_API_GRAPHICS_SHADER_H
#endif // !AUM_ONO_API_GRAPHICS_SHADER_H

#ifndef AUM_ONO_API_GRAPHICS_CONTEXT_H
#include "../Contextual-Scope/Graphics/AUM-Ono-API-Context-Graphics.h"
using namespace AUM_Ono_API_Context_Graphics;
#define AUM_ONO_API_GRAPHICS_CONTEXT_H
#endif // !AUM_API_GRAPHICS_CONTEXT_H

namespace AUM_Ono_API_Graphics {

    class IAUMOnoAPIGraphics : public AUMWorkstationItem {
    public:
        IAUMOnoAPIGraphics(string name);
        ~IAUMOnoAPIGraphics();
        GLuint DynamicShader;
        // Debugger:
    private:
        string Name;
        AUMOnoAPIGraphicsShader ShaderCompiler;
        GLFWwindow* graphicalOutput;
        GLuint vertexArrayObject;
        virtual int Run() override;
        void InitializeGLFW();
        void InitializeGLEW() const;
        void BuildGraphicsOutput();
        void DrawBuffer(GLuint vertexArrayObject, GLuint ibo);
        void CleanGLErrors() const;
        void GetGLErrors() const;
        bool ListenForGLErrorEvent(const char* function, const char* file, int line) const;
        void DynamicallyUpdateShaderColor(float red, float green, float blue, float alpha) const;
        void SetupVertexArray();
        void Shutdown();
    };

}