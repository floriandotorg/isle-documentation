#ifndef MXDIRECTDRAW_H
#define MXDIRECTDRAW_H

#include "mxdirectxinfo.h"

#include <ddraw.h>
#include <windows.h>

// VTABLE: LEGO1 0x100db818
// VTABLE: BETA10 0x101c1b10
// SIZE 0x880

/**
 * @brief Class responsible for interfacing with DirectDraw to manage rendering surfaces, palettes, and fullscreen/windowed device modes. [AI]
 * @details [AI] Manages creation, destruction, and manipulation of primary/back buffers, palettes, display modes, clipper objects, z-buffers, and debug text surfaces for LEGO Island's rendering subsystem. Handles error notification and surface restoration. Allows for windowed and fullscreen operation and provides utility for palette management; also supports custom error handlers. [AI]
 */
class MxDirectDraw {
public:
	/**
	 * @brief Function pointer type for error handling callbacks. [AI]
	 * @param const char* Error message string. [AI]
	 * @param HRESULT Error code from DirectDraw. [AI]
	 * @param void* User-defined callback argument. [AI]
	 */
	typedef void (*ErrorHandler)(const char*, HRESULT, void*);

	/**
	 * @brief Returns the bit depth (color depth) of the primary display device. [AI]
	 * @details [AI] Queries the current display mode and determines if it's palette-indexed. May set a global indicating 8-bit palette mode is active. [AI]
	 */
	static int GetPrimaryBitDepth();

	/**
	 * @brief Constructs a MxDirectDraw instance and initializes its members. [AI]
	 */
	MxDirectDraw();

	/**
	 * @brief Virtual destructor. Destroys the DirectDraw instance and releases all resources. [AI]
	 */
	virtual ~MxDirectDraw();

	/**
	 * @brief Creates and initializes the DirectDraw device and associated surfaces/windows/state. [AI]
	 * @param hWnd The window handle to attach DirectDraw to. [AI]
	 * @param fullscreen_1 If TRUE, the device is set up for exclusive fullscreen; otherwise windowed. [AI]
	 * @param surface_fullscreen If TRUE, enables flipping surfaces (primary/back) for fullscreen rendering. [AI]
	 * @param onlySystemMemory If TRUE, surfaces are allocated in system RAM only (not video memory). [AI]
	 * @param width Desired screen width. [AI]
	 * @param height Desired screen height. [AI]
	 * @param bpp Desired bits per pixel (color depth). [AI]
	 * @param pPaletteEntries Palette data to use for palettized displays. [AI]
	 * @param paletteEntryCount Number of entries in pPaletteEntries. [AI]
	 * @return TRUE on success, FALSE if device or surfaces could not be created. [AI]
	 */
	virtual BOOL Create(
		HWND hWnd,
		BOOL fullscreen_1,
		BOOL surface_fullscreen,
		BOOL onlySystemMemory,
		int width,
		int height,
		int bpp,
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount
	);                                      // vtable+0x04

	/**
	 * @brief Shuts down DirectDraw and releases all resources, including device and surfaces. [AI]
	 */
	virtual void Destroy();                 // vtable+0x08

	/**
	 * @brief Releases all DirectDraw-related resources except the DirectDraw device itself. [AI]
	 */
	virtual void DestroyButNotDirectDraw(); // vtable+0x0c

	/**
	 * @brief Returns the DirectDraw device interface pointer. [AI]
	 * @return IDirectDraw* DirectDraw COM interface. [AI]
	 */
	IDirectDraw* DirectDraw() { return m_pDirectDraw; }

	/**
	 * @brief Returns the surface used as the primary/front buffer. [AI]
	 * @return IDirectDrawSurface* Pointer to the front buffer surface. [AI]
	 */
	IDirectDrawSurface* FrontBuffer() { return m_pFrontBuffer; }

	/**
	 * @brief Returns the back buffer surface. [AI]
	 * @return IDirectDrawSurface* Pointer to the back buffer surface. [AI]
	 */
	IDirectDrawSurface* BackBuffer() { return m_pBackBuffer; }

