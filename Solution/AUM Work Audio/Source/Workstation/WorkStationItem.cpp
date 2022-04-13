//Written by Eric Dee.

#include "WorkStationItem.h"

namespace AUMWorkstation {

    void AUMWorkstationItem::MakeAvailable() {
        this->IsAvailable = true;
    }

    /// <summary>
    /// Placeholder delegate to know if it has been set or not.
    /// </summary>
    /// <returns></returns>
    int DefaultDelegate() { return 0xff; };

    AUMWorkstationItem::AUMWorkstationItem(string name){
        this->Name = name;
        AUMPluginTrace("Constructing {0}.", this->Name);
        this->DelegatedEntry = DefaultDelegate;
    }

    AUMWorkstationItem::AUMWorkstationItem(Integer_Delegate entryPoint, string name) {
        this->Name = name;
        this->DelegatedEntry = entryPoint;
    }

    void AUMWorkstationItem::PresentationMode() const {
        if (this->Name == "Validation Name")
        {
            AUMAPIInfo("- ----");
            AUMAPIInfo("How to create AUM runtimes:");
            AUMAPIInfo("---- ----------------");
            AUMAPIInfo("Welcome to an AUM Workstation item.");
            AUMAPIInfo("Create a class that inherits the AUMWorkStationItem to define the 'Run()' method.");
            AUMAPIInfo("Then add it to the WorkstationItems vector using an instance of the Application class.");
            AUMAPIWarn("New status:");
            AUMAPITrace("Status: Not yet run, {0}.", this->Name);
        }
    }

    int AUMWorkstationItem::RunAssignments() {
        return this->Run();
    }

    int AUMWorkstationItem::EntryPoint() const {
        return this->DelegatedEntry();
    }

    int AUMWorkstationItem::Run() {
        this->PresentationMode();
        AUMAPIWarn("New status:");
        AUMAPITrace("Status: {0}, {1}.", this->DelegatedEntry(), this->Name);
        return 0;
    }

}