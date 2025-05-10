#ifndef LEGOACT2_H
#define LEGOACT2_H

#include "act2brick.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

class Act2Actor;
class LegoPathStructNotificationParam;
class MxEndActionNotificationParam;

// VTABLE: LEGO1 0x100d4a70
// VTABLE: BETA10 0x101ba910
// SIZE 0x10
/**
 * @brief Represents the state object for Act 2 of the game. [AI]
 * 
 * LegoAct2State is a subclass of LegoState and is used to store state information 
 * specific to Act 2. It holds an unknown value, and an enabled flag indicating
 * whether the state is currently active/used.
 * 
 * Not serializable (IsSerializable always returns FALSE). [AI]
 */
class LegoAct2State : public LegoState {
public:
	/**
	 * @brief Constructor, initializes state members. [AI]
	 */
	LegoAct2State()
	{
		m_unk0x08 = 0;
		m_enabled = FALSE;
	}

	/**
	 * @brief Destructor. [AI]
	 */
	~LegoAct2State() override {}

	/**
	 * @brief Always returns FALSE, as this state is not serializable. [AI]
	 */
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14

	/**
	 * @brief Returns the class name of this state ("LegoAct2State"). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0428
		return "LegoAct2State";
	}

	/**
	 * @brief Type check against class name or parent class. [AI]
	 * @param p_name Name to check. [AI]
	 * @details Checks if the provided class name matches this class or a base class. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoAct2State::ClassName()) || LegoState::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1000e040
	// LegoAct2State::`scalar deleting destructor'

	/**
	 * @brief Sets the unknown value (purpose unclear). [AI]
	 * @param p_unk0x08 Value to assign. [AI]
	 */
	void SetUnknown0x08(undefined4 p_unk0x08) { m_unk0x08 = p_unk0x08; }

	/**
	 * @brief Gets the value of the unknown member variable. [AI]
	 * @return Current value of m_unk0x08. [AI]
	 */
	undefined4 GetUnknown0x08() { return m_unk0x08; }

	// TODO: Most likely getters/setters are not used according to BETA. (?)

	undefined4 m_unk0x08; ///< [AI] Unknown state variable. Purpose unclear. [AI]
	MxBool m_enabled;     ///< [AI] TRUE if this state is currently enabled/active. [AI]
};

// VTABLE: LEGO1 0x100d82e0
// VTABLE: BETA10 0x101ba898
// SIZE 0x1154
/**
 * @brief Implements the world and game logic for Act 2. [AI]
 * 
 * LegoAct2 is a subclass of LegoWorld and manages all logic, scripting, 
 * entities, and scene transitions for the second act of the game storyline. [AI]
 * 
 * Handles initialization, tick-based updates, notification handling, 
 * cutscenes/animations, entity/boundary management, music, and more. [AI]
 */
class LegoAct2 : public LegoWorld {
public:
	/**
	 * @brief Constructor, initializes all members and registers to the notification manager. [AI]
	 */
	LegoAct2();

	/**
	 * @brief Destructor. Handles unregistering from managers and cleanup. [AI]
	 */
	~LegoAct2() override;

	/**
	 * @brief Handles incoming notifications dispatched by the notification system. [AI]
	 * @param p_param Notification/event parameter structure. [AI]
	 * @details Handles EndAction, PathStruct and other notifications. [AI]
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief Main update tick for Act 2. [AI]
	 * @details Contains the core step-wise logic, particularly state transitions
	 * during cutscenes, handling random events and progress. [AI]
	 */
	MxResult Tickle() override;

	/**
	 * @brief Creates and initializes this world object using a DSAction. [AI]
	 * @param p_dsAction Reference to the data source action. [AI]
	 * @details Also sets up the game state, area info, and initial registration for input and managers. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief Prepares the world for player interaction, resumes animation, registers tickle, etc. [AI]
	 * @details Sets up initial camera, spawns player, scene, music, managers, etc. [AI]
	 */
	void ReadyWorld() override;

	/**
	 * @brief Always returns TRUE: internal state-check used by engine. [AI]
	 */
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/**
	 * @brief Unused; placeholder for possible extension. [AI]
	 */
	void VTable0x60() override;

