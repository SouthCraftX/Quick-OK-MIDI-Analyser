#include "tick_basic_statistics.h"
#include <memalloc.h>

struct _QOMA_TickBasicStatistics
{
    qoma_ref_count_t    reference_count;

    qoma_size_t         tick_count;
    qoma_size_t         free_count;
    qoma_size_t         allocated_size;

    QOMA_TickBasicStatisticsMono * mono_end;

    QOMA_TickBasicStatisticsMono mono[];
};

QOMA_TickBasicStatistics *
qoma_tick_basic_statistics_new()
{
    QOMA_TickBasicStatistics * stat = xoc_alloc(sizeof(QOMA_TickBasicStatistics));
    if (QOMA_LIKELY(stat))
    {
        stat->tick_count = 0;
        stat->free_count = 0;
        stat->reference_count = 1;
        stat->allocated_size = sizeof(QOMA_TickBasicStatistics);
        stat->mono_end = stat->mono;
    }
    return stat;
}

void
qoma_tick_basic_statistics_unref(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
){
    if (p_tick_basic_statistics)
    {
        if (--p_tick_basic_statistics->reference_count == 0)
        {
            xoc_free(p_tick_basic_statistics);
        }
    }
}

QOMA_TickBasicStatisticsMono *
qoma_tick_basic_statistics_get_begin(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
){
    return p_tick_basic_statistics->mono;
}

QOMA_TickBasicStatisticsMono *
qoma_tick_basic_statistics_get_end(
    QOMA_TickBasicStatistics * p_tick_basic_statistics
){
    return p_tick_basic_statistics->mono_end;
}

qoma_bool_t
qoma_tick_basic_statistics_extend(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics ,
    qoma_size_t count
){
    QOMA_TickBasicStatistics * new_stat = xoc_realloc(
        *pp_tick_basic_statistics , 
        (*pp_tick_basic_statistics)->allocated_size + count * sizeof(QOMA_TickBasicStatisticsMono)
    );
    if (QOMA_LIKELY(new_stat))
    {
        new_stat->free_count += count;
        new_stat->allocated_size += count * sizeof(QOMA_TickBasicStatisticsMono);
        *pp_tick_basic_statistics = new_stat;
        return qoma_true;
    }
    else
    {
        return qoma_false;
    }
}

QOMA_FORCE_INLINE
qoma_bool_t
__extend_for_add(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics
){
    return qoma_tick_basic_statistics_extend(pp_tick_basic_statistics ,
           (*pp_tick_basic_statistics)->tick_count * 3 / 2
    );
}

qoma_bool_t
qoma_tick_basic_statistics_add(
    QOMA_TickBasicStatistics ** pp_tick_basic_statistics ,
    QOMA_TickBasicStatisticsMono mono
){
    if (QOMA_UNLIKELY(!(*pp_tick_basic_statistics)->free_count))
    {
        if (__extend_for_add(pp_tick_basic_statistics))
        {
            goto add;
        }
        return qoma_false;
    }
add:
    *(*pp_tick_basic_statistics)->mono_end++ = mono;
    (*pp_tick_basic_statistics)->free_count--;
    (*pp_tick_basic_statistics)->tick_count++;
    return qoma_true;
}