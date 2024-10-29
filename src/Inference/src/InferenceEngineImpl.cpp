#include "InferenceEngineImpl.h"

#include "Inference/Algorithms/AlgorithmsFactory.h"
#include "Inference/LowerFramework/LowerFrameworkFactory.h"

#include "Common/Logger.h"

namespace Inference
{
    

    bool InferenceEngineImpl::Initialize(const std::string& model_path, 
        const std::string& algo_type, 
        const std::string& infer_framework, 
        size_t threadNum)
    {
        m_threadNum = threadNum;
        assert(m_threadNum > 0);

        if(m_threadNum) {
            m_thread_pool =  std::make_unique<Common::ThreadPool>(m_threadNum);
        }
        if(!CreateContext(model_path, algo_type, infer_framework) ) {
            Common::logError("Failed to Create Inference Context!");
            return false;
        }

        return true;
    }

    Base::OutputBoxes InferenceEngineImpl::Infer(const std::string &img_path)
    {
        cv::Mat img = cv::imread(img_path);
        
        return Infer(img);
    }

    Base::OutputBoxes InferenceEngineImpl::Infer(const cv::Mat &img)
    {
        // fixme: confidence threshold, iou threshold
        InferenceContextPtr ctx = std::make_shared<InferenceContext>();
        auto inputs = m_prepos->Preprocessing(img, ctx);
        auto outputs = m_framework->Infer(inputs);
        auto boxes = m_prepos->Postprocessing(outputs, ctx);

        return boxes;
    }

    void InferenceEngineImpl::InferAsyn(const std::string &img_path, const Base::AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img_path);
                callback(output);
            }
        );
    }

    void InferenceEngineImpl::InferAsyn(const cv::Mat &img, const Base::AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img);
                callback(output);
            }
        );
    }

    cv::Mat InferenceEngineImpl::RenderBoxes(const std::string &img_path, const Base::OutputBoxes& boxes)
    {
        return m_prepos->RenderBoxes(boxes, img_path);
    }

    const std::vector<std::string> &InferenceEngineImpl::GetLabels() const
    {
        if(m_metadata) {
            return m_metadata->labels;
        }
        return std::vector<std::string>();
    }

    bool InferenceEngineImpl::CreateContext(const std::string &model_path, const std::string &algo_type, const std::string &infer_framework)
    {
        using namespace Algorithms;
        using namespace LowerFramework;

        auto algo_impl = AlgorithmsFactory::CreateAlgorithm(algo_type);
        auto frameork_impl = LowerFrameworkFactory::CreateFramework(infer_framework);
        if(!algo_impl || !frameork_impl) {
            Common::logError("Failed to Create Algorithm or Framework. algo:%s, framework:%s", 
                algo_type.c_str(), infer_framework.c_str());
            return false;
        }

        m_prepos = std::make_unique<PrePostProcessor>(std::move(algo_impl));
        m_framework = std::make_unique<Framework>(std::move(frameork_impl));
        if(!m_prepos || !m_framework) {
            return false;
        }
        
        if(!m_framework->Initialize(model_path)) {
            Common::logError("Failed to initialize the framework!");
            return false;
        }

        m_metadata = m_framework->ParseModel(model_path);
        
        if(!m_prepos->Initialize(m_metadata)) {
            Common::logError("Failed to initialize the algo propostprocessor!");
            return false;
        }

        return true;
    };

} // namespace Inference
