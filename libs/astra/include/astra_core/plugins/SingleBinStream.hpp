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
#ifndef ASTRA_SINGLEBIN_STREAM_HPP
#define ASTRA_SINGLEBIN_STREAM_HPP

#include "PluginStream.hpp"
#include "StreamBin.hpp"
#include <memory>

namespace astra { namespace plugins {

    template<typename TFrameType>
    class single_bin_stream : public astra::plugins::stream
    {
    public:
        single_bin_stream(PluginServiceProxy& pluginService,
                          astra_streamset_t streamSet,
                          StreamDescription description,
                          size_t bufferSize)
            : stream(pluginService,
                     streamSet,
                     description)
        {
            bin_ = astra::make_unique<bin_type>(pluginService,
                                                get_handle(),
                                                sizeof(TFrameType) + bufferSize);
        }

        using frame_type = TFrameType;

        bool has_connections()
        {
            return bin_->has_connections();
        }

        TFrameType* begin_write(size_t frameIndex)
        {
            return bin_->begin_write(frameIndex);
        }

        void end_write()
        {
            return bin_->end_write();
        }

    protected:
        virtual void on_connection_added(astra_streamconnection_t connection) override
        {
            bin_->link_connection(connection);
        }

        virtual void on_connection_removed(astra_bin_t bin,
                                           astra_streamconnection_t connection) override
        {
            bin_->unlink_connection(connection);
        }

    private:
        using bin_type = stream_bin<TFrameType>;
        std::unique_ptr<bin_type> bin_;
    };
}}

#endif /* ASTRA_SINGLEBIN_STREAM_HPP */
