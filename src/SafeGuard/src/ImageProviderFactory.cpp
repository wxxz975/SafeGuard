#include "SafeGuard/ImageProviderFactory.h"

#include "Providers/FileImageProvider.h"
#include "Providers/CameraImageProvider.h"
#include "Providers/NetworkImageProvider.h"
#include "Providers/VideoImageProvider.h"

#include "Common/Logger.h"

namespace SafeGuard
{
   

    /*
         enum class ImageProviderType: int32_t {
        FROM_IMAGE = 0,
        FROM_VIDEO = 1,
        FROM_NETWORK = 2,
        FROM_CAMERA = 3, 
        MAX_TYPE
    };

    */
    std::unique_ptr<ImageProvider> ImageProviderFactory::CreateProvider(ImageProviderType type, const std::string& params)
    {
        switch (type)
        {
        case ImageProviderType::FROM_IMAGE:     {
            auto ptr = std::make_unique<FileImageProvider>();
            ptr->Initialize(params, true);
            return std::move(ptr);
        }
        case ImageProviderType::FROM_VIDEO: {
            auto ptr = std::make_unique<VideoImageProvider>();
            ptr->Initialize(params, true);
            return std::move(ptr);
        }
        case ImageProviderType::FROM_NETWORK: {
            auto ptr = std::make_unique<NetworkImageProvider>();
            return std::move(ptr);
        }
        case ImageProviderType::FROM_CAMERA: {
            auto ptr = std::make_unique<CameraImageProvider>();
            try
            {
                int idx = std::stoi(params);
                ptr->Initialize(idx);
            }
            catch(const std::exception& e)
            {
                Common::logError("Invalid image provider params: {}", params);
                return nullptr;
            }
            
            return std::move(ptr);
        }
        default:
            assert(0 && "Invalid Image Provider type!");
        }
    }
} // namespace SafeGuard



