#ifndef MXTYPES_H
#define MXTYPES_H

/**
 * @typedef MxU8
 * @brief [AI] 8-bit unsigned integer type used throughout the engine for small values and binary data.
 */
typedef unsigned char MxU8; ///< [AI]

/**
 * @typedef MxS8
 * @brief [AI] 8-bit signed integer type used for small signed values and data.
 */
typedef signed char MxS8; ///< [AI]

/**
 * @typedef MxU16
 * @brief [AI] 16-bit unsigned integer type.
 */
typedef unsigned short MxU16; ///< [AI]

/**
 * @typedef MxS16
 * @brief [AI] 16-bit signed integer type.
 */
typedef signed short MxS16; ///< [AI]

/**
 * @typedef MxU32
 * @brief [AI] 32-bit unsigned integer type, main unsigned integer for many resource IDs, counters, etc.
 */
typedef unsigned int MxU32; ///< [AI]

/**
 * @typedef MxS32
 * @brief [AI] 32-bit signed integer type, principal signed integer for main calculations, indexes, etc.
 */
typedef signed int MxS32; ///< [AI]

#ifdef _MSC_VER
/**
 * @typedef MxU64
 * @brief [AI] 64-bit unsigned integer, represented as unsigned __int64 on MSVC, for large values and file positions.
 */
typedef unsigned __int64 MxU64; ///< [AI]
/**
 * @typedef MxS64
 * @brief [AI] 64-bit signed integer, represented as signed __int64 on MSVC.
 */
typedef signed __int64 MxS64; ///< [AI]
#else
/**
 * @typedef MxU64
 * @brief [AI] 64-bit unsigned integer type for file positions and large data, version for non-MSVC compilers.
 */
typedef unsigned long long int MxU64; ///< [AI]
/**
 * @typedef MxS64
 * @brief [AI] 64-bit signed integer type for large signed values, version for non-MSVC compilers.
 */
typedef signed long long int MxS64; ///< [AI]
#endif

/**
 * @typedef MxFloat
 * @brief [AI] 32-bit floating point type, main float type for 3D coordinates, matrices, and general calculations.
 */
typedef float MxFloat; ///< [AI]

/**
 * @typedef MxDouble
 * @brief [AI] 64-bit floating point type, used for precise calculations or storage of high-precision data.
 */
typedef double MxDouble; ///< [AI]

/**
 * @typedef MxLong
 * @brief [AI] Signed integer with 32-bit width on all platforms, guaranteed to match 'long' on MSVC. Used for compatibility with Windows DLL linkage.
 */
#if defined(_MSC_VER)
typedef long MxLong; ///< [AI]
#else
typedef int MxLong; ///< [AI]
#endif

/**
 * @typedef MxULong
 * @brief [AI] Unsigned integer with 32-bit width on all platforms, guaranteed to match 'unsigned long' on MSVC. Used for Windows DLL compatibility.
 */
#if defined(_MSC_VER)
typedef unsigned long MxULong; ///< [AI]
#else
typedef unsigned int MxULong; ///< [AI]
#endif

/**
 * @typedef MxTime
 * @brief [AI] Signed 32-bit integer used for time values (e.g., ticks, time offsets).
 */
typedef MxS32 MxTime; ///< [AI]

/**
 * @typedef MxResult
 * @brief [AI] Result type for functions, usually uses SUCCESS (0) or FAILURE (-1) as return value, can supply extended result codes.
 */
typedef MxLong MxResult; ///< [AI]

//! @def SUCCESS
//! @brief [AI] Macro for function success return value, always 0.
#ifndef SUCCESS
#define SUCCESS 0
#endif

//! @def FAILURE
//! @brief [AI] Macro for function failure return value, always -1.
#ifndef FAILURE
#define FAILURE -1
#endif

/**
 * @typedef MxBool
 * @brief [AI] Boolean type, 1 byte in size, with TRUE (1) and FALSE (0) macros for clarity.
 */
typedef MxU8 MxBool; ///< [AI]

//! @def TRUE
//! @brief [AI] Macro for boolean true value, always 1.
#ifndef TRUE
#define TRUE 1
#endif

//! @def FALSE
//! @brief [AI] Macro for boolean false value, always 0.
#ifndef FALSE
#define FALSE 0
#endif

//! @def NULL
//! @brief [AI] Macro for null pointer, always 0.
#ifndef NULL
#define NULL 0
#endif

/**
 * @def TWOCC(a, b)
 * @brief [AI] Macro to compose a 16-bit code from two 8-bit characters (e.g., for type IDs).
 * @param a First character (low byte) [AI]
 * @param b Second character (high byte) [AI]
 * @details [AI] Returns an integer where the low byte is 'a' and the high byte is 'b'.
 */
#define TWOCC(a, b) (((a) << 0) | ((b) << 8)) ///< [AI]

/**
 * @def FOURCC(a, b, c, d)
 * @brief [AI] Macro to compose a 32-bit code from four 8-bit characters (e.g., for resource and chunk IDs).
 * @param a First character (lowest byte) [AI]
 * @param b Second character [AI]
 * @param c Third character [AI]
 * @param d Fourth character (highest byte) [AI]
 * @details [AI] Used for things like identifying file/resource chunk types in SI files.
 */
#define FOURCC(a, b, c, d) (((a) << 0) | ((b) << 8) | ((c) << 16) | ((d) << 24)) ///< [AI]

/**
 * @union FlagBitfield
 * @brief [AI] Union that provides a convenient bit field view of a byte for flag manipulation.
 * @details [AI] Used for cases where a value needs to provide quick access to individual flag bits, e.g., status, types, etc. The 8 bits (m_bit0..m_bit7) can be accessed individually.
 */
typedef union {
	struct {
		MxU8 m_bit0 : 1; ///< [AI] Least significant bit of the flag byte.
		MxU8 m_bit1 : 1; ///< [AI] 
		MxU8 m_bit2 : 1; ///< [AI]
		MxU8 m_bit3 : 1; ///< [AI]
		MxU8 m_bit4 : 1; ///< [AI]
		MxU8 m_bit5 : 1; ///< [AI]
		MxU8 m_bit6 : 1; ///< [AI]
		MxU8 m_bit7 : 1; ///< [AI] Most significant bit of the flag byte.
	};
	// BYTE all; // ? [AI]
} FlagBitfield; ///< [AI]

#endif // MXTYPES_H
