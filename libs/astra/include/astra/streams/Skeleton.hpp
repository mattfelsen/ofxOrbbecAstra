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
#ifndef ASTRA_SKELETON_HPP
#define ASTRA_SKELETON_HPP

#include <stdexcept>
#include <astra_core/astra_core.hpp>
#include <astra/capi/astra_ctypes.h>
#include <astra/capi/streams/skeleton_capi.h>
#include <astra/Vector.hpp>

namespace astra {

    class skeleton_joint
    {
    public:
        skeleton_joint(astra_skeleton_joint_t joint)
            : joint_(joint) {}

        inline astra_joint_status status() { return joint_.status; }
        inline astra_joint_type type() { return joint_.jointType; }
        inline const Vector3f position() { return joint_.position; }

    private:
        astra_skeleton_joint_t joint_;
    };

    class skeleton
    {
    public:
        explicit skeleton(astra_skeleton_t skeleton) :
            skeleton_(skeleton)
        { }

        inline int32_t trackingId() const { return skeleton_.trackingId; }
        inline astra_skeleton_status status() const { return skeleton_.status; }

        inline std::vector<skeleton_joint> joints()
        {
            verify_jointlist();
            return joints_;
        }

        void verify_jointlist()
        {
            if (jointsInitialized_)
            {
                return;
            }

            jointsInitialized_ = true;
            for (size_t i = 0; i < skeleton_.jointCount; ++i)
            {
                if (skeleton_.joints[i].status ==
                    ASTRA_JOINT_STATUS_TRACKED)
                {
                    joints_.push_back(skeleton_joint(skeleton_.joints[i]));
                }
            }
        }

    private:
        bool jointsInitialized_{false};
        astra_skeleton_t skeleton_;
        std::vector<skeleton_joint> joints_;
    };

    using SkeletonList = std::vector<skeleton>;

    class skeletonstream : public DataStream
    {
    public:
        explicit skeletonstream(astra_streamconnection_t connection)
            : DataStream(connection),
              skeletonStream_(reinterpret_cast<astra_skeletonstream_t>(connection))
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_SKELETON;

        // temporary band-pass variables (until segmentation)
        void set_zMin(std::uint16_t zMin)
        {
            astra_skeletonstream_set_z_min(skeletonStream_, zMin);
        }

        const std::uint16_t zMin()
        {
            std::uint16_t zMin = 0;
            astra_skeletonstream_get_z_min(skeletonStream_, &zMin);

            return zMin;
        }

        void set_zMax(std::uint16_t zMax)
        {
            astra_skeletonstream_set_z_max(skeletonStream_, zMax);
        }

        // temporary band-pass variables (until segmentation)
        const std::uint16_t zMax()
        {
            std::uint16_t zMax = 65535;
            astra_skeletonstream_get_z_max(skeletonStream_, &zMax);

            return zMax;
        }

    private:
        astra_skeletonstream_t skeletonStream_{nullptr};
    };

    class skeletonframe
    {
    public:
        template<typename TFrameType>
        static TFrameType acquire(astra_reader_frame_t readerFrame,
                                  astra_stream_subtype_t subtype)
        {
            if (readerFrame != nullptr)
            {
                astra_skeletonframe_t skeletonFrame;
                astra_frame_get_skeletonframe(readerFrame, &skeletonFrame);
                return TFrameType(skeletonFrame);
            }

            return TFrameType(nullptr);
        }

        skeletonframe(astra_skeletonframe_t skeletonFrame)
        {
            skeletonFrame_ = skeletonFrame;

            if (skeletonFrame_)
            {
                astra_skeletonframe_get_frameindex(skeletonFrame_, &frameIndex_);

                size_t maxSkeletonCount;
                astra_skeletonframe_get_skeleton_count(skeletonFrame_, &maxSkeletonCount);

                skeletons_.reserve(maxSkeletonCount);
            }
        }

        bool is_valid() { return skeletonFrame_ != nullptr; }
        astra_skeletonframe_t handle() { return skeletonFrame_; }

        size_t skeleton_count()
        {
            throwIfInvalidFrame();
            verify_skeletonlist();
            return skeletons_.size();
        }

        const SkeletonList& skeletons()
        {
            throwIfInvalidFrame();
            verify_skeletonlist();
            return skeletons_;
        }

        astra_frame_index_t frameIndex() { throwIfInvalidFrame(); return frameIndex_; }

    private:
        void throwIfInvalidFrame()
        {
            if (skeletonFrame_ == nullptr)
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }

        void verify_skeletonlist()
        {
            if (skeletonsInitialized_)
            {
                return;
            }

            skeletonsInitialized_ = true;

            astra_skeleton_t* skeletonPtr;
            size_t skeletonCount;

            astra_skeletonframe_get_skeletons_ptr(skeletonFrame_, &skeletonPtr, &skeletonCount);

            for (size_t i = 0; i < skeletonCount; ++i, ++skeletonPtr)
            {
                astra_skeleton_t& p = *skeletonPtr;
                if (p.status != astra_skeleton_status::ASTRA_SKELETON_STATUS_NOT_TRACKED)
                {
                    skeletons_.push_back(astra::skeleton(p));
                }
            }
        }

        bool skeletonsInitialized_{false};
        SkeletonList skeletons_;
        astra_skeletonframe_t skeletonFrame_{nullptr};
        astra_frame_index_t frameIndex_;
    };
}

#endif /* ASTRA_SKELETON_HPP */
