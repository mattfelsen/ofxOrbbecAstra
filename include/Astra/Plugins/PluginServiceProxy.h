/* THIS FILE AUTO-GENERATED FROM PluginServiceProxy.h.lpp. DO NOT EDIT. */
#ifndef PLUGINSERVICEPROXY_H
#define PLUGINSERVICEPROXY_H

#include "PluginServiceProxyBase.h"
#include <cstdarg>
#include <cstdio>

namespace astra {

    class PluginServiceProxy : public PluginServiceProxyBase
    {
    public:

    astra_status_t register_stream_registered_callback(stream_registered_callback_t callback,
                                                       void* clientTag,
                                                       astra_callback_id_t* callbackId)
    {
        return PluginServiceProxyBase::register_stream_registered_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t register_stream_unregistering_callback(stream_unregistering_callback_t callback,
                                                          void* clientTag,
                                                          astra_callback_id_t* callbackId)
    {
        return PluginServiceProxyBase::register_stream_unregistering_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t register_host_event_callback(host_event_callback_t callback,
                                                void* clientTag,
                                                astra_callback_id_t* callbackId)
    {
        return PluginServiceProxyBase::register_host_event_callback(pluginService, callback, clientTag, callbackId);
    }

    astra_status_t unregister_host_event_callback(astra_callback_id_t callback)
    {
        return PluginServiceProxyBase::unregister_host_event_callback(pluginService, callback);
    }

    astra_status_t unregister_stream_registered_callback(astra_callback_id_t callback)
    {
        return PluginServiceProxyBase::unregister_stream_registered_callback(pluginService, callback);
    }

    astra_status_t unregister_stream_unregistering_callback(astra_callback_id_t callback)
    {
        return PluginServiceProxyBase::unregister_stream_unregistering_callback(pluginService, callback);
    }

    astra_status_t create_stream_set(const char* setUri,
                                     astra_streamset_t& setHandle)
    {
        return PluginServiceProxyBase::create_stream_set(pluginService, setUri, setHandle);
    }

    astra_status_t destroy_stream_set(astra_streamset_t& setHandle)
    {
        return PluginServiceProxyBase::destroy_stream_set(pluginService, setHandle);
    }

    astra_status_t get_streamset_uri(astra_streamset_t setHandle,
                                     const char** uri)
    {
        return PluginServiceProxyBase::get_streamset_uri(pluginService, setHandle, uri);
    }

    astra_status_t create_stream(astra_streamset_t setHandle,
                                 astra_stream_desc_t desc,
                                 astra_stream_t* handle)
    {
        return PluginServiceProxyBase::create_stream(pluginService, setHandle, desc, handle);
    }

    astra_status_t register_stream(astra_stream_t handle,
                                   stream_callbacks_t pluginCallbacks)
    {
        return PluginServiceProxyBase::register_stream(pluginService, handle, pluginCallbacks);
    }

    astra_status_t unregister_stream(astra_stream_t handle)
    {
        return PluginServiceProxyBase::unregister_stream(pluginService, handle);
    }

    astra_status_t destroy_stream(astra_stream_t& handle)
    {
        return PluginServiceProxyBase::destroy_stream(pluginService, handle);
    }

    astra_status_t create_stream_bin(astra_stream_t streamHandle,
                                     size_t lengthInBytes,
                                     astra_bin_t* binHandle,
                                     astra_frame_t** binBuffer)
    {
        return PluginServiceProxyBase::create_stream_bin(pluginService, streamHandle, lengthInBytes, binHandle, binBuffer);
    }

    astra_status_t destroy_stream_bin(astra_stream_t streamHandle,
                                      astra_bin_t* binHandle,
                                      astra_frame_t** binBuffer)
    {
        return PluginServiceProxyBase::destroy_stream_bin(pluginService, streamHandle, binHandle, binBuffer);
    }

    astra_status_t bin_has_connections(astra_bin_t binHandle,
                                       bool* hasConnections)
    {
        return PluginServiceProxyBase::bin_has_connections(pluginService, binHandle, hasConnections);
    }

    astra_status_t cycle_bin_buffers(astra_bin_t binHandle,
                                     astra_frame_t** binBuffer)
    {
        return PluginServiceProxyBase::cycle_bin_buffers(pluginService, binHandle, binBuffer);
    }

    astra_status_t link_connection_to_bin(astra_streamconnection_t connection,
                                          astra_bin_t binHandle)
    {
        return PluginServiceProxyBase::link_connection_to_bin(pluginService, connection, binHandle);
    }

    astra_status_t get_parameter_bin(size_t byteSize,
                                     astra_parameter_bin_t* binHandle,
                                     astra_parameter_data_t* parameterData)
    {
        return PluginServiceProxyBase::get_parameter_bin(pluginService, byteSize, binHandle, parameterData);
    }

    astra_status_t log(const char* channel,
                       astra_log_severity_t logLevel,
                       const char* fileName,
                       int lineNo,
                       const char* func,
                       const char* format,
                       va_list args)
    {
        return PluginServiceProxyBase::log(pluginService, channel, logLevel, fileName, lineNo, func, format, args);
    }
    };
}

#endif /* PLUGINSERVICEPROXY_H */
