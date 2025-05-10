#ifndef AMBULANCE_H
#define AMBULANCE_H

#include "islepathactor.h"
#include "legostate.h"

class MxEndActionNotificationParam;

/// \class AmbulanceMissionState
/// \brief Holds state and scoring information for the Ambulance mission. [AI]
/// \details [AI] Keeps track of per-actor scores and high scores for the Ambulance gameplay mission, as well as timing and progress flags for mission flow control. The scores are stored per major character ("Pepper", "Mama", "Papa", "Nick", "Laura"). Offers score persistence by serializing to/from storage. [AI]
class AmbulanceMissionState : public LegoState {
public:
	/// \brief [AI] Default constructor; initializes all scores, high scores, time and internal state to zero. [AI]
	AmbulanceMissionState();

	/// \brief [AI] Serializes (loads or saves) the mission state information for the Ambulance mission. [AI]
	/// \details [AI] Serializes the per-character (Pepper/Mama/Papa/Nick/Laura) scores and high scores from or into a given LegoStorage. Ensures player progress and results persist across sessions. Also defers serialization of parent state (LegoState). [AI]
	/// \param p_storage The storage interface to read from or write to. [AI]
	/// \return SUCCESS on successful operation; otherwise error status. [AI]
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c [AI]

	/// \brief [AI] Returns the class name string. [AI]
	/// \details [AI] For runtime type identification. Used by IsA. [AI]
	/// \return Static string: "AmbulanceMissionState". [AI]
	const char* ClassName() const override; // vtable+0x0c [AI]

	/// \brief [AI] Runtime type check for class identity or inheritance. [AI]
	/// \param p_name Class name to test. [AI]
	/// \return Returns MxTrue if this is or inherits from the requested class. [AI]
	MxBool IsA(const char* p_name) const override; // vtable+0x10 [AI]

	/// \brief [AI] Retrieves the highest score achieved by a specified actor. [AI]
	/// \param p_actorId The ID of the actor as defined by LegoActor::c_* enum. [AI]
	/// \return The actor's personal high score for the Ambulance mission. [AI]
	MxS16 GetHighScore(MxU8 p_actorId); // [AI]

	/// \brief [AI] Updates the current and high score for a specific actor, if the new score is higher. [AI]
	/// \param p_score The score to record. [AI]
	/// \param p_actorId The target actor as determined by LegoActor::c_* enum values. [AI]
	void UpdateScore(ScoreColor p_score, MxS16 p_actorId); // [AI]

	/// \brief [AI] Flag/state variable—purpose unclear, likely denotes mission sub-state or phase. [AI_SUGGESTED_NAME: m_progressFlag]
	undefined4 m_unk0x08; // 0x08 [AI]
	/// \brief [AI] Mission timer: records when the mission started (in milliseconds?). [AI]
	MxLong m_startTime;   // 0x0c [AI]

	/// \brief [AI] Last achieved mission score for Pepper. [AI]
	MxS16 m_peScore;      // 0x10 [AI]
	/// \brief [AI] Last achieved mission score for Mama. [AI]
	MxS16 m_maScore;      // 0x12 [AI]
	/// \brief [AI] Last achieved mission score for Papa. [AI]
	MxS16 m_paScore;      // 0x14 [AI]
	/// \brief [AI] Last achieved mission score for Nick. [AI]
	MxS16 m_niScore;      // 0x16 [AI]
	/// \brief [AI] Last achieved mission score for Laura. [AI]
	MxS16 m_laScore;      // 0x18 [AI]

	/// \brief [AI] Highest ever mission score for Pepper. [AI]
	MxS16 m_peHighScore;  // 0x1a [AI]
	/// \brief [AI] Highest ever mission score for Mama. [AI]
	MxS16 m_maHighScore;  // 0x1c [AI]
	/// \brief [AI] Highest ever mission score for Papa. [AI]
	MxS16 m_paHighScore;  // 0x1e [AI]
	/// \brief [AI] Highest ever mission score for Nick. [AI]
	MxS16 m_niHighScore;  // 0x20 [AI]
	/// \brief [AI] Highest ever mission score for Laura. [AI]
	MxS16 m_laHighScore;  // 0x22 [AI]
};


