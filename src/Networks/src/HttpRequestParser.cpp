#include "Networks/HttpRequestParser.h"
#include "Networks/HttpRequest.h"
#include <sstream>

namespace Networks
{
    HttpRequest HttpRequestParser::ParseRequest(mg_connection *conn)
    {
        HttpRequest req;
        const mg_request_info* reqInfo = mg_get_request_info(conn);
        std::string query = reqInfo->query_string ? reqInfo->query_string : "";
        req.SetPath(reqInfo->request_uri);
        req.SetMethod(reqInfo->request_method);
        GetHeaders(&req, reqInfo);
        GetParams(&req, query);
        
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
    void HttpRequestParser::GetParams(HttpRequest *req, const std::string& query)
    {
        std::istringstream queryStream(query);
        std::string pair;

        // 按 '&' 分割每个 key=value 对
        while (std::getline(queryStream, pair, '&')) {
            size_t equalPos = pair.find("=");
            if (equalPos != std::string::npos) {
                // 提取 key 和 value
                std::string key = pair.substr(0, equalPos);
                std::string value = pair.substr(equalPos + 1);
                req->AddParams(key, value);
            } else {
                // 如果没有 '=', 只存储 key，value 为空字符串
                req->AddParams(pair,  "");
            }
        }
    }
} // namespace Networks
