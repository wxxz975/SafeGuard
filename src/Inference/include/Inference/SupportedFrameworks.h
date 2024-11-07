#pragma once 

#include <cstdint>
#include <unordered_map>
#include <string>
#include <vector>

namespace Inference
{

    enum class FrameworkType: uint32_t 
    {
        OpenVINO = 0,
        ONNXRuntime,
        FRAMEWORK_MAX
    };


    class SupportedFrameworks
    {
    public:
        static bool IsValid(const std::string& framework_name);
        static FrameworkType GetFrameworkType(const std::string& framework_name);
        static std::vector<std::string> GetAllFrameworks();
    private:
        const static std::unordered_map<std::string, FrameworkType> m_str2type;

    private:
        SupportedFrameworks() = delete;
        ~SupportedFrameworks() = delete;
    };
    
   
    
    
} // namespace Inference
