/**
 * @file
 * @brief
 * Utility function for path handling only using kernel32 calls.
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "string.h"
#include "path.h"


/**
 * @brief
 * Byte nibble to hex character translation table.
 */
static const CHAR HexChars[] = "0123456789abcdef";


VOID Path_Concat(CHAR* dir, const CHAR* member)
{
    DWORD index;
    DWORD pos;

    if (NULL != dir)
    {
        /* Get end of string */
        index = 0;
        while ('\0' != dir[index])
        {
            ++index;
        }

        /* Strip away all backslashes */
        if (index > 0)
        {
            while ((('\\' == dir[index-1]) || ('/' == dir[index-1])) && (index > 0))
            {
                dir[--index] = '\0';
            }
        }

        /* At this point dir[index] always points to zero terminator */

        /* Append second argument */
        if (NULL != member)
        {
            if ('\0' != member[0])
            {
                /* Ensure that there is one (and only one) backslash when concatenating non-empty strings */
                if (index > 0)
                {
                    dir[index++] = '\\';
                }
                pos = 0;
                do
                {
                    dir[index++] = member[pos++];
                }
                while ('\0' != member[pos]);
            }
        }

        /* Ensure result is always zero terminated */
        dir[index] = '\0';
    }
}


VOID Path_Copy(CHAR* dest, const CHAR* source)
{
    String_Copy(dest, source);
}


DWORD Path_HomeDir(CHAR* buffer, DWORD size)
{
    HMODULE handle;
    DWORD result;
    DWORD index;
    
    result = 0;
    
    if ((NULL != buffer) && (0 != size))
    {
        /* Zero initialize buffer */
        for (index = 0; index < size; ++index)
        {
            buffer[index] = '\0';
        }
        
        if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&Path_HomeDir, &handle))
        {
            index = GetModuleFileName(handle, buffer, size);
            
            /* Cut away file portion of the fully qualified file name (including final backslash) */
            while (0 != index)
            {
                /* Initially skip zero terminator */
                --index;
                if (('\\' == buffer[index]) || ('/' == buffer[index]))
                {
                    buffer[index] = '\0';
                    break;
                }
                buffer[index] = '\0';
            }
            result = index;
        }
    }
    
    return result;
}


DWORD Path_TempDir(CHAR* buffer, DWORD size)
{
    DWORD result;

    result = 0;

    if ((NULL != buffer) && (0 != size))
    {
        result = GetTempPath(size, buffer);
        /* Ensure the result is always zero terminated */
        if ((0 == result) || (result > size))
        {
            buffer[0] = '\0';
            result = 0;
        }
            else
            {
                buffer[size - 1] = '\0';
                result++;
            }
    }

    return result;
}


DWORD Path_TempName(CHAR* buffer, const CHAR* prefix, DWORD unique)
{
    DWORD index;
    DWORD pos;
    
    index = 0;
    
    if (NULL != buffer)
    {
        /* Copy prefix */
        if (NULL != prefix)
        {
            while ('\0' != prefix[index])
            {
                buffer[index] = prefix[index];
                ++index;
            }
        }
        /* Append unique number as hex string */
        for (pos = 0; pos < 8; ++pos)
        {
            buffer[index++] = HexChars[0xF & (unique >> (4 * (7 - pos)))];
        }
        /* Append zero terminator */
        buffer[index] = '\0';
    }
    
    return index;
}


BOOL Path_Exists(const CHAR* path)
{
    BOOL result;
    HANDLE handle;
    WIN32_FIND_DATA data;
    
    result = FALSE;
    
    if (NULL != path)
    {
        handle = FindFirstFile(path, &data);
        if (INVALID_HANDLE_VALUE != handle)
        {
            result = TRUE;
            FindClose(handle);
        }
    }
    
    return result;
}
