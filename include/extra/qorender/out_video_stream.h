#include "../../base.h"
#include "xoceanlib/include/thread_pool.h"

#include <libavformat/avio.h>
#include <libavcodec/packet.h>

struct _QORender_OutVideoStream;
typedef struct _QORender_OutVideoStream QORender_OutVideoStream;

struct _QORender_OutVideoStreamBufferStrategy
{
    /// @brief Maxiumum number of requests that can be queued. If this number is
    /// reached and caller don't write in "try" mode, requesters will be blocked
    /// until some requests are flushed.
    qoma_int32_t    hung_requests_max;

    /// @brief The number of requests that lead to flush.
    qoma_int32_t    flush_threshold;   
    
    /// @brief The number of little buffer in the ring list.
    qoma_int32_t    little_buffer_count;

    /// @brief The size of each little buffer.
    qoma_size_t     little_buffer_size;
};
typedef struct _QORender_OutVideoStreamBufferStrategy 
        QORender_OutVideoStreamBufferStrategy;

/// @brief Create a out video stream.
/// @param pp_out_video_stream Pointer to the pointer of the out video stream.
/// @param video_path The path of the video.
/// @param p_buffer_strategy The buffer strategy. NULL is allowed, in which case
/// the default strategy will be used.
/// @param p_thread_pool Pointer to the thread pool. If you don't desire parallel writing,
/// set it to NULL.
qoma_stat_t
qorender_out_video_stream_new(
    QORender_OutVideoStream **  pp_out_video_stream ,
    qoma_ccstring_t             video_path ,
    QORender_OutVideoStreamBufferStrategy *  p_buffer_strategy ,
    XOC_ThreadPool *            p_thread_pool
) QOMA_NONNULL(1 , 2);

/// @brief Try to write a packet to the out video stream.
/// @param p_out_video_stream Pointer to the out video stream.
/// @param p_packet Pointer to the packet.
/// @return The status of the operation.
/// @retval QOMA_TARGET_BUSY The queue of hung write requests is full.
/// @retval QOMA_ACCESS_VIOLETED The out video stream is bound to other object
///         and it require exclusive access.
qoma_stat_t
qorender_out_video_stream_try_write(
    QORender_OutVideoStream *  p_out_video_stream ,
    AVPacket *                 p_packet
) QOMA_NONNULL(1 , 2);

/// @brief Write a packet to the out video stream.
/// @param p_out_video_stream Pointer to the out video stream.
/// @param p_packet Pointer to the packet.
/// @return The status of the operation.
/// @retval QOMA_ACCESS_VIOLETED The out video stream is bound to other object
///         and it require exclusive access.
/// @note This function will block if the queue of hung write requests is full.
/// If it is not desired, use qorender_out_video_stream_try_write() instead.
qoma_stat_t
qorender_out_video_stream_write(
    QORender_OutVideoStream *  p_out_video_stream ,
    AVPacket *                 p_packet
) QOMA_NONNULL(1 , 2);

/// @brief Flush the out video stream.
void
qorender_out_video_stream_flush(
    QORender_OutVideoStream *  p_out_video_stream
) QOMA_NONNULL(1);

/// @brief Decrement the reference count of the out video stream. If the 
/// reference count reaches zero, the out video stream will be closed.
/// @param p_out_video_stream Pointer to the out video stream. NULL is allowed,
/// in which case the function does nothing.
void
qorender_out_video_stream_unref(
    QORender_OutVideoStream *  p_out_video_stream
);