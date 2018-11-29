/**
 * @file
 * @brief
 * Simple memory allocator only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#ifndef MEMORY_H_
#define MEMORY_H_ MEMORY_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Allocates a new chunk of memory of specified size (in bytes).
 *
 * @details
 * If the function fails to allocate new memory it returns NULL.
 * You must free the memory returned by calling Memory_Free().
 *
 * @param size          Size of memory area (in bytes).
 *                      If set to zero memory is allocated and returned
 *                      but may not read or write to the memory location.
 * @return              Pointer to allocated memory area
 *                      or NULL if the function was unable to allocate memory.
 */
CHAR* Memory_Allocate(DWORD size);

/**
 * @brief
 * Resizes the specified memory area.
 *
 * @details
 * If the new size is smaller than the current size of the memory area
 * the function has no effect and returns the pointer to the old memory area.
 * Otherwise if the new size is greater than the current size
 * the function allocates a new memory area, copies the contents of the old memory area
 * and finally frees the old memory area and returns the pointer to the new memory area.
 *
 * If the function fails to allocate new memory it returns NULL.
 *
 * After calling this function the old memory area is gone
 * and trying to access it has undefined effects.
 * 
 * If the pointer has not been allocated before or
 * already has been freed the function has undefined effects.
 *
 * @param buffer        Memory area to resize.
 *                      If set to NULL the function allocates a memory area of specified size.
 * @param size          New size (in bytes) of memory area.
 *
 * @return              Pointer to resized memory area.
 */
CHAR* Memory_Resize(CHAR* buffer, DWORD size);

/**
 * @brief
 * Free the specified memory area.
 *
 * @details
 * If the specified pointer is NULL the function has no effect.
 * If the pointer has not been allocated before or
 * already has been freed the function has undefined effects.
 *
 * @param buffer        Memory area to free.
 *                      If set to NULL the function has no effect.
 */
VOID Memory_Free(CHAR* buffer);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H_ */

