#pragma once
#include "SampleAlgo.h"

namespace Inference
{
    namespace Algorithms
    {
        struct rtdetrRawOutput
        {
            float cx;
            float cy;
            float w;
            float h;
            /// .... class socre
        };
        typedef rtdetrRawOutput* pRtdetrRawOutput;
        
        #define RTDETR_OUTBOX_ELEMENT_COUNT (sizeof(rtdetrRawOutput) / sizeof(float))


        class ARtdetr: public SampleAlgo
        {
        public:
            ARtdetr();
            ~ARtdetr() = default;

            virtual std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic) override;

            virtual std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& output, std::shared_ptr<InferenceContext> ic) override;

        };
        
    } // namespace Algorithms
    
    
} // namespace Inference
