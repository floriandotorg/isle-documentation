#ifndef _LegoView1_h
#define _LegoView1_h

#include "compat.h"
#include "decomp.h"
#include "tglsurface.h"

namespace Tgl
{
class Camera;
class Light;
} // namespace Tgl

/////////////////////////////////////////////////////////////////////////////
// LegoView

/**
 * @brief [AI] Represents a 3D rendering surface holding the main scene group and camera for rendering.
 * @details [AI] LegoView encapsulates a TglSurface, containing a Tgl::Group root scene node and an associated Tgl::Camera to define the scene's viewpoint and projection. It provides lifecycle and resource management (create/destroy), and gives access to the scene and camera for further manipulation or extension. [AI]
 */
// VTABLE: LEGO1 0x100dc000
// VTABLE: BETA10 0x101c3578
// SIZE 0x78
class LegoView : public TglSurface {
public:
	/**
	 * @brief [AI] Constructs an empty LegoView with uninitialized scene and camera.
	 */
	LegoView();

	/**
	 * @brief [AI] Destructor. Ensures scene and camera are destroyed and released.
	 */
	~LegoView() override;

	/**
	 * @brief [AI] Initialize the LegoView with a scene root and camera using the provided creation parameters and renderer.
	 * @param rCreateStruct  [AI] Structure describing the view's creation parameters (e.g., resolution, view angle). [AI]
	 * @param pRenderer  [AI] Renderer used to create scene and camera objects and underlying TglSurface resources. [AI]
	 * @return TRUE if creation succeeded, FALSE on error (resource allocation failed or bad input). [AI]
	 */
	BOOL Create(const CreateStruct& rCreateStruct, Tgl::Renderer* pRenderer);

	/**
	 * @brief [AI] Release all scene and camera resources, call TglSurface cleanup.
	 * @details [AI] This overrides TglSurface::Destroy to ensure scene root and camera are deleted and set to null before calling the parent's cleanup. [AI]
	 */
	void Destroy() override; // vtable+0x08

	/**
	 * @brief [AI] Accessor for the root scene group.
	 * @return Pointer to the root scene group node of the rendered world. [AI]
	 */
	Tgl::Group* GetScene() const;

	/**
	 * @brief [AI] Accessor for the view's main camera.
	 * @return Pointer to the camera object used for viewing the scene. [AI]
	 */
	Tgl::Camera* GetCamera() const;

protected:
	/**
	 * @brief [AI] Create and return the Tgl::View object for this surface.
	 * @param pRenderer The rendering system used to instantiate the view. [AI]
	 * @param pDevice The actual output device (window, surface, etc) for rendering. [AI]
	 * @return Initialized Tgl::View with camera set, sized to match the surface. [AI]
	 */
	Tgl::View* CreateView(Tgl::Renderer* pRenderer, Tgl::Device* pDevice) override; // vtable+0x10

private:
	Tgl::Group* m_pScene;   ///< @brief [AI] Root group node of the 3D scene graph rendered in this view. [AI]
	Tgl::Camera* m_pCamera; ///< @brief [AI] Main camera object through which the scene is observed. [AI]
};

/////////////////////////////////////////////////////////////////////////////
// LegoView implementation

inline Tgl::Group* LegoView::GetScene() const
{
	return m_pScene;
}

inline Tgl::Camera* LegoView::GetCamera() const
{
	return m_pCamera;
}

// SYNTHETIC: LEGO1 0x100ab580
// SYNTHETIC: BETA10 0x1017cb80
// LegoView::`scalar deleting destructor'

/////////////////////////////////////////////////////////////////////////////
// LegoView1

/**
 * @brief [AI] 3D view that supports advanced lighting for scene rendering.
 * @details [AI] LegoView1 extends the basic scene/camera view of LegoView by managing three separate lights (sun, directional, ambient)
 *              to control scene illumination. Includes methods for attaching and configuring these lights, such as transformation matrices and colors.
 *              Used for levels or scenes requiring realistic and flexible 3D lighting models. [AI]
 */
