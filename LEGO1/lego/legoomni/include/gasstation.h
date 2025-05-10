#ifndef GASSTATION_H
#define GASSTATION_H

#include "decomp.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "radio.h"

class MxStillPresenter;

/// \class GasStationState
/// \brief Maintains persistent, serializable state information for the gas station/garage area, including actor animation choice tracking [AI].
/// \details GasStationState extends LegoState to provide save/load support and persistent run state for the game's garage (gas station) world. It tracks action progressions for each main actor character and manages which scripted GarageScript actions are currently running (typically for animations and triggered logic) [AI].
// VTABLE: LEGO1 0x100d46e0
// VTABLE: BETA10 0x101b9818
// SIZE 0x24
class GasStationState : public LegoState {
public:
	/// \brief [AI] Creates and resets state for gas station, initializing all actor counters and action lists.
	GasStationState();

	/// \brief Returns the class name string used for RTTI and IsA queries [AI].
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0174
		return "GasStationState";
	}

	/// \brief Checks if this object is or inherits from a specified class [AI].
	/// \param p_name the class name to query [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, GasStationState::ClassName()) || LegoState::IsA(p_name);
	}

	/// \brief Serializes/deserializes the gas station state from the given storage [AI].
	/// \details Writes and reads persistent per-character action indices (last completed variation) for animation progression. [AI]
	/// \param p_storage The storage stream for persistent state [AI]
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	// SYNTHETIC: LEGO1 0x10006290
	// GasStationState::`scalar deleting destructor'

	/// \brief Records a running GarageScript action as currently active in this state [AI].
	/// \param p_objectId The GarageScript action being started [AI]
	void PlayAction(GarageScript::Script p_objectId);

	/// \brief Removes the specified GarageScript action from the active set as no longer running [AI].
	/// \param p_objectId Script whose running status is to be cleared [AI]
	void StopAction(GarageScript::Script p_objectId);

	/// \brief [AI] Stops all running actions tracked in this state and raises background audio volume.
	void StopActions();

	// TODO: Most likely getters/setters are not used according to BETA.

	GarageScript::Script m_actions[3]; ///< List of up to 3 currently running GarageScript actions [AI]
	undefined4 m_unk0x14;              ///< [AI_SUGGESTED_NAME: m_actionState] Tracks the phase in scripted action sequence for state machine control [AI]
	MxS16 m_pepperAction;              ///< Current animation/action index for Pepper actor (cycles variants) [AI]
	MxS16 m_mamaAction;                ///< Current animation/action index for Mama actor [AI]
	MxS16 m_papaAction;                ///< Current animation/action index for Papa actor [AI]
	MxS16 m_nickAction;                ///< Current animation/action index for Nick actor [AI]
	MxS16 m_lauraAction;               ///< Current animation/action index for Laura actor [AI]
};

/// \class GasStation
/// \brief The in-game gas station (garage) area/world logic controller, handling all interactive gameplay, state transitions, and actors [AI].
/// \details Controls the lifecycle (create/play/stop/escape/enable/tick) as well as interactive triggers, input routing, background music, triggered scripts and persistence for the garage/gas station 3D world [AI].
// VTABLE: LEGO1 0x100d4650
// VTABLE: BETA10 0x101b97a0
// SIZE 0x128
class GasStation : public LegoWorld {
public:
	/// \brief [AI] Constructs and initializes the gas station world logic.
	GasStation();
	/// \brief [AI] Destroys gas station logic and unregisters this world from input, control and tick managers, cleaning up resources.
	~GasStation() override; // vtable+0x00

	/// \brief [AI] Responds to engine/system notifications (actions, keypress, etc).
	/// \param p_param The notification parameter, to be handled according to type [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Called every frame to update the garage world state for timers and LED animation.
	MxResult Tickle() override;               // vtable+0x08

