//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

#ifndef AUM_WORK_AUDIO_LOGS_H
#include "../Log/Log.h"
using namespace AUMLog;
#define AUM_WORK_AUDIO_LOGS_H
#endif // !AUM_WORK_AUDIO_LOGS_H

namespace AUMWorkstation {

    struct AUMBuildMacro AUMWorkstationItem {
    public:
        typedef int (*IntegerFunction)();
        string Name;
        AUMWorkstationItem();
        AUMWorkstationItem(IntegerFunction runDelegate, string name);
        virtual ~AUMWorkstationItem() {}
        virtual void PresentationMode() const;
        int Start() const;
        int StartDelegate() const;

    private:
        virtual int Run() const;
        int(*DelegateRun)();
    };

}