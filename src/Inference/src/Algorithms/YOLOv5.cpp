#include "Algorithms/YOLOv5.h"
#include "Common/Utils.h"
#include "Common/Logger.h"
#include "Matrix.hpp"

namespace Inference
{
    namespace Algorithms
    { 
        const std::vector<std::uint64_t> YOLOv5::m_theoryOutShape_old = {1 ,25200, 85};
        const std::vector<std::uint64_t> YOLOv5::m_theoryOutShape_new = {1, 18, 8400};
        const std::vector<std::uint64_t> YOLOv5::m_theoryInShape = {1, 3, 640, 640};

        const std::string YOLOv5::m_OutShapeMask_old = "xx?";
        const std::string YOLOv5::m_OutShapeMask_new = "x?x";
        const std::string YOLOv5::m_InShapeMask = "xx??";

        std::vector<Base::BoundingBox> YOLOv5::ParseRawOutput(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;
            auto& output = outputs.at(0);
            auto* raw_ptr = output->Ptr<float>();
            const auto& shape = output->GetShape();

            std::size_t num_channels = 0;
            std::size_t num_anchors = 0;
            size_t iterations = 0;

            /*
                old shape: [1,25200,85] ,
                new shape: [1, 85, 8400], 
            */
            if(m_useNewOutputShape) {
                num_channels = shape.at(1); // 85
                num_anchors = shape.at(2);  // 8400
                iterations = num_channels;
            }else {
                num_channels = shape.at(2); // 85
                num_anchors = shape.at(1);  // 25200
                iterations = num_anchors;
            }
            // num_channels = shape.at(1);
            // num_anchors = shape.at(2);
            // iterations = m_useNewOutputShape ? num_anchors : num_channels;

            Matrix<float> mat = Matrix<float>(raw_ptr, num_channels, num_anchors, !m_useNewOutputShape);

            for (std::size_t idx = 0; idx < iterations; ++idx)
            {
                int32_t width = 0;
                int32_t height = 0;
                int32_t left = 0;
                int32_t top = 0;
                float score = 0.f;
                int class_idx = -1;
                
                if(m_useNewOutputShape) {
                    mat.GetMaxValueWithIndexCol(idx, YOLOV5NEW_OUTBOX_ELEMENT_COUNT, score, class_idx);
                    width = mat.Get(2, idx);
                    height = mat.Get(3, idx);
                    left = mat.Get(0, idx) - width * 0.5;
                    top = mat.Get(1, idx) - height * 0.5;
                }else {
                    mat.GetMaxValueWithIndexRow(idx, YOLOV5_OUTBOX_ELEMENT_COUNT, score, class_idx);
                    width = mat.Get(idx, 2);
                    height = mat.Get(idx, 3);
                    left = mat.Get(idx, 0) - width * 0.5;                    
                    top = mat.Get(idx, 1) - height * 0.5;
                    score *= mat.Get(idx, 4); // old version has box confidence element
                }
                
                if (score > ic->conf_threshold)
                {
                    result.emplace_back(left, top, width, height,
                        static_cast<float>(score),
                        static_cast<std::size_t>(class_idx));
                }
                
            }

            return result;
        }
       
        bool YOLOv5::CheckIOShape()
        {
            using namespace Common;
            const std::vector<std::uint64_t>& model_input_shape = m_metadata->inputs.at(0).shape;
            const std::vector<std::uint64_t>& model_output_shape = m_metadata->outputs.at(0).shape;

            // compare real output shape with theory shape(2 situations)
            bool useNewOutShape = CompareVecWithMask(m_OutShapeMask_new, m_theoryOutShape_new, model_output_shape);
            bool useOldOutShape = CompareVecWithMask(m_OutShapeMask_old, m_theoryOutShape_old, model_output_shape);

            m_useNewOutputShape = useNewOutShape;
            if(!useOldOutShape && !useNewOutShape) {
                auto shape = VecToStr(model_output_shape);
                auto shapeNew = VecToStr(m_theoryOutShape_new);
                auto shapeOld = VecToStr(m_theoryOutShape_old);
                Common::logError("OutputShape:{}, imcompatiable with ShapeNew:{} or ShapeOld:{}", 
                    shape, shapeNew, shapeOld);
            }


            return CompareVecWithMask(m_InShapeMask, m_theoryInShape, model_input_shape) 
                    && (useNewOutShape || useOldOutShape);
        }
    } // namespace Algorithms

} // namespace Inference
