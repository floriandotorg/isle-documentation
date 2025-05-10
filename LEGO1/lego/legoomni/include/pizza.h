#ifndef PIZZA_H
#define PIZZA_H

#include "actionsfwd.h"
#include "decomp.h"
#include "isleactor.h"
#include "legostate.h"

class Act1State;
class PizzeriaState;
class SkateBoard;

// VTABLE: LEGO1 0x100d7408
// VTABLE: BETA10 0x101bf750
// SIZE 0xb4
/**
 * @brief Pizza mission state for the pizza delivery minigame and related characters. [AI]
 * @details PizzaMissionState encapsulates the persistent state for the pizza delivery mission for each character (Pepper, Mama, Papa, Nick, Laura).
 * It stores the mission scripting, finish time thresholds, and score tracking for each actor, as well as state for mission progress and serialization. [AI]
 */
class PizzaMissionState : public LegoState {
public:
	/**
	 * @brief Holds all data for a single pizza mission for a specific actor. [AI]
	 * @details Each Mission contains finish time thresholds, action scripts for standard and finish actions, and current/high score. [AI]
	 */
	// SIZE 0x20
	struct Mission {
		/**
		 * @brief Default mission constructor. [AI]
		 */
		// FUNCTION: LEGO1 0x10039220
		// FUNCTION: BETA10 0x100ef880
		Mission() {}

		/**
		 * @brief Initializes the mission with actor, time thresholds, scripts array, and number of actions. [AI]
		 * @param p_actorId The actor ID (Pepper, Mama, etc.). [AI]
		 * @param p_unk0x04 Unknown purpose. Used by game logic for mission state (typically 2). [AI]
		 * @param p_finishTimes Pointer to array of finish time thresholds for red, blue, yellow, and timeout. [AI]
		 * @param p_actions Pointer to array of scripts used for this mission. [AI]
		 * @param p_numActions Number of standard actions before finish actions. [AI]
		 */
		// FUNCTION: BETA10 0x100ef8a0
		Mission(
			MxU8 p_actorId,
			undefined2 p_unk0x04,
			MxLong* p_finishTimes,
			IsleScript::Script* p_actions,
			MxS16 p_numActions
		)
		{
			m_numActions = p_numActions;
			m_actorId = p_actorId;
			m_unk0x04 = p_unk0x04;
			m_unk0x06 = 1;
			m_unk0x08 = 1;
			m_finishTimes = p_finishTimes;
			m_startTime = INT_MIN;
			m_unk0x14 = 1;
			m_score = LegoState::e_grey;
			m_hiScore = LegoState::e_grey;
			m_actions = p_actions;
		}

		/**
		 * @brief Assignment operator for copying all mission data. [AI]
		 * @param p_mission The mission to copy from. [AI]
		 * @return Reference to this. [AI]
		 */
		// FUNCTION: LEGO1 0x10039230
		Mission& operator=(const Mission& p_mission)
		{
			m_actorId = p_mission.m_actorId;
			m_unk0x04 = p_mission.m_unk0x04;
			m_unk0x06 = p_mission.m_unk0x06;
			m_unk0x08 = p_mission.m_unk0x08;
			m_finishTimes = p_mission.m_finishTimes;
			m_startTime = p_mission.m_startTime;
			m_unk0x14 = p_mission.m_unk0x14;
			m_score = p_mission.m_score;
			m_hiScore = p_mission.m_hiScore;
			m_actions = p_mission.m_actions;
			m_numActions = p_mission.m_numActions;
			return *this;
		}

		/**
		 * @brief Gets the script for the "red" (best time) mission finish. [AI]
		 * @details Returns the script after m_numActions+6 in the array. [AI]
		 */
		// FUNCTION: BETA10 0x100ef610
		IsleScript::Script GetRedFinishAction() { return m_actions[m_numActions + 6]; }

		/**
		 * @brief Gets the script for the "blue" (medium time) mission finish. [AI]
		 * @details Returns the script after m_numActions+7 in the array. [AI]
		 */
		// FUNCTION: BETA10 0x100ef640
		IsleScript::Script GetBlueFinishAction() { return m_actions[m_numActions + 7]; }

