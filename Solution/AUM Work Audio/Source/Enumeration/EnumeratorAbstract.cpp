#include "EnumeratorAbstract.h"

namespace AUMEnumeration {

    AUMEnumeratorAbstract::AUMEnumeratorAbstract() {
        const int enumSize = 1;
        string enumStrings[enumSize] = { "AUM_NULL" };
        this->Map = this->MakeMap(this->Map, enumStrings, enumSize);
    }

    /// <summary>
    /// Inherit the class for quick enum mapping. Not supposed to be a singleton.
    /// </summary>
    AUMEnumeratorAbstract::AUMEnumeratorAbstract(string strings[], int elementCount) {
        this->Map = this->MakeMap(this->Map, strings, elementCount);
        this->Map[0] = "AUM_NULL";
    }

    map<int, string> AUMEnumeratorAbstract::MakeMap(map<int, string> mapReference, string strings[], int elementCount) const {
        map<int, string> newMap;
        int amount = 0;
        // Leaves zero alone.
        for (int i = 0; i < (elementCount); i++)
        {
            newMap[i+1] = strings[i];
            amount++;
        }
        AUMPluginTrace("Enums:");
        AUMPluginTrace("_________");
        for (int i = 0; i < amount; i++)
        {
            AUMPluginTrace(newMap[i+1]);
        }
        AUMPluginTrace("End of enums printout.");
        AUMPluginTrace("___\n");
        return newMap;
    }

}