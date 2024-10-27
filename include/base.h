#pragma once
#define __QOMA_BASE_H__

#include "xoceanlib/include/base.h"

#define qoma_true   xoc_true
#define qoma_false  xoc_false

#if XOC_SYSTEM_BIT(64)
#define QOMA_64BIT_AVALIABLE 1
#else
#define QOMA_64BIT_AVALIABLE 0
#endif

typedef xoc_uint8_t     qoma_uint8_t;
typedef xoc_uint16_t    qoma_uint16_t;
typedef xoc_uint32_t    qoma_uint32_t;
typedef xoc_uint64_t    qoma_uint64_t;

typedef xoc_int8_t      qoma_int8_t;
typedef xoc_int16_t     qoma_int16_t;
typedef xoc_int32_t     qoma_int32_t;
typedef xoc_int64_t     qoma_int64_t;

typedef xoc_flag8_t     qoma_flag8_t;
typedef xoc_flag16_t    qoma_flag16_t;
typedef xoc_flag32_t    qoma_flag32_t;
typedef xoc_flag64_t    qoma_flag64_t;

typedef xoc_fp32_t      qoma_fp32_t;
typedef xoc_fp64_t      qoma_fp64_t;

typedef xoc_size_t      qoma_size_t;
typedef xoc_ssize_t     qoma_ssize_t;
typedef xoc_offset_t    qoma_offset_t;
typedef xoc_bool_t      qoma_bool_t;
typedef xoc_stat_t      qoma_stat_t;
typedef xoc_byte_t      qoma_byte_t;

typedef xoc_uintmax_t   qoma_uintmax_t;
typedef xoc_intmax_t    qoma_intmax_t;

typedef xoc_cstring_t   qoma_cstring_t;
typedef xoc_ccstring_t  qoma_ccstring_t;

typedef xoc_pointer_t   qoma_pointer_t;

typedef xoc_ref_count_t qoma_ref_count_t;

typedef xoc_flag8_t     qoma_midi_format_t;
typedef xoc_uint16_t    qoma_midi_resolution_t;
typedef xoc_uint16_t    qoma_track_count_t;

#if XOC_SYSTEM_BIT(64)
typedef xoc_fp64_t      qoma_tempo_t;
#else
typedef xoc_fp32_t      qoma_tempo_t;
#endif

#define QOMA_DEPRCATED      XOC_DEPRECATED
#define QOMA_THREAD_LOCAL   XOC_THREAD_LOCAL
#define QOMA_NODISCARD      XOC_NODISCARD
#define QOMA_NONNULL        XOC_NONNULL
#define QOMA_FLATTEN        XOC_FLATTEN
#define QOMA_NO_INLINE      XOC_NO_INLINE
#define QOMA_LIKELY         XOC_LIKELY
#define QOMA_UNLIKELY       XOC_UNLIKELY
#define QOMA_RESTRICT       XOC_RESTRICT
#define QOMA_UNREACHABLE    XOC_UNREACHABLE
#define QOMA_NORETURN       XOC_NORETURN
#define QOMA_FALLTHROUGH    XOC_FALLTHROUGH
#define QOMA_PACKED         XOC_PACKED
#define QOMA_EXPORT         XOC_EXPORT
#define QOMA_IMPORT         XOC_IMPORT
#define QOMA_PURE           XOC_PURE
#define QOMA_NO_SIDE_EFFECTS   XOC_NO_SIDE_EFFECTS


#define QOMA_FORCE_INLINE   XOC_FORCE_INLINE
#define QOMA_ALIGNAS        XOC_ALIGNAS

#define QOMA_NOT_SUPPORTED      XOC_NOT_SUPPORTED
#define QOMA_BAD_IO             XOC_BAD_IO
#define QOMA_NOT_FOUND          XOC_NOT_FOUND
#define QOMA_BAD_PATH           XOC_BAD_PATH
#define QOMA_OUT_OF_MEMORY      XOC_OUT_OF_MEMORY
#define QOMA_INVALID_ARG        XOC_INVALID_ARG
#define QOMA_BAD_FILE           XOC_BAD_FILE
#define QOMA_FILE_TOO_BIG       XOC_FILE_TOO_BIG
#define QOMA_NO_RESOURCE        XOC_NO_RESOURCE
#define QOMA_DISK_NO_SPACE      XOC_DISK_NO_SPACE
#define QOMA_TARGET_BUSY        XOC_TARGET_BUSY
#define QOMA_ACCESS_VIOLATED    XOC_ACCESS_VIOLATED

// Describe whether the argument is in or out.
#define _QOMA_IN_
#define _QOMA_OUT_
#define _QOMA_INOUT_

