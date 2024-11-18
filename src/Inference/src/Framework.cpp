#include "Framework.h"


namespace Inference
{
    Framework::Framework(std::unique_ptr<FrameworkImpl> impl)
        :m_impl(std::move(impl))
    {

    }

    bool Framework::Initialize(const std::string &model_path)
    {
        if(m_impl->Initialize(model_path)) {
            m_impl->SetMetadata(m_impl->ParseModel());
            return true;
        }
        return false;
    }

    std::vector<Base::TensorPtr> Framework::Infer(const std::vector<Base::TensorPtr> &input)
    {
        return m_impl->Infer(input);
    }

    std::shared_ptr<Base::ModelMetadata> Framework::ParseModel(const std::string &model_path)
    {
        return m_impl->ParseModel(model_path);
    }

    std::shared_ptr<Base::ModelMetadata> Framework::GetMetadata()
    {
        return m_impl->GetMetadata();
    }

} // namespace Inference
