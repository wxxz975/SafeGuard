#include "Inference/InferenceEngine.h"



namespace Inference
{
    bool InferenceEngine::Initialize(const std::string& model_path, const std::string& algo_type, const std::string& infer_framework, size_t threadNum)
    {
        m_impl = std::make_unique<InferenceEngineImpl>();
        return m_impl->Initialize(model_path, algo_type, infer_framework, threadNum);
    }

    std::vector<Base::BoundingBox> InferenceEngine::Infer(const std::string &img_path)
    {
        return m_impl->Infer(img_path);
    }
    std::vector<Base::BoundingBox> InferenceEngine::Infer(const cv::Mat &img)
    {
        return m_impl->Infer(img);
    }
    void InferenceEngine::InferAsyn(const std::string &img_path, const Base::AsynInferCallback &callback)
    {
        return m_impl->InferAsyn(img_path, callback);
    }
    void InferenceEngine::InferAsyn(const cv::Mat &img, const Base::AsynInferCallback &callback)
    {
        return m_impl->InferAsyn(img, callback);
    }
    cv::Mat InferenceEngine::RenderBoxes(const std::string &img_path, const Base::OutputBoxes& boxes)
    {
        return m_impl->RenderBoxes(img_path, boxes);
    }

    const std::vector<std::string> &InferenceEngine::GetLabels() const
    {
        return m_impl->GetLabels();
    }
} // namespace Inference


