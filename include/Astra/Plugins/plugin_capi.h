#ifndef PLUGIN_CAPI_H
#define PLUGIN_CAPI_H

#include <Astra/astra_capi.h>
#include <Astra/Plugins/plugin_callbacks.h>
#include <Astra/Plugins/StreamServiceProxyBase.h>
#include <Astra/Plugins/PluginServiceProxyBase.h>

#if ! defined(__ANDROID__) && (defined(__GNUC__) || defined(__clang__))
#define PACK_STRUCT __attribute__((packed))
#else
#define PACK_STRUCT
#endif

struct _astra_streamconnection {
    astra_streamconnection_handle_t handle;
    astra_stream_desc_t desc;
};

struct _astra_reader_callback_id {
    astra_reader_t reader;
    astra_callback_id_t callbackId;
};


#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

struct _astra_frame {
    size_t byteLength;
    astra_frame_index_t frameIndex;
    union {
        void* data;
        uint64_t pad0;
    };
} PACK_STRUCT;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif /* PLUGIN_CAPI_H */
