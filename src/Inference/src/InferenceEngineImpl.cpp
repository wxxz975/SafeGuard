#include "InferenceEngineImpl.h"


namespace Inference
{
    bool InferenceEngine::InferenceEngineImpl::Initialize(std::unique_ptr<PrePostProcessor> prepos, 
        std::unique_ptr<Framework> framework,
        std::shared_ptr<Base::ModelMetadata> metadata, 
        size_t threadNum)
    {
        m_prepos = std::move(prepos);
        m_framework = std::move(framework);
        m_metadata = metadata;
        m_threadNum = threadNum; assert(m_threadNum > 0);
        
        if(m_threadNum) {
            m_thread_pool =  std::make_unique<Common::ThreadPool>(m_threadNum);
        }

        return m_prepos != nullptr && m_framework != nullptr;
    }

    InferenceEngine::OutputBoxes InferenceEngine::InferenceEngineImpl::Infer(const std::string &img_path)
    {
        cv::Mat img = cv::imread(img_path);
        
        return Infer(img);
    }

    InferenceEngine::OutputBoxes InferenceEngine::InferenceEngineImpl::Infer(const cv::Mat &img)
    {
        // fixme: confidence threshold, iou threshold
        InferenceContextPtr ctx = std::make_shared<InferenceContext>();
        auto inputs = m_prepos->Preprocessing(img, ctx);
        auto outputs = m_framework->Infer(inputs);
        auto boxes = m_prepos->Postprocessing(outputs, ctx);

        return boxes;
    }

    void InferenceEngine::InferenceEngineImpl::InferAsyn(const std::string &img_path, const AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img_path);
                callback(output);
            }
        );
    }

    void InferenceEngine::InferenceEngineImpl::InferAsyn(const cv::Mat &img, const AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img);
                callback(output);
            }
        );
    }

} // namespace Inference
