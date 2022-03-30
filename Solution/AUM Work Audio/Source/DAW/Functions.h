#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_IO
#include <stdio.h>
#define AUM_IO
#endif // !AUM_IO

namespace AUMFunctions {
    class AUMBuildMacro Functions {
    public:
        Functions();
        virtual ~Functions();
        void GetAddresses();
        void Run();
    };

    /// <summary>
    /// Should be defined in the client, or passed around as a context.
    /// Acts as a virtual constructor.
    /// </summary>
    /// <returns>Functions* {Any}</returns>
    Functions* CreateFunctionality();
}
