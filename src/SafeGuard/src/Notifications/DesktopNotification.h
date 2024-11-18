#pragma once
#include "SafeGuard/INotification.h"

namespace SafeGuard
{

    class DesktopNotification: public INotification
    {
    public:
        DesktopNotification() = default;
        ~DesktopNotification() = default;

        virtual void NotifyImpl(const std::string& msg) override;
    };
    
  
    
    
} // namespace SafeGuard
