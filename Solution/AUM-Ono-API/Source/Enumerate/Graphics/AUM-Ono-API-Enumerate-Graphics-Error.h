//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ENUMERATE_H
#include "Enumerate/AUM-Workstation-Enumerate.h"
using namespace AUM_Workstation_Enumerate;
#define AUM_WORKSTATION_ENUMERATE_H
#endif // !AUM_WORKSTATION_ENUMERATE_H

namespace AUM_Ono_API_Enumerate_Graphics {
    
    class AUMOnoAPIGraphicsErrorEnum : public AUMWorkstationEnumerate {

    public:
        //Member
        enum AUMEnum { 
            AUM_ONO_API_GRAPHICS_SUCCESS = 1,
            GLFW = 2,
            GLFW_WINDOW = 3,
            GLEW = 4,
            SHADER = 5,
            SHADER_CAUGHT_INTERNALLY = 6
        };

        //Ctr
        AUMOnoAPIGraphicsErrorEnum() {
            this->Name = "AUM Ono API Graphics Errors";
            const int enumSize = 6;
            string enumStrings[enumSize] = { 
                "AUM_ONO_API_GRAPHICS_SUCCESS",
                "GLFW",
                "GLFW_WINDOW",
                "GLEW",
                "SHADER",
                "SHADER_CAUGHT_INTERNALLY"
            };
            this->Map = this->MakeMap(enumStrings, enumSize);
        }
    };
    //Namespace scoped
    typedef AUM_Ono_API_Enumerate_Graphics::AUMOnoAPIGraphicsErrorEnum::AUMEnum AUMOnoAPIGraphicsError;

}