#include "WebPageHandler.h"
#include <sstream>

#include "HttpResponse.h"

namespace Communications
{

    bool WebPageHandler::handleGet(CivetServer *server, mg_connection *conn)
    {
        HttpResponse resp;
        bool status = false;
        if(!checkAuth(conn)) {
            // Fixme: 
            return true;
        }

        if(status = handleGetImpl(&resp, conn)) {
            ApplyResponse(resp, conn);
        }
        
        return status;
    }

    bool WebPageHandler::handlePost(CivetServer *server, mg_connection *conn)
    {
        HttpResponse resp;
        bool status = false;
        if(!checkAuth(conn)) return false;
        
        if(status = handlePostImpl(&resp, conn)) {
            ApplyResponse(resp, conn);
        }

        return status;
    }

    bool WebPageHandler::checkAuth(mg_connection *conn)
    {
        return true;
    }

    void WebPageHandler::ApplyResponse(const HttpResponse &res, struct mg_connection* conn)
    {
        std::stringstream ss;
        
        // first line
        ss << "HTTP/1.1 " << static_cast<int>(res.m_statusCode) << " "
            << res.m_statusMsg << "\r\n";

        if(res.m_closeConnection) {
            ss << "Connection: close\r\n";
        }else {
            ss << "Content-Length: " << res.m_body.size() << "\r\n";
            ss << "Connection: Keep-Alive\r\n";
        }

        for(const auto& header : res.m_headers) {
            ss << header.first <<": " << header.second << "\r\n";
        }

        ss << "\r\n";
        ss << res.m_body;

        mg_printf(conn, "%s", ss.str().c_str());

    }

} // namespace Communications
