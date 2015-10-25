#ifndef SINGLEBINSTREAM_H
#define SINGLEBINSTREAM_H

#include "Stream.h"
#include "StreamBin.h"
#include <memory>

namespace astra { namespace plugins {

    template<typename TFrameType>
    class SingleBinStream : public astra::plugins::Stream
    {
    public:
        SingleBinStream(PluginServiceProxy& pluginService,
                        astra_streamset_t streamSet,
                        StreamDescription description,
                        size_t bufferSize)
            : Stream(pluginService,
                     streamSet,
                     description)
        {
            m_bin = std::make_unique<bin_type>(pluginService,
                                               get_handle(),
                                               sizeof(TFrameType) + bufferSize);
        }

        using frame_type = TFrameType;

        bool has_connections()
        {
            return m_bin->has_connections();
        }

        TFrameType* begin_write(size_t frameIndex)
        {
            return m_bin->begin_write(frameIndex);
        }

        void end_write()
        {
            return m_bin->end_write();
        }

    protected:
        virtual void on_connection_added(astra_streamconnection_t connection) override
        {
            m_bin->link_connection(connection);
        }

        virtual void on_connection_removed(astra_bin_t bin,
                                           astra_streamconnection_t connection) override
        {
            m_bin->unlink_connection(connection);
        }

    private:
        using bin_type = StreamBin<TFrameType>;
        std::unique_ptr<bin_type> m_bin;
    };
}}

#endif /* SINGLEBINSTREAM_H */
