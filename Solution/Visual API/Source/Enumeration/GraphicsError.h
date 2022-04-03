//Written by Eric Dee.

#pragma once

#ifndef AUM_ENUMERATION_H
#include "Enumeration/Enumerator.h"
using namespace AUMEnumeration;
#define AUM_ENUMERATION_H
#endif // !AUM_WORKSTATION_ITEM_H

namespace AUMGraphics {

    class AUMGraphicsErrorEnum : public AUMEnumeratorAbstract
    {
    public:
        AUMGraphicsErrorEnum() {};
        AUMGraphicsErrorEnum(const char* name, string strings[], int elementCount)
            : AUMEnumeratorAbstract(name, strings, elementCount) {};
        enum AUMEnum { AUM_NULL, AUM_GRAPHICS_SUCCESS, GLFW, GLFW_WINDOW, GLEW };
    };

}