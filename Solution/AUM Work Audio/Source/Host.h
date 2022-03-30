#pragma once

#ifdef AUMPlatformWindows

#ifndef AUM_HOST_FUNCTIONS
using namespace AUMFunctions;
extern Functions* AUMFunctions::CreateFunctionality();
#define AUM_HOST_FUNCTIONS
#endif

#ifndef AUM_HOST_LOGS
using namespace AUMLogs;
#define AUM_HOST_LOGS
#endif

int main(int argc, char** argv) {
    Log::Init();
    auto gui = CreateFunctionality();
    gui->Run();
    delete gui;
}

#else
#error Can only build on Windows.
#endif