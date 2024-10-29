#pragma once
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Inference/PrePostProcessor.h"
#include "Inference/Framework.h"

#include "Inference/Base/BoundingBox.h"
#include "Common/ThreadPool.h"

namespace Inference
{   
    

    class InferenceEngineImpl
    {
    public:
        InferenceEngineImpl() = default;
        ~InferenceEngineImpl() = default;

        bool Initialize(const std::string& model_path, const std::string& algo_type, const std::string& infer_framework, size_t threadNum = 4);

        Base::OutputBoxes Infer(const std::string& img_path);

        Base::OutputBoxes Infer(const cv::Mat& img);

        void InferAsyn(const std::string& img_path, const Base::AsynInferCallback& callback);

        void InferAsyn(const cv::Mat& img, const Base::AsynInferCallback& callback);    

        cv::Mat RenderBoxes(const std::string& img_path, const Base::OutputBoxes& boxes);

        const std::vector<std::string>& GetLabels() const;
    
    private:
        bool CreateContext(const std::string &model_path, const std::string &algo_type, const std::string &infer_framework);

    private:
        std::shared_ptr<Base::ModelMetadata> m_metadata;    // model info
        std::unique_ptr<PrePostProcessor> m_prepos;         // prepostprocess
        std::unique_ptr<Framework> m_framework;             // lower inference
        
        size_t m_threadNum;
        std::unique_ptr<Common::ThreadPool> m_thread_pool;  // thread pool, handle asyn infernece
    };
    
} // namespace Inference
