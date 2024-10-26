#pragma once
#include <opencv2/opencv.hpp>
#include "Inference/InferenceEngine.h"
#include "Inference/Framework.h"
#include "Common/ThreadPool.h"


namespace Inference
{
    
    class InferenceEngine::InferenceEngineImpl
    {
    public:
        InferenceEngineImpl() = default;
        ~InferenceEngineImpl() = default;

        // TODO FIXME
        bool Initialize(std::unique_ptr<PrePostProcessor> prepos,  
            std::unique_ptr<Framework> framework,
            std::shared_ptr<Base::ModelMetadata> metadata, 
            size_t threadNum = 4);

        OutputBoxes Infer(const std::string& img_path);

        OutputBoxes Infer(const cv::Mat& img);

        void InferAsyn(const std::string& img_path, const AsynInferCallback& callback);

        void InferAsyn(const cv::Mat& img, const AsynInferCallback& callback);    
    
    private:
        std::shared_ptr<Base::ModelMetadata> m_metadata;    // model info
        std::unique_ptr<PrePostProcessor> m_prepos;         // prepostprocess
        std::unique_ptr<Framework> m_framework;             // lower inference
        
        size_t m_threadNum;
        std::unique_ptr<Common::ThreadPool> m_thread_pool;  // thread pool, handle asyn infernece
    };
    
    
    
} // namespace Inference
