#pragma once
#include <memory>
#include <functional>
#include <string>
#include <fstream>


#include "Networks/HttpServer.h"
#include "Inference/InferenceEngine.h"

#include "Common/SafeQueue.h"
#include "Common/json.hpp"
#include "Common/Logger.h"

#include "SafeGuard/SafeGuardConfig.h"
#include "SafeGuard/ImageProviderType.h"
#include "SafeGuard/ImageProvider.h"
#include "SafeGuard/ImageSourceManager.h"
#include "SafeGuard/ModelSourceManager.h"

namespace SafeGuard
{
    using namespace Networks;    
    

    class SafeGuard
    {
    public:

        SafeGuard() = default;
        ~SafeGuard() = default;

        bool Initialize(const std::string& config_path);

        void MainLoop();
        
    private:
        bool InitNetwork(const std::string& rootDoc, int16_t listen_port);
        bool InitInference(const std::string& model_path, const std::string& model_type, const std::string& framework);
        
        Config LoadConfigFromFile(const std::string& path);
        void SaveConfigToFile(const std::string& path);


        bool InitImageProvider(ImageProviderType type, const std::string& params);

    private:
        std::unique_ptr<Networks::HttpServer> m_httpServer;
        std::unique_ptr<Inference::InferenceEngine> m_inferEngine;
        std::unique_ptr<ImageProvider> m_imageProvider; // provide all image source whatever they from

        ImageProviderType m_image_source_type;  
        std::shared_ptr<Common::SafeQueue<std::string>> m_image_source_queue;

        std::unique_ptr<ImageSourceManager> m_image_source_mgr; // provide the image path for the web 
        std::unique_ptr<ModelSourceManager> m_model_source_mgr;

        // typedef std::pair<Inference::Base::OutputBoxes> DetectionRecord;
        std::shared_ptr<Common::SafeQueue<Inference::Base::OutputBoxes>> m_detection_result_queue;
        //std::shared_ptr<Common::SafeQueue<Inference::Base::BoundingBox>>

        Config m_config;


        /// @brief reinitialize the inference engine
        /// @params model_path: onnx model path
        /// @params model_type: YOLOv3|YOLOv5|YOLOv8|RTDetr 
        /// @params framework:  ONNXRuntime|OpenVINO|TensorRT
        typedef std::function<bool(const std::string& model_path, const std::string& model_type, const std::string& framework)> ReloadInferenceEngine;

        ReloadInferenceEngine m_reloadCallback = nullptr;
    };
    
    
    
}; // namespace SafeGuard
