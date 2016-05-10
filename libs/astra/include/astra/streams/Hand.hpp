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
#ifndef ASTRA_HAND_HPP
#define ASTRA_HAND_HPP

#include <stdexcept>
#include <cstdint>
#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/hand_capi.h>
#include <astra/Vector.hpp>

namespace astra {

    class HandPoint : public astra_handpoint_t
    {
    public:
        HandPoint(std::int32_t trackingId,
                  astra_handstatus_t status,
                  Vector2i depthPosition,
                  Vector3f worldPosition,
                  Vector3f worldDeltaPosition)
        {
            astra_handpoint_t::trackingId = trackingId;
            astra_handpoint_t::status = status;
            astra_handpoint_t::depthPosition = depthPosition;
            astra_handpoint_t::worldPosition = worldPosition;
            astra_handpoint_t::worldDeltaPosition = worldDeltaPosition;
        }

        HandPoint(const astra_handpoint_t& handPoint)
        {
            *this = handPoint;
        }

        HandPoint& operator=(const ::astra_handpoint_t& handPoint)
        {
            astra_handpoint_t::trackingId = handPoint.trackingId;
            astra_handpoint_t::status = handPoint.status;
            astra_handpoint_t::depthPosition = handPoint.depthPosition;
            astra_handpoint_t::worldPosition = handPoint.worldPosition;
            astra_handpoint_t::worldDeltaPosition = handPoint.worldDeltaPosition;

            return *this;
        }

        inline operator ::astra_handpoint_t*() { return this; }
        inline operator const ::astra_handpoint_t*() const { return this; }

        inline std::int32_t tracking_id() const { return astra_handpoint_t::trackingId; }
        inline astra_handstatus_t status() const { return astra_handpoint_t::status; }
        inline Vector2i depth_position() const { return astra_handpoint_t::depthPosition; }
        inline Vector3f world_position() const { return astra_handpoint_t::worldPosition; }
        inline Vector3f world_delta_position() const { return astra_handpoint_t::worldDeltaPosition; }

    private:
        astra_handpoint_t handPoint_;
        Vector2i depthPosition_;
        Vector3f worldPosition_;
        Vector3f worldDeltaPosition_;
    };

    class HandStream : public DataStream
    {
    public:
        explicit HandStream(astra_streamconnection_t connection)
            : DataStream(connection),
              handStream_(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_HAND;

        bool get_include_candidate_points() const
        {
            bool includeCandidatePoints;
            astra_handstream_get_include_candidate_points(handStream_, &includeCandidatePoints);
            return includeCandidatePoints;
        }

        void set_include_candidate_points(bool includeCandidatePoints)
        {
            astra_handstream_set_include_candidate_points(handStream_, includeCandidatePoints);
        }
    private:
        astra_handstream_t handStream_;
    };

    class HandFrame
    {
    public:
        using HandPointList = std::vector<HandPoint>;

        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_handframe_t handFrame;
                astra_frame_get_handframe_with_subtype(readerFrame, subtype, &handFrame);
                return TFrameType(handFrame);
            }

            return TFrameType(nullptr);
        }

        HandFrame(astra_handframe_t handFrame)
        {
            handFrame_ = handFrame;
            if (handFrame_)
            {
                astra_handframe_get_frameindex(handFrame_, &frameIndex_);

                size_t maxHandCount;
                astra_handframe_get_hand_count(handFrame_, &maxHandCount);

                handPoints_.reserve(maxHandCount);
            }
        }

        bool is_valid() const { return handFrame_ != nullptr; }
        astra_handframe_t handle() const { return handFrame_; }

        size_t handpoint_count() const
        {
            throw_if_invalid_frame();
            verify_handpoints();

            return handPoints_.size();
        }

        const HandPointList& handpoints() const
        {
            throw_if_invalid_frame();
            verify_handpoints();
            return handPoints_;
        }

        astra_frame_index_t frame_index() { throw_if_invalid_frame(); return frameIndex_; }

    private:
        void throw_if_invalid_frame() const
        {
            if (!handFrame_) { throw std::logic_error("Cannot operate on an invalid frame"); }
        }

        void verify_handpoints() const
        {
            if (handPointsInitialized_) { return; }
            handPointsInitialized_ = true;

            astra_handpoint_t* handPtr;
            size_t maxHandCount;

            astra_handframe_get_shared_hand_array(handFrame_, &handPtr, &maxHandCount);

            for (int i = 0; i < maxHandCount; ++i, ++handPtr)
            {
                astra_handpoint_t& p = *handPtr;
                if (p.status != astra_handstatus_t::HAND_STATUS_NOTTRACKING)
                {
                    handPoints_.emplace_back(HandPoint(p));
                }
            }
        }

        // mutable for purposes of lazy computation
        mutable bool handPointsInitialized_{false};
        mutable HandPointList handPoints_;

        astra_handframe_t handFrame_{nullptr};
        astra_frame_index_t frameIndex_;
    };
}

#endif /* ASTRA_HAND_HPP */
