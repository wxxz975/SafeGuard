#pragma once
#include "SafeGuard/INotification.h"

namespace SafeGuard
{

    class WebSocketNotification: public INotification
    {
    public:
        WebSocketNotification() = default;
        ~WebSocketNotification() = default;
    protected:
        virtual void NotifyImpl(const std::string& msg) override;
    };
    
    
    
    
} // namespace SafeGuard
