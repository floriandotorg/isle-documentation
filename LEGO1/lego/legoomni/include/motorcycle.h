#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "decomp.h"
#include "islepathactor.h"

// VTABLE: LEGO1 0x100d7090
// VTABLE: BETA10 0x101bf3d8
// SIZE 0x16c

/**
 * @brief Motocycle is an IslePathActor representing the motorcycle vehicle the user can drive in LEGO Island. [AI]
 * @details [AI] The Motocycle class allows the player to control the motorcycle within the game. It manages the interactive dashboard, fuel system, player transitions for entering/exiting, handles dashboard control interactions and supports scene activation logic specific to the motorcycle. It tracks the vehicle's current fuel, last update time, and notifies scene and world state changes as the player enters or leaves the motorcycle mode. [AI]
 */
class Motocycle : public IslePathActor {
public:
	/**
	 * @brief [AI] Creates a Motocycle actor with initial default physics and fuel.
	 * @details [AI] Sets up the base navigation parameters (max speed, acceleration, etc.) and initializes fuel to full (1.0). [AI]
	 */
	Motocycle();

	/**
	 * @brief [AI] Returns the class name string ("Motorcycle"). [AI]
	 * @details [AI] Used for run-time type checks/casting in the LEGO1 engine class system. [AI]
	 * @return Class name string constant for this class ("Motorcycle"). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f38e8
		return "Motorcycle";
	}

	/**
	 * @brief [AI] Checks if this object is of the given class type name or any parent class. [AI]
	 * @param p_name Class name to test (case-sensitive). [AI]
	 * @details [AI] Returns true if `p_name` is "Motorcycle" or any base class of Motocycle. [AI]
	 * @return Whether the type name matches this class or a parent. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Motocycle::ClassName()) || IslePathActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates and registers the Motocycle in the game world from a DS action. [AI]
	 * @param p_dsAction SI/DS action info parsed from script. [AI]
	 * @details [AI] Calls IslePathActor::Create, registers the motobike in the game world, and sets up its variables for fuel and timer reset. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Updates animation state and Motocycle-specific logic, including fuel and dashboard variables. [AI]
	 * @param p_time Updated time for the animation tick. [AI]
	 * @details [AI] Updates underlying animation, updates on-screen speed/fuel variables if the motorcycle is user-controlled, and decreases fuel over time. [AI]
	 */
	void Animate(float p_time) override;

	/**
	 * @brief [AI] Handles the event when the user clicks to enter/use the motorcycle. [AI]
	 * @details [AI] Starts the dashboard/actor transition, triggers transition and actor handoff, hands control to the Motocycle, resets its time base, and registers dashboard controls. [AI]
	 * @return Always returns 1 on handled click. [AI]
	 */
	MxLong HandleClick() override;

	/**
	 * @brief [AI] Handles dashboard or control area UI interactions for the motorcycle. [AI]
	 * @param p_param Control notification parameter object (which object was clicked). [AI]
	 * @details [AI] Handles exit (arms), info button actions, and triggers corresponding transitions and scene changes.
	 * @return 1 if handled, 0 if ignored. [AI]
	 */
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;

	/**
	 * @brief [AI] Handles notifications for special-path contact, e.g. refueling at the gas station. [AI]
	 * @param p_param Path structure notification parameter. [AI]
	 * @details [AI] If the Motocycle is driven onto the gas station path, refuels to full. [AI]
	 * @return Always 0. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override;

	/**
	 * @brief [AI] Handles exit and cleanup from Motocycle mode, including dashboard and HUD. [AI]
	 * @details [AI] Unregisters HUD/dashboard controls, sets area in game state, and removes motobike controls from world/hud. [AI]
	 */
	void Exit() override;

	/**
	 * @brief [AI] Triggers in-game events when scene actions should execute after transition into Motocycle. [AI]
	 * @details [AI] Plays relevant music, triggers unique one-time animations, and ensures contextual actions for Act 1 are marked as done (e.g. NPC animations). [AI]
	 */
	void ActivateSceneActions();

	// SYNTHETIC: LEGO1 0x100359d0
	// Motocycle::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Unknown 4 bytes; usage not reverse engineered yet. [AI]
	 * @details [AI] Placeholder for possible Motocycle state or padding. [AI]
	 */
	undefined m_unk0x160[4]; // 0x160

	/**
	 * @brief [AI] Remaining fuel in the motorcycle. Range: 0.0 (empty) to 1.0 (full). [AI]
	 * @details [AI] Decreases automatically while driving, replenished at specific locations/events. Synced with UI variable. [AI]
	 */
	MxFloat m_fuel;          // 0x164

	/**
	 * @brief [AI] Last in-game time when events for the motorcycle were processed. [AI]
	 * @details [AI] Used for accurate time-based updates of fuel and dashboard state. [AI]
	 */
	MxFloat m_time;          // 0x168
};

#endif // MOTORCYCLE_H
