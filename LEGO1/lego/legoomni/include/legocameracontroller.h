#ifndef LEGOCAMERACONTROLLER_H
#define LEGOCAMERACONTROLLER_H

#include "legopointofviewcontroller.h"
#include "mxgeometry.h"
#include "mxgeometry/mxgeometry3d.h"
#include "mxgeometry/mxmatrix.h"

// VTABLE: LEGO1 0x100d57b0
// VTABLE: BETA10 0x101bb748
// SIZE 0xc8

/**
 * @brief Camera controller for 3D scenes, handles interactive camera manipulation and view transformation. [AI]
 * @details Inherits from LegoPointOfViewController. Handles left/right mouse button and mouse movement to manipulate a camera's position and orientation within a 3D world. Maintains two transformation matrices for current and original state, and is capable of interacting with sound and video managers to reflect the new camera positions. [AI]
 */
class LegoCameraController : public LegoPointOfViewController {
public:
	/**
	 * @brief Constructor. Initializes the camera's world transform to a default pose at origin, looking forward. [AI]
	 */
	LegoCameraController();

	/**
	 * @brief Destructor. Cleans up and deregisters the camera from the input manager if set. [AI]
	 */
	~LegoCameraController() override; // vtable+0x00

	/**
	 * @brief Handles notifications for camera-relevant events (like mouse drag and mouse clicks). [AI]
	 * @param p_param Notification parameter. Casts to specific notification types as needed. [AI]
	 * @details This method dispatches notifications to appropriate event handlers (OnLButtonDown/Up, OnRButtonDown/Up, OnMouseMove) depending on the notification type and mouse button states. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+04

	/**
	 * @brief Returns the runtime class name for this type. [AI]
	 * @return Pointer to literal class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0850
		return "LegoCameraController";
	}

	/**
	 * @brief Checks if the name is compatible with this type or its ancestors. [AI]
	 * @param p_name Name string to compare. [AI]
	 * @return True if the queried name matches this class or a parent; otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief Called when the left mouse button is pressed at a screen point. [AI]
	 * @param p_point 2D point, typically window coordinates. [AI]
	 * @details Used to initiate camera interactions like dragging. [AI]
	 */
	virtual void OnLButtonDown(MxPoint32 p_point);                // vtable+0x30

	/**
	 * @brief Called when the left mouse button is released at a screen point. [AI]
	 * @param p_point 2D point, typically window coordinates. [AI]
	 */
	virtual void OnLButtonUp(MxPoint32 p_point);                  // vtable+0x34

	/**
	 * @brief Called when the right mouse button is pressed at a screen point. [AI]
	 * @param p_point 2D point, typically window coordinates. [AI]
	 */
	virtual void OnRButtonDown(MxPoint32 p_point);                // vtable+0x38

	/**
	 * @brief Called when the right mouse button is released at a screen point. [AI]
	 * @param p_point 2D point, typically window coordinates. [AI]
	 */
	virtual void OnRButtonUp(MxPoint32 p_point);                  // vtable+0x3c

	/**
	 * @brief Called when the mouse is moved. [AI]
	 * @param p_modifier Modifier indicating which mouse buttons/states are active (bitmask from LegoEventNotificationParam). [AI]
	 * @param p_point 2D mouse position. [AI]
	 * @details Used to process camera rotation or movement during dragging. [AI]
	 */
	virtual void OnMouseMove(MxU8 p_modifier, MxPoint32 p_point); // vtable+0x40

	/**
	 * @brief Registers the camera controller with input manager and initializes state with current view. [AI]
	 * @return Result status for creation. [AI]
	 */
	virtual MxResult Create();                                    // vtable+0x44

	/**
	 * @brief Updates the camera's world transformation matrix using view reference parameters. [AI]
	 * @param p_at Camera position or 'at' vector. [AI]
	 * @param p_dir Camera forward direction. [AI]
	 * @param p_up Camera up vector. [AI]
	 * @details Computes the local transform matrix from position, direction, and up vector. Stores both original and working matrices. [AI]
	 */
	void SetWorldTransform(const Vector3& p_at, const Vector3& p_dir, const Vector3& p_up);

	/**
	 * @brief Rotates the current camera transformation by a given angle around the Z axis. [AI]
	 * @param p_angle Angle in radians to rotate around Z. [AI]
	 * @details Restores backup matrix before applying new rotation to avoid cumulative drift. [AI]
	 */
	void FUN_10012290(float p_angle);

	/**
	 * @brief Rotates the current camera transformation by a given angle around the Y axis. [AI]
	 * @param p_angle Angle in radians to rotate around Y. [AI]
	 * @details Restores backup matrix before applying new rotation to avoid cumulative drift. [AI]
	 */
	void FUN_10012320(float p_angle);

	/**
	 * @brief Retrieves the current point-of-view transformation into a matrix if it exists. [AI]
	 * @param p_matrix Reference to the destination Matrix4. [AI]
	 * @return SUCCESS if POV matrix is available; otherwise FAILURE. [AI]
	 */
	MxResult FUN_100123b0(Matrix4& p_matrix);

	/**
	 * @brief Sets the camera's transformation matrix in the 3D view, optionally applying a blend with the internal matrix. [AI]
	 * @param p_transform The new transformation matrix to use. [AI]
	 * @param p_und If true, a combined transform is computed with the current matrix; otherwise, p_transform is used as-is. [AI]
	 * @details Also updates the associated sound listener orientation to match the camera. [AI]
	 */
	void FUN_100123e0(const Matrix4& p_transform, MxU32 p_und);

	/**
	 * @brief Gets the camera's current world-space up vector. [AI]
	 * @return Current up vector as a Mx3DPointFloat. Returns zero vector if not available. [AI]
	 */
	Mx3DPointFloat GetWorldUp();

	/**
	 * @brief Gets the camera's current world-space location. [AI]
	 * @return Current location as a Mx3DPointFloat. Applies entity offset if available; returns zero vector if not available. [AI]
	 */
	Mx3DPointFloat GetWorldLocation();

	/**
	 * @brief Gets the camera's world-space forward direction vector. [AI]
	 * @return Current direction as a Mx3DPointFloat. Returns zero vector if not available. [AI]
	 */
	Mx3DPointFloat GetWorldDirection();

private:
	/**
	 * @brief The current world transformation matrix (may be manipulated directly). [AI]
	 */
	MxMatrix m_matrix1; // 0x38

	/**
	 * @brief A backup (original) transformation matrix that is restored prior to new rotation operations. [AI]
	 */
	MxMatrix m_matrix2; // 0x80
};

// SYNTHETIC: LEGO1 0x10011f50
// LegoCameraController::`scalar deleting destructor'

#endif // LEGOCAMERACONTROLLER_H
