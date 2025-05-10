#ifndef _Lego3DView_h
#define _Lego3DView_h

#include "decomp.h"
#include "legoview1.h"

class ViewManager;
class ViewROI;

/////////////////////////////////////////////////////////////////////////////
// Lego3DView

/**
 * @brief [AI] Represents a 3D view for rendering and managing LEGO game objects in a 3D scene. 
 * 
 * Inherits from LegoView1 and acts as the main render target for 3D objects, handling the addition and removal
 * of objects, point of view management, and rendering logic. Utilizes a ViewManager to coordinate the scene and camera.
 * [AI]
 */
class Lego3DView : public LegoView1 {
public:
	/**
	 * @brief [AI] Constructs a new Lego3DView instance.
	 */
	Lego3DView();

	/**
	 * @brief [AI] Destroys the Lego3DView instance and all associated resources via Destroy().
	 */
	~Lego3DView() override;

	/**
	 * @brief [AI] Initializes the 3D view with the specified surface creation parameters and renderer interface.
	 * 
	 * Initializes the underlying rendering view, sets up the viewing frustum and constructs 
	 * the ViewManager for scene management. 
	 * 
	 * @param rCreateStruct Struct containing properties for initialization, including view angle.
	 * @param pRenderer Renderer interface used for low-level rendering context creation.
	 * @return TRUE if successfully created; FALSE otherwise. [AI]
	 */
	BOOL Create(const CreateStruct& rCreateStruct, Tgl::Renderer* pRenderer);

	/**
	 * @brief [AI] Cleans up resources allocated by the view, including the ViewManager,
	 * unset the point of view, and calls the parent Destroy(). [AI]
	 */
	void Destroy() override; // vtable+0x08

	/**
	 * @brief [AI] Adds a ViewROI (renderable object instance) to the scene.
	 * Forwards to ViewManager::Add().
	 * 
	 * @param rROI Reference to the ViewROI to be added.
	 * @return TRUE if added successfully. [AI]
	 */
	BOOL Add(ViewROI& rROI);

	/**
	 * @brief [AI] Removes a ViewROI from the scene.
	 * Forwards to ViewManager::Remove(). If the ViewROI is the current point of view,
	 * it resets the POV.
	 * 
	 * @param rROI Reference to the ViewROI to remove.
	 * @return TRUE if removed successfully. [AI]
	 */
	BOOL Remove(ViewROI& rROI);

	/**
	 * @brief [AI] Notifies the view that a ViewROI has moved. 
	 * If the moved object is the current point of view, updates the camera transformation
	 * to match the object's transformation.
	 * 
	 * @param rROI The ViewROI that moved.
	 * @return TRUE after handling update. [AI]
	 */
	BOOL Moved(ViewROI& rROI);

	/**
	 * @brief [AI] Sets the current point of view to the specified ViewROI and updates the camera transformation.
	 * Updates the ViewManager's POV source as well.
	 * 
	 * @param rROI The ViewROI to use as the new point of view.
	 * @return TRUE if successful. [AI]
	 */
	BOOL SetPointOfView(ViewROI& rROI);

	/**
	 * @brief [AI] Renders the scene using the ViewManager and returns the render time.
	 * Calls ViewManager::Update() and then base surface Render().
	 * 
	 * @param p_und Elapsed time or time delta since last render, for frame update logic.
	 * @return The time of the last render; used for animation/timing. [AI]
	 */
	double Render(double p_und);

	/**
	 * @brief [AI] Picks (selects) a ViewROI in the scene by screen-space coordinates.
	 * Uses ViewManager's picking logic.
	 * 
	 * @param x The horizontal screen coordinate.
	 * @param y The vertical screen coordinate.
	 * @return The ViewROI* under the (x, y) position or nullptr if none. [AI]
	 */
	ViewROI* Pick(unsigned long x, unsigned long y);

	/**
	 * @brief [AI] Returns the current point-of-view object (the ViewROI the camera is following).
	 * @return Pointer to the current POV ViewROI, or nullptr if none. [AI]
	 */
	ViewROI* GetPointOfView();

	/**
	 * @brief [AI] Returns the ViewManager responsible for managing scene objects and transformations.
	 * @return Pointer to the associated ViewManager. [AI]
	 */
	ViewManager* GetViewManager();

private:
	/**
	 * @brief [AI] The ViewManager associated with this view, responsible for object management, 
	 * picking, and frustum settings. [AI]
	 */
	ViewManager* m_pViewManager; // 0x88

	/**
	 * @brief [AI] Stores the most recent render time for frame-based update logic. [AI]
	 */
	double m_previousRenderTime; // 0x90

	/**
	 * @brief [AI] Unknown double; likely reserved for future timing or animation state.
	 * [AI_SUGGESTED_NAME: m_additionalRenderState] [AI]
	 */
	double m_unk0x98;            // 0x98

	/**
	 * @brief [AI] Pointer to the current POV source, i.e., the ViewROI that defines the
	 * camera's transformation in the scene. [AI]
	 */
	ViewROI* m_pPointOfView;     // 0xa0
};

// SYNTHETIC: LEGO1 0x100aaf10
// Lego3DView::`scalar deleting destructor'

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DView implementation

/**
 * @copydoc Lego3DView::GetViewManager [AI]
 */
inline ViewManager* Lego3DView::GetViewManager()
{
	return m_pViewManager;
}

/**
 * @copydoc Lego3DView::GetPointOfView [AI]
 */
inline ViewROI* Lego3DView::GetPointOfView()
{
	return m_pPointOfView;
}

#endif /* _Lego3DView_h */