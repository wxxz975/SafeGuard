#include "FileImageProvider.h"

#include "Common/IFilesystem.h"
#include "Common/Logger.h"

namespace SafeGuard
{
    bool FileImageProvider::Initialize(const std::string &path, bool loopReading)
    {
        using namespace Common::IFilesystem;
        m_filter = std::make_unique<Networks::ImageFilter>();
        m_path = path;
        m_loopReading = loopReading;
        if(IsFile(m_path) && m_filter->IsValid(m_path)) {
            m_images.push_back(m_path);
        }else {
            std::vector<std::string> images = ListDir(m_path);
            images.erase(std::remove_if(images.begin(), images.end(), [&](const std::string& item){
                return !m_filter->IsValid(item);
            }));

            m_images = std::move(images);
        }

        m_imageIter = m_images.begin();

        return true;
    }

    std::pair<std::string, cv::Mat> FileImageProvider::NextImage()
    {
        using namespace Common::IFilesystem;
        cv::Mat img;
        std::string filename;
        if(m_imageIter == m_images.end() && m_loopReading) {
            m_imageIter = m_images.begin();
            Common::logInfo("reset image provider to first!");
        }

        if(m_imageIter != m_images.end()) {
            filename = Common::IFilesystem::GetFilename(*m_imageIter);
            img = cv::imread(*m_imageIter);
            if(m_callback) m_callback(filename, *m_imageIter);

            m_imageIter++;
        }
        
        return {filename, img};
    }

} // namespace SafeGuard
