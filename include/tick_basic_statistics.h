#pragma once
#define __QOMA_TICK_BASIC_STATISTICS_H__

#include "track.h"

#if defined(__cplusplus)
extern "C" {
#endif

union _QOMA_TickBasicStatisticsMono32
{
    struct {
        qo_uint32_t   noteon_count;
        qo_uint32_t   noteoff_count;
        qo_uint32_t   tempo_change_us;   //< Quarter Note per millionsecond .0 indicates no tempo change
    };
    struct
    {
        qo_uint32_t   noteinfo[2];
        qo_uint32_t   tempo_change_us;
    };
};
typedef union _QOMA_TickBasicStatisticsMono32 QOMA_TickBasicStatisticsMono32;

union _QOMA_TickBasicStatisticsMono64
{
    struct 
    {
        qo_uint64_t   noteon_count;
        qo_uint64_t   noteoff_count;
        qo_uint32_t   tempo_change_us;   //< Tick per .0 indicates no tempo change. Unit: microsecond
    };
    struct 
    {
        qo_uint64_t   noteinfo[2];
        qo_uint32_t   tempo_change_us;
    }
    
};
typedef struct _QOMA_TickBasicStatisticsMono64 QOMA_TickBasicStatisticsMono64;

// The contects of this structure are not exposed to the user.
struct _QOMA_TickBasicStatistics;
typedef struct _QOMA_TickBasicStatistics QOMA_TickBasicStatistics;

#if QOMA_64BIT_AVAILABLE
typedef QOMA_TickBasicStatisticsMono64 QOMA_TickBasicStatisticsMono;
#else
typedef QOMA_TickBasicStatisticsMono32 QOMA_TickBasicStatisticsMono;
#endif

/// @brief  Create a new QOMA_TickBasicStatistics object.
/// @return The pointer to the newly created object. NULL if failed.
/// @sa     qoma_tick_basic_statistics_unref()
QOMA_TickBasicStatistics *
qoma_tick_basic_statistics_new();

/// @brief  Increase the reference count of the statistics object.
/// @param  p_tick_basic_statistics Pointer to the statistics object.
void
qoma_tick_basic_statistics_ref(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
) QO_NONNULL(1);

/// @brief  Reduce the reference count of the statistics object. If the reference
///         count reaches zero, the object will be destroyed.
/// @param  p_tick_basic_statistics Pointer to the statistics object. NULL is
///         allowed, in which case this function does nothing.
/// @sa     qoma_tick_basic_statistics_new()
void
qoma_tick_basic_statistics_unref(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
);

/// @brief  Get the first mono of the statistics object.
/// @param  p_tick_basic_statistics Pointer to the statistics object.
/// @return The pointer to the first mono. The pointer may be equal to end if
///         the statistics object is empty.
/// @sa     qoma_tick_basic_statistics_get_end()
QOMA_TickBasicStatisticsMono *
qoma_tick_basic_statistics_get_begin(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
) QO_NONNULL(1);

/// @brief  Get the last mono of the statistics object.
/// @param  p_tick_basic_statistics Pointer to the statistics object.
/// @return The pointer to the last mono. The pointer may be equal to begin if
///         the statistics object is empty.
/// @sa     qoma_tick_basic_statistics_get_begin()
QOMA_TickBasicStatisticsMono *
qoma_tick_basic_statistics_get_end(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
) QO_NONNULL(1);

/// @brief  Extend the statistics object to hold more monos.
/// @param  pp_tick_basic_statistics Pointer to the pointer to the statistics
///         object. The pointer will be updated to point to the new object.
/// @param  mono_count The number of monos to extend.
/// @return qo_true if succeeded. qoma_false if failed.
qo_bool_t
qoma_tick_basic_statistics_extend(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics ,
    qo_size_t                 mono_count
) QO_NONNULL(1);

/// @brief  Add a mono to the statistics object.
/// @param  pp_tick_basic_statistics Pointer to the pointer to the statistics
///         object. The pointer may be updated to point to the new object if
///         the object needs to be extended.
/// @param  mono The mono to add.
qo_bool_t
qoma_tick_basic_statistics_add(
    QOMA_TickBasicStatistics **     pp_tick_basic_statistics ,
    QOMA_TickBasicStatisticsMono    mono
) QO_NONNULL(1);

/// @brief  Add a mono to the statistics object at the specified index.
/// @param  pp_tick_basic_statistics Pointer to the pointer to the statistics
///         object. The pointer may be updated to point to the new object if
///         the object needs to be extended.
/// @param  index The index to add the mono.
qo_bool_t
qoma_tick_basic_statistics_add_at(
    QOMA_TickBasicStatistics **     pp_tick_basic_statistics ,
    qo_size_t                     index ,
    QOMA_TickBasicStatisticsMono    mono
) QO_NONNULL(1);

QOMA_TickBasicStatisticsMono *
qoma_tick_basic_statistics_reach(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics ,
    qoma_tick_t                 index
) QO_NONNULL(1);

/// @brief  Merge the source statistics object into the target statistics object.
/// @param  pp_target Pointer to the pointer to the target statistics object.
///         The pointer may be updated to point to the new object if the
///         object needs to be extended.
/// @param  p_source Pointer to the source statistics object.
/// @return qo_true if succeeded. qoma_false if pp_target needs to be extended
///         but failed.
qo_bool_t
qoma_tick_basic_statistics_merge(
    QOMA_TickBasicStatistics **     pp_target ,
    QOMA_TickBasicStatistics *      p_source
) QO_NONNULL(1 , 2);

/// @brief  Analyse the track and update the statistics object.
/// @param  pp_tick_basic_statistics Pointer to the pointer to the statistics
///         object. The pointer may be updated to point to the new object if
///         the object needs to be extended.
/// @param  p_track Pointer to the track to analyse.
/// @return The status of the analysis.
/// @note   If allocation fails during the analysis, the content of the
///         statistics object is undefined.
qo_stat_t
qoma_track_analyse(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics ,
    QOMA_Track * p_track
) QO_NONNULL(1 , 2);

/// @brief  Iterate over the monos of the statistics object.
#define QOMA_TRACK_BASIC_STATISTICS_ITERATE(p_tick_basic_statistics , p_mono) \
    for (p_mono = qoma_tick_basic_statistics_get_begin(p_tick_basic_statistics) , \
         p_end = qoma_tick_basic_statistics_get_end(p_tick_basic_statistics) ; \
         p_mono != p_end ; \
         p_mono++)


#if defined(__cplusplus)
}
#endif