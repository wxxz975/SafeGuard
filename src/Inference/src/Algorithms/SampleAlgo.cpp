#include "Inference/Algorithms/SampleAlgo.h"
#include "Inference/Base/ModelMetadata.h"

#include "Common/Logger.h"
#include "Common/Utils.h"
#include "ImageOps.h"

namespace Inference
{
    namespace Algorithms
    {
        bool SampleAlgo::Initialize(std::shared_ptr<Base::ModelMetadata> metadata)
        {
            m_metadata = metadata;
            
            if(!CheckIOShape()) {
                Common::logError("Error on Input and output shapes do not match\n");
                return false;
            }

            return true;
        }

        cv::Mat SampleAlgo::RenderBoxes(const std::vector<Base::BoundingBox> &boxes, const std::string &image_path)
        {
            const auto&labels =  m_metadata ? m_metadata->labels : std::vector<std::string>();
            return RenderBoundingBoxes(image_path, boxes, labels);
        }

        bool SampleAlgo::CheckIOShape()
        {
            using namespace Common;
            using namespace Base;
            using IOShape = std::vector<std::vector<std::uint64_t>>;
            
            assert(m_theoryInShape.size() == m_InShapeMask.size());
            assert(m_theoryOutShape.size() == m_OutShapeMask.size());

            auto CheckIO = [&](const IOShape & shapes1,  const std::vector<IOInfo>& shapes2, const std::vector<std::string>& masks) 
                -> bool {
                for(int idx = 0; idx < shapes1.size(); ++idx) {
                    const auto& shape = shapes1[idx];
                    const auto& mask = masks[idx];
                    const auto& model_shape = shapes2.at(idx).shape;;
                    if(!CompareVecWithMask(mask, shape, model_shape)) {
                        auto shape1 = VecToStr(shape);
                        auto shape2 = VecToStr(model_shape);
                        // Common::zlog("Shape:%s imcompatiable with:%s\n", shape1.c_str(), shape2.c_str());
                        return false;
                    }
                        
                }
                return true;
            };

            return  CheckIO(m_theoryInShape, m_metadata->inputs, m_InShapeMask) &&
                     CheckIO(m_theoryOutShape, m_metadata->outputs, m_OutShapeMask);
                     
        }

    } // namespace Algorithms
    
    
} // namespace Inference
