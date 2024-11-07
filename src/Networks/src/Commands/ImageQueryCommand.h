#pragma once
#include <string>
#include "Networks/Command.h"

namespace Networks
{
    class ImageQueryCommand: public Command
    {
    public:
        ImageQueryCommand() = default;
        ~ImageQueryCommand() = default;

        virtual std::string Execute(const HttpRequest& req) override;
    };
    
    
} // namespace Networks
