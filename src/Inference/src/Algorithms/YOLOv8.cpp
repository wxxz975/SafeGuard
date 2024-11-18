#include "Algorithms/YOLOv8.h"


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
            
            // 1, 84, 8400
            std::size_t num_channels = shape.at(1);	// 84
            std::size_t num_anchors = shape.at(2);	// 8400
            cv::Size outShape = cv::Size(num_anchors, num_channels);

            /* 
            * 转置会拷贝内存，并且会拖慢这个解析的过程， 减少使用这个转置，但是如果使用转置这个我们 
            *	定义的结构体就用不上了，因为这个每一个raw 的box 内存排列不是按照顺序排列的
            * */ 
            cv::Mat output0 = cv::Mat(outShape, CV_32F, raw_ptr);
            for(int idx = 0; idx < output0.cols; ++idx) {
                const cv::Mat classes_scores = output0.col(idx).rowRange(YOLOV8_OUTBOX_ELEMENT_COUNT, num_channels);
                const Yolov8RawResult* bbox = output0.col(idx).ptr<Yolov8RawResult>();
                cv::Point classIdPoint;
                double score;
                cv::minMaxLoc(classes_scores, nullptr, &score, nullptr, &classIdPoint);

                // 置信度 0～1之间
                if (score > ic->conf_threshold) {
                    int32_t width = output0.at<float>(2, idx);
                    int32_t height = output0.at<float>(3, idx);
                    int32_t left = output0.at<float>(0, idx) - width / 2;
                    int32_t top = output0.at<float>(1, idx) - height / 2;

                    result.emplace_back(
                            left, top, width, height, 
                            static_cast<float>(score), 
                            static_cast<std::size_t>(classIdPoint.x));
                }
            }
            /*
                cv::Mat output0 = cv::Mat(outShape, CV_32F, raw_ptr).t();
		        使用转置的版本 
            */
            // for (std::size_t idx = 0; idx < output0.rows; ++idx)
            // {
            //     cv::Mat scores = output0.row(idx).colRange(YOLOV8_OUTBOX_ELEMENT_COUNT, num_channels);
            //     const Yolov8RawResult* bbox = output0.row(idx).ptr<Yolov8RawResult>();
            //     cv::Point classIdPoint;
            //     double score = 0;
            //     cv::minMaxLoc(scores, 0, &score, 0, &classIdPoint);
                
            //     if (score > ic->conf_threshold)
            //     {
            //         std::int32_t width = static_cast<std::int32_t>(bbox->w);
            //         std::int32_t height = static_cast<std::int32_t>(bbox->h);
            //         std::int32_t left = static_cast<std::int32_t>(bbox->cx) - width / 2;
            //         std::int32_t top = static_cast<std::int32_t>(bbox->cy) - height / 2;

            //         result.emplace_back(
            //                 left, top, width, height, 
            //                 static_cast<float>(score), 
            //                 static_cast<std::size_t>(classIdPoint.x));
            //     }
            // }

            return result;
        }
    }
}
