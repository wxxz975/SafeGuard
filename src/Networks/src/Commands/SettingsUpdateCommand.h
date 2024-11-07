#pragma once
#include "Networks/Command.h"

namespace Networks
{
    class SettingsUpdateCommand: public Command
    {

    public:
        SettingsUpdateCommand() = default;
        ~SettingsUpdateCommand() = default;

        virtual std::string Execute(const HttpRequest& req) override;

    private:
        bool Check(float v);
    };
    
   
    
    
} // namespace Networks
