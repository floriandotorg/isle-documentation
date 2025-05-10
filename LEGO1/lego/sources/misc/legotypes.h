/*
	This unpublished source code contains trade secrets and
	copyrighted materials which are the property of Mindscape, Inc.
	Unauthorized use, copying or distribution is a violation of U.S.
	and international laws and is strictly prohibited.
*/

/**
 * @file legotypes.h
 * @brief [AI] Defines basic fixed-width data types and platform-neutral constants for LEGO Island codebase.
 * @details [AI] This file provides typedefs for integer and floating point types as well as macros for success/error codes and boolean logic, ensuring consistent use throughout the game.
 */

#ifndef __LEGOTYPES_H
#define __LEGOTYPES_H

#ifndef TRUE
#define TRUE 1 ///< [AI] Boolean TRUE value.
#endif

#ifndef FALSE
#define FALSE 0 ///< [AI] Boolean FALSE value.
#endif

#ifndef NULL
#define NULL 0 ///< [AI] Null pointer value (C/C++ semantics).
#endif

#ifndef SUCCESS
#define SUCCESS 0 ///< [AI] Used to indicate a successful operation in result codes.
#endif

#ifndef FAILURE
#define FAILURE -1 ///< [AI] Used to indicate a failed operation in result codes.
#endif

/**
 * @typedef LegoS8
 * @brief [AI] Signed 8-bit integer type used throughout LEGO Island.
 */
typedef char LegoS8;

/**
 * @typedef LegoU8
 * @brief [AI] Unsigned 8-bit integer type used throughout LEGO Island.
 */
typedef unsigned char LegoU8;

/**
 * @typedef LegoS16
 * @brief [AI] Signed 16-bit integer type for cross-platform compatibility.
 */
typedef short LegoS16;

/**
 * @typedef LegoU16
 * @brief [AI] Unsigned 16-bit integer type for cross-platform compatibility.
 */
typedef unsigned short LegoU16;

/**
 * @typedef LegoS32
 * @brief [AI] Signed 32-bit integer type for cross-platform compatibility.
 */
typedef long LegoS32;

/**
 * @typedef LegoU32
 * @brief [AI] Unsigned 32-bit integer type for cross-platform compatibility.
 */
typedef unsigned long LegoU32;

/**
 * @typedef LegoFloat
 * @brief [AI] Floating point type used throughout LEGO Island. (Usually float, 32-bit IEEE)
 */
typedef float LegoFloat;

/**
 * @typedef LegoChar
 * @brief [AI] Alias for `char`, for use in character/byte data and string handling.
 */
typedef char LegoChar;

/**
 * @typedef LegoBool
 * @brief [AI] Boolean value used throughout the codebase. Defined as LegoU8 (0 for FALSE, 1 for TRUE).
 */
typedef LegoU8 LegoBool;

/**
 * @typedef LegoTime
 * @brief [AI] Time value, typically used for tick counts, durations, or timing; defined as a signed 32-bit integer.
 */
typedef LegoS32 LegoTime;

/**
 * @typedef LegoResult
 * @brief [AI] Function result type (return code): typically SUCCESS (0) or FAILURE (-1).
 */
typedef LegoS32 LegoResult;

#endif // __LEGOTYPES_H
