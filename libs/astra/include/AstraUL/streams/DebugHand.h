#ifndef HANDDEBUG_H
#define HANDDEBUG_H

#include <Astra/Astra.h>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/hand_capi.h>

namespace astra {

    using DebugHandViewType = astra_debug_hand_view_type_t;

    class DebugHandStream : public DataStream
    {
    public:
        explicit DebugHandStream(astra_streamconnection_t connection)
            : DataStream(connection),
            m_debugHandStream(connection)
            { }

        static const astra_stream_type_t id = ASTRA_STREAM_DEBUG_HAND;

        void set_view_type(DebugHandViewType view)
        {
            astra_debug_handstream_set_view_type(m_debugHandStream, view);
        }

        void set_use_mouse_probe(bool useMouseProbe)
        {
            astra_debug_handstream_set_use_mouse_probe(m_debugHandStream, useMouseProbe);
        }

        void set_mouse_position(Vector2f position)
        {
            astra_debug_handstream_set_mouse_position(m_debugHandStream, position);
        }

        void set_pause_input(bool pauseInput)
        {
            astra_debug_handstream_set_pause_input(m_debugHandStream, pauseInput);
        }

        void set_lock_spawn_point(bool lockSpawnPoint)
        {
            astra_debug_handstream_set_lock_spawn_point(m_debugHandStream, lockSpawnPoint);
        }

        DebugHandViewType get_view_type()
        {
            DebugHandViewType view;
            astra_debug_handstream_get_view_type(m_debugHandStream, &view);
            return view;
        }

    private:
        astra_debug_handstream_t m_debugHandStream;
    };

    class DebugHandFrame : public ImageFrame<RGBPixel, ASTRA_STREAM_DEBUG_HAND>
    {
    public:
        DebugHandFrame(astra_imageframe_t frame)
            : ImageFrame(frame, ASTRA_PIXEL_FORMAT_RGB888)
        {}
    };
}

#endif /* HANDDEBUG_H */
