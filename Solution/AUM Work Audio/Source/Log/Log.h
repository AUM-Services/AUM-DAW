//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_WORK_AUDIO_POINTERS_H
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_POINTERS_H
#endif // !AUM_WORK_AUDIO_POINTERS_H

// I use vcpkg to maintain C++ includes, but this has been included in the Ext-Dependencies folder.
// If needed, use #include "Vendors/spdlog/include/spdlog/spdlog.h".
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace AUMLog {

    static class AUMBuildMacro Log {
    public:
        Log(const Log&) = delete;
        static void AppendSettingsToAllLoggers(string statusString, string pluginString);
        static shared_ptr<spdlog::logger>& GetStatusLogger();
        static shared_ptr<spdlog::logger>& GetPluginLogger();
    private:
        static shared_ptr<spdlog::logger> static_statusLogger;
        static shared_ptr<spdlog::logger> static_pluginLogger;
    };

#define AUMAPIInfo(...) Log::GetStatusLogger()->info(__VA_ARGS__)
#define AUMAPITrace(...) Log::GetStatusLogger()->trace(__VA_ARGS__)
#define AUMAPIWarn(...) Log::GetStatusLogger()->warn(__VA_ARGS__)
#define AUMAPIDebug(...) Log::GetStatusLogger()->debug(__VA_ARGS__)
#define AUMAPICritical(...) Log::GetStatusLogger()->critical(__VA_ARGS__)
#define AUMAPIError(...) Log::GetStatusLogger()->error(__VA_ARGS__)
#define AUMPluginInfo(...) Log::GetPluginLogger()->info(__VA_ARGS__)
#define AUMPluginTrace(...) Log::GetPluginLogger()->trace(__VA_ARGS__)
#define AUMPluginWarn(...) Log::GetPluginLogger()->warn(__VA_ARGS__)
#define AUMPluginDebug(...) Log::GetPluginLogger()->debug(__VA_ARGS__)
#define AUMPluginCritical(...) Log::GetPluginLogger()->critical(__VA_ARGS__)
#define AUMPluginError(...) Log::GetPluginLogger()->error(__VA_ARGS__)

}