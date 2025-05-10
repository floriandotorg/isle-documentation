#ifndef __LEGONAVCONTROLLER_H
#define __LEGONAVCONTROLLER_H

#include "decomp.h"
#include "mxcore.h"
#include "mxtypes.h"

struct LegoLocation;
class Vector3;

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

// VTABLE: LEGO1 0x100d85b8
// VTABLE: BETA10 0x101bcc80
// SIZE 0x70

/**
 * @brief [AI] Handles user navigation input (keyboard and joystick) and determines avatar movement and direction in the world. It encapsulates logic for target position/velocity setting, acceleration/deceleration, and navigation parameter defaults for LEGO Island's 3D world.
 * @details [AI] LegoNavController centralizes the logic for player-controlled navigation within the LEGO Island engine. It interprets user input (both keyboard and joystick), manages transitions between velocity/acceleration targets, and integrates movement into the engine's control loop. It provides interfaces for updating viewpoints to named "locations" and allows application-based adjustment of navigation dynamics (accel/decel/sensitivity/deadzone).
 */
class LegoNavController : public MxCore {
public:
	/**
	 * @brief [AI] Constructs a navigation controller and registers it for input processing.
	 */
	LegoNavController();

	/**
	 * @brief [AI] Destroys the controller and unregisters it from input processing.
	 */
	~LegoNavController() override;

	/**
	 * @brief [AI] Responds to notifications, including keypresses and special debug shortcuts for avatar control, animation, and world management.
	 * @param p_param Notification or event parameter, often a keypress or controller event. [AI]
	 * @return Returns 0 in all cases. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns this class's string name: "LegoNavController".
	 * @return Name string literal. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f66d8
		return "LegoNavController";
	}

	/**
	 * @brief [AI] Tests if this object is of type "LegoNavController" or any MxCore ancestor.
	 * @param p_name Class or ancestor class name to test. [AI]
	 * @return TRUE if type matches; FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief [AI] Set the horizontal/vertical target positions from input and optionally apply acceleration/dynamics.
	 * @param p_hPos Target X/horizontal position (e.g., joystick, mouse, etc). [AI]
	 * @param p_vPos Target Y/vertical position (e.g., joystick, mouse, etc). [AI]
	 * @param p_accel If TRUE, use acceleration (smooth ramping) toward target, otherwise jumps directly. [AI]
	 */
	void SetTargets(int p_hPos, int p_vPos, MxBool p_accel);

	/**
	 * @brief [AI] Set limits for horizontal and vertical input controls, typically reflecting window/screen size.
	 * @param p_hMax Maximum horizontal value (e.g., 640 for fullscreen). [AI]
	 * @param p_vMax Maximum vertical value (e.g., 480 for fullscreen). [AI]
	 */
	void SetControlMax(int p_hMax, int p_vMax);

	/**
	 * @brief [AI] Resets current navigation parameters to globally set defaults.
	 */
	void SetToDefaultParams();

	/**
	 * @brief [AI] Calculates the new position and direction vectors based on input, current velocity, and elapsed time.
	 * @param p_curPos Current position in world coordinates. [AI]
	 * @param p_curDir Current view or movement direction. [AI]
	 * @param p_newPos [out] Populated with computed new position vector. [AI]
	 * @param p_newDir [out] Populated with computed new direction vector. [AI]
	 * @param p_und Optional pointer to up-direction vector; affects calculation for inverse navigation/rotation direction. [AI]
	 * @return TRUE if position or direction changed, FALSE otherwise. [AI]
	 */
	MxBool CalculateNewPosDir(
		const Vector3& p_curPos,
		const Vector3& p_curDir,
		Vector3& p_newPos,
		Vector3& p_newDir,
		const Vector3* p_und
	);

	/**
	 * @brief [AI] Static: Retrieves current global default navigation parameter values.
	 * @param p_dz [out] Deadzone threshold. [AI]
	 * @param p_lv [out] Maximum linear velocity. [AI]
	 * @param p_rv [out] Maximum rotational velocity. [AI]
	 * @param p_la [out] Maximum linear acceleration. [AI]
	 * @param p_ra [out] Maximum rotational acceleration. [AI]
	 * @param p_ld [out] Maximum linear deceleration. [AI]
	 * @param p_rd [out] Maximum rotational deceleration. [AI]
	 * @param p_lmina [out] Minimum linear acceleration. [AI]
	 * @param p_rmina [out] Minimum rotational acceleration. [AI]
	 * @param p_rs [out] Rotation sensitivity. [AI]
	 * @param p_urs [out] Use rotational velocity flag. [AI]
	 */
	static void GetDefaults(
		int* p_dz,
		float* p_lv,
		float* p_rv,
		float* p_la,
		float* p_ra,
		float* p_ld,
		float* p_rd,
		float* p_lmina,
		float* p_rmina,
		float* p_rs,
		MxBool* p_urs
	);

