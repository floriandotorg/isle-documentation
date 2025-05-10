#ifndef BIKE_H
#define BIKE_H

#include "decomp.h"
#include "islepathactor.h"

// VTABLE: LEGO1 0x100d9808
// VTABLE: BETA10 0x101b91e8
// SIZE 0x164

/**
 * @brief [AI] Represents the player's bicycle vehicle in LEGO Island, allowing for in-world interactions such as riding, honking the horn, and displaying dashboard UI. 
 * @details [AI] The Bike class is a specialized IslePathActor for the "bike" playable actor. It handles all logic for interacting with the bike, state transitions (such as entering/exiting the bike area), user input and click handling, initialization into the world scene, and communication with the scene's control manager. [AI]
 */
class Bike : public IslePathActor {
public:
	/**
	 * @brief [AI] Default constructor. Initializes bike-specific speed/velocity parameters inherited from IslePathActor.
	 */
	Bike();

	/**
	 * @brief [AI] Returns the class name for this object. Used for runtime type identification. [AI]
	 * @return Pointer to a string "Bike". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03d0
		return "Bike";
	}

	/**
	 * @brief [AI] Checks for runtime type identification against the provided class name. [AI]
	 * @param p_name Name of class to check against. [AI]
	 * @return TRUE if p_name matches "Bike" or a supertype, FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Bike::ClassName()) || IslePathActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles initialization and placement of the bike into the world. Also adds itself to the current world if applicable.
	 * @param p_dsAction SI action object with instantiation details. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Handles response when the bike actor is clicked (e.g. player attempts to ride the bike). Initiates transition into Bike area and triggers dashboard overlay/UI. [AI]
	 * @return 1 if successful, 0 or other value otherwise. [AI]
	 */
	MxLong HandleClick() override;

	/**
	 * @brief [AI] Responds to control events from the LegoControlManager related to the Bike, such as horn, dashboard, or info controls. [AI]
	 * @param p_param Notification object indicating the specific control event. [AI]
	 * @return Nonzero if input was handled.
	 */
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;

	/**
	 * @brief [AI] Cleans up and removes the bike actor from the world and updates the global game state to indicate the player has exited the bike. Also deregisters control handlers and dashboard overlays.
	 */
	void Exit() override;

	/**
	 * @brief [AI] Triggers the bike's area-specific actions, such as playing background music and starting scripted animations. Called when entering the bike area. [AI]
	 */
	void ActivateSceneActions();

	// SYNTHETIC: LEGO1 0x10076880
	// Bike::`scalar deleting destructor'

private:
	// TODO: Bike fields
	/**
	 * @brief [AI] Unknown Bike-related data fields at offset 0x160. Purpose currently undetermined.
	 *
	 * [AI_SUGGESTED_NAME: m_unkBikeData]
	 */
	undefined m_unk0x160[4];
};

#endif // BIKE_H