#include "SafeGuard/SafeGuard.h"

#include "SafeGuard/ImageProviderFactory.h"

#include "Networks/WebPage/FileUploadHandler.h"
#include "Networks/WebPage/MainWebPageHandler.h"
#include "Networks/WebPage/WebSocketHandler.h"

#include "Common/IFilesystem.h"
#include "Common/ServiceLocator.h"

#include "Inference/Base/BoundingBox.h"
#include "Inference/SupportedFrameworks.h"
#include "Inference/SupportedModels.h"

#include "NetworkImageProvider.h"

#include <iostream>

namespace SafeGuard
{
    
    bool SafeGuard::Initialize(const std::string& config_path)
    {
        m_image_source_queue = std::make_shared<Common::SafeQueue<std::string>>();
        m_detection_result_queue = std::make_shared<Common::SafeQueue<Inference::Base::OutputBoxes>>();
        
        m_image_source_mgr = std::make_unique<ImageSourceManager>();
        Common::ServiceLocator::Provide(*m_image_source_mgr);

        
        
        m_config = std::make_shared<SafeGuardConfig>();
        if(!m_config->LoadConfig(config_path) || !m_config->IsValidConfig()) {
            Common::logError("Failed to load config or config Invalid!");
            return false;
        }
        
        m_model_source_mgr = std::make_unique<ModelSourceManager>();
        m_model_source_mgr->Initialize(m_config->infer.model_path);
        Common::ServiceLocator::Provide(*m_model_source_mgr);

        m_image_source_type = static_cast<ImageProviderType>(m_config->infer.image_source_type);
        if(!InitImageProvider(m_image_source_type, m_config->infer.image_source)) {
            Common::logError("Failed to init image provider!");
            return false;
        }
        
        if(!InitInference(m_config->infer.model_path, m_config->infer.model_type, m_config->infer.framework)) {
            Common::logError("Failed to init inference service!");
            return false;
        }

        if(!InitNetwork(m_config->net.root_doc, m_config->net.listen_port)) {
            Common::logError("Failed to init network service!");
            return false;
        }
        
        return true;
    }

    void SafeGuard::MainLoop()
    {
        using namespace Common::IFilesystem;
        std::string save_dir = m_config->image_cache_dir;
        while(true) {
            
            auto imageInfo = m_imageProvider->NextImage();
            auto img = imageInfo.second;
            std::string filename = imageInfo.first;
            if(!img.empty()) {
                auto boxes = m_inferEngine->Infer(img); // beceuse set the callback, don`t need received the return value
                std::string filepath = m_image_source_mgr->GetImagePath(filename);

                std::string save_path = ConcatPath(save_dir, "rendered_" + filename);
                // Common::logInfo("[render] filename:{}, filepath:{}, save_path:{}", filename, filepath, save_path);
                m_inferEngine->RenderBoxes(filepath, boxes, save_path);

                // fixme : send the result to web, use web socket
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(m_config->loop_Interval));
        }
    }

    bool SafeGuard::InitNetwork(const std::string &rootDoc, int16_t listen_port)
    {
        using namespace Common::IFilesystem;
        HttpServer::Config config = {
            {"document_root", IsRelativePath(rootDoc) ? ConcatPath(GetCurrentPath(), rootDoc) : rootDoc},
            {"listening_ports", std::to_string(listen_port)}
        };
        m_httpServer = std::make_unique<Networks::HttpServer>();
        if(m_httpServer->Initialize(config)) {
            auto fileUploadHandler = std::make_unique<Networks::FileUploadHandler>();
            fileUploadHandler->SetReceivedFileDir(ConcatPath(GetCurrentPath(), "tmp"));
            fileUploadHandler->SetReceivedFileCallback([&](const std::string& filename, const std::string& storeDir){
                if(m_image_source_type == ImageProviderType::FROM_NETWORK) {
                    m_image_source_queue->Put(ConcatPath(storeDir, filename)); 
                }
            });

            m_httpServer->AddPageHandler("/upload", std::move(fileUploadHandler));

            auto mainPageHandler = std::make_unique<Networks::MainWebPageHandler>();
            m_httpServer->AddPageHandler("/main", std::move(mainPageHandler));
            
            auto websockHandler = std::make_unique<Networks::WebSocketHandler>();
            m_httpServer->AddSocketHandler("/ws", std::move(websockHandler));

            Common::ServiceLocator::Provide(*m_httpServer);

            Common::logInfo("http service start at: http://127.0.0.1:{}, root doc:{}", listen_port, config["document_root"]);
            return true;
        }

        return false;
    }

    bool SafeGuard::InitInference(const std::string& model_path, const std::string& model_type, const std::string& framework)
    {
        m_inferEngine = std::make_unique<Inference::InferenceEngine>();
        if(m_inferEngine->Initialize(model_path, model_type, framework)) {
            Common::logInfo("Inference Engine initialized!");
            m_inferEngine->SetGeneralCallback([&](const Inference::Base::OutputBoxes& boxes){
                m_detection_result_queue->Put(boxes);
            });
            Common::ServiceLocator::Provide(*m_inferEngine);
            return true;
        }

        return false;
    }

    Config SafeGuard::LoadConfigFromFile(const std::string &path)
    {
        if(!m_config) m_config = std::make_shared<SafeGuardConfig>();
        return m_config->LoadConfig(path) ? m_config : nullptr;
    }

    void SafeGuard::SaveConfigToFile(const std::string &path)
    {
        if(m_config) m_config->SaveConfig(path);
    }

    bool SafeGuard::InitImageProvider(ImageProviderType type, const std::string& params)
    {
        using namespace Common::IFilesystem;
        
        m_imageProvider = ImageProviderFactory::CreateProvider(type, params);

        m_imageProvider->SetNextImageCallback([&](const std::string& filename, const std::string& filepath){
            m_image_source_mgr->AddImageAsset(filename, filepath);
        });
        m_imageProvider->SetSaveDirectory(m_config->image_cache_dir);

        if(m_imageProvider && m_image_source_type == ImageProviderType::FROM_NETWORK)
        {
            if(auto ptr = dynamic_cast<NetworkImageProvider*>(m_imageProvider.get()))
            {
                return ptr->Initialize(m_image_source_queue);
            }
        }

        return true;
    }

} //

