//Written by Eric Dee.

#include "AUM-Workstation-Enumerate-Abstract.h"

namespace AUM_Workstation_Enumerate {

    AUMWorkstationEnumerateAbstract::AUMWorkstationEnumerateAbstract
        ()
    {
        this->Name = "Default name";
        const int enumSize = 1;
        string enumStrings[enumSize] = {
            "AUM_WORKSTATION_UNDEFINED"
        };
        this->Map = this->MakeMap(enumStrings, enumSize);
    }

    /// <summary>
    /// Inherit the class for quick enum mapping. Not supposed to be a singleton.
    /// </summary>
    AUMWorkstationEnumerateAbstract::AUMWorkstationEnumerateAbstract
        (const char* name, string strings[], int elementCount)
    {
        this->Name = name;
        this->Map = this->MakeMap(strings, elementCount);
    }

    map<int, string> AUMWorkstationEnumerateAbstract::MakeMap
        (string strings[], int elementCount) const
    {
        map<int, string> newMap;
        int amount = 0;
        // Leaves zero alone.
        for (int i = 0; i < (elementCount); i++)
        {
            newMap[i+1] = strings[i];
            amount++;
        }
        newMap[0] = "AUM_WORKSTATION_NULL";
        return newMap;
    }

}