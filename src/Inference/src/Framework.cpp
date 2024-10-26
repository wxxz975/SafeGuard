#include "Inference/Framework.h"
#include "FrameworkImpl.h"


namespace Inference
{
    bool Framework::Initialize(const std::string &model_path)
    {
        return m_impl->Initialize(model_path);
    }

    std::vector<Base::TensorPtr> Framework::Infer(const std::vector<Base::TensorPtr> &input)
    {
        return m_impl->Infer(input);
    }

    std::shared_ptr<Base::ModelMetadata> Framework::ParseModel(const std::string &model_path)
    {
        return m_impl->ParseModel(model_path);
    }

} // namespace Inference
