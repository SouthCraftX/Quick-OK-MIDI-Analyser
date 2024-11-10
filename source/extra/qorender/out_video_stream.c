#include "extra/qorender/out_video_stream.h"
#include "xoceanlib/include/condlock.h"
#include "xoceanlib/include/atomic.h"

struct _RingRuquests
{
    qoma_ref_count_t    reference_count;

    void
    (* destructor)(
        RingRequests *
    );

    /// @brief Lock when quue is full. Function that pop a request from the 
    /// queue is responsible for releasing the lock if it finds the queue is full.
    XOC_CondLock        queue_full_lock;

    /// @brief Lock when queue is empty. Function that push a request into the
    /// queue is responsible for releasing the lock if it finds the queue is empty.
    XOC_CondLock        queue_empty_lock;

    qoma_uint32_t       request_max;
    //qoma_auint32_t      request_count;

    xoc_auint32_t       head_index;
    xoc_auint32_t       tail_index;

    AVPacket *          packets[];
};
typedef struct _RingRuquests RingRequests;

// Assume you have allocated memory for packets
void
__ring_requests_init(
    RingRequests *      ring_requests ,
    qoma_uint32_t       request_max
){
    ring_requests->request_max = request_max;
    //ring_requests->request_count = 1;
    ring_requests->head_index = 0;
    ring_requests->tail_index = 0;
    xoc_condlock_init(&ring_requests->queue_full_lock);
    xoc_condlock_init(&ring_requests->queue_empty_lock);
}

// Pop a request from the queue. If the queue is empty, NULL will be returned.
AVPacket *
__ring_requests_try_pop(
    RingRequests *      ring_requests
){
    if(
        xoc_atomic_load(&ring_requests->head_index) 
        == 
        xoc_atomic_load(&ring_requests->tail_index)
    ) {
        return NULL;
    }

    qoma_uint32_t index = xoc_atomic_load(&ring_requests->head_index);
    AVPacket * packet = ring_requests->packets[index];

    xoc_atomic_cas_strong(
        &ring_requests->head_index , 
        &index , 
        (index + 1) % ring_requests->request_max
    );

    xoc_condlock_wake(&ring_requests->queue_empty_lock);
    xoc_condlock_unlock(&ring_requests->queue_empty_lock);
}

AVPacket *
__ring_requests_pop(
    RingRequests *      ring_requests
){
    if(
        xoc_atomic_load(&ring_requests->head_index)
        == 
        xoc_atomic_load(&ring_requests->tail_index)
    ) {
        xoc_condlock_wait(&ring_requests->queue_empty_lock);
    }

    qoma_uint32_t index = xoc_atomic_load(&ring_requests->head_index);
    AVPacket * packet = ring_requests->packets[index];

    xoc_atomic_cas_strong(
        &ring_requests->head_index ,
        &index ,
        (index + 1) % ring_requests->request_max
    );

    // TODO: Keep releasing code in not 'try' mode?
    xoc_condlock_wake(&ring_requests->queue_empty_lock);
    xoc_condlock_unlock(&ring_requests->queue_empty_lock);

    return packet;
}

qoma_bool_t
__ring_requests_try_push(
    RingRequests *      ring_requests ,
    AVPacket *          packet
){
    qoma_uint32_t index = xoc_atomic_load(&ring_requests->tail_index);
    qoma_uint32_t next_index = (index + 1) % ring_requests->request_max;

    if(next_index == xoc_atomic_load(&ring_requests->head_index)) {
        return qoma_false;
    }

    ring_requests->packets[index] = packet;

    xoc_atomic_cas_strong(
        &ring_requests->tail_index ,
        &index ,
        next_index
    );

    xoc_condlock_wake(&ring_requests->queue_full_lock);
    xoc_condlock_unlock(&ring_requests->queue_full_lock);

    return qoma_true;
}

void
__ring_requests_push(
    RingRequests *      ring_requests ,
    AVPacket *          packet
){
    qoma_uint32_t index = xoc_atomic_load(&ring_requests->tail_index);
    qoma_uint32_t next_index = (index + 1) % ring_requests->request_max;

    if(next_index == xoc_atomic_load(&ring_requests->head_index)) {
        xoc_condlock_wait(&ring_requests->queue_full_lock);
    }

    // TODO: 
}
struct _LittleBuffer
{
    LittleBuffer *      next;
    qoma_size_t         total_size;
    qoma_size_t         used_size;
    qoma_byte_t         data[];
};
typedef struct _LittleBuffer LittleBuffer;

struct _ChainBuffer
{
    qoma_uint32_t       little_buffer_count;
    LittleBuffer *      buffers;
};
typedef struct _ChainBuffer ChainBuffer;

struct _QORenderOutVideoStream 
{
    qoma_ref_count_t    reference_count;
    AVIOContext *       avio_context;

    RingRequests        ring_requests;
} ;