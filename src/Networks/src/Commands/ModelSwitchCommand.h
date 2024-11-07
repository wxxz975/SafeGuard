#pragma once

#include "Networks/Command.h"



namespace Networks
{
    class ModelSwitchCommand: public Command
    {
    public:
        ModelSwitchCommand() = default;
        ~ModelSwitchCommand() = default;

        virtual std::string Execute(const HttpRequest& req) override;
    };
    
    
    
    
} // namespace Networks
