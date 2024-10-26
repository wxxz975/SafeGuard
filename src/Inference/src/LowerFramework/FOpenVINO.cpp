#include "Inference/LowerFramework/FOpenVINO.h"
#include "Common/Utils.h"
#include "Inference/Base/ModelMetadata.h"

namespace Inference
{
    namespace LowerFramework
    {
        
        std::unordered_map<Base::Type_t, ov::element::Type_t> FOpenVINO::m_type2ovType = 
        {
            {Base::Type_t::u8, ov::element::u8},
            {Base::Type_t::f32, ov::element::f32},
            {Base::Type_t::i32, ov::element::i32},
            {Base::Type_t::i64, ov::element::i64}
        };
        std::unordered_map<ov::element::Type_t, Base::Type_t> FOpenVINO::m_ovType2type;

        FOpenVINO::FOpenVINO()
        {
            MapType();
        }

        bool FOpenVINO::Initialize(const std::string &model_path)
        {
            try
            {
                ov::Core ov_core;
                m_ov_model = ov_core.read_model(model_path);
                m_ov_compiled_model = ov_core.compile_model(m_ov_model, "AUTO");
                m_ov_infer_request = m_ov_compiled_model.create_infer_request();
                return true;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return false;
            }
            return true;
        }

        std::vector<Base::TensorPtr> FOpenVINO::Infer(const std::vector<Base::TensorPtr> &input)
        {
            auto input_tensor = CreateTensor(input);
            m_ov_infer_request.set_input_tensors(input_tensor);
            m_ov_infer_request.infer();

            return ParseOutput();
        }

        std::shared_ptr<Base::ModelMetadata> FOpenVINO::ParseModel(const std::string &model_path)
        {
            m_metadata = std::make_shared<Base::ModelMetadata>();

            std::shared_ptr<ov::Model> model;
            if(!model_path.empty()) {
                ov::Core ov_core;
                model = ov_core.read_model(model_path);
            }
            else model = m_ov_model;
            
            
            // 获取 shape type, name
            auto inputs = model->inputs();
            auto outputs = model->outputs();
            auto getIOInfo = [&](const ov::OutputVector& nodes) -> std::vector<Base::IOInfo> {
                std::vector<Base::IOInfo> result;
                for(const auto& node : nodes)
                {   
                    auto name = node.get_any_name();
                    ov::element::Type_t ov_ele_type = node.get_element_type();
                    ov::Shape ov_shape = node.get_shape();
                    result.emplace_back(name, ConvertType(ov_ele_type), Common::VecToVec<uint64_t, ov::Shape>(ov_shape));
                }

                return result;
            };
            m_metadata->inputs = getIOInfo(inputs);
            m_metadata->outputs = getIOInfo(outputs);


            /// 获取这个标签
            std::vector<std::string> labels;
            auto rtInfo = model->get_rt_info();
            if(rtInfo.count("framework")) {
                auto framework = rtInfo["framework"].as<ov::AnyMap>();
                if(framework.count("names")) {
                    auto names = framework["names"].as<ov::AnyMap>();
                    for(auto iter : names) {
                        labels.emplace_back(iter.second.as<std::string>());
                    }
                }
            }
            m_metadata->labels = std::move(labels);


            return m_metadata;
        }

        void FOpenVINO::MapType()
        {
            for(auto type : m_type2ovType) {
                m_ovType2type.emplace(type.second, type.first);
            }
        }
        ov::Tensor FOpenVINO::CreateTensor(Base::TensorPtr tensor)
        {
            return  ov::Tensor(
                        ConvertType(tensor->GetElementType().Type()),
                        tensor->GetShape(), // 1, 3, 640, 640
                        tensor->Ptr<void*>()
            );
        }
        std::vector<ov::Tensor> FOpenVINO::CreateTensor(const std::vector<Base::TensorPtr> &tensors)
        {
            std::vector<ov::Tensor> result;
            for(const auto& tensor : tensors) {
                result.emplace_back(CreateTensor(tensor));
            }
        }
        Base::Type_t FOpenVINO::ConvertType(ov::element::Type_t type)
        {
            return m_ovType2type[type];
        }

        ov::element::Type_t FOpenVINO::ConvertType(Base::Type_t type)
        {
            return m_type2ovType[type];
        }

        ov::Shape FOpenVINO::ConvertShape(const Base::Shape &shape)
        {
            return shape;
        }

        Base::Shape FOpenVINO::ConvertShape(const ov::Shape& shape)
        {
            return Base::Shape(shape.begin(), shape.end());
        }
        std::vector<Base::TensorPtr> FOpenVINO::ParseOutput()
        {
            std::vector<Base::TensorPtr> result;
            for(int idx = 0; idx < m_metadata->outputs.size(); ++idx) {
                auto output_tensor = m_ov_infer_request.get_output_tensor(idx);
                auto ele_type = ConvertType(output_tensor.get_element_type());
                auto ele_shape = Common::VecToVec<size_t, ov::Shape>(output_tensor.get_shape());
                auto byte_count = output_tensor.get_byte_size();

                auto begin = reinterpret_cast<std::uint8_t*>(output_tensor.data());
                std::vector<std::uint8_t> data(begin, begin + byte_count);                

                Base::TensorPtr tensor = std::make_shared<Base::Tensor>(
                    ele_shape,
                    ele_type,
                    std::move(data)
                );

                result.push_back(
                    tensor
                );
            }
            return result;
        }
    } // namespace LowerFramework

} // namespace Inference
