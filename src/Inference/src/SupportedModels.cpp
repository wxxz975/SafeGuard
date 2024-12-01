#include "Inference/SupportedModels.h"


namespace Inference
{
    const std::unordered_map<std::string, AlgorithmsType> SupportedModels::m_str2type = 
    {
        {"YOLOv3", AlgorithmsType::YOLOv3},
        {"YOLOv5", AlgorithmsType::YOLOv5},
        {"YOLOv8", AlgorithmsType::YOLOv8},
        {"YOLOv9", AlgorithmsType::YOLOv9},
        {"YOLOv10", AlgorithmsType::YOLOv10},
        {"YOLOv11", AlgorithmsType::YOLOv11},
        {"RTDetr", AlgorithmsType::RTDetr}
    };
    

    bool SupportedModels::IsValid(const std::string& model_name)
    {
        return m_str2type.count(model_name);
    };
        
    AlgorithmsType SupportedModels::GetModelType(const std::string& model_name)
    {
        AlgorithmsType type = AlgorithmsType::ALGO_MAX;
        if(IsValid(model_name)) {
            type = m_str2type.at(model_name);
        }
        return type;
    };

    std::vector<std::string> SupportedModels::GetAllAlgorithms()
    {
        std::vector<std::string> result;
        for(const auto& iter : m_str2type) {
            result.emplace_back(iter.first);
        }
        return result;
    }

} // namespace Inference
