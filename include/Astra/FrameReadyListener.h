#ifndef FRAMEREADYLISTENER_H
#define FRAMEREADYLISTENER_H

namespace astra {

    class StreamReader;
    class Frame;

    class FrameReadyListener
    {
    public:
        virtual ~FrameReadyListener() = default;
        virtual void on_frame_ready(StreamReader& reader, Frame& frame) = 0;
    };

    inline bool operator==(const FrameReadyListener& l, const FrameReadyListener& r)
    {
        return &l == &r;
    }
}

#endif /* FRAMEREADYLISTENER_H */
