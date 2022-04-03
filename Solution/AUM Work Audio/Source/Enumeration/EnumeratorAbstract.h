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

namespace AUMEnumeration {

    /// <summary>
    /// Class base to runtime enums; allows enum inheritance to be local, and mapping.
    /// </summary>
    class AUMBuildMacro AUMEnumeratorAbstract {
    public:
        AUMEnumeratorAbstract();
        AUMEnumeratorAbstract(string strings[], int elementCount);
        virtual map<int, string> MakeMap(map<int, string> mapReference, string strings[], int elementCount) const;
        enum AUMEnum{ AUM_UNDEFINED };
        map<int, string> Map = { {0, "AUM_NULL"} };
    };

}