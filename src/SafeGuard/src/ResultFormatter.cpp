#include "SafeGuard/ResultFormatter.h"
#include "Networks/ResponseJsonBuilder.h"
#include <array>

namespace SafeGuard
{

    std::string ResultFormatter::Format(const std::string& filename,  const Inference::Base::OutputBoxes& boxes, std::shared_ptr<std::vector<std::string>> labels)
    {
        return Networks::ResponseJsonBuilder::CreateNewResultMessage(filename, boxes, labels);
    }
    
} // namespace SafeGuard
