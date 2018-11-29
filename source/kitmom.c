/**
 * @file
 * @brief
 * Kitmom TCL extension.
 *
 * @author Klaus Saalfeld
 */
#include <tcl.h>
#include "platform.h"
#include "path.h"
#include "file.h"
#include "memory.h"
#include "log.h"
#include "filetree.h"
#include "kitmom.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Check if the specified file or directory is within the temporary location.
 *
 * @param path          Path to check.
 *                      If set to NULL the function returns FALSE.
 *
 * @return              FALSE if NOT within temporary location, TRUE otherwise.
 */
static BOOL InsideTempDir(const CHAR* path);

/**
 * @brief
 * Called for each file and directory found.
 *
 * @param dir           Directory containing the specified file.
 * @param file          File (relative to given directory).
 *                      Is NULL when directory is visited.
 *
 * @return              Value to sum.
 */
static DWORD Iterator(const CHAR* dir, const CHAR* file);

/**
 * @brief
 * TCL command that returns temporary location kitmom is managing.
 */
static int Kitmom_Dir(ClientData data, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[]);

#ifdef __cplusplus
}
#endif

/**
 * @brief
 * Maximum path length in characters (including zero terminator)
 */
#define MAX_SIZE (MAX_PATH + 1)

/**
 * @brief
 * Location of Windows temporary directory.
 *
 * @details
 * Typically this is "<drive>:\Users\<name>\AppData\Local\Temp"
 */
static CHAR TempDir[MAX_SIZE];

/**
 * @brief
 * Install directory of executable.
 */
static CHAR HomeDir[MAX_SIZE];

/**
 * @brief
 * Temporary location kitmom cares about.
 */
static CHAR PlayDir[MAX_SIZE];


static BOOL InsideTempDir(const CHAR* path)
{
    DWORD index;
    BOOL result;

    result = FALSE;

    if (NULL != path)
    {
        index = 0;
        if (('\0' != path[index]) && ('\0' != TempDir[index]))
        {
            result = TRUE;
            do
            {
                if ((index >= MAX_SIZE) || (path[index] != TempDir[index]) || ('\0' == path[index]))
                {
                    result = FALSE;
                    break;
                }
            }
            while ('\0' != TempDir[++index]);
        }
    }

    return result;
}


static DWORD Iterator(const CHAR* dir, const CHAR* file)
{
    DWORD result;
    CHAR* str;

    result = 0;

    str = Memory_Allocate(MAX_PATH + 1);
    if (NULL != str)
    {
        /* Concatenate arguments */
        Path_Copy(str, dir);
        Path_Concat(str, file);

        /* Expand to a fully qualified path */
        GetFullPathName(str, MAX_PATH, str, NULL);
        
        /* If there is no such file there is no such work */
        if (Path_Exists(str))
        {
            /* As a measure of safety we reject all files and
             * directories that are NOT within the temporary location.
             */
            if (InsideTempDir(str))
            {
                File_DeleteAfterReboot(str);
                Log_Write(str);
                result++;
            }
        }

        Memory_Free(str);
    }

    return result;
}


VOID Startup(VOID)
{
    CHAR buffer[32];
    DWORD pid;
    
    Path_TempDir(TempDir, MAX_SIZE);
    Path_HomeDir(HomeDir, MAX_SIZE);
    
    if (InsideTempDir(HomeDir))
    {
        /* We're running from a temporary location.
         * Most likely this means we are running within a starpack.
         */
        Path_Copy(PlayDir, HomeDir);
    }
        else
        {
            /* We're not running from a temporary location.
             * However we want to supply a temporary location to the user.
             * So we create one and take care that everything within this location gets erased again.
             */
            pid = GetCurrentProcessId();
            do
            {
                Path_Copy(PlayDir, TempDir);
                Path_TempName(buffer, "TCL", pid);
                Path_Concat(PlayDir, buffer);
                /* Some day we find a name that does not exist yet */
                pid++;
            }
            while (Path_Exists(PlayDir));
            CreateDirectory(PlayDir, NULL);
        }
}


VOID TearDown(VOID)
{
    /* Start a log file in our temporary location */
    Log_Start(PlayDir, "kitmom.log");
    Log_Write("# Started kitmom processing log");
    
    FileTree_Iterate(PlayDir, NULL, &Iterator);
    
    /* End log */
    Log_Write("# End of file");
}


static int Kitmom_Dir(ClientData data, Tcl_Interp* interp, int objc, Tcl_Obj* const objv[])
{
    int result;
    (void)data;
    
    result = TCL_ERROR;
    
    if (objc == 1)
    {
        Tcl_SetObjResult(interp, Tcl_NewStringObj(PlayDir, -1));
        result = TCL_OK;
    }
        else
        {
            /* This function does not expect any arguments */
            Tcl_WrongNumArgs(interp, 1, objv, NULL);
        }
    
    return result;
}


DLLEXPORT int Kitmom_Init(Tcl_Interp* interp)
{
    int result;
    
    result = TCL_ERROR;
    
    if (NULL != Tcl_InitStubs(interp, "8.6", 0))
    {
        if (TCL_ERROR != Tcl_PkgProvide(interp, "kitmom", "1.0.0"))
        {
            /* The "init" command is a dummy command only that is present only
             * so that the interface is compatible with the interface we have for Linux.
             * It does the same as the "dir" command and only returns the temporary location.
             */
            Tcl_CreateObjCommand(interp, "::kitmom::init", Kitmom_Dir, NULL, NULL);
            Tcl_CreateObjCommand(interp, "::kitmom::dir", Kitmom_Dir, NULL, NULL);
            result = TCL_OK;
        }
    }
    
    return result;
}
