//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_BUILD_H
#include "../AUM-Workstation-Build.h"
#define AUM_WORKSTATION_BUILD_H
#endif // !AUM_WORKSTATION_BUILD_H

#ifndef AUM_WORKSTATION_IO_H
#include <IO/AUM-Workstation-IO.h>
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

#ifndef AUM_VENDORS_SPDLOG_H
#include "Vendors/spdlog/include/spdlog/spdlog.h".
#include "Vendors/spdlog/include/spdlog/sinks/stdout_color_sinks.h"
#define AUM_VENDORS_SPDLOG_H
#endif // !AUM_VENDORS_SPDLOG_H

namespace AUM_Workstation_Log {

    static class AUMWorkstationBuildMacro AUMWorkstationLog {
    public:
        AUMWorkstationLog(const AUMWorkstationLog&) = delete;
        static void AppendSettingsToAllLoggers(string workstationString, string runtimeString, string itemString);
        static shared_ptr<spdlog::logger>& GetWorkstationLogger();
        static shared_ptr<spdlog::logger>& GetRuntimeLogger();
        static shared_ptr<spdlog::logger>& GetItemLogger();
    private:
        static shared_ptr<spdlog::logger> workstationLogger;
        static shared_ptr<spdlog::logger> runtimeLogger;
        static shared_ptr<spdlog::logger> itemLogger;
    };

#define AUMWorkstationInfo(...) AUMWorkstationLog::GetWorkstationLogger()->info(__VA_ARGS__)
#define AUMWorkstationTrace(...) AUMWorkstationLog::GetWorkstationLogger()->trace(__VA_ARGS__)
#define AUMWorkstationWarn(...) AUMWorkstationLog::GetWorkstationLogger()->warn(__VA_ARGS__)
#define AUMWorkstationDebug(...) AUMWorkstationLog::GetWorkstationLogger()->debug(__VA_ARGS__)
#define AUMWorkstationCritical(...) AUMWorkstationLog::GetWorkstationLogger()->critical(__VA_ARGS__)
#define AUMWorkstationError(...) AUMWorkstationLog::GetWorkstationLogger()->error(__VA_ARGS__)

#define AUMWorkstationRuntimeInfo(...) AUMWorkstationLog::GetRuntimeLogger()->info(__VA_ARGS__)
#define AUMWorkstationRuntimeTrace(...) AUMWorkstationLog::GetRuntimeLogger()->trace(__VA_ARGS__)
#define AUMWorkstationRuntimeWarn(...) AUMWorkstationLog::GetRuntimeLogger()->warn(__VA_ARGS__)
#define AUMWorkstationRuntimeDebug(...) AUMWorkstationLog::GetRuntimeLogger()->debug(__VA_ARGS__)
#define AUMWorkstationRuntimeCritical(...) AUMWorkstationLog::GetRuntimeLogger()->critical(__VA_ARGS__)
#define AUMWorkstationRuntimeError(...) AUMWorkstationLog::GetRuntimeLogger()->error(__VA_ARGS__)

#define AUMWorkstationItemInfo(...) AUMWorkstationLog::GetItemLogger()->info(__VA_ARGS__)
#define AUMWorkstationItemTrace(...) AUMWorkstationLog::GetItemLogger()->trace(__VA_ARGS__)
#define AUMWorkstationItemWarn(...) AUMWorkstationLog::GetItemLogger()->warn(__VA_ARGS__)
#define AUMWorkstationItemDebug(...) AUMWorkstationLog::GetItemLogger()->debug(__VA_ARGS__)
#define AUMWorkstationItemCritical(...) AUMWorkstationLog::GetItemLogger()->critical(__VA_ARGS__)
#define AUMWorkstationItemError(...) AUMWorkstationLog::GetItemLogger()->error(__VA_ARGS__)

}