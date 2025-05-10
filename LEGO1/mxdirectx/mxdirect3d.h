#ifndef MXDIRECT3D_H
#define MXDIRECT3D_H

#include "decomp.h"
#include "mxdirectdraw.h"
#include "mxdirectxinfo.h"
#include "mxstl/stlcompat.h"

#include <d3d.h>

// VTABLE: LEGO1 0x100db800
// VTABLE: BETA10 0x101c1af8
// SIZE 0x894

/**
 * @brief [AI] MxDirect3D provides Direct3D (D3D) rendering capabilities layered on top of MxDirectDraw, managing device selection, initialization, and drawing contexts for LEGO Island's 3D rendering.
 * 
 * This class manages Direct3D interfaces and connected devices, handles the creation and teardown of Direct3D objects and devices, ZBuffer creation/selection, as well as switching between fullscreen/windowed rendering modes and hardware/software rendering paths. It is also responsible for supporting palette and pixel format handling, and for tracking the availability and type of texture support at runtime.
 *
 * It is the base rendering system for 3D content in LEGO Island, providing all D3D context and resource management for the rest of the rendering pipeline.
 * 
 * @details [AI] MxDirect3D wraps DirectX 5's DirectDraw and Direct3D2 interfaces, and stores references to selected D3D devices. It handles choosing the best rendering device based on hardware/software support, managing the device list from enumeration, and setting video modes.  It allows toggling textures, manages creation/locking/zeroing of drawing surfaces, and creating the correct ZBuffer format. This class is intended to be used by higher-level abstractions to provide scene rendering services.
 */
class MxDirect3D : public MxDirectDraw {
public:
	/**
	 * @brief [AI] Constructs a new MxDirect3D object. Initializes member pointers to null and disables texture optimization by default.
	 */
	MxDirect3D();

	/**
	 * @brief [AI] Destroys the MxDirect3D object, releasing associated Direct3D interfaces and memory for assigned devices.
	 */
	~MxDirect3D() override;

	/**
	 * @brief [AI] Initializes DirectDraw and Direct3D, prepares primary surfaces and selects the video mode, optionally honoring palette/bit-depth and device selection.
	 * @param hWnd [AI] Window handle to attach DirectDraw/3D context to.
	 * @param fullscreen_1 [AI] Whether the video mode should be fullscreen.
	 * @param surface_fullscreen [AI] Whether drawing surfaces should be fullscreen.
	 * @param onlySystemMemory [AI] If TRUE, only use system memory and avoid video memory when creating surfaces.
	 * @param width [AI] Width of the desired video mode.
	 * @param height [AI] Height of the desired video mode.
	 * @param bpp [AI] Bits per pixel for the desired video mode.
	 * @param pPaletteEntries [AI] Optional palette entries for indexed color modes.
	 * @param paletteEntryCount [AI] Number of palette entries used. May be 0 if not palette-based.
	 * @return BOOL [AI] TRUE if creation and initialization succeed, FALSE if any part of DirectDraw or Direct3D setup fails.
	 */
	BOOL Create(
		HWND hWnd,
		BOOL fullscreen_1,
		BOOL surface_fullscreen,
		BOOL onlySystemMemory,
		int width,
		int height,
		int bpp,
		const PALETTEENTRY* pPaletteEntries,
		int paletteEntryCount
	) override;                              // vtable+0x04

	/**
	 * @brief [AI] Tears down the Direct3D environment, including releasing D3D and D3DDevice objects, and destroys allocated context state and surfaces.
	 */
	void Destroy() override;                 // vtable+0x08

	/**
	 * @brief [AI] Like Destroy(), but preserves the DirectDraw context; only Direct3D/3DDevice and D3D-specific objects are released.
	 */
	void DestroyButNotDirectDraw() override; // vtable+0x0c

	/**
	 * @brief [AI] Returns the currently selected/active rendering device information for 3D output.
	 * @return MxAssignedDevice* [AI] Current rendering device context, including flags, GUID, and caps.
	 */
	MxAssignedDevice* AssignedDevice() { return m_currentDeviceInfo; }

	/**
	 * @brief [AI] Provides access to the underlying IDirect3D2 interface for advanced 3D rendering operations.
	 * @return IDirect3D2* [AI] Pointer to the IDirect3D2 COM interface; may be NULL if not initialized.
	 */
	IDirect3D2* Direct3D() { return m_pDirect3d; }

	/**
	 * @brief [AI] Provides access to the currently selected Direct3D device interface.
	 * @return IDirect3DDevice2* [AI] Pointer to the IDirect3DDevice2 COM interface; may be NULL if not initialized.
	 */
	IDirect3DDevice2* Direct3DDevice() { return m_pDirect3dDevice; }

	/**
	 * @brief [AI] Selects which Direct3D device to be used for rendering, given an enumeration of available devices, a preferred driver, and device info.
	 * @param p_deviceEnumerate [AI] Enumerated device/driver/format list to select from.
	 * @param p_driver [AI] Specific driver to select.
	 * @param p_device [AI] Desired Direct3D device info.
	 * @return BOOL [AI] TRUE if device was set successfully, FALSE on failure or not found.
	 */
	BOOL SetDevice(MxDeviceEnumerate& p_deviceEnumerate, MxDriver* p_driver, Direct3DDeviceInfo* p_device);

protected:
	/**
	 * @brief [AI] Internal D3D initialization helper: acquires the IDirect3D2 interface from DirectDraw.
	 * @return BOOL [AI] TRUE if D3D is set up, FALSE on error.
	 */
	BOOL D3DCreate();

	/**
	 * @brief [AI] Internal method to initialize D3D video mode, create devices, ZBuffer, and clear surfaces as needed for selected hardware/software settings.
	 * @return BOOL [AI] TRUE if device/mode setup succeeds, FALSE on error.
	 */
	BOOL D3DSetMode();

	/**
	 * @brief [AI] Determines the suitable ZBuffer depth for a selected rendering device, according to its capabilities.
	 * @param p_assignedDevice [AI] The device for which to query the ZBuffer depth.
	 * @return int [AI] Depth in bits (e.g., 8/16/24/32), or -1 on failure.
	 */
	int ZBufferDepth(MxAssignedDevice* p_assignedDevice);

	// SYNTHETIC: LEGO1 0x1009b120
	// SYNTHETIC: BETA10 0x1011c0f0
	// MxDirect3D::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Currently selected rendering device for D3D output. Tracks the active hardware/software device and its properties.
	 */
	MxAssignedDevice* m_currentDeviceInfo; // 0x880

	/**
	 * @brief [AI] Pointer to the Direct3D2 COM interface. Used for managing 3D rendering contexts and device creation.
	 */
	IDirect3D2* m_pDirect3d;               // 0x884

	/**
	 * @brief [AI] Pointer to the active Direct3DDevice2 interface for issuing 3D rendering commands.
	 */
	IDirect3DDevice2* m_pDirect3dDevice;   // 0x888

	/**
	 * @brief [AI] TRUE to disable Direct3D textures entirely (uses flat colors); set automatically based on device & mode support for texturing.
	 */
	BOOL m_bTexturesDisabled;              // 0x88c

	/**
	 * @brief [AI] Purpose unknown. Likely an undocumented or unused member in the class layout. [AI_SUGGESTED_NAME: m_unusedOrUnknown0x890]
	 */
	undefined4 m_unk0x890;                 // 0x890
};

// GLOBAL: LEGO1 0x100dd1b0
// GLOBAL: BETA10 0x101c2de8
// IID_IDirect3D2

#endif // MXDIRECT3D_H
