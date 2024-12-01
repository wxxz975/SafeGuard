#include "Algorithms/YOLOv8.h"
#include "Common/Logger.h"
#include "Matrix.hpp"
namespace Inference
{
    namespace Algorithms
    {
        YOLOv8::YOLOv8()
        {
            m_theoryOutShape.push_back({1 ,84, 8400});
            m_OutShapeMask.push_back("x?x");

            m_theoryInShape.push_back({1, 3, 640, 640});
            m_InShapeMask.push_back("xx??");
        }

        std::vector<Base::BoundingBox> YOLOv8::ParseRawOutput(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;
            auto& output = outputs.at(0);
            const auto raw_ptr = output->Ptr<float>();  // Adjust according to the size of model elements
            const auto& shape = output->GetShape();
            // cv::Size sz = cv::Size(); // width, height;
            // 1, 84, 8400
            std::size_t num_channels = shape.at(1);	// 84
            std::size_t num_anchors = shape.at(2);	// 8400

            /* 
            * 转置会拷贝内存，并且会拖慢这个解析的过程， 减少使用这个转置，但是如果使用转置这个我们 
            *	定义的结构体就用不上了，因为这个每一个raw 的box 内存排列不是按照row first顺序排列的
            * */ 
            Matrix<float> mat = Matrix<float>(raw_ptr, num_channels, num_anchors, false);
            for(int idx = 0; idx < mat.Cols(); ++idx) {
                
                float score = 0.f;
                int class_idx = -1;
                
                mat.GetMaxValueWithIndexCol(idx, YOLOV8_OUTBOX_ELEMENT_COUNT, score, class_idx);
                
                // 置信度 0～1之间
                if (score > ic->conf_threshold) {
                    int32_t width = mat.Get(2, idx);
                    int32_t height = mat.Get(3, idx);
                    int32_t left = mat.Get(0, idx) - width * 0.5;
                    int32_t top = mat.Get(1, idx) - height * 0.5;

                    result.emplace_back(
                            left, top, width, height, 
                            static_cast<float>(score), 
                            static_cast<std::size_t>(class_idx));
                }
            }
            return result;
        }
    }
}
