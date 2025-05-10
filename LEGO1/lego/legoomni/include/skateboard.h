#ifndef SKATEBOARD_H
#define SKATEBOARD_H

#include "decomp.h"
#include "islepathactor.h"

class Act1State;

/// \brief [AI] Represents the skateboard vehicle actor used in the minigame and cutscenes. Inherits path follow and interactive capabilities from IslePathActor. [AI]
/// \details [AI] The SkateBoard class manages the in-game skateboard, particularly its interactions, scene presentation (like pizza delivery bits), and state management specific to the skateboard sequence. Handles click events, notification responses, scene transitions, and pizza visibility logic. Also maintains information about Act1State for integration with story sequences. [AI]
// VTABLE: LEGO1 0x100d55f0
// VTABLE: BETA10 0x101bfc70
// SIZE 0x168
class SkateBoard : public IslePathActor {
public:
	/// \brief [AI] Constructs the SkateBoard actor and registers it for notifications. [AI]
	SkateBoard();

	/// \brief [AI] Destructor that performs de-registration from control/notification managers. [AI]
	~SkateBoard() override;

	/// \brief [AI] Returns the class name "SkateBoard" for runtime type checks. [AI]
	/// \return Pointer to "SkateBoard" string literal. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f041c
		return "SkateBoard";
	}

	/// \brief [AI] Checks if this instance is of type "SkateBoard" or a base type. [AI]
	/// \param p_name Type name to check against. [AI]
	/// \return True if name matches this class or any base class, false otherwise. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, SkateBoard::ClassName()) || IslePathActor::IsA(p_name);
	}

	/// \brief [AI] Initializes the SkateBoard from a DSAction (e.g., script sequence start). [AI]
	/// \param p_dsAction Action object describing creation parameters/sequence. [AI]
	/// \details [AI] On success, links the actor to its world, registers itself, and links to Pizza scene if present. [AI]
	MxResult Create(MxDSAction& p_dsAction) override;                            // vtable+0x18

	/// \brief [AI] Handles player click events on the SkateBoard. [AI]
	/// \details [AI] Processes input to enter and start the skateboard minigame, plays transitions, and updates the controlling actor if necessary. [AI]
	MxLong HandleClick() override;                                               // vtable+0xcc

	/// \brief [AI] Responds to a generic notification. [AI]
	/// \details [AI] Used to (re-)enable the scene's pizza presentation when needed, usually after some external change. [AI]
	MxLong HandleNotification0() override;                                       // vtable+0xd0

	/// \brief [AI] Handles controller input or notification events directed at the SkateBoard (e.g., button presses on overlays). [AI]
	/// \param p_param Control notification/command parameter. [AI]
	/// \details [AI] Handles input for exiting from certain skate scene control overlays. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override; // vtable+0xd4

	/// \brief [AI] Exits the skateboard sequence, unregisters itself, and resets related scene state. [AI]
	/// \details [AI] Also stops pizza actions and removes various UI and control overlays. [AI]
	void Exit() override;                                                        // vtable+0xe4

	/// \brief [AI] Sets whether the pizza bitmap/scene is visible in the skateboard minigame. [AI]
	/// \param p_pizzaVisible True to show pizza, false to hide. [AI]
	void SetPizzaVisible(MxBool p_pizzaVisible) { m_pizzaVisible = p_pizzaVisible; }

	/// \brief [AI] Activates the skateboard scene-specific scripted actions, including animations and music. [AI]
	/// \details [AI] Triggers unique skateboarding entrance/run behaviors if not already performed in this state. [AI]
	void ActivateSceneActions();

	/// \brief [AI] Enables or disables the presentation (visual display) of pizza in the skateboard scene. [AI]
	/// \param p_enable Set to true to show, false to hide pizza and related overlays. [AI]
	/// \details [AI] If appropriate scene objects exist, enables/disables their display; if not, sends a notification for fallback logic. [AI]
	void EnableScenePresentation(MxBool p_enable);

	// SYNTHETIC: LEGO1 0x1000ff60
	// SkateBoard::`scalar deleting destructor'

private:
	MxBool m_pizzaVisible;  ///< [AI] Whether the pizza scene/bitmap is currently visible in the skate sequence UI. [AI]
	Act1State* m_act1state; ///< [AI] Pointer to current story (Act1) state, enabling context-sensitive logic for special sequences (like pizza delivery cutscene). [AI]
};

#endif // SKATEBOARD_H
