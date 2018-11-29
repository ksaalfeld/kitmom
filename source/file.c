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
    
    if (NULL != name)
    {
        attr = GetFileAttributes(name);
        if ((INVALID_FILE_ATTRIBUTES != attr) && (0 == (attr & FILE_ATTRIBUTE_DIRECTORY)))
        {
            /* Remove read-only attribute, otherwise DeleteFile() will fail */
            if (0 != (attr & FILE_ATTRIBUTE_READONLY))
            {
                SetFileAttributes(name, attr & (~(DWORD)FILE_ATTRIBUTE_READONLY));
            }
            /* Delete it now and if that fails delete it later */
            if (FALSE == DeleteFile(name))
            {
                MoveFileEx(name, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
            }
        }
    }
}
