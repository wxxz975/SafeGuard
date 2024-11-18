#include "NetworkImageProvider.h"
#include "Common/Logger.h"
#include "Common/IFilesystem.h"

namespace SafeGuard
{
    bool NetworkImageProvider::Initialize(std::shared_ptr<Common::SafeQueue<std::string>> source_queue)
    {
        if(!source_queue) {
            Common::logError("Invalid Network queue!");
            return false;
        }

        m_queue = source_queue;
        return true;
    }

    std::pair<std::string, cv::Mat> NetworkImageProvider::NextImage()
    {
        cv::Mat img;
        std::string filename;
        auto img_path = m_queue->Take();
        if(img_path) {
            img = cv::imread(*img_path);

            filename = Common::IFilesystem::GetFilename(*img_path);
            if(m_callback) m_callback(filename, *img_path);
        }

        return {filename, img};
    }

} // namespace SafeGuard
