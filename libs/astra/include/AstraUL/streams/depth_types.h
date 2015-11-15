#ifndef DEPTH_TYPES_H
#define DEPTH_TYPES_H

#include <Astra/astra_types.h>
#include <AstraUL/streams/image_types.h>

typedef struct {
    float xzFactor;
    float yzFactor;
    float coeffX;
    float coeffY;
    int resolutionX;
    int resolutionY;
    int halfResX;
    int halfResY;
} conversion_cache_t;

typedef astra_streamconnection_t astra_depthstream_t;
typedef struct _astra_imageframe* astra_depthframe_t;

#endif // DEPTH_TYPES_H
