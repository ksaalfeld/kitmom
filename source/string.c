/**
 * @file
 * @brief
 * String utility functions.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "string.h"


DWORD String_Length(const CHAR* str)
{
    DWORD result;
    
    result = 0;
    
    if (NULL != str)
    {
        while ('\0' != str[result])
        {
            ++result;
        }
    }
    
    return result;
}


DWORD String_Copy(CHAR* dest, const CHAR* src)
{
    DWORD result;
    DWORD index;
    
    result = 0;
    
    if (NULL != dest)
    {
        /* Self-copy does not require any additional work */
        if ((const CHAR*)dest != src)
        {
            if (NULL != src)
            {
                /* Handle partially overlapping strings a such
                 * a way that the result is defined (unlike strcpy).
                 */
                if ((const VOID*)dest < (const VOID*)src)
                {
                    /* Copy source buffer in direction of increasing addresses */
                    for (; /*forever*/; ++result)
                    {
                        dest[result] = src[result];
                        if ('\0' == src[result])
                        {
                            break;
                        }
                    }
                }
                    else
                    {
                        /* Get number of characters to copy.
                         * Length is excluding zero terminator,
                         * so index on first copy is the zero terminator.
                         */
                        result = String_Length(src);
                    
                        /* Copy source buffer in direction of decreasing addresses */
                        for (index = result; /*forever*/; --index)
                        {
                            dest[index] = src[index];
                            if (0 == index)
                            {
                                break;
                            }
                        }
                    }
            }
                else
                {
                    /* When source buffer is pointing to nowhere
                     * we make destination buffer an empty string.
                     */
                    dest[0] = '\0';
                }
        }
    }
    
    return result;
}
