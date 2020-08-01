/**
 * @file
 * @brief
 * Simple memory allocator only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "memory.h"


/**
 * @brief
 * Header put in front of allocated memory blocks.
 */
struct MEMORY_AREA_ST
{
    /**
     * @brief
     * Handle of process heap.
     */
    HANDLE handle;
    /**
     * @brief
     * Size of memory block after this header (in bytes).
     */
    DWORD size;
};

/**
 * @see MEMORY_AREA_ST
 */
typedef struct MEMORY_AREA_ST MEMORY_AREA_T;


CHAR* Memory_Allocate(DWORD size)
{
    CHAR* result;
    HANDLE handle;
    MEMORY_AREA_T* ptr;
    
    result = NULL;
    
    handle = GetProcessHeap();
    if (NULL != handle)
    {
        /* Dont want any overflow */
        if (size <= ((DWORD)-1) - sizeof(*ptr))
        {
            ptr = (MEMORY_AREA_T*)HeapAlloc(handle, HEAP_ZERO_MEMORY, size + sizeof(*ptr));
            if (NULL != ptr)
            {
                ptr->handle = handle;
                ptr->size = size;
                result = ((CHAR*)ptr) + sizeof(*ptr);
            }
        }
    }
    
    return result;
}


CHAR* Memory_Resize(CHAR* buffer, DWORD size)
{
    CHAR* result;
    DWORD index;
    MEMORY_AREA_T* ptr;

    result = buffer;

    if (NULL != buffer)
    {
        ptr = (MEMORY_AREA_T*)(buffer - sizeof(*ptr));
        if (ptr->size < size)
        {
            /* Allocate a new memory block of specified size
             * and copy the contents of the old memory block.
             * Finally free the old memory block.
             */
            result = Memory_Allocate(size);
            if (NULL != result)
            {
                for (index = 0; index < ptr->size; ++index)
                {
                    result[index] = buffer[index];
                }
            }
            Memory_Free(buffer);
        }
    }
        else
        {
            /* If buffer is NULL we allocate new memory of specified size */
            result = Memory_Allocate(size);
        }

    return result;
}


VOID Memory_Free(CHAR* buffer)
{
    MEMORY_AREA_T* ptr;
    
    if (NULL != buffer)
    {
        ptr = (MEMORY_AREA_T*)(buffer - sizeof(*ptr));
        if (NULL != ptr->handle)
        {
            HeapFree(ptr->handle, 0, ptr);
        }
    }
}

