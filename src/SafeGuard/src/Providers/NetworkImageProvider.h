#pragma once
#include <memory>
#include "SafeGuard/ImageProvider.h"
#include "Common/SafeQueue.h"
namespace SafeGuard
{

    class NetworkImageProvider: public ImageProvider
    {
    public:
        NetworkImageProvider() = default;
        ~NetworkImageProvider() = default;

        bool Initialize(std::shared_ptr<Common::SafeQueue<std::string>> source_queue);

        virtual std::pair<std::string, cv::Mat> NextImage() override;

    private:
        std::shared_ptr<Common::SafeQueue<std::string>> m_queue;
    };
    
    
    

    
} // namespace SafeGuard
