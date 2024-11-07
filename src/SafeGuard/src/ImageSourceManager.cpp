#include "SafeGuard/ImageSourceManager.h"


namespace SafeGuard
{
    
    void ImageSourceManager::AddImageAsset(const std::string &filename, const std::string &filepath)
    {
        m_filename2path.insert({filename, filepath});
    }

    std::string ImageSourceManager::GetImagePath(const std::string& filename) const
    {
        std::string path;
        if(m_filename2path.count(filename)) {
            path = m_filename2path.at(filename);
        }
        return path;
    }
} // namespace SafeGuard


