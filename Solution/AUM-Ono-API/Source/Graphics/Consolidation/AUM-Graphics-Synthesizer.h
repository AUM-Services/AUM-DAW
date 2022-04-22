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

#ifndef AUM_OSCILLATOR_H
#include "../../Digital-Audio/AUM-Oscillator.h"
using namespace AUM_API_Synthesis;
#define AUM_OSCILLATOR_H
#endif

namespace AUM_API_Synthesis {

    class IAUMGraphicsSynthesizer : public AUMWorkstationItem
    {
    private:
        AUMOscillator oscillator;
        void UseFFOZZSamplerateAndBufferTheWave(float frequency, int resolution);
        void UseEETZZSamplerateAndBufferTheWave(float frequency, int resolution);
        void BindASineWave(
            unsigned int shader,
            int xSectionCount,
            GLFWwindow* graphicalOutput,
            float frequency
        );

        //Method
        virtual int Run() override;

    public:
        //Ctr
        IAUMGraphicsSynthesizer(string name);
    };

}

