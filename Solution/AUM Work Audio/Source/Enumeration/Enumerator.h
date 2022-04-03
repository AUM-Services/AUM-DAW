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

#include "EnumeratorAbstract.h"

namespace AUMEnumeration {

    class AUMBuildMacro AUMEnumerator : public AUMEnumeratorAbstract{
    public:
        AUMEnumerator() {};
        AUMEnumerator(const char* name, string strings[], int elementCount)
            : AUMEnumeratorAbstract(name, strings, elementCount) {};
        enum AUMEnum{ AUM_UNDEFINED, AUM_SUCCESS, AUM_TRACE, AUM_DEBUG, AUM_ERROR, AUM_CRITICAL };
    };

}