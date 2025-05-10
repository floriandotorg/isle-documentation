#ifndef JETSKIRACE_H
#define JETSKIRACE_H

#include "legorace.h"

// VTABLE: LEGO1 0x100d4fe8
// VTABLE: BETA10 0x101bd268
// SIZE 0x144
/**
 * @brief [AI] LEGO Island's "Jetski" racing game logic and presenter class, derived from LegoRace.
 * @details [AI] Handles the game-specific logic and UI for Jetski racing sequences, including event handling, state management, progress visualization, course lap tracking, and scripted actions. Integrates fully into the engine scene, presenter, and entity system.
 */
class JetskiRace : public LegoRace {
public:
	/**
	 * @brief [AI] Returns the handler class name used for runtime type checks and scripting.
	 * @details [AI] Used internally for identifying the JetskiRace class in reflection points, scripts, and serialization.
	 * @return Pointer to a static string literal: "JetskiRace" [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Gets the runtime class name for this instance.
	 * @details [AI] Used for in-game reflection, serialization/inspection, and scripting systems.
	 * @return Class name string as "JetskiRace". [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Determines if this object matches or inherits from the specified class name.
	 * @param p_name Name or type to check against this or parent classes. [AI]
	 * @details [AI] Supports both JetskiRace and parent LegoRace type checks for scripting and game logic dispatch.
	 * @return True if class name matches or is inherited. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Instantiates and initializes the Jetski race with SI script action context.
	 * @param p_dsAction The action parameters controlling initial instantiation, normally from script/scene load. [AI]
	 * @details [AI] Sets up the world, race state, registers the appropriate presenter/logic, and initializes lap and race counters.
	 * @return Success/failure of JetskiRace creation. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Prepares the game world objects and scene for Jetski racing gameplay.
	 * @details [AI] Initializes UI presenters, background music, animation resumption, and resets core state/variables for race start.
	 */
	void ReadyWorld() override;

	/**
	 * @brief [AI] Handles escape/exit-from-minigame actions for JetskiRace.
	 * @details [AI] Cleans up animation, removes temporary entities, updates state variables, and manages transition to previous location or menu.
	 * @return Always TRUE after performing cleanup and exit work. [AI]
	 */
	MxBool Escape() override;

	/**
	 * @brief [AI] Handles click/interaction events on JetskiRace-specific controls or UI.
	 * @param p_param Click notification details, castable to various subtypes depending on the event source. [AI]
	 * @details [AI] Dispatches arm/info panel actions, triggers state cleanup, or scene transitions.
	 * @return 1 if the click triggered a handled state change, otherwise 0. [AI]
	 */
	MxLong HandleClick(LegoEventNotificationParam&) override;

	/**
	 * @brief [AI] Handles path struct notifications during path/race progression.
	 * @param p_param Path struct action notification, includes entity ID and event data. [AI]
	 * @details [AI] Checks progress, updates lap/section counters, and manages checkpoints, victory logic, and race effect updates.
	 * @return 1 if a critical event (such as lap or goal reached) is processed, otherwise 0. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override;

	/**
	 * @brief [AI] Handles notifications when scripted actions end.
	 * @param p_param Details for end-of-action notification including the action type. [AI]
	 * @details [AI] Handles unmuting, state variable updates, and advances the race or concludes events after sounds (e.g., horn start) play.
	 * @return 1 if the action end caused a handled state/event, otherwise 0. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam&) override;

	/**
	 * @brief [AI] Updates auxiliary race progress presenters for opponents or other racers.
	 * @details [AI] Calculates and updates visual UI marker position for AI/jukebox trackers at each lap or race section.
	 * @param p_param1 Entity/racer type or ID (typically 11 for the first, 12 for the second AI opponent). [AI]
	 * @param p_param2 Section, lap, or progress value to visualize. [AI]
	 */
	void FUN_10016930(MxS32 p_param1, MxS16 p_param2);

private:
	/**
	 * @brief [AI] Global static for segment count or lap multiplier in Jetski race pathway logic.
	 * @details [AI] Used for distance/progress scaling and to determine lap loop endpoints and positioning.
	 *
	 * [AI_SUGGESTED_NAME: s_numJetskiRaceLaps]
	 */
	static MxS32 g_unk0x100f0c78;
};

// VTABLE: LEGO1 0x100d4fa8
// VTABLE: BETA10 0x101bd5d0
// SIZE 0x2c
/**
 * @brief [AI] Per-race state data and logic holder for JetskiRace, used for tracking player and AI standings, lap progress, and results.
 * @details [AI] Derived from RaceState, supports reflection, serialization, and score/goal tracking for the Jetski racing minigame.
 */
class JetskiRaceState : public RaceState {
public:
	/**
	 * @brief [AI] Returns class name for runtime introspection and type matching.
	 * @return "JetskiRaceState" string. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Runtime type check for JetskiRaceState or parent types.
	 * @param p_name Class name for which to check matching/inheritance. [AI]
	 * @details [AI] Supports both self and parent RaceState checks for scripting and logic dispatch.
	 * @return True if names match this or a parent class. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	// SYNTHETIC: LEGO1 0x1000f680
	// SYNTHETIC: BETA10 0x100a9d10
	// JetskiRaceState::`scalar deleting destructor'
};

// SYNTHETIC: LEGO1 0x1000f530
// SYNTHETIC: BETA10 0x100a9b70
// JetskiRace::`scalar deleting destructor'

// SYNTHETIC: BETA10 0x100aa150
// JetskiRace::~JetskiRace

#endif // JETSKIRACE_H
