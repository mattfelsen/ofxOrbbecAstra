#ifndef INFRARED_H
#define INFRARED_H

#include <Astra/Astra.h>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/infrared_capi.h>
#include <AstraUL/streams/Image.h>
#include <AstraUL/Vector.h>

namespace astra {

    class InfraredStream : public ImageStream
    {
    public:
        explicit InfraredStream(astra_streamconnection_t connection)
            : ImageStream(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_INFRARED;
    };

    class InfraredFrame16 : public ImageFrame<uint16_t, ASTRA_STREAM_INFRARED>
    {
    public:
        InfraredFrame16(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_GRAY16)
        {}
    };

    class InfraredFrameRGB : public ImageFrame<RGBPixel, ASTRA_STREAM_INFRARED>
    {
    public:
        InfraredFrameRGB(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };

}

#endif /* INFRARED_H */
