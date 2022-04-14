#include "AUM-Workstation-Enumerate.h"

namespace AUM_Workstation_Enumerate {

	AUMWorkstationEnumerate::AUMWorkstationEnumerate
		() : AUMWorkstationEnumerateAbstract()
	{
        this->Name = "AUM Workstation Errors";
        const int enumSize = 6;
        string enumStrings[enumSize] = {
            "AUM_WORKSTATION_SUCCESS",
            "AUM_WORKSTATION_TRACE",
            "AUM_WORKSTATION_DEBUG",
            "AUM_WORKSTATION_ERROR",
            "AUM_WORKSTATION_CRITICAL" };
        this->Map = this->MakeMap(enumStrings, enumSize);
	}

}