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
#ifndef SKELETON_TYPES_H
#define SKELETON_TYPES_H

#include <astra_core/capi/astra_types.h>
#include <astra/capi/astra_ctypes.h>

enum astra_joint_type {
    ASTRA_JOINT_TYPE_LEFT_SHOULDER = 1,
    ASTRA_JOINT_TYPE_LEFT_ELBOW = 2,
    ASTRA_JOINT_TYPE_LEFT_HAND = 3,
    ASTRA_JOINT_TYPE_RIGHT_SHOULDER = 4,
    ASTRA_JOINT_TYPE_RIGHT_ELBOW = 5,
    ASTRA_JOINT_TYPE_RIGHT_HAND = 6,
    ASTRA_JOINT_TYPE_HEAD = 7,
    ASTRA_JOINT_TYPE_HIP = 8
};

enum astra_skeleton_status {
    ASTRA_SKELETON_STATUS_NOT_TRACKED = 0,
    ASTRA_SKELETON_STATUS_TRACKED = 1
};

enum astra_joint_status {
    ASTRA_JOINT_STATUS_NOT_TRACKED = 0,
    ASTRA_JOINT_STATUS_TRACKED = 1
};

const size_t ASTRA_MAX_JOINTS = 20;

typedef struct _astra_skeleton_joint {
    int32_t trackingId;
    astra_joint_status status;
    astra_joint_type jointType;
    astra_vector3f_t position;
} astra_skeleton_joint_t;

typedef struct _astra_skeleton {
    int32_t trackingId;
    size_t jointCount;
    astra_skeleton_status status;
    astra_skeleton_joint_t joints[ASTRA_MAX_JOINTS];
} astra_skeleton_t;

struct _astra_skeletonframe {
    astra_frame_t* frame;
    size_t skeletonCount;
    astra_skeleton_t* skeletons;
};

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4200 )
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc99-extensions"
#endif

typedef struct _astra_skeletonframe_wrapper {
    _astra_skeletonframe frame;
    char frame_data[];
} astra_skeletonframe_wrapper_t;

#if defined(_MSC_VER)
#pragma warning( pop )
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

typedef struct _astra_skeletonframe* astra_skeletonframe_t;
typedef astra_streamconnection_t astra_skeletonstream_t;

typedef struct _astra_imageframe* astra_debug_skeletonframe_t;
typedef astra_streamconnection_t astra_debug_skeletonstream_t;

#endif /* SKELETON_TYPES_H */
