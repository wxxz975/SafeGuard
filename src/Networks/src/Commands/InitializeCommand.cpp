#include "Commands/InitializeCommand.h"
#include "Common/ServiceLocator.h"
#include "Common/Utils.h"

#include "Inference/InferenceEngine.h"
#include "Inference/SupportedFrameworks.h"
#include "Inference/SupportedModels.h"
#include "SafeGuard/ModelSourceManager.h"

#include "Networks/ResponseJsonBuilder.h"

namespace Networks
{
    std::string InitializeCommand::Execute(const HttpRequest &req)
    {
        const auto& state = Common::ServiceLocator::Get<Inference::InferenceEngine>().GetState();
        auto modelnames = Common::ServiceLocator::Get<SafeGuard::ModelSourceManager>().GetAllModelNames();
        auto algorithms = Inference::SupportedModels::GetAllAlgorithms();
        auto frameworks = Inference::SupportedFrameworks::GetAllFrameworks();

        int curModelIdx = Common::FindValueIndex(modelnames, state.model_name);
        int curFrameworkIdx = Common::FindValueIndex(frameworks, state.framework);
        int curAlgoIdx = Common::FindValueIndex(algorithms, state.algo_name);
        
        assert(curAlgoIdx != -1 && curFrameworkIdx != -1 && curAlgoIdx != -1);

        return ResponseJsonBuilder::CreateInitResponse(modelnames, frameworks, algorithms,
                    curModelIdx, curFrameworkIdx,  curAlgoIdx);
    } 
} // namespace Networks


