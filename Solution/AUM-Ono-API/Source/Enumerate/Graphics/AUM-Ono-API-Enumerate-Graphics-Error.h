//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ENUMERATE_H
#include "Enumerate/AUM-Workstation-Enumerate.h"
using namespace AUM_Workstation_Enumerate;
#define AUM_WORKSTATION_ENUMERATE_H
#endif // !AUM_WORKSTATION_ENUMERATE_H

namespace AUM_Ono_API_Enumerate_Graphics {
    
    class AUMOnoAPIGraphicsErrorEnum : public AUMWorkstationEnumerate
    {
    public:
        enum AUMEnum { 
            AUM_ONO_API_GRAPHICS_SUCCESS = 1,
            GLFW = 2,
            GLFW_WINDOW = 3,
            GLEW = 4,
            SHADER = 5
        };
        //Default map
        AUMOnoAPIGraphicsErrorEnum() {
            this->Name = "AUM Ono API Graphics Errors";
            const int enumSize = 5;
            string enumStrings[enumSize] = { 
                "AUM_ONO_API_GRAPHICS_SUCCESS",
                "GLFW",
                "GLFW_WINDOW",
                "GLEW",
                "SHADER"
            };
            this->Map = this->MakeMap(enumStrings, enumSize);
        };
        //Custom map
        AUMOnoAPIGraphicsErrorEnum(const char* name, string strings[], int elementCount)
            : AUMWorkstationEnumerate(name, strings, elementCount) {};
    };

}

typedef AUM_Ono_API_Enumerate_Graphics::AUMOnoAPIGraphicsErrorEnum::AUMEnum AUMOnoAPIGraphicsError;