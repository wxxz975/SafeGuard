#include "Inference/Algorithms/RTDetr.h"

#include "ImageOps.h"

namespace Inference
{
    namespace Algorithms
    {
        ARtdetr::ARtdetr()
        {
            m_theoryOutShape.push_back({1 ,300, 18});
            m_OutShapeMask.push_back("xx?");
            m_theoryInShape.push_back({1, 3, 640, 640});
            m_InShapeMask.push_back("xx??");
        }

        std::vector<Base::TensorPtr> ARtdetr::Preprocessing(const cv::Mat &image, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::TensorPtr> result;
            // 1. letterbox
            // 2. convert ele type [float]
            // 3. convert color to rgb
            // 4. convert layout NCHW -> [1, 3, 640, 640]
            // 5. scale -> [0~255]

            const std::vector<uint64_t>& inputShape = m_metadata->inputs.at(0).shape;
            
            cv::Size original_size = image.size();
            ic->original_size = {original_size.width, original_size.height};

            ic->target_size = {inputShape.at(3), inputShape.at(2)}; // [1, 3, 640, 640] [NCHW]
            cv::Size target_size = ConvertToCVSize(ic->target_size);

            auto newimg = BlobFromImage(image, 1 / 255.0, target_size,  cv::Scalar(0,0,0), true);
           
            ic->input_tensor = std::make_shared<Base::Tensor>(
                Base::Shape({}),
                Base::ElementType(Base::Type_t::f32),
                reinterpret_cast<void*>(newimg.data)
            );

            result.emplace_back(
                    ic->input_tensor
                );

            return result;
        }

        std::vector<Base::BoundingBox> ARtdetr::Postprocessing(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;
            auto output = outputs.at(0);
            float* raw_ptr = output->Ptr<float>();
            const auto& shape = output->GetShape();
            /*
                output shape:[1,300,18]
            */
            std::size_t num_channels = shape.at(2);	// 18
            std::size_t num_anchors = shape.at(1);	// 300
            num_channels = shape.at(2);
            num_anchors = shape.at(1);
            cv::Size outShape = cv::Size(num_channels, num_anchors);
            cv::Mat output0 = cv::Mat(outShape, CV_32F, raw_ptr);

            for(std::size_t idx = 0; idx < output0.rows; ++idx) {
                cv::Mat scores = output0.
                    row(idx).colRange(RTDETR_OUTBOX_ELEMENT_COUNT, num_channels);

                const rtdetrRawOutput* bbox = output0.row(idx).ptr<rtdetrRawOutput>();
                cv::Point classIdPoint;
                double score;
                cv::minMaxLoc(scores, 0, &score, 0, &classIdPoint);
                
                cv::Size oriSize = ConvertToCVSize(ic->original_size);
                if (score > ic->conf_threshold)
                {
                    std::int32_t width = static_cast<std::int32_t>(bbox->w * oriSize.width);
                    std::int32_t height = static_cast<std::int32_t>(bbox->h * oriSize.height);
                    std::int32_t left = static_cast<std::int32_t>((bbox->cx - bbox->w / 2) * oriSize.width);
                    std::int32_t top = static_cast<std::int32_t>((bbox->cy - bbox->h / 2) * oriSize.height);

                    result.emplace_back(left, top, width, height,
                        static_cast<float>(score),
                        static_cast<std::size_t>(classIdPoint.x));
                }
            }

            return result;

        }

    } // namespace Algorithms
    
    
} // namespace Inference
