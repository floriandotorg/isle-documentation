#ifndef INFOCENTERDOOR_H
#define INFOCENTERDOOR_H

#include "legogamestate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;

/// @brief [AI] Represents the door world for the information center, handling control, transitions and area switching when the player interacts with infocenter exits and arrows.
/// @details [AI] Specializes the LegoWorld behavior to represent the area outside the Infocenter. Handles notification messages to trigger area transitions, raise/lower music volume, and routes user control to the correct destination (main infocenter, elevator, etc). Maintains the destination area to transition to when the player makes a choice at the Infocenter door. [AI]
///
/// VTABLE: LEGO1 0x100d72d8
/// VTABLE: BETA10 0x101b9bc0
class InfocenterDoor : public LegoWorld {
public:
	/// @brief [AI] Constructs the InfocenterDoor and registers for notifications. [AI]
	InfocenterDoor();
	/// @brief [AI] Cleans up InfocenterDoor, unregistering from control/notification managers and updating input state. [AI]
	~InfocenterDoor() override; // vtable+0x00

	/// @brief [AI] Handles notifications for actions ending, control input, and transitions in this world. [AI]
	/// @details [AI] Responds to the following notifications:
	/// - EndAction: Raises audio volume.
	/// - Control: Dispatches to HandleControl to process user actions.
	/// - Transitioned: Swaps to the destination location as decided by user input.
	/// Only handles these if the world is started. Returns status values according to handling. [AI]
	/// @param p_param Notification parameter, downcast depending on event. [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// @brief [AI] Used to signal this is a world with actor support (see base implementation). [AI]
	/// @return Always TRUE. [AI]
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// @brief [AI] Class name of this class for run-time type identification. [AI]
	/// @return The string literal "InfocenterDoor". [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return "InfocenterDoor";
	}

	/// @brief [AI] Checks if this object is of the specified class or inherits from it. [AI]
	/// @details [AI] Compares against "InfocenterDoor" and delegates to LegoWorld::IsA otherwise. [AI]
	/// @param p_name Name of class to check against. [AI]
	/// @return True if match, otherwise checks base class. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, InfocenterDoor::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// @brief [AI] Creates the InfocenterDoor world from a script action and sets up input/control handlers. [AI]
	/// @details [AI] Registers as the current world with the input and control managers and initializes state for the Infocenter door. [AI]
	/// @param p_dsAction SI script action to initialize with. [AI]
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// @brief [AI] Prepares the world for entry. [AI]
	/// @details [AI] Calls base ReadyWorld, plays Infocenter music via JukeboxScript, and disables input/3D/clears the screen. [AI]
	void ReadyWorld() override;                       // vtable+0x50

	/// @brief [AI] Handles ESC key (or game escape) in the InfocenterDoor world. [AI]
	/// @details [AI] Deletes pending audio objects, sets destination to Infocenter main, and signals escape complete. [AI]
	MxBool Escape() override;                         // vtable+0x64

	/// @brief [AI] Enables or disables the world, controlling input routing and world state. [AI]
	/// @details [AI] When enabling, sets self as input world; when disabling, clears input if this world is active. [AI]
	/// @param p_enable True to enable, false to disable. [AI]
	void Enable(MxBool p_enable) override;            // vtable+0x68

	// SYNTHETIC: LEGO1 0x100378d0
	// InfocenterDoor::`scalar deleting destructor'

private:
	LegoGameState::Area m_destLocation; ///< @brief [AI] The area ID (destination) the player should go upon completing the transition. [AI]

	/// @brief [AI] Handles control notification (user mouse/click input for arrows/doors) in this world. [AI]
	/// @details [AI] Determines which door or arrow was clicked and sets destination area accordingly. Handles playing appropriate sounds, music volume, and starts transition. If Info Door is entered, checks registration state before allowing exit. [AI]
	/// @param p_param The control input parameter, includes which control was clicked. [AI]
	/// @return 1 if handled, 0 otherwise. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
};

#endif // INFOCENTERDOOR_H
