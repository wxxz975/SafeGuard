#pragma once
#include "Networks/Command.h"


namespace Networks
{
    // fixme: this need database
    class HistoryQueryCommand: public Command
    {
    public:
        HistoryQueryCommand() = default;
        ~HistoryQueryCommand() = default;
        
        virtual std::string Execute(const HttpRequest& req) override;
    };
    
    
    
} // namespace Networks
