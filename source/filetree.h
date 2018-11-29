/**
 * @file
 * @brief
 * File iterator only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#ifndef FILETREE_H_
#define FILETREE_H_ FILETREE_H_

#include "platform.h"


/**
 * @brief
 * Callback function prototype.
 *
 * @details
 * This function is called for each file and directory visited.
 *
 * @param dir           Directory.
 * @param file          Name of file within directory.
 *                      This argument is NULL when visiting a directory.
 * @return              Value summed up and returned by the caller.
 *                      Typically used to count the number of items processed.
 */
typedef DWORD (*FILETREE_CALLBACK_T)(const CHAR* dir, const char* file);


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Recursively iterates over files and directories in the given location.
 *
 * @details
 * Files are found before the directory they reside in.
 *
 * @param dir           Path to iterate.
 *                      If set to NULL the function has no effect.
 * @param file          Must be set to NULL.
 * @param func          Callback function that is called for each file and directory found.
 *                      If set to NULL the function has no effect.
 */
DWORD FileTree_Iterate(const CHAR* dir, const CHAR* file, FILETREE_CALLBACK_T func);

#ifdef __cplusplus
}
#endif

#endif /* FILETREE_H_ */

