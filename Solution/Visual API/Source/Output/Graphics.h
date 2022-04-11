//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ITEM_H
#include "Workstation/WorkStationItem.h"
using namespace AUMWorkstation;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_GRAPHICS_ERRORS_H
#include "../Enumeration/GraphicsError.h"
#include "../Enumeration/GraphicsErrorType.h"
#define AUM_GRAPHICS_ERRORS_H
#endif // !AUM_GRAPHICS_ERRORS_H

// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")

namespace AUMGraphics {

    class IAUMGraphicsOutput : public AUMWorkstationItem {
    public:
        string Name;
        AUMGraphicsErrorEnum Errors;
        AUMGraphicsErrorTypeEnum ErrorTypes;
        IAUMGraphicsOutput(string name) : AUMWorkstationItem() {
            this->Name = name;
            AUMPluginInfo("Constructing {0}.", this->Name);
            const int enumSize = 4;
            string enumStrings[enumSize] = { "AUM_GRAPHICS_SUCCESS", "GLFW", "GLFW_WINDOW", "GLEW" };
            this->Errors = AUMGraphicsErrorEnum("Graphics readouts", enumStrings, enumSize);
            const int enum2Size = 1;
            string enum2Strings[enumSize] = { "INITIALIZATION" };
            this->ErrorTypes = AUMGraphicsErrorTypeEnum("Graphics readout types", enum2Strings, enum2Size);
        };
    private:
        virtual int Run() override;
        GLFWwindow* InitializeGLFW() const;
        void InitializeGLEW() const;
    };

}