#include "Algorithms/AlgorithmsFactory.h"

#include "Algorithms/YOLOv3.h"
#include "Algorithms/YOLOv5.h"
#include "Algorithms/YOLOv8.h"
#include "Algorithms/YOLOv9.h"
#include "Algorithms/YOLOv10.h"
#include "Algorithms/YOLOv11.h"
#include "Algorithms/RTDetr.h"

#include <cassert>

namespace Inference
{
    namespace Algorithms
    {
        std::unique_ptr<PrePostProcessorImpl> AlgorithmsFactory::CreateAlgorithm(AlgorithmsType type)
        {
            switch (type)
            {
            case AlgorithmsType::YOLOv5: return std::make_unique<YOLOv5>();
            case AlgorithmsType::YOLOv8: return std::make_unique<YOLOv8>();
            case AlgorithmsType::YOLOv3: return std::make_unique<YOLOv3>();
            case AlgorithmsType::YOLOv9: return std::make_unique<YOLOv9>();
            case AlgorithmsType::YOLOv10: return std::make_unique<YOLOv10>();
            case AlgorithmsType::YOLOv11: return std::make_unique<YOLOv11>();
            case AlgorithmsType::RTDetr: return std::make_unique<RTDetr>();
            default: {
                assert(0 && "Unknown algorithms!");
                return nullptr;
            }
            }
        }

        std::unique_ptr<PrePostProcessorImpl> AlgorithmsFactory::CreateAlgorithm(const std::string &type)
        {
            if(SupportedModels::IsValid(type)) {
                AlgorithmsType algo = SupportedModels::GetModelType(type);
                return CreateAlgorithm(algo);
            }

            return nullptr;
        }

    } // namespace Algorithms

   

} // namespace Inference
