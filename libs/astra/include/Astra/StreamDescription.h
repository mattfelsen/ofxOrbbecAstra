#ifndef STREAMDESCRIPTION_H
#define STREAMDESCRIPTION_H

#include <Astra/astra_capi.h>
#include <cassert>

namespace astra {

    class StreamDescription : private ::astra_stream_desc_t
    {
    public:
        StreamDescription(::astra_stream_type_t type,
                          ::astra_stream_subtype_t subtype = DEFAULT_SUBTYPE)
        {
            ::astra_stream_desc_t::type = type;
            ::astra_stream_desc_t::subtype = subtype;
        }

        StreamDescription(const ::astra_stream_desc_t& desc)
        {
            *this = desc;
        }

        StreamDescription& operator=(const ::astra_stream_desc_t& desc)
        {
            ::astra_stream_desc_t::type = desc.type;
            ::astra_stream_desc_t::subtype = desc.subtype;

            return *this;
        }

        operator ::astra_stream_desc_t*() { return this; }
        operator const ::astra_stream_desc_t*() const { return this; }

        astra_stream_type_t type() const { return ::astra_stream_desc_t::type; }
        void set_type(astra_stream_type_t type) { ::astra_stream_desc_t::type = type; }

        astra_stream_subtype_t subtype() const { return ::astra_stream_desc_t::subtype; }
        void set_subtype(astra_stream_subtype_t subtype) { ::astra_stream_desc_t::subtype = subtype; }
    };

    inline bool operator==(const StreamDescription& lhs, const StreamDescription& rhs)
    {
        return lhs.type() == rhs.type() && lhs.subtype() == rhs.subtype();
    }

    inline bool operator!=(const StreamDescription& lhs, const StreamDescription& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif /* STREAMDESCRIPTION_H */
