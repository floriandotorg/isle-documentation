#ifndef ISLEAPP_H
#define ISLEAPP_H

#include "mxtypes.h"
#include "mxvideoparam.h"

#include <windows.h>

// SIZE 0x8c
/**
 * @brief [AI] Main application class for LEGO Island. Manages the main game window and overall game flow, including resource paths, graphics, input, cursor state, registry settings, and config handling.
 * @details [AI] This class acts as the entry point of the LEGO Island game and handles initial setup, window creation, configuration loading, registry values, video settings, cursor handling, the primary update/tick loop, and communication with the underlying engine (LegoOmni and subsystems). 
 */
class IsleApp {
public:
	/**
	 * @brief [AI] Constructor. Initializes the application, default config, and allocates/sets up class members.
	 */
	IsleApp();

	/**
	 * @brief [AI] Destructor. Cleans up resources, destroys the engine, and deallocates buffers.
	 */
	~IsleApp();

	/**
	 * @brief [AI] Gracefully closes down the LEGO Island game, including engine teardown and saving player progress.
	 * @details [AI] Saves game state and player progress, triggers object destruction and world removal, handles queued input, and synchronizes shutdown with the data streamer.
	 */
	void Close();

	/**
	 * @brief [AI] Initializes the core LEGO Island engine with the current settings and media path.
	 * @return TRUE if the engine setup was successful, FALSE otherwise. [AI]
	 */
	BOOL SetupLegoOmni();

	/**
	 * @brief [AI] Configures video mode and 3D device flags for rendering (fullscreen, backbuffers, bit depth, etc).
	 * @param fullScreen Fullscreen mode enable flag. [AI]
	 * @param flipSurfaces Double buffering/flip surfaces flag. [AI]
	 * @param backBuffers Flag for VRAM backbuffer usage (see registry). [AI]
	 * @param using8bit If true, prefer 8-bit color. [AI]
	 * @param using16bit If true, prefer 16-bit color. [AI]
	 * @param param_6 Unknown video option (propagated to SetF2bit0). [AI]
	 * @param param_7 Unknown video option (propagated to SetF1bit7). [AI]
	 * @param wideViewAngle Enables wide field-of-view. [AI]
	 * @param deviceId 3D video device identifier string. [AI]
	 */
	void SetupVideoFlags(
		BOOL fullScreen,
		BOOL flipSurfaces,
		BOOL backBuffers,
		BOOL using8bit,
		BOOL using16bit,
		BOOL param_6,
		BOOL param_7,
		BOOL wideViewAngle,
		char* deviceId
	);

	/**
	 * @brief [AI] Creates the application window, registers the window class, loads icons/cursors, and sets up video and config.
	 * @param hInstance Handle to current application instance. [AI]
	 * @param lpCmdLine Command line arguments. [AI]
	 * @return [AI] SUCCESS or FAILURE as MxResult depending on window and system initialization.
	 */
	MxResult SetupWindow(HINSTANCE hInstance, LPSTR lpCmdLine);

	/**
	 * @brief [AI] Reads a string value from the LEGO Island registry key under HKLM.
	 * @param name Registry value name to read (e.g. "diskpath", "cdpath", etc). [AI]
	 * @param outValue Pointer to string buffer to receive the value. [AI]
	 * @param outSize Size of outValue buffer in bytes. [AI]
	 * @return TRUE if the value was successfully read. [AI]
	 */
	BOOL ReadReg(LPCSTR name, LPSTR outValue, DWORD outSize);

	/**
	 * @brief [AI] Reads a boolean (YES/NO string) value from registry.
	 * @param name Registry value to read. [AI]
	 * @param out Pointer to BOOL to receive value. [AI]
	 * @return TRUE if the value was read and parsed successfully. [AI]
	 */
	BOOL ReadRegBool(LPCSTR name, BOOL* out);

	/**
	 * @brief [AI] Reads an integer value from registry.
	 * @param name Registry value to read. [AI]
	 * @param out Pointer to int to receive value. [AI]
	 * @return TRUE if the value was read and parsed successfully. [AI]
	 */
	BOOL ReadRegInt(LPCSTR name, int* out);

	/**
	 * @brief [AI] Loads all configuration from the registry (disk path, CD path, sound, joystick, quality, etc) and applies defaults if necessary.
	 * @details [AI] Also applies config to MxOmni global paths and fills out member variables for later use.
	 */
	void LoadConfig();

	/**
	 * @brief [AI] Executes a single frame tick/update for the game, managing timing, engine state, initial/first load sequence, and background audio.
	 * @param sleepIfNotNextFrame If true, yields processor if it's not time for next frame. [AI]
	 */
	void Tick(BOOL sleepIfNotNextFrame);

