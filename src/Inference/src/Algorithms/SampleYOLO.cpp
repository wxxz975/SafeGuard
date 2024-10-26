#include "Inference/Algorithms/SampleYOLO.h"
#include "ImageOps.h"

namespace Inference
{
    namespace Algorithms
    {
        SampleYOLO::SampleYOLO(/* args */)
        {
        }
        
        SampleYOLO::~SampleYOLO()
        {
        }

        inline std::vector<Base::TensorPtr> SampleYOLO::Preprocessing(const cv::Mat &image, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::TensorPtr> result;
            // std::vector<ImageData> result;
            // 1. letterbox
            // 2. convert ele type [float]
            // 3. convert color to rgb
            // 4. convert layout NCHW -> [1, 3, 640, 640]
            // 5. scale -> [0~255]
            const std::vector<uint64_t>& inputShape = m_metadata->inputs.at(0).shape;      // default only one input

            cv::Size original_size = image.size();
            ic->original_size = {original_size.width, original_size.height};
            
            ic->target_size = {inputShape.at(3), inputShape.at(2)}; // [1, 3, 640, 640] [NCHW]
            cv::Size target_size = ConvertToCVSize(ic->target_size);
                        
            auto newimg = Letterbox(image, target_size);
            newimg = BlobFromImage(newimg, 1 / 255.0, target_size,  cv::Scalar(0,0,0), true);

            ic->input_tensor = std::make_shared<Base::Tensor>(
                Base::Shape({inputShape.at(1), inputShape.at(2), inputShape.at(3)}),
                Base::ElementType(Base::Type_t::f32),
                reinterpret_cast<void*>(newimg.data)
            );

            result.emplace_back(
                    ic->input_tensor
                );
           
            return result;
        }

        std::vector<Base::BoundingBox> SampleYOLO::Postprocessing(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;

            result = ParseRawOutput(outputs, ic);
            result = NMS(result, ic->conf_threshold);
            RestoreOriginalCoordsInBatch(ConvertToCVSize(ic->target_size), ConvertToCVSize(ic->original_size), result);
        
            return result;
        }
    } // namespace Algorithms
} // namespace Inference
