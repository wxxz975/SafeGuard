#pragma once
#include <unordered_map>
#include <memory>
#include <string>

#include "Networks/WebPageHandler.h"
#include "Networks/HttpResponse.h"
#include "Networks/Command.h"

namespace Networks
{


    class MainWebPageHandler: public WebPageHandler
    {
    public:
        MainWebPageHandler();
        ~MainWebPageHandler() = default;

        bool HandleGetImpl(HttpResponse* resp, struct mg_connection *conn) override;

    private:
        std::unordered_map<std::string, std::unique_ptr<Command>> m_cmds;
    };
    
    
    
} // namespace Networks
