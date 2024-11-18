#pragma once
#include <string>
#include <memory>
#include "Inference/Base/BoundingBox.h"
#include "SafeGuard/ResultFormatter.h"


namespace SafeGuard
{
    class INotification {
    public:
        virtual ~INotification() = default;

        inline void Notify(const std::string& filename, const Inference::Base::OutputBoxes& boxes, std::shared_ptr<std::vector<std::string>> labels) {
            std::string result = ResultFormatter::Format(filename, boxes, labels);
            NotifyImpl(result);
        }
    protected:
        // 发送通知
        virtual void NotifyImpl(const std::string& message) = 0;
};
    
} // namespace SafeGuard
