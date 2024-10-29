#include "Inference/PrePostProcessor.h"


namespace Inference
{
    
    PrePostProcessor::PrePostProcessor(std::unique_ptr<PrePostProcessorImpl> impl)
        :m_impl(std::move(impl))
    {

    }
    
    bool PrePostProcessor::Initialize(std::shared_ptr<Base::ModelMetadata> metadata)
    {
        return m_impl->Initialize(metadata);
    }
    std::vector<Base::TensorPtr> PrePostProcessor::Preprocessing(const cv::Mat &image, std::shared_ptr<InferenceContext> ic)
    {
        return m_impl->Preprocessing(image, ic);
    }
    std::vector<Base::BoundingBox> PrePostProcessor::Postprocessing(const std::vector<Base::TensorPtr> &output, std::shared_ptr<InferenceContext> ic)
    {
        return m_impl->Postprocessing(output, ic);
    }
    cv::Mat PrePostProcessor::RenderBoxes(const std::vector<Base::BoundingBox> &boxes, const std::string &image_path)
    {
        return m_impl->RenderBoxes(boxes, image_path);
    }
} // namespace Inference
