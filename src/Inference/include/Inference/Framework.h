#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Base/Tensor.h"
#include "Base/ModelMetadata.h"
#include "FrameworkImpl.h"

namespace Inference
{

    enum class FrameworkType: uint32_t 
    {
        OpenVINO = 0,
        ONNXRuntime,
        FRAMEWORK_MAX
    };

    class FrameworkImpl;
    class Framework
    {  
    private:
        std::unique_ptr<FrameworkImpl> m_impl;
    public:
        Framework(std::unique_ptr<FrameworkImpl> impl);
        ~Framework() = default;

        /// @brief 
        /// @param model_path 
        /// @return 
        bool Initialize(const std::string& model_path);


        /// @brief 
        /// @param input 输入是由预处理之后返回的值 
        /// @return 返回的是由原生的框架输出，并且解析标准后的数据，方便后续的处理
        std::vector<Base::TensorPtr> Infer(const std::vector<Base::TensorPtr>& inputs);
        

        /// @brief 解析模型，并且返回获取到的数据结构
        /// @param model_path 模型的路径
        /// @return 
        std::shared_ptr<Base::ModelMetadata> ParseModel(const std::string& model_path = "");
    };
    
    
    

} // namespace Inference
