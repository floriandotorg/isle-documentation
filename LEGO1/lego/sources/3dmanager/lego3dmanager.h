#ifndef _Lego3DManager_h
#define _Lego3DManager_h

#include "assert.h"
#include "lego3dview.h"

namespace Tgl
{
class Renderer;
class Group;
} // namespace Tgl

class ViewROI;

// ??? for now
class ViewLODListManager;

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DManager

// VTABLE: LEGO1 0x100dbfa4
// SIZE 0x10
/**
 * @brief [AI] Central class managing the LEGO Island 3D rendering subsystem.
 * 
 * This manager is responsible for orchestrating rendering, scene composition, 
 * and related view and display options. 
 * 
 * Internally, it aggregates the core rendering objects, scene views, and a manager 
 * for level-of-detail (LOD) lists. It provides interfaces to add/remove objects 
 * from the 3D scene, set the camera point of view, manipulate frustum parameters, 
 * and trigger rendering.
 * 
 * Ownership of created objects (Renderer, Lego3DView, ViewLODListManager) is managed here.
 * 
 * @details [AI] This class encapsulates the main 3D responsibilities for the LEGO Island game, delegating view-based logic to Lego3DView and rendering commands to Tgl::Renderer.
 */
class Lego3DManager {
public:
	/**
	 * @brief [AI] Construction parameters for initializing the 3D system.
	 * @details [AI] This struct bundles all relevant handles, devices, and display properties required to set up DirectDraw/Direct3D rendering context and windowing.
	 */
	struct CreateStruct {
		const GUID* m_pDriverGUID;          ///< [AI] Pointer to DirectDraw driver GUID to use (NULL for default)
		HWND m_hWnd;                        ///< [AI] Window handle to associate DirectDraw surfaces with
		IDirectDraw* m_pDirectDraw;         ///< [AI] Pointer to active DirectDraw interface
		IDirectDrawSurface* m_pFrontBuffer; ///< [AI] DirectDraw front buffer surface
		IDirectDrawSurface* m_pBackBuffer;  ///< [AI] DirectDraw back buffer surface
		IDirectDrawPalette* m_pPalette;     ///< [AI] Color palette for indexed display modes
		BOOL m_isFullScreen;                ///< [AI] TRUE if 3D system should run in full-screen mode
		BOOL m_isWideViewAngle;             ///< [AI] TRUE for wide-angle (FOV) projection
		IDirect3D2* m_direct3d;             ///< [AI] Direct3D interface
		IDirect3DDevice2* m_d3dDevice;      ///< [AI] Direct3D device to use for rendering
	};

public:
	/**
	 * @brief [AI] Constructs and initializes the Lego3DManager in an uninitialized state.
	 */
	Lego3DManager();

	/**
	 * @brief [AI] Destructor. Calls Destroy() to clean up owned resources.
	 */
	virtual ~Lego3DManager();

	/**
	 * @brief [AI] Initializes the LEGO 3D system using the specified creation parameters.
	 * 
	 * This sets up the Tgl::Renderer, Lego3DView, and ViewLODListManager. Must be called once before use.
	 *
	 * @param rCreateStruct [AI] Details the rendering window, buffers, and device settings.
	 * @return TRUE on success, FALSE otherwise [AI]
	 */
	BOOL Create(CreateStruct& rCreateStruct);

	/**
	 * @brief [AI] Cleans up the 3D system and destroys internal objects.
	 * 
	 * Frees the Renderer, View, and LOD Manager.
	 */
	void Destroy();

	/**
	 * @brief [AI] Adds a ViewROI (rendered object) to the scene.
	 * 
	 * Delegates to Lego3DView. The ROI will be taken into account for rendering.
	 * 
	 * @param rROI [AI] Reference to the ROI to add.
	 * @return TRUE if added successfully, FALSE otherwise [AI]
	 */
	BOOL Add(ViewROI& rROI);

	/**
	 * @brief [AI] Removes a ViewROI from the scene.
	 * 
	 * Delegates to Lego3DView.
	 * 
	 * @param rROI [AI] The ROI to remove.
	 * @return TRUE if removed, FALSE if not present [AI]
	 */
	BOOL Remove(ViewROI& rROI);

	/**
	 * @brief [AI] Notifies the manager that the ROI has moved and needs spatial update.
	 * 
	 * Calls corresponding update on Lego3DView.
	 * 
	 * @param rROI [AI] The ROI that has moved.
	 * @return TRUE if update required, FALSE otherwise [AI]
	 */
	BOOL Moved(ViewROI& rROI);

