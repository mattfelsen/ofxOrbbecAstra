#ifndef PLUGINSTREAM_H
#define PLUGINSTREAM_H

#include <Astra/Astra.h>
#include <Astra/Plugins/PluginLogger.h>
#include <Astra/Plugins/PluginServiceProxy.h>
#include <Astra/Plugins/StreamCallbackListener.h>
#include <system_error>
#include <cassert>
#include <unordered_set>

namespace astra { namespace plugins {

    class StreamHandleHash
    {
    public:
        std::size_t operator()(const astra_stream_t streamHandle) const
        {
            return std::hash<astra_stream_t>()(streamHandle);
        }
    };

    class StreamHandleEqualTo
    {
    public:
        std::size_t operator()(const astra_stream_t& lhs,
                               const astra_stream_t& rhs) const
        {
            return lhs == rhs;
        }
    };

    template<class T, class U>
    T* make_stream(U&& u)
    {
        T* t = new T(std::forward<U>(u));
        t->register_self();

        return t;
    }

    template<class T, class... U>
    T* make_stream(U&&... u)
    {
        T* t = new T(std::forward<U>(u)...);
        t->register_self();

        return t;
    }

    class Stream : public StreamCallbackListener
    {
    public:
        Stream(PluginServiceProxy& pluginService,
               astra_streamset_t streamSet,
               StreamDescription description)
            : m_pluginService(pluginService),
              m_streamSet(streamSet),
              m_description(description)
        {
            create_stream(description);
        }

        virtual ~Stream()
        {
            m_pluginService.destroy_stream(m_streamHandle);
        }

        void register_self()
        {
            if (m_registered)
                return;

            stream_callbacks_t pluginCallbacks = create_plugin_callbacks(this);
            m_pluginService.register_stream(m_streamHandle, pluginCallbacks);
            m_registered = true;
        }

        inline const StreamDescription& description() { return m_description; }
        inline astra_stream_t get_handle() { return m_streamHandle; }

    protected:
        inline PluginServiceProxy& pluginService() const { return m_pluginService; }
    private:
        virtual void connection_added(astra_stream_t stream,
                                      astra_streamconnection_t connection) override final;

        virtual void connection_removed(astra_stream_t stream,
                                        astra_bin_t bin,
                                        astra_streamconnection_t connection) override final;

        virtual void connection_started(astra_stream_t stream,
                                        astra_streamconnection_t connection) override final;

        virtual void connection_stopped(astra_stream_t stream,
                                        astra_streamconnection_t connection) override final;

        virtual void set_parameter(astra_streamconnection_t connection,
                                   astra_parameter_id id,
                                   size_t inByteLength,
                                   astra_parameter_data_t inData) override final;

        virtual void get_parameter(astra_streamconnection_t connection,
                                   astra_parameter_id id,
                                   astra_parameter_bin_t& parameterBin) override final;

        virtual void invoke(astra_streamconnection_t connection,
                            astra_command_id commandId,
                            size_t inByteLength,
                            astra_parameter_data_t inData,
                            astra_parameter_bin_t& parameterBin) override final;

        virtual void on_connection_added(astra_streamconnection_t connection) {}

        virtual void on_connection_removed(astra_bin_t bin,
                                           astra_streamconnection_t connection) {}

        virtual void on_connection_started(astra_streamconnection_t connection) {}

        virtual void on_connection_stopped(astra_streamconnection_t connection) {}

        virtual void on_set_parameter(astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      size_t inByteLength,
                                      astra_parameter_data_t inData) {}

        virtual void on_get_parameter(astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      astra_parameter_bin_t& parameterBin) {}

        virtual void on_invoke(astra_streamconnection_t connection,
                               astra_command_id commandId,
                               size_t inByteLength,
                               astra_parameter_data_t inData,
                               astra_parameter_bin_t& parameterBin) {};

        void create_stream(StreamDescription& description)
        {
            assert(m_streamHandle == nullptr);

            astra_stream_desc_t* desc = static_cast<astra_stream_desc_t*>(m_description);

            LOG_INFO("astra.plugins.Stream", "creating a %u, %u", desc->type, desc->subtype);
            m_pluginService.create_stream(m_streamSet,
                                          *desc,
                                          &m_streamHandle);


        }

        bool m_registered{false};
        PluginServiceProxy& m_pluginService;
        astra_streamset_t m_streamSet{nullptr};
        StreamDescription m_description;
        astra_stream_t m_streamHandle{nullptr};
    };

    inline void Stream::set_parameter(astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      size_t inByteLength,
                                      astra_parameter_data_t inData)
    {
        on_set_parameter(connection, id, inByteLength, inData);
    }

    inline void Stream::get_parameter(astra_streamconnection_t connection,
                                      astra_parameter_id id,
                                      astra_parameter_bin_t& parameterBin)
    {
        on_get_parameter(connection, id, parameterBin);
    }

    inline void Stream::invoke(astra_streamconnection_t connection,
                               astra_command_id commandId,
                               size_t inByteLength,
                               astra_parameter_data_t inData,
                               astra_parameter_bin_t& parameterBin)
    {
        on_invoke(connection, commandId, inByteLength, inData, parameterBin);
    }

    inline void Stream::connection_added(astra_stream_t stream,
                                         astra_streamconnection_t connection)
    {
        assert(stream == m_streamHandle);
        LOG_INFO("astra.plugins.Stream", "adding connection");
        on_connection_added(connection);
    }

    inline void Stream::connection_removed(astra_stream_t stream,
                                           astra_bin_t bin,
                                           astra_streamconnection_t connection)
    {
        assert(stream == m_streamHandle);
        LOG_INFO("astra.plugins.Stream", "removing connection");
        on_connection_removed(bin, connection);
    }

    inline void Stream::connection_started(astra_stream_t stream,
                                           astra_streamconnection_t connection)
    {
        assert(stream == m_streamHandle);
        on_connection_started(connection);
    }

    inline void Stream::connection_stopped(astra_stream_t stream,
                                           astra_streamconnection_t connection)
    {
        assert(stream == m_streamHandle);
        on_connection_stopped(connection);
    }
}}

#endif /* PLUGINSTREAM_H */
