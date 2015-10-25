#ifndef HOST_EVENTS_H
#define HOST_EVENTS_H

#include "astra_defines.h"
#include "astra_types.h"
#include <stddef.h>
#include <stdint.h>

ASTRA_BEGIN_DECLS

ASTRA_API astra_status_t astra_notify_host_event(astra_event_id id, const void* data, size_t dataSize);
ASTRA_API astra_status_t astra_notify_resource_available(const char* resourceURI);
ASTRA_API astra_status_t astra_notify_resource_unavailable(const char* resourceURI);

enum {
    ASTRA_EVENT_RESOURCE_AVAILABLE = 1,
    ASTRA_EVENT_RESOURCE_UNAVAILABLE = 2
};

ASTRA_END_DECLS

#endif /* HOST_EVENTS_H */
