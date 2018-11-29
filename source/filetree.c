/**
 * @file
 * @brief
 * File iterator only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "memory.h"
#include "path.h"
#include "filetree.h"


DWORD FileTree_Iterate(const CHAR* dir, const CHAR* file, FILETREE_CALLBACK_T func)
{
    CHAR* str;
    CHAR* search;
    DWORD attr;
    DWORD result;
    HANDLE handle;
    WIN32_FIND_DATA data;
    
    result = 0;
    
    if ((NULL != dir) && (NULL != func))
    {
        str = Memory_Allocate(MAX_PATH + 1);
        if (NULL != str)
        {
            /* Build the base path to operate on */
            Path_Copy(str, dir);
            Path_Concat(str, file);

            /* If the specified name refers to a file (and not a directory)
             * there is nothing we need to do here.
             */
            attr = GetFileAttributes(str);
            if ((attr != INVALID_FILE_ATTRIBUTES) && (0 != (attr & FILE_ATTRIBUTE_DIRECTORY)))
            {
                search = Memory_Allocate(MAX_PATH + 1);
                if (NULL != search)
                {
                    /* Build search mask for everything that is within supplied directory */
                    Path_Copy(search, str);
                    Path_Concat(search, "*");

                    /* Iterate over files and subdirectories */
                    handle = FindFirstFile(search, &data);
                    if (INVALID_HANDLE_VALUE != handle)
                    {
                        do
                        {
                            /* Process file or directory here */
                            if (0 != (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                            {
                                /* Ignore "." and ".." pseudo directories */
                                if ('.' != data.cFileName[0])
                                {
                                    /* Here we have found a real sub-directory.
                                     * Recurse and process that sub-directory.
                                     */
                                    result += FileTree_Iterate(str, data.cFileName, func);
                                }
                            }
                                else
                                {
                                    /* Here we have found a file */
                                    result += func(str, data.cFileName);
                                }
                        }
                        while (FindNextFile(handle, &data));

                        FindClose(handle);
                    }
                    Memory_Free(search);
                }

                /* At this point everything within specified directory has been processed */
                result += func(str, NULL);
            }

            Memory_Free(str);
        }
    }

    return result;
}