		/**
		 * @brief Gets the script for the "yellow" (slowest success) finish. [AI]
		 * @details Returns script at offset m_numActions+8. [AI]
		 */
		// FUNCTION: BETA10 0x100ef670
		IsleScript::Script GetYellowFinishAction() { return m_actions[m_numActions + 8]; }

		/**
		 * @brief Gets the maximum allowed time for a "red" (perfect) finish. [AI]
		 */
		// FUNCTION: BETA10 0x100ef6a0
		MxLong GetRedFinishTime() { return m_finishTimes[0]; }

		/**
		 * @brief Gets the maximum allowed time for a "blue" finish. [AI]
		 */
		// FUNCTION: BETA10 0x100ef6d0
		MxLong GetBlueFinishTime() { return m_finishTimes[1]; }

		/**
		 * @brief Updates both current and high score with the supplied new score color, raising high score if necessary. [AI]
		 * @param p_score New score to set. [AI]
		 */
		// FUNCTION: BETA10 0x100ef700
		void UpdateScore(ScoreColor p_score)
		{
			m_score = p_score;
			if (m_hiScore < p_score) {
				m_hiScore = p_score;
			}
		}

		/**
		 * @brief Returns pointer to array of all action scripts for this mission. [AI]
		 * @return Pointer to the script array. [AI]
		 */
		// FUNCTION: BETA10 0x100ef780
		IsleScript::Script* GetActions() { return m_actions; }

		/**
		 * @brief Gets the script corresponding to the "unknown finish", used as an alternative timeout/decline action. [AI]
		 * @details Returns script at (m_numActions + 2). [AI]
		 */
		// FUNCTION: BETA10 0x100ef7b0
		IsleScript::Script GetUnknownFinishAction() { return m_actions[m_numActions + 2]; }

		/**
		 * @brief Gets the threshold time used for mission timeout events. [AI]
		 * @details Returns value at m_finishTimes[3]. [AI]
		 */
		// FUNCTION: BETA10 0x100ef7e0
		MxLong GetTimeoutTime() { return m_finishTimes[3]; }

		MxS16 m_numActions;            ///< Number of standard actions in script (before special finish actions) [AI]
		MxU8 m_actorId;                ///< Actor (character) ID for this mission [AI]
		undefined2 m_unk0x04;          ///< Used by mission logic, typically 2. [AI]
		MxS16 m_unk0x06;               ///< Used by serialization and progress tracking (mission attempt counter/state) [AI]
		undefined m_unk0x08;           ///< Unknown, always set to 1 at construction. [AI]
		MxLong* m_finishTimes;         ///< Pointer to array of finish time thresholds, 4 per mission [AI]
		MxLong m_startTime;            ///< Time when mission started (INT_MIN if not started) [AI]
		MxS16 m_unk0x14;               ///< Used by helicopter and special mission checks [AI]
		MxS16 m_score;                 ///< Current completion score (LegoState color encoding) [AI]
		MxS16 m_hiScore;               ///< Historical best (high score) for this mission/color [AI]
		IsleScript::Script* m_actions; ///< Script array for actions and finish events for the mission [AI]
	};

	/**
	 * @brief Constructs a new PizzaMissionState and initializes missions for all possible actors. [AI]
	 */
	PizzaMissionState();

