#include "base.h"

// The contents of the track object are not exposed to the user.
struct _QOMA_Track;
typedef struct _QOMA_Track QOMA_Track;

/// @brief  Reduce the reference count of a track. If the reference count
///         reaches zero, the track will be freed.
/// @param  track 
void
qoma_track_unref(
    QOMA_Track * track
);

qoma_track_count_t
qoma_track_get_id(
    QOMA_Track * track
);

qo_uint32_t
qoma_track_get_size(
    QOMA_Track * track
);

/// @brief Get pointer to raw events data.
/// @param track 
/// @return 
qo_byte_t const *
qoma_track_get_content(
    QOMA_Track * track
);
