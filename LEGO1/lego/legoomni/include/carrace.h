#ifndef CARRACE_H
#define CARRACE_H

#include "decomp.h"
#include "legorace.h"

class RaceSkel;

// VTABLE: LEGO1 0x100d4b70
// VTABLE: BETA10 0x101bd5f0
// SIZE 0x2c
/**
 * @brief The state object used for the car race mini-game. [AI]
 * @details [AI] CarRaceState manages and tracks the game state for the car racing sequence in the game. It implements type identification via ClassName and IsA for runtime checks and inheritance testing. [AI]
 */
class CarRaceState : public RaceState {
public:
	/**
	 * @brief Returns the class name for runtime type identification ("CarRaceState"). [AI]
	 * @details [AI] Used for dynamic IsA checks and scripting. [AI]
	 * @return Pointer to the class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f009c
		return "CarRaceState";
	}

	/**
	 * @brief Checks if this object is the specified class or inherits from it. [AI]
	 * @param p_name Class name to check against. [AI]
	 * @details [AI] Performs a string comparison and delegates up to RaceState if there is no match. [AI]
	 * @return TRUE if this object matches the specified type, or a parent does. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, CarRaceState::ClassName()) || RaceState::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1000f740
	// CarRaceState::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100d5e50
// VTABLE: BETA10 0x101be290
// SIZE 0x154
/**
 * @brief Implements the LEGO Island car race game mode. [AI]
 * @details [AI] CarRace manages the entire lifecycle of the car racing mini-game, handling object creation, race state management, notifications (clicks, race progress), setting up the 3D scene, handling transitions, updating visual feedback, and interfacing with other game systems (scripts, animation, audio, variable table, etc). [AI]
 *
 * When started, CarRace configures the player and NPC racers, prepares UI and world, handles animations, sound, and user interaction/input, and manages progression and finish logic. [AI]
 */
class CarRace : public LegoRace {
public:
	/**
	 * @brief Constructs a CarRace instance and initializes member variables. [AI]
	 */
	CarRace();

	/**
	 * @brief Returns the class name for runtime type identification ("CarRace"). [AI]
	 * @details [AI] Used for IsA() type checks and scripting. [AI]
	 * @return Pointer to the class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0528
		return "CarRace";
	}

	/**
	 * @brief Checks if this object is the specified class or inherits from it. [AI]
	 * @param p_name Class name to check against. [AI]
	 * @details [AI] Performs a string comparison and delegates up to LegoRace if there is no match. [AI]
	 * @return TRUE if this is class or base type matches p_name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, CarRace::ClassName()) || LegoRace::IsA(p_name);
	}

	/**
	 * @brief Initializes the car racing game mode and underlying state based on the supplied DSAction. [AI]
	 * @param p_dsAction Script action (usually from SI files) to create the race context. [AI]
	 * @details [AI] This sets up controllers, audio, variables, scripts, and state tracking for the car race sequence. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;                   // vtable+0x18

	/**
	 * @brief Prepares the car race world and all interactive actors, UI, and animations. [AI]
	 * @details [AI] This runs post-initialization before the first race frame. It activates HUD, inputs, animation, race progress tracking, positions UI presenters, and sets race distance. [AI]
	 */
	void ReadyWorld() override;                                         // vtable+0x50

	/**
	 * @brief Handles the user-initiated escape/action to quit or exit the car race mini-game. [AI]
	 * @details [AI] Stops race-specific actions, resets relevant state and transitions back to main menu/other area. [AI]
	 * @return TRUE if escape is handled successfully. [AI]
	 */
	MxBool Escape() override;                                           // vtable+0x64

	/**
	 * @brief Handles click input in the context of the car race UI (such as quit buttons). [AI]
	 * @param p_param The click notification details. [AI]
	 * @details [AI] Processes which UI object was clicked and handles stop transitions, variable updates, and game state changes. [AI]
	 * @return Always 1 (Handled). [AI]
	 */
	MxLong HandleClick(LegoEventNotificationParam&) override;           // vtable+0x6c