	/**
	 * @brief Returns the current DirectDraw clipper object used for window clipping. [AI]
	 * @return IDirectDrawClipper* Pointer to the clipper. [AI]
	 */
	IDirectDrawClipper* Clipper() { return m_pClipper; }

	/**
	 * @brief Provides access to the current selected display mode (width, height, bpp). [AI]
	 * @return DeviceModesInfo::Mode* Pointer to the mode structure. [AI]
	 */
	DeviceModesInfo::Mode* CurrentMode() { return &m_currentMode; }

	/**
	 * @brief Returns TRUE if DirectDraw is currently set in exclusive fullscreen mode. [AI]
	 */
	BOOL IsFullScreen() { return m_bFullScreen; }

	/**
	 * @brief Checks if the given mode (resolution, bpp) is supported by the current device. [AI]
	 * @param width Width in pixels. [AI]
	 * @param height Height in pixels. [AI]
	 * @param bpp Bits per pixel. [AI]
	 * @return TRUE if the mode is available, FALSE otherwise. [AI]
	 */
	BOOL IsSupportedMode(int width, int height, int bpp);

	/**
	 * @brief Pauses or resumes DirectDraw rendering. Used to handle palette/surface swapping on alt-tab, restoring. [AI]
	 * @param Flag indicating whether to pause (TRUE) or resume (FALSE). [AI]
	 * @return TRUE on success, FALSE on failure. [AI]
	 */
	int Pause(BOOL);

	/**
	 * @brief Attempts to restore all DirectDraw surfaces that may have been lost. [AI]
	 * @details [AI] Surfaces can become lost when switching to/from exclusive fullscreen or losing the device context. [AI]
	 * @return TRUE on success, FALSE on surface restoration failure. [AI]
	 */
	BOOL RestoreSurfaces();

	/**
	 * @brief Draws the specified text string to the debug "text1" surface. [AI]
	 * @param text Null-terminated string to draw. [AI]
	 * @return TRUE on success. [AI]
	 */
	BOOL TextToTextSurface1(const char* text);

	/**
	 * @brief Draws the specified string to the debug "text2" surface. [AI]
	 * @param lpString Null-terminated string to draw. [AI]
	 * @return TRUE on success. [AI]
	 */
	BOOL TextToTextSurface2(const char* lpString);

	/**
	 * @brief Converts DirectDraw error code to a human-readable string. [AI]
	 * @param p_error HRESULT error code from a DirectDraw operation. [AI]
	 * @return Pointer to error message string. [AI]
	 */
	virtual const char* ErrorToString(HRESULT p_error); // vtable+0x10

	/**
	 * @brief Flips to the Windows GDI surface, restoring the desktop when leaving exclusive fullscreen. [AI]
	 * @return TRUE on success, FALSE on error. [AI]
	 */
	int FlipToGDISurface();

protected:
	/**
	 * @brief Sets the DirectDraw palette using the provided palette entries. Used for palettized display modes. [AI]
	 * @param pPaletteEntries Pointer to palette entries. [AI]
	 * @param paletteEntryCount Number of palette entries. [AI]
	 * @param fullscreen Whether called in fullscreen context (may affect updates to system palette). [AI]
	 * @return TRUE on palette update success, otherwise FALSE. [AI]
	 */
	BOOL SetPaletteEntries(const PALETTEENTRY* pPaletteEntries, int paletteEntryCount, BOOL fullscreen);

	/**
	 * @brief Caches the original Windows/system palette for restoration. [AI]
	 * @return TRUE if palette was cached or not applicable. [AI]
	 */
	BOOL CacheOriginalPaletteEntries();

	/**
	 * @brief Restores the original Windows palette from backup. [AI]
	 * @return TRUE if palette was restored. [AI]
	 */
	BOOL RestoreOriginalPaletteEntries();

	/**
	 * @brief Restores the active DirectDraw palette entries from the internal palette array. [AI]
	 * @return TRUE if palette was set. [AI]
	 */
	BOOL RestorePaletteEntries();

