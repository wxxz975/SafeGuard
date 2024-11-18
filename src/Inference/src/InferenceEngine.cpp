#include "Inference/InferenceEngine.h"
#include "InferenceEngineImpl.h"

#include "Common/IFilesystem.h"

namespace Inference
{
    InferenceEngine::~InferenceEngine()
    {
        if(m_impl) {
            delete m_impl;
            m_impl = nullptr;
        }
    }
    const InferenceEngine::CurrentState& InferenceEngine::GetState() const
    {
        return m_state;
    }

    bool InferenceEngine::Initialize(const std::string &model_path, const std::string &algo_type, const std::string &infer_framework, size_t threadNum)
    {
        if(m_impl) delete m_impl;

        m_impl = new InferenceEngineImpl();
        
        if(m_impl->Initialize(model_path, algo_type, infer_framework, threadNum)) {
            m_state.model_name =  Common::IFilesystem::GetFilename(model_path);
            m_state.algo_name = algo_type;
            m_state.framework = infer_framework;
            m_state.async_threads = threadNum;
            m_state.initialized = true;
        }

        return m_state.initialized;
    }

    std::vector<Base::BoundingBox> InferenceEngine::Infer(const std::string &img_path)
    {
        assert(m_state.initialized);
        return m_impl->Infer(img_path);
    }
    std::vector<Base::BoundingBox> InferenceEngine::Infer(const cv::Mat &img)
    {
        assert(m_state.initialized);
        return m_impl->Infer(img);
    }
    void InferenceEngine::InferAsyn(const std::string &img_path, const Base::AsynInferCallback &callback)
    {
        assert(m_state.initialized);
        return m_impl->InferAsyn(img_path, callback);
    }
    // void InferenceEngine::InferAsyn(const cv::Mat &img, const Base::AsynInferCallback &callback)
    // {
    //     assert(m_initialized);
    //     return m_impl->InferAsyn(img, callback);
    // }
    void InferenceEngine::RenderBoxes(const std::string &img_path, const Base::OutputBoxes& boxes, const std::string& save_path)
    {
        assert(m_state.initialized);
        return m_impl->RenderBoxes(img_path, boxes, save_path);
    }

    void InferenceEngine::RenderBoxes(const cv::Mat &img, const Base::OutputBoxes &boxes, const std::string &save_path)
    {
        assert(m_state.initialized);
        cv::Mat rendered = m_impl->RenderBoxes(img, boxes);
        cv::imwrite(save_path, rendered);
    }
    std::shared_ptr<std::vector<std::string>> InferenceEngine::GetLabels() const
    {
        assert(m_state.initialized);
        return m_impl->GetLabels();
    }

    std::shared_ptr<Base::ModelMetadata> InferenceEngine::ParseModel(const std::string& path) const
    {
        return m_impl->ParseModel(path);
    }

    void InferenceEngine::SetConfidenceThreshold(float conf)
    {
        assert(m_state.initialized);
        m_impl->SetConfidenceThreshold(conf);
    }

    void InferenceEngine::SetIOUThreshold(float iou)
    {
        assert(m_state.initialized);
        m_impl->SetIOUThreshold(iou);
    }

    void InferenceEngine::SetGeneralCallback(const Base::AsynInferCallback &callback)
    {
        assert(m_state.initialized);
        m_impl->SetGeneralCallback(callback);
    }

} // namespace Inference

