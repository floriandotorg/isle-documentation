#ifndef TOWTRACK_H
#define TOWTRACK_H

#include "decomp.h"
#include "islepathactor.h"
#include "legostate.h"

class MxEndActionNotificationParam;

// VTABLE: LEGO1 0x100d7fd8
// VTABLE: BETA10 0x101bfee0
// SIZE 0x28
/**
 * @brief [AI] State class for the TowTrack mini-game, storing scores by character and handling their serialization.
 * @details [AI] The TowTrackMissionState class stores both the current scores and high scores for each actor in the Tow Track mini-game. It is responsible for serialization/deserialization of these values for save/load functionality. It provides update and retrieval methods for handling actor-specific scores, and inherits from LegoState.
 */
class TowTrackMissionState : public LegoState {
public:
	/**
	 * @brief [AI] Constructs and initializes all score and state values for the Tow Track mini-game.
	 */
	TowTrackMissionState();

	/**
	 * @brief [AI] Serializes or deserializes the mission state, including per-actor scores and highscores, to/from LegoStorage.
	 * @param p_storage [AI] The storage object used for reading or writing the state.
	 * @return SUCCESS on success. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	/**
	 * @brief [AI] Returns the class name for RTTI/dispatch.
	 * @return "TowTrackMissionState" [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if this instance is of the provided name or derives from a parent with that name.
	 * @param p_name [AI] The name to check against.
	 * @return True if name matches this class or parent class. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Retrieves the highscore for a given actor in the Tow Track mini-game.
	 * @param p_actorId [AI] The identifier for the actor (see LegoActor constant IDs).
	 * @return High score associated with the actor. [AI]
	 */
	MxS16 GetHighScore(MxU8 p_actorId);

	/**
	 * @brief [AI] Updates the score for an actor and also updates the highscore if the new score exceeds the previous highscore.
	 * @param p_score [AI] The new score value.
	 * @param p_actorId [AI] The actor identifier.
	 */
	void UpdateScore(ScoreColor p_score, MxS16 p_actorId);

	// SYNTHETIC: LEGO1 0x1004e060
	// TowTrackMissionState::`scalar deleting destructor'

	undefined4 m_unk0x08;      ///< [AI] Mission substage/step flag for Tow Track, typically takes 0,1,2,3 (purpose per stage flow).
	MxLong m_startTime;        ///< [AI] Start time of the mission attempt, used to track performance.
	MxBool m_unk0x10;          ///< [AI] Flag for one-time event in end-sequence (prevents repeated trigger).
	MxS16 m_peScore;           ///< [AI] Current Pepper score in the mission.
	MxS16 m_maScore;           ///< [AI] Current Mama score in the mission.
	MxS16 m_paScore;           ///< [AI] Current Papa score in the mission.
	MxS16 m_niScore;           ///< [AI] Current Nick score in the mission.
	MxS16 m_laScore;           ///< [AI] Current Laura score in the mission.
	MxS16 m_peHighScore;       ///< [AI] Highscore for Pepper achieved so far in the mission.
	MxS16 m_maHighScore;       ///< [AI] Highscore for Mama achieved so far in the mission.
	MxS16 m_paHighScore;       ///< [AI] Highscore for Papa achieved so far in the mission.
	MxS16 m_niHighScore;       ///< [AI] Highscore for Nick achieved so far in the mission.
	MxS16 m_laHighScore;       ///< [AI] Highscore for Laura achieved so far in the mission.
};

// VTABLE: LEGO1 0x100d7ee0
// VTABLE: BETA10 0x101bfdc0
// SIZE 0x180
/**
 * @brief [AI] 3D world actor for the Tow Track mini-game; manages Tow Track mission logic, scene activation and input events.
 * @details [AI] The TowTrack actor controls the state and interactions of the Tow Track mini-game. It handles user interactions, manages mission state (start/stop, score updates), fuel/time metrics, and deals with both in-game action triggers and UI events tied to the Tow Track context within the world.
 */
class TowTrack : public IslePathActor {
public:
	/**
	 * @brief [AI] Constructs the TowTrack actor and initializes runtime state.
	 */
	TowTrack();
	/**
	 * @brief [AI] Destructor unregisters this TowTrack from control handlers and performs cleanup.
	 */
	~TowTrack() override;

	/**
	 * @brief [AI] Returns the class name for RTTI/dispatch.
	 * @return "TowTrack" [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if this instance is of the provided name or derives from a parent with that name.
	 * @param p_name [AI] The name to check against.
	 * @return True if name matches this class or parent. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Notifies the TowTrack actor of an event. Dispatches per-type handler (end-action, click, control, anim, path).
	 * @param p_param [AI] The event parameter data (must be a MxNotificationParam or derived).
	 * @return An integer code per-event, typically 0 or 1. [AI]
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief [AI] Instantiates or restores this actor in the current world according to DSAction.
	 * @param p_dsAction [AI] DSAction for specifying script/context instantiation.
	 * @return SUCCESS or FAILURE. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Main per-frame update. Performs fuel metering, speed calculation, and triggers late-sequence actions as needed.
	 * @param p_time [AI] Current world or mission time in milliseconds (float).
	 */
	void Animate(float p_time) override;

