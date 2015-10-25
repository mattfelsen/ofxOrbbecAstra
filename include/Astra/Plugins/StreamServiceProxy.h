/* THIS FILE AUTO-GENERATED FROM StreamServiceProxy.h.lpp. DO NOT EDIT. */
#ifndef STREAMSERVICEPROXY_H
#define STREAMSERVICEPROXY_H

#include "StreamServiceProxyBase.h"

namespace astra {

    class StreamServiceProxy : public StreamServiceProxyBase
    {
    public:

        astra_status_t streamset_open(const char* connectionString,
                                      astra_streamsetconnection_t* streamSet)
        {
            return StreamServiceProxyBase::streamset_open(streamService, connectionString, streamSet);
        }

        astra_status_t streamset_close(astra_streamsetconnection_t* streamSet)
        {
            return StreamServiceProxyBase::streamset_close(streamService, streamSet);
        }

        astra_status_t reader_create(astra_streamsetconnection_t streamSet,
                                     astra_reader_t* reader)
        {
            return StreamServiceProxyBase::reader_create(streamService, streamSet, reader);
        }

        astra_status_t reader_destroy(astra_reader_t* reader)
        {
            return StreamServiceProxyBase::reader_destroy(streamService, reader);
        }

        astra_status_t reader_get_stream(astra_reader_t reader,
                                         astra_stream_type_t type,
                                         astra_stream_subtype_t subtype,
                                         astra_streamconnection_t* connection)
        {
            return StreamServiceProxyBase::reader_get_stream(streamService, reader, type, subtype, connection);
        }

        astra_status_t stream_get_description(astra_streamconnection_t connection,
                                              astra_stream_desc_t* description)
        {
            return StreamServiceProxyBase::stream_get_description(streamService, connection, description);
        }

        astra_status_t stream_start(astra_streamconnection_t connection)
        {
            return StreamServiceProxyBase::stream_start(streamService, connection);
        }

        astra_status_t stream_stop(astra_streamconnection_t connection)
        {
            return StreamServiceProxyBase::stream_stop(streamService, connection);
        }

        astra_status_t reader_open_frame(astra_reader_t reader,
                                         int timeoutMillis,
                                         astra_reader_frame_t* frame)
        {
            return StreamServiceProxyBase::reader_open_frame(streamService, reader, timeoutMillis, frame);
        }

        astra_status_t reader_close_frame(astra_reader_frame_t* frame)
        {
            return StreamServiceProxyBase::reader_close_frame(streamService, frame);
        }

        astra_status_t reader_register_frame_ready_callback(astra_reader_t reader,
                                                            astra_frame_ready_callback_t callback,
                                                            void* clientTag,
                                                            astra_reader_callback_id_t* callbackId)
        {
            return StreamServiceProxyBase::reader_register_frame_ready_callback(streamService, reader, callback, clientTag, callbackId);
        }

        astra_status_t reader_unregister_frame_ready_callback(astra_reader_callback_id_t* callbackId)
        {
            return StreamServiceProxyBase::reader_unregister_frame_ready_callback(streamService, callbackId);
        }

        astra_status_t reader_get_frame(astra_reader_frame_t frame,
                                        astra_stream_type_t type,
                                        astra_stream_subtype_t subtype,
                                        astra_frame_t** subFrame)
        {
            return StreamServiceProxyBase::reader_get_frame(streamService, frame, type, subtype, subFrame);
        }

        astra_status_t stream_set_parameter(astra_streamconnection_t connection,
                                            astra_parameter_id parameterId,
                                            size_t inByteLength,
                                            astra_parameter_data_t inData)
        {
            return StreamServiceProxyBase::stream_set_parameter(streamService, connection, parameterId, inByteLength, inData);
        }

        astra_status_t stream_get_parameter(astra_streamconnection_t connection,
                                            astra_parameter_id parameterId,
                                            size_t* resultByteLength,
                                            astra_result_token_t* token)
        {
            return StreamServiceProxyBase::stream_get_parameter(streamService, connection, parameterId, resultByteLength, token);
        }

        astra_status_t stream_get_result(astra_streamconnection_t connection,
                                         astra_result_token_t token,
                                         size_t dataByteLength,
                                         astra_parameter_data_t dataDestination)
        {
            return StreamServiceProxyBase::stream_get_result(streamService, connection, token, dataByteLength, dataDestination);
        }

        astra_status_t stream_invoke(astra_streamconnection_t connection,
                                     astra_command_id commandId,
                                     size_t inByteLength,
                                     astra_parameter_data_t inData,
                                     size_t* resultByteLength,
                                     astra_result_token_t* token)
        {
            return StreamServiceProxyBase::stream_invoke(streamService, connection, commandId, inByteLength, inData, resultByteLength, token);
        }

        astra_status_t temp_update()
        {
            return StreamServiceProxyBase::temp_update(streamService);
        }
    };
}

#endif /* STREAMSERVICEPROXY_H */
