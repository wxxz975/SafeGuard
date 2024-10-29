#pragma once
#include "SampleAlgo.h"

namespace Inference
{
    namespace Algorithms
    {
        struct RTDetrRawOutput
        {
            float cx;
            float cy;
            float w;
            float h;
            /// .... class socre
        };
        typedef RTDetrRawOutput* pRTDetrRawOutput;
        
        #define RTDetr_OUTBOX_ELEMENT_COUNT (sizeof(RTDetrRawOutput) / sizeof(float))


        class RTDetr: public SampleAlgo
        {
        public:
            RTDetr();
            ~RTDetr() = default;

            virtual std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic) override;

            virtual std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& output, std::shared_ptr<InferenceContext> ic) override;

        };
        
    } // namespace Algorithms
    
    
} // namespace Inference
