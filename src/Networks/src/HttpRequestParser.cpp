#include "Networks/HttpRequestParser.h"
#include "Networks/HttpRequest.h"


namespace Networks
{
    HttpRequest HttpRequestParser::ParseRequest(mg_connection *conn)
    {
        HttpRequest req;
        const mg_request_info* reqInfo = mg_get_request_info(conn);
        
        req.SetPath(reqInfo->request_uri);
        req.SetMethod(reqInfo->request_method);
        GetHeaders(&req, reqInfo);
        
        return std::move(req);
    }
    void HttpRequestParser::GetHeaders(HttpRequest *req, const mg_request_info* reqInfo)
    {
        int numHeaders = reqInfo->num_headers;
        const mg_header* headers = reqInfo->http_headers;

        for(int idx = 0; idx < numHeaders; ++idx) {
            const mg_header& header = headers[idx];
            req->AddHeader(header.name, header.value);
        }
    }
} // namespace Networks
