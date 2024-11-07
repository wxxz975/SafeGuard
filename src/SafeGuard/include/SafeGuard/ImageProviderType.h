#pragma once
#include <cstdint>
#include <string>

namespace SafeGuard
{
    
    enum class ImageProviderType: int32_t {
        FROM_IMAGE = 0,
        FROM_VIDEO = 1,
        FROM_NETWORK = 2,
        FROM_CAMERA = 3, 
        MAX_TYPE
    };

    inline std::string ImageProviderTypeToStr(ImageProviderType type){
        switch (type)
        {
        case ImageProviderType::FROM_IMAGE:     return "FROM_IMAGE";
        case ImageProviderType::FROM_VIDEO:     return "FROM_VIDEO";
        case ImageProviderType::FROM_NETWORK:   return "FROM_NETWORK";
        case ImageProviderType::FROM_CAMERA:    return "FROM_CAMERA";
        
        default: return std::string();
        }
    }


} // namespace SafeGuard
