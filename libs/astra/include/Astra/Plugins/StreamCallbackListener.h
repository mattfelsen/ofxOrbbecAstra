/* THIS FILE AUTO-GENERATED FROM StreamCallbackListener.h.lpp. DO NOT EDIT. */
#ifndef STREAMCALLBACKTARGET_H
#define STREAMCALLBACKTARGET_H

#include <Astra/astra_types.h>
#include <Astra/Plugins/plugin_callbacks.h>

namespace astra {

    class StreamCallbackListener
    {
    public:
        virtual ~StreamCallbackListener() = default;
    private:

        static void set_parameter_thunk(void* instance,
                                        astra_streamconnection_t connection,
                                        astra_parameter_id id,
                                        size_t inByteLength,
                                        astra_parameter_data_t inData)
        {
            static_cast<StreamCallbackListener*>(instance)->set_parameter(connection,
                                                                          id,
                                                                          inByteLength,
                                                                          inData);
        }

        static void get_parameter_thunk(void* instance,
                                        astra_streamconnection_t connection,
                                        astra_parameter_id id,
                                        astra_parameter_bin_t* parameterBin)
        {
            static_cast<StreamCallbackListener*>(instance)->get_parameter(connection,
                                                                          id,
                                                                          *parameterBin);
        }

        static void invoke_thunk(void* instance,
                                 astra_streamconnection_t connection,
                                 astra_command_id commandId,
                                 size_t inByteLength,
                                 astra_parameter_data_t inData,
                                 astra_parameter_bin_t* parameterBin)
        {
            static_cast<StreamCallbackListener*>(instance)->invoke(connection,
                                                                   commandId,
                                                                   inByteLength,
                                                                   inData,
                                                                   *parameterBin);
        }

        static void connection_added_thunk(void* instance,
                                           astra_stream_t stream,
                                           astra_streamconnection_t connection)
        {
            static_cast<StreamCallbackListener*>(instance)->connection_added(stream,
                                                                             connection);
        }

        static void connection_removed_thunk(void* instance,
                                             astra_stream_t stream,
                                             astra_bin_t bin,
                                             astra_streamconnection_t connection)
        {
            static_cast<StreamCallbackListener*>(instance)->connection_removed(stream,
                                                                               bin,
                                                                               connection);
        }

        static void connection_started_thunk(void* instance,
                                             astra_stream_t stream,
                                             astra_streamconnection_t connection)
        {
            static_cast<StreamCallbackListener*>(instance)->connection_started(stream,
                                                                               connection);
        }

        static void connection_stopped_thunk(void* instance,
                                             astra_stream_t stream,
                                             astra_streamconnection_t connection)
        {
            static_cast<StreamCallbackListener*>(instance)->connection_stopped(stream,
                                                                               connection);
        }

        virtual void set_parameter(astra_streamconnection_t connection,
                                   astra_parameter_id id,
                                   size_t inByteLength,
                                   astra_parameter_data_t inData) {}

        virtual void get_parameter(astra_streamconnection_t connection,
                                   astra_parameter_id id,
                                   astra_parameter_bin_t& parameterBin) {}

        virtual void invoke(astra_streamconnection_t connection,
                            astra_command_id commandId,
                            size_t inByteLength,
                            astra_parameter_data_t inData,
                            astra_parameter_bin_t& parameterBin) {}

        virtual void connection_added(astra_stream_t stream,
                                      astra_streamconnection_t connection) {}

        virtual void connection_removed(astra_stream_t stream,
                                        astra_bin_t bin,
                                        astra_streamconnection_t connection) {}

        virtual void connection_started(astra_stream_t stream,
                                        astra_streamconnection_t connection) {}

        virtual void connection_stopped(astra_stream_t stream,
                                        astra_streamconnection_t connection) {}


        friend stream_callbacks_t create_plugin_callbacks(StreamCallbackListener* context);
    };

    inline stream_callbacks_t create_plugin_callbacks(StreamCallbackListener* context)
    {
        stream_callbacks_t callbacks;

        callbacks.context = context;
        callbacks.set_parameter_callback = &StreamCallbackListener::set_parameter_thunk;
        callbacks.get_parameter_callback = &StreamCallbackListener::get_parameter_thunk;
        callbacks.invoke_callback = &StreamCallbackListener::invoke_thunk;
        callbacks.connection_added_callback = &StreamCallbackListener::connection_added_thunk;
        callbacks.connection_removed_callback = &StreamCallbackListener::connection_removed_thunk;
        callbacks.connection_started_callback = &StreamCallbackListener::connection_started_thunk;
        callbacks.connection_stopped_callback = &StreamCallbackListener::connection_stopped_thunk;

        return callbacks;
    }
}

#endif /* STREAMCALLBACKTARGET_H */
