#include "Notifications/WebSocketNotification.h"

#include "Common/ServiceLocator.h"
#include "Networks/WebPage/WebSocketHandler.h"

namespace SafeGuard
{
    void WebSocketNotification::NotifyImpl(const std::string& msg)
    {
        if(Common::ServiceLocator::IsValid<Networks::WebSocketHandler>()) {
            Common::ServiceLocator::Get<Networks::WebSocketHandler>().WriteData(msg);
        }
    }

} // namespace SafeGuard
