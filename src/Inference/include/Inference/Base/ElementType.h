#pragma once
#include <string>
#include <ostream>

#include "Common/BiMap.hpp"

namespace Inference
{
    namespace Base
    {
        
        enum class Type_t
        {
            undefined = -1,
            i8 = 0,
            u8,
            f32,
            i32,
            u32,
            i64,
            u64
        };

        class ElementType
        {
        public:
            ElementType() = default;
            ElementType(const ElementType& type);
            ElementType(Type_t type);
            explicit ElementType(const std::string& type);

            /// <summary>
            /// get the element size
            /// </summary>
            /// <returns></returns>
            std::size_t Size() const;

            /// <summary>
            /// get the element string name
            /// </summary>
            /// <returns></returns>
            std::string GetName() const;

            Type_t Type() const;

        private:
            ElementType TypeFromString(const std::string& type);
        private:
            Type_t m_type{ Type_t::undefined };
            
            const static Common::BiMap<Type_t, std::string> m_type2str;
        };

        inline std::ostream& operator<<(std::ostream& os, const ElementType& type) {
            os << "element name:" << type.GetName() << "element size:" << type.Size();
            return os;
        }

        
    } // namespace Base
    

} // namespace Inference
