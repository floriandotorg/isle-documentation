#if !defined(AFX_STDAFX_H)
#define AFX_STDAFX_H

/**
 * @file stdafx.h
 * @brief [AI] Precompiled header including MFC and common control headers for the LEGO Island game codebase.
 * @details [AI] This header is intended for use as the precompiled header in the project's build, providing all necessary
 * MFC includes and configuration macros to speed up compilation. It ensures Windows-specific optimizations and disables inclusion
 * of rarely-used components with VC_EXTRALEAN.
 */

// Exclude rarely-used stuff from Windows headers
#define VC_EXTRALEAN ///< [AI] Macro to minimize inclusion of rarely used components in Windows headers for faster build times.

// [AI] MFC extensions and core components included for user interface and application framework
#include <afxext.h> ///< [AI] Includes MFC extensions used for advanced GUI functionality.
#include <afxwin.h> ///< [AI] Includes MFC core and standard components required for Windows apps.

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> ///< [AI] Enables MFC support for Windows Common Controls (e.g., progress bars, sliders).
#endif              // _AFX_NO_AFXCMN_SUPPORT

#if 0
// [AI] The section below documents addresses of commonly overridden MFC methods for diagnostic or serialization utilities.

// FUNCTION: CONFIG 0x402ca0
// CObject::Serialize

// FUNCTION: CONFIG 0x402cb0
// CObject::AssertValid

// FUNCTION: CONFIG 0x402cc0
// CObject::Dump

// FUNCTION: CONFIG 0x00403c90
// CWnd::BeginModalState

// FUNCTION: CONFIG 0x00403ca0
// CWnd::EndModalState

#endif

#endif // !defined(AFX_STDAFX_H)
