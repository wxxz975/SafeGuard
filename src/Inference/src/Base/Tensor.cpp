#include "Inference/Base/Tensor.h"

#include <cassert>

namespace Inference
{
    namespace Base
    {
        // ElementType getElementType(const cv::Mat& img) {
        //     switch (img.type()) {
        //     case CV_8UC1:
        //     case CV_8UC3:
        //     case CV_8UC4:
        //         return Type_t::u8; // 8-bit unsigned integer
        //     case CV_16UC1:
        //     case CV_16UC3:
        //     case CV_16UC4:
        //         return Type_t::u32; // 16-bit unsigned integer
        //     case CV_32FC1:
        //     case CV_32FC3:
        //     case CV_32FC4:
        //         return Type_t::f32; // 32-bit float
        //     case CV_64FC1:
        //     case CV_64FC3:
        //     case CV_64FC4:
        //         return Type_t::u64; // 64-bit float
                
        //     default:
        //         return Type_t::undefined; // 未知类型
        //     }
        // }


        Tensor::Tensor(const Shape& shape, ElementType type, void* ptr) 
        {
            SetShape(shape);
            SetElementType(type);
            
            size_t byte_size = GetByteSize();
            m_data.assign(ptr, ptr + byte_size);
        }
        Tensor::Tensor(const Shape &shape, ElementType type, std::vector<uint8_t> &&data) 
            :m_data(std::move(data))
        {
            SetShape(shape);
            SetElementType(type);
        };

        Tensor::~Tensor()
        {
        };

        size_t Tensor::GetSize()
        {
            size_t size = 1;
            for (auto v : m_shape) {
                size *= v;
            }

            return size == 1 ? 0 : size;
        }


        size_t Tensor::GetByteSize()
        {
            size_t element_count = GetSize();
            size_t element_size = GetElementType().Size();
            
            size_t size = element_count * element_size;

            assert(size > 0);

            return size;
        }

        Tensor Tensor::CreateTensor(const Shape &shape, ElementType type, void *ptr)
        {
            //return Tensor();
        }
        
        const Shape& Tensor::GetShape() const
        {
            return m_shape;
        }
        
        void Tensor::SetShape(const Shape& shape)
        {
            m_shape = shape;
        }

        const ElementType& Tensor::GetElementType() const
        {
            return m_elemType;
        }

        void Tensor::SetElementType(const ElementType &type)
        {
            m_elemType = type;
        }

    } // namespace Base
    
} // namespace Inference