	/**
	 * @brief [AI] Handles user (mouse) click event on the TowTrack, including state setup and spawning side-effects/UI.
	 * @return Usually returns 1 if click is accepted, otherwise 0. [AI]
	 */
	MxLong HandleClick() override;

	/**
	 * @brief [AI] Handles user input or control notifications (such as UI widget actions) directed at TowTrack.
	 * @param p_param [AI] Notification parameter from the control manager, provides object/event ID and other info.
	 * @return 1 if an action was handled, otherwise 0. [AI]
	 */
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param) override;

	/**
	 * @brief [AI] Called when an animation finishes; used for state progression in the mini-game.
	 * @param p_param [AI] Notification parameter containing animation context.
	 * @return Always returns 1; does not perform additional work. [AI]
	 */
	MxLong HandleEndAnim(LegoEndAnimNotificationParam& p_param) override;

	/**
	 * @brief [AI] Handles path-structure trigger events (e.g., player crossing locations on path networks).
	 * @param p_param [AI] Path notification containing trigger type and location (ID).
	 * @return Nonzero if handled, otherwise 0. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override;

	/**
	 * @brief [AI] Called when the TowTrack mini-game is exited (by player or action/trigger).
	 */
	void Exit() override;

	/**
	 * @brief [AI] Handles end of scripted in-game action (or cutscene) for the TowTrack.
	 * @param p_param [AI] End action notification containing action context.
	 * @return Usually 1 if handled, otherwise 0. [AI]
	 */
	virtual MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/**
	 * @brief [AI] Ensures the TowTrackMissionState exists and is registered in the global state manager.
	 * @details [AI] If state is absent, a new one is created and registered.
	 */
	void CreateState();

	/**
	 * @brief [AI] Begins the Tow Track mission, sets state variable, and triggers click-handling sequence.
	 */
	void FUN_1004dab0();

	/**
	 * @brief [AI] Triggers scene-based scripted actions according to mission state.
	 */
	void ActivateSceneActions();

	/**
	 * @brief [AI] Halts all ongoing Tow Track mini-game actions.
	 */
	void StopActions();

	/**
	 * @brief [AI] Handles cleanup tasks upon mini-game exit, including resetting state variables and unregistering handlers.
	 */
	void FUN_1004dbe0();

	// SYNTHETIC: LEGO1 0x1004c950
	// TowTrack::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Removes TowTrack from the world, disables ROI visibility, and unregisters all UI/control components.
	 */
	void Leave();

	/**
	 * @brief [AI] Plays the final, outcome-dependent animation after Tow Track is won/lost, and records last animation ID.
	 * @param p_objectId [AI] Script object ID for the animation to play.
	 */
	void PlayFinalAnimation(IsleScript::Script p_objectId);

	/**
	 * @brief [AI] Triggers an in-game animation associated with the provided objectScript ID, updates last animation field.
	 * @param p_objectId [AI] Script object ID for the animation to play.
	 */
	void FUN_1004dcb0(IsleScript::Script p_objectId);

	/**
	 * @brief [AI] Triggers an in-game action based on a script (e.g., dialog or start of animation). Stores last action and lowers background volume.
	 * @param p_objectId [AI] Script object ID for the action.
	 */
	void PlayAction(IsleScript::Script p_objectId);

	undefined4 m_unk0x160;              ///< [AI] Unexplored/unused runtime field relating to actor state or sequencing.
	TowTrackMissionState* m_state;      ///< [AI] Pointer to the associated TowTrackMissionState, driving mission storage.
	MxS16 m_unk0x168;                   ///< [AI] Unexplored field, possibly a local step/stage flag.
	MxS16 m_actorId;                    ///< [AI] Current player-controlled actor for the Tow Track mini-game (LegoActor::c_* ID).
	MxS16 m_unk0x16c;                   ///< [AI] Used to prevent repeated invoking of gas station subactions.
	MxS16 m_unk0x16e;                   ///< [AI] Used to prevent repeated invoking of gas station subactions.
	IsleScript::Script m_lastAction;    ///< [AI] Script ID of last triggered action, used for cleanup and state progression.
	IsleScript::Script m_lastAnimation; ///< [AI] Script ID of last played animation, for end-sequence management.
	MxFloat m_fuel;                     ///< [AI] Remaining fuel value [0.0–1.0] tracked for the mission, visually updated.
	MxFloat m_time;                     ///< [AI] Last time value (ms) used for time/fuel tracking in Animate().
};

#endif // TOWTRACK_H
