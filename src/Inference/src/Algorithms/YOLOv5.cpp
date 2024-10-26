#include "Inference/Algorithms/YOLOv5.h"
#include "Common/Utils.h"

namespace Inference
{
    namespace Algorithms
    { 
        std::vector<Base::BoundingBox> YOLOv5::ParseRawOutput(const std::vector<Base::TensorPtr> &outputs, std::shared_ptr<InferenceContext> ic)
        {
            std::vector<Base::BoundingBox> result;
            auto& output = outputs.at(0);
            auto* raw_ptr = output->Ptr<float>();
            const auto& shape = output->GetShape();

            std::size_t num_channels = 0;
            std::size_t num_anchors = 0;

            cv::Size outShape;
            cv::Mat output0;
            /*
                old shape: [1,25200,85] ,
                new shape: [1, 85, 8400], 
            */
            if(m_useNewOutputShape) {
                num_channels = shape.at(1);
                num_anchors = shape.at(2);
                outShape = cv::Size(num_anchors, num_channels);
                // Common::zlog("use new shape\n");
            }else {
                num_channels = shape.at(2);
                num_anchors = shape.at(1);
                outShape = cv::Size(num_channels, num_anchors);
                // Common::zlog("use old shape\n");
            }
            
            output0 = cv::Mat(outShape, CV_32F, raw_ptr);
            if(m_useNewOutputShape) output0 = output0.t();

            for (std::size_t idx = 0; idx < output0.rows; ++idx)
            {
                cv::Mat scores = output0.
                    row(idx).colRange(
                        m_useNewOutputShape ? YOLOV5NEW_OUTBOX_ELEMENT_COUNT:YOLOV5_OUTBOX_ELEMENT_COUNT, 
                        num_channels);
                
                const Yolov5RawResult* bbox = output0.row(idx).ptr<Yolov5RawResult>();
                cv::Point classIdPoint;
                double score;
                cv::minMaxLoc(scores, 0, &score, 0, &classIdPoint);
                
                if (score > ic->conf_threshold)
                {
                    // TODO: old version something error in output
                    if(score * bbox->box_conf > ic->conf_threshold) {
                        // Common::zlog("objConf:%f, boxConf:%f\n", (float)score, bbox->box_conf);
                    }
                    
                    std::int32_t width = static_cast<std::int32_t>(bbox->w);
                    std::int32_t height = static_cast<std::int32_t>(bbox->h);
                    std::int32_t left = static_cast<std::int32_t>(bbox->cx) - width / 2;
                    std::int32_t top = static_cast<std::int32_t>(bbox->cy) - height / 2;

                    result.emplace_back(left, top, width, height,
                        static_cast<float>(m_useNewOutputShape ? score : score * bbox->box_conf),
                        static_cast<std::size_t>(classIdPoint.x));
                }
                
            }

            return result;
        }

        bool YOLOv5::CheckIOShape()
        {
            using namespace Common;
            const std::vector<std::uint64_t>& model_input_shape = m_metadata->inputs.at(0).shape;
            const std::vector<std::uint64_t>& model_output_shape = m_metadata->outputs.at(0).shape;

            // compare real output shape with theory shape(2 situations)
            bool useNewOutShape = CompareVecWithMask(m_OutShapeMask_new, m_theoryOutShape_new, model_output_shape);
            bool useOldOutShape = CompareVecWithMask(m_OutShapeMask_old, m_theoryOutShape_old, model_output_shape);

            m_useNewOutputShape = useNewOutShape;
            if(!useOldOutShape && !useNewOutShape) {
                auto shape = VecToStr(model_output_shape);
                auto shapeNew = VecToStr(m_theoryOutShape_new);
                auto shapeOld = VecToStr(m_theoryOutShape_old);
                //Common::zlog("OutputShape:%s, imcompatiable with ShapeNew:%s or ShapeOld:%s\n", 
                    //shape.c_str(), shapeNew.c_str(), shapeOld.c_str());
            }


            return CompareVecWithMask(m_InShapeMask, m_theoryInShape, model_input_shape) 
                    && (useNewOutShape || useOldOutShape);
        }
    } // namespace Algorithms

} // namespace Inference
