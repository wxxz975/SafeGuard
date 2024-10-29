#pragma once
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>
#include "Inference/Base/Tensor.h"
#include "Inference/Base/ModelMetadata.h"
#include "Inference/Base/BoundingBox.h"

#include "Inference/InferenceContext.h"

namespace Inference
{
    class PrePostProcessorImpl
    {
    public:
        PrePostProcessorImpl() = default;
        virtual ~PrePostProcessorImpl() = default;

        virtual bool Initialize(std::shared_ptr<Base::ModelMetadata> metadata) = 0;

        virtual std::vector<Base::TensorPtr> Preprocessing(const cv::Mat& image, std::shared_ptr<InferenceContext> ic) = 0;

        virtual std::vector<Base::BoundingBox> Postprocessing(const std::vector<Base::TensorPtr>& output, std::shared_ptr<InferenceContext> ic) = 0;

        virtual cv::Mat RenderBoxes(const std::vector<Base::BoundingBox>& boxes, const std::string& image_path) = 0;

        virtual bool CheckIOShape() = 0;

    protected:

        std::shared_ptr<Base::ModelMetadata> m_metadata;
    };
    

} // namespace Inference