	/// \brief [AI] Returns TRUE; identifies this world as a "special" interactable world.
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// \brief [AI] Returns class name for RTTI/IsA queries.
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0168
		return "GasStation";
	}
	/// \brief [AI] IsA-style RTTI: checks if object is of a particular class.
	/// \param p_name Name to query against. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, GasStation::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// \brief [AI] Creates and activates the gas station world, setting up input/control managers and persistent state [AI].
	/// \param p_dsAction Data describing the action/scene to initialize [AI]
	MxResult Create(MxDSAction& p_dsAction) override;                           // vtable+0x18

	/// \brief [AI] Initializes world assets, actors, and interactive scripts according to saved state/current actor [AI].
	void ReadyWorld() override;                                                 // vtable+0x50

	/// \brief [AI] Cleans up and transitions out of the gas station on user escape [AI].
	MxBool Escape() override;                                                   // vtable+0x64

	/// \brief [AI] Enables or disables this world (switches input/camera registration, etc) [AI].
	/// \param p_enable Whether to enable the gas station world [AI]
	void Enable(MxBool p_enable) override;                                      // vtable+0x68

	/// \brief [AI] Handles direct control manager notifications (UI interaction, navigation, etc).
	/// \param p_param Parameters describing the UI/control event [AI]
	virtual MxLong HandleControl(LegoControlManagerNotificationParam& p_param); // vtable+0x6c

	// SYNTHETIC: LEGO1 0x100048a0
	// GasStation::`scalar deleting destructor'

private:
	/// \brief [AI] Triggers the GarageScript action as an in-world animation/event and notifies persistent state [AI].
	/// \param p_objectId GarageScript action object ID to trigger [AI]
	inline void PlayAction(GarageScript::Script p_objectId);

	/// \brief [AI] Issues stop command for GarageScript action, restores audio volume, and notifies persistent state [AI].
	/// \param p_objectId GarageScript action ID to stop [AI]
	inline void StopAction(GarageScript::Script p_objectId);

	/// \brief [AI] Handles end-of-action notifications (animation completion etc), drives state machines for animation progress [AI].
	/// \param p_param End action notification param [AI]
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/// \brief [AI] Handles keyboard presses for garage world, allowing users to interrupt animations or skip [AI].
	/// \param p_key The key pressed [AI]
	MxLong HandleKeyPress(MxS8 p_key);

	/// \brief [AI] Processes mouse button-down events on interactive world ROIs, enabling triggers based on their names [AI].
	/// \param p_param The parameter containing UI click info [AI]
	MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param);

	MxS16 m_currentActorId;             ///< The ID (Pepper, Mama, etc) of current player actor in this world [AI]
	undefined2 m_unk0xfa;               ///< [AI_SUGGESTED_NAME: m_reserved1] Unidentified/unused state data [AI]
	LegoGameState::Area m_destLocation; ///< Next destination/world to load after this (by area enum) [AI]
	GasStationState* m_state;           ///< Pointer to persistent/serializable state object for gas station [AI]
	undefined2 m_unk0x104;              ///< [AI_SUGGESTED_NAME: m_actionProgress] Used to track progression in story sequence/animation [AI]
	undefined2 m_unk0x106;              ///< [AI_SUGGESTED_NAME: m_animationStatus] Used as flag for action-in-progress or animation phase [AI]
	MxStillPresenter* m_trackLedBitmap; ///< Presenter for the animated "track LED" indicator in the UI [AI]
	MxLong m_unk0x10c;                  ///< [AI_SUGGESTED_NAME: m_lastActionTimestamp] Used for timing (e.g., inactivity timer for UI or script) [AI]
	MxLong m_trackLedTimer;             ///< Timer for toggling the track LED indicator in UI [AI]
	MxBool m_unk0x114;                  ///< [AI_SUGGESTED_NAME: m_ledTimerActive] If TRUE, periodically updates/toggles LED [AI]
	MxBool m_unk0x115;                  ///< [AI_SUGGESTED_NAME: m_ledBlinking] If TRUE, flashes the track LED indicator [AI]
	Radio m_radio;                      ///< Handles in-world radio/music scripting and notifications [AI]
};

#endif // GASSTATION_H
