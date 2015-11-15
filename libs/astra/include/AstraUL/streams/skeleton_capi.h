#ifndef SKELETON_CAPI_H
#define SKELETON_CAPI_H

#include <Astra/astra_defines.h>
#include <Astra/astra_types.h>
#include "skeleton_types.h"

ASTRA_BEGIN_DECLS

ASTRA_API_EX astra_status_t astra_reader_get_skeletonstream(astra_reader_t reader,
                                                                     astra_skeletonstream_t* skeletonStream);

ASTRA_API_EX astra_status_t astra_frame_get_skeletonframe(astra_reader_frame_t readerFrame,
                                                                   astra_skeletonframe_t* skeletonFrame);

ASTRA_API_EX astra_status_t astra_skeletonframe_get_frameindex(astra_skeletonframe_t skeletonFrame,
                                                                        astra_frame_index_t* index);

ASTRA_API_EX astra_status_t astra_skeletonframe_get_skeleton_count(astra_skeletonframe_t skeletonFrame,
                                                                            size_t* skeletonCount);

ASTRA_API_EX astra_status_t astra_skeletonframe_copy_skeletons(astra_skeletonframe_t skeletonFrame,
                                                                        astra_skeleton_t* skeletonsDestination);

ASTRA_API_EX astra_status_t astra_skeletonframe_get_skeletons_ptr(astra_skeletonframe_t skeletonFrame,
                                                                           astra_skeleton_t** skeletons,
                                                                           size_t* skeletonCount);

ASTRA_END_DECLS

#endif // SKELETON_CAPI_H
