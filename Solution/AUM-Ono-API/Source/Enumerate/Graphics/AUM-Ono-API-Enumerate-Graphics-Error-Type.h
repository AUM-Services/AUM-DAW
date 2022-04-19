//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ENUMERATE_H
#include "Enumerate/AUM-Workstation-Enumerate.h"
using namespace AUM_Workstation_Enumerate;
#define AUM_WORKSTATION_ENUMERATE_H
#endif // !AUM_WORKSTATION_ENUMERATE_H

namespace AUM_Ono_API_Enumerate_Graphics {

    class AUMOnoAPIGraphicsErrorTypeEnum : public AUMWorkstationEnumerate {

    public:
        //Member
        enum AUMEnum {
            INITIALIZATION = 1,
            UPDATE = 2
        };

        //Ctr
        AUMOnoAPIGraphicsErrorTypeEnum() {
            this->Name = "AUM Ono API Graphics Error Types";
            const int enumSize = 2;
            string enumStrings[enumSize] = {
                "INITIALIZATION",
                "UPDATE"
            };
            this->Map = this->MakeMap(enumStrings, enumSize);
        }
        
    };
    typedef AUM_Ono_API_Enumerate_Graphics::AUMOnoAPIGraphicsErrorTypeEnum::AUMEnum AUMOnoAPIGraphicsErrorType;

}