#if !defined(AFX_DETECTDX5_H)
#define AFX_DETECTDX5_H

#include <windows.h>

/**
 * @brief [AI] Checks whether DirectX 5 or a later version is present and available on the system.
 * @details [AI] This function calls DetectDirectX to determine the installed DirectX version and whether DirectX is found, then returns TRUE if the version is 5.0 (0x500) or newer.
 * @return TRUE if DirectX 5.0 or newer is detected, otherwise FALSE. [AI]
 */
extern BOOL DetectDirectX5();

/**
 * @brief [AI] Detects the version of DirectX installed and indicates if it is present.
 * @param p_version [OUT] Receives the version number in hexadecimal (e.g., 0x100, 0x200, 0x300, 0x500). [AI]
 * @param p_found [OUT] Will be set to TRUE or platform indicator if DirectX-related components are found. [AI]
 * @details [AI] Examines the Windows platform and attempts to load key DirectX components (DirectDraw and DirectInput)
 *   to determine the DirectX version installed. This includes probing the system for the presence of the required DLLs and interfaces,
 *   and incrementally setting the version according to available interfaces and features (DirectDraw2, DirectInput, DirectDrawSurface3, etc.). 
 *   Sets both the version and a found/platform marker.
 */
extern void DetectDirectX(unsigned int* p_version, BOOL* p_found);

#endif // !defined(AFX_DETECTDX5_H)
