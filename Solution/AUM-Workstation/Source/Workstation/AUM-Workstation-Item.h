//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_LOG_H
#include "../Log/AUM-Workstation-Log.h"
using namespace AUM_Workstation_Log;
#define AUM_WORKSTATION_LOG_H
#endif // !AUM_WORKSTATION_LOG_H

#ifndef AUM_WORKSTATION_BUILD_H
#include "../AUM-Workstation-Build.h"
#define AUM_WORKSTATION_BUILD_H
#endif // !AUM_WORKSTATION_BUILD_H

#ifndef AUM_WORKSTATION_IO_H
#include <IO/AUM-Workstation-IO.h>
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

namespace AUM_Workstation_Item {

    struct AUMWorkstationBuildMacro AUMWorkstationItem {
    public:
        typedef int (*Integer_Delegate)();
        string Name;
        AUMWorkstationItem(string name = "Default Name");
        AUMWorkstationItem(Integer_Delegate entryPoint, string name = "Default Name");
        virtual ~AUMWorkstationItem() {}
        virtual void PresentationMode() const;
        bool IsAvailable;
        void MakeAvailable();
        int RunAssignments();
        int EntryPoint() const;
    private:
        virtual int Run();
        int(*DelegatedEntry)();
    };

}