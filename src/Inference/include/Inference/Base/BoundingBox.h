#pragma once
#include <cstdint>

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

        
    } // namespace Base
    
    
} // namespace Inference
