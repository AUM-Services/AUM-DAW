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

int main(int argc, char** argv) {
    AUMWorkstationLog::AppendSettingsToAllLoggers("AUM Workstation log", "AUM Workstation runtime log", "AUM Workstation item log");
    AUMWorkstationCritical("*Start of the Host application**");
    AUMWorkstationRuntime DAWRuntimes = AUMWorkstationInitMain();
    DAWRuntimes.MakeAllWorkItemsAvailable();
    // While there is a primary window:
    while (DAWRuntimes.WorkstationItems[0]->IsAvailable)
    {
        DAWRuntimes.CompletePendingWorkloads();
    }
    AUMWorkstationCritical("All functions have stopped looping.");
    AUMWorkstationCritical("**End of the Host application****");
    return 0;
}

#else
#error Can only build on Windows.
#endif