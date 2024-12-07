#pragma once
#define __QOMA_MIDI_META_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

struct _QOMA_MIDIMeta
{
    qoma_midi_format_t      format;         ///< MIDI format
    qoma_midi_resolution_t  resolution;     ///< Aka. PPQN (Pulses Per Quarter Note)
    qoma_track_count_t      track_count;    ///< Number of tracks
};
typedef struct _QOMA_MIDIMeta QOMA_MIDIMeta;

/// @brief  Convert MIDI format to string
/// @param  format The MIDI format
/// @return String representation of MIDI format. NULL if invalid format.
QO_FORCE_INLINE
qo_ccstring_t
qoma_midi_format_to_string(qoma_midi_format_t format)
{
    // Refer from Standard MIDI-File Format Spec. 1.1, updated, Chapter 2.2
    // See http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
    static qo_ccstring_t format_strings[] = {
        "Single multi-channel track",
        "One or more simultaneous tracks (or MIDI outputs) of a sequence",
        "One or more sequentially independent single-track patterns"
    };
    return ((format >= 0) && (format <= 2)) ? format_strings[format] : NULL;
}

#if defined(__cplusplus)
}
#endif // defined(__cplusplus)