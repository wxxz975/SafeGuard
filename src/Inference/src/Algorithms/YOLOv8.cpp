#include "Inference/Algorithms/YOLOv8.h"




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
            auto raw_ptr = output->Ptr<float>();  // Adjust according to the size of model elements
            const auto& shape = output->GetShape();
            
            // 1, 84, 8400
            std::size_t num_channels = shape.at(1);	// 84
            std::size_t num_anchors = shape.at(2);	// 8400
            cv::Size outShape = cv::Size(num_anchors, num_channels);

            cv::Mat output0 = cv::Mat(outShape, CV_32F, raw_ptr).t();

            for (std::size_t idx = 0; idx < output0.rows; ++idx)
            {
                cv::Mat scores = output0.row(idx).colRange(YOLOV8_OUTBOX_ELEMENT_COUNT, num_channels);
                const Yolov8RawResult* bbox = output0.row(idx).ptr<Yolov8RawResult>();
                cv::Point classIdPoint;
                double score = 0;
                cv::minMaxLoc(scores, 0, &score, 0, &classIdPoint);
                
                if (score > ic->conf_threshold)
                {
                    std::int32_t width = static_cast<std::int32_t>(bbox->w);
                    std::int32_t height = static_cast<std::int32_t>(bbox->h);
                    std::int32_t left = static_cast<std::int32_t>(bbox->cx) - width / 2;
                    std::int32_t top = static_cast<std::int32_t>(bbox->cy) - height / 2;

                    result.emplace_back(
                            left, top, width, height, 
                            static_cast<float>(score), 
                            static_cast<std::size_t>(classIdPoint.x));
                }
            }

            return result;
        }
    }
}