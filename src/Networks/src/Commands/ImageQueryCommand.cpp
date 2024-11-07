#include "Commands/ImageQueryCommand.h"
#include "Common/ServiceLocator.h"
#include "SafeGuard/ImageSourceManager.h"


namespace Networks
{
    std::string ImageQueryCommand::Execute(const HttpRequest &req)
    {
        std::string filename = req.GetHeader("Image");

        return Common::ServiceLocator::Get<SafeGuard::ImageSourceManager>().GetImagePath(filename);
    } 
} // namespace Networks

