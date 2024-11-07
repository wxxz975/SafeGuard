#pragma once
#include <memory>
#include <string>


#include "PrePostProcessorImpl.h"
#include "Inference/SupportedModels.h"

namespace Inference
{
    namespace Algorithms
    {
        class AlgorithmsFactory
        {
        public:
            AlgorithmsFactory() = delete;
            ~AlgorithmsFactory() = delete;

            // TODO: fixme, ignore the case
            static std::unique_ptr<PrePostProcessorImpl> CreateAlgorithm(AlgorithmsType type);
            
            static std::unique_ptr<PrePostProcessorImpl> CreateAlgorithm(const std::string& type);
        };
        
        
        
    } // namespace Algorithms
    
    
} // namespace Inference
