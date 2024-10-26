#include "Inference/Base/Shape.h"


namespace Inference
{
    namespace Base
    {
        Shape::Shape(std::initializer_list<size_t> init)
		    :std::vector<size_t>(init)
        {

        }
        std::string Shape::to_string() const {
            std::string result = "Shape: ";
            for (const auto& dim : *this) {
                result += std::to_string(dim) + " ";
            }
            return result;
        };
    } // namespace Base
    
} // namespace Inference