/// \class Ambulance
/// \brief Main game logic and control entity for the Ambulance gameplay activity. [AI]
/// \details [AI] Handles player and world interaction during the Ambulance rescue mini-game mission. Manages actor animations, mission state, controls, UI transitions, scoring, audio, and the player's progress. Inherits from IslePathActor to utilize navigation and path-following support. [AI]
class Ambulance : public IslePathActor {
public:
	/// \brief [AI] Creates and initializes the ambulance actor; sets default velocities and initial mission state. [AI]
	Ambulance();
	/// \brief [AI] Destructor—unregisters the Ambulance from control and tickle managers and performs cleanup. [AI]
	~Ambulance() override;

	/// \brief [AI] Handles notifications from the system (events, actions, button presses, etc.). [AI]
	/// \param p_param The notification parameter describing the event. [AI]
	/// \return Implementation-defined int status (often 1 for consumed events). [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04 [AI]

	/// \brief [AI] Called on each game "tick" to update state, handle random sounds, etc. [AI]
	/// \return SUCCESS on successful tick. [AI]
	MxResult Tickle() override;               // vtable+0x08 [AI]

	/// \brief [AI] Does nothing for Ambulance; stub for virtual destroy. [AI]
	/// \param p_fromDestructor Is this called from destructor? [AI]
	void Destroy(MxBool p_fromDestructor) override {} // vtable+0x1c [AI]

	/// \brief [AI] Returns the class name "Ambulance" for RTTI. [AI]
	const char* ClassName() const override; // vtable+0x0c [AI]

	/// \brief [AI] Checks whether this object is of type "Ambulance" or inherits from a type with the given name. [AI]
	/// \param p_name Type name. [AI]
	/// \return True if matches type or ancestor. [AI]
	MxBool IsA(const char* p_name) const override; // vtable+0x10 [AI]

	/// \brief [AI] Creates this Ambulance object based on the provided DS action (from scripts/etc). [AI]
	/// \param p_dsAction The action that spawns/configures the Ambulance. [AI]
	MxResult Create(MxDSAction& p_dsAction) override;                              // vtable+0x18 [AI]

	/// \brief [AI] Per-frame update for position, fuel, and any animation logic. [AI]
	/// \param p_time The animation frame timestamp or delta time. [AI]
	void Animate(float p_time) override;                                           // vtable+0x70 [AI]

	/// \brief [AI] Handles a "click" on this Ambulance actor (starts mission, triggers transitions, etc.). [AI]
	/// \return Implementation-defined response; typically 1 = handled. [AI]
	MxLong HandleClick() override;                                                 // vtable+0xcc [AI]

	/// \brief [AI] Responds to control (UI/keyboard/joystick) input events. [AI]
	/// \param p_param The detail of control manager input. [AI]
	/// \return Implementation-defined status. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;   // vtable+0xd4 [AI]

	/// \brief [AI] Handles notifications related to path structure triggers such as mission segments or locations. [AI]
	/// \param p_param Notification carrying trigger details, e.g. for start, gas, finish locations. [AI]
	/// \return 0 if not handled, or as otherwise dictated by game logic. [AI]
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;    // vtable+0xdc [AI]

	/// \brief [AI] Exits the mission; triggers cleanup, world removal, and area/state updates. [AI]
	void Exit() override;                                                          // vtable+0xe4 [AI]

