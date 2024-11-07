#pragma once
#include <string>
#include <vector>

#include "SampleYOLO.h"

namespace Inference
{
    namespace Algorithms
    {

        struct Yolov5RawResultNew {
            float cx;       // center x
            float cy;       // center y
            float w;        // width
            float h;        // height
            // class confidence
        };
        struct Yolov5RawResult: public Yolov5RawResultNew
        {
            float box_conf; // box confidence // no this member in new output structure
            // class confidence
        };

        #define YOLOV5_OUTBOX_ELEMENT_COUNT sizeof(Yolov5RawResult)/sizeof(float)
        #define YOLOV5NEW_OUTBOX_ELEMENT_COUNT sizeof(Yolov5RawResultNew)/sizeof(float)

        class YOLOv5: public SampleYOLO
        {
        public:
            YOLOv5() = default;
            ~YOLOv5() = default;

        private:
            virtual std::vector<Base::BoundingBox> ParseRawOutput(const std::vector<Base::TensorPtr>& outputs, std::shared_ptr<InferenceContext> ic) override;

            virtual bool CheckIOShape() override;
        
            const static std::vector<std::uint64_t> m_theoryOutShape_old;
            const static std::string m_OutShapeMask_old;

            const static std::vector<std::uint64_t> m_theoryOutShape_new;
            const static std::string m_OutShapeMask_new;

            const static std::vector<std::uint64_t> m_theoryInShape;
            const static std::string m_InShapeMask;

        protected:
            bool m_useNewOutputShape = false;

        };
    }; // namespace Algorithms
}; // namespace Inference
