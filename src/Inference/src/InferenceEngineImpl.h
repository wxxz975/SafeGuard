#pragma once
#include <memory>
#include <vector>

#include "PrePostProcessor.h"
#include "Framework.h"

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

        cv::Mat RenderBoxes(const cv::Mat& img, const Base::OutputBoxes& boxes);
        cv::Mat RenderBoxes(const std::string& img_path, const Base::OutputBoxes& boxes);

        void RenderBoxes(const std::string &img_path, const Base::OutputBoxes& boxes, const std::string& save_path);
        void RenderBoxes(const cv::Mat &img, const Base::OutputBoxes& boxes, const std::string& save_path);

        const std::vector<std::string>& GetLabels() const;

        void SetIOUThreshold(float iou);
        void SetConfidenceThreshold(float conf);

        void SetGeneralCallback(const Base::AsynInferCallback& callback);

    private:
        
        bool CreateContext(const std::string &model_path, const std::string &algo_type, const std::string &infer_framework);

    private:
        std::shared_ptr<Base::ModelMetadata> m_metadata;    // model info
        std::unique_ptr<PrePostProcessor> m_prepos;         // prepostprocess
        std::unique_ptr<Framework> m_framework;             // lower inference
        
        size_t m_threadNum;
        std::unique_ptr<Common::ThreadPool> m_thread_pool;  // thread pool, handle asyn infernece

        float m_iou_default = 0.5;
        float m_conf_default = 0.55;

        Base::AsynInferCallback m_general_callback = nullptr;   // all inference will call this after infer
    };
    
} // namespace Inference
