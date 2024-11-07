#include "Inference/SupportedFrameworks.h"



namespace Inference
{
    const std::unordered_map<std::string, FrameworkType> SupportedFrameworks::m_str2type = 
    {
        {"OpenVINO", FrameworkType::OpenVINO},
        {"ONNXRuntime", FrameworkType::ONNXRuntime}
    };
    
    bool SupportedFrameworks::IsValid(const std::string &framework_name)
    {
        return m_str2type.count(framework_name);
    }

    FrameworkType SupportedFrameworks::GetFrameworkType(const std::string &framework_name)
    {
        FrameworkType type = FrameworkType::FRAMEWORK_MAX;
        if(IsValid(framework_name)) {
            type = m_str2type.at(framework_name);
        }
        return type;
    }

    std::vector<std::string> SupportedFrameworks::GetAllFrameworks()
    {
        std::vector<std::string> result;
        for(const auto& iter : m_str2type) {
            result.emplace_back(iter.first);
        }
        return result;
    }

} // namespace Inference

