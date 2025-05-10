#if !defined(AFX_CONFIG_H)
#define AFX_CONFIG_H

#include "StdAfx.h"
#include "compat.h"
#include "decomp.h"

#include <d3d.h>

// [AI] Forward declarations for engine device enumeration and Direct3D objects.
class LegoDeviceEnumerate;
struct Direct3DDeviceInfo;
struct MxDriver;

#define currentConfigApp ((CConfigApp*) afxCurrentWinApp) ///< [AI] Macro to access the currently running configuration application instance (cast from afxCurrentWinApp).

// [AI] CConfigApp manages hardware/software settings, registry I/O, and user configuration for LEGO Island's setup utility.
// VTABLE: CONFIG 0x00406040
// SIZE 0x108
class CConfigApp : public CWinApp {
public:
	/**
	 * @brief [AI] Constructs the configuration application instance. Primarily zero-initializes members and prepares for initialization.
	 */
	CConfigApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigApp)

public:
	/**
	 * @brief [AI] Initializes the configuration application, checks DirectX availability and system memory, enumerates devices, reads/writes registry, and potentially launches game.
	 * @return TRUE if the application instance starts successfully, otherwise FALSE. [AI]
	 */
	BOOL InitInstance() override;

	/**
	 * @brief [AI] Finalizes and cleans up resources before configuration application exit.
	 * @return Exit code from inherited CWinApp::ExitInstance(). [AI]
	 */
	int ExitInstance() override;
	//}}AFX_VIRTUAL

	// Implementation

	/**
	 * @brief [AI] Writes a string value into the registry under the LEGO Island key.
	 * @param p_key Registry value name/key. [AI]
	 * @param p_value Value to write. [AI]
	 * @return TRUE on success, FALSE if the registry operation fails. [AI]
	 */
	BOOL WriteReg(const char* p_key, const char* p_value) const;

	/**
	 * @brief [AI] Reads a string value from the registry under the LEGO Island key.
	 * @param p_key Registry value name/key to query. [AI]
	 * @param p_value Buffer to receive the value. [AI]
	 * @param p_size Size of p_value buffer. [AI]
	 * @return TRUE if value read, FALSE otherwise. [AI]
	 */
	BOOL ReadReg(LPCSTR p_key, LPCSTR p_value, DWORD p_size) const;

	/**
	 * @brief [AI] Reads a BOOL value ("YES"/"NO") from the registry.
	 * @param p_key Registry value name/key. [AI]
	 * @param p_bool Receives the parsed boolean result. [AI]
	 * @return TRUE if value read and translated to boolean; FALSE otherwise. [AI]
	 */
	BOOL ReadRegBool(LPCSTR p_key, BOOL* p_bool) const;

	/**
	 * @brief [AI] Reads an integer-valued registry entry.
	 * @param p_key Registry value name/key to query. [AI]
	 * @param p_value Integer result written here. [AI]
	 * @return TRUE if value read and converted to int, FALSE otherwise. [AI]
	 */
	BOOL ReadRegInt(LPCSTR p_key, int* p_value) const;

	/**
	 * @brief [AI] Checks if the selected Direct3D device operates in basic RGB color model mode.
	 * @return TRUE if the device is in basic RGB mode, FALSE otherwise. [AI]
	 */
	BOOL IsDeviceInBasicRGBMode() const;

	/**
	 * @brief [AI] Returns the color model (RGB or other) used by the hardware Direct3D device.
	 * @return D3DCOLORMODEL value from hardware device. [AI]
	 */
	D3DCOLORMODEL GetHardwareDeviceColorModel() const;

	/**
	 * @brief [AI] Determines if the currently selected driver is the primary driver detected by enumeration.
	 * @return TRUE if this is the primary driver, FALSE otherwise. [AI]
	 */
	BOOL IsPrimaryDriver() const;

	/**
	 * @brief [AI] Loads all settings from the registry if present, else selects appropriate default device/settings.
	 * @return TRUE if any settings were modified, FALSE if all matches registry. [AI]
	 */
	BOOL ReadRegisterSettings();

	/**
	 * @brief [AI] Ensures all configuration values are legal/compatible, correcting them if needed (e.g., bit depths, surface flips).
	 * @return TRUE if any values were changed, otherwise FALSE. [AI]
	 */
	BOOL ValidateSettings();

	/**
	 * @brief [AI] Returns bit mask status for the conditional device-rendered bit depth, depending on current device and mode.
	 * @return Status flags (DWORD) representing device render capabilities (dword flags). [AI]
	 */
	DWORD GetConditionalDeviceRenderBitDepth() const;

	/**
	 * @brief [AI] Returns bit mask status for the currently active device's rendering status (e.g., can it render in a certain mode).
	 * @return DWORD status bitfield. [AI]
	 */
	DWORD GetDeviceRenderBitStatus() const;

	/**
	 * @brief [AI] Adjusts display (screen) bit depth according to the device's rendering capabilities and configuration.
	 * @return TRUE if m_display_bit_depth changed, FALSE otherwise. [AI]
	 */
	BOOL AdjustDisplayBitDepthBasedOnRenderStatus();

	/**
	 * @brief [AI] Saves current hardware/gameplay option selections to the registry under LEGO Island.
	 */
	void WriteRegisterSettings() const;

	//{{AFX_MSG(CConfigApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	/**
	 * @brief [AI] Checks if LEGO Island is not already running (by window title/class), brings it to foreground if it is.
	 * @return TRUE if it is not running, FALSE otherwise. [AI]
	 */
	BOOL IsLegoNotRunning();