	/// \brief [AI] Handles button down events in the mission interface (e.g., gate click). [AI]
	/// \param p_param Button down event details. [AI]
	/// \return 1 if a handled special interaction occurred, else 0. [AI]
	virtual MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param); // vtable+0xf0 [AI]

	/// \brief [AI] Handles end action notifications (e.g., animation completion), progresses mission or triggers feedback. [AI]
	/// \param p_param Notification about an action's end. [AI]
	/// \return Always 1 for handled. [AI]
	virtual MxLong HandleEndAction(MxEndActionNotificationParam& p_param);         // vtable+0xf4 [AI]

	/// \brief [AI] Ensures AmbulanceMissionState is present in the game state manager; creates if missing. [AI]
	void CreateState(); // [AI]

	/// \brief [AI] Marks mission as failed/successful, triggers cutscene/animation for mission outcome. [AI_SUGGESTED_NAME: SetMissionOutcomeAnimation]
	void FUN_10036e60(); // [AI]

	/// \brief [AI] Handles the enabling of in-game ambient/scene actions when player enters the hospital scene. [AI]
	void ActivateSceneActions(); // [AI]

	/// \brief [AI] Stops currently running scripted actions/animations associated with the Ambulance mission. [AI]
	void StopActions(); // [AI]

	/// \brief [AI] Resets game- and mission-related state after the mission; restores music, resets state objects, etc. [AI_SUGGESTED_NAME: ResetAfterMission]
	void FUN_10037250(); // [AI]

private:
	/// \brief [AI] Plays an animation by script ID; sets as current last animation. [AI]
	/// \param p_objectId Script/animation object ID to play. [AI]
	void PlayAnimation(IsleScript::Script p_objectId); // [AI]

	/// \brief [AI] Plays an animation marking mission completion (final cutscene). [AI]
	/// \param p_objectId The finishing animation's script ID. [AI]
	void PlayFinalAnimation(IsleScript::Script p_objectId); // [AI]

	/// \brief [AI] Immediately stops the specified scripted action. [AI]
	/// \param p_objectId The script action to stop. [AI]
	void StopAction(IsleScript::Script p_objectId); // [AI]

	/// \brief [AI] Plays a scripted action, and records it as the last action. Audio volume is reduced during playback. [AI]
	/// \param p_objectId The action to run. [AI]
	void PlayAction(IsleScript::Script p_objectId); // [AI]

	/// \brief [AI] Removes this object from active world, resets visibility, unregisters input and tickle handlers, and cleans mission UI elements. [AI]
	void Leave(); // [AI]

	/// \brief [AI] Padding or unknown data, used internally. [AI]
	undefined m_unk0x160[4];            // 0x160 [AI]
	/// \brief [AI] Pointer to AmbulanceMissionState associated with this mission run. [AI]
	AmbulanceMissionState* m_state;     // 0x164 [AI]
	/// \brief [AI] Unknown mission/path state flag; used in phase and state transitions (e.g., path-to-gas location). [AI_SUGGESTED_NAME: m_gasStationPathFlag]
	MxS16 m_unk0x168;                   // 0x168 [AI]
	/// \brief [AI] The ID of the actor currently playing the ambulance mission. [AI]
	MxS16 m_actorId;                    // 0x16a [AI]
	/// \brief [AI] Unknown mission/path state flag; used for tracking if a specific part of the mission has started. [AI_SUGGESTED_NAME: m_pathStartFlag]
	MxS16 m_unk0x16c;                   // 0x16c [AI]
	/// \brief [AI] Unknown phase/state flag; controls mission logic branching for result handling. [AI]
	MxS16 m_unk0x16e;                   // 0x16e [AI]
	/// \brief [AI] Counter/flag controlling logic for multi-phase script progression. [AI]
	MxS16 m_unk0x170;                   // 0x170 [AI]
	/// \brief [AI] General-purpose temporary flag, reused for initial tick and input handling gating. [AI]
	MxS16 m_unk0x172;                   // 0x172 [AI]
	/// \brief [AI] The script object id of the last played scene-related action. [AI]
	IsleScript::Script m_lastAction;    // 0x174 [AI]
	/// \brief [AI] The script object id of the last played animation, used to track animation completion. [AI]
	IsleScript::Script m_lastAnimation; // 0x178 [AI]
	/// \brief [AI] Fuel meter value (1.0 = full, 0.0 = empty), decrementing as time passes. [AI]
	MxFloat m_fuel;                     // 0x17c [AI]
	/// \brief [AI] Tracks elapsed time for animations, fuel usage, mission scoring, and timers. [AI]
	MxFloat m_time;                     // 0x180 [AI]
};

#endif // AMBULANCE_H
