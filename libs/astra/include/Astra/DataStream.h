#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <Astra/astra_capi.h>
#include <Astra/StreamDescription.h>
#include <stdexcept>

namespace astra {

    class DataStream
    {
    public:
        DataStream()
        {}

        DataStream(astra_streamconnection_t connection)
            : m_connection(connection)
        {
            if (m_connection != nullptr)
            {
                astra_stream_get_description(connection, &m_description);
            }
        }

        bool is_available() { return m_connection != nullptr; }

        void start()
        {
            if (m_connection == nullptr)
            {
                throw std::logic_error("Cannot start a stream that is not available");
            }
            astra_stream_start(m_connection);
        }
        void stop()

        {
            if (m_connection == nullptr)
            {
                throw std::logic_error("Cannot stop a stream that is not available");
            }
            astra_stream_stop(m_connection);
        }

    private:
        astra_streamconnection_t m_connection{nullptr};
        astra_stream_desc_t m_description;
    };
}

#endif /* DATASTREAM_H */
