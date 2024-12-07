#pragma once
#define __QOMA_TIME_BASED_STATISTICS_H__

#include "tick_basic_statistics.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

struct _QOMA_TimeBasedStatisticsMono32
{
    qo_uint32_t   noteon;        //< The number of noteon events in this duration
    qo_uint32_t   polyphony;     //< The number of notes that are played simultaneously
    qoma_fp32_t     bpm;           //< Beats per minute
};
typedef struct _QOMA_TimeBasedStatisticsMono32 QOMA_TimeBasedStatisticsMono32;

struct _QOMA_TimeBasedStatisticsMono64
{
    qo_uint64_t   noteon;        //< The number of noteon events in this duration
    qo_uint64_t   polyphony;     //< The number of notes that are played simultaneously
    qoma_fp64_t     bpm;           //< Beats per minute
};
typedef struct _QOMA_TimeBasedStatisticsMono64 QOMA_TimeBasedStatisticsMono64;

#if QOMA_64BIT_AVAILABLE
typedef QOMA_TimeBasedStatisticsMono64 QOMA_TimeBasedStatisticsMono;
#else
typedef QOMA_TimeBasedStatisticsMono32 QOMA_TimeBasedStatisticsMono;
#endif // QOMA_64BIT_AVAILABLE

struct _QOMA_TimeBasedStatistics;
typedef struct _QOMA_TimeBasedStatistics QOMA_TimeBasedStatistics;

/// @brief  Create a new time based statistics object
/// @return The pointer to the new object. NULL if failed.
QOMA_TimeBasedStatistics * 
qoma_time_based_statistics_new();

/// @brief  Increment the reference count of the object
/// @param  p_time_based_statistics The pointer to the object. 
void
qoma_time_based_statistics_ref(
    QOMA_TimeBasedStatistics * p_time_based_statistics
) QO_NONNULL(1);

/// @brief  Decrement the reference count of the object
/// @param  p_time_based_statistics The pointer to the object. NULL is allowed,
///         in which case this function does nothing.
void
qoma_time_based_statistics_unref(
    QOMA_TimeBasedStatistics * p_time_based_statistics
);

/// @brief  Get the begin of the time based statistics
/// @param  p_time_based_statistics The pointer to the object.
/// @return The pointer to the first mono, which may be equal to the end if the 
///         statistic is empty.
/// @sa     qoma_time_based_statistics_get_end()
QOMA_TimeBasedStatisticsMono *
qoma_time_based_statistics_get_begin(
    QOMA_TimeBasedStatistics * p_time_based_statistics
) QO_NONNULL(1);

/// @brief  Get the end of the time based statistics
/// @param  p_time_based_statistics The pointer to the object.
/// @return The pointer to the end of the statistics, which is equal to the
///         begin if the statistics is empty.
/// @sa     qoma_time_based_statistics_get_begin()
QOMA_TimeBasedStatisticsMono *
qoma_time_based_statistics_get_end(
    QOMA_TimeBasedStatistics * p_time_based_statistics
) QO_NONNULL(1);

/// @brief  Transform the tick based statistics to time based statistics
/// @param  pp_time_based_statistics The pointer to the pointer to the object.
/// @param  p_tick_basic_statistics The pointer to the tick based statistics.
/// @param  ppqn The pulses per quarter note.
/// @return The status of the operation.
/// @retval QOMA_OK The operation was successful.
/// @retval QOMA_INVALID_ARG ppqn is not valid.
/// @retval QOMA_OUT_OF_MEMORY No enough memory to handle the operation.
qo_stat_t
qoma_time_based_statistics_transform(
    QOMA_TimeBasedStatistics ** pp_time_based_statistics ,
    QOMA_TickBasicStatistics *  p_tick_basic_statistics ,
    qoma_midi_resolution_t      ppqn
) QO_NONNULL(1 , 2);

/// @brief  Merge the time based statistics
/// @param  pp_target The pointer to the pointer to the target object.
/// @param  p_source The pointer to the source object.
/// @return qo_true if succeeded, qoma_false if pp_target needs to be extended
///         but no enough memory is available.
qo_bool_t
qoma_time_based_statistics_merge(
    QOMA_TimeBasedStatistics ** pp_target ,
    QOMA_TimeBasedStatistics *  p_source
) QO_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus