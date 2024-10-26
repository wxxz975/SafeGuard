#pragma once
#include "CivetServer.h"

namespace Communications
{
    class HttpRequest;

    class HttpRequestParser
    {
    public:
        HttpRequestParser() = delete;
        ~HttpRequestParser() = delete;

        static HttpRequest parseRequest(mg_connection* conn);

    private:
        static void getHeaders(HttpRequest* req, const mg_request_info* reqInfo);

    };
    
    
    
} // namespace Communications
