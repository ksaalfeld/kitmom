/**
 * @file
 * @brief
 * File utility functions.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "file.h"


VOID File_DeleteAfterReboot(const CHAR* name)
{
    if (NULL != name)
    {
        MoveFileEx(name, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
    }
}


VOID File_DeleteSingleFile(const CHAR* name)
{
    DWORD attr;
    DWORD mask;
    
    if (NULL != name)
    {
        attr = GetFileAttributes(name);
        if ((INVALID_FILE_ATTRIBUTES != attr) && (0 == (attr & FILE_ATTRIBUTE_DIRECTORY)))
        {
            mask = FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN;
            /* Remove read-only attribute, otherwise DeleteFile() will fail */
            if (0 != (attr & mask))
            {
                SetFileAttributes(name, attr & (DWORD)~mask);
            }
            /* Delete it now and if that fails delete it later */
            if (FALSE == DeleteFile(name))
            {
                MoveFileEx(name, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
            }
        }
    }
}