	/**
	 * @brief [AI] Static: Sets new global defaults for navigation parameters.
	 * @param p_dz Deadzone threshold. [AI]
	 * @param p_lv Maximum linear velocity. [AI]
	 * @param p_rv Maximum rotational velocity. [AI]
	 * @param p_la Maximum linear acceleration. [AI]
	 * @param p_ra Maximum rotational acceleration. [AI]
	 * @param p_ld Maximum linear deceleration. [AI]
	 * @param p_rd Maximum rotational deceleration. [AI]
	 * @param p_lmina Minimum linear acceleration. [AI]
	 * @param p_rmina Minimum rotational acceleration. [AI]
	 * @param p_rs Rotation sensitivity. [AI]
	 * @param p_urs Use rotational velocity flag. [AI]
	 */
	static void SetDefaults(
		int p_dz,
		float p_lv,
		float p_rv,
		float p_la,
		float p_ra,
		float p_ld,
		float p_rd,
		float p_lmina,
		float p_rmina,
		float p_rs,
		MxBool p_urs
	);

	/**
	 * @brief [AI] Static: Changes the current world/camera location to the specified index in the location registry.
	 * @param p_location Index into the known locations array. [AI]
	 * @return SUCCESS if valid, FAILURE otherwise. [AI]
	 */
	static MxResult UpdateLocation(MxU32 p_location);

	/**
	 * @brief [AI] Static: Sets the world/camera location to a location registered by name.
	 * @param p_location Name string as registered in LegoLocation. [AI]
	 * @return SUCCESS if found and updated, FAILURE otherwise. [AI]
	 */
	static MxResult UpdateLocation(const char* p_location);

	/**
	 * @brief [AI] Static: Retrieves the number of named locations registered in the navigation system.
	 * @return Number of available locations. [AI]
	 */
	static MxS32 GetNumLocations();

	/**
	 * @brief [AI] Static: Retrieves the pointer to a LegoLocation struct by its index.
	 * @param p_location Index into the global location array. [AI]
	 * @return Pointer to the location struct, or NULL if out of bounds. [AI]
	 */
	static LegoLocation* GetLocation(MxU32 p_location);

	/**
	 * @brief [AI] Sets the current linear velocity for user navigation.
	 * @param p_linearVel New linear velocity value. [AI]
	 */
	void SetLinearVel(MxFloat p_linearVel) { m_linearVel = p_linearVel; }

	/**
	 * @brief [AI] Sets the deadzone radius for input processing (region within which inputs are ignored).
	 * @param p_deadZone Deadzone value in input units. [AI]
	 */
	void SetDeadZone(MxS32 p_deadZone) { m_deadZone = p_deadZone; }

	/**
	 * @brief [AI] Marks the controller to track global/default navigation parameters rather than custom overrides.
	 * @param p_trackDefault If TRUE, controller tracks default params. [AI]
	 */
	void SetTrackDefault(MxS32 p_trackDefault) { m_trackDefault = p_trackDefault; }

	/**
	 * @brief [AI] Resets the internal navigation state and all navigation parameters to current defaults.
	 */
	void Reset()
	{
		m_trackDefault = TRUE;
		SetToDefaultParams();
	}

	/**
	 * @brief [AI] Returns the current linear velocity (units per sec).
	 */
	MxFloat GetLinearVel() { return m_linearVel; }

	/**
	 * @brief [AI] Returns the current rotational velocity (degrees per sec).
	 */
	MxFloat GetRotationalVel() { return m_rotationalVel; }

	/**
	 * @brief [AI] Returns the current maximum linear velocity (units per sec).
	 */
	MxFloat GetMaxLinearVel() { return m_maxLinearVel; }

	/**
	 * @brief [AI] Returns the current maximum linear acceleration.
	 */
	MxFloat GetMaxLinearAccel() { return m_maxLinearAccel; }

	/**
	 * @brief [AI] Returns the current maximum linear deceleration.
	 */
	MxFloat GetMaxLinearDeccel() { return m_maxLinearDeccel; }

