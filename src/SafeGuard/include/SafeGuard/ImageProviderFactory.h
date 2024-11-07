#pragma once
#include <memory>
#include <string>
#include "SafeGuard/ImageProviderType.h"
#include "SafeGuard/ImageProvider.h"

namespace SafeGuard
{
    class ImageProviderFactory
    {
    public:

        static std::unique_ptr<ImageProvider> CreateProvider(ImageProviderType type, const std::string& params);

    private:
        ImageProviderFactory() = delete;
        ~ImageProviderFactory() = delete;
    };
    
    
    

} // namespace SafeGuard
