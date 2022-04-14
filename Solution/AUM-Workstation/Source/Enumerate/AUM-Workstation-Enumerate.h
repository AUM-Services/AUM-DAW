//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ENUMERATE_ABSTRACT_H
#include "AUM-Workstation-Enumerate-Abstract.h"
#define AUM_WORKSTATION_ENUMERATE_ABSTRACT_H
#endif // !AUM_WORKSTATION_ENUMERATE_ABSTRACT_H

namespace AUM_Workstation_Enumerate {

    class AUMWorkstationBuildMacro AUMWorkstationEnumerate : public AUMWorkstationEnumerateAbstract {
    public:
        AUMWorkstationEnumerate();
        AUMWorkstationEnumerate(const char* name, string strings[], int elementCount)
            : AUMWorkstationEnumerateAbstract(name, strings, elementCount) {};
        enum AUMWorkstationEnum{ 
            AUM_WORKSTATION_SUCCESS = 1,
            AUM_WORKSTATION_TRACE = 2,
            AUM_WORKSTATION_DEBUG = 3,
            AUM_WORKSTATION_ERROR = 4,
            AUM_WORKSTATION_CRITICAL = 5,
            AUM_WORKSTATION_ITEM_SUCCESS = 6,
            AUM_WORKSTATION_ITEM_TRACE = 7,
            AUM_WORKSTATION_ITEM_DEBUG = 8,
            AUM_WORKSTATION_ITEM_ERROR = 9,
            AUM_WORKSTATION_ITEM_CRITICAL = 10,
        };
    };

}