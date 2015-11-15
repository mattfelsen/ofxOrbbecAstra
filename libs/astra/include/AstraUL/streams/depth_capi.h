#ifndef DEPTH_CAPI_H
#define DEPTH_CAPI_H

#include <Astra/astra_defines.h>
#include <Astra/astra_types.h>
#include <AstraUL/streams/depth_types.h>
#include <stdbool.h>

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_convert_depth_to_world(astra_depthstream_t depthStream,
                                                         float depthX, float depthY, float depthZ,
                                                         float* pWorldX, float* pWorldY, float* pWorldZ);

ASTRA_API_EX astra_status_t astra_convert_world_to_depth(astra_depthstream_t depthStream,
                                                         float worldX, float worldY, float worldZ,
                                                         float* pDepthX, float* pDepthY, float* pDepthZ);

ASTRA_API_EX astra_status_t astra_reader_get_depthstream(astra_reader_t reader,
                                                         astra_depthstream_t* depthStream);

ASTRA_API_EX astra_status_t astra_depthstream_get_depth_to_world_data(astra_depthstream_t depthStream,
                                                                      conversion_cache_t* conversion_data);

ASTRA_API_EX astra_status_t astra_depthstream_get_hfov(astra_depthstream_t depthStream,
                                                       float* hFov);

ASTRA_API_EX astra_status_t astra_depthstream_get_vfov(astra_depthstream_t depthStream,
                                                       float* vFov);

ASTRA_API_EX astra_status_t astra_depthstream_get_registration(astra_depthstream_t depthStream,
                                                               bool* enabled);

ASTRA_API_EX astra_status_t astra_depthstream_set_registration(astra_depthstream_t depthStream,
                                                               bool enabled);

ASTRA_API_EX astra_status_t astra_frame_get_depthframe(astra_reader_frame_t readerFrame,
                                                       astra_depthframe_t* depthFrame);

ASTRA_API_EX astra_status_t astra_frame_get_depthframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                    astra_stream_subtype_t subtype,
                                                                    astra_depthframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_depthframe_get_data_byte_length(astra_depthframe_t depthFrame,
                                                                  size_t* byteLength);

ASTRA_API_EX astra_status_t astra_depthframe_get_data_ptr(astra_depthframe_t depthFrame,
                                                          int16_t** data,
                                                          size_t* byteLength);

ASTRA_API_EX astra_status_t astra_depthframe_copy_data(astra_depthframe_t depthFrame,
                                                       int16_t* data);

ASTRA_API_EX astra_status_t astra_depthframe_get_metadata(astra_depthframe_t depthFrame,
                                                          astra_image_metadata_t* metadata );

ASTRA_API_EX astra_status_t astra_depthframe_get_frameindex(astra_depthframe_t depthFrame,
                                                            astra_frame_index_t* index);

ASTRA_END_DECLS

#endif // DEPTH_CAPI_H
