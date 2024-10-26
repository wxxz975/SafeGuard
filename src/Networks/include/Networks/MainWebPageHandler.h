#pragma once
#include "WebPageHandler.h"
#include "HttpResponse.h"

namespace Communications
{
#define QueryNewTask "QueryResult"


    class MainWebPageHandler: public WebPageHandler
    {
    public:
        MainWebPageHandler() = default;
        ~MainWebPageHandler() = default;

        bool handleGetImpl(HttpResponse* resp, struct mg_connection *conn) override;

    private:
        std::string executeQuery();
    };
    
    
    
} // namespace Communications
