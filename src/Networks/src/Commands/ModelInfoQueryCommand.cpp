#include "Commands/ModelInfoQueryCommand.h"
#include "Common/ServiceLocator.h"
#include "Common/Logger.h"

#include "Inference/InferenceEngine.h"
#include "SafeGuard/ModelSourceManager.h"

#include "Networks/ResponseJsonBuilder.h"

namespace Networks
{
    
    std::string ModelInfoQueryCommand::Execute(const HttpRequest& req)
    {   
        bool status = false;
        std::string filename = req.GetParams("ModelName");
        Common::logInfo("ModelInfoQuery: {}", filename);
        std::shared_ptr<std::vector<std::string>> labels = nullptr;
        auto modelMgr = Common::ServiceLocator::Get<SafeGuard::ModelSourceManager>();
        const auto& inferEngine = Common::ServiceLocator::Get<Inference::InferenceEngine>();
        if(filename == inferEngine.GetState().model_name) {
            labels = inferEngine.GetLabels();
            status = true;
        }

        return Networks::ResponseJsonBuilder::CreateModelInfoQueryResponse(status, filename, labels);
    }
} // namespace Networks
