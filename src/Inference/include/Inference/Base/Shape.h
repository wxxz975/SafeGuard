#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace Inference
{
    namespace Base
    {
        struct ImageSize {
            int width;
            int height;
            ImageSize(int width = 0, int height = 0)
                : width(width), height(height) 
                { }
        };

        class Shape: public std::vector<size_t>
        {
        public:
            Shape() = default;
            ~Shape() = default;

            Shape(std::initializer_list<size_t> init);

            template <class InputIterator>
            Shape(InputIterator first, InputIterator last) : std::vector<size_t>(first, last) {};


            std::string to_string() const;
        };

        std::ostream& operator<<(std::ostream& os, const Shape& shape) {
            os << shape.to_string();
            return os;
        }

    } // namespace Base
    

} // namespace Inference