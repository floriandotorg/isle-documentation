#ifndef _TglSurface_h
#define _TglSurface_h

#include "mxdirectx/mxstopwatch.h"
#include "tgl/tgl.h"

/**
 * @namespace Tgl
 * @brief [AI] Namespace containing all classes related to the 3D graphics abstraction/rendering engine.
 * @details [AI] Used as an abstraction layer over Direct3D (Retained Mode) and device representations in the LEGO Island engine. [AI]
 */
namespace Tgl
{
class Renderer; ///< [AI] Abstract renderer for 3D rendering tasks.
class Device;   ///< [AI] Abstract representation of a Direct3D-capable device.
class View;     ///< [AI] Represents a viewport or camera in the 3D engine.
class Group;    ///< [AI] Represents a group or scene node for 3D objects.
} // namespace Tgl

/////////////////////////////////////////////////////////////////////////////
// TglSurface

/**
 * @class TglSurface
 * @brief [AI] Encapsulates a rendering surface, its associated hardware device, renderer, and view.
 * @details [AI] TglSurface is the main representation of a 3D rendering target, managing the renderer,
 *   device, viewport, and main scene group. It handles initialization, device creation, rendering timing/statistics, 
 *   and render loop operations for LEGO Island's DirectX-based renderer. [AI]
 *
 * Advanced users may subclass this to customize viewport creation or device handling. [AI]
 */
class TglSurface {
public:
	/**
	 * @struct CreateStruct
	 * @brief [AI] Contains initialization parameters for creating a TglSurface and its underlying DDraw/D3D resources.
	 * @details [AI] Used to pass all necessary Windows handles, DirectDraw, Direct3D, and palette surfaces for full or windowed rendering.
	 *   The parameters support both hardware and emulated pixel processing depending on the provided interfaces. [AI]
	 */
	struct CreateStruct {
		const GUID* m_pDriverGUID;          ///< [AI] DirectDraw driver GUID to use or NULL for primary display.
		HWND m_hWnd;                        ///< [AI] Handle to the window to be associated with this surface.
		IDirectDraw* m_pDirectDraw;         ///< [AI] DirectDraw interface pointer for low-level surface management.
		IDirectDrawSurface* m_pFrontBuffer; ///< [AI] DirectDraw primary/front buffer surface.
		IDirectDrawSurface* m_pBackBuffer;  ///< [AI] Optional DirectDraw back buffer for double buffering.
		IDirectDrawPalette* m_pPalette;     ///< [AI] Optional palette for indexed color surfaces.
		BOOL m_isFullScreen;                ///< [AI] TRUE to use fullscreen mode, FALSE for windowed rendering.
		BOOL m_isWideViewAngle;             ///< [AI] Enables wide or default field-of-view projection.
		IDirect3D2* m_direct3d;             ///< [AI] Direct3D2 interface pointer for 3D initialization.
		IDirect3DDevice2* m_d3dDevice;      ///< [AI] Direct3D2 device interface (hardware or emulated).
	};

public:
	/**
	 * @brief [AI] Constructs a new TglSurface instance with members initialized to their default state.
	 */
	TglSurface();

	/**
	 * @brief [AI] Virtual destructor also triggers Destroy(). Frees device, view, and related resources.
	 */
	virtual ~TglSurface();

	/**
	 * @brief [AI] Creates and initializes the surface, rendering device, and optionally installs scene graph.
	 * @details [AI] This function selects the appropriate color, shading and texturing models for
	 *   the provided DDraw surfaces, configures texture and color settings based on device format,
	 *   and initializes the view/camera and rendering statistics.
	 *   Subclassed implementations will usually handle advanced device and scene graph setup.
	 * @param rCreateStruct [AI] Initialization parameters (window, buffers, palette etc.).
	 * @param pRenderer [AI] Renderer used to create and manage 3D device and scene.
	 * @param pScene [AI] Top-level Tgl::Group representing the 3D scene graph root.
	 * @retval TRUE [AI] On successful device/view/scene setup.
	 * @retval FALSE [AI] If device/view failed to create/setup.
	 */
	virtual BOOL Create(const CreateStruct&, Tgl::Renderer*, Tgl::Group* pScene); // vtable+0x04

	/**
	 * @brief [AI] Destroys all resources (view, device), releasing scene and renderer references.
	 * @details [AI] Safe to call multiple times, always results in idle/inert surface.
	 */
	virtual void Destroy(); // vtable+0x08

	/**
	 * @brief [AI] Renders a single frame and returns the render time for that frame.
	 * @details [AI] Uses and updates the statistics meters for framerate and rendering time monitoring.
	 *   Handles view-calling and statistics upkeep.
	 * @return [AI] Elapsed render time in seconds for the completed frame.
	 */
	virtual double Render(); // vtable+0x0c

	/**
	 * @brief [AI] Gets the active renderer for this surface.
	 * @return [AI] Renderer instance, or nullptr if not created.
	 */
	Tgl::Renderer* GetRenderer() const { return m_pRenderer; }

