#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Inference/Base/Tensor.h"
#include "Inference/Base/ModelMetadata.h"
#include "FrameworkImpl.h"

namespace Inference
{

    
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

        std::shared_ptr<Base::ModelMetadata> GetMetadata();
    };
    
    
    

} // namespace Inference
