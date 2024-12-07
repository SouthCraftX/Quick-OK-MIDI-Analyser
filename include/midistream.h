#pragma once
#define __QOMA_MIDISTREAM_H__

#include "track.h"
#include "xoceanlib/include/error_descriptor.h"

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)


struct _QOMA_MIDIStream;
typedef struct _QOMA_MIDIStream QOMA_MIDIStream;

struct _QOMA_MIDIFileInfo
{
    qo_ccstring_t  file_path;
    qo_ccstring_t  filename;
    qo_uint16_t    file_path_length;
    qo_uint16_t    filename_length;
    qo_size_t      file_size;
};
typedef struct _QOMA_MIDIFileInfo QOMA_MIDIFileInfo;

struct _QOMA_MIDIStreamCacheStat
{
    qo_bool_t          will_automatically_cache_forward;
    qoma_track_count_t  active_cached_track_count;
    qoma_track_count_t  discarded_cached_track_count;
    qo_size_t          active_cache_size;
    qo_size_t          discarded_cache_size;
};
typedef struct _QOMA_MIDIStreamCacheStat QOMA_MIDIStreamCacheStat;

/// @brief Optimized for sequential reading
#define QOMA_MIDISTREAM_SEQUENICAL 0b0 

/// @brief  Optimized for fast-random reading storage
/// @remark In some implementation, this will indicate using memory mapping
#define QOMA_MIDISTREAM_RANDOM 0b1

/* ---------- Caching Strategies  ---------- */
/* These strategies are only work without QOMA_MIDISTREAM_RANDOM*/
/// @brief Cache the whole file in memory
/// @note  Operation may be costy and easier to fail if no enough memory
#define QOMA_MIDISTREAM_FULL_CACHED 0b10

/// @brief Cache a track when needed
#define QOMA_MIDISTREAM_TRACK_CACHED 0b100

/// @brief  Automatically cache tracks forward until meeting the end of the file
///         or memory limit
#define QOMA_MIDISTREAM_MAX_CACHED 0b1000

/// @brief  Begin caching MIDI once the midi stream is created.
/// @remark If not specified, caching will be started at first reading request
#define QOMA_MIDISTREAM_CACHE_ON_INIT 0b10000

/// @brief  Check and refuse to open it if traversal found in the file path
#define QOMA_MIDISTREAM_NO_TRAVERSAL 0b100000000000000000000000000000

/// @brief  Lock the access to the midi file, to prevent other process from
///         writing or deleting the file
#define QOMA_MIDISTREAM_LOCK_ACCESS 0b1000000000000000000000000000000

/// @brief  If specified flags conflict or cannot be satisfied, this flag will 
///         stop proceeding instead of trying to ignore those flags
#define QOMA_MIDISTREAM_STRICT 0b10000000000000000000000000000000

/// @brief  Open a midi file
/// @param  p_midistream     Pointer to the midi stream
/// @param  midi_path        Path to the midi file
/// @param  creation_flags   Flags for creation
/// @return The error descriptor if failed, otherwise NULL
QO_ErrDesc *
qoma_midistream_open(
    QOMA_MIDIStream **       pp_midistream ,
    qo_ccstring_t          midi_path ,
    qoma_flag32_t            creation_flags
);

/// @brief  Query meta information of the midi file
/// @param  p_midistream The midi stream
/// @param  p_midimeta Pointer to the meta information
/// @return The status of the operation
qo_stat_t
qoma_midistream_query_meta(
    QOMA_MIDIStream *       p_midistream ,
    QOMA_MIDIMeta *         p_midimeta
);

/// @brief Reduce the reference count of the midi stream. If the reference
///        count reaches 0, the midi stream will be closed and freed.
/// @param p_midistream 
void
qoma_midistream_unref(
    QOMA_MIDIStream *       p_midistream
);

/// @brief Get the cache status of the midi stream
/// @param p_midistream    The midi stream
/// @param p_cache_stat  Pointer to the cache status
/// @return The status of the operation
qo_stat_t
qoma_midistream_get_cache_stat(
    QOMA_MIDIStream *           p_midistream ,
    QOMA_MIDIStreamCacheStat *  p_cache_stat
);

/// @brief  Query the file information of the midi file
/// @param  p_midistream The midi stream
/// @param  p_fileinfo Pointer to the file information
/// @return The status of the operation
qo_stat_t
qoma_midistream_query_file_info(
    QOMA_MIDIStream *       p_midistream ,
    QOMA_MIDIFileInfo *     p_fileinfo
);

/// @brief  Fetch a track from the midi stream
/// @param  p_midistream  The midi stream
/// @param  pp_track    Pointer to the pointer of the track. *pp_track will set to
///                     NULL if no tracks left.
/// @return The status of the operation
/// @retval QOMA_OK if successful
/// @retval QOMA_ACCESS_VIOLATED if the stream is bound to another object and it
///         requires exclusive access
qo_stat_t
qoma_midistream_fetch_track(
    QOMA_MIDIStream *       p_midistream ,
    QOMA_Track **           pp_track 
);

#if defined(__cplusplus)
}
#endif // __cplusplus