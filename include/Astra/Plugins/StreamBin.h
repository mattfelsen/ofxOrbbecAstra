#ifndef PLUGIN_STREAMBIN_H
#define PLUGIN_STREAMBIN_H

#include <Astra/astra_types.h>
#include <Astra/Plugins/plugin_capi.h>
#include <Astra/Plugins/PluginServiceProxy.h>

namespace astra { namespace plugins {

    template<typename TFrameType>
    class StreamBin
    {
    public:
        StreamBin(PluginServiceProxy& pluginService,
                  astra_stream_t streamHandle,
                  size_t dataSize)
            : m_streamHandle(streamHandle),
              m_pluginService(pluginService)
        {
            size_t dataWrapperSize = dataSize + sizeof(TFrameType);
            m_pluginService.create_stream_bin(streamHandle,
                                              dataWrapperSize,
                                              &m_binHandle,
                                              &m_currentBuffer);
        }

        ~StreamBin()
        {
            m_pluginService.destroy_stream_bin(m_streamHandle, &m_binHandle, &m_currentBuffer);
        }

        bool has_connections()
        {
            bool hasConnections = false;
            m_pluginService.bin_has_connections(m_binHandle, &hasConnections);

            return hasConnections;
        }

        void cycle()
        {
            m_pluginService.cycle_bin_buffers(m_binHandle, &m_currentBuffer);
        }

        TFrameType* begin_write(size_t frameIndex)
        {
            if (m_locked)
                return reinterpret_cast<TFrameType*>(m_currentBuffer->data);

            m_locked = true;
            m_currentBuffer->frameIndex = frameIndex;
            return reinterpret_cast<TFrameType*>(m_currentBuffer->data);
        }

        std::pair<astra_frame_t*, TFrameType*> begin_write_ex(size_t frameIndex)
        {
            if (m_locked)
            {
                return std::make_pair(m_currentBuffer, reinterpret_cast<TFrameType*>(m_currentBuffer->data));
            }

            m_locked = true;
            m_currentBuffer->frameIndex = frameIndex;

            return std::make_pair(m_currentBuffer, reinterpret_cast<TFrameType*>(m_currentBuffer->data));
        }

        void end_write()
        {
            if (!m_locked)
                return;

            cycle();
            m_locked = false;
        }

        void link_connection(astra_streamconnection_t connection)
        {
            m_pluginService.link_connection_to_bin(connection, m_binHandle);

        }

        void unlink_connection(astra_streamconnection_t connection)
        {
            m_pluginService.link_connection_to_bin(connection, nullptr);
        }

    private:
        astra_stream_t m_streamHandle;
        astra_bin_t m_binHandle;
        size_t m_bufferSize{0};
        astra_frame_t* m_currentBuffer{nullptr};
        PluginServiceProxy& m_pluginService;
        bool m_locked{false};
    };

}}

#endif /* PLUGIN_STREAMBIN_H */
