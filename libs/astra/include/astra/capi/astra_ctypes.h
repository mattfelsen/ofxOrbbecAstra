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
#ifndef ASTRAUL_CTYPES_H
#define ASTRAUL_CTYPES_H

#include <stdint.h>

typedef struct _astra_vector2i {
    int32_t x;
    int32_t y;
} astra_vector2i_t;

typedef struct _astra_vector2f {
    float x;
    float y;
} astra_vector2f_t;

typedef struct _astra_vector3f {
    float x;
    float y;
    float z;
} astra_vector3f_t;

typedef struct _astra_vector3i {
    int32_t x;
    int32_t y;
    int32_t z;
} astra_vector3i_t;

enum astra_core_stream_types {
    ASTRA_STREAM_DEPTH = 1,
    ASTRA_STREAM_COLOR = 2,
    ASTRA_STREAM_INFRARED = 3,
    ASTRA_STREAM_HAND = 4,
    ASTRA_STREAM_SKELETON = 5,
    ASTRA_STREAM_STYLIZED_DEPTH = 6,
    ASTRA_STREAM_POINT = 7,
    ASTRA_STREAM_DEBUG_HAND = 3001,
};

#endif /* ASTRAUL_CTYPES_H */
