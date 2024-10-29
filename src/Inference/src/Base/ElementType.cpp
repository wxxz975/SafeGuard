#include "Inference/Base/ElementType.h"
#include <assert.h>


namespace Inference
{
    namespace Base
    {
        const Common::BiMap<Type_t, std::string> ElementType::m_type2str = {
            { Type_t::undefined, "undefined" },
            { Type_t::i8, "i8" },
            { Type_t::u8, "u8" },
            { Type_t::f32, "f32" },
            { Type_t::i32, "i32" },
            { Type_t::u32, "u32" },
            { Type_t::i64, "i64" },
            { Type_t::u64, "u64" }
        };

        ElementType::ElementType(const ElementType& type)
            :m_type(type.Type())
        {

        }

        ElementType::ElementType(Type_t type)
            :m_type(type)
        {
        }
        
        ElementType::ElementType(const std::string &type)
            : ElementType(TypeFromString(type))
        {

        }

        std::size_t ElementType::Size() const
        {
            if (m_type == Type_t::undefined) {
                return 0;
            }

            switch (m_type)
            {
            case Type_t::i8: return sizeof(int8_t);
            case Type_t::u8: return sizeof(uint8_t);
            case Type_t::f32: return sizeof(float);
            case Type_t::i32: return sizeof(int32_t);
            case Type_t::u32: return sizeof(uint32_t);
            case Type_t::i64: return sizeof(int64_t);
            case Type_t::u64: return sizeof(uint64_t);
            default: assert(0 && "Not a base type!");
            }
            return 0;
        }

        std::string ElementType::GetName() const
        {
            if (auto strname = m_type2str[m_type]) {
                return *strname;
            }
            assert(0 && "Not a base type!");
            return std::string("undefined");
        }

        Type_t ElementType::Type() const
        {
            return m_type;
        }

        ElementType ElementType::TypeFromString(const std::string& name)
        {
            if (auto type = m_type2str[name]) {
                return *type;
            }
            assert(0 && "Not a base type!");
            return ElementType(Type_t::undefined);
        }

        
    } // namespace Base
    
    
} // namespace Inference
