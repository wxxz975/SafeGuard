#include "Algorithms/YOLOv10.h"
#include "Matrix.hpp"
#include "Common/Logger.h"

namespace Inference
{
    namespace Algorithms
    {
        YOLOv10::YOLOv10()
        {
            m_theoryOutShape.push_back({1, 300, 6});
            m_OutShapeMask.push_back("x?x");

            m_theoryInShape.push_back({1, 3, 640, 640});
            m_InShapeMask.push_back("xx??");
        }

        std::vector<Base::BoundingBox> YOLOv10::ParseRawOutput(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;
            auto& output = outputs.at(0);
            const auto raw_ptr = output->Ptr<float>();  // Adjust according to the size of model elements
            const auto& shape = output->GetShape();
            
            // [1, 300, 6] end to end
            std::size_t num_channels = shape.at(1);	// 300
            std::size_t num_anchors = shape.at(2);	// 6
            Matrix<float> mat = Matrix<float>(raw_ptr, num_channels, num_anchors);
            for(int idx = 0; idx < mat.Rows(); ++idx)
            {
                int left = mat.Get(idx, 0);
                int top = mat.Get(idx, 1);
                int width = mat.Get(idx, 2);
                int height = mat.Get(idx, 3);
                float score = mat.Get(idx, 4);
                int class_idx = mat.Get(idx, 5);
                
                if(score > ic->conf_threshold) {
                    result.emplace_back(left, top, width, height, score, class_idx);
                }
            }

            return result;            
        }
    } // namespace Algorithms
    
    
} // namespace Inference


