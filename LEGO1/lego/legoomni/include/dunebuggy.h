#ifndef DUNEBUGGY_H
#define DUNEBUGGY_H

#include "decomp.h"
#include "islepathactor.h"

// VTABLE: LEGO1 0x100d8f98
// VTABLE: BETA10 0x101b95c0
// SIZE 0x16c

/**
 * @class DuneBuggy
 * @brief [AI] Represents the player-controllable dune buggy vehicle in LEGO Island, inheriting movement and interaction logic from IslePathActor. Handles its own fuel management, dashboard state, click/control/path logic, and specific in-game actions such as refueling and entering/exiting the vehicle. 
 * @details [AI] This class manages the life cycle, animation, and event handling of the dune buggy within the game. It manages a specific dashboard interface, monitors fuel consumption, and updates related script variables for display and gameplay logic. It provides specialized responses for in-game events that pertain to the vehicle, such as refueling when at a certain path marker, modifying the UI via dashboard controls, handling interactions for special parts of the dashboard, and activating cutscenes or transitions related to the dune buggy scenario. 
 */
class DuneBuggy : public IslePathActor {
public:
	/**
	 * @brief [AI] Constructor. Initializes the dune buggy with default velocity and fuel.
	 */
	DuneBuggy();

	/**
	 * @brief [AI] Returns the class name string for run-time type identification. Overrides IslePathActor.
	 * @return [AI] "DuneBuggy"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0410
		return "DuneBuggy";
	}

	/**
	 * @brief [AI] Checks if the object matches the provided class name or any of its ancestor types.
	 * @param p_name Class name string to check. [AI]
	 * @retval TRUE if type matches or inherits the queried type [AI]
	 * @retval FALSE otherwise [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, DuneBuggy::ClassName()) || IslePathActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates and initializes the dune buggy from a MxDSAction, also placing it into the current world and initializing script variables for the vehicle's state and fuel.
	 * @param p_dsAction The script action that defines the initialization parameters and context. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Advances the animation and updates state variables for the dune buggy, including updating the speed and fuel variable tables used for display and logic.
	 * @param p_time The new time (game time or animation time) used to update state. [AI]
	 */
	void Animate(float p_time) override;

	/**
	 * @brief [AI] Handles player click interactions on the dune buggy. Initiates the entry transition, dash setup, and registers the actor for input handling.
	 * @return 1 if click was handled, otherwise different for failure. [AI]
	 */
	MxLong HandleClick() override;

	/**
	 * @brief [AI] Handles control manager notifications (e.g., dashboard button presses) while the dune buggy is active. Can trigger exit, open the info screen, or play the horn sound.
	 * @param p_param Notification details about the control event. [AI]
	 * @return 1 if a handled event occurred (exit, info, etc.), 0 otherwise. [AI]
	 */
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;

	/**
	 * @brief [AI] Handles notifications if the dune buggy actor reaches a certain location/path segment (e.g., the gas station). Used for specialized event triggers, such as auto-refueling the buggy.
	 * @param p_param Struct containing information about the path/trigger reached. [AI]
	 * @return Always returns 0 for this implementation. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;

	/**
	 * @brief [AI] Exits the dune buggy scenario, cleaning up the HUD, unregistering dashboard elements, and updating the game state. [AI]
	 */
	void Exit() override;

	/**
	 * @brief [AI] Triggers cutscene/cinematic actions associated with the garage/dune buggy scenario ("scene actions") and ensures cutscenes only play once. [AI]
	 * @details [AI] Plays the Garage music, checks and sets cutscene state, and spawns cutscene actors/animations positioned relative to the user actor.
	 */
	void ActivateSceneActions();

	/**
	 * @brief [AI] Determines the color offset index for the dune buggy dashboard based on a variable. Used for selecting the correct dashboard resource/asset.
	 * @param p_variable Name of variable storing selected color (string like "lego green", "lego red", etc). [AI]
	 * @details [AI] Looks up the color string in the variable table and returns a numeric offset (1-6) matching the color's slot.
	 * @return The integer offset corresponding to the color value. [AI]
	 */
	static MxS32 GetColorOffset(const char* p_variable);

	// SYNTHETIC: LEGO1 0x10067dc0
	// DuneBuggy::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Stores the dashboard HUD object index for the dune buggy area. Used for removal/activation of UI elements. [AI]
	 */
	MxS16 m_dashboard; // 0x160

	/**
	 * @brief [AI] The current fuel level of the dune buggy (0.0 to 1.0, float). Updated regularly and displayed in HUD. [AI]
	 */
	MxFloat m_fuel;    // 0x164

	/**
	 * @brief [AI] The last time (simulation/game time) the fuel and animation state were updated, used to compute elapsed time and adjust consumption. [AI]
	 */
	MxFloat m_time;    // 0x168
};

#endif // DUNEBUGGY_H
