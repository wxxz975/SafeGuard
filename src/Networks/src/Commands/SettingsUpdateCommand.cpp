#include "SettingsUpdateCommand.h"
#include "Common/ServiceLocator.h"
#include "Common/Logger.h"
#include "Inference/InferenceEngine.h"

#include "Networks/ResponseJsonBuilder.h"

namespace Networks
{
    std::string SettingsUpdateCommand::Execute(const HttpRequest &req)
    {
        std::string str_conf = req.GetHeader("conf_threshold");
        std::string str_iou = req.GetHeader("iou_threshold");
        bool status = true;
        float conf = 0.f;
        float iou = 0.f;
        try
        {
            conf = std::stof(str_conf);
            iou = std::stof(str_iou);
        }
        catch(const std::exception& e)
        {
            status = false;
            Common::logError("Invalid conf_threshold:{} or iou_threshold:{}", str_conf, str_iou);
        }
        
        if(status && Check(conf) && Check(iou)) {
            Common::ServiceLocator::Get<Inference::InferenceEngine>().SetIOUThreshold(iou);
            Common::ServiceLocator::Get<Inference::InferenceEngine>().SetConfidenceThreshold(conf);
        }
        std::unordered_map<std::string, std::string> values = {
            {"conf_threshold", std::to_string(conf)}, 
            {"iou_threshold", std::to_string(iou)}
        };

        return ResponseJsonBuilder::CreateSettingsUpdateResponse(status, values);
    }

    bool SettingsUpdateCommand::Check(float v)
    {
        return v > 0.f && v < 1.f;
    }
}
