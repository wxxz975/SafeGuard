#include "HttpRequestParser.h"
#include "HttpRequest.h"


namespace Communications
{
    HttpRequest HttpRequestParser::parseRequest(mg_connection *conn)
    {
        HttpRequest req;
        const mg_request_info* reqInfo = mg_get_request_info(conn);
        
        req.setPath(reqInfo->request_uri);
        req.setMethod(reqInfo->request_method);
        getHeaders(&req, reqInfo);
        
        return std::move(req);
    }
    void HttpRequestParser::getHeaders(HttpRequest *req, const mg_request_info* reqInfo)
    {
        int numHeaders = reqInfo->num_headers;
        const mg_header* headers = reqInfo->http_headers;

        for(int idx = 0; idx < numHeaders; ++idx) {
            const mg_header& header = headers[idx];
            req->addHeader(header.name, header.value);
        }
    }
} // namespace Communications
