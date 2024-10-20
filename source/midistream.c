#include "midistream.h"
#include "xoceanlib/include/abstract_file.h"
#include "xoceanlib/include/condlock.h"

struct _QOMA_MIDIStreamSyncContext
{
    XOC_CondLock * memory_available;
};
typedef struct _QOMA_MIDIStreamSyncContext QOMA_MIDIStreamSyncContext;

// typedef (void)(*qoma_midistream_destructor_t)(QOMA_MIDIStream * p_midistream);

struct _QOMA_MIDIStream
{
    xoc_ref_count_t             reference_count;

    void
    (* destructor)(
        QOMA_MIDIStream *       p_midistream
    );

    QOMA_MIDIStreamSyncContext  sync_context;
    XOC_AbstractFile *          midi_file;
    
};

qoma_stat_t
qoma_midistream_open(
    qoma_midistream_t * p_midistream ,
    qoma_ccstring_t      midi_path ,
    qoma_flag32_t        creation_flags
){

}