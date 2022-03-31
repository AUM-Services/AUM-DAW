// Written by Eric Dee

#include "WorkStationItem.h"

namespace AUMWorkstation {

    int AUMWorkstationItem::Run() {
        AUMStatusInfo("Welcome to AUM Work Audio.");
        AUMStatusInfo("Create a class that inherits the AUMWorkStationItem to define the 'Run()' method");
        while (true);
        return 0;
    }

    AUMWorkstationItem* AUMWorkstationFactory::CreateFunctionality() {
        AUMPluginInfo("Welcome to AUM API. Attempting to connect default settings.");
        return new AUMWorkstationItem();
    }
}