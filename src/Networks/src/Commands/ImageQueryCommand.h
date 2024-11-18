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

    private:
        std::string ParseFilename(const std::string& uri);
    };
    
    
} // namespace Networks
