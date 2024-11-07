#pragma once
#include <string>
#include <functional>
#include <opencv2/opencv.hpp>


namespace SafeGuard
{
    class ImageProvider
    {
    public:
        typedef std::function<void(const std::string&, const std::string&)> NextImageCallback;

        ImageProvider() = default;
        ~ImageProvider() = default;

        inline void SetNextImageCallback(const NextImageCallback& callback) { m_callback = callback; };
        inline void SetSaveDirectory(const std::string& dir) { m_save_dir = dir; };

        virtual std::pair<std::string, cv::Mat> NextImage() = 0; 

        
    protected:
        NextImageCallback m_callback;
        std::string m_save_dir;
    };
    
    
    
} // namespace SafeGuard
