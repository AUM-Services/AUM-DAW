#pragma once

#ifndef AUM_WORK_AUDIO_BUILD_H
#include "../Build.h"
#define AUM_WORK_AUDIO_BUILD_H
#endif // !AUM_WORK_AUDIO_BUILD_H

#ifndef AUM_POINTERS
#include <memory.h>
using namespace std;
#define AUM_POINTERS
#endif

// I use vcpkg to maintain C++ includes, but this has been included in the Ext-Dependencies folder.
// If needed, use #include "Vendors/spdlog/include/spdlog/spdlog.h".
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace AUMLogs {
    static class AUMBuildMacro Log {
    public:
        static void Init();
        static shared_ptr<spdlog::logger> &GetStatusLogger();
        static shared_ptr<spdlog::logger> &GetPluginLogger();
    private:
        static shared_ptr<spdlog::logger> static_statusLogger;
        static shared_ptr<spdlog::logger> static_pluginLogger;
    };

#define AUMStatusInfo(...) Log::GetStatusLogger()->info(__VA_ARGS__)
#define AUMStatusTrace(...) Log::GetStatusLogger()->trace(__VA_ARGS__)
#define AUMStatusWarn(...) Log::GetStatusLogger()->warn(__VA_ARGS__)
#define AUMStatusError(...) Log::GetStatusLogger()->error(__VA_ARGS__)
#define AUMPluginInfo(...) Log::GetStatusLogger()->info(__VA_ARGS__)
#define AUMPluginTrace(...) Log::GetStatusLogger()->trace(__VA_ARGS__)
#define AUMPluginWarn(...) Log::GetStatusLogger()->warn(__VA_ARGS__)
#define AUMPluginError(...) Log::GetStatusLogger()->error(__VA_ARGS__)
}