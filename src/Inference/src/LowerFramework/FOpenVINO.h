#pragma once

#include <unordered_map>
#include <openvino/openvino.hpp>
#include "Inference/Base/Shape.h"
#include "FrameworkImpl.h"

namespace Inference
{
    namespace LowerFramework
    {
        class FOpenVINO: public FrameworkImpl
        {
        public:
            FOpenVINO();
            ~FOpenVINO() = default;

            virtual bool Initialize(const std::string& model_path) override;

            virtual std::vector<Base::TensorPtr> Infer(const std::vector<Base::TensorPtr>& input) override;
            
            virtual std::shared_ptr<Base::ModelMetadata> ParseModel(const std::string& model_path = "") override;

        private:
            static void MapType();


            ov::Tensor CreateTensor(Base::TensorPtr tensor);
            
            std::vector<ov::Tensor> CreateTensor(const std::vector<Base::TensorPtr>& tensors);


            Base::Type_t ConvertType(ov::element::Type_t type);
            ov::element::Type_t ConvertType(Base::Type_t type);

            ov::Shape ConvertShape(const Base::Shape& shape);
            Base::Shape ConvertShape(const ov::Shape& shape);

            std::vector<Base::TensorPtr> ParseOutput();

        private:
            std::shared_ptr<ov::Model> m_ov_model;
            ov::CompiledModel m_ov_compiled_model;
            ov::InferRequest m_ov_infer_request;

            std::shared_ptr<Base::ModelMetadata> m_metadata;
        
            static std::unordered_map<Base::Type_t, ov::element::Type_t> m_type2ovType;
            static std::unordered_map<ov::element::Type_t, Base::Type_t> m_ovType2type;
        };
        
    } // namespace LowerFramework
    
    
} // namespace Inference
