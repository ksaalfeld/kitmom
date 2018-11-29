/**
 * @file
 * @brief
 * String utility functions.
 *
 * @author Klaus Saalfeld
 */
#ifndef STRING_H_
#define STRING_H_ STRING_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Returns the length (in characters) of the specified string.
 *
 * @brief str           String (zero terminated) to process.
 *                      If set to NULL the function has no effect and returns zero.
 *
 * @return              Number of characters (excluding zero terminator).
 */
DWORD String_Length(const CHAR* str);

/**
 * @brief
 * Copies source string into destination buffer.
 *
 * @details
 * Caller must ensure that destination buffer is big enough
 * to store source string and that both strings are zero terminated.
 * The function behaves well when source and destination buffer overlap.
 *
 * @param dest          Destination buffer.
 *                      If set to NULL the function has no effect.
 * @param src           Source string to copy (zero terminated).
 *                      If set to NULL an empty string is copied.
 *                      If source equals destination buffer nothing is copied.
 *
 * @return              Number of bytes copied (excluding zero terminator).
 */
DWORD String_Copy(CHAR* dest, const CHAR* src);

#ifdef __cplusplus
}
#endif

#endif /* STRING_H_ */
