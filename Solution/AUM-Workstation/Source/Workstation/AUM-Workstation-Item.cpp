//Written by Eric Dee.

#include "AUM-Workstation-Item.h"

namespace AUM_Workstation_Item {

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
        AUMWorkstationRuntimeTrace("Constructing {0}.", this->Name);
        this->DelegatedEntry = DefaultDelegate;
    }

    AUMWorkstationItem::AUMWorkstationItem(Integer_Delegate entryPoint, string name) {
        this->Name = name;
        this->DelegatedEntry = entryPoint;
    }

    void AUMWorkstationItem::PresentationMode() const {
        if (this->Name == "Validation Name")
        {
            AUMWorkstationRuntimeInfo("- --");
            AUMWorkstationRuntimeInfo("How to create AUM runtimes:");
            AUMWorkstationRuntimeInfo("-- ----");
            AUMWorkstationRuntimeInfo("Welcome to an AUM Workstation item.");
            AUMWorkstationRuntimeInfo("Create a class that inherits the AUMWorkStationItem to define the 'Run()' method.");
            AUMWorkstationRuntimeInfo("Then add it to the WorkstationItems vector using an instance of the Application class.");
            AUMWorkstationRuntimeWarn("New status:");
            AUMWorkstationRuntimeTrace("Status: Not yet run, {0}.", this->Name);
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
        AUMWorkstationRuntimeWarn("New status:");
        AUMWorkstationRuntimeTrace("Status: {0}, {1}.", this->DelegatedEntry(), this->Name);
        return 0;
    }

}