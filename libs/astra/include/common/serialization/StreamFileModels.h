#ifndef STREAMFILEMODELS_H
#define STREAMFILEMODELS_H

namespace astra { namespace serialization {

    struct StreamHeader
    {
        int frameType;
    };

    struct Frame
    {
        int byteLength;
        int frameIndex;
        void* rawFrameWrapper;
    };

    struct FrameDescription
    {
        double framePeriod;
        int bufferLength;
    };

}}

#endif /* STREAMFILEMODELS_H */