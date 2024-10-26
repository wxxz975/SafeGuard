#include "MainWebPageHandler.h"
#include "HttpRequest.h"
#include "HttpRequestParser.h"

namespace Communications
{
    bool MainWebPageHandler::handleGetImpl(HttpResponse *resp, mg_connection *conn)
    {
        HttpRequest req = HttpRequestParser::parseRequest(conn);

        std::string cmd = req.getHeader("cmd");
        
        if(cmd == QueryNewTask) {
            std::string result = executeQuery();
            resp->setJsonResponse(result);
        }else {
            resp->setUnknownErrorResponse("Unknown CMD.");
        }

        return true;
    }

    std::string MainWebPageHandler::executeQuery()
    {
	    // 需要处理如何从外部查询并获取数据，然后使用这个QueryResponsebuilder  构造返回的json      
        return std::string();
    }

} // namespace Communications
