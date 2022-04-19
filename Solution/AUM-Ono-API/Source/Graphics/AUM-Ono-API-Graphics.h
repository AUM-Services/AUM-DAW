//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_CONTEXT_RUNTIME_H
#include "Runtime/AUM-Workstation-Context-Runtime.h"
#define AUM_WORKSTATION_CONTEXT_RUNTIME_H
#endif // !AUM_WORKSTATION_CONTEXT_RUNTIME_H

#ifndef AUM_WORKSTATION_ITEM_H
#include <Workstation/AUM-Workstation-Item.h>
using namespace AUM_Workstation_Item;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_ONO_API_GRAPHICS_CONTEXT_H
#include "../Contextual-Scope/Graphics/AUM-Ono-API-Context-Graphics.h"
using namespace AUM_Ono_API_Context_Graphics;
#define AUM_ONO_API_GRAPHICS_CONTEXT_H
#endif // !AUM_API_GRAPHICS_CONTEXT_H

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
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_SHADER_H
#endif // !AUM_ONO_API_GRAPHICS_SHADER_H

#ifndef AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#include "AUM-Ono-API-Graphics-Vertex-Buffer.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#endif // !AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H

#ifndef AUM_ONO_API_GRAPHICS_INDEX_BUFFER_H
#include "AUM-Ono-API-Graphics-Index-Buffer.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_INDEX_BUFFER_H
#endif // !AUM_ONO_API_GRAPHICS_INDEX_BUFFER_H

#ifndef AUM_ONO_API_GRAPHICS_VERTEX_ARRAY_H
#include "AUM-Ono-API-Graphics-Vertex-Array.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_VERTEX_ARRAY_H
#endif // !AUM_ONO_API_GRAPHICS_VERTEX_ARRAY_H

namespace AUM_Ono_API_Graphics {

    class IAUMOnoAPIGraphics : public AUMWorkstationItem {

    public:
        //Field
        int Width;
        int Height;
        unsigned int DynamicShader;
        AUMOnoAPIGraphicsVertexBuffer VertexBuffer;
        AUMOnoAPIGraphicsIndexBuffer IndexBuffer;
        bool IsRunning;
        struct colors {
            float Red_ = 0.51f;
            float Green_ = 0.0f;
            float Blue_ = 0.64f;
            float Alpha_ = 0.64f;
            float ColorIncrement_ = 0.01f;
        } ShaderColors;

    private:
        //Field
        string Name;
        AUMOnoAPIGraphicsShader ShaderCompiler;
        GLFWwindow* graphicalOutput;
        unsigned int defaultVertexArray;

        //Method
        virtual int Run() override;
        void InitializeGLFW();
        void InitializeGLEW() const;
        void BuildTheGraphicsOutput();
        void DrawASineWave();
        void SetupATestingBuffer();
        void DrawTheTestingBuffer();
        void UpdateTheShaderColor();
        void SetupTheVertexArrayObject();
        void SetAndUseTheDynamicShader(const string filePath);
        void RotateGreen();
        void Shutdown();

    public:
        //Ctr
        IAUMOnoAPIGraphics(string name);
        ~IAUMOnoAPIGraphics();
    };

}