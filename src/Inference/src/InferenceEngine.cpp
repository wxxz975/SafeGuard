#include "Inference/InferenceEngine.h"

#include "InferenceEngineImpl.h"


namespace Inference
{
    std::vector<Base::BoundingBox> InferenceEngine::Infer(const std::string &img_path)
    {
        return m_impl->Infer(img_path);
    }
    std::vector<Base::BoundingBox> InferenceEngine::Infer(const cv::Mat &img)
    {
        return m_impl->Infer(img);
    }
    void InferenceEngine::InferAsyn(const std::string &img_path, const AsynInferCallback &callback)
    {
        return m_impl->InferAsyn(img_path, callback);
    }
    void InferenceEngine::InferAsyn(const cv::Mat &img, const AsynInferCallback &callback)
    {
        return m_impl->InferAsyn(img, callback);
    }
} // namespace Inference
