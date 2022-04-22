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
#include "../../Contextual-Scope/Graphics/AUM-Ono-API-Context-Graphics.h"
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
#include "AUM-Ono-Api-Graphics-Shader-Compiler.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_SHADER_H
#endif // !AUM_ONO_API_GRAPHICS_SHADER_H

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

#include "../Consolidation/AUM-Graphics-Synthesizer.h"
using namespace AUM_API_Synthesis;

namespace AUM_Ono_API_Graphics {
    
    class IAUMOnoAPIGraphics : public AUMWorkstationItem {

    public:

    private:
        //Field
        int width;
        int height;
        AUMOnoAPIGraphicsShaderCompiler shaderCompiler;
        GLFWwindow* graphicalOutput;
        unsigned int defaultVertexArray;
        unsigned int dynamicShader;
        AUMOnoAPIGraphicsIndexBuffer indexBuffer;

        //Member
        struct Colors {
            float Red_ = 0.64f;
            float Green_ = 0.0f;
            float Blue_ = 0.64f;
            float Alpha_ = 0.64f;
            float ColorIncrement_ = 0.01f;
        } shaderColors;
        static struct Oscillator {
            float Frequency_ = 16.0f;
            int Resolution_ = 1;
        } oscillator_staticMember;
        struct point {
            float x;
            float y;
        };
        int sampleRate = 44100;

        //Method
        virtual int Run() override;
        void InitializeGLFW();
        void InitializeGLEW() const;
        void BuildTheGraphicsOutput();
        void SetupATestingBuffer();
        void DrawTheTestingBuffer();
        void UpdateTheShaderColor();
        void SetupTheVertexArrayObject();
        void SetAndUseTheDynamicShader(const string filePath);
        void RotateGreen();
        void Shutdown();
        void DrawBuffer();

        //Hardware
        void SetTheCallbacks();
        static void KeyEvent_KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
        
        //Interface
        float CheckAndGetFrequency();
        int CheckAndGetResolution();

        //Events
        void BroadcastRebind();

    public:
        //Ctr
        IAUMOnoAPIGraphics(string name);
        ~IAUMOnoAPIGraphics();
    };

}