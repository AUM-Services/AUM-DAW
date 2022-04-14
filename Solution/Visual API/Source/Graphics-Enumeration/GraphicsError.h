//Written by Eric Dee.

#pragma once

#ifndef AUM_ENUMERATION_H
#include "Enumeration/Enumerator.h"
using namespace AUMEnumeration;
#define AUM_ENUMERATION_H
#endif // !AUM_WORKSTATION_ITEM_H

namespace AUMEnumerate {
    
    class AUMGraphicsErrorEnum : public AUMEnumeratorAbstract
    {
    public:
        enum AUMEnum { AUM_NULL, AUM_GRAPHICS_SUCCESS, GLFW, GLFW_WINDOW, GLEW, SHADER };
        //Default map
        AUMGraphicsErrorEnum() {
            this->Name = "AUM Graphics Errors";
            const int enumSize = 5;
            string enumStrings[enumSize] = { "AUM_GRAPHICS_SUCCESS", "GLFW", "GLFW_WINDOW", "GLEW", "SHADER"};
            this->Map = this->MakeMap(enumStrings, enumSize);
            this->Map[0] = "AUM_NULL";
        };
        //Custom map
        AUMGraphicsErrorEnum(const char* name, string strings[], int elementCount)
            : AUMEnumeratorAbstract(name, strings, elementCount) {};
    };

}

typedef AUMEnumerate::AUMGraphicsErrorEnum::AUMEnum AUMGraphicsError;