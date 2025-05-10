#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "islepathactor.h"
#include "legostate.h"
#include "mxgeometry/mxquaternion.h"

class Act3;

/// \class HelicopterState
/// \brief [AI] Game state entity specialized for tracking Helicopter-related state during gameplay. [AI]
/// \details [AI] This stores simple state/progress (m_unk0x08) specific to Helicopter interactions/animations and serializes via LegoState. [AI]
/// \ingroup State
class HelicopterState : public LegoState {
public:
	/// \brief [AI] Default constructor initializes unmapped state property to zero. [AI]
	HelicopterState() : m_unk0x08(0) {}

	/// \brief [AI] Indicates if this state can be serialized (always false for HelicopterState). [AI]
	/// \return Always FALSE; HelicopterState is *not* serializable. [AI]
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14

	/// \brief [AI] Resets helicopter-specific state/progress tracking variable. [AI]
	/// \details [AI] Sets m_unk0x08 (the main state variable) to zero, clearing the internal state/progress for the helicopter. [AI]
	/// \return Always TRUE. [AI]
	MxBool Reset() override
	{
		m_unk0x08 = 0;
		return TRUE;
	} // vtable+0x18

	/// \brief [AI] Returns the runtime class name string of this object. [AI]
	/// \return "HelicopterState" [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0144
		return "HelicopterState";
	}

	/// \brief [AI] Checks if this object is of the requested class or a parent class. [AI]
	/// \param p_name Class name string to check. [AI]
	/// \return TRUE if matches HelicopterState or a parent class. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, HelicopterState::ClassName()) || LegoState::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1000e190
	// HelicopterState::`scalar deleting destructor'

	MxU32 m_unk0x08; ///< [AI] State/progress value for the helicopter, used for tracking animation or progress in gameplay. [AI]
};

/// \class Helicopter
/// \brief [AI] Represents the flyable helicopter vehicle/path actor in the game, handling all in-game behaviors. [AI]
/// \details [AI] Handles animation, control/click events, and camera movement for the helicopter entity and interacts with the Act3/Arena minigame. [AI]
class Helicopter : public IslePathActor {
public:
	/// \brief [AI] Constructs and initializes helicopter-specific settings. [AI]
	Helicopter();

	/// \brief [AI] Destructor, handles cleanup/unregistration. [AI]
	~Helicopter() override; // vtable+0x00

	/// \brief [AI] Returns the runtime class name string for this object instance. [AI]
	/// \return "Helicopter" [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0130
		return "Helicopter";
	}

	/// \brief [AI] Checks if this object is of the requested class or a superclass. [AI]
	/// \param p_name Class name string to check. [AI]
	/// \return TRUE if matches Helicopter or any parent class. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Helicopter::ClassName()) || IslePathActor::IsA(p_name);
	}

	/// \brief [AI] Creates (initializes) the helicopter entity from an action script. [AI]
	/// \details [AI] Registers with the world, initializes m_state, and ties actor to Act3 as needed. [AI]
	/// \param p_dsAction Action descriptor used for creation. [AI]
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// \brief [AI] Handles animation logic for the helicopter. [AI]
	/// \param p_time Elapsed time or frame time. [AI]
	void Animate(float p_time) override; // vtable+0x70

	/// \brief [AI] Applies world transformations relevant to helicopter motion/position. [AI]
	/// \param p_transform World transformation to apply. [AI]
	void VTable0x74(Matrix4& p_transform) override; // vtable+0x74

	/// \brief [AI] Processes click interactions with the helicopter UI/actor. [AI]
	/// \return Game-specific value (e.g., TRUE if handled, FALSE if not applicable). [AI]
	MxLong HandleClick() override; // vtable+0xcc

	/// \brief [AI] Processes input/control events specific to helicopter (dashboard/cockpit/archetype event handling). [AI]
	/// \param p_param Control manager notification parameters. [AI]
	/// \return Nonzero if handled. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override; // vtable+0xd4

	/// \brief [AI] Handles end-of-animation events for the helicopter (e.g., animation state transitions). [AI]
	/// \param p_param End animation notification. [AI]
	/// \return Nonzero if processed/transitioned. [AI]
	MxLong HandleEndAnim(LegoEndAnimNotificationParam& p_param) override; // vtable+0xd8

	/// \brief [AI] Handles the helicopter's exit/teardown. Resets state, unregisters, updates game state and cleans dashboard/UI. [AI]
	void Exit() override; // vtable+0xe4

	/// \brief [AI] Creates or retrieves the associated HelicopterState instance for this actor. [AI]
	void CreateState();
	
	/// \brief [AI] Initiates camera transition for takeoff (Act3 minigame). [AI]
	/// \details [AI] Used to smoothly animate the camera when helicopter takes off. [AI]
	/// \param p_matrix World matrix for target transform. [AI]
	void FUN_10004640(const Matrix4& p_matrix);

	/// \brief [AI] Initiates camera transition for landing (Act3 minigame). [AI]
	/// \details [AI] Used to smoothly animate the camera when helicopter lands. [AI]
	/// \param p_matrix World matrix for target transform. [AI]
	void FUN_10004670(const Matrix4& p_matrix);

	// SYNTHETIC: LEGO1 0x10003210
	// Helicopter::`scalar deleting destructor'

	/// \brief [AI] This allows Act3 arena/minigame to access and modify the helicopter's state. [AI]
	friend class Act3;

protected:
	/// \brief [AI] Internal: Sets up smooth camera path and stores transform endpoints used for takeoff/landing transitions. [AI]
	/// \param p_matrix End transform used for interpolating camera. [AI]
	void FUN_100042a0(const Matrix4& p_matrix);

	MxMatrix m_unk0x160;                ///< [AI] Stores start matrix (camera/actor) for camera transitions/interpolation. [AI]
	MxMatrix m_unk0x1a8;                ///< [AI] Stores end matrix (camera/actor) for camera transitions/interpolation. [AI]
	float m_unk0x1f0;                   ///< [AI] Timestamp for beginning of camera/copter transition—used for timing interpolation. [AI]
	MxQuaternionTransformer m_unk0x1f4; ///< [AI] Interpolator for quaternion/matrix transforms (camera movement for animation). [AI]
	HelicopterState* m_state;           ///< [AI] Pointer to the associated HelicopterState tracking per-helicopter animation/state. [AI]
	MxAtomId m_script;                  ///< [AI] Current script-atom identifier for action callbacks and in-game object referencing. [AI]
};

#endif // HELICOPTER_H