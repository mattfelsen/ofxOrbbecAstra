#ifndef STREAMSET_H
#define STREAMSET_H

#include <string>
#include <Astra/astra_capi.h>
#include <Astra/StreamReader.h>
#include <stdexcept>

namespace astra {

    class StreamSet
    {
    public:
        StreamSet(std::string uri)
        {
            astra_streamsetconnection_t streamSetConnection;
            astra_streamset_open(uri.c_str(), &streamSetConnection);
            m_sensorRef = std::make_shared<StreamSetRef>(streamSetConnection);
        }

        StreamSet(const astra_streamsetconnection_t& streamSetHandle)
        {
            if (streamSetHandle == nullptr)
            {
                throw std::invalid_argument("streamSetHandle must not be null");
            }
            m_sensorRef = std::make_shared<StreamSetRef>(streamSetHandle);
        }

        StreamSet()
            : StreamSet("device/default")
        {}

        bool is_valid() { return m_sensorRef != nullptr; }

        inline StreamReader create_reader();
        astra_streamsetconnection_t get_handle() const { return m_sensorRef->get_connection(); }

    private:
        std::string m_uri;

        class StreamSetRef;
        using StreamSetRefPtr = std::shared_ptr<StreamSetRef>;

        class StreamSetRef :
            public std::enable_shared_from_this<StreamSetRef>
        {
        public:
            StreamSetRef(astra_streamsetconnection_t connection)
                :  m_connection(connection)
            { }

            ~StreamSetRef()
            {
                astra_streamset_close(&m_connection);
            }

            astra_streamsetconnection_t get_connection() const { return m_connection; }

        private:
            astra_streamsetconnection_t m_connection;
        };

        StreamSetRefPtr m_sensorRef;

        friend bool operator==(const StreamSet& lhs, const StreamSet& rhs);
        friend bool operator!=(const StreamSet& lhs, const StreamSet& rhs);
    };

    inline bool operator==(const StreamSet& lhs, const StreamSet& rhs)
    {
        return lhs.m_sensorRef == rhs.m_sensorRef;
    }

    inline bool operator!=(const StreamSet& lhs, const StreamSet& rhs)
    {
        return !(lhs == rhs);
    }

    StreamReader StreamSet::create_reader()
    {
        astra_reader_t reader;
        astra_reader_create(get_handle(), &reader);

        return StreamReader(reader);
    }
}

#endif /* STREAMSET_H */
