#pragma once
#include <string>
#include "Networks/HttpRequest.h"
namespace Networks
{
    class Command
    {
    public:
        Command() = default;
        virtual ~Command() = default;

        virtual std::string Execute(const HttpRequest& req) = 0;
    };    
} // namespace Networks