	/**
	 * @brief [AI] Resets the maximum allowed linear velocity and marks controller as using custom parameters.
	 * @param p_maxLinearVel New value for maximum linear velocity. [AI]
	 */
	void ResetMaxLinearVel(MxFloat p_maxLinearVel)
	{
		m_maxLinearVel = p_maxLinearVel;
		m_trackDefault = FALSE;
	}

	/**
	 * @brief [AI] Resets the maximum allowed linear acceleration and marks controller as using custom parameters.
	 * @param p_maxLinearAccel New value for maximum linear acceleration. [AI]
	 */
	void ResetMaxLinearAccel(MxFloat p_maxLinearAccel)
	{
		m_maxLinearAccel = p_maxLinearAccel;
		m_trackDefault = FALSE;
	}

	/**
	 * @brief [AI] Resets the maximum allowed linear deceleration and marks controller as using custom parameters.
	 * @param p_maxLinearDeccel New value for maximum linear deceleration. [AI]
	 */
	void ResetMaxLinearDeccel(MxFloat p_maxLinearDeccel)
	{
		m_maxLinearDeccel = p_maxLinearDeccel;
		m_trackDefault = FALSE;
	}

	/**
	 * @brief [AI] Returns the application-global default deadzone value for navigation input processing.
	 * @return Integer deadzone value. [AI]
	 */
	int GetDefaultDeadZone() { return g_defdeadZone; }

	// SYNTHETIC: LEGO1 0x10054c10
	// LegoNavController::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Calculates the next velocity given a target velocity, current velocity, acceleration, and elapsed time, clamped as needed.
	 * @param p_targetVel The target velocity to approach. [AI]
	 * @param p_currentVel The current velocity. [AI]
	 * @param p_accel The acceleration to use. [AI]
	 * @param p_time Time elapsed since last calculation (seconds). [AI]
	 * @return New velocity value. [AI]
	 */
	float CalculateNewVel(float p_targetVel, float p_currentVel, float p_accel, float p_time);

	/**
	 * @brief [AI] Translates control position into a new target velocity, applying deadzone and centering logic.
	 * @param p_pos Current axis position (input region, e.g., mouse/joystick). [AI]
	 * @param p_center Center value of the axis. [AI]
	 * @param p_max Maximum allowed velocity for this axis. [AI]
	 * @return New target velocity. [AI]
	 */
	float CalculateNewTargetVel(int p_pos, int p_center, float p_max);

	/**
	 * @brief [AI] Computes new acceleration value based on position, axis center, maximum and minimum acceleration.
	 * @param p_pos Input axis position. [AI]
	 * @param p_center Center value of the axis. [AI]
	 * @param p_max Maximum allowed acceleration. [AI]
	 * @param p_min Minimum allowed acceleration. [AI]
	 * @return New acceleration. [AI]
	 */
	float CalculateNewAccel(int p_pos, int p_center, float p_max, int p_min);

	/**
	 * @brief [AI] Processes current joystick/gamepad input and updates navigation targets and accelerations.
	 * @param p_und [out] Set TRUE if the joystick POV control resulted in freeview rotation (e.g., camera rotation from D-pad hatswitch). [AI]
	 * @return SUCCESS if joystick data was read and applied, FAILURE otherwise. [AI]
	 */
	MxResult ProcessJoystickInput(MxBool& p_und);

	/**
	 * @brief [AI] Reads and processes keyboard navigation input to update velocity/acceleration targets.
	 * @return SUCCESS if keys are active and state processed, FAILURE otherwise. [AI]
	 */
	MxResult ProcessKeyboardInput();

	/**
	 * @brief [AI] Current horizontal axis control maximum (e.g., 640 for screen width).
	 */
	int m_hMax;                  // 0x08

	/**
	 * @brief [AI] Current vertical axis control maximum (e.g., 480 for screen height).
	 */
	int m_vMax;                  // 0x0c

	/**
	 * @brief [AI] Deadzone value; minimum distance input must be from axis center to register as movement.
	 */
	int m_deadZone;              // 0x10

	/**
	 * @brief [AI] Threshold below which movements are considered negligible/zero.
	 */
	float m_zeroThreshold;       // 0x14

	/**
	 * @brief [AI] Current linear velocity.
	 */
	float m_linearVel;           // 0x18

	/**
	 * @brief [AI] Current rotational velocity.
	 */
	float m_rotationalVel;       // 0x1c

	/**
	 * @brief [AI] Target value for linear velocity, used for acceleration smoothing.
	 */
	float m_targetLinearVel;     // 0x20

	/**
	 * @brief [AI] Target value for rotational velocity, used for smoothing.
	 */
	float m_targetRotationalVel; // 0x24

