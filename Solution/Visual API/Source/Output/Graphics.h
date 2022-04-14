//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ITEM_H
#include "Workstation/WorkStationItem.h"
using namespace AUMWorkstation;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_GRAPHICS_DEPENDENCIES_H
#endif

#ifndef AUM_GRAPHICS_PERIPHERALS_H
#include "Shader.h"
#define AUM_GRAPHICS_PERIPHERALS_H
#endif // !AUM_GRAPHICS_PERIPHRIALS_H

#ifndef AUM_GRAPHICS_CONTEXT_H
#include "../Contextual-Scoping/GraphicsContext.h"
using namespace AUMContext;
#define AUM_GRAPHICS_CONTEXT_H
#endif

namespace AUMGraphics {

    class IAUMGraphicsOutput : public AUMWorkstationItem {
    public:
        IAUMGraphicsOutput(string name);
        ~IAUMGraphicsOutput();
        GLuint DynamicShader;
        // Debugger:
    private:
        string Name;
        Shader ShaderCompiler;
        GLFWwindow* graphicalOutput;
        virtual int Run() override;
        void InitializeGLFW();
        void InitializeGLEW() const;
        void BuildGraphicsOutput();
        void DrawItem(GLFWwindow* graphicalItem, GLuint indexBuffer, GLuint ibo) const;
        void CleanGLErrors() const;
        void GetGLErrors() const;
        bool ListenForGLErrorEvent(const char* function, const char* file, int line) const;
        void DynamicallyUpdateShaderColor(float red, float green, float blue, float alpha) const;
    };

}