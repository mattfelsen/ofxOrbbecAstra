#ifndef FRAMESTREAMREADER_H
#define FRAMESTREAMREADER_H

#include "StreamFileModels.h"
#include "FrameInputStream.h"
#include "../clock/Pulser.h"

namespace astra { namespace serialization {

    FrameInputStream* open_frame_input_stream(const char* path);

    class FrameStreamReader
    {
    public:
        FrameStreamReader(FrameInputStream* frameStream);
        ~FrameStreamReader();

        void close();
        bool read();
        bool seek(int numberOfFrames);
        int get_stream_type();
        int get_buffer_length();
        bool is_end_of_file();
        Frame& peek();
        FrameInputStream* get_frame_input_stream();

    private:

        FrameInputStream* m_inputStream;
        FrameDescription* m_frameDescription;
        StreamHeader* m_streamHeader;
        Frame* m_frame;
        clock::Pulser m_pulser;

        bool m_isEndOfFile{ false };
    };
}}

#endif /* FRAMESTREAMREADER_H */