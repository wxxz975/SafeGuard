#include "InferenceEngineImpl.h"

#include <opencv2/opencv.hpp>

#include "Algorithms/AlgorithmsFactory.h"
#include "LowerFramework/LowerFrameworkFactory.h"

#include "Common/Logger.h"
#include "Common/IFilesystem.h"

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
        
        auto boxes = Infer(img);
        
        return boxes;
    }

    Base::OutputBoxes InferenceEngineImpl::Infer(const cv::Mat &img)
    {
        InferenceContextPtr ctx = std::make_shared<InferenceContext>(m_iou_default, m_conf_default);
        auto inputs = m_prepos->Preprocessing(img, ctx);
        auto outputs = m_framework->Infer(inputs);
        auto boxes = m_prepos->Postprocessing(outputs, ctx);
        if(m_general_callback) m_general_callback(boxes);
        return boxes;
    }

    void InferenceEngineImpl::InferAsyn(const std::string &img_path, const Base::AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img_path);
            }
        );
    }

    void InferenceEngineImpl::InferAsyn(const cv::Mat &img, const Base::AsynInferCallback &callback)
    {
        m_thread_pool->enqueue(
            [&](){
                auto output = Infer(img);
            }
        );
    }

    cv::Mat InferenceEngineImpl::RenderBoxes(const cv::Mat &img, const Base::OutputBoxes &boxes)
    {
        return m_prepos->RenderBoxes(boxes, img);
    }

    cv::Mat InferenceEngineImpl::RenderBoxes(const std::string &img_path, const Base::OutputBoxes& boxes)
    {
        return m_prepos->RenderBoxes(boxes, img_path);
    }

    void InferenceEngineImpl::RenderBoxes(const std::string &img_path, const Base::OutputBoxes &boxes, const std::string &save_path)
    {
        using namespace Common::IFilesystem;
        cv::Mat rendered = RenderBoxes(img_path, boxes);
        
        std::string save_path_ = save_path.empty() ? 
            ConcatPath(GetParentPath(img_path), "rendered_"+ GetFilename(img_path)) : save_path;
        
        cv::imwrite(save_path_, rendered);
    }

    void InferenceEngineImpl::RenderBoxes(const cv::Mat &img, const Base::OutputBoxes &boxes, const std::string &save_path)
    {
        using namespace Common::IFilesystem;
        cv::Mat rendered = RenderBoxes(img, boxes);
        
        cv::imwrite(save_path, rendered);
    }

    const std::vector<std::string> &InferenceEngineImpl::GetLabels() const
    {
        if(m_metadata) {
            return m_metadata->labels;
        }
        return std::vector<std::string>();
    }

    void InferenceEngineImpl::SetIOUThreshold(float iou)
    {
        if(iou < 0 || iou > 1.f) {
            Common::logWarn("set invalid iou value:{}", iou);
            return ;
        }
        m_iou_default = iou;
    }

    void InferenceEngineImpl::SetConfidenceThreshold(float conf)
    {
        if(conf < 0 || conf > 1.f) {
            Common::logWarn("set invalid conf value:{}", conf);
            return ;
        }
        m_conf_default = conf;
    }

    void InferenceEngineImpl::SetGeneralCallback(const Base::AsynInferCallback &callback)
    {
        m_general_callback = callback;
    }

    bool InferenceEngineImpl::CreateContext(const std::string &model_path, const std::string &algo_type, const std::string &infer_framework)
    {
        using namespace Algorithms;
        using namespace LowerFramework;

        auto algo_impl = AlgorithmsFactory::CreateAlgorithm(algo_type);
        auto frameork_impl = LowerFrameworkFactory::CreateFramework(infer_framework);
        if(!algo_impl || !frameork_impl) {
            Common::logError("Failed to Create Algorithm or Framework. algo:{}, framework:{}", 
                algo_type, infer_framework);
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
    }
  

} // namespace Inference
