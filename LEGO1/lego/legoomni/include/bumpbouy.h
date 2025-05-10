#ifndef BUMPBOUY_H
#define BUMPBOUY_H

#include "legoanimactor.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d6790 LegoPathActor
// VTABLE: LEGO1 0x100d6860 LegoAnimActor
// VTABLE: BETA10 0x101b9430 LegoPathActor
// VTABLE: BETA10 0x101b9520 LegoAnimActor
// SIZE 0x174

/**
 * @brief [AI] Represents a bumpable buoy in the world that handles user interactions, specifically the Jetski click event in LEGO Island's race sequence.
 * @details [AI] This actor subclass handles notifications for events targeting the bump buoy; if a Jetski actor collides or "clicks" the buoy, it triggers the 3D rendering to pause, stops the Jetski, advances the game state, and initiates a transition to the Jet Race sequence. The buoy is registered for notifications via the notification manager on creation, and unregistered on destruction.
 */
class BumpBouy : public LegoAnimActor {
public:
	/**
	 * @brief [AI] Constructs a BumpBouy and registers it with the notification manager to receive in-game notifications.
	 */
	BumpBouy();

	/**
	 * @brief [AI] Destructor unregisters the BumpBouy from the notification manager.
	 */
	~BumpBouy() override;

	/**
	 * @brief [AI] Handles notifications sent to this BumpBouy instance.
	 * @details [AI] Processes a click notification from a Jetski actor. This triggers the transition from open-world driving to the jet race: it disables 3D rendering, stops the Jetski's movement, calls its exit method, updates Act1 game state, sets the world destination to the Jet Race, and starts a mosaic transition effect.
	 * @param p_param The generic event or notification parameter, expected to be an MxNotificationParam for handling notification details. [AI]
	 * @return 1 if the user was a Jetski and the notification was a click; otherwise, 0. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns the class name for run-time type identification.
	 * @return Pointer to a static string literal: "BumpBouy". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0394
		return "BumpBouy";
	}

	/**
	 * @brief [AI] Checks for run-time type identification.
	 * @details [AI] Returns true if the type matches "BumpBouy" or any of its base types via LegoAnimActor::IsA.
	 * @param p_name String name of the type to check against this instance. [AI]
	 * @return Whether p_name matches this class or a superclass. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, BumpBouy::ClassName()) || LegoAnimActor::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x100274a0
	// BumpBouy::`scalar deleting destructor'
};

/**
 * @brief [AI] Global variable for BumpBouy vbtable to support multiple inheritance and dynamic casting. [AI]
 */
// GLOBAL: LEGO1 0x100d6788
// BumpBouy::`vbtable'

#endif // BUMPBOUY_H