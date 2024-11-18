#pragma once
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <opencv2/opencv.hpp>

#include "Inference/Base/BoundingBox.h"
#include "Inference/Base/ModelMetadata.h"

namespace Inference
{
    class InferenceEngineImpl;
    class InferenceEngine
    {
        struct CurrentState
        {
            std::string model_name;
            std::string algo_name;
            std::string framework;
            std::size_t async_threads;
            bool initialized = false;
        }m_state;
    

    public:
       
        InferenceEngine() = default;
        ~InferenceEngine();

        const CurrentState& GetState() const; 
     
        bool Initialize(const std::string& model_path, const std::string& algo_type, const std::string& infer_framework, size_t threadNum = 4);

        Base::OutputBoxes Infer(const std::string& img_path);

        // 
        Base::OutputBoxes Infer(const cv::Mat& img);
        // void InferAsyn(const cv::Mat& img, const Base::AsynInferCallback& callback);
        void RenderBoxes(const std::string& img_path, const Base::OutputBoxes& boxes, const std::string& save_path);

        void RenderBoxes(const cv::Mat& img, const Base::OutputBoxes& boxes, const std::string& save_path);

        void InferAsyn(const std::string& img_path, const Base::AsynInferCallback& callback);

        std::shared_ptr<std::vector<std::string>> GetLabels() const;

        std::shared_ptr<Base::ModelMetadata> ParseModel(const std::string& path) const;

        void SetConfidenceThreshold(float conf);

        void SetIOUThreshold(float iou);

        void SetGeneralCallback(const Base::AsynInferCallback& callback);
        
    private:
        InferenceEngineImpl* m_impl = nullptr;
    };
    
    

} // namespace Inference
