#pragma once
#include "SampleYOLO.h"


namespace Inference
{
    namespace Algorithms
    {
        // end to end
        struct Yolov10RawResult
        {
            float left;
            float top;
            float width;
            float height;
            float score;
            int class_idx;
        };
        
        typedef Yolov10RawResult* pYolov10RawResult;

        class YOLOv10: public SampleYOLO
        {
        public:
            YOLOv10();
            ~YOLOv10() = default;


        private:
            virtual std::vector<Base::BoundingBox> ParseRawOutput(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) override;

        };
        

    }
}