#pragma once
#define __QOMA_UNIVERSAL_CALCULATION_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

xoc_uint32_t
qoma_varint_to_u32le(
    const xoc_byte_t * start
);



#if defined(__cplusplus)
}
#endif // defined(__cplusplus)
