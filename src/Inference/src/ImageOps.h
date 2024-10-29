#pragma once
#include <opencv2/opencv.hpp>

#include "Inference/Base/BoundingBox.h"
#include "Inference/Base/Shape.h"

namespace Inference
{
    cv::Mat Letterbox(const cv::Mat& image, const cv::Size& newShape = cv::Size(640, 640),
            const cv::Scalar& color = cv::Scalar(114, 114, 114), bool scaleFill = false, bool scaleUp = true,
            int stride = 32);

        void RestoreOriginalCoordinates(const cv::Size& currentShape, const cv::Size& originalShape, Base::BoundingBox& bbox);

        void RestoreOriginalCoordsInBatch(const cv::Size& currentShape, const cv::Size& originalShape, std::vector<Base::BoundingBox>& boxes);


        inline cv::Mat BlobFromImage(const cv::Mat& image, double scalefactor=1.0, const cv::Size& size = cv::Size(),
                                   const cv::Scalar& mean = cv::Scalar(), bool swapRB=false, bool crop=false,
                                   int ddepth=CV_32F) {
            return cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB, crop, ddepth);
        }

        
        float IoU(const Base::BoundingBox& box1, const Base::BoundingBox& box2);

        
        std::vector<Base::BoundingBox> NMS(const std::vector<Base::BoundingBox>& boxes, float iou_threshold);

       
        cv::Mat Convert2RGB(const cv::Mat& image);


        
        void HWC2CHW(const cv::Mat& image, std::vector<float>& blob);

        void HWC2CHW(const cv::Mat& image, float* blob);


        cv::Mat RenderBoundingBoxes(const cv::Mat& image, const std::vector<Base::BoundingBox>& boxes,
            const std::vector<std::string>& labels = std::vector<std::string>());

        cv::Mat RenderBoundingBoxes(const std::string& img_path, const std::vector<Base::BoundingBox>& boxes,
            const std::vector<std::string>& labels = std::vector<std::string>());


        cv::Size ConvertToCVSize(const Base::ImageSize& size);
} // namespace Inference
