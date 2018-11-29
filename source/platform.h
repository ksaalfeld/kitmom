/**
 * @file
 * @brief
 * Platform specific includes.
 *
 * @author Klaus Saalfeld
 */
#ifndef PLATFORM_H_
#define PLATFORM_H_ PLATFORM_H_

/* Suppose we have at least Windows XP */
#define _WIN32_WINNT 0x502
#define WINVER 0x502

#define WIN32_LEAN_AND_MEAN
#include <windef.h>
#include <winnt.h>
#include <windows.h>

#endif /* PLATFORM_H_ */
