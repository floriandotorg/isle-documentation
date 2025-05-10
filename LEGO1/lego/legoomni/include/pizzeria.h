#ifndef PIZZERIA_H
#define PIZZERIA_H

#include "actionsfwd.h"
#include "decomp.h"
#include "isleactor.h"
#include "legostate.h"

class PizzaMissionState;

// VTABLE: LEGO1 0x100d5ee8
// VTABLE: BETA10 0x101bf788
// SIZE 0x58
/**
 * @brief [AI] Stores all state information for the pizzeria (Pizza Shop) minigame. Tracks animation progress for each
 *           character (Pepper, Mama, Papa, Nick, Laura) and manages action playlists and progress for each.
 * @details [AI] Maintains an array of Playlist objects for each character (for animation sequences) and an array that
 *           tracks individual progress/state for each character. Serialization saves/loads playlist indexes so that progress
 *           is consistent through save/load cycles.
 */
class PizzeriaState : public LegoState {
public:
	/**
	 * @brief [AI] Constructor that initializes the playlists for each pizzeria actor and resets progress state.
	 */
	PizzeriaState();

	/**
	 * @brief [AI] Returns the class name string identifier.
	 * @return const char* "PizzeriaState" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0370
		return "PizzeriaState";
	}

	/**
	 * @brief [AI] Checks if this object is a PizzeriaState or a base type.
	 * @param p_name Name of class to check type against. [AI]
	 * @return MxBool True if matching classname or parent type, false otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, PizzeriaState::ClassName()) || LegoState::IsA(p_name);
	}

	/**
	 * @brief [AI] Serializes Playlist progress/state for all actors to/from the provided storage. Reads and writes the
	 *        next action index for each playlist to allow save-load of animation progress.
	 * @param p_storage Save/load storage object. [AI]
	 * @return MxResult Result code from LegoState::Serialize and serialization operations. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	// SYNTHETIC: LEGO1 0x10017ce0
	// PizzeriaState::`scalar deleting destructor'

	/**
	 * @brief [AI] Returns the per-actor progress state index for the actor corresponding to the current player's actorId.
	 * @details [AI] Used to determine how far the player has progressed in the pizzeria sequence.
	 * @return MxS16 Current progress state index for the active actor. [AI]
	 */
	MxS16 FUN_10017d50();

	/**
	 * @brief [AI] Advance and fetch the next action (animation script) for the player's actor in the pizzeria.
	 * @details [AI] Updates per-actor state to ensure actors progress through their available action scripts, incrementing
	 *         the action index up to 2. Uses Playlist for cycling through actor animation scripts.
	 * @return MxU32 The next IsleScript::Script value (animation/action script ID) to use. [AI]
	 */
	MxU32 NextAction();

	/**
	 * @brief [AI] Playlists (one for each actor in the pizzeria: Pepper, Mama, Papa, Nick, Laura)
	 * holding the list of animation script IDs to be played in order. [AI]
	 */
	Playlist m_unk0x08[5]; // 0x08

	/**
	 * @brief [AI] Per-actor state counters. Index corresponds to actor ID - 1. Tracks how many actions
	 * have already been performed by each actor, used for sequentially advancing through available actions. [AI]
	 */
	MxS32 m_unk0x44[5];    // 0x44

	/**
	 * @brief [AI] Static list of script IDs for Pepper's actions/animations in the pizzeria minigame.
	 */
	static IsleScript::Script g_pepperActions[];
	/**
	 * @brief [AI] Static list of script IDs for Mama's actions/animations in the pizzeria minigame.
	 */
	static IsleScript::Script g_mamaActions[];
	/**
	 * @brief [AI] Static list of script IDs for Papa's actions/animations in the pizzeria minigame.
	 */
	static IsleScript::Script g_papaActions[];
	/**
	 * @brief [AI] Static list of script IDs for Nick's actions/animations in the pizzeria minigame.
	 */
	static IsleScript::Script g_nickActions[];
	/**
	 * @brief [AI] Static list of script IDs for Laura's actions/animations in the pizzeria minigame.
	 */
	static IsleScript::Script g_lauraActions[];
};


// VTABLE: LEGO1 0x100d5520
// VTABLE: BETA10 0x101bd0b0
// SIZE 0x84
/**
 * @brief [AI] Actor representing the pizzeria (Pizza Shop) as an interactive entity in the LEGO Island world.
 * Handles state management and click events related to the pizzeria minigame.
 */
class Pizzeria : public IsleActor {
public:
	/**
	 * @brief [AI] Constructor. Initializes state pointers to null.
	 */
	Pizzeria() : m_pizzeriaState(NULL) {}

	/**
	 * @brief [AI] Returns the class name string identifier.
	 * @return const char* "Pizzeria" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0380
		return "Pizzeria";
	}

	/**
	 * @brief [AI] Checks if this object is a Pizzeria or a base type.
	 * @param p_name Name of class to check type against. [AI]
	 * @return MxBool True if matching classname or parent type, false otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Pizzeria::ClassName()) || IsleActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles the initialization of the Pizzeria actor in response to a data source action (SI script logic).
	 * @param p_dsAction Data source action describing the action to create. [AI]
	 * @return MxResult Result of the creation process (SUCCESS if successful). [AI]
	 * @details [AI] On SUCCESS, creates and links relevant state blocks for both PizzeriaState and PizzaMissionState.
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Handles click/interact actions on the Pizzeria actor, triggering minigame logic.
	 * @details [AI] If the pizza mission isn't active, triggers the next animation/action in the character's script via Playlist
	 * and manages participant actors. Also manages animation and actor exit logic for the user's current actor.
	 * @return MxLong Always returns 1 (indicates click handled). [AI]
	 */
	MxLong HandleClick() override;                    // vtable+0x68

	/**
	 * @brief [AI] Searches the game state for existing state objects for "PizzeriaState" and "PizzaMissionState",
	 * creating them if necessary, and links them to this actor.
	 * @details [AI] Ensures the actor has valid state objects to read/write progress and actions for the minigame.
	 */
	void CreateState();

	// SYNTHETIC: LEGO1 0x1000e8d0
	// Pizzeria::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Pointer to the PizzeriaState object that tracks persistent progress for the player's actions in the pizzeria minigame.
	 */
	PizzeriaState* m_pizzeriaState;         // 0x7c

	/**
	 * @brief [AI] Pointer to PizzaMissionState block, tracking global pizza delivery minigame state.
	 * [AI_SUGGESTED_NAME: m_pizzaMissionState]
	 */
	PizzaMissionState* m_pizzaMissionState; // 0x80
};

#endif // PIZZERIA_H