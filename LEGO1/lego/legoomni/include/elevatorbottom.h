#ifndef ELEVATORBOTTOM_H
#define ELEVATORBOTTOM_H

#include "decomp.h"
#include "legogamestate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;

/// \class ElevatorBottom
/// \brief [AI] This class represents the "Elevator Bottom" area in the LEGO Island game. It is responsible for handling the logic and transitions specific to the bottom of the elevator, including reacting to in-game events, user controls, and area transitions.
/// \details [AI] ElevatorBottom derives from LegoWorld and represents a special game world (area) tied to the bottom elevator location. It manages in-game notifications, control logic for user clicks on elevator controls, handling transitions to other areas, and updating game state appropriately. [AI]
/// 
/// Key responsibilities:
/// - Handles control notifications (such as button presses in the elevator area).
/// - Initiates transitions to other areas based on user input.
/// - Updates the area recorded in the global game state.
/// - Manages the enabling/disabling of input and world state for this area.
/// - Plays area-specific music when the world is prepared.
/// [AI]
///
/// SIZE 0xfc
class ElevatorBottom : public LegoWorld {
public:
	/// \brief [AI] Constructs the ElevatorBottom object and registers it for notifications. [AI]
	ElevatorBottom();

	/// \brief [AI] Destroys the ElevatorBottom object, unregistering it from input, control, and notification managers. [AI]
	~ElevatorBottom() override; // vtable+0x00

	/// \brief [AI] Handles notifications received while this world is active, such as control interactions and transitions. [AI]
	/// \param p_param [AI] Notification parameter received from the system, expected as an MxNotificationParam or derived type.
	/// \return [AI] Implementation-specific value, typically indicating if the notification was handled.
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Indicates that this world is always considered "active" for tickling purposes. [AI]
	/// \return [AI] Always returns TRUE for ElevatorBottom.
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// \brief [AI] Returns the class name identifier for runtime type checking. [AI]
	/// \return [AI] The string "ElevatorBottom".
	const char* ClassName() const override // vtable+0x0c
	{
		return "ElevatorBottom";
	}

	/// \brief [AI] Checks if this object is a class or subclass matching the provided name. [AI]
	/// \param p_name [AI] The name to check against ("ElevatorBottom" or parent types).
	/// \return [AI] TRUE if the class matches, otherwise delegates to base class.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ElevatorBottom::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// \brief [AI] Initializes the world with a given action, registers input/world, and sets initial area state. [AI]
	/// \param p_dsAction [AI] The DSAction driving creation/transition to this world.
	/// \return [AI] SUCCESS or appropriate error result from base class.
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// \brief [AI] Prepares the world for activation (e.g., starts music, disables input/3D as needed). [AI]
	void ReadyWorld() override;                       // vtable+0x50

	/// \brief [AI] Handles the user's "escape" action (such as pressing ESC), transitioning out of this area, and cleans up relevant objects. [AI]
	/// \return [AI] Always returns TRUE after transitioning to the info main area.
	MxBool Escape() override;                         // vtable+0x64

	/// \brief [AI] Enables or disables the world, updating input manager links and world activation state. [AI]
	/// \param p_enable [AI] TRUE to enable, FALSE to disable.
	void Enable(MxBool p_enable) override;            // vtable+0x68

	// SYNTHETIC: LEGO1 0x10018040
	// ElevatorBottom::`scalar deleting destructor'

private:
	/// \brief [AI] Destination area for the next area transition initiated from this world. [AI]
	LegoGameState::Area m_destLocation; // 0xf8

	/// \brief [AI] Handles user control notifications, such as clicking the elevator arrows or buttons, causing transitions or updating Act1State as appropriate. [AI]
	/// \param p_param [AI] Control notification parameter, typically including clicked control/button identifiers.
	/// \return [AI] 1 if a transition/action was taken, 0 otherwise.
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);
};

#endif // ELEVATORBOTTOM_H
