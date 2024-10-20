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

