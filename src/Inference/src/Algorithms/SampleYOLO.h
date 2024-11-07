
#pragma once
#include "SampleAlgo.h"


namespace Inference
{
    namespace Algorithms
    {
        class SampleYOLO: public SampleAlgo
        {
        public:
            SampleYOLO();
            ~SampleYOLO();

            virtual std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic) override;

            virtual std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) override;


        protected:
            virtual std::vector<Base::BoundingBox> ParseRawOutput(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) = 0;
        
        };
        
        

    } // namespace Algorithms
} // namespace Inference
