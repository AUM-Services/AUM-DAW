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
            AUM_WORKSTATION_UNDEFINED,
            AUM_WORKSTATION_SUCCESS,
            AUM_WORKSTATION_TRACE,
            AUM_WORKSTATION_DEBUG,
            AUM_WORKSTATION_ERROR,
            AUM_WORKSTATION_CRITICAL };
    };

}