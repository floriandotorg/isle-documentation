#ifndef MXDEBUG_H
#define MXDEBUG_H

#include "compat.h"

#ifdef _DEBUG

// In debug mode, replace the macro with the function call.
/**
 * @def MxTrace
 * @brief [AI] Macro that expands to the debug trace function _MxTrace in debug builds.
 * @details [AI] Allows printing formatted debug output via _MxTrace. In release builds, this is a no-op.
 */
#define MxTrace _MxTrace

/**
 * @brief [AI] Outputs a formatted debug trace string.
 * @details [AI] Prints a formatted string to the debug output, similar to printf but uses OutputDebugString for Windows. 
 * Used for logging debug messages in debug builds.
 * @param format The printf-style format string. [AI]
 * @param ... Variable argument list for formatting. [AI]
 */
void _MxTrace(const char* format, ...);

/**
 * @brief [AI] Checks and reports the state of the debug heap.
 * @details [AI] Returns the state of the debug heap. This function is primarily a stub with no actual heap checking in this implementation,
 * but could be extended for memory diagnostics during debugging.
 * @return int Always returns 0 in this implementation. [AI]
 */
int DebugHeapState();

#else

// If not debug, MxTrace is a no-op.

#ifdef COMPAT_MODE

// Use variadic args for macro (C99)
/**
 * @def MxTrace
 * @brief [AI] Macro for trace logging, expands to nothing in release or non-debug builds.
 * @details [AI] When not in debug mode, any usage of MxTrace is eliminated at compile time.
 */
#define MxTrace(...)

#else

// MSVC 4.20 does not have variadic args for macros
/**
 * @def MxTrace
 * @brief [AI] Macro for trace logging (non-variadic version, MSVC compatibility), expands to nothing.
 * @details [AI] In release or non-debug builds, any usage of MxTrace is eliminated at compile time.
 */
#define MxTrace(args)

#endif // COMPAT_MODE

#endif // _DEBUG

#endif // MXDEBUG_H
