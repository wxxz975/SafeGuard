#include "Commands/HistoryQueryCommand.h"
#include "Common/Utils.h"

namespace Networks
{
    std::string HistoryQueryCommand::Execute(const HttpRequest& req)
    {
        std::string result;
        std::string startTime = req.GetParams("StartTime");
        std::string endTime = req.GetParams("EndTime");
        std::string modelname = req.GetParams("ModelName");
        

        std::string timestamp_start = Common::DateToTimestamp(startTime);
        std::string timestamp_end = Common::DateToTimestamp(endTime);
        
        

        return std::string();
    }
} // namespace Networks
