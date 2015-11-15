#ifndef COLOR_H
#define COLOR_H

#include <Astra/Astra.h>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/color_capi.h>
#include <AstraUL/streams/Image.h>

namespace astra {

    class ColorStream : public ImageStream
    {
    public:

        explicit ColorStream(astra_streamconnection_t connection)
            : ImageStream(connection)
        {
            m_colorStream = reinterpret_cast<astra_colorstream_t>(connection);
        }

        static const astra_stream_type_t id = ASTRA_STREAM_COLOR;


    private:
        astra_colorstream_t m_colorStream;
    };

    class ColorFrame : public ImageFrame<RGBPixel, ASTRA_STREAM_COLOR>
    {
    public:
        ColorFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };

    class ColorFrameRaw : public ImageFrame<uint8_t, ASTRA_STREAM_COLOR>
    {
    public:
        ColorFrameRaw(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };
}

#endif // COLOR_H
