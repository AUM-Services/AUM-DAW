// Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_ITEM_H
#include "Workstation/WorkStationItem.h"
#include "Log/Log.h"
using namespace AUMWorkstation;
using namespace AUMLog;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#include "Vendors/glfw/include/GLFW/glfw3.h"

namespace AUMGraphics {

    class IAUMGraphicsOutput : public AUMWorkstationItem {
    public:
        string Name;
        IAUMGraphicsOutput(string name) : AUMWorkstationItem() {
            this->Name = name;
            AUMPluginInfo("Constructing {0}.", this->Name);
        };
        virtual int Run() const;
    };

}