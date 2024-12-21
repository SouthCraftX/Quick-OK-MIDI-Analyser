#include "track.h"
#include "tick_basic_statistics.h"
#include "universal_calculation.h"  

#include <string.h>

// Move to one byte after sysex event
// Return true if the 0xF7 byte isn't found, which indicates the track is corrupted. 
qoma_bool_t
__midi1_skip_sysex(
    qoma_byte_t **  p_buffer ,
    qoma_uint32_t   search_limit
) {
    qoma_byte_t * ret = memchr(*p_buffer , 0xF7 , search_limit);
    if (QOMA_LIKELY(ret))
    {
        *p_buffer = ret + 1;
        return qoma_false;
    }
    return qoma_true;
}

// Return true if EOT reached
qoma_bool_t
__midi1_parse_meta_event(
    qoma_byte_t ** p_buffer , //<Point to 0xFF next byte
    QOMA_TickBasicStatisticsMono * mono
) {
    // Only EOT and tempo changing events are useful to us.
    switch (**p_buffer)
    {
        case 0x51: // Tempo Change
            *p_buffer ++;
            mono->tempo_change_us += (*(qoma_uint32_t *)(*p_buffer) & 0x00FFFFFF);
            // do bitwise to get length indicator 0x03 off
            *p_buffer += sizeof(qoma_uint32_t);
            return qoma_false;

        case 0x2F:  // EOT
            return qoma_true;

        default:
            *p_buffer += 1; // Go to length byte
            *p_buffer += **p_buffer + 1; // +1 for length byte itself 
    } 
}



qoma_stat_t
__midi1_parse_track(
    qoma_byte_t * buffer , //<First event begin
    qoma_uint32_t length , //<Length except the track meta 
    QOMA_TickBasicStatistics ** pp_tick_stat
) {
    const qoma_byte_t * end = buffer + length;
    QOMA_TickBasicStatisticsMono * mono; 
    qoma_tick_t         ticks;
    qoma_uint32_t       delta_tick;
    qoma_bool_t         eot_reached;
    qoma_uint8_t        last_noteoff_arg;

    do
    {
        delta_tick = qoma_delta_time_read(&buffer);
        ticks += delta_tick;

        mono = qoma_tick_basic_statistics_reach(pp_tick_stat , ticks);
        if (QOMA_UNLIKELY(!mono))
            return QOMA_OUT_OF_MEMORY;

        switch (*buffer & 0xF0) // 0b11110000
        {
            case 0xF0:
                if(*buffer == 0xF0) // sysex
                {
                    if(__midi1_skip_sysex(&buffer , end - buffer))
                        return QOMA_BAD_TRACK;
                }
                if (__midi1_parse_meta_event(&buffer , mono))
                {
                    eot_reached;
                }
                break;
                
            /* 2-bytes-length events */
            case 0x80: // noteoff
                mono->noteoff_count++;
                buffer += 3;
                break;

            case 0x90:  // noteon (format: pitch velocity)
                last_noteoff_arg = !(buffer + 2);
                mono->noteinfo[last_noteoff_arg]++; // velocity 0 indicates noteoff

            case 0xA0: // Key After Touch
            case 0xB0: // Controller
            case 0xE0: // Pitch bend
                buffer += 3;
                break;


            case 0xC0: // Program Change
            case 0xD0: // Channel After Touch
                buffer +=2;
                break;

        }
    }   
    while(buffer < end);

    if ((buffer < end) || !eot_reached)
    {
        // Do we jump out of parsing in advcance due to End of track event?
        // Or we have interated the whole track but EOT isn't occurred?
        // If it is the case, the track is corrupted.
        // (The length of the track doesn't match the claimed length in track header)
        return QOMA_TRACK_LENGTH_MISMATCH;
    }
    
}