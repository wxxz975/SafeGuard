#include "SafeGuard/SafeGuardConfig.h"



namespace SafeGuard
{
    bool SafeGuardConfig::LoadConfig(const std::string& config_path) {
        using json = nlohmann::json;
        using namespace Common::IFilesystem;
        config_path_ = config_path;
        try
        {
            std::ifstream ifs(config_path);
            if(!ifs.is_open()) {
                Common::logError("failed to open config path:{}", config_path);
                return false;
            }

            ifs >> root_json;
            if(root_json.contains("loop_Interval")) loop_Interval = root_json["loop_Interval"];
            Common::logInfo("[Config] Main loop interval:{} ms!", loop_Interval);

            if(root_json.contains("image_cache_dir")) image_cache_dir = root_json["image_cache_dir"];
            Common::logInfo("[Config] image_cache_dir:{}", image_cache_dir);
            image_cache_dir = ConcatPath(GetCurrentPath(), image_cache_dir);
            if(!IsExist(image_cache_dir)) CreateDir(image_cache_dir);
            

            if(root_json.contains("Inference")) {
                auto inferDoc = root_json["Inference"];
                
                if(inferDoc.contains("iou_threshold")) infer.iou_threshold = inferDoc["iou_threshold"];
                if(inferDoc.contains("conf_threshold")) infer.conf_threshold = inferDoc["conf_threshold"];
                
                if(inferDoc.contains("model_path")) infer.model_path = inferDoc["model_path"];
                if(inferDoc.contains("model_type")) infer.model_type = inferDoc["model_type"];
                if(inferDoc.contains("framework")) infer.framework = inferDoc["framework"];

                if(inferDoc.contains("image_source_type")) infer.image_source_type = inferDoc["image_source_type"];
                if(inferDoc.contains("image_source")) infer.image_source = inferDoc["image_source"];
            }

            if(root_json.contains("Networks")) {
                auto netDoc = root_json["Networks"];
                
                if(netDoc.contains("root_doc")) net.root_doc = netDoc["root_doc"]; 
                if(netDoc.contains("listen_port")) net.listen_port = netDoc["listen_port"];
            }


        }
        catch(const std::exception& e)
        {
            Common::logError("Parse Config Error:{}", e.what());
            return false;
        }

        return true;
    };


    void SafeGuardConfig::SaveConfig(const std::string& save_path) {
        std::ofstream ofs(save_path.empty() ? config_path_ : save_path);
        if(ofs.is_open()) {
            ofs << root_json.dump();
            ofs.close();
        }
    }

    bool SafeGuardConfig::IsValidConfig() 
    {
        return CheckInference() && CheckNetworks();    
    }

    bool SafeGuardConfig::CheckInference()
    {
        using namespace Common::IFilesystem;
        if(infer.conf_threshold <= 0.f || infer.conf_threshold >= 1.f) {
            Common::logError("[Config Inference] Invalid conf_threshold:{}, value range(0~1)", infer.conf_threshold);
            return false;
        }
        Common::logInfo("[Config Inference] conf_threshold:{}", infer.conf_threshold);

        if(infer.iou_threshold <= 0.f || infer.iou_threshold >= 1.f) {
            Common::logError("[Config Inference] Invalid iou_threshold:{}, value range(0~1)", infer.iou_threshold);
            return false;
        }
        Common::logInfo("[Config Inference] iou_threshold:{}", infer.iou_threshold);

        if(!::Inference::SupportedFrameworks::IsValid(infer.framework)) {
            Common::logError("[Config Inference] Invalid framework:{}", infer.framework);
            return false;
        }
        Common::logInfo("[Config Inference] framework:{}", infer.framework);

        if(!::Inference::SupportedModels::IsValid(infer.model_type)) {
            Common::logError("Invalid model_type:{}", infer.model_type);
            return false;
        }
        Common::logInfo("[Config Inference] model_type:{}", infer.model_type);

        if(!IsExist(infer.model_path) || !IsEndWith(infer.model_path, "onnx")) {
            Common::logError("[Config Inference] Invalid model_path:{}, need ending with onnx", infer.model_path);
            return false;
        }
        Common::logInfo("[Config Inference] [Config] model_path:{}", infer.model_path);
        
        ImageProviderType source_type = static_cast<ImageProviderType>(infer.image_source_type);
        switch (source_type)
        {
        case ImageProviderType::FROM_IMAGE:
        case ImageProviderType::FROM_VIDEO: {
            if(!IsExist(infer.image_source)) {
                Common::logError("[Config Inference] Source Type:{}, but image source path not exist:{}", 
                    ImageProviderTypeToStr(source_type),
                    infer.image_source);
                return false;
            }
            break;
        }
        case ImageProviderType::FROM_CAMERA: break;
        case ImageProviderType::FROM_NETWORK: break;
        
        default:
            Common::logError("[Config Inference] Invalid image_source_type:{} or image_source:{}",  
                ImageProviderTypeToStr(source_type), 
                infer.image_source);
            break;
        }
        Common::logInfo("[Config Inference] image_source_type:{}, image_source:{}", ImageProviderTypeToStr(source_type), infer.image_source);

        return true;
    }
    bool SafeGuardConfig::CheckNetworks()
    {
        if(net.listen_port < 0 || net.listen_port > 65535) {
            Common::logError("[Config Networks] Invalid port:{}, port range:(1~65535)", net.listen_port);
            return false;
        }
        Common::logInfo("[Config Networks] listen_port:{}", net.listen_port);

        if(!Common::IFilesystem::IsExist(net.root_doc)) {
            Common::logError("[Config Networks] Invalid path:{}", net.root_doc);
            return false;
        }
        Common::logInfo("[Config Networks] web root doc:{}", net.root_doc);

        return true;
    }
} // namespace SafeGuard
