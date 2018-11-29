/**
 * @file
 * @brief
 * Kitmom TCL extension.
 *
 * @author Klaus Saalfeld
 */
#ifndef KITMON_H_
#define KITMON_H_ KITMON_H_

#include <tcl.h>
#include "platform.h"


#ifndef DLLEXPORT
#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __attribute__((visibility("default")))
#endif
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief
 * Called when DLL is loaded.
 */
VOID Startup(VOID);

/**
 * @brief
 * Called when DLL is unloaded.
 */
VOID TearDown(VOID);

/**
 * @brief
 * Called when Tcl extension is loaded.
 *
 * @details
 * This function will register all commands of the Tcl extension at the Tcl interpreter calling.
 *
 * @param interp        Tcl interpreter.
 *                      If set to NULL the function has no effect and returns TCL_ERROR.
 *
 * @return              TCL_OK on success, or TCL_ERROR if there was an error.
 */
DLLEXPORT int Kitmom_Init(Tcl_Interp* interp);

#ifdef __cplusplus
}
#endif

#endif /* KITMON_H_ */
