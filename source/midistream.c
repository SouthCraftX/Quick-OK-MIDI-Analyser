#include "midistream.h"
#include "xoceanlib/include/abstract_file.h"
#include "xoceanlib/include/condlock.h"

struct _QOMA_MIDIStreamSyncContext
{
    QO_CondLock * memory_available;
};
typedef struct _QOMA_MIDIStreamSyncContext QOMA_MIDIStreamSyncContext;

// typedef (void)(*qoma_midistream_destructor_t)(QOMA_MIDIStream * p_midistream);

struct _QOMA_MIDIStream
{
    qo_ref_count_t             reference_count;

    void
    (* destructor)(
        QOMA_MIDIStream *       p_midistream
    );

    QOMA_MIDIStreamSyncContext  sync_context;
    QO_AbstractFile *          midi_file;
    
};

// Return true if the track is OK
qo_bool_t
__precheck_track_validity(
    qo_byte_t * buffer ,
    qo_uint32_t * p_track_length  
){
    const char head_mark = {'M' , 'T' , 'r' , 'k'};
    if(memcmp(buffer , &head_mark , 4))
    {
        return qoma_false;
    }

    const qo_int32_t track_length = *(qo_int32_t *)(buffer + 4);
    *p_track_length = track_length;
    
    buffer += track_length - 3;
    if (buffer[0] == (qo_uint8_t)0xFF && buffer[1] == (qo_uint8_t)0x2F  && buffer[2] == (qo_uint8_t)0x00)
    {
        return qo_true;
    }
    return qoma_false;
}

qo_stat_t
qoma_midistream_open(
    QOMA_MIDIStream **   pp_midistream ,
    qo_ccstring_t      midi_path ,
    qoma_flag32_t        creation_flags
){

}