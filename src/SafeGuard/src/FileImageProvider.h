#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SafeGuard/ImageProvider.h"
#include "Networks/ImageFilter.h"


namespace SafeGuard
{
    class FileImageProvider: public ImageProvider
    {
        typedef std::vector<std::string>::iterator Iter;
    public:

        FileImageProvider() = default;
        ~FileImageProvider() = default;

        bool Initialize(const std::string& path, bool loopReading);

        virtual std::pair<std::string, cv::Mat> NextImage() override; 

    private:


    private:
        std::string m_path;
        std::vector<std::string> m_images;
        Iter m_imageIter;
        bool m_loopReading;

        std::unique_ptr<Networks::ImageFilter> m_filter;
    };
    
    
    
} // namespace SafeGuard
