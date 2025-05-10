#ifndef LEGOPOINTOFVIEWCONTROLLER_H
#define LEGOPOINTOFVIEWCONTROLLER_H

#include "decomp.h"
#include "mxcore.h"
#include "mxgeometry.h"

#include <windows.h>

class Lego3DView;
class LegoEntity;
class LegoNavController;

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

// VTABLE: LEGO1 0x100d8dd8
// SIZE 0x20
/**
 * @brief [AI] Handles mouse input relevant to camera or entity control. [AI]
 * @details [AI] LegoMouseController processes mouse button presses, drags, and releases for the left and right mouse buttons, 
 * maintaining the pressed state and the position at which the mouse was last pressed. It is designed as a base class for more
 * specific controllers, such as LegoPointOfViewController. [AI]
 */
class LegoMouseController : public MxCore {
public:
	LegoMouseController(); ///< @brief [AI] Constructor initializing state of mouse button. [AI]
	~LegoMouseController() override; ///< @brief [AI] Destructor for mouse controller. [AI]

	/**
	 * @brief [AI] Invoked when the left mouse button is pressed. [AI]
	 * @param x [AI] X coordinate in screen space. [AI]
	 * @param y [AI] Y coordinate in screen space. [AI]
	 */
	virtual void LeftDown(int, int);  // vtable+0x14

	/**
	 * @brief [AI] Invoked as the mouse drags while the left button is held. [AI]
	 * @param x [AI] Current X coordinate. [AI]
	 * @param y [AI] Current Y coordinate. [AI]
	 */
	virtual void LeftDrag(int, int);  // vtable+0x18

	/**
	 * @brief [AI] Invoked when the left mouse button is released. [AI]
	 * @param x [AI] X coordinate where the button was released. [AI]
	 * @param y [AI] Y coordinate where the button was released. [AI]
	 */
	virtual void LeftUp(int, int);    // vtable+0x1c

	/**
	 * @brief [AI] Invoked when the right mouse button is pressed. [AI]
	 * @param x [AI] X coordinate in screen space. [AI]
	 * @param y [AI] Y coordinate in screen space. [AI]
	 */
	virtual void RightDown(int, int); // vtable+0x20

	/**
	 * @brief [AI] Invoked as the mouse drags while the right button is held. [AI]
	 * @param x [AI] Current X coordinate. [AI]
	 * @param y [AI] Current Y coordinate. [AI]
	 */
	virtual void RightDrag(int, int); // vtable+0x24

	/**
	 * @brief [AI] Invoked when the right mouse button is released. [AI]
	 * @param x [AI] X coordinate where the button was released. [AI]
	 * @param y [AI] Y coordinate where the button was released. [AI]
	 */
	virtual void RightUp(int, int);   // vtable+0x28

	/**
	 * @brief [AI] Returns whether any mouse button is currently in the 'down' state. [AI]
	 */
	BOOL GetIsButtonDown() { return m_isButtonDown; }

	/**
	 * @brief [AI] Returns the X coordinate where the last mouse button event occurred. [AI]
	 */
	MxDouble GetButtonX() { return m_buttonX; }

	/**
	 * @brief [AI] Returns the Y coordinate where the last mouse button event occurred. [AI]
	 */
	MxDouble GetButtonY() { return m_buttonY; }

private:
	BOOL m_isButtonDown;  ///< @brief [AI] Indicates if a mouse button is currently pressed. [AI]
	undefined4 m_unk0x0c; ///< @brief [AI] Reserved/unknown, potentially for future state or padding. [AI_UNK]
	MxDouble m_buttonX;   ///< @brief [AI] Stores X position of mouse at last button event. [AI]
	MxDouble m_buttonY;   ///< @brief [AI] Stores Y position of mouse at last button event. [AI]
};

// SYNTHETIC: LEGO1 0x100655b0
// LegoMouseController::`scalar deleting destructor'

// VTABLE: LEGO1 0x100d8e08
// SIZE 0x38
/**
 * @brief [AI] Controller that links mouse actions to manipulation of the user's point of view in the 3D scene. [AI]
 * @details [AI] Extends LegoMouseController to apply mouse button and drag events to camera or entity point of view control.
 * Connects actions such as dragging or clicking to navigation/camera manipulation, typically inside a 3D game view.
 * Holds references to entity and navigation controller to enable direct manipulation and feedback. [AI]
 */
class LegoPointOfViewController : public LegoMouseController {
public:
	LegoPointOfViewController(); ///< @brief [AI] Initializes state for coordinating mouse and point-of-view. [AI]
	~LegoPointOfViewController() override; ///< @brief [AI] Destructor; cleans up any owned references. [AI]

