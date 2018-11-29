/**
 * @file
 * @brief
 * Entrypoint function
 *
 * @author Klaus Saalfeld
 */
#ifndef MAIN_H_
#define MAIN_H_ MAIN_H_

#include "platform.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * DLL entry point function.
 *
 * @param instance      Handle to DLL module.
 * @param reason        Can be one value of:
 *                      - DLL_PROCESS_ATTACH
 *                      - DLL_PROCESS_DETACH
 *                      - DLL_THREAD_ATTACH
 *                      - DLL_THREAD_DETACH
 * @param reserved      Dynamic or static load/free.
 *
 * @return              TRUE on success.
 */
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_ */
