#ifndef ASTRA_H
#define ASTRA_H

#include <Astra/StreamSet.h>
#include <Astra/StreamDescription.h>
#include <Astra/Frame.h>
#include <Astra/FrameReadyListener.h>
#include <Astra/StreamReader.h>
#include <Astra/DataStream.h>
#include <Astra/astra_cxx_make_unique.hpp>

namespace astra {

    class Astra
    {
    public:
        static astra_status_t initialize()
        {
            return astra_initialize();
        }

        static astra_status_t terminate()
        {
            return astra_terminate();
        }
    };

}

#endif // ASTRA_H
