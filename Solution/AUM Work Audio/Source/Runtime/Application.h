//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_POINTERS_H
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_POINTERS_H
#endif // !AUM_WORK_AUDIO_POINTERS_H

#ifndef AUM_WORK_AUDIO_LOGS_H
#include "../Log/Log.h"
using namespace AUMLog;
#define AUM_WORK_AUDIO_LOGS_H
#endif // !AUM_WORK_AUDIO_LOGS_H

#ifndef AUM_WORK_AUDIO_HOST_FUNCTIONS_H
#include "../Workstation/WorkStationItem.h"
using namespace AUMWorkstation;
#define AUM_WORK_AUDIO_HOST_FUNCTIONS_H
#endif // !AUM_WORK_AUDIO_HOST_FUNCTIONS_H

namespace AUMWorkAudio {

    class AUMApplication {
    public:
        vector<unique_ptr<AUMWorkstationItem>> WorkstationItems;
        virtual void InitWorkstationItems();
        void MakeAllWorkItemsAvailable();
        void CompletePendingWorkloads();
    };

    // The compiler generates errors if this is moved into a .cpp file.
    void AUMApplication::InitWorkstationItems() {
        AUMAPICritical("You have no workstation items. You must override AUMApplication::InitWorkstationItems()");
    }

    /// <summary>
    /// Namespace scoped.
    /// </summary>
    /// <returns>
    /// An AUMApplication class that contains interface implementations based off of the AUMWorkstationItems abstraction.
    /// Each interface is required to implement the run method, as it gets called in the main entrypoint.
    /// </returns>
    AUMApplication AUMWorkstationInitMain();

    void AUMApplication::MakeAllWorkItemsAvailable() {
        for (auto const& runtime : this->WorkstationItems)
        {
            runtime->MakeAvailable();
        }
    }

    void AUMApplication::CompletePendingWorkloads() {
        for (auto const& runtime : this->WorkstationItems)
        {
            runtime->EntryPoint();
            runtime->RunAssignments();
        }
    }

}