//Written by Eric Dee.

#include "AUM-Workstation-Log.h"

namespace AUM_Workstation_Log {

    // Static/class only.
    shared_ptr<spdlog::logger> AUMWorkstationLog::workstationLogger;
    shared_ptr<spdlog::logger> AUMWorkstationLog::runtimeLogger;
    shared_ptr<spdlog::logger> AUMWorkstationLog::itemLogger;

    shared_ptr<spdlog::logger> & AUMWorkstationLog::GetWorkstationLogger
        ()
    {
        return AUMWorkstationLog::workstationLogger;
    }
    
    shared_ptr<spdlog::logger> & AUMWorkstationLog::GetRuntimeLogger
        ()
    {
        return AUMWorkstationLog::runtimeLogger;
    }

    shared_ptr<spdlog::logger>& AUMWorkstationLog::GetItemLogger
        ()
    {
        return AUMWorkstationLog::itemLogger;
    }

    void AUMWorkstationLog::AppendSettingsToAllLoggers
        (string workstationString, string runtimeString, string itemString)
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        
        AUMWorkstationLog::workstationLogger = spdlog::stderr_color_mt(workstationString);
        AUMWorkstationLog::workstationLogger->set_level(spdlog::level::trace);
        
        AUMWorkstationLog::runtimeLogger = spdlog::stderr_color_mt(runtimeString);
        AUMWorkstationLog::runtimeLogger->set_level(spdlog::level::trace);

        AUMWorkstationLog::itemLogger = spdlog::stderr_color_mt(itemString);
        AUMWorkstationLog::itemLogger->set_level(spdlog::level::trace);
    }

}