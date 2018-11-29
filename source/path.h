/**
 * @file
 * @brief
 * Utility function for path handling only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#ifndef PATH_H_
#define PATH_H_ PATH_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Concatenates specified directory with given path.
 *
 * @details
 * Upon return specified directory contain the concatenated path.
 * The caller is responsible to ensure underlying buffer is big enough.
 * Any trailing backslash is removed by this function.
 *
 * The function has undefined effects if dir and member point to the same buffer or overlap.
 *
 * @param dir           Directory.
 *                      If set to NULL the function has no effect.
 * @param member        Member to concatenate.
 *                      If set to NULL nothing is concatenated.
 */
VOID Path_Concat(CHAR* dir, const CHAR* member);

/**
 * @brief
 * Copies specified path from source into dest.
 *
 * @details
 * The caller is responsible to ensure underlying buffer is big enough.
 * If dest and source point to the same buffer nothing is copied.
 *
 * @param dest          Buffer written to.
 *                      If set to NULL the function has no effect.
 * @param source        Buffer copied.
 */
VOID Path_Copy(CHAR* dest, const CHAR* source);

/**
 * @brief
 * Returns the installation directory of the executable file.
 *
 * @param buffer        Buffer written.
 *                      If set to NULL the function has no effect.
 * @param size          Size of given buffer (in characters).
 *                      If set to zero the function has no effect.
 *
 * @return              On success number of characters written (including zero terminator).
 */
DWORD Path_HomeDir(CHAR* buffer, DWORD size);

/**
 * @brief
 * Returns the fully qualified path to the temporary directory location.
 *
 * @param buffer        Buffer written.
 *                      If set to NULL the function has no effect.
 * @param size          Size of given buffer (in characters).
 *                      If set to zero the function has no effect.
 *
 * @return              On success number of characters written (including zero terminator).
 */
DWORD Path_TempDir(CHAR* buffer, DWORD size);

/**
 * @brief
 * Create a temporary file or directory name using given prefix and unique number.
 *
 * @details
 * If buffer and prefix overlap the function has undefined effects.
 *
 * @param buffer        Buffer written.
 *                      If set to NULL the function has no effect and returns zero.
 * @param prefix        Prefix appended.
 *                      If set to NULL no prefix is appended.
 * @param unique        A unique number that is appended as hex string (8 hex characters).
 *                      The function does NOT ensure that a file or directory having this name does not already exist.
 *
 * @return              Number of characters written.
 */
DWORD Path_TempName(CHAR* buffer, const CHAR* prefix, DWORD unique);

/**
 * @brief
 * Returns if a file or directory with the specified path exists.
 *
 * @param path          Path (a file or directory) to check.
 *                      If set to NULL the function has no effect and returns FALSE.
 *
 * @return              TRUE if (and only if) the file or directory exists.
 *                      FALSE if the file or directory does not exist or there was an error.
 */
BOOL Path_Exists(const CHAR* path);

#ifdef __cplusplus
}
#endif

#endif /* PATH_H_ */