// VTABLE: LEGO1 0x100dc018
// VTABLE: BETA10 0x101c3590
// SIZE 0x88
class LegoView1 : public LegoView {
public:
	/**
	 * @brief [AI] Constructs the view and zeros out all light pointers (sun, directional, ambient). [AI]
	 */
	LegoView1();

	/**
	 * @brief [AI] Destructor. Calls Destroy to remove lights and free their memory. [AI]
	 */
	~LegoView1() override;

	/**
	 * @brief [AI] Adds the view's lights (sun, directional, ambient) to the active Tgl view for rendering.
	 * @details [AI] All three lights are registered with the scene's Tgl::View. Assumes lights exist and view is ready. [AI]
	 * @return TRUE on success (always, unless view/lights are missing), FALSE otherwise. [AI]
	 */
	BOOL AddLightsToViewport();

	/**
	 * @brief [AI] Initializes scene, camera, and three types of lights (sun, directional, ambient) using supplied renderer.
	 * @param rCreateStruct  [AI] Structure with view/camera/scene setup parameters. [AI]
	 * @param pRenderer  [AI] Renderer used to create scene, camera, and all three lights. [AI]
	 * @return TRUE if creation (including all lights) succeeded, FALSE if failed at any stage. [AI]
	 */
	BOOL Create(const TglSurface::CreateStruct& rCreateStruct, Tgl::Renderer* pRenderer);

	/**
	 * @brief [AI] Safely removes all lights from the scene, deletes them, and nulls pointers. [AI]
	 * @details [AI] Called by destructor; also chains to LegoView::Destroy for full view resource cleanup. [AI]
	 */
	void Destroy() override; // vtable+0x08

	/**
	 * @brief [AI] Sets the transformation matrix (position/orientation) for either the sun or directional light.
	 * @param bDirectionalLight [AI] If TRUE, sets directional light; if FALSE, sets sun (point) light. [AI]
	 * @param rMatrix [AI] 4x4 transformation matrix defining new position/direction for the selected light. [AI]
	 */
	void SetLightTransform(BOOL bDirectionalLight, Tgl::FloatMatrix4& rMatrix);

	/**
	 * @brief [AI] Sets the RGB color for either the sun or directional light.
	 * @param bDirectionalLight [AI] If TRUE, updates directional light; if FALSE, updates sun (point) light. [AI]
	 * @param red [AI] Red color component in range [0,1]. [AI]
	 * @param green [AI] Green color component in range [0,1]. [AI]
	 * @param blue [AI] Blue color component in range [0,1]. [AI]
	 */
	void SetLightColor(BOOL bDirectionalLight, float red, float green, float blue);

private:
	/**
	 * @brief [AI] Utility to set transformation of an arbitrary light object.
	 * @param pLight [AI] Light to transform. [AI]
	 * @param rMatrix [AI] New transformation matrix to apply. [AI]
	 */
	void SetLightTransform(Tgl::Light* pLight, Tgl::FloatMatrix4& rMatrix);

	/**
	 * @brief [AI] Utility to set RGB color of an arbitrary light object.
	 * @param pLight [AI] Light to alter color for. [AI]
	 * @param red [AI] Red color component [AI]
	 * @param green [AI] Green color component [AI]
	 * @param blue [AI] Blue color component [AI]
	 */
	void SetLightColor(Tgl::Light* pLight, float red, float green, float blue);

	Tgl::Light* m_pSunLight;         ///< @brief [AI] Point light source simulating sunlight. [AI]
	Tgl::Light* m_pDirectionalLight; ///< @brief [AI] Directional light source simulating directional sunlight or moonlight. [AI]
	Tgl::Light* m_pAmbientLight;     ///< @brief [AI] Ambient light source for base scene illumination. [AI]
};

// SYNTHETIC: LEGO1 0x100ab7a0
// SYNTHETIC: BETA10 0x1017cc00
// LegoView1::`scalar deleting destructor'

#endif /* _LegoView1_h */