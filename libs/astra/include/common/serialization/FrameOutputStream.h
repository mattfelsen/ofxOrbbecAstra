#ifndef FRAMEOUTPUTSTREAM_H
#define FRAMEOUTPUTSTREAM_H

#include "StreamFileModels.h"
#include <cstdint>

namespace astra { namespace serialization {

    class FrameOutputStream
    {
    public:
        FrameOutputStream() { }
        virtual ~FrameOutputStream() { }

        virtual void stage_frame(Frame& frame) = 0;
        virtual void stage_frame_description(FrameDescription& frameDesc) = 0;
        virtual void stage_stream_header(StreamHeader& streamHeader) = 0;
        virtual bool write_frame() = 0;
        virtual bool write_frame_description() = 0;
        virtual bool write_stream_header() = 0;
    };

}}

#endif /* FRAMEOUTPUTSTREAM_H */