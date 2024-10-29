#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "Inference/PrePostProcessor.h"
#include "PrePostProcessorImpl.h"

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
        private:
            const static std::unordered_map<std::string, AlgorithmsType> m_str2type; 
        };
        
        
        
    } // namespace Algorithms
    
    
} // namespace Inference
