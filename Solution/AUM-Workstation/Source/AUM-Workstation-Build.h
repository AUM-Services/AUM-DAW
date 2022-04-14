//Written by Eric Dee.

#pragma once

#ifdef AUMWorkstationPlatformWindows
    #ifdef AUMWorkstationBuildDLL
        #define AUMWorkstationBuildMacro __declspec(dllexport)
    #else
        #define AUMWorkstationBuildMacro __declspec(dllimport)
    #endif
#else
    #error Can only build on Windows.
#endif