#pragma once
#include <memory>
#include <string>
#include "SafeGuard/ImageProvider.h"
#include "Common/Utils.h"

namespace SafeGuard
{
    class CameraImageProvider: public ImageProvider
    {
    public:
        CameraImageProvider() = default;
        ~CameraImageProvider();

        bool Initialize(int index = 0);
        bool Initialize(const std::string& filename, bool loopReading);

        virtual std::pair<std::string, cv::Mat> NextImage() override;

    private:
        std::string GenerateName();
    private:
        cv::VideoCapture m_caper;
        std::string m_source;
        int m_index = -1;

        bool m_loopReading = false;
    };
    
    
    
    
} // namespace SafeGuard
