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
#ifndef ASTRA_HAND_DEBUG_HPP
#define ASTRA_HAND_DEBUG_HPP

#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/hand_capi.h>

namespace astra {

    using DebugHandViewType = astra_debug_hand_view_type_t;

    class DebugHandStream : public DataStream
    {
    public:
        explicit DebugHandStream(astra_streamconnection_t connection)
            : DataStream(connection),
              debugHandStream_(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEBUG_HAND;

        void set_view_type(DebugHandViewType view)
        {
            astra_debug_handstream_set_view_type(debugHandStream_, view);
        }

        void set_use_mouse_probe(bool useMouseProbe)
        {
            astra_debug_handstream_set_use_mouse_probe(debugHandStream_, useMouseProbe);
        }

        void set_mouse_position(Vector2f position)
        {
            astra_debug_handstream_set_mouse_position(debugHandStream_, position);
        }

        void set_pause_input(bool pauseInput)
        {
            astra_debug_handstream_set_pause_input(debugHandStream_, pauseInput);
        }

        void set_lock_spawn_point(bool lockSpawnPoint)
        {
            astra_debug_handstream_set_lock_spawn_point(debugHandStream_, lockSpawnPoint);
        }

        DebugHandViewType get_view_type() const
        {
            DebugHandViewType view;
            astra_debug_handstream_get_view_type(debugHandStream_, &view);
            return view;
        }

    private:
        astra_debug_handstream_t debugHandStream_;
    };

    class DebugHandFrame : public ImageFrame<RgbPixel, ASTRA_STREAM_DEBUG_HAND>
    {
    public:
        DebugHandFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };
}

#endif /* ASTRA_HAND_DEBUG_HPP */
