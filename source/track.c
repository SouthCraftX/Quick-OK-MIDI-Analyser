#include "track.h"

struct _QOMA_Track
{
    qoma_ref_count_t    reference_count;

    void
    (* destructor)(
        QOMA_Track *
    );

    qoma_track_count_t  id;
    qoma_uint32_t       size;
    qoma_pointer_t      content;    
};

QOMA_NO_SIDE_EFFECTS
qoma_track_count_t
qoma_track_get_id(
    QOMA_Track * track
){
    return track->id;
}

QOMA_NO_SIDE_EFFECTS
qoma_uint32_t
qoma_track_get_size(
    QOMA_Track * track
){
    return track->size;
}

QOMA_NO_SIDE_EFFECTS
qoma_byte_t const *
qoma_track_get_content(
    QOMA_Track * track
){
    return (qoma_byte_t const *)track->content;
}