public:
	LegoDeviceEnumerate* m_device_enumerator; ///< [AI] Enumerates all supported Direct3D and DirectSound devices, used for configuration panel. Owned by this class.
	MxDriver* m_driver;                       ///< [AI] Currently selected (or default) 3D hardware driver. Managed externally or by enumerator. 
	Direct3DDeviceInfo* m_device;             ///< [AI] Selected Direct3D device structure, describes device capabilities and mode. Not owned by this class.
	int m_display_bit_depth;                  ///< [AI] User-selected or optimal display (screen) bit depth (8/16/etc.).
	BOOL m_flip_surfaces;                     ///< [AI] If TRUE, enables flipping display buffers during rendering (double-buffering).
	BOOL m_full_screen;                       ///< [AI] TRUE for fullscreen Direct3D, FALSE for windowed.
	BOOL m_3d_video_ram;                      ///< [AI] TRUE if back-buffering should use 3D video RAM, else system RAM.
	BOOL m_wide_view_angle;                   ///< [AI] If TRUE, increases camera field-of-view for wider display.
	BOOL m_3d_sound;                          ///< [AI] TRUE if 3D positional audio is enabled.
	BOOL m_draw_cursor;                       ///< [AI] TRUE if in-game mouse cursor is drawn.
	BOOL m_use_joystick;                      ///< [AI] Enables joystick/gamepad input if supported and selected.
	int m_joystick_index;                     ///< [AI] Index of selected joystick (if multiple present).
	BOOL m_run_config_dialog;                 ///< [AI] Set to TRUE if the configuration dialog should run (otherwise will read reg & launch game).
	int m_model_quality;                      ///< [AI] Detail/complexity level for 3D models (0 = low, 1 = medium, 2 = high).
	int m_texture_quality;                    ///< [AI] Quality (bit-depth, filtering) of loaded textures (0 = low, 1 = high).
	undefined m_unk0x100[4];                  ///< [AI] [AI_SUGGESTED_NAME: padding_or_reserved4] Reserved, unknown (possibly padding or future expansion).
	BOOL m_music;                             ///< [AI] If TRUE, enables background music.
};

// SYNTHETIC: CONFIG 0x00402cd0
// CConfigApp::`scalar deleting destructor'

// FUNCTION: CONFIG 0x402c20
// CConfigApp::_GetBaseMessageMap

// FUNCTION: CONFIG 0x402c30
// CConfigApp::GetMessageMap

// GLOBAL: CONFIG 0x406008
// CConfigApp::messageMap

// GLOBAL: CONFIG 0x406010
// CConfigApp::_messageEntries

#endif // !defined(AFX_CONFIG_H)
