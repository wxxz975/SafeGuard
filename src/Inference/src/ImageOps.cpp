#include "ImageOps.h"


namespace Inference
{
    cv::Mat Letterbox(const cv::Mat& image, 
        const cv::Size& newShape, 
        const cv::Scalar& color, 
        bool scaleFill, bool scaleUp, 
        int stride)
        {
            cv::Mat outImage;
            cv::Size shape = image.size();
            float scale_factor = std::min(static_cast<float>(newShape.height) / static_cast<float>(shape.height),
                static_cast<float>(newShape.width) / static_cast<float>(shape.width));

            if (!scaleUp)
                scale_factor = std::min(scale_factor, 1.0f);

            float width_padding = (newShape.width - shape.width * scale_factor) / 2.f;
            float height_padding = (newShape.height - shape.height * scale_factor) / 2.f;

            if (scaleFill) {
                width_padding = 0.0f;
                height_padding = 0.0f;
                scale_factor = static_cast<float>(newShape.width) / shape.width;
            }

            // 调整图像大小
            //cv::Mat outImage;
            if (shape.width != static_cast<int>(shape.width * scale_factor) &&
                shape.height != static_cast<int>(shape.height * scale_factor)) {
                cv::resize(image, outImage, cv::Size(static_cast<int>(shape.width * scale_factor),
                    static_cast<int>(shape.height * scale_factor)));
            }
            else {
                outImage = image;
            }

            // 计算边界
            int top = static_cast<int>(std::round(height_padding - 0.1f));
            int bottom = static_cast<int>(std::round(height_padding + 0.1f));
            int left = static_cast<int>(std::round(width_padding - 0.1f));
            int right = static_cast<int>(std::round(width_padding + 0.1f));

            // 添加边界
            cv::copyMakeBorder(outImage, outImage, top, bottom, left, right, cv::BORDER_CONSTANT, color);

            return outImage;
        }

        void RestoreOriginalCoordinates(const cv::Size &currentShape, const cv::Size &originalShape, Base::BoundingBox &bbox)
        {
            float gain = std::min(static_cast<float>(currentShape.height) / static_cast<float>(originalShape.height),
            static_cast<float>(currentShape.width) / static_cast<float>(originalShape.width));

            int pad[2] = {
            static_cast<int>((static_cast<float>(currentShape.width) - static_cast<float>(originalShape.width) * gain) / 2.0f),
            static_cast<int>((static_cast<float>(currentShape.height) - static_cast<float>(originalShape.height) * gain) / 2.0f)
            };

            bbox.left = static_cast<int>(std::round((static_cast<float>(bbox.left - pad[0]) / gain)));
            bbox.top = static_cast<int>(std::round((static_cast<float>(bbox.top - pad[1]) / gain)));

            bbox.width = static_cast<int>(std::round(((float)bbox.width / gain)));
            bbox.height = static_cast<int>(std::round(((float)bbox.height / gain)));
        }

        void RestoreOriginalCoordsInBatch(const cv::Size& currentShape, const cv::Size& originalShape, std::vector<Base::BoundingBox>& boxes)
        {
            for (auto& box : boxes)
                RestoreOriginalCoordinates(currentShape, originalShape, box);
        }


        float IoU(const Base::BoundingBox& box1, const Base::BoundingBox& box2)
        {
            float x1 = std::max(box1.left, box2.left);
            float y1 = std::max(box1.top, box2.top);
            float x2 = std::min(box1.left + box1.width, box2.left + box2.width);
            float y2 = std::min(box1.top + box1.height, box2.top + box2.height);

            float intersection_width = std::max(0.0f, x2 - x1);
            float intersection_height = std::max(0.0f, y2 - y1);
            float intersection_area = intersection_width * intersection_height;

            float box1_area = box1.width * box1.height;
            float box2_area = box2.width * box2.height;

            float union_area = box1_area + box2_area - intersection_area;

            return intersection_area / union_area;
        }

        std::vector<Base::BoundingBox> NMS(const std::vector<Base::BoundingBox>& boxes, float iou_threshold)
        {
            std::vector<Base::BoundingBox> selected_boxes;
            std::vector<bool> is_selected(boxes.size(), false);

            for (size_t i = 0; i < boxes.size(); ++i) {
                if (is_selected[i])
                    continue;

                selected_boxes.push_back(boxes[i]);
                is_selected[i] = true;

                for (size_t j = i + 1; j < boxes.size(); ++j) {
                    if (!is_selected[j] && IoU(boxes[i], boxes[j]) > iou_threshold) {
                        is_selected[j] = true;
                    }
                }
            }

            return selected_boxes;
        }


        

        cv::Mat Convert2RGB(const cv::Mat& image)
        {
            cv::Mat out;

            int channel = image.channels();
            
            if (channel == 1)
                cv::cvtColor(image, out, cv::COLOR_GRAY2RGB);
            else if (channel == 3)
                cv::cvtColor(image, out, cv::COLOR_BGR2RGB);
            else if (channel == 4)
                cv::cvtColor(image, out, cv::COLOR_BGRA2RGB);
            

            return out;
        }

        void HWC2CHW(const cv::Mat& image, std::vector<float>& blob)
        {
            std::size_t channels = image.channels();
            std::size_t width = image.cols;
            std::size_t height = image.rows;
            std::size_t blob_size = width * height * channels;
            cv::Size channel_size = { image.cols, image.rows };

            if (blob.size() < blob_size)
                blob.resize(blob_size);

            std::vector<cv::Mat> chw(channels);
            for (std::size_t idx = 0; idx < channels; ++idx)
            {
                chw[idx] = cv::Mat(channel_size, CV_32FC1, blob.data() + idx * width * height);
            }
            cv::split(image, chw);  // In fact, it is output to the memory pointed to by this blob.
        }

        void HWC2CHW(const cv::Mat& image, float* blob)
        {
            std::size_t channels = image.channels();
            std::size_t width = image.cols;
            std::size_t height = image.rows;
            std::size_t blob_size = width * height * channels;
            cv::Size channel_size = { image.cols, image.rows };
            

            std::vector<cv::Mat> chw(channels);
            for (std::size_t idx = 0; idx < channels; ++idx)
            {
                chw[idx] = cv::Mat(channel_size, CV_32FC1, blob + idx * width * height);
            }
            cv::split(image, chw);  // In fact, it is output to the memory pointed to by this blob.
        }

        cv::Mat RenderBoundingBoxes(const cv::Mat& image, const std::vector<Base::BoundingBox>& boxes,
            const std::vector<std::string>& labels)
        {
            cv::Mat out = image.clone();
            for (const auto& box : boxes) {
                cv::rectangle(out, cv::Rect(box.left, box.top, box.width, box.height), cv::Scalar(0, 0, 255), 2); // 绘制绿色边界框，线宽为2

                cv::Point labelPosition(box.left, box.top - 10); 
                std::string label = labels.empty() ? std::to_string(box.class_index) : labels[box.class_index];
                cv::putText(out, label, labelPosition, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
            }
            return out;
        }

        cv::Mat RenderBoundingBoxes(const std::string& img_path, const std::vector<Base::BoundingBox>& boxes,
            const std::vector<std::string>& labels)
        {
            auto img = cv::imread(img_path);   
            return RenderBoundingBoxes(img, boxes, labels);
        }

        cv::Size ConvertToCVSize(const Base::ImageSize &size)
        {
            return cv::Size(size.width, size.height);
        }

} // namespace Inference
