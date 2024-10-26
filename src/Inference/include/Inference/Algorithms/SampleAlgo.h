#pragma once
#include "PrePostProcessorImpl.h"

namespace Inference
{
    namespace Algorithms
    {
        class SampleAlgo: public PrePostProcessor::PrePostProcessorImpl
        {
        public:
            SampleAlgo() = default;
            ~SampleAlgo() = default;

            virtual bool Initialize(std::shared_ptr<Base::ModelMetadata> metadata) override;

            virtual std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic) = 0;

            virtual std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& output, std::shared_ptr<InferenceContext> ic) = 0;

            virtual cv::Mat RenderBoxes(const std::vector<Base::BoundingBox>& boxes, const std::string& image_path) override;

            virtual bool CheckIOShape() override;

        protected:

            std::vector<std::vector<std::uint64_t>> m_theoryOutShape;
            std::vector<std::vector<std::uint64_t>> m_theoryInShape;
            std::vector<std::string> m_InShapeMask;
            std::vector<std::string> m_OutShapeMask;
        };        
        
    } // namespace Algorithms
    
    
} // namespace Inference
