#ifndef STLCOMPAT_H
#define STLCOMPAT_H

/// @file
/// @brief [AI] STL compatibility layer header to provide consistent STL (Standard Template Library) types and algorithms across different compiler versions.
/// @details [AI] This header abstracts away differences between compiler STL implementations by conditionally including a custom STL emulation layer (`mxstl.h`) for old MSVC 4.2 compilers, or by importing standard STL types if available (for modern compilers). By including this file, code can rely on commonly used STL containers (`vector`, `list`, `set`, etc.) regardless of environment. [AI]

#include "compat.h"

#if defined(_MSC_VER) && _MSC_VER <= MSVC420_VERSION
// Disable "nonstandard extension used : 'bool'" warning spam
#pragma warning(disable : 4237)
#include "mxstl.h" ///< @include [AI] Custom Mindscape STL emulation header for legacy MSVC compilers. [AI]
#else
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>
using std::list;     ///< @brief [AI] Provides std::list as list for compatibility. [AI]
using std::map;      ///< @brief [AI] Provides std::map as map for compatibility. [AI]
using std::multiset; ///< @brief [AI] Provides std::multiset as multiset for compatibility. [AI]
using std::pair;     ///< @brief [AI] Provides std::pair as pair for compatibility. [AI]
using std::set;      ///< @brief [AI] Provides std::set as set for compatibility. [AI]
using std::vector;   ///< @brief [AI] Provides std::vector as vector for compatibility. [AI]
#endif

#endif // STLCOMPAT_H