	/**
	 * @brief Handles race progress triggers from path segments. [AI]
	 * @param p_param Notification about an entity passing a trigger point along the race path. [AI]
	 * @details [AI] Updates position, win/lose logic, UI position, sets variables for distance/lap completion, and handles transitions and mute on race finish. [AI]
	 * @return 1 if the event is handled (such as lap finishing), otherwise 0. [AI]
	 */
	MxLong HandlePathStruct(LegoPathStructNotificationParam&) override; // vtable+0x70

	/**
	 * @brief Handles the ending of scripted race actions. [AI]
	 * @param p_param Notification for actions (e.g., animations, audio) completing. [AI]
	 * @details [AI] Used to chain script events and update post-race animations, dialog, and state changes. [AI]
	 * @return 1 if the notification was handled, otherwise 0. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam&) override;     // vtable+0x74

	/**
	 * @brief Handles notifications of an unclassified ("type 0") game event in this game mode. [AI]
	 * @param param Game notification parameter. [AI]
	 * @details [AI] Used to monitor and react to generic notifications, such as state transitions at the end of the race. [AI]
	 * @return Always 1. [AI]
	 */
	MxLong HandleType0Notification(MxNotificationParam&) override;      // vtable+0x78

	/**
	 * @brief Provides access to the RaceSkel (race skeleton) object managing actor animations or kinematics. [AI]
	 * @return Pointer to the RaceSkel object. [AI]
	 */
	RaceSkel* GetSkeleton() { return m_skeleton; }

	/**
	 * @brief Sets the current RaceSkel instance for this car race. [AI]
	 * @param p_skeleton Race skeleton instance to assign. [AI]
	 */
	void SetSkeleton(RaceSkel* p_skeleton) { m_skeleton = p_skeleton; }

	/**
	 * @brief Updates the location of still presenters for UI progress based on race advancement. [AI]
	 * @param p_param1 Entity group/type (11 for car 1, 12 for car 2). [AI]
	 * @param p_param2 Race segment index reached to update the position for. [AI]
	 * @details [AI] Moves UI elements to reflect race progress for secondary actors (NPC vehicles). [AI]
	 */
	void FUN_10017820(MxS32 p_param1, MxS16 p_param2);

	// SYNTHETIC: LEGO1 0x10016c70
	// CarRace::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Table of animation script IDs for use in the car race sequence (set 1). [AI]
	 * @details [AI] Used to randomize which animation or sequence gets triggered for certain cinematics. [AI]
	 */
	static MxS32 g_unk0x100d5d10[];

	/**
	 * @brief [AI] Table of animation script IDs for set 2. [AI]
	 * @details [AI] Used for alternate/secondary animation random selection. [AI]
	 */
	static MxS32 g_unk0x100d5d30[];

	/**
	 * @brief [AI] Table of animation script IDs for set 3. [AI]
	 */
	static MxS32 g_unk0x100d5d40[];

	/**
	 * @brief [AI] Table of animation script IDs for set 4. [AI]
	 */
	static MxS32 g_unk0x100d5d50[];

	/**
	 * @brief [AI] Table of animation script IDs for set 5. [AI]
	 */
	static MxS32 g_unk0x100d5d60[];

	/**
	 * @brief [AI] Script or animation object currently active for a major sequence. [AI]
	 * @details [AI] Used for keeping track of progression/animation state. See HandleEndAction/ReadyWorld/HandlePathStruct. [AI]
	 */
	MxS32 m_unk0x144;     // 0x144

	/**
	 * @brief [AI] Animation/sequence ID or script for a secondary post-race event or placement (e.g. win/lose). [AI]
	 */
	MxS32 m_unk0x148;     // 0x148

	/**
	 * @brief [AI] Animation/sequence ID or script for an alternate/counter post-race animation. [AI]
	 */
	MxS32 m_unk0x14c;     // 0x14c

	/**
	 * @brief [AI] Pointer to the race skeleton (for animation/kinematics and actor structure). [AI]
	 * @details [AI] This manages the logical skeleton for the race cars (for animation or physics bindings). [AI]
	 */
	RaceSkel* m_skeleton; // 0x150
};

#endif // CARRACE_H
