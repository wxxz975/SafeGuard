#pragma once
#include "SampleYOLO.h"

namespace Inference
{
    namespace Algorithms
    {

        
        struct Yolov8RawResult
        {
            float cx;	// center x
            float cy;	// center y
            float w;	// width
            float h;	// height
            // class confidence
        };
        #define YOLOV8_OUTBOX_ELEMENT_COUNT (sizeof(Yolov8RawResult) / sizeof(float))

        class YOLOv8: public SampleYOLO
        {
        public:
            YOLOv8();
            ~YOLOv8() = default;

        private:
            virtual std::vector<Base::BoundingBox> ParseRawOutput(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) override;
        };
        
        
        
        
    } // namespace Algorithms
    
    
} // namespace Inference
