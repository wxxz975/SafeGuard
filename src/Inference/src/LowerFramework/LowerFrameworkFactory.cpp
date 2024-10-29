#include "Inference/LowerFramework/LowerFrameworkFactory.h"

#include <cassert>

#include "Inference/LowerFramework/FONNXRuntime.h"
#include "Inference/LowerFramework/FOpenVINO.h"


namespace Inference
{

    namespace LowerFramework
    {

        const std::unordered_map<std::string, FrameworkType> LowerFrameworkFactory::m_str2type = 
        {
            {"OpenVINO", FrameworkType::OpenVINO},
            {"ONNXRuntime", FrameworkType::ONNXRuntime}
        };
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
            if(m_str2type.count(framework)) {
                FrameworkType type = m_str2type.at(framework);
                return CreateFramework(type);
            }

            return nullptr;
        }
        
    } // namespace LowerFramework
} // namespace Inference


