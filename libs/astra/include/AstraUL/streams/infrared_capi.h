#ifndef INFRARED_CAPI_H
#define INFRARED_CAPI_H

#include <Astra/astra_defines.h>
#include <Astra/astra_types.h>
#include <AstraUL/streams/infrared_types.h>
#include <stdbool.h>

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_reader_get_infraredstream(astra_reader_t reader,
                                                            astra_infraredstream_t* infraredstream);

ASTRA_API_EX astra_status_t astra_infraredstream_get_hfov(astra_infraredstream_t infraredstream,
                                                          float* hFov);

ASTRA_API_EX astra_status_t astra_infraredstream_get_vfov(astra_infraredstream_t infraredstream,
                                                          float* vFov);

ASTRA_API_EX astra_status_t astra_frame_get_infraredframe(astra_reader_frame_t readerFrame,
                                                          astra_infraredframe_t* infraredframe);

ASTRA_API_EX astra_status_t astra_frame_get_infraredframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                       astra_stream_subtype_t subtype,
                                                                       astra_infraredframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_infraredframe_get_data_byte_length(astra_infraredframe_t infraredframe,
                                                                     size_t* byteLength);

ASTRA_API_EX astra_status_t astra_infraredframe_get_data_ptr(astra_infraredframe_t infraredframe,
                                                             uint8_t** data,
                                                             size_t* byteLength);

ASTRA_API_EX astra_status_t astra_infraredframe_copy_data(astra_infraredframe_t infraredframe,
                                                          uint8_t* data);

ASTRA_API_EX astra_status_t astra_infraredframe_get_metadata(astra_infraredframe_t infraredframe,
                                                             astra_image_metadata_t* metadata );

ASTRA_API_EX astra_status_t astra_infraredframe_get_frameindex(astra_infraredframe_t infraredframe,
                                                               astra_frame_index_t* index);

ASTRA_END_DECLS


#endif /* INFRARED_CAPI_H */
