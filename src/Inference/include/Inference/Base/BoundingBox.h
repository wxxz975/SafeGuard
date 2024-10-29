#pragma once
#include <cstdint>
#include <vector>
#include <ostream>

namespace Inference
{
    namespace Base
    {
         /*
        这个定义的是inference 推理后输出的结果信息
        */
        struct BoundingBox
        {
            std::int32_t    left;
            std::int32_t    top;
            std::int32_t    width;
            std::int32_t    height;
            float           confidence;
            std::size_t     class_index;

            BoundingBox() :left(0), top(0), width(0), height(0), confidence(0), class_index(0) {};
            BoundingBox(std::int32_t left, std::int32_t top,
                std::int32_t width, std::int32_t height,
                float confidence, std::size_t class_index) :
                left(left), top(top), width(width), height(height),
                confidence(confidence), class_index(class_index)
            {
            };
        };

        typedef std::vector<Base::BoundingBox> OutputBoxes;
        typedef std::function<void(const Base::OutputBoxes&)> AsynInferCallback;

        inline std::ostream& operator<<(std::ostream& os, const BoundingBox& box) {
            os << "label index:" << box.class_index << " confidence:" << box.confidence
                << " left:" << box.left << " top:" << box.top
                << " width:" << box.width << "height:" << box.height << "\n";
            return os;
        }

    } // namespace Base
    
    
} // namespace Inference
