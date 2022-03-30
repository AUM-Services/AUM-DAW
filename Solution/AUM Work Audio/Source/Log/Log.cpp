#include "Log.h"

namespace AUMLogs {

    // Static/class only.
    shared_ptr<spdlog::logger> Log::static_statusLogger;
    shared_ptr<spdlog::logger> Log::static_pluginLogger;

    shared_ptr<spdlog::logger> &Log::GetStatusLogger() {
        return static_statusLogger;
    }
    shared_ptr<spdlog::logger> &Log::GetPluginLogger() {
        return static_pluginLogger;
    }
    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        static_statusLogger = spdlog::stderr_color_mt("AUM Work Audio log");
        static_statusLogger->set_level(spdlog::level::trace);
        static_pluginLogger = spdlog::stderr_color_mt("Plugin log");
        static_pluginLogger->set_level(spdlog::level::trace);
    }
}