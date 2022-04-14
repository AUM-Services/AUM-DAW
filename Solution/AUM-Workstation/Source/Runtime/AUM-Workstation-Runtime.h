//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_LOG_H
#include "../Log/AUM-Workstation-Log.h"
using namespace AUM_Workstation_Log;
#define AUM_WORKSTATION_LOG_H
#endif // !AUM_WORKSTATION_LOG_H

#ifndef AUM_WORKSTATION_ITEM_H
#include "../Workstation/AUM-Workstation-Item.h"
using namespace AUM_Workstation_Item;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_WORKSTATION_IO_H
#include "IO/AUM-Workstation-IO.h"
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

namespace AUM_Workstation_Runtime {

    class AUMWorkstationRuntime {
    public:
        vector<unique_ptr<AUMWorkstationItem>> WorkstationItems;
        virtual void InitWorkstationItems();
        void MakeAllWorkItemsAvailable();
        void CompletePendingWorkloads();
    };

    // The compiler generates errors if this is moved into a .cpp file.
    void AUMWorkstationRuntime::InitWorkstationItems() {
        AUMWorkstationCritical("You have no workstation items. You must override AUMApplication::InitWorkstationItems()");
    }

    /// <summary>
    /// Namespace scoped.
    /// </summary>
    /// <returns>
    /// An AUMApplication class that contains interface implementations based off of the AUMWorkstationItems abstraction.
    /// Each interface is required to implement the run method, as it gets called in the main entrypoint.
    /// </returns>
    AUMWorkstationRuntime AUMWorkstationInitMain();

    void AUMWorkstationRuntime::MakeAllWorkItemsAvailable() {
        for (auto const& runtime : this->WorkstationItems)
        {
            runtime->MakeAvailable();
        }
    }

    void AUMWorkstationRuntime::CompletePendingWorkloads() {
        for (auto const& runtime : this->WorkstationItems)
        {
            runtime->EntryPoint();
            runtime->RunAssignments();
        }
    }

}