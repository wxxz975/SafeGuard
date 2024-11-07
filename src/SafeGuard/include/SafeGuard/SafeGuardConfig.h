#pragma once
#include <memory>
#include <fstream>

#include "Common/Logger.h"
#include "Common/json.hpp"
#include "Common/IFilesystem.h"

#include "Inference/SupportedFrameworks.h"
#include "Inference/SupportedModels.h"

#include "SafeGuard/ImageProviderType.h"

namespace SafeGuard
{
    
    struct SafeGuardConfig
    {
        using json = nlohmann::json;
        std::string config_path_;
        json root_json;
        int loop_Interval = 500; // ms
        std::string image_cache_dir = "tmp";
        struct Inference
        {
            float       iou_threshold;
            float       conf_threshold;

            std::string model_path;     //  onnx model path
            std::string model_type;     //  YOLOv3|YOLOv5|YOLOv8|RTDetr
            std::string framework;      //  OpenVINO|ONNXRuntime|TensorRT

            int    image_source_type;   //  0=image file or image dir|1=video file|2=network|3=camera
            std::string image_source;   //  is filepath or video path or camera index
        }infer;

        struct Networks
        {
            std::string root_doc;
            uint16_t    listen_port;
        }net;

        bool LoadConfig(const std::string& config_path);

        void SaveConfig(const std::string& save_path);

        bool IsValidConfig();

    private:
        bool CheckInference();
        bool CheckNetworks();
    };
    typedef std::shared_ptr<SafeGuardConfig> Config; 
} // namespace SafeGuard