	/**
	 * @brief [AI] Sets the current mouse cursor based on application or game state.
	 * @param wParam Cursor identifier (see Lego cursor enum). [AI]
	 */
	void SetupCursor(WPARAM wParam);

	/// @name Window/Cursor Properties Accessors [AI]
	///@{
	/**
	 * @brief [AI] Returns the handle to the main application window.
	 */
	HWND GetWindowHandle() { return m_windowHandle; }

	/**
	 * @brief [AI] Returns the current frame delta (milliseconds per game frame).
	 */
	MxLong GetFrameDelta() { return m_frameDelta; }

	/**
	 * @brief [AI] Returns TRUE if the game is in fullscreen mode.
	 */
	BOOL GetFullScreen() { return m_fullScreen; }

	/**
	 * @brief [AI] Gets the HCURSOR currently active for the application.
	 */
	HCURSOR GetCursorCurrent() { return m_cursorCurrent; }

	/**
	 * @brief [AI] Gets the HCURSOR representing the "busy" cursor.
	 */
	HCURSOR GetCursorBusy() { return m_cursorBusy; }

	/**
	 * @brief [AI] Gets the HCURSOR representing the "not allowed" cursor.
	 */
	HCURSOR GetCursorNo() { return m_cursorNo; }

	/**
	 * @brief [AI] Returns TRUE if the application is drawing the custom cursor.
	 */
	BOOL GetDrawCursor() { return m_drawCursor; }
	///@}

	/**
	 * @brief [AI] Sets application window active status (focus/active state).
	 * @param p_windowActive TRUE if the window is active. [AI]
	 */
	void SetWindowActive(BOOL p_windowActive) { m_windowActive = p_windowActive; }

private:
	LPSTR m_hdPath;            ///< [AI] Allocated string with current hard disk data path (for game files/scripts/assets). Set from registry/config. 
	LPSTR m_cdPath;            ///< [AI] Allocated string with CD-ROM data path.
	LPSTR m_deviceId;          ///< [AI] 3D/graphics device identifier, used for rendering.
	LPSTR m_savePath;          ///< [AI] Base save path location for player progress.
	BOOL m_fullScreen;         ///< [AI] Fullscreen mode setting (registry: "Full Screen").
	BOOL m_flipSurfaces;       ///< [AI] Enable/disable double-buffering flip surfaces (registry: "Flip Surfaces").
	BOOL m_backBuffersInVram;  ///< [AI] Backbuffers stored in VRAM if TRUE (reverse of registry: "Back Buffers in Video RAM").
	BOOL m_using8bit;          ///< [AI] Prefer 8-bit framebuffer. Set via registry: "Display Bit Depth".
	BOOL m_using16bit;         ///< [AI] Prefer 16-bit framebuffer. Set via registry: "Display Bit Depth".
	int m_unk0x24;             ///< [AI] Unknown video flag (propagated to video param; set by registry).
	BOOL m_use3dSound;         ///< [AI] 3D Sound enabled state.
	BOOL m_useMusic;           ///< [AI] Background music enabled state.
	BOOL m_useJoystick;        ///< [AI] Game is configured to use joystick/controller.
	int m_joystickIndex;       ///< [AI] Joystick hardware index (from registry; default 0).
	BOOL m_wideViewAngle;      ///< [AI] Enable "wide view" camera mode (registry: "Wide View Angle").
	int m_islandQuality;       ///< [AI] Environment geometry quality/complexity (registry: "Island Quality").
	int m_islandTexture;       ///< [AI] Environment texture mode (registry: "Island Texture").
	BOOL m_gameStarted;        ///< [AI] Is the main game sequence started/executing.
	MxLong m_frameDelta;       ///< [AI] Nominal time in ms between game logic frames/tick.
	MxVideoParam m_videoParam; ///< [AI] Structure containing video configuration/settings (flags, bit depth, fullscreen, etc).
	BOOL m_windowActive;       ///< [AI] Whether the main window is currently active/focused.
	HWND m_windowHandle;       ///< [AI] Win32 handle for the game window.
	BOOL m_drawCursor;         ///< [AI] TRUE if custom cursor drawing is enabled.
	HCURSOR m_cursorArrow;     ///< [AI] Handle to the standard arrow cursor.
	HCURSOR m_cursorBusy;      ///< [AI] Handle to the busy/wait cursor.
	HCURSOR m_cursorNo;        ///< [AI] Handle to the "not-allowed" cursor.
	HCURSOR m_cursorCurrent;   ///< [AI] Handle to the current cursor in use.
};

#endif // ISLEAPP_H
