#pragma once
#include <string>
#include <vector>
#include <unordered_map>


namespace SafeGuard
{
    // only onnx model
    class ModelSourceManager
    {
    public:
        ModelSourceManager() = default;
        ~ModelSourceManager() = default;

        // path or dir 
        bool Initialize(const std::string& model_dir);

        std::string GetModelPath(const std::string& model_name) const;

        std::vector<std::string> GetAllModelNames() const;


    private:
        // model name , model path
        std::unordered_map<std::string, std::string> m_filename2path;
    };
    
    
    
    
} // namespace SafeGuard
