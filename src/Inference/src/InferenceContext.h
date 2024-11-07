#pragma once
#include <memory>
#include "Inference/Base/Tensor.h"
#include "Inference/Base/Shape.h"

namespace Inference
{
    
    struct InferenceContext
    {
        Base::TensorPtr input_tensor;
		Base::TensorPtr output_tensor;

        Base::ImageSize original_size;
        Base::ImageSize target_size;    

        float conf_threshold = 0.55;
        float iou_threshold = 0.6;
        InferenceContext(float iou, float conf): iou_threshold(iou), conf_threshold(conf) {}
        InferenceContext(){};
    };
    
    typedef std::shared_ptr<InferenceContext> InferenceContextPtr;
} // namespace Inference
