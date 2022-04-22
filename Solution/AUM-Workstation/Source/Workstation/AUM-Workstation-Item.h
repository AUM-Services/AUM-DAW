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
        //Field
        string Name;
        bool IsAvailable;
        bool IsRunning;

        //Member
        typedef int (*Integer_Delegate)();

        //Method
        virtual ~AUMWorkstationItem() {}
        virtual void PresentationMode() const;
        void MakeAvailable();
        int RunAssignments();
        int EntryPoint() const;
    
    private:
        //Method
        virtual int Run();

        //Member
        int(*DelegatedEntry)();

    public:
        //Ctr
        AUMWorkstationItem(string name = "Default Name");
        AUMWorkstationItem(Integer_Delegate entryPoint, string name = "Default Name");
    };

}