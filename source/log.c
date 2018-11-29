/**
 * @file
 * @brief
 * Simple logger only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "string.h"
#include "path.h"
#include "log.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Append the specified text to the file using (opened) handle.
 *
 * @param handle        Handle of file to write into.
 * @param text          Text to write.
 */
static VOID Log_Append(HANDLE handle, const CHAR* text);

#ifdef __cplusplus
}
#endif


/**
 * @brief
 * Name including path of log file
 */
static CHAR name[MAX_PATH + 1];


static VOID Log_Append(HANDLE handle, const CHAR* text)
{
    LARGE_INTEGER pos;
    DWORD count;
    
    if (INVALID_HANDLE_VALUE != handle)
    {
        pos.QuadPart = 0;
        SetFilePointerEx(handle, pos, NULL, FILE_END);
        if (NULL != text)
        {
            WriteFile(handle, text, String_Length(text), &count, NULL);
        }
        WriteFile(handle, "\r\n", 2, &count, NULL);
    }
}


VOID Log_Start(const CHAR* dir, const char* file)
{
    Path_Copy(name, dir);
    Path_Concat(name, file);
}


VOID Log_Write(const CHAR* line)
{
    HANDLE handle;
    
    if (NULL != line)
    {
        /* If a filename has been append to this file (possibly creating it) */
        if ('\0' != name[0])
        {
            handle = CreateFile(
                name,
                GENERIC_WRITE,
                FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                NULL,
                OPEN_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
            if (INVALID_HANDLE_VALUE != handle)
            {
                /* Append given string as new line */
                Log_Append(handle, line);
                /* Do not keep file open so that file is up to date after each call */
                CloseHandle(handle);
            }
        }
    }
}
