#include "Networks/WebPage/MainWebPageHandler.h"
#include "Networks/HttpRequest.h"
#include "Networks/HttpRequestParser.h"

#include "Commands/InitializeCommand.h"
#include "Commands/ModelSwitchCommand.h"
#include "Commands/SettingsUpdateCommand.h"
#include "Commands/HistoryQueryCommand.h"

namespace Networks
{
#define NewTaskQuery        "QueryResult"
#define InitQuery           "Init"
#define ModelSwitchQuery    "SwitchModel"
#define SettingsUpdateQuery "UpdateSettings"
#define HistoryQuery        "History"
#define QueryImage          "QueryImage"

    MainWebPageHandler::MainWebPageHandler()
    {
        m_cmds.emplace(InitQuery, std::make_unique<InitializeCommand>());
        m_cmds.emplace(ModelSwitchQuery, std::make_unique<ModelSwitchCommand>());
        m_cmds.emplace(SettingsUpdateQuery, std::make_unique<SettingsUpdateCommand>());
        m_cmds.emplace(HistoryQuery, std::make_unique<HistoryQueryCommand>());
    }

    bool MainWebPageHandler::HandleGetImpl(HttpResponse *resp, mg_connection *conn)
    {
        HttpRequest req = HttpRequestParser::ParseRequest(conn);

        std::string cmd = req.GetHeader("cmd");
        if(m_cmds.count(cmd)) {
            std::string result = m_cmds.at(cmd)->Execute(req);

            if(cmd == QueryImage) resp->SetFileResponse(result);
            else resp->SetJsonResponse(result);

        }else {
            resp->SetUnknownErrorResponse("Unknown CMD.");
        }

        return true;
    }

} // namespace Networks
