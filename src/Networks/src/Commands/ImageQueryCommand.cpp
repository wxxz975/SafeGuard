#include "Commands/ImageQueryCommand.h"
#include "Common/ServiceLocator.h"
#include "SafeGuard/ImageSourceManager.h"


namespace Networks
{
    std::string ImageQueryCommand::Execute(const HttpRequest &req)
    {
        std::string filename = ParseFilename(req.GetPath());
        if(filename.empty()) return "";

        return Common::ServiceLocator::Get<SafeGuard::ImageSourceManager>().GetImagePath(filename);
    } 

    std::string ImageQueryCommand::ParseFilename(const std::string& uri)
    {
        std::string filename;
        
        auto pos = uri.find_last_of('/');
        if(pos != std::string::npos)
            filename = uri.substr(pos + 1);

        return filename;
    }
} // namespace Networks

