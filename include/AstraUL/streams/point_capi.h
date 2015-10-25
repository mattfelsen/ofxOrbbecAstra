#ifndef POINT_CAPI_H
#define POINT_CAPI_H

#include <Astra/astra_types.h>
#include "point_types.h"

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_reader_get_pointstream(astra_reader_t reader,
                                                                  astra_pointstream_t* pointStream);

ASTRA_API_EX astra_status_t astra_frame_get_pointframe(astra_reader_frame_t readerFrame,
                                                                astra_pointframe_t* pointFrame);

ASTRA_API_EX astra_status_t astra_frame_get_pointframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                             astra_stream_subtype_t subtype,
                                                                             astra_pointframe_t* pointFrame);

ASTRA_API_EX astra_status_t astra_pointframe_get_data_byte_length(astra_pointframe_t pointFrame,
                                                                           size_t* byteLength);

ASTRA_API_EX astra_status_t astra_pointframe_get_data_ptr(astra_pointframe_t pointFrame,
                                                                   astra_vector3f_t** data,
                                                                   size_t* byteLength);

ASTRA_API_EX astra_status_t astra_pointframe_copy_data(astra_pointframe_t pointFrame,
                                                                astra_vector3f_t* data);

ASTRA_API_EX astra_status_t astra_pointframe_get_metadata(astra_pointframe_t pointFrame,
                                                                   astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_pointframe_get_frameindex(astra_pointframe_t pointFrame,
                                                                     astra_frame_index_t* index);
ASTRA_END_DECLS

#endif /* POINT_CAPI_H */
