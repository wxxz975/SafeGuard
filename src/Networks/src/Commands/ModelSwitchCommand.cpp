#include "Commands/ModelSwitchCommand.h"

#include "Common/ServiceLocator.h"

#include "Inference/InferenceEngine.h"
#include "Inference/SupportedFrameworks.h"
#include "Inference/SupportedModels.h"

#include "SafeGuard/ModelSourceManager.h"

#include "Networks/ResponseJsonBuilder.h"

namespace Networks
{
    std::string ModelSwitchCommand::Execute(const HttpRequest &req)
    {
        std::string model_name = req.GetHeader("ModelName");
        std::string algorithm = req.GetHeader("Algorithm");
        std::string framework = req.GetHeader("Framework");
        bool status = false;
        std::vector<std::string> labels;

        std::string model_path = Common::ServiceLocator::Get<SafeGuard::ModelSourceManager>().GetModelPath(model_name);
        if(!model_path.empty() && Inference::SupportedFrameworks::IsValid(framework) && Inference::SupportedModels::IsValid(algorithm)) {
            status = Common::ServiceLocator::Get<Inference::InferenceEngine>().Initialize(model_path, algorithm, framework);
            labels = Common::ServiceLocator::Get<Inference::InferenceEngine>().GetLabels();
        }
        
        return ResponseJsonBuilder::CreateModelSwitchResponse(status, model_name, algorithm, framework, labels);
    }
}
