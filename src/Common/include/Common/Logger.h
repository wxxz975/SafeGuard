#pragma once
#include <string>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Singleton.h"

namespace Common
{

    /*
        format use {}
    */
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL
    };

    class Logger: public Singleton<Logger>
    {
    public:
        Logger() = default;
        ~Logger() = default;

        void OutputToFile(const std::string& filepath);

        void SetLevel(LogLevel level);

        template<typename... Args>
        void Print(LogLevel level, const std::string& fmt, Args&&... args)
        {
            auto formatted_str = fmt::format(fmt, std::forward<Args>(args)...);
            
            switch (level)
            {
                case LogLevel::TRACE: {    
                    spdlog::trace(formatted_str);
                    if(m_output2file) m_logger->trace(formatted_str);
                    break;
                }
                case LogLevel::DEBUG: {  
                    spdlog::debug(formatted_str);
                    if(m_output2file) m_logger->debug(formatted_str);
                    break;
                }
                case LogLevel::INFO: {
                    spdlog::info(formatted_str);
                    if(m_output2file) m_logger->info(formatted_str);
                    break;
                }
                case LogLevel::WARN: {            
                    spdlog::warn(formatted_str);
                    if(m_output2file) m_logger->warn(formatted_str);
                    break;
                }
                case LogLevel::ERROR: {
                    spdlog::error(formatted_str);
                    if(m_output2file) m_logger->error(formatted_str);
                    break;
                }
                case LogLevel::CRITICAL: {
                    spdlog::critical(formatted_str);
                    if(m_output2file) m_logger->critical(formatted_str);
                    break;
                }
            }
        }
        
        
    private:
        bool m_output2file = false;

        std::shared_ptr<spdlog::logger> m_logger = nullptr;
    };
    
    
#define logTrace(fmt, ...)      Logger::Instance()->Print(Common::LogLevel::TRACE, fmt, ##__VA_ARGS__)
#define logWarn(fmt, ...)       Logger::Instance()->Print(Common::LogLevel::WARN, fmt, ##__VA_ARGS__)
#define logDebug(fmt, ...)      Logger::Instance()->Print(Common::LogLevel::DEBUG, fmt, ##__VA_ARGS__)
#define logInfo(fmt, ...)       Logger::Instance()->Print(Common::LogLevel::INFO, fmt, ##__VA_ARGS__)
#define logError(fmt, ...)      Logger::Instance()->Print(Common::LogLevel::ERROR, fmt, ##__VA_ARGS__)
#define logCritical(fmt, ...)   Logger::Instance()->Print(Common::LogLevel::CRITICAL, fmt, ##__VA_ARGS__)    

} // namespace Common

