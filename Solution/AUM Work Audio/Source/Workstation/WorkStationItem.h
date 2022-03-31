// Written by Eric Dee

#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_IO_H
#include <stdio.h>
#define AUM_IO_H
#endif // !AUM_IO_H

#ifndef AUM_LOGS_H
#include "../Log/Log.h"
using namespace AUMLogs;
#define AUM_LOGS_H
#endif // !AUM_LOGS_H

#ifndef AUM_POINTERS_H
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_POINTERS_H
#endif // !AUM_POINTERS_H

namespace AUMWorkstation {

    class AUMBuildMacro AUMWorkstationItem {
    public:
        virtual int Run();
    };

    class AUMBuildMacro AUMWorkstationFactory {
    public:
        virtual AUMWorkstationItem* CreateFunctionality();
    };

    /// <summary>
    /// This is going to need some form of accessor method
    /// to assign runtimes as a vector array
    /// and also keep them inaccessible. AKA protected.
    /// </summary>
    /// <returns>Functions* {Any}</returns>
    AUMWorkstationItem* AUMWorkstationInitMain();
}