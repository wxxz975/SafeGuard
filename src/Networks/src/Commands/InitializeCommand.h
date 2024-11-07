#pragma once
#include "Networks/Command.h"

namespace Networks
{
    class InitializeCommand: public Command
    {
    public:
        InitializeCommand() = default;
        ~InitializeCommand() = default;
        
        virtual std::string Execute(const HttpRequest& req) override;
    };
    
   
    
} // namespace Networks
