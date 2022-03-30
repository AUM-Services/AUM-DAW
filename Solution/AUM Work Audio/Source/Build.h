#pragma once

#ifdef AUMPlatformWindows
    #ifdef AUMBuildDLL
        #define AUMBuildMacro __declspec(dllexport)
    #else
        #define AUMBuildMacro __declspec(dllimport)
    #endif
#else
    #error Can only build on Windows.
#endif