	/**
	 * @brief Handles the Escape (quit/abort) action, stops audio/cutscene/cleans up state. [AI]
	 * @return TRUE if escape succeeded. [AI]
	 */
	MxBool Escape() override;

	/**
	 * @brief Enables or disables the Act 2 world and logic. [AI]
	 * @param p_enable TRUE to activate, FALSE to suspend/cleanup. [AI]
	 * @details Activates or deactivates tickle, managers, updates music, and restores state as needed. [AI]
	 */
	void Enable(MxBool p_enable) override;

	/**
	 * @brief Sets the Act2Actor instance (main NPC or controller) used within Act2 logic. [AI]
	 * @param p_unk0x1138 Pointer to the Act2Actor instance. [AI]
	 */
	void SetUnknown0x1138(Act2Actor* p_unk0x1138) { m_unk0x1138 = p_unk0x1138; }

	/**
	 * @brief Sets the destination location for area transition upon completion. [AI]
	 * @param p_destLocation Target area enum value. [AI]
	 */
	void SetDestLocation(LegoGameState::Area p_destLocation) { m_destLocation = p_destLocation; }

	/**
	 * @brief Spawns the next collectible brick at its position and plays associated animation if possible. [AI]
	 * @details Handles brick increment and state progression logic. [AI]
	 */
	MxResult FUN_100516b0();

	/**
	 * @brief Spawns the next brick and triggers sound/whistle for the new brick. [AI]
	 * @details Used in brick collection sequences. [AI]
	 */
	void FUN_100517b0();

	/**
	 * @brief Handles the "bad ending" sequence for Act 2. [AI]
	 * @details Removes all bricks, disables main actor, marks transition for return to main area. [AI]
	 */
	MxResult BadEnding();

	/**
	 * @brief Plays an animation (or cutscene) at optional location/direction in world space. [AI]
	 * @param p_objectId Animation/cutscene script object id. [AI]
	 * @param p_param2 Determines path/animation playing logic (true/false). [AI]
	 * @param p_param3 Override flag for repeated/optional actions. [AI]
	 * @param p_location Optional pointer to world location. [AI]
	 * @param p_direction Optional pointer to direction vector. [AI]
	 * @param p_param6 Optional pointer for up vector(?). [AI]
	 * @details Prepares and plays script/animation based on parameters, using DSAction or direct animations. [AI]
	 */
	MxResult FUN_10052560(
		Act2mainScript::Script p_objectId,
		MxBool p_param2,
		MxBool p_param3,
		Mx3DPointFloat* p_location,
		Mx3DPointFloat* p_direction,
		Mx3DPointFloat* p_param6
	);

	// SYNTHETIC: LEGO1 0x1004fe20
	// LegoAct2::`scalar deleting destructor'

private:
	/**
	 * @brief Callback for handling EndAction notifications (usually after cutscene/script event). [AI]
	 * @param p_param Parameter object containing relevant end action info. [AI]
	 * @return 0 (unused or success code). [AI]
	 * @details Handles post-cutscene world updates, entity state, music, bricks, etc. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/**
	 * @brief Callback triggered at the end of a world/area transition. [AI]
	 * @return 1 to indicate success. [AI]
	 * @details Switches to the destination area, if set. [AI]
	 */
	MxLong HandleTransitionEnd();

	/**
	 * @brief Handles a path struct notification from path-following events. [AI]
	 * @param p_param Path notification parameter. [AI]
	 * @return Unused (always 0). [AI]
	 * @details Triggers cutscenes, brick spawning, or state changes based on event. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);

	/**
	 * @brief Starts the given music track for Act 2, using background audio manager. [AI]
	 * @param p_objectId Jukebox script object ID. [AI]
	 */
	void PlayMusic(JukeboxScript::Script p_objectId);

	/**
	 * @brief Helper for suspending and resuming animation manager, used for cutscene transitions. [AI]
	 */
	void FUN_10051900();

	/**
	 * @brief Sets main NPCs (mama, papa, infoman) invisible and resets main actor state. [AI]
	 * @details Used for scripting transitions and state changes. [AI]
	 */
	void FUN_10051960();

