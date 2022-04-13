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

#include "Validator/APIValidator.h"
using namespace AUMAPIValidation;

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
RuntimeValidator apiValidator = RuntimeValidator();
#define VALIDATE_BUILD false
#define AUM_DIGITAL_AUDIO_API_H
#endif // !AUM_DIGITAL_AUDIO_API_H

AUMApplication AUMWorkAudio::AUMWorkstationInitMain() {
    AUMPluginCritical("*Start of AUM Visual API items****");
    AUMRuntime newRuntime = AUMRuntime();
    newRuntime.InitWorkstationItems();
    if (VALIDATE_BUILD)
    {
        apiValidator.ValidateRuntimeFunctionality(&newRuntime.WorkstationItems);
    }
    AUMPluginCritical("****End of AUM Visual API items****************");
    return newRuntime;
};