#ifndef SKELETON_H
#define SKELETON_H

#include <Astra/Astra.h>
#include <stdexcept>
#include <AstraUL/astraul_ctypes.h>
#include <AstraUL/streams/skeleton_capi.h>
#include <AstraUL/Vector.h>

namespace astra {

    class SkeletonJoint
    {
    public:
        SkeletonJoint(astra_skeleton_joint_t joint)
            : m_joint(joint) {}

        inline astra_joint_status status() { return m_joint.status; }
        inline astra_joint_type type() { return m_joint.jointType; }
        inline const Vector3f position() { return m_joint.position; }

    private:
        astra_skeleton_joint_t m_joint;
    };

    class Skeleton
    {
    public:
        explicit Skeleton(astra_skeleton_t skeleton) :
            m_skeleton(skeleton)
        { }

        inline int32_t trackingId() const { return m_skeleton.trackingId; }
        inline astra_skeleton_status status() const { return m_skeleton.status; }

        inline std::vector<SkeletonJoint> joints()
        {
            verify_jointlist();
            return m_joints;
        }

        void verify_jointlist()
        {
            if (m_jointsInitialized)
            {
                return;
            }

            m_jointsInitialized = true;
            for (size_t i = 0; i < m_skeleton.jointCount; ++i)
            {
                if (m_skeleton.joints[i].status ==
                    ASTRA_JOINT_STATUS_TRACKED)
                {
                    m_joints.push_back(SkeletonJoint(m_skeleton.joints[i]));
                }
            }
        }

    private:
        bool m_jointsInitialized{false};
        astra_skeleton_t m_skeleton;
        std::vector<SkeletonJoint> m_joints;
    };

    using SkeletonList = std::vector<Skeleton>;

    class SkeletonStream : public DataStream
    {
    public:
        explicit SkeletonStream(astra_streamconnection_t connection)
            : DataStream(connection)
        { }

        static const astra_stream_type_t id = ASTRA_STREAM_SKELETON;
    };

    class SkeletonFrame
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

        SkeletonFrame(astra_skeletonframe_t skeletonFrame)
        {
            m_skeletonFrame = skeletonFrame;

            if (m_skeletonFrame)
            {
                astra_skeletonframe_get_frameindex(m_skeletonFrame, &m_frameIndex);

                size_t maxSkeletonCount;
                astra_skeletonframe_get_skeleton_count(m_skeletonFrame, &maxSkeletonCount);

                m_skeletons.reserve(maxSkeletonCount);
            }
        }

        bool is_valid() { return m_skeletonFrame != nullptr; }
        astra_skeletonframe_t handle() { return m_skeletonFrame; }

        size_t skeleton_count()
        {
            throwIfInvalidFrame();
            verify_skeletonlist();
            return m_skeletons.size();
        }

        const SkeletonList& skeletons()
        {
            throwIfInvalidFrame();
            verify_skeletonlist();
            return m_skeletons;
        }

        astra_frame_index_t frameIndex() { throwIfInvalidFrame(); return m_frameIndex; }

    private:
        void throwIfInvalidFrame()
        {
            if (m_skeletonFrame == nullptr)
            {
                throw std::logic_error("Cannot operate on an invalid frame");
            }
        }

        void verify_skeletonlist()
        {
            if (m_skeletonsInitialized)
            {
                return;
            }

            m_skeletonsInitialized = true;

            astra_skeleton_t* skeletonPtr;
            size_t skeletonCount;

            astra_skeletonframe_get_skeletons_ptr(m_skeletonFrame, &skeletonPtr, &skeletonCount);

            for (size_t i = 0; i < skeletonCount; ++i, ++skeletonPtr)
            {
                astra_skeleton_t& p = *skeletonPtr;
                if (p.status != astra_skeleton_status::ASTRA_SKELETON_STATUS_NOT_TRACKED)
                {
                    m_skeletons.push_back(Skeleton(p));
                }
            }
        }

        bool m_skeletonsInitialized{false};
        SkeletonList m_skeletons;
        astra_skeletonframe_t m_skeletonFrame{nullptr};
        astra_frame_index_t m_frameIndex;
    };
}

#endif /* SKELETON_H */
