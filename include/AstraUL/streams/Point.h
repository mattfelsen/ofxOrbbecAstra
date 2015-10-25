#ifndef POINT_H
#define POINT_H

#include <Astra/Astra.h>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/point_capi.h>
#include <AstraUL/streams/Image.h>

namespace astra {

    class PointStream : public DataStream
    {
    public:
        PointStream()
        {}

        explicit PointStream(astra_streamconnection_t connection)
            : DataStream(connection)
        {
            m_pointStream = reinterpret_cast<astra_pointstream_t>(connection);
        }

        static const astra_stream_type_t id = ASTRA_STREAM_POINT;

    private:
        astra_pointstream_t m_pointStream;
    };

    class PointFrame : public ImageFrame<Vector3f, ASTRA_STREAM_POINT>
    {
    public:
        PointFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_POINT)
        {}
    };
}

#endif // POINT_H
