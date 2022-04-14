//Written by Eric Dee.

#pragma once

#ifndef AUM_ENUMERATION_H
#include "Enumeration/Enumerator.h"
using namespace AUMEnumeration;
#define AUM_ENUMERATION_H
#endif // !AUM_WORKSTATION_ITEM_H

namespace AUMEnumerate {

    class AUMGraphicsErrorTypeEnum : public AUMEnumeratorAbstract
    {
    public:
        enum AUMEnum { AUM_NULL, INITIALIZATION, UPDATE };
        AUMGraphicsErrorTypeEnum() {
            this->Name = "AUM Graphics Error Types";
            const int enumSize = 2;
            string enumStrings[enumSize] = { "INITIALIZATION", "UPDATE"};
            this->Map = this->MakeMap(enumStrings, enumSize);
            this->Map[0] = "AUM_NULL";
        };
        AUMGraphicsErrorTypeEnum(const char* name, string strings[], int elementCount)
            : AUMEnumeratorAbstract(name, strings, elementCount) {};
    };

}