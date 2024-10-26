#pragma once
#include <memory>
#include "Base/Tensor.h"
#include "Base/Shape.h"

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
    };
    
    typedef std::shared_ptr<InferenceContext> InferenceContextPtr;
} // namespace Inference
