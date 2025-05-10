#ifndef POLICE_H
#define POLICE_H

#include "decomp.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "radio.h"

class LegoControlManagerNotificationParam;
class LegoEventNotificationParam;
class MxDSAction;

/// \brief [AI] Represents the state information specific to the Police area of the game. [AI]
///
/// This holds the currently active police script/animation and a flag
/// for internal state machine transitions. Serialized as part of the game state when saving/loading.
/// Inherits from LegoState for polymorphic game state management. [AI]
class PoliceState : public LegoState {
public:
	/// \brief [AI] Constructs a new PoliceState. Initializes script and internal state. [AI]
	PoliceState();

	/// \brief [AI] Default destructor. [AI]
	~PoliceState() override {}

	/// \brief [AI] Returns the class name for this type; used for RTTI and IsA checks. [AI]
	/// \return Pointer to string literal "PoliceState". [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return "PoliceState";
	}

	/// \brief [AI] Checks whether the given type name matches this class or any ancestor. [AI]
	/// \param p_name Name of the class to match. [AI]
	/// \return TRUE if match, FALSE otherwise. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, PoliceState::ClassName()) || LegoState::IsA(p_name);
	}

	/// \brief [AI] Serialize the PoliceState to or from the provided storage. [AI]
	/// \param p_storage File or memory storage interface for serialization. [AI]
	/// \details [AI] Reads or writes the current script from/to storage, as well as base LegoState members. [AI]
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	/// \brief [AI] Returns the value of the internal state variable at offset 0x0c. [AI]
	/// \return Internal state value (purpose: tracks running donut animation, toggles between allowed actions). [AI]
	undefined4 GetUnknown0x0c() { return m_unk0x0c; }

	/// \brief [AI] Set the value of the internal state variable at offset 0x0c. [AI]
	/// \param p_unk0x0c New internal state value. [AI]
	void SetUnknown0x0c(undefined4 p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

	/// \brief [AI] Trigger the "donut" animation event. [AI]
	/// \details [AI] Switches the police script according to the user-controlled actor, plays corresponding anim, and marks donut animation as started. [AI]
	void FUN_1005ea40();

	/// \brief [AI] The currently active animation/script for the Police state (e.g. which minifig or animation runs). [AI]
	PoliceScript::Script m_policeScript; // 0x08

	/// \brief [AI] Internal flag to indicate whether the donut animation has started (1), finished (0), or unused. [AI]
	/// Used to block or allow additional interactions. [AI]
	undefined4 m_unk0x0c;                // 0x0c
};

/// \brief [AI] Main world object for the Police Station area in LEGO Island. [AI]
///
/// Handles script/animation management, user interactions, state transitions, and links to PoliceState for serialization.
/// Extends LegoWorld to participate in the general world handling infrastructure. [AI]
class Police : public LegoWorld {
public:
	/// \brief [AI] Constructs the Police world, setting up default state and registering for notifications. [AI]
	Police();

	/// \brief [AI] Destructor: deregisters world from managers and clears input/world pointers. [AI]
	~Police() override; // vtable+0x00

	/// \brief [AI] Handle incoming notifications (key presses, controls, end actions, transitions). [AI]
	/// \param p_param Struct containing the notification event details. [AI]
	/// \details [AI] Routes to appropriate local handler, typically on user input or script actions. [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Returns TRUE for this virtual slot (area loading indication or presence check). [AI]
	/// \details [AI] Used for slot/area readiness in the world manager. [AI]
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// \brief [AI] Returns the class name for this type ("Police")—used for IsA and RTTI. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return "Police";
	}

	/// \brief [AI] Checks if this object matches the given class name, including ancestors (LegoWorld). [AI]
	/// \param p_name Class name string. [AI]
	/// \return TRUE if name matches this or an ancestor class. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Police::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// \brief [AI] Handles world creation, input setup, and PoliceState initialization. [AI]
	/// \param p_dsAction The startup/trigger action for the world. [AI]
	/// \details [AI] Registers input/controls and ensures the PoliceState object is available. [AI]
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// \brief [AI] Prepares the Police world for activation, setting music and disabling user input/3d as needed. [AI]
	void ReadyWorld() override; // vtable+0x50

	/// \brief [AI] Handles user request to exit the Police area (e.g., Escape key). [AI]
	/// \details [AI] Deletes script objects and switches destination area to infotainment area. [AI]
	MxBool Escape() override; // vtable+0x64

	/// \brief [AI] Enables or disables the Police world for input and activity. [AI]
	/// \param p_enable If TRUE, enables world; if FALSE, disables and clears world from input manager. [AI]
	void Enable(MxBool p_enable) override; // vtable+0x68

private:
	/// \brief [AI] Handles control notification events from the control manager (e.g., button clicks). [AI]
	/// \param p_param Control notification parameters containing the clicked control/object. [AI]
	/// \details [AI] Triggers script deletion, area transitions, and special events like donut animation. [AI]
	/// \return Always returns 1. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);

	/// \brief [AI] Handles end-of-action notifications (animation/script finished). [AI]
	/// \param p_param End action notification with pointer to finished DSAction. [AI]
	/// \return 1 if donut anim finished (flag reset), 0 otherwise. [AI]
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/// \brief [AI] Handle key press notification events for the Police world. [AI]
	/// \param p_param Event notification with key code pressed. [AI]
	/// \details [AI] Special handling for SPACE to interrupt donut animation. [AI]
	/// \return 1 if recognized, 0 otherwise. [AI]
	MxLong HandleKeyPress(LegoEventNotificationParam& p_param);

	/// \brief [AI] Handles in-game radio in Police station, plays/stops music or sound events. [AI]
	Radio m_radio;                      // 0xf8

	/// \brief [AI] Pointer to the currently active PoliceState, used for animation state, serializing progress, etc. [AI]
	PoliceState* m_policeState;         // 0x108

	/// \brief [AI] Area to switch to on transition (police door, infotainment, or copter build). [AI]
	LegoGameState::Area m_destLocation; // 0x10c
};

#endif // POLICE_H
