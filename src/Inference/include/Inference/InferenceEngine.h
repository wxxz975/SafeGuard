#pragma once
#include <memory>
#include <vector>
#include <string>
#include <functional>

#include <opencv2/opencv.hpp>

#include "Inference/Base/BoundingBox.h"
#include "InferenceEngineImpl.h"


namespace Inference
{
    class InferenceEngineImpl;

    class InferenceEngine
    {
    public:
       
        InferenceEngine() = default;
        ~InferenceEngine() = default;

     
        bool Initialize(const std::string& model_path, const std::string& algo_type, const std::string& infer_framework, size_t threadNum = 4);

        Base::OutputBoxes Infer(const std::string& img_path);

        Base::OutputBoxes Infer(const cv::Mat& img);

        void InferAsyn(const std::string& img_path, const Base::AsynInferCallback& callback);

        void InferAsyn(const cv::Mat& img, const Base::AsynInferCallback& callback);

        cv::Mat RenderBoxes(const std::string& img_path, const Base::OutputBoxes& boxes);

        const std::vector<std::string>& GetLabels() const;

        
    private:
        std::unique_ptr<InferenceEngineImpl> m_impl;
    };
    
    

} // namespace Inference
