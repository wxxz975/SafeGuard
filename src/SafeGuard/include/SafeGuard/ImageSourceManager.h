#pragma once

#include <unordered_map>
#include <string>


namespace SafeGuard
{
    
    class ImageSourceManager
    {
    public:
        ImageSourceManager() = default;
        ~ImageSourceManager() = default;

        void AddImageAsset(const std::string& filename, const std::string& filepath);

        std::string GetImagePath(const std::string& filename) const;

    private:
        //                  filename    filepath
        std::unordered_map<std::string, std::string> m_filename2path;
    };
    
} // namespace SafeGuard
