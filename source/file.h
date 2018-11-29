/**
 * @file
 * @brief
 * File utility functions.
 *
 * @author Klaus Saalfeld
 */
#ifndef FILE_H_
#define FILE_H_ FILE_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * The specified file or directory is marked for deletion upon reboot.
 *
 * @details
 * If a directory it must be empty.
 *
 * @param name          File or directory to delete upon reboot.
 *                      If set to NULL the function has no effect.
 */
VOID File_DeleteAfterReboot(const CHAR* name);

/**
 * @brief
 * Deletes the specified file.
 *
 * @details
 * The function removes read-only attribute before deleting the file.
 * If the file can't be deleted (e.g. because still in use by another application)
 * it is marked for deletion on reboot.
 *
 * @param name          Name of file to delete.
 *                      If the specified name refer to a directory the function has no effect.
 *                      If set to NULL the function has no effect.
 */
VOID File_DeleteSingleFile(const CHAR* name);

#ifdef __cplusplus
}
#endif

#endif /* FILE_H_ */
