/**
 * @file
 * @brief
 * Simple logger only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#ifndef LOG_H_
#define LOG_H_ LOG_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Prepares a log file having the specified name.
 *
 * @param dir           Directory where to place log file.
 * @param file          Name of log file to use.
 */
VOID Log_Start(const CHAR* dir, const char* file);

/**
 * @brief
 * Writes given text into the log file.
 *
 * @param line          New line to write.
 *                      A line feed is automatically appended by the function.
 *                      If set to NULL the function has no effect.
 */
VOID Log_Write(const CHAR* line);

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
