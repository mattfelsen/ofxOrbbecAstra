// This file is part of the Orbbec Astra SDK [https://orbbec3d.com]
// Copyright (c) 2015 Orbbec 3D
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Be excellent to each other.
#ifndef ASTRA_DEPTH_HPP
#define ASTRA_DEPTH_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/depth_capi.h>
#include <astra/streams/Image.hpp>
#include <astra/Vector.hpp>

namespace astra {

    class CoordinateMapper
    {
    public:
        CoordinateMapper(astra_depthstream_t depthStream)
            : depthStream_(depthStream)
        { }

        CoordinateMapper(const CoordinateMapper& rhs)
        {
            this->depthStream_ = rhs.depthStream_;
        }

        CoordinateMapper operator=(const CoordinateMapper& rhs)
        {
            this->depthStream_ = rhs.depthStream_;
            return *this;
        }

        astra::Vector3f convert_depth_to_world(astra::Vector3f depthPosition) const
        {
            float worldX, worldY, worldZ;
            astra_convert_depth_to_world(depthStream_,
                                         depthPosition.x,
                                         depthPosition.y,
                                         depthPosition.z,
                                         &worldX, &worldY, &worldZ);

            return Vector3f(worldX, worldY, worldZ);
        }

        Vector3f convert_world_to_depth(Vector3f worldPosition) const
        {
            float depthX, depthY, depthZ;
            astra_convert_world_to_depth(depthStream_,
                                         worldPosition.x,
                                         worldPosition.y,
                                         worldPosition.z,
                                         &depthX, &depthY, &depthZ);

            return Vector3f(depthX, depthY, depthZ);
        }

        void convert_depth_to_world(float  depthX, float  depthY, float  depthZ,
                                    float* worldX, float* worldY, float* worldZ) const
        {
            astra_convert_depth_to_world(depthStream_, depthX, depthY, depthZ,
                                         worldX, worldY, worldZ);
        }

        void convert_world_to_depth(float  worldX, float  worldY, float  worldZ,
                                    float* depthX, float* depthY, float* depthZ) const
        {
            astra_convert_world_to_depth(depthStream_,
                                         worldX, worldY, worldZ,
                                         depthX, depthY, depthZ);
        }

    private:
        astra_depthstream_t depthStream_;
    };

    class DepthStream : public ImageStream
    {
    public:
        explicit DepthStream(astra_streamconnection_t connection)
            : ImageStream(connection),
              depthStream_(reinterpret_cast<astra_depthstream_t>(connection)),
              coordinateMapper_(reinterpret_cast<astra_depthstream_t>(connection))
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEPTH;

        conversion_cache_t depth_to_world_data() const
        {
            conversion_cache_t data;
            astra_depthstream_get_depth_to_world_data(depthStream_, &data);

            return data;
        }

        bool registration_enabled() const
        {
            bool enabled = false;
            astra_depthstream_get_registration(depthStream_, &enabled);

            return enabled;
        }

        void enable_registration(bool enable)
        {
            astra_depthstream_set_registration(depthStream_, enable);
        }

        const CoordinateMapper& coordinateMapper() const { return coordinateMapper_; };

    private:
        astra_depthstream_t depthStream_;
        CoordinateMapper coordinateMapper_;
    };

    class DepthFrame : public ImageFrame<int16_t, ASTRA_STREAM_DEPTH>
    {
    public:
        DepthFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_DEPTH_MM)
        {}

    };
}

#endif /* ASTRA_DEPTH_HPP */