	/**
	 * @brief [AI] Returns the graphics device used by this surface, e.g. hardware or software abstraction.
	 * @return [AI] Device instance, or nullptr if not ready.
	 */
	Tgl::Device* GetDevice() const { return m_pDevice; }

	/**
	 * @brief [AI] Gets the current view/camera for this surface.
	 * @return [AI] View/camera pointer.
	 */
	Tgl::View* GetView() const { return m_pView; }

	/**
	 * @brief [AI] Returns the currently attached 3D scene root/group.
	 * @return [AI] Scene group pointer, or nullptr if not attached.
	 */
	Tgl::Group* GetScene() const { return m_pScene; }

	/**
	 * @brief [AI] Returns the width (in pixels) of the rendered surface.
	 * @return [AI] The current device width.
	 */
	unsigned long GetWidth() const { return m_width; }

	/**
	 * @brief [AI] Returns the height (in pixels) of the rendered surface.
	 * @return [AI] The current device height.
	 */
	unsigned long GetHeight() const { return m_height; }

	/**
	 * @brief [AI] Returns the measured rendering rate (frames per second) for the rendering routine.
	 * @details [AI] Uses the rendering rate frequency meter to report recent rendering rate. [AI]
	 */
	double GetRenderingRate() const { return m_renderingRateMeter.Frequency(); }

	/**
	 * @brief [AI] Returns the measured frame rate (frames per second) for the current surface.
	 * @details [AI] Uses the frame rate frequency meter to report the last few frames' average rate. [AI]
	 */
	double GetFrameRate() const { return m_frameRateMeter.Frequency(); }

	/**
	 * @brief [AI] Returns the frame count since creation or since last meter reset.
	 * @details [AI] Used for diagnostics, animation timing, or display statistics.
	 */
	unsigned long GetFrameCount() const { return m_frameCount; }

#ifdef _DEBUG
	/**
	 * @brief [AI] Returns the measured triangles-per-second rendering rate, in debug builds.
	 * @details [AI] Value may be zero in release builds or when triangle count is not tracked.
	 */
	double GetTriangleRate() const { return m_triangleRateMeter.Frequency(); }
#endif

protected:
	/**
	 * @brief [AI] Abstract view creation. Subclasses must override to provide appropriate view/camera for the surface.
	 * @param pRenderer [AI] The renderer with which to associate the new view.
	 * @param pDevice [AI] The device on which this view will be rendered.
	 * @return [AI] Pointer to the created Tgl::View, or nullptr on failure.
	 */
	virtual Tgl::View* CreateView(Tgl::Renderer*, Tgl::Device*) = 0; // vtable+0x10

	/**
	 * @brief [AI] Destroys (deletes) the surface's view/camera, and resets the pointer to null.
	 * @details [AI] Provided for use in cleanup and destruction workflows. Safe to call if view is null. [AI]
	 */
	virtual void DestroyView(); // vtable+0x14

private:
	Tgl::Renderer* m_pRenderer; ///< [AI] Attached renderer used for device and scene management. [AI]
	Tgl::Device* m_pDevice;     ///< [AI] Graphics device for rendering to this surface (hardware or software). [AI]
	Tgl::View* m_pView;         ///< [AI] View (camera/viewport) into the 3D scene; owned by surface. [AI]
	Tgl::Group* m_pScene;       ///< [AI] Root of the 3D scene graph to be rendered. [AI]

	unsigned long m_width;   ///< [AI] Width of the rendering area in pixels, as reported by the device. [AI]
	unsigned long m_height;  ///< [AI] Height of the rendering area in pixels, as reported by the device. [AI]

	BOOL m_isInitialized; ///< [AI] TRUE if the surface was successfully initialized and ready for rendering. [AI]
	BOOL m_stopRendering; ///< [AI] TRUE if rendering should be paused/skipped. [AI]

	// statistics
	MxFrequencyMeter m_renderingRateMeter; ///< [AI] Frequency meter for measuring rendering throughput. [AI]
	MxFrequencyMeter m_frameRateMeter;     ///< [AI] Frequency meter for measuring scene frame rate. [AI]
	unsigned long m_frameCount;            ///< [AI] Number of frames rendered since the last reset or creation. [AI]
#ifdef _DEBUG
	MxFrequencyMeter m_triangleRateMeter; ///< [AI] [DEBUG] Tracks triangle-per-second statistics. [AI]
	unsigned long m_triangleCount;        ///< [AI] [DEBUG] Storing triangle count for statistics since last update. [AI]
#endif
};

/////////////////////////////////////////////////////////////////////////////

/**
 * @brief [AI] Scalar deleting destructor for TglSurface. Called internally for object destruction.
 * @details [AI] Ensures that TglSurface resources are deleted properly if there are compiler-generated or dynamic allocations. [AI]
 */
// SYNTHETIC: LEGO1 0x100abcf0
// SYNTHETIC: BETA10 0x1017de00
// TglSurface::`scalar deleting destructor'

#endif /* _TglSurface_h */
