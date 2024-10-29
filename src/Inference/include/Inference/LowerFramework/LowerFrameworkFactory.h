#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "Inference/Framework.h"

#include "FrameworkImpl.h"

namespace Inference
{
    namespace LowerFramework
    {
        class LowerFrameworkFactory
        {
        public:
            LowerFrameworkFactory() = delete;
            ~LowerFrameworkFactory() = delete;

            static std::unique_ptr<FrameworkImpl> CreateFramework(FrameworkType framework);

            static std::unique_ptr<FrameworkImpl> CreateFramework(const std::string& framework);

        private:
            const static std::unordered_map<std::string, FrameworkType> m_str2type;
        };
        
    } // namespace LowerFramework
    
    
} // namespace Inference
