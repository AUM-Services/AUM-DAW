//Written by Eric Dee.

#pragma once

#ifdef AUMWorkstationPlatformWindows

#ifndef AUM_WORKSTATION_H
#include "Enumerate/AUM-Workstation-Enumerate.h"
#include "Workstation/AUM-Workstation-Item.h"
#include "Workstation/AUM-Workstation-Item-Factory.h"
#include "Runtime/AUM-Workstation-Runtime.h"
using namespace AUM_Workstation_Runtime;
#define AUM_WORKSTATION_H
#endif // !AUM_WORKSTATION_H

int StartAUMApplication(int argc, char** argv) {
    AUMWorkstationLog::AppendSettingsToAllLoggers("AUM Workstation log", "AUM Workstation runtime log", "AUM Workstation item log");
    AUMWorkstationCritical("*Start of the AUM Workstation**");
    AUMWorkstationRuntime workstation = AUMWorkstationInitMain();
    workstation.MakeAllWorkItemsAvailable();
    // While there is a primary window:
    while (workstation.WorkstationItems[0]->IsAvailable)
    {
        workstation.CompletePendingWorkloads();
    }
    AUMWorkstationCritical("All functions have stopped looping.");
    AUMWorkstationCritical("**End of the AUM Workstation****");
    return 0;
}

#else
#error Can only build on Windows.
#endif