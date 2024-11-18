#include "SettingsUpdateCommand.h"
#include "Common/ServiceLocator.h"
#include "Common/Logger.h"
#include "Inference/InferenceEngine.h"

#include "Networks/ResponseJsonBuilder.h"

namespace Networks
{
    std::string SettingsUpdateCommand::Execute(const HttpRequest &req)
    {
        std::string str_conf = req.GetParams("conf_threshold");
        std::string str_iou = req.GetParams("iou_threshold");
        if(str_conf.empty() || str_iou.empty()) return "";

        bool status = true;
        float conf = 0.f;
        float iou = 0.f;
        if(!FloatParse(str_conf, conf) || !FloatParse(str_iou, iou)) {
            Common::logError("[SettingsUpdateCommand] Invalid conf:{} or iou:{} value!", str_conf, str_iou);
            return "";
        }
        Common::Logger::logInfo("update iou:{}, conf:{}",iou, conf);
        
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

    bool SettingsUpdateCommand::FloatParse(const std::string& str, float& ret)
    {
        try
        {
            ret = std::stof(str);
        }
        catch(const std::exception& e)
        {
            Common::logError("Invalid string to float value:{}", str);
            return false;
        }
        return true;
    }
}
