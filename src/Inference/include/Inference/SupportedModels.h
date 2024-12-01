#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>

namespace Inference
{
    enum class AlgorithmsType: uint32_t
    {
        YOLOv3 = 0,
        YOLOv5,
        YOLOv8,
        YOLOv9,
        YOLOv10,
        YOLOv11,
        RTDetr,
        ALGO_MAX
    };

    class SupportedModels
    {
    public:
        static bool IsValid(const std::string& model_name);
        
        static AlgorithmsType GetModelType(const std::string& model_name);

        static std::vector<std::string> GetAllAlgorithms();

    private:
        const static std::unordered_map<std::string, AlgorithmsType> m_str2type; 
    private:
        SupportedModels() = delete;
        ~SupportedModels() = delete;
    };    
    
} // namespace Inference