	/**
	 * @brief Initializes whistle sounds for all bricks that are visible. [AI]
	 */
	void InitBricks();

	/**
	 * @brief Stops all brick whistle sounds. [AI]
	 */
	void UninitBricks();

	/**
	 * @brief Spawns bricks at random or pre-determined locations for Act 2. [AI]
	 * @details Handles randomization of brick order/locations. [AI]
	 */
	void SpawnBricks();

	/**
	 * @brief Handles secondary logic after certain path events ("stage 7" logic). [AI]
	 * @param p_param1 Event type code. [AI]
	 * @details Plays relevant animations and sound triggers depending on event code and randomness. [AI]
	 */
	void FUN_10051fa0(MxS32 p_param1);

	/**
	 * @brief Handles additional logic for path struct notifications when Act2Phase == 5. [AI]
	 * @param p_param1 PathStruct event type code. [AI]
	 * @details Selects specific cutscenes/animations based on code and actor/brick variables. [AI]
	 */
	void FUN_100521f0(MxS32 p_param1);

	/**
	 * @brief Triggers ambulace/character animations, placement, and logic for next sequence. [AI]
	 * @details Advances game logic for Act 2 brick sequence. [AI]
	 */
	MxResult FUN_10052800();

	Act2Brick m_bricks[10];        ///< [AI] The list of collectible bricks for this act. [AI]
	MxU8 m_nextBrick;              ///< [AI] Index of the next brick to spawn/interact with. [AI]
	undefined m_unk0x10c1;         ///< [AI] Unknown, used as counter in event/notification handling. [AI]
	MxBool m_ready;                ///< [AI] Set TRUE when act is fully initialized and ready. [AI]
	undefined4 m_unk0x10c4;        ///< [AI] Current phase/state of the Act2 progression machine. [AI]
	JukeboxScript::Script m_music; ///< [AI] Music currently playing or to play next. [AI]
	LegoAct2State* m_gameState;    ///< [AI] Current state object for this act. [AI]
	MxS32 m_unk0x10d0;             ///< [AI] Timer or state variable for progression within cutscenes. [AI]
	const char* m_siFile;          ///< [AI] SI script file loaded or associated with Act 2. [AI]
	LegoROI* m_pepper;                  ///< [AI] Main player/actor ROI for pepper in Act 2. [AI]
	MxMatrix m_unk0x10dc;               ///< [AI] World transformation matrix backup for pepper. [AI]
	LegoPathBoundary* m_unk0x1124;      ///< [AI] Path boundary reference used during transitions. [AI]
	LegoROI* m_ambulance;               ///< [AI] Reference to ambulance ROI actor. [AI]
	undefined4 m_unk0x112c;             ///< [AI] Unknown; used as a timer/counter during cutscenes. [AI]
	undefined4 m_unk0x1130;             ///< [AI] Unknown, general purpose. [AI]
	undefined4 m_unk0x1134;             ///< [AI] Unknown, general purpose. [AI]
	Act2Actor* m_unk0x1138;             ///< [AI] Pointer to the current Act2's main NPC/controlled actor. [AI]
	undefined m_unk0x113c;              ///< [AI] Counter or randomizer for event sequencing. [AI]
	Act2mainScript::Script m_unk0x1140; ///< [AI] Object ID for currently running cutscene or animation. [AI]
	Act2mainScript::Script m_unk0x1144; ///< [AI] Object ID for secondary (optional) running animation/event. [AI]
	undefined4 m_unk0x1148;             ///< [AI] Unknown, general purpose. [AI]
	undefined m_firstBrick;             ///< [AI] Index identifier for which brick location was chosen first. [AI]
	undefined m_secondBrick;            ///< [AI] Index identifier for second brick. [AI]
	undefined m_thirdBrick;             ///< [AI] Index identifier for third brick. [AI]
	undefined m_fourthBrick;            ///< [AI] Index identifier for fourth brick. [AI]
	LegoGameState::Area m_destLocation; ///< [AI] Next area to transfer to after act completion. [AI]
};

#endif // LEGOACT2_H