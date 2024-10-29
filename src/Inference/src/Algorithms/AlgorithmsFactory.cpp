#include "Inference/Algorithms/AlgorithmsFactory.h"

#include "Inference/Algorithms/YOLOv3.h"
#include "Inference/Algorithms/YOLOv5.h"
#include "Inference/Algorithms/YOLOv8.h"
#include "Inference/Algorithms/RTDetr.h"

#include <cassert>

namespace Inference
{
    namespace Algorithms
    {
        const std::unordered_map<std::string, AlgorithmsType> AlgorithmsFactory::m_str2type = 
        {
            {"YOLOv3", AlgorithmsType::YOLOv3},
            {"YOLOv5", AlgorithmsType::YOLOv5},
            {"YOLOv8", AlgorithmsType::YOLOv8},
            {"RTDetr", AlgorithmsType::RTDetr}
        };
        std::unique_ptr<PrePostProcessorImpl> AlgorithmsFactory::CreateAlgorithm(AlgorithmsType type)
        {
            switch (type)
            {
            case AlgorithmsType::YOLOv5: return std::make_unique<YOLOv5>();
            case AlgorithmsType::YOLOv8: return std::make_unique<YOLOv8>();
            case AlgorithmsType::YOLOv3: return std::make_unique<YOLOv3>();
            case AlgorithmsType::RTDetr: return std::make_unique<RTDetr>();
            default: {
                assert(0 && "Unknown algorithms!");
                return nullptr;
            }
            }
        }

        std::unique_ptr<PrePostProcessorImpl> AlgorithmsFactory::CreateAlgorithm(const std::string &type)
        {
            if(m_str2type.count(type)) {
                AlgorithmsType algo = m_str2type.at(type);
                return CreateAlgorithm(algo);
            }

            return nullptr;
        }

    } // namespace Algorithms

   

} // namespace Inference
