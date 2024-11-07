#include "LowerFramework/LowerFrameworkFactory.h"

#include <cassert>

#include "LowerFramework/FONNXRuntime.h"
#include "LowerFramework/FOpenVINO.h"


namespace Inference
{

    namespace LowerFramework
    {
        std::unique_ptr<FrameworkImpl> LowerFrameworkFactory::CreateFramework(FrameworkType framework)
        {
            switch (framework)
            {
            case FrameworkType::OpenVINO: return std::make_unique<FOpenVINO>();
            case FrameworkType::ONNXRuntime: return std::make_unique<FONNXRuntime>();
            default:  {
                assert(0 && "UNKNOWN Framework Type");
                return nullptr;
            }
            }
        }

        std::unique_ptr<FrameworkImpl> LowerFrameworkFactory::CreateFramework(const std::string &framework)
        {
            if(SupportedFrameworks::IsValid(framework)) {
                FrameworkType type = SupportedFrameworks::GetFrameworkType(framework);
                return CreateFramework(type);
            }

            return nullptr;
        }
        
    } // namespace LowerFramework
} // namespace Inference


