//Written by Eric Dee.

#include "Runtime.h"

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

///////////////////////////////////////////////////////////
////                                                   ////
//// Design the API, and tell it which runtimes to use ////
////                                                   ////
///////////////////////////////////////////////////////////

namespace Runtime {

    class AUMRuntime : public AUMApplication {
    public:
        void InitWorkstationItems() override;
    };

    void AUMRuntime::InitWorkstationItems()
    {
        this->WorkstationItems.emplace_back(make_unique<IAUMGraphicsOutput>("GLFW GUI"));
    }

}

/////////////////////////////////////////////
////                                     ////
//// Send them to the application's host ////
////                                     ////
/////////////////////////////////////////////

#ifndef AUM_DIGITAL_AUDIO_API_H
using namespace Runtime;
#define AUM_DIGITAL_AUDIO_API_H
#endif // !AUM_DIGITAL_AUDIO_API_H

#ifndef AUM_BUILD_VALIDATION_H
#define VALIDATE_BUILD false
#define AUM_BUILD_VALIDATION_H
#endif // !AUM_BUILD_VALIDATION

#ifndef AUM_RUNTIME_TESTS_H
#include "Unit-Testing/RuntimeUnitTest.h"
using namespace AUMUnitTest;
#define AUM_RUNTIME_TESTS_H
#endif // !AUM_UNIT_TESTING_H

AUMApplication AUMWorkAudio::AUMWorkstationInitMain() {
    AUMPluginCritical("*Start of AUM Runtime API items****");
    AUMRuntime newRuntime = AUMRuntime();
    newRuntime.InitWorkstationItems();
    if (VALIDATE_BUILD)
    {
        _RuntimeTests.ValidateRuntimeFunctionality(&newRuntime.WorkstationItems);
    }
    AUMPluginCritical("****End of AUM Runtime API items****************");
    return newRuntime;
};