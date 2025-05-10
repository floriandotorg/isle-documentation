#ifndef JETSKI_H
#define JETSKI_H

#include "decomp.h"
#include "islepathactor.h"

class LegoControlManagerNotificationParam;

/// \class Jetski
/// \brief [AI] Represents the jetski vehicle placed in the 3D world of LEGO Island. Inherits from IslePathActor.
/// \details [AI] The Jetski class is a specialized path actor designed to allow player control over a jetski on water surfaces in-game.
/// It manages creation, animation, click handling, control handling (for UI interactions), and proper removal/cleanup within the game world.
/// It keeps track of dashboard stream IDs for rendering the jetski dashboard overlays based on player's color customization. [AI]
/// 
/// Jetski also interacts with global managers (e.g., VariableTable, AnimationManager), and participates in transitions/scenes with dedicated logic for 
/// handling player actions and world exit. [AI]
///
/// SIZE 0x164 [AI]
class Jetski : public IslePathActor {
public:
	/// \brief [AI] Constructs a Jetski instance, initializing velocity and control parameters.
	Jetski(); // [AI]

	/// \brief [AI] Gets the class name string for runtime type checking and serialization.
	/// \return [AI] The string literal "Jetski".
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03d8
		return "Jetski";
	}

	/// \brief [AI] Checks if this object is of type "Jetski" or a parent class by name.
	/// \param p_name Name to check type against. [AI]
	/// \return [AI] True if this object is considered an instance of the queried type.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Jetski::ClassName()) || IslePathActor::IsA(p_name);
	}

	/// \brief [AI] Creates and initializes the Jetski by adding it to the current world, initializing variables, and delegating core creation to the base IslePathActor.
	/// \param p_dsAction Data structure action for creation (initialization data). [AI]
	/// \return [AI] Result of the base IslePathActor::Create logic.
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// \brief [AI] Updates jetski state for the current animation frame, including world speed, dashboard, and scripting variable updates.
	/// \param p_time Delta time or timestamp for animation update. [AI]
	void Animate(float p_time) override; // vtable+0x70

	/// \brief [AI] Handles when the player clicks or interacts with the jetski. 
	/// Handles logic for transitions, dashboard/overlay selection, player hand-off, and world state/camera changes. [AI]
	/// \return [AI] 1 for handled, other values for ignored/unhandled.
	MxLong HandleClick() override; // vtable+0xcc

	/// \brief [AI] Handles control notifications from the LegoControlManager (e.g., UI element actions, dashboard button presses).
	/// Responds to arms/info control inputs by exiting or triggering transitions/scenes as appropriate. [AI]
	/// \param [AI] p_param Notification with click/control information.
	/// \return [AI] 1 for handled, 0 for ignored/unhandled.
	MxLong HandleControl(LegoControlManagerNotificationParam&) override; // vtable+0xd4
	
	/// \brief [AI] Handles jetski exit logic for the player, including hand-off to other actors, resetting spawns, re-enabling world/animations, and unregistering from the control manager.
	void Exit() override; // vtable+0xe4

	/// \brief [AI] Activates scene-specific scripted actions, such as music or camera animations, relevant when entering the Jetski scene.
	void ActivateSceneActions(); // [AI]

	/// \brief [AI] Gets the current jetski dashboard stream ID, used to select/activate the dashboard/overlay for rendering/animation.
	/// \return [AI] Internal dashboard stream ID, updated when handling clicks.
	MxS16 GetUnknown0x160() { return m_jetskiDashboardStreamId; } // [AI_SUGGESTED_NAME: GetDashboardStreamId] [AI]

	// SYNTHETIC: LEGO1 0x1007e5c0
	// Jetski::`scalar deleting destructor'

private:
	/// \brief [AI] Removes dashboard and related overlays from the current scene/world. Called during jetski exit or deactivation logic.
	void RemoveFromWorld(); // [AI]

	/// \brief [AI] Dashboard stream ID used to display the appropriate overlay for the currently selected jetski color and state.
	/// [AI] Set in HandleClick; used in removal and transitions; correlates with scripting and game asset identifiers.
	MxS16 m_jetskiDashboardStreamId; // 0x160 [AI]
};

#endif // JETSKI_H
