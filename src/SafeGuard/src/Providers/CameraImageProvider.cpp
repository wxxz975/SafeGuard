#include "CameraImageProvider.h"
#include "Common/Logger.h"
#include "Common/IFilesystem.h"


namespace SafeGuard
{
    CameraImageProvider::~CameraImageProvider()
    {
        if(m_caper.isOpened()) {
            m_caper.release();
        }
    }

    bool CameraImageProvider::Initialize(int index)
    {
        m_index = index;
        if(!m_caper.open(index)) {
            Common::logError("Failed to open camera index:{}", index);
            return false;
        }
        return true;
    }

    bool CameraImageProvider::Initialize(const std::string& filename, bool loopReading)
    {
        m_source = filename;
        if(!m_caper.open(filename)) {
            Common::logError("Failed to open camera filename:{}", filename);
            return false;
        }
        return true;
    }

    std::pair<std::string, cv::Mat> CameraImageProvider::NextImage()
    {
        cv::Mat img;
        std::string filename;
        std::string save_path;
        if(m_caper.isOpened()) {
            m_caper >> img;
            if(img.empty() && m_loopReading && !m_source.empty()) { 
                m_caper.release();
                m_caper.open(m_source);
                Common::logWarn("Failed to read camera image, start reset video!");
            }
            if(!img.empty()) {
                filename = GenerateName();
                save_path = Common::IFilesystem::ConcatPath(m_save_dir, filename);
                cv::imwrite(save_path, img);
                if(m_callback) m_callback(filename, save_path);
            }
        }
        return {filename, img};
    }

    std::string CameraImageProvider::GenerateName()
    {
        std::string basename = Common::GetCurrentTimestamp() + ".jpg";

        return m_index == -1 ? "video_" + basename : "camera_" + basename;
    }

} // namespace SafeGuard