	/**
	 * @brief Initializes DirectDraw cooperative level for fullscreen or windowed mode. [AI]
	 * @param fullscreen Whether to use exclusive fullscreen or not. [AI]
	 * @return TRUE if initialization succeeded, otherwise FALSE. [AI]
	 */
	BOOL DDInit(BOOL fullscreen);

	/**
	 * @brief Changes DirectDraw to the specified display mode and creates relevant surfaces. [AI]
	 * @details [AI] Handles resizing and switching window styles for windowed mode; validates that the requested mode exists. [AI]
	 * @param width Requested width. [AI]
	 * @param height Requested height. [AI]
	 * @param bpp Requested bits per pixel. [AI]
	 * @return TRUE if the mode was set and surfaces created, FALSE on failure. [AI]
	 */
	BOOL DDSetMode(int width, int height, int bpp);

	/**
	 * @brief Internal: Creates all necessary front/back/offscreen surfaces for rendering. [AI]
	 * @return TRUE if surfaces were created successfully. [AI]
	 */
	BOOL DDCreateSurfaces();

	/**
	 * @brief Creates a DirectDraw surface with the given surface description. [AI]
	 * @param a2 The DDSURFACEDESC that specifies the new surface parameters. [AI]
	 * @param a3 Receives the created surface pointer. [AI]
	 * @param a4 Optional: outer COM object for aggregation, usually NULL. [AI]
	 * @return HRESULT from DirectDraw CreateSurface call. [AI]
	 */
	HRESULT CreateDDSurface(LPDDSURFACEDESC a2, LPDIRECTDRAWSURFACE* a3, IUnknown* a4);

	/**
	 * @brief Retrieves the surface description for the given DirectDraw surface. [AI]
	 * @param lpDDSurfDesc Pointer to DDSURFACEDESC to receive surface info. [AI]
	 * @param lpDDSurf The surface to be queried. [AI]
	 * @return TRUE if description was retrieved. [AI]
	 */
	BOOL GetDDSurfaceDesc(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE lpDDSurf);

	/**
	 * @brief Creates a z-buffer with the given memory type/capabilities and attaches it to the back buffer. [AI]
	 * @param memorytype Device memory type (e.g., system or video memory). [AI]
	 * @param depth Number of bits for the z-buffer. [AI]
	 * @return TRUE if the z-buffer was created and attached successfully. [AI]
	 */
	BOOL CreateZBuffer(DWORD memorytype, DWORD depth);

	/**
	 * @brief Creates the two offscreen text surfaces used for debug overlay. [AI]
	 * @return TRUE if surfaces and font created successfully. [AI]
	 */
	BOOL CreateTextSurfaces();

	/**
	 * @brief Renders a string to the given surface and fills in its onscreen size. [AI]
	 * @param text Null-terminated string to draw. [AI]
	 * @param pSurface Target DirectDraw surface. [AI]
	 * @param textSizeOnSurface Receives the size of the rendered text. [AI]
	 * @return TRUE on success, FALSE on failure. [AI]
	 */
	BOOL TextToTextSurface(const char* text, IDirectDrawSurface* pSurface, SIZE& textSizeOnSurface);

	/**
	 * @brief Invokes the error handler, optionally destroying the device, and outputs the given error message/code. [AI]
	 * @param p_message Description or context message. [AI]
	 * @param p_error DirectDraw HRESULT error or custom error code. [AI]
	 */
	void Error(const char* p_message, int p_error);

	/**
	 * @brief Recreates the DirectDraw device, deleting and restoring the device object pointer. [AI]
	 * @details [AI] Used during device mode switches or DX context loss; can be passed a GUID for the device. [AI]
	 * @param a2 Pointer to GUID pointer, usually obtained from DeviceModesInfo. [AI]
	 * @return TRUE if device was created successfully. [AI]
	 */
	BOOL RecreateDirectDraw(GUID** a2);

	/**
	 * @brief Internal: Clears the backbuffer(s), locking and filling with zero color, possibly flipping to front. [AI]
	 * @details [AI] Called after (re)creating surfaces or setting new modes; ensures surface memory is initialized. [AI]
	 */
	void FUN_1009e020();

