#pragma once
#include <unordered_map>
#include "FrameworkImpl.h"

#include <onnxruntime_cxx_api.h>

namespace Inference
{
    namespace LowerFramework
    {
        class FONNXRuntime: public FrameworkImpl
        {
        public:
            FONNXRuntime();
            ~FONNXRuntime() = default;

            virtual bool Initialize(const std::string& model_path) override;

            virtual std::vector<Base::TensorPtr> Infer(const std::vector<Base::TensorPtr>& input) override;
            
            virtual std::shared_ptr<Base::ModelMetadata> ParseModel(const std::string& model_path = "") override;

        private:
            std::vector<Ort::Value> CreateTensor(const std::vector<Base::TensorPtr>& tensors);

            Ort::Value CreateTensor(Base::TensorPtr tensor);

            bool IsGPUAvailable();

            Base::Type_t ConvertType(ONNXTensorElementDataType type);

            ONNXTensorElementDataType ConvertType(Base::Type_t type);

            Base::Shape ConvertShape(const std::vector<std::int64_t>& shape);

            static void MapType();

            std::vector<const char*> GetInputNames();
            std::vector<const char*> GetOutputNames();

            std::vector<Base::TensorPtr> ParseOutput(const std::vector<Ort::Value>& output_tensor);


        private:
        
            std::shared_ptr<Ort::Session> m_ort_session;
            std::shared_ptr<Ort::Env> m_ort_env;

            std::string m_env_name;
            std::wstring m_env_namew;
            

            std::shared_ptr<Base::ModelMetadata> m_metadata;

            static std::unordered_map<Base::Type_t, ONNXTensorElementDataType> m_type2ortType;
            static std::unordered_map<ONNXTensorElementDataType, Base::Type_t> m_ortType2type;
        };

    } // namespace LowerFramework
    
    
} // namespace Inference
