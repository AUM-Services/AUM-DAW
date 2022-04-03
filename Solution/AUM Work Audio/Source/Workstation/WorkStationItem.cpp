//Written by Eric Dee.

#include "WorkStationItem.h"

namespace AUMWorkstation {

    int DefaultDelegate() { return 16; };

    AUMWorkstationItem::AUMWorkstationItem(){
        this->Name = "DefaultRuntime";
        this->DelegateRun = DefaultDelegate;
    }

    AUMWorkstationItem::AUMWorkstationItem(IntegerFunction runDelegate, string name) {
        this->Name = name;
        this->DelegateRun = runDelegate;
    }

    void AUMWorkstationItem::PresentationMode() const {
        if (this->Name == "ExampleRuntime")
        {
            AUMAPIInfo("Welcome to AUM Work Audio API.");
            AUMAPIInfo("Method #1 for creating runtimes:");
            AUMAPIInfo("Create a class that inherits the AUMWorkStationItem to define the 'Run()' method.");
        }
    }

    int AUMWorkstationItem::Start() const {
        return this->Run();
    }

    int AUMWorkstationItem::StartDelegate() const {
        return this->DelegateRun();
    }

    int AUMWorkstationItem::Run() const {
        this->PresentationMode();
        AUMAPIWarn("Plugin status:");
        AUMAPIInfo("Status: {0}, {1}.", this->DelegateRun(), this->Name);
        AUMAPIInfo("____");
        return 0;
    }

}