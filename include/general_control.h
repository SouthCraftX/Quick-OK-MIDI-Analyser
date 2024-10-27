#pragma once
#define __QOMA_GENERAL_CONTROL_H__

#include "base.h"

#if defined(__cplusplus)
extern "C" {
#endif

struct _QOMA_Allocator
{
    qoma_pointer_t
    (* malloc)(
        qoma_size_t     size
    );

    qoma_pointer_t
    (* realloc)(
        qoma_pointer_t  memory ,
        qoma_size_t     new_size
    );

    qoma_pointer_t
    (* calloc)(
        qoma_size_t     size
    );

    qoma_pointer_t
    (* recalloc)(
        qoma_pointer_t  memory ,
        qoma_size_t     new_size 
    );

    void
    (* free)(
        qoma_pointer_t  memory
    );

};
typedef struct _QOMA_Allocator  QOMA_Allocator;

// Modes for qoma_set_allocation_behavior
#define QOMA_ALLOC_PHYSICAL_LIMIT 0b0
#define QOMA_ALLOC_SPECIFIC_LIMIT 0b1
#define QOMA_ALLOC_AS_PHYSICAL_PERCENTAGE 0b10

/// @brief  Set allocation behavior
/// @param  p_allocator Pointer to allocator function sets. All function 
///         pointers must be valid. Setting p_allocator to NULL is allowed,
///         if you want to use default allocator.
/// @param  size The limit of the allocation. Make it negative to take free 
///         physical memory into consideration, which may make the allocable
///         memory size less than the specified size. Make it 0 to disable
///         the limit.
/// @param  mode 
/// @return The status of the operation
/// @retval QOMA_INVALID_OBJECT p_allocator contains NULL pointer
/// @note   If abs(size) is unreasonably small, the function will still succeed
///         but you may make many functions fail if it requires allocation.
qoma_stat_t
qoma_set_allocation_behavior(
    QOMA_Allocator *    p_allocator ,
    qoma_ssize_t        size ,
    qoma_flag32_t       mode
);

/// @brief Get allocation behavior
/// @param p_allocator Pointer to allocator function sets that QOMA is using
/// @param p_allocated_size Pointer to store the allocated memory size  
void
qoma_get_allocation_behavior(
    QOMA_Allocator *    p_allocator ,
    qoma_ssize_t *      p_allocated_size
);

#if defined(__cplusplus)
}
#endif