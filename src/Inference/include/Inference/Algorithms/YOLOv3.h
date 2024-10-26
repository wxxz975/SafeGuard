#pragma once
#include "SampleYOLO.h"

namespace Inference
{
    namespace Algorithms
    {
        struct Yolov3RawResult
        {
            float cx;       // center x
            float cy;       // center y
            float w;        // width
            float h;        // height
        };
        #define YOLOV3_OUTBOX_ELEMENT_COUNT sizeof(Yolov3RawResult)/sizeof(float)
        
        // 
        class YOLOv3: public SampleYOLO
        {
        public:
            YOLOv3();
            ~YOLOv3() = default;


        private:
            virtual std::vector<Base::BoundingBox> ParseRawOutput(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) override;
    
        };
        
    }; // namespace Algorithms
    
    
}; // namespace Inference
