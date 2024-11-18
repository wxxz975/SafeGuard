#include "Networks/WebPage/MainWebPageHandler.h"
#include "Networks/HttpRequest.h"
#include "Networks/HttpRequestParser.h"

#include "Commands/InitializeCommand.h"
#include "Commands/ModelSwitchCommand.h"
#include "Commands/SettingsUpdateCommand.h"
#include "Commands/HistoryQueryCommand.h"
#include "Commands/ImageQueryCommand.h"
#include "Commands/ModelInfoQueryCommand.h"

#include "Common/Logger.h"

namespace Networks
{
#define NewTaskQuery        "QueryResult"
#define InitQuery           "Init"
#define ModelSwitchQuery    "SwitchModel"
#define SettingsUpdateQuery "UpdateSettings"
#define HistoryQuery        "QueryHistory"
#define ImageQuery          "QueryImage"
#define ModelInfoQuery      "QueryModelInfo"

    MainWebPageHandler::MainWebPageHandler()
    {
        m_cmds.emplace(InitQuery, std::make_unique<InitializeCommand>());
        m_cmds.emplace(ModelSwitchQuery, std::make_unique<ModelSwitchCommand>());
        m_cmds.emplace(SettingsUpdateQuery, std::make_unique<SettingsUpdateCommand>());
        m_cmds.emplace(HistoryQuery, std::make_unique<HistoryQueryCommand>());
        m_cmds.emplace(ImageQuery, std::make_unique<ImageQueryCommand>());
        m_cmds.emplace(ModelInfoQuery, std::make_unique<ModelInfoQueryCommand>());
    }

    bool MainWebPageHandler::HandleGetImpl(HttpResponse *resp, mg_connection *conn)
    {
        HttpRequest req = HttpRequestParser::ParseRequest(conn);

        std::string cmd = req.GetHeader("cmd");
        if(m_cmds.count(cmd)) {
            std::string result = m_cmds.at(cmd)->Execute(req);
            Common::Logger::logInfo("send:{}", result);
            if(cmd == ImageQuery) {
                if(!result.empty()) resp->SetFileResponse(result);
                else resp->SetUnknownErrorResponse("Unknown File!");
            }   
            else resp->SetJsonResponse(result);

        }else {
            resp->SetUnknownErrorResponse("Unknown CMD.");
        }

        return true;
    }

} // namespace Networks