	/**
	 * @brief Internal: Restores original palette and resets display mode and cooperative level. [AI]
	 * @details [AI] Used for gracefully transitioning out of exclusive fullscreen or when deinitializing. [AI]
	 */
	void FUN_1009d920();

	// SYNTHETIC: LEGO1 0x1009d510
	// SYNTHETIC: BETA10 0x10122f80
	// MxDirectDraw::`scalar deleting destructor'

protected:
	BOOL m_bOnlySoftRender;                     ///< If TRUE, restricts rendering to software only; disables hardware acceleration. [AI]
	BOOL m_bFlipSurfaces;                       ///< TRUE if using DirectDraw flipping (fullscreen buffer swap); windowed disables this. [AI]
	IDirectDraw* m_pDirectDraw;                 ///< Pointer to the DirectDraw COM device. [AI]
	IDirectDrawSurface* m_pFrontBuffer;         ///< Primary or front display surface. [AI]
	IDirectDrawSurface* m_pBackBuffer;          ///< Backbuffer for offscreen rendering/flipping. [AI]
	IDirectDrawSurface* m_pZBuffer;             ///< Attached Z-buffer for 3D rendering. [AI]
	IDirectDrawSurface* m_pText1Surface;        ///< Debug overlay surface for "text1". [AI]
	IDirectDrawSurface* m_pText2Surface;        ///< Debug overlay surface for "text2". [AI]
	IDirectDrawClipper* m_pClipper;             ///< Clipper for managing windowed surface boundaries. [AI]
	IDirectDrawPalette* m_pPalette;             ///< DirectDraw palette assigned to the primary/back surfaces. [AI]
	PALETTEENTRY m_paletteEntries[256];         ///< Active 8-bit palette entries for palettized modes. [AI]
	PALETTEENTRY m_originalPaletteEntries[256]; ///< Backup of system/Windows palette for restoration. [AI]
	SIZE m_text1SizeOnSurface;                  ///< Pixel size of rendered text1 overlay surface. [AI]
	SIZE m_text2SizeOnSurface;                  ///< Pixel size of rendered text2 overlay surface. [AI]
	HWND m_hWndMain;                            ///< Main window handle on which DirectDraw is initialized. [AI]
	HFONT m_hFont;                              ///< Font handle for debug text overlays. [AI]
	BOOL m_bIgnoreWMSIZE;                       ///< Internal flag to suppress window resize messages during device switching. [AI]
	BOOL m_bPrimaryPalettized;                  ///< TRUE if primary/backbuffer is using 8-bit palettized mode. [AI]
	BOOL m_bFullScreen;                         ///< TRUE if device is in exclusive fullscreen mode. [AI]
	void* m_unk0x850;                           ///< [AI] Purpose unknown; possibly driver-specific data or reserved.
	BOOL m_bOnlySystemMemory;                   ///< TRUE for system RAM-only surfaces; disables video memory allocation. [AI]
	BOOL m_bIsOnPrimaryDevice;                  ///< TRUE if rendering on Windows' main display; disables windowed mode for other devices. [AI]
	ErrorHandler m_pErrorHandler;               ///< Callback for non-fatal DirectDraw errors. [AI]
	ErrorHandler m_pFatalErrorHandler;          ///< Callback invoked for fatal device errors. [AI]
	void* m_pErrorHandlerArg;                   ///< Custom argument pointer for error handler. [AI]
	void* m_pFatalErrorHandlerArg;              ///< Custom argument pointer for fatal error handler. [AI]
	int m_pauseCount;                           ///< Count of nested pauses; ensures multiple Pause(TRUE)/Pause(FALSE) work correctly. [AI]
	DeviceModesInfo* m_currentDevInfo;          ///< Device info array for storing supported display modes. [AI]
	DeviceModesInfo::Mode m_currentMode;        ///< Struct with current width, height, and bits per pixel. [AI]
};

#endif // MXDIRECTDRAW_H