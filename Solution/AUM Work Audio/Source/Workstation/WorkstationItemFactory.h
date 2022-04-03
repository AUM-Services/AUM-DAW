//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

#ifndef AUM_WORK_AUDIO_POINTERS_H
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_POINTERS_H
#endif // !AUM_WORK_AUDIO_POINTERS_H

#ifndef AUM_WORK_AUDIO_LOGS_H
#include "../Log/Log.h"
using namespace AUMLog;
#define AUM_WORK_AUDIO_LOGS_H
#endif // !AUM_WORK_AUDIO_LOGS_H

namespace AUMWorkstation {

    class AUMBuildMacro AUMWorkstationItemFactory {
    public:
        typedef int (*IntegerFunction)();
        virtual void PresentationMode(string name) const;
        virtual void CreateItemFunctionality(IntegerFunction runDelegate, string name) const;
    };

}
