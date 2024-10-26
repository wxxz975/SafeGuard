#pragma once

#include <memory>

#include "Shape.h"
#include "ElementType.h"

namespace Inference
{
    namespace Base
    {
        
        class Tensor: public std::enable_shared_from_this<Tensor>
        {
        public:
            Tensor(const Shape& shape, ElementType type, void* ptr = nullptr);
            Tensor(const Shape& shape, ElementType type, std::vector<uint8_t>&& data);
            ~Tensor();

            /// <summary>
            /// Returns the total number of elements
            /// </summary>
            /// <returns></returns>
            size_t GetSize();

            /// <summary>
            /// Returns the size of the current Tensor in bytes.
            /// </summary>
            /// <returns></returns>
            size_t GetByteSize();
            

            /// @brief create tensor`s interface
            /// @param shape 
            /// @param type 
            /// @param ptr 
            /// @return 
            static Tensor CreateTensor(const Shape& shape, ElementType type, void* ptr);


            /// <summary>
            /// return the raw ptr
            /// </summary>
            /// <typeparam name="T"></typeparam>
            /// <returns></returns>
            template<typename T>
            T* Ptr() {
                return reinterpret_cast<T*>(m_data.data());
            };

            /// <summary>
            /// 
            /// </summary>
            /// <returns></returns>
            const Shape& GetShape() const;

            /// <summary>
            /// 
            /// </summary>
            /// <param name="shape"></param>
            void SetShape(const Shape& shape);

            /// <summary>
            /// 
            /// </summary>
            /// <returns></returns>
            const ElementType& GetElementType() const;

            void SetElementType(const ElementType& type);

        private:

            std::vector<uint8_t> m_data;
            Shape m_shape;
            ElementType m_elemType;
        };

        std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
            const auto& shape = tensor.GetShape();
            const auto& eletype = tensor.GetElementType();
            os << shape << "\t" << eletype << "\n";
            return os;
        }

        typedef std::shared_ptr<Tensor> TensorPtr;

    } // namespace Base
    
    
} // namespace Inference
