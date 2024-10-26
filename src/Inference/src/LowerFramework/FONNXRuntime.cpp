#include "Inference/LowerFramework/FONNXRuntime.h"

#include "Common/Utils.h"

namespace Inference
{
    namespace LowerFramework
    {

        std::unordered_map<Inference::Base::Type_t, ONNXTensorElementDataType> 
            FONNXRuntime::m_type2ortType = 
            {
                {Base::Type_t::u8, ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8},
                {Base::Type_t::f32, ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT},
                {Base::Type_t::i32, ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32},
                {Base::Type_t::i64, ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64}
            };
        std::unordered_map<ONNXTensorElementDataType, Inference::Base::Type_t> FONNXRuntime::m_ortType2type;


        FONNXRuntime::FONNXRuntime()
        {
            MapType();
        }

        bool FONNXRuntime::Initialize(const std::string &model_path)
        {
            try
            {
                m_env_name = model_path;
                m_env_namew = std::wstring(m_env_name.begin(), m_env_name.end());
                Ort::SessionOptions ort_session_opt;

                m_ort_env = std::make_shared<Ort::Env>(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, m_env_name.c_str());

                ort_session_opt.SetIntraOpNumThreads(0);
                ort_session_opt.SetGraphOptimizationLevel(ORT_ENABLE_BASIC);
            
                if (IsGPUAvailable()) {
                    OrtCUDAProviderOptions cudaOption{};
                    ort_session_opt.AppendExecutionProvider_CUDA(cudaOption);
                }

            #ifdef _WIN32
                m_ort_session = std::make_shared<Ort::Session>(*m_ort_env, m_env_namew.c_str(), ort_session_opt);
            #else
                m_ort_session = std::make_shared<Ort::Session>(*m_ort_env, m_env_name.c_str(), ort_session_opt);
            #endif
            }
            catch(const std::exception& e)
            {
                // Common::zlog("Failed Init ONNXRuntime:%s\n", e.what());
                return false;
            }

            return true;
        }

        std::vector<Base::TensorPtr> FONNXRuntime::Infer(const std::vector<Base::TensorPtr> &input)
        {
            m_metadata->inputs;
            auto input_names = GetInputNames();
            auto output_names = GetOutputNames();

            auto tensors = CreateTensor(input);
            
            auto output = m_ort_session->Run(
                    Ort::RunOptions{ nullptr },
                    input_names.data(),
                    tensors.data(),
                    tensors.size(),
                    output_names.data(),
                    output_names.size()
                );

            return ParseOutput(output);    
        }

        std::shared_ptr<Base::ModelMetadata> FONNXRuntime::ParseModel(const std::string &model_path)
        {
            Ort::AllocatorWithDefaultOptions allocator;
            m_metadata = std::make_shared<Base::ModelMetadata>();
            auto inputCnt = m_ort_session->GetInputCount();
            auto outputCnt = m_ort_session->GetOutputCount();

            auto GetIOInfo = [&](const std::string& name, const Ort::TypeInfo& typeInfo, std::vector<Base::IOInfo>& result) {
                auto typeAndShape = typeInfo.GetTensorTypeAndShapeInfo();
                auto shape = typeAndShape.GetShape();
                auto type = typeAndShape.GetElementType();
                result.emplace_back(std::move(name), 
                    ConvertType(type), 
                    Common::VecToVec<uint64_t, std::vector<int64_t>>(shape));
            };

            for(std::size_t idx = 0; idx < inputCnt; ++idx) {
                auto name = m_ort_session->GetInputNameAllocated(idx, allocator);
                auto TypeInfo = m_ort_session->GetInputTypeInfo(idx);
                GetIOInfo(name.get(), TypeInfo, m_metadata->inputs);
            }
            for(std::size_t idx = 0; idx < outputCnt; ++idx) {
                auto name = m_ort_session->GetOutputNameAllocated(idx, allocator);
                auto TypeInfo = m_ort_session->GetOutputTypeInfo(idx);
                GetIOInfo(name.get(), TypeInfo, m_metadata->outputs);
            }

            // find labels 
            auto ort_metaData = m_ort_session->GetModelMetadata();
            auto keys = ort_metaData.GetCustomMetadataMapKeysAllocated(allocator);
            const std::string label_name = "names";
            for(const auto& key : keys) {
                if (label_name != key.get())
				    continue;

                auto labelsRaw = ort_metaData.LookupCustomMetadataMapAllocated(label_name.c_str(), allocator);
                std::string rawjson = std::string(labelsRaw.get());
                m_metadata->labels = Common::ParseJsonRaw(rawjson);
			    break;
            }

            return m_metadata;     
        }