	/**
	 * @brief [AI] Sets the camera's point of view to match the given ROI.
	 * 
	 * Delegates to Lego3DView, which applies the transformation.
	 * 
	 * @param rROI [AI] The ROI serving as the new point of view.
	 * @return TRUE if successful [AI]
	 */
	BOOL SetPointOfView(ViewROI& rROI);

	/**
	 * @brief [AI] Renders the current frame.
	 * 
	 * Triggers drawing of the 3D scene. Accepts a parameter (purpose unclear, possibly frame time or LOD factor).
	 * 
	 * @param p_und [AI] Unclear usage (likely time delta or update tick).
	 * @return Rendering time, frame statistics, or implementation-defined double value. [AI]
	 */
	double Render(double p_und);

	/**
	 * @brief [AI] Sets the 3D perspective frustum parameters for camera and view.
	 * 
	 * Updates field-of-view, near, and far plane distances used for rendering.
	 * 
	 * @param p_fov [AI] Field of view in degrees
	 * @param p_front [AI] Near clipping plane
	 * @param p_back [AI] Far clipping plane
	 * @return Always 0 (no error handling) [AI] 
	 */
	int SetFrustrum(float p_fov, float p_front, float p_back);

	/**
	 * @brief [AI] Provides access to the underlying Tgl::Renderer instance.
	 * 
	 * Use to submit lower-level rendering commands or queries.
	 * 
	 * @return Renderer instance pointer [AI]
	 */
	Tgl::Renderer* GetRenderer();

	/**
	 * @brief [AI] Returns the root Tgl::Group for the 3D scene.
	 * 
	 * This is the object tree containing all rendered geometry.
	 * 
	 * @return Root scene group [AI]
	 */
	Tgl::Group* GetScene();

	/**
	 * @brief [AI] Returns the encapsulated Lego3DView instance.
	 * 
	 * View handles detailed scene/camera logic and should be used for advanced manipulation.
	 * 
	 * @return Pointer to Lego3DView [AI]
	 */
	Lego3DView* GetLego3DView();

	/**
	 * @brief [AI] Returns the internal ViewLODListManager instance.
	 * 
	 * Used for managing all LOD object lists within the 3D subsystem.
	 * 
	 * @return ViewLODListManager pointer [AI]
	 */
	ViewLODListManager* GetViewLODListManager();

	// SYNTHETIC: LEGO1 0x100ab340
	// Lego3DManager::`scalar deleting destructor'

private:
	Tgl::Renderer* m_pRenderer; ///< [AI] The main Direct3D/DirectDraw compatible renderer. [Owned]
	Lego3DView* m_pLego3DView;                 ///< [AI] Encapsulates scene, camera, and node management. [Owned]
	ViewLODListManager* m_pViewLODListManager; ///< [AI] Responsible for tracking LOD-variant geometry in the scene. [Owned]
};

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DManager implementaion

// FUNCTION: BETA10 0x10079bd0
inline BOOL Lego3DManager::Add(ViewROI& rROI)
{
	assert(m_pLego3DView);

	return m_pLego3DView->Add(rROI);
}

// FUNCTION: BETA10 0x10037430
inline BOOL Lego3DManager::Remove(ViewROI& rROI)
{
	assert(m_pLego3DView);

	return m_pLego3DView->Remove(rROI);
}

// FUNCTION: BETA10 0x100d8990
inline BOOL Lego3DManager::SetPointOfView(ViewROI& rROI)
{
	assert(m_pLego3DView);

	return m_pLego3DView->SetPointOfView(rROI);
}

// FUNCTION: BETA10 0x1004af70
inline BOOL Lego3DManager::Moved(ViewROI& rROI)
{
	assert(m_pLego3DView);

	return m_pLego3DView->Moved(rROI);
}

inline Tgl::Renderer* Lego3DManager::GetRenderer()
{
	return m_pRenderer;
}

inline Tgl::Group* Lego3DManager::GetScene()
{
	assert(m_pLego3DView);

	return m_pLego3DView->GetScene();
}

// FUNCTION: BETA10 0x10011840
inline Lego3DView* Lego3DManager::GetLego3DView()
{
	return m_pLego3DView;
}

inline ViewLODListManager* Lego3DManager::GetViewLODListManager()
{
	return m_pViewLODListManager;
}

#endif /* _Lego3DManager_h */