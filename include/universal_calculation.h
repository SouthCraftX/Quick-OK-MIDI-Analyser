#pragma once
#define __QOMA_UNIVERSAL_CALCULATION_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

// We will move it to one byte after the delta time VLA
qo_uint32_t
qoma_delta_time_read(
    const qo_byte_t ** pp_start
);



#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