	/**
	 * @brief Returns the name of this state class (PizzaMissionState). [AI]
	 */
	// FUNCTION: LEGO1 0x10039290
	// FUNCTION: BETA10 0x100efa20
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f00d4
		return "PizzaMissionState";
	}

	/**
	 * @brief Checks whether the given class name is PizzaMissionState or any base. [AI]
	 * @param p_name Class name to check. [AI]
	 * @return True if it matches. [AI]
	 */
	// FUNCTION: LEGO1 0x100392a0
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, PizzaMissionState::ClassName()) || LegoState::IsA(p_name);
	}

	/**
	 * @brief Serializes custom mission fields (score, progress) for saving/loading game state. [AI]
	 * @param p_storage Storage to serialize with. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	/**
	 * @brief Sets the m_unk0xb0 member, which holds the current object ID of the pending mission action. [AI]
	 * @param p_unk0xb0 The object ID to set. [AI]
	 */
	// FUNCTION: BETA10 0x100ef470
	void SetUnknown0xb0(MxU32 p_unk0xb0) { m_unk0xb0 = p_unk0xb0; }

	/**
	 * @brief Gets the m_unk0xb0 member, which holds the object ID associated with current/next mission flow. [AI]
	 * @return The unknown object ID. [AI]
	 */
	// FUNCTION: BETA10 0x100ef850
	MxU32 GetUnknown0xb0() { return m_unk0xb0; }

	/**
	 * @brief Retrieves the historical best (high) score for a given actor's pizza mission. [AI]
	 * @param p_actorId Character whose mission is checked. [AI]
	 */
	// FUNCTION: BETA10 0x10088850
	MxS16 GetHighScore(MxU8 p_actorId) { return GetMission(p_actorId)->m_hiScore; }

	/**
	 * @brief Finds the Mission struct belonging to a given actor/character. [AI] [AI_SUGGESTED_NAME: GetMission]
	 * @param p_actorId The actor ID (Pepper, Mama, etc.) [AI]
	 * @return Pointer to that actor's Mission struct. [AI]
	 */
	Mission* GetMission(MxU8 p_actorId);

	/**
	 * @brief Invokes logic in the PizzeriaState required for mission state transitions. [AI] [AI_SUGGESTED_NAME: GetPizzeriaProgressStage]
	 * @return Value indicating current mission proposal state/progress. [AI]
	 */
	MxS16 FUN_10039540();

	PizzeriaState* m_pizzeriaState; ///< Pointer to current pizzeria state for delegating cross-mission logic. [AI]
	undefined4 m_unk0x0c;           ///< Used for internal state machine; controls mission flow/progress (e.g., 0=idle, 1=proposed, ...) [AI]
	Mission m_missions[5];          ///< Array with per-actor mission progress. [AI]
	MxU32 m_unk0xb0;                ///< Holds currently "pending" action/object for mission transitions. [AI]

	/// Action scripts for each actor's pizza mission (indexed in Mission::m_actions) [AI]
	static IsleScript::Script g_pepperActions[];
	static IsleScript::Script g_mamaActions[];
	static IsleScript::Script g_papaActions[];
	static IsleScript::Script g_nickActions[];
	static IsleScript::Script g_lauraActions[];

	/// Finish time thresholds (red/blue/yellow/timeout) for all pizza missions (per-actor) [AI]
	static MxLong g_pepperFinishTimes[];
	static MxLong g_mamaFinishTimes[];
	static MxLong g_papaFinishTimes[];
	static MxLong g_nickFinishTimes[];
	static MxLong g_lauraFinishTimes[];
};

// VTABLE: LEGO1 0x100d7380
// VTABLE: BETA10 0x101bf6b0
// SIZE 0x9c
/**
 * @brief Interactive pizza entity actor; manages the in-game pizza delivery sequence and reacts to mission triggers. [AI]
 * @details Pizza provides the in-world 3D/IsleActor for pizza gameplay, message routing, mission state requests, user interaction and 
 * advance tickle logic such as timeouts or scripted scene events. Links together animation flow with SkateBoard, Act1State and mission state. [AI]
 */
class Pizza : public IsleActor {
public:
	/**
	 * @brief Constructs a new Pizza actor, zeroing mission and UI/logic references. [AI]
	 */
	Pizza();

	/**
	 * @brief Destroys the Pizza actor and unregisters it as a tickle client. [AI]
	 */
	~Pizza() override;