        std::vector<Ort::Value> FONNXRuntime::CreateTensor(const std::vector<Base::TensorPtr> &tensors)
        {
            std::vector<Ort::Value> result;
            for(auto& tensor : tensors) {
                result.emplace_back(CreateTensor(tensor));
            }

            return result;
        }

        Ort::Value FONNXRuntime::CreateTensor(Base::TensorPtr tensor)
        {
            auto allocator = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);
            std::vector<std::int64_t> shape = Common::VecToVec<int64_t, Base::Shape>(tensor->GetShape());
            
            return Ort::Value::CreateTensor(allocator, 
                    tensor->Ptr<void>(), tensor->GetByteSize(), 
                    shape.data(), shape.size(),
                    ConvertType(tensor->GetElementType().Type())
                );
        }
        bool FONNXRuntime::IsGPUAvailable()
        {
            std::vector<std::string> availableProviders = Ort::GetAvailableProviders();
            auto cudaAvailable = std::find(availableProviders.begin(), availableProviders.end(),
                "CUDAExecutionProvider");

            return cudaAvailable != availableProviders.end();
        }
        Base::Type_t FONNXRuntime::ConvertType(ONNXTensorElementDataType type)
        {
            return m_ortType2type[type];
        }
        ONNXTensorElementDataType FONNXRuntime::ConvertType(Base::Type_t type)
        {
            return m_type2ortType[type];
        }
        void FONNXRuntime::MapType()
        {
            for(auto type : m_type2ortType) {
                m_ortType2type.emplace(type.second, type.first);
            }
        }
        std::vector<const char *> FONNXRuntime::GetInputNames()
        {
            std::vector<const char*> result;
            for(auto& dim : m_metadata->inputs) {
                result.push_back(dim.name.c_str());
            }
            return result;
        }
        std::vector<const char *> FONNXRuntime::GetOutputNames()
        {
            std::vector<const char*> result;
            for(auto& dim : m_metadata->outputs) {
                result.push_back(dim.name.c_str());
            }
            return result;
        }
        std::vector<Base::TensorPtr> FONNXRuntime::ParseOutput(const std::vector<Ort::Value> &output_tensor)
        {
            std::vector<Base::TensorPtr> result;
            
            for(std::size_t idx = 0; idx < m_metadata->outputs.size(); ++idx) {
                const auto& value = output_tensor[idx];
                auto begin = value.GetTensorData<std::uint8_t>();
                auto typeAndShape = value.GetTensorTypeAndShapeInfo();
                auto ele_type = ConvertType(typeAndShape.GetElementType());
                auto ele_shape = Common::VecToVec<size_t, std::vector<std::int64_t>>(typeAndShape.GetShape());
                auto ele_count = typeAndShape.GetElementCount();
                auto ele_size = Base::ElementType(ele_type).Size(); 

                std::vector<std::uint8_t> data = std::vector<std::uint8_t>(
                    begin,
                    begin + ele_count * ele_size
                );


                Base::TensorPtr tensor = std::make_shared<Base::Tensor>(
                    ele_shape,
                    ele_type,
                    std::move(data)
                );
                
                result.push_back(tensor);
            }

            return result;
        }
    } // namespace LowerFramework

} // namespace Inference
