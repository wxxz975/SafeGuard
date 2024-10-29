#pragma once
#include "Inference/Framework.h"

namespace Inference
{
    class FrameworkImpl
    {
    public:
        FrameworkImpl() = default;
        virtual ~FrameworkImpl() = default;

        virtual bool Initialize(const std::string& model_path) = 0;

        /// @brief 
        /// @param input 输入是由预处理之后返回的值 
        /// @return 返回的是由原生的框架输出，并且解析标准后的数据，方便后续的处理
        virtual std::vector<Base::TensorPtr> Infer(const std::vector<Base::TensorPtr>& input) = 0;


        /// @brief 解析模型，并且返回获取到的数据结构
        /// @param model_path 模型的路径
        /// @return 
        virtual std::shared_ptr<Base::ModelMetadata> ParseModel(const std::string& model_path = "") = 0;
    };
    
} // namespace Inference
