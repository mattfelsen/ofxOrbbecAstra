/* THIS FILE AUTO-GENERATED FROM StreamServiceProxyBase.h.lpp. DO NOT EDIT. */
#ifndef STREAMSERVICEPROXYBASE_H
#define STREAMSERVICEPROXYBASE_H

#include <Astra/astra_types.h>

struct StreamServiceProxyBase
{
    void* streamService;

    astra_status_t (*streamset_open)(void*,
                                     const char*,
                                     astra_streamsetconnection_t*);

    astra_status_t (*streamset_close)(void*,
                                      astra_streamsetconnection_t*);

    astra_status_t (*reader_create)(void*,
                                    astra_streamsetconnection_t,
                                    astra_reader_t*);

    astra_status_t (*reader_destroy)(void*,
                                     astra_reader_t*);

    astra_status_t (*reader_get_stream)(void*,
                                        astra_reader_t,
                                        astra_stream_type_t,
                                        astra_stream_subtype_t,
                                        astra_streamconnection_t*);

    astra_status_t (*stream_get_description)(void*,
                                             astra_streamconnection_t,
                                             astra_stream_desc_t*);

    astra_status_t (*stream_start)(void*,
                                   astra_streamconnection_t);

    astra_status_t (*stream_stop)(void*,
                                  astra_streamconnection_t);

    astra_status_t (*reader_open_frame)(void*,
                                        astra_reader_t,
                                        int,
                                        astra_reader_frame_t*);

    astra_status_t (*reader_close_frame)(void*,
                                         astra_reader_frame_t*);

    astra_status_t (*reader_register_frame_ready_callback)(void*,
                                                           astra_reader_t,
                                                           astra_frame_ready_callback_t,
                                                           void*,
                                                           astra_reader_callback_id_t*);

    astra_status_t (*reader_unregister_frame_ready_callback)(void*,
                                                             astra_reader_callback_id_t*);

    astra_status_t (*reader_get_frame)(void*,
                                       astra_reader_frame_t,
                                       astra_stream_type_t,
                                       astra_stream_subtype_t,
                                       astra_frame_t**);

    astra_status_t (*stream_set_parameter)(void*,
                                           astra_streamconnection_t,
                                           astra_parameter_id,
                                           size_t,
                                           astra_parameter_data_t);

    astra_status_t (*stream_get_parameter)(void*,
                                           astra_streamconnection_t,
                                           astra_parameter_id,
                                           size_t*,
                                           astra_result_token_t*);

    astra_status_t (*stream_get_result)(void*,
                                        astra_streamconnection_t,
                                        astra_result_token_t,
                                        size_t,
                                        astra_parameter_data_t);

    astra_status_t (*stream_invoke)(void*,
                                    astra_streamconnection_t,
                                    astra_command_id,
                                    size_t,
                                    astra_parameter_data_t,
                                    size_t*,
                                    astra_result_token_t*);

    astra_status_t (*temp_update)(void*);

};

#endif /* STREAMSERVICEPROXYBASE_H */