	/**
	 * @brief Called every tick when Pizza is active; handles mission timers, timeouts, and auto-advances mission state when needed. [AI]
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief Returns the class name string "Pizza". [AI]
	 */
	// FUNCTION: LEGO1 0x10037f90
	// FUNCTION: BETA10 0x100ef300
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f038c
		return "Pizza";
	}

	/**
	 * @brief Checks if the given class name is this or a base. [AI]
	 * @param p_name Class name string. [AI]
	 * @return True if this is (or is-a) "Pizza". [AI]
	 */
	// FUNCTION: LEGO1 0x10037fa0
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Pizza::ClassName()) || IsleActor::IsA(p_name);
	}

	/**
	 * @brief Initializes Pizza and links in-game state and SkateBoard reference after DSAction evaluation. [AI]
	 * @param p_dsAction The action executed to create this Pizza object. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;                           // vtable+0x18

	/**
	 * @brief Handles mouse or user interaction with Pizza: advances pizza mission state and starts corresponding action/animation. [AI]
	 * @return Nonzero if the pizza accepted and started the mission proposal, 0 otherwise. [AI]
	 */
	MxLong HandleClick() override;                                              // vtable+0x68

	/**
	 * @brief Handles the end of an action/animation sequence, advancing mission state machine if action matches a pending event. [AI]
	 * @param p_param Parameters for end-of-action notification. [AI]
	 * @return Result depending on state. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param) override;     // vtable+0x74

	/**
	 * @brief Handles notification from a path struct event, e.g., actors walking, object triggers, camera anim triggers. [AI]
	 * @param p_param Struct parameter describing the path trigger event. [AI]
	 * @return Zero in all cases; advances state by side effect. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param) override; // vtable+0x80

	/**
	 * @brief Initializes or restores references to PizzaMissionState and Act1State in GameState. [AI]
	 * @details Called at creation and when restoring mission state. [AI]
	 */
	void CreateState();

	/**
	 * @brief Starts mission flow for Pizza with the given action script object. [AI]
	 * @param p_objectId The objectId of the action/script to play. [AI]
	 */
	void FUN_10038220(IsleScript::Script p_objectId);

	/**
	 * @brief Cancels or resets the Pizza mission, stopping music, resetting camera, and animation state. [AI]
	 * @details Side effect: disables pizza/SkateBoard meshes, enables music, resets progress. [AI]
	 */
	void FUN_100382b0();

	/**
	 * @brief Stops all currently running pizza mission actions and resets to an idle state. [AI]
	 * @details Called internally on timeout/failure and at mission completion. [AI]
	 */
	void StopActions();

	/**
	 * @brief Plays an animation action for the pizza mission, updating active object ID and handling script concurrency. [AI]
	 * @param p_objectId The id of the animation/action to play. [AI]
	 * @param p_param7 If TRUE, passes through to animation manager for action playback customization. [AI]
	 */
	void PlayAction(MxU32 p_objectId, MxBool p_param7);

	/**
	 * @brief Sets the SkateBoard actor pointer used for interaction and scene presentation. [AI]
	 * @param p_skateBoard Pointer to SkateBoard. [AI]
	 */
	void SetSkateboard(SkateBoard* p_skateBoard) { m_skateBoard = p_skateBoard; }

private:
	PizzaMissionState* m_state;            ///< Current pizza mission state, tracking mission progress per actor [AI]
	PizzaMissionState::Mission* m_mission; ///< Points to the currently active character's Mission [AI]
	SkateBoard* m_skateBoard;              ///< Reference to SkateBoard actor for pizza cutscenes and animations [AI]
	Act1State* m_act1state;                ///< Global Act1 story state, needed for mission flow and cutscene logic [AI]
	IsleScript::Script m_unk0x8c;          ///< Holds temporary script id for one-shot timeout audio/events [AI]
	MxLong m_unk0x90;                      ///< Timer for special cutscenes/finale wait-after [AI]
	MxLong m_unk0x94;                      ///< Timer duration for above; various wait/hold intervals in ms [AI]
	MxBool m_unk0x98;                      ///< Used to prevent repeat triggers for certain overlapping events [AI]
};

#endif // PIZZA_H
