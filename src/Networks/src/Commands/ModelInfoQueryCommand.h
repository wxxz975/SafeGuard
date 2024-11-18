#pragma once
#include "Networks/Command.h"


namespace Networks
{

    class ModelInfoQueryCommand: public Command
    {
    public:
        ModelInfoQueryCommand() = default;
        ~ModelInfoQueryCommand() = default;

        virtual std::string Execute(const HttpRequest& req) override;
    };
    
    
    
    
} // namespace Networks
