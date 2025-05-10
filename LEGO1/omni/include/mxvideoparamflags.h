#ifndef MXVIDEOPARAMFLAGS_H
#define MXVIDEOPARAMFLAGS_H

#include "mxtypes.h"

#include <windows.h>

/**
 * @brief [AI] Manages video parameter flags, providing an abstraction for various video settings such as fullscreen, buffer flipping, color depth, and view angle controls.
 * 
 * This class encapsulates bit field flags that are used by the LEGO Island engine to toggle and query low-level video settings.
 * 
 * The configuration controlled here is passed, for example, into the DirectX initialization process to control rendering modes at runtime.
 * 
 * Each group of flags is split into separate bit field instances to match the structure and packing requirements of the game.
 * 
 * @details [AI] The first field (m_flags1) stores primary drawing option flags like fullscreen, flip surfaces, buffer count, color depth, and view angle; the second field (m_flags2) stores additional flags (purpose for these specific bits may be defined by video device requirements and engine conventions).
 */
class MxVideoParamFlags {
public:

	/**
	 * @brief [AI] Constructs an MxVideoParamFlags instance and sets default values as found in the original game.
	 */
	MxVideoParamFlags();

	/**
	 * @brief [AI] Enable or disable fullscreen mode.
	 * @param p_e True to enable fullscreen, false for windowed. [AI]
	 */
	void SetFullScreen(MxBool p_e) { m_flags1.m_bit0 = p_e; }

	/**
	 * @brief [AI] Toggle the use of flip (page flipping) for surfaces.
	 * @param p_e True to enable flipping, false to disable. [AI]
	 */
	void SetFlipSurfaces(MxBool p_e) { m_flags1.m_bit1 = p_e; }

	/**
	 * @brief [AI] Toggle the use of a back buffer (double-buffered rendering).
	 * @param p_e True for double buffering, false for single buffer. [AI]
	 */
	void SetBackBuffers(MxBool p_e) { m_flags1.m_bit2 = p_e; }

	/**
	 * @brief [AI] Set an additional primary flag; exact usage is unknown but may control a video mode detail.
	 * @param p_e Value to assign to primary flag 3. [AI]
	 */
	void SetF1bit3(MxBool p_e) { m_flags1.m_bit3 = p_e; }

	/**
	 * @brief [AI] Specify whether 16-bit color depth should be used for rendering.
	 * @param p_e True for 16-bit color; false for 8-bit or 32-bit depending on the rest of the configuration. [AI]
	 */
	void Set16Bit(MxBool p_e) { m_flags1.m_bit5 = p_e; }

	/**
	 * @brief [AI] Enable or disable a wider field of view for 3D rendering.
	 * @param p_e True to use a wider field of view. [AI]
	 */
	void SetWideViewAngle(MxBool p_e) { m_flags1.m_bit6 = p_e; }

	/**
	 * @brief [AI] Set an additional flag (purpose unknown; originally used by the engine for extension).
	 * @param p_e Value to assign to primary flag 7. [AI]
	 */
	void SetF1bit7(MxBool p_e) { m_flags1.m_bit7 = p_e; }

	/**
	 * @brief [AI] Set secondary flag 0 (often used for internal video logic).
	 * @param p_e Value for the corresponding secondary flag. [AI]
	 */
	void SetF2bit0(MxBool p_e) { m_flags2.m_bit0 = p_e; }

	/**
	 * @brief [AI] Set secondary flag 1 (often used for internal video logic).
	 * @param p_e Value for the corresponding secondary flag. [AI]
	 */
	void SetF2bit1(MxBool p_e) { m_flags2.m_bit1 = p_e; }

	/**
	 * @brief [AI] Get whether fullscreen mode is enabled.
	 * @return True if fullscreen mode is enabled. [AI]
	 */
	MxBool GetFullScreen() { return m_flags1.m_bit0; }

	/**
	 * @brief [AI] Get whether page flipping of surfaces is enabled.
	 * @return True if flip surfaces is enabled. [AI]
	 */
	MxBool GetFlipSurfaces() { return m_flags1.m_bit1; }

	/**
	 * @brief [AI] Get whether back buffering (double buffering) is enabled.
	 * @return True if back buffers are enabled. [AI]
	 */
	MxBool GetBackBuffers() { return m_flags1.m_bit2; }

	/**
	 * @brief [AI] Get the value of primary flag 3. The specific meaning is currently unknown.
	 * @return Value of flag 3. [AI]
	 */
	MxBool GetF1bit3() { return m_flags1.m_bit3; }

	/**
	 * @brief [AI] Get whether 16-bit rendering mode is selected.
	 * @return True if 16-bit mode is enabled. [AI]
	 */
	MxBool Get16Bit() { return m_flags1.m_bit5; }

	/**
	 * @brief [AI] Get whether a wide view angle is enabled.
	 * @return True if wide view angle is enabled. [AI]
	 */
	MxBool GetWideViewAngle() { return m_flags1.m_bit6; }

	/**
	 * @brief [AI] Get the value of secondary flag 0.
	 * @return Value of flag 0 in m_flags2. [AI]
	 */
	MxBool GetF2bit0() { return m_flags2.m_bit0; }

	/**
	 * @brief [AI] Get the value of secondary flag 1.
	 * @return Value of flag 1 in m_flags2. [AI]
	 */
	MxBool GetF2bit1() { return m_flags2.m_bit1; }

private:
	FlagBitfield m_flags1; ///< @brief [AI] Primary set of rendering flags packed into a bitfield.
	FlagBitfield m_flags2; ///< @brief [AI] Secondary set of rendering flags packed into a bitfield.
};

#endif // MXVIDEOPARAMFLAGS_H
