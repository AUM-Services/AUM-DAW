//Written by Eric Dee.

#include "Log.h"

namespace AUMLog {

    // Static/class only.
    shared_ptr<spdlog::logger> Log::static_statusLogger;
    shared_ptr<spdlog::logger> Log::static_pluginLogger;

    shared_ptr<spdlog::logger> &Log::GetStatusLogger
        ()
    {
        return static_statusLogger;
    }
    
    shared_ptr<spdlog::logger> &Log::GetPluginLogger
        ()
    {
        return static_pluginLogger;
    }

    void Log::AppendSettingsToAllLoggers
        (std::string statusString, std::string pluginString)
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        static_statusLogger = spdlog::stderr_color_mt(statusString);
        static_statusLogger->set_level(spdlog::level::trace);
        static_pluginLogger = spdlog::stderr_color_mt(pluginString);
        static_pluginLogger->set_level(spdlog::level::trace);
    }

}