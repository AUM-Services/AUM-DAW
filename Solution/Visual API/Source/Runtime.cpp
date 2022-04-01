// Written by Eric Dee

#include "Runtime.h"

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

namespace Runtime {

    int ExampleDelegate() { return 4; };

    class AUMRuntime : public AUMApplication {
    public:
        void InitWorkstationItems() override;
    };

    void AUMRuntime::InitWorkstationItems()
    {
        AUMPluginCritical("*Start of init workstation items****");
        this->WorkstationItems.emplace_back(make_unique<AUMWorkstationItem>());
        this->WorkstationItems.emplace_back(make_unique<AUMWorkstationItem>(ExampleDelegate, "ExampleRuntime"));
        this->WorkstationItems.emplace_back(make_unique<IAUMGraphicsOutput>("GLFW GUI"));
    }

}

#ifndef AUM_DIGITAL_AUDIO_API_H
using namespace Runtime;
#define AUM_DIGITAL_AUDIO_API_H
#endif // !AUM_DIGITAL_AUDIO_API_H

AUMApplication AUMWorkAudio::AUMWorkstationInitMain() {

    AUMRuntime newRuntime = Runtime::AUMRuntime();
    newRuntime.InitWorkstationItems();
    AUMPluginCritical("****End of init workstation items****************");
    
    AUMWorkstationItemFactory itemFactory = AUMWorkstationItemFactory();
    auto exampleDelegate = []()
    {
        return 4;
    };
    printf("\n- -- --- ----\n");
    printf("How to create plugins:\n");
    printf("- -- --- ----\n");
    itemFactory.CreateItemFunctionality(exampleDelegate, "ExamplePlugin");
    printf("\n- -- --- ----\n");
    printf("How to create runtimes:\n");
    printf("- -- --- ----\n");

    return newRuntime;
};