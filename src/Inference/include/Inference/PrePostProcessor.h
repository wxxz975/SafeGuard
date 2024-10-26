#pragma once
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include "Inference/Base/BoundingBox.h"
#include "Inference/Base/Tensor.h"
#include "Inference/Base/ModelMetadata.h"
#include "Inference/InferenceContext.h"


namespace Inference
{
    class PrePostProcessor final
    {
    public:
        class PrePostProcessorImpl;
    private:
        std::unique_ptr<PrePostProcessorImpl> m_impl;
        
    public:
        PrePostProcessor(std::unique_ptr<PrePostProcessorImpl> impl);
        ~PrePostProcessor() = default;

        
        bool Initialize(std::shared_ptr<Base::ModelMetadata> metadata);

        /// @brief 按照m_metadata的输入的shape的大小进行预处理，并且验证是否一一对应
        /// @param image 传入需要处理的图像, 可同时传入多张图像，或者是多个输入口
        /// @return 
        std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic);

        /// @brief 按照BoundingBox的格式解析出标准的结果
        /// @param output 这是经过底层框架推理之后得到的结果
        /// @return 
        std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& output, std::shared_ptr<InferenceContext> ic);


        cv::Mat RenderBoxes(const std::vector<Base::BoundingBox>& boxes, const std::string& image_path);
    
        
    };
    

} // namespace Inference


