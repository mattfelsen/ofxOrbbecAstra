#ifndef DEPTH_H
#define DEPTH_H

#include <Astra/Astra.h>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/depth_capi.h>
#include <AstraUL/streams/Image.h>
#include <AstraUL/Vector.h>

namespace astra {

    class CoordinateMapper
    {
    public:
        CoordinateMapper(astra_depthstream_t depthStream)
            : m_depthStream(depthStream)
        { }

        CoordinateMapper(const CoordinateMapper& rhs)
        {
            this->m_depthStream = rhs.m_depthStream;
        }

        CoordinateMapper operator=(const CoordinateMapper& rhs)
        {
            this->m_depthStream = rhs.m_depthStream;
            return *this;
        }

        Vector3f convert_depth_to_world(astra::Vector3f depthPosition) const
        {
            float worldX, worldY, worldZ;
            astra_convert_depth_to_world(m_depthStream,
                                         depthPosition.x,
                                         depthPosition.y,
                                         depthPosition.z,
                                         &worldX, &worldY, &worldZ);

            return Vector3f(worldX, worldY, worldZ);
        }

        Vector3f convert_world_to_depth(Vector3f worldPosition) const
        {
            float depthX, depthY, depthZ;
            astra_convert_world_to_depth(m_depthStream,
                                         worldPosition.x,
                                         worldPosition.y,
                                         worldPosition.z,
                                         &depthX, &depthY, &depthZ);

            return Vector3f(depthX, depthY, depthZ);
        }

        void convert_depth_to_world(float  depthX, float  depthY, float  depthZ,
                                    float* worldX, float* worldY, float* worldZ) const
        {
            astra_convert_depth_to_world(m_depthStream, depthX, depthY, depthZ,
                                         worldX, worldY, worldZ);
        }

        void convert_world_to_depth(float  worldX, float  worldY, float  worldZ,
                                    float* depthX, float* depthY, float* depthZ) const
        {
            astra_convert_world_to_depth(m_depthStream,
                                         worldX, worldY, worldZ,
                                         depthX, depthY, depthZ);
        }

    private:
        astra_depthstream_t m_depthStream;
    };

    class DepthStream : public ImageStream
    {
    public:
        explicit DepthStream(astra_streamconnection_t connection)
            : ImageStream(connection),
              m_depthStream(reinterpret_cast<astra_depthstream_t>(connection)),
              m_coordinateMapper(reinterpret_cast<astra_depthstream_t>(connection))
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEPTH;

        conversion_cache_t depth_to_world_data()
        {
            conversion_cache_t data;
            astra_depthstream_get_depth_to_world_data(m_depthStream, &data);

            return data;
        }

        bool registration_enabled()
        {
            bool enabled = false;
            astra_depthstream_get_registration(m_depthStream, &enabled);

            return enabled;
        }

        void enable_registration(bool enable)
        {
            astra_depthstream_set_registration(m_depthStream, enable);
        }

        const CoordinateMapper& coordinateMapper() { return m_coordinateMapper; };

    private:
        astra_depthstream_t m_depthStream;
        CoordinateMapper m_coordinateMapper;
    };

    class DepthFrame : public ImageFrame<int16_t, ASTRA_STREAM_DEPTH>
    {
    public:
        DepthFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_DEPTH_MM)
        {}

    };
}

#endif /* DEPTH_H */
