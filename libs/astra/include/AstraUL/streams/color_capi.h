#ifndef COLOR_CAPI_H
#define COLOR_CAPI_H

#include <Astra/astra_types.h>
#include "color_types.h"
#include <stdbool.h>

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_reader_get_colorstream(astra_reader_t reader,
                                                         astra_colorstream_t* colorStream);

ASTRA_API_EX astra_status_t astra_frame_get_colorframe(astra_reader_frame_t readerFrame,
                                                       astra_colorframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_frame_get_colorframe_with_subtype(astra_reader_frame_t readerFrame,
                                                                    astra_stream_subtype_t subtype,
                                                                    astra_colorframe_t* colorFrame);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_byte_length(astra_colorframe_t colorFrame,
                                                                  size_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_ptr(astra_colorframe_t colorFrame,
                                                          uint8_t** data,
                                                          size_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_get_data_rgb_ptr(astra_colorframe_t colorFrame,
                                                              astra_rgb_pixel_t** data,
															  size_t* byteLength);

ASTRA_API_EX astra_status_t astra_colorframe_copy_data(astra_colorframe_t colorFrame,
                                                       uint8_t* data);

ASTRA_API_EX astra_status_t astra_colorframe_get_metadata(astra_colorframe_t colorFrame,
                                                          astra_image_metadata_t* metadata);

ASTRA_API_EX astra_status_t astra_colorframe_get_frameindex(astra_colorframe_t colorFrame,
                                                            astra_frame_index_t* index);
ASTRA_END_DECLS

#endif /* COLOR_CAPI_H */
