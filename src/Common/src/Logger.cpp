#include "Common/Logger.h"
#include "Common/AppInfo.h"


namespace Common
{
    void Logger::OutputToFile(const std::string& filepath)
    {   
        m_logger = spdlog::basic_logger_mt(AppName, filepath);
        if(m_logger) m_output2file = true;
    }

    void Logger::SetLevel(LogLevel level)
    {
        spdlog::level::level_enum spdlevel = spdlog::level::info;
        switch (level)
        {
        case LogLevel::TRACE:       spdlevel = spdlog::level::trace;    break;
        case LogLevel::DEBUG:       spdlevel = spdlog::level::debug;    break;
        case LogLevel::INFO:        spdlevel = spdlog::level::info;     break;
        case LogLevel::WARN:        spdlevel = spdlog::level::warn;     break;
        case LogLevel::ERROR:       spdlevel = spdlog::level::err;      break;
        case LogLevel::CRITICAL:    spdlevel = spdlog::level::critical; break;
        }

        spdlog::set_level(spdlevel);
    }

   

} // namespace Common
