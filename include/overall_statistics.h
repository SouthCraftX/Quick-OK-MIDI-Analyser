#pragma once
#define __QOMA_OVERALL_STATISTICS_H__

#include "time_based_statistics.h"

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus


struct _QOMA_OverallStatistics64
{
    qo_uint64_t   noteon_count;
    qo_uint64_t   noteoff_count;
    qo_uint64_t   tick_count;
    qo_uint64_t   bar_count;

    qo_uint64_t   max_polyphony;
    qo_uint64_t   min_polyphony;
    qo_uint64_t   avg_polyphony;

    qo_uint64_t   max_nps;
    qo_uint64_t   min_nps;
    qo_uint64_t   avg_nps;

    qoma_tempo_t     max_bpm;
    qoma_tempo_t     min_bpm;
    qoma_tempo_t     avg_bpm;
};
typedef struct _QOMA_OverallStatistics64 QOMA_OverallStatistics64;

struct _QOMA_OverallStatistics32
{
    qo_uint32_t   noteon_count;
    qo_uint32_t   noteoff_count;
    qo_uint32_t   tick_count;
    qo_uint32_t   bar_count;

    qo_uint32_t   max_polyphony;
    qo_uint32_t   min_polyphony;
    qo_uint32_t   avg_polyphony;

    qo_uint32_t   max_nps;
    qo_uint32_t   min_nps;
    qo_uint32_t   avg_nps;

    qoma_tempo_t    max_bpm;
    qoma_tempo_t    min_bpm;
    qoma_tempo_t    avg_bpm;
};
typedef struct _QOMA_OverallStatistics32 QOMA_OverallStatistics32;

#if QOMA_64BIT_AVALIABLE
typedef QOMA_OverallStatistics64 QOMA_OverallStatistics;
#else
typedef QOMA_OverallStatistics32 QOMA_OverallStatistics;
#endif // QOMA_64BIT_AVALIABLE

void
qoma_overall_statisticize(
    QOMA_OverallStatistics *    p_overall_statistics    _QOMA_OUT_,
    QOMA_TimeBasedStatistics *  p_time_based_statistics _QOMA_IN_
) QO_NONNULL(1 , 2);

#if defined(__cplusplus)
}
#endif // __cplusplus