// Written by Eric Dee

#pragma once

#ifndef AUM_WORK_AUDIO_H
#include <AUMWorkAudio.h>
#include <vector>
using namespace AUMWorkstation;
#define AUM_WORK_AUDIO_H
#endif // !AUM_WORK_AUDIO_H

#include "Vendors/glfw/include/GLFW/glfw3.h"

namespace VisualAPI {

    class GUI : public AUMWorkstationItem {
    public:
        string Name;
        GUI(string name) : AUMWorkstationItem() {
            this->Name = name;
        };
        int Run() override;
    };

}