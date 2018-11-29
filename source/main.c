/**
 * @file
 * @brief
 * Entrypoint function
 *
 * @author Klaus Saalfeld
 */
#include "platform.h"
#include "kitmom.h"
#include "main.h"


BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    (void)instance;
    (void)reserved;
    
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            Startup();
            break;
        case DLL_PROCESS_DETACH:
            TearDown();
            break;
        default:
            break;
    }
    
    return TRUE;
}
