// Written by Eric Dee

#pragma once

#ifdef AUMPlatformWindows

#ifndef AUM_HOST_LOGS_N
using namespace AUMLogs;
#define AUM_HOST_LOGS_N
#endif

#ifndef AUM_HOST_FUNCTIONS
using namespace AUMWorkstation;
extern AUMWorkstationItem* AUMWorkstation::AUMWorkstationInitMain();
#define AUM_HOST_FUNCTIONS
#endif

#ifndef AUM_POINTERS_H
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_POINTERS_H
#endif // !AUM_POINTERS_H

int main(int argc, char** argv) {
    Log::AppendSettingsToAllLoggers("AUM Work Audio log", "Plugin log");
    AUMWorkstationItem* Runtimes = AUMWorkstation::AUMWorkstationInitMain();
    Runtimes->Run();
    delete Runtimes;
}

#else
#error Can only build on Windows.
#endif