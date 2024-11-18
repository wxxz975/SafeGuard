#pragma once

#include "civetweb/CivetServer.h"

namespace Networks
{
    class HttpRequest;

    class HttpRequestParser
    {
    public:
        HttpRequestParser() = delete;
        ~HttpRequestParser() = delete;

        static HttpRequest ParseRequest(mg_connection* conn);

    private:
        static void GetHeaders(HttpRequest* req, const mg_request_info* reqInfo);

        static void GetParams(HttpRequest *req, const std::string& query);

    };
    
    
    
} // namespace Networks
