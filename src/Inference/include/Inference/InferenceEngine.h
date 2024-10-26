#pragma once
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "Base/ModelMetadata.h"
#include "PrePostProcessor.h"

namespace Inference
{
    class InferenceEngine
    {
    public:
        class InferenceEngineImpl;
        std::unique_ptr<InferenceEngineImpl> m_impl;

        typedef std::vector<Base::BoundingBox> OutputBoxes;
        typedef std::function<void(const OutputBoxes&)> AsynInferCallback;
        
    public:
        InferenceEngine() = default;
        ~InferenceEngine() = default;

        // TODO FIXME
        //bool Initialize();

        OutputBoxes Infer(const std::string& img_path);

        OutputBoxes Infer(const cv::Mat& img);

        void InferAsyn(const std::string& img_path, const AsynInferCallback& callback);

        void InferAsyn(const cv::Mat& img, const AsynInferCallback& callback);
    };
    
    

} // namespace Inference
