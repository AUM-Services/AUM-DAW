//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ITEM_H
#include "Workstation/WorkStationItem.h"
using namespace AUMWorkstation;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_GRAPHICS_ERRORS_H
#include "../Enumeration/GraphicsEnum.h"
#define AUM_GRAPHICS_ERRORS_H
#endif // !AUM_GRAPHICS_ERRORS_H

// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"

namespace AUMGraphics {

    class IAUMGraphicsOutput : public AUMWorkstationItem {
    public:
        string Name;
        AUMGraphicsEnum Errors;
        IAUMGraphicsOutput(string name) : AUMWorkstationItem() {
            this->Name = name;
            AUMPluginInfo("Constructing {0}.", this->Name);
            const int enumSize = 4;
            string enumStrings[enumSize] = { "AUM_GRAPHICS_SUCCESS", "GLFW", "GLFW_WINDOW", "GLEW" };
            this->Errors = AUMGraphicsEnum(enumStrings, enumSize);
        };
    private:
        virtual int Run() const;
        GLFWwindow* InitializeGLFW() const;
        void InitializeGLEW() const;
    };
}