	/**
	 * @brief [AI] Called each frame (tick) to update the state of the point of view, potentially responding to input or animation. [AI]
	 * @return [AI] Result indicating status of the tick (success or error). [AI]
	 */
	MxResult Tickle() override;               // vtable+0x08

	/**
	 * @brief [AI] Called when left mouse button is pressed; may start point-of-view manipulation. [AI]
	 * @param p_x [AI] X coordinate. [AI]
	 * @param p_y [AI] Y coordinate. [AI]
	 */
	void LeftDown(int p_x, int p_y) override; // vtable+0x0c

	/**
	 * @brief [AI] Called when cursor moves with left mouse button held; typically drags the point of view. [AI]
	 * @param p_x [AI] New X coordinate. [AI]
	 * @param p_y [AI] New Y coordinate. [AI]
	 */
	void LeftDrag(int p_x, int p_y) override; // vtable+0x10

	/**
	 * @brief [AI] Called when the left button is released, possibly to end the manipulation and update the camera/entity. [AI]
	 * @param p_x [AI] Release X. [AI]
	 * @param p_y [AI] Release Y. [AI]
	 */
	void LeftUp(int p_x, int p_y) override
	{
		LegoMouseController::LeftUp(p_x, p_y);
		AffectPointOfView();
	}
	// vtable+0x14

	/**
	 * @brief [AI] Called when the right mouse button is pressed; often used for alternative camera controls. [AI]
	 * @param p_x [AI] X coordinate. [AI]
	 * @param p_y [AI] Y coordinate. [AI]
	 */
	void RightDown(int p_x, int p_y) override
	{
		LegoMouseController::RightDown(p_x, p_y);
		AffectPointOfView();
	}
	// vtable+0x20

	/**
	 * @brief [AI] Called when right button is held and cursor is moved, e.g., for rotational camera movement. [AI]
	 * @param p_x [AI] New X coordinate. [AI]
	 * @param p_y [AI] New Y coordinate. [AI]
	 */
	void RightDrag(int p_x, int p_y) override
	{
		LegoMouseController::RightDrag(p_x, p_y);
		AffectPointOfView();
	}
	// vtable+0x24

	/**
	 * @brief [AI] Called when the right mouse button is released, possibly to finalize alternative camera/entity action. [AI]
	 * @param p_x [AI] Release X coordinate. [AI]
	 * @param p_y [AI] Release Y coordinate. [AI]
	 */
	void RightUp(int p_x, int p_y) override
	{
		LegoMouseController::RightUp(p_x, p_y);
		AffectPointOfView();
	}                                             // vtable+0x28

	/**
	 * @brief [AI] Assign the entity which this controller operates on, typically to associate the point of view with a specific character or camera. [AI]
	 * @param p_entity [AI] Pointer to target LegoEntity. [AI]
	 */
	virtual void SetEntity(LegoEntity* p_entity); // vtable+0x2c

	/**
	 * @brief [AI] Initializes the controller with a specific 3D view. [AI]
	 * @param p_lego3DView [AI] Target 3D view context for rendering and input. [AI]
	 * @return [AI] Status of creation. [AI]
	 */
	MxResult Create(Lego3DView* p_lego3DView);

	/**
	 * @brief [AI] Updates the controller's internal state for a view size change, such as resizing the 3D viewport. [AI]
	 * @param p_width [AI] New width in pixels. [AI]
	 * @param p_height [AI] New height in pixels. [AI]
	 */
	void OnViewSize(int p_width, int p_height);

	/**
	 * @brief [AI] Accessor for the currently attached entity. [AI]
	 */
	LegoEntity* GetEntity() { return m_entity; }

	/**
	 * @brief [AI] Accessor for the navigation controller associated with this point-of-view controller. [AI]
	 */
	LegoNavController* GetNavController() { return m_nav; }

protected:
	/**
	 * @brief [AI] Internal method to compute and apply the effect of user mouse input on the current point of view, entity, or camera, as appropriate. [AI]
	 */
	void AffectPointOfView();

	Lego3DView* m_lego3DView;  ///< @brief [AI] The active 3D view that input actions are translated into. [AI]
	LegoEntity* m_entity;      ///< @brief [AI] The entity whose point of view this controller manipulates. [AI]
	MxDouble m_entityOffsetUp; ///< @brief [AI] Offset along the entity's upward vector (for perspective/camera alignment). [AI]
	LegoNavController* m_nav;  ///< @brief [AI] Navigation controller used to translate input to navigation/camera changes. [AI]
};

// SYNTHETIC: LEGO1 0x10065750
// LegoPointOfViewController::`scalar deleting destructor'

#endif /* LEGOPOINTOFVIEWCONTROLLER_H */