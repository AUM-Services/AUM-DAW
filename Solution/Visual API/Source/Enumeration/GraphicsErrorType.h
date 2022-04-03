//Written by Eric Dee.

#pragma once

#ifndef AUM_ENUMERATION_H
#include "Enumeration/Enumerator.h"
using namespace AUMEnumeration;
#define AUM_ENUMERATION_H
#endif // !AUM_WORKSTATION_ITEM_H

namespace AUMGraphics {

    class AUMGraphicsErrorTypeEnum : public AUMEnumeratorAbstract
    {
    public:
        AUMGraphicsErrorTypeEnum() {};
        AUMGraphicsErrorTypeEnum(const char* name, string strings[], int elementCount)
            : AUMEnumeratorAbstract(name, strings, elementCount) {};
        enum AUMEnum { AUM_NULL, INITIALIZATION };
    };

}