	/**
	 * @brief [AI] Maximum allowed linear velocity.
	 */
	float m_maxLinearVel;        // 0x28

	/**
	 * @brief [AI] Maximum allowed rotational velocity.
	 */
	float m_maxRotationalVel;    // 0x2c

	/**
	 * @brief [AI] Current linear acceleration used to interpolate linear velocity.
	 */
	float m_linearAccel;         // 0x30

	/**
	 * @brief [AI] Current rotational acceleration used to interpolate rotational velocity.
	 */
	float m_rotationalAccel;     // 0x34

	/**
	 * @brief [AI] Maximum allowed linear acceleration.
	 */
	float m_maxLinearAccel;      // 0x38

	/**
	 * @brief [AI] Maximum allowed rotational acceleration.
	 */
	float m_maxRotationalAccel;  // 0x3c

	/**
	 * @brief [AI] Minimum allowed linear acceleration.
	 */
	float m_minLinearAccel;      // 0x40

	/**
	 * @brief [AI] Minimum allowed rotational acceleration.
	 */
	float m_minRotationalAccel;  // 0x44

	/**
	 * @brief [AI] Maximum allowed linear deceleration (negative accel).
	 */
	float m_maxLinearDeccel;     // 0x48

	/**
	 * @brief [AI] Maximum allowed rotational deceleration.
	 */
	float m_maxRotationalDeccel; // 0x4c

	/**
	 * @brief [AI] Sensitivity multiplier for rotation (applies if useRotationalVel is FALSE).
	 */
	float m_rotSensitivity;      // 0x50

	/**
	 * @brief [AI] If TRUE, rotation is determined by velocity (dynamic turning); if FALSE, snaps turn instantly.
	 */
	MxBool m_useRotationalVel;   // 0x54

	/**
	 * @brief [AI] Tracks time of the last navigation tick for smooth movement with deltaTime.
	 */
	MxTime m_lastTime;           // 0x58

	/**
	 * @brief [AI] TRUE if navigation parameters should match the application defaults; FALSE to allow per-instance override.
	 */
	MxBool m_trackDefault;       // 0x5c

	/**
	 * @brief [AI] Indicates that Notify() should inject a one-time movement/turn based on special debug or event triggers.
	 */
	MxBool m_unk0x5d;            // 0x5d

	/**
	 * @brief [AI] [Usage: debug/direct movement] Y-offset applied to next position after Notify key event.
	 */
	float m_unk0x60;             // 0x60

	/**
	 * @brief [AI] [Usage: debug/direct movement] Linear velocity applied to next position after Notify key event.
	 */
	float m_unk0x64;             // 0x64

	/**
	 * @brief [AI] [Usage: debug/direct movement] Rotational offset (degrees), to next direction vector after Notify event.
	 */
	float m_unk0x68;             // 0x68

	/**
	 * @brief [AI] TRUE if last input was an active movement/acceleration (vs. at rest).
	 */
	MxBool m_isAccelerating;     // 0x6c

	// one copy of defaults (these can be set by App.)
	/**
	 * @brief [AI] Application-global default deadzone value.
	 */
	static int g_defdeadZone;

	/**
	 * @brief [AI] Application-global default zero threshold value.
	 */
	static float g_defzeroThreshold;

	/**
	 * @brief [AI] Application-global default max linear velocity.
	 */
	static float g_defmaxLinearVel;

	/**
	 * @brief [AI] Application-global default max rotational velocity.
	 */
	static float g_defmaxRotationalVel;

	/**
	 * @brief [AI] Application-global default max linear acceleration.
	 */
	static float g_defmaxLinearAccel;

	/**
	 * @brief [AI] Application-global default max rotational acceleration.
	 */
	static float g_defmaxRotationalAccel;

	/**
	 * @brief [AI] Application-global default min linear acceleration.
	 */
	static float g_defminLinearAccel;

	/**
	 * @brief [AI] Application-global default min rotational acceleration.
	 */
	static float g_defminRotationalAccel;

	/**
	 * @brief [AI] Application-global default max linear deceleration.
	 */
	static float g_defmaxLinearDeccel;

	/**
	 * @brief [AI] Application-global default max rotational deceleration.
	 */
	static float g_defmaxRotationalDeccel;

	/**
	 * @brief [AI] Application-global default rotation sensitivity.
	 */
	static float g_defrotSensitivity;

	/**
	 * @brief [AI] Application-global default for useRotationalVel.
	 */
	static MxBool g_defuseRotationalVel;
};

#endif // __LEGOPOVCONTROLLER_H
