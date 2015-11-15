#ifndef PLUGINBASE_H
#define PLUGINBASE_H

#include <cassert>

#include <Astra/astra_types.h>
#include <Astra/host_events.h>
#include "PluginServiceProxy.h"
#include "PluginLogger.h"

namespace astra {

    inline const char* get_uri_for_streamset(PluginServiceProxy& pluginService, astra_streamset_t streamSet)
    {
        const char* uri;
        pluginService.get_streamset_uri(streamSet, &uri);

        return uri;
    }

    class PluginBase
    {
    public:
        PluginBase(PluginServiceProxy* pluginService, const char* pluginName)
            :  m_pluginService(pluginService)
        {
            assert(pluginService != nullptr);
        }

        virtual ~PluginBase() = default;

        void initialize() { on_initialize(); };

        virtual void temp_update() { };

    protected:
        inline PluginServiceProxy& pluginService() const { return *m_pluginService; }

        void register_for_stream_events()
        {
            pluginService().
                register_stream_registered_callback(&PluginBase::stream_added_handler_thunk,
                                                    this,
                                                    &m_streamAddedCallbackId);

            pluginService().
                register_stream_unregistering_callback(&PluginBase::stream_removing_handler_thunk,
                                                       this,
                                                       &m_streamRemovingCallbackId);
        }

        void register_for_host_events()
        {

            pluginService().
                register_host_event_callback(&PluginBase::host_event_handler_thunk,
                                             this,
                                             &m_hostEventCallbackId);
        }

        void unregister_for_stream_events()
        {
            pluginService().unregister_stream_registered_callback(m_streamAddedCallbackId);
            pluginService().unregister_stream_unregistering_callback(m_streamRemovingCallbackId);
        }

        void unregister_for_host_events()
        {
            pluginService().unregister_host_event_callback(m_hostEventCallbackId);
        }

    private:
        PluginServiceProxy* m_pluginService{nullptr};

        virtual void on_initialize() { };

        static void stream_added_handler_thunk(void* clientTag,
                                               astra_streamset_t setHandle,
                                               astra_stream_t streamHandle,
                                               astra_stream_desc_t desc)
        {
            PluginBase* plugin = static_cast<PluginBase*>(clientTag);
            plugin->stream_added_handler(setHandle, streamHandle, desc);
        }

        static void stream_removing_handler_thunk(void* clientTag,
                                                  astra_streamset_t setHandle,
                                                  astra_stream_t streamHandle,
                                                  astra_stream_desc_t desc)

        {
            PluginBase* plugin = static_cast<PluginBase*>(clientTag);
            plugin->stream_removing_handler(setHandle, streamHandle, desc);
        }

        static void host_event_handler_thunk(void* clientTag,
                                             astra_event_id id,
                                             const void* data,
                                             size_t dataSize)
        {
            PluginBase* self = static_cast<PluginBase*>(clientTag);
            self->host_event_handler(id, data, dataSize);
        }

        void stream_added_handler(astra_streamset_t setHandle,
                                  astra_stream_t streamHandle,
                                  astra_stream_desc_t desc)
        {
            on_stream_added(setHandle, streamHandle, desc);
        }

        void stream_removing_handler(astra_streamset_t setHandle,
                                     astra_stream_t streamHandle,
                                     astra_stream_desc_t desc)
        {
            on_stream_removed(setHandle, streamHandle, desc);
        }

        void host_event_handler(astra_event_id id,
                                const void* data,
                                size_t dataSize)
        {
            on_host_event(id, data, dataSize);
        }

        virtual void on_stream_added(astra_streamset_t setHandle,
                                     astra_stream_t streamHandle,
                                     astra_stream_desc_t desc)
        {}

        virtual void on_stream_removed(astra_streamset_t setHandle,
                                       astra_stream_t streamHandle,
                                       astra_stream_desc_t desc)
        {}

        virtual void on_host_event(astra_event_id id, const void* data, size_t dataSize)
        {}

        astra_callback_id_t m_streamAddedCallbackId;
        astra_callback_id_t m_streamRemovingCallbackId;
        astra_callback_id_t m_hostEventCallbackId;
    };
}

#define EXPORT_PLUGIN(className)                                                         \
                                                                                         \
    static std::unique_ptr<className> g_plugin;                                          \
    astra::PluginServiceProxy* __g_serviceProxy;                                         \
                                                                                         \
    ASTRA_BEGIN_DECLS                                                                    \
                                                                                         \
    ASTRA_EXPORT void astra_plugin_initialize(PluginServiceProxyBase* pluginProxy)       \
    {                                                                                    \
        __g_serviceProxy = static_cast<astra::PluginServiceProxy*>(pluginProxy);         \
        g_plugin = std::make_unique<className>(                                          \
            static_cast<astra::PluginServiceProxy*>(pluginProxy));                       \
        g_plugin->initialize();                                                          \
    }                                                                                    \
                                                                                         \
    ASTRA_EXPORT void astra_plugin_update()                                              \
    {                                                                                    \
        g_plugin->temp_update();                                                         \
    }                                                                                    \
                                                                                         \
    ASTRA_EXPORT void astra_plugin_terminate()                                           \
    {                                                                                    \
        g_plugin = nullptr;                                                              \
        __g_serviceProxy = nullptr;                                                      \
    }                                                                                    \
                                                                                         \
    ASTRA_END_DECLS

#endif /* PLUGINBASE_H */