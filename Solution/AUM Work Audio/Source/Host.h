//Written by Eric Dee.

#pragma once

#ifdef AUMPlatformWindows

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

#ifndef AUM_WORK_AUDIO_HOST_FUNCTIONS_H
#include "Enumeration/Enumerator.h"
#include "Workstation/WorkStationItem.h"
#include "Workstation/WorkstationItemFactory.h"
#include "Runtime/Application.h"
using namespace AUMWorkstation;
using namespace AUMWorkAudio;
#define AUM_WORK_AUDIO_HOST_FUNCTIONS_H
#endif // !AUM_WORK_AUDIO_HOST_FUNCTIONS_H

int main(int argc, char** argv) {
    Log::AppendSettingsToAllLoggers("AUM Work Audio log", "AUM Plugin log");
    AUMAPIDebug("*Start of the Host application****");
    AUMApplication DAWRuntimes = AUMWorkAudio::AUMWorkstationInitMain();
    for (auto const& runtime : DAWRuntimes.WorkstationItems)
    {
        runtime->Start();
    }
    AUMAPICritical("All functions have stopped looping.");
    AUMAPIDebug("****End of the Host application****************");
    return 0;
}

#else
#error Can only build on Windows.
#endif