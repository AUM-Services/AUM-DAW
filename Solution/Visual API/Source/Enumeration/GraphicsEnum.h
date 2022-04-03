#pragma once

#ifndef AUM_ENUMERATION_H
#include "Enumeration/Enumerator.h"
using namespace AUMEnumeration;
#define AUM_ENUMERATION_H
#endif // !AUM_WORKSTATION_ITEM_H

namespace AUMGraphics {

    class AUMGraphicsEnum : public AUMEnumeratorAbstract
    {
    public:
        AUMGraphicsEnum() {};
        AUMGraphicsEnum(string strings[], int elementCount) : AUMEnumeratorAbstract(strings, elementCount) {};
        enum AUMEnum { AUM_GRAPHICS_UNDEFINED, AUM_GRAPHICS_SUCCESS, GLFW, GLFW_WINDOW, GLEW };
    };

}