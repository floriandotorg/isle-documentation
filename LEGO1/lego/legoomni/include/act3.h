#ifndef ACT3_H
#define ACT3_H

#include "act3ammo.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

/**
 * @brief [AI] Forward declarations for classes used in Act3 logic.
 * 
 * Act3Brickster: Main antagonist of Act 3.
 * Act3Cop: Police officers involved in Act 3.
 * Act3Shark: Shark character. 
 * Helicopter: Vehicle used in Act 3.
 * MxQuaternionTransformer: Used for orientation and matrix/quaternion math.
 */
class Act3Brickster;
class Act3Cop;
class Act3Shark;
class Helicopter;
class MxQuaternionTransformer;

/// @brief [AI] Maximum number of pizzas that can be handled in Act 3 logic.
#define MAX_PIZZAS 20
/// @brief [AI] Maximum number of donuts that can be handled in Act 3 logic.
#define MAX_DONUTS 20

/**
 * @struct Act3ListElement
 * @brief [AI] Represents an element in a custom list for activity scripting and audio/animation event queueing in Act 3.
 * 
 * Used within Act3List for managing queued actions or states, e.g. scheduled sounds, animations, or story actions.
 * Contains an object ID, an integer which is most likely used as a queue type/priority or option (0x04), and a byte-flag (0x08).
 * 
 * SIZE 0x0c
 */
struct Act3ListElement {
	MxU32 m_objectId;     ///< @brief [AI] Refers to an in-game object or script action; exact semantics are context-dependent.
	undefined4 m_unk0x04; ///< @brief [AI] Option/type/priority for this action. [AI_SUGGESTED_NAME: m_option]
	undefined m_unk0x08;  ///< @brief [AI] Boolean/flag; indicates if the corresponding object/action is active, completed, or should trigger removal. [AI_SUGGESTED_NAME: m_isActive]

	/**
	 * @brief [AI] Default constructor.
	 */
	Act3ListElement() {}

	/**
	 * @brief [AI] Initializes all fields in Act3ListElement.
	 * @param p_objectId The object or script action id [AI].
	 * @param p_unk0x04 The queue type/option/prio [AI].
	 * @param p_unk0x08 Boolean/flag (see above) [AI].
	 */
	Act3ListElement(MxU32 p_objectId, undefined4 p_unk0x04, undefined p_unk0x08)
		: m_objectId(p_objectId), m_unk0x04(p_unk0x04), m_unk0x08(p_unk0x08)
	{
	}

	/**
	 * @brief [AI] Comparison operator, seems to be a placeholder (always returns 0).
	 * @param other Element to compare [AI].
	 * @return [AI] Always false.
	 */
	int operator==(Act3ListElement) const { return 0; }

	/**
	 * @brief [AI] Comparison operator for sorting, seems to be a placeholder (always returns 0).
	 * @param other Element to compare [AI].
	 * @return [AI] Always false.
	 */
	int operator<(Act3ListElement) const { return 0; }
};

/**
 * @class Act3List
 * @brief [AI] A custom intrusive list for handling state machine or scheduled actions/events during Act 3 sequences.
 * 
 * Used to hold and sequence various events such as playing sound, animation, activating or removing in-game objects as determined by scripts.
 * SIZE 0x10
 */
class Act3List : private list<Act3ListElement> {
public:
	/**
	 * @brief [AI] Constructor, initializes the guarded flag to zero.
	 */
	Act3List() { m_unk0x0c = 0; }

	/**
	 * @brief [AI] Inserts a new element, and conditionally triggers associated script actions or events depending on the queueing logic.
	 * @param p_objectId ID of the object or script action. [AI]
	 * @param p_option Queue type/option, determines logic branch. [AI]
	 * @details [AI] Triggers events or actions according to the branching order for options 1, 2, 3, see source for details.
	 */
	void Insert(MxS32 p_objectId, MxS32 p_option); ///< @param p_objectId [AI] @param p_option [AI] @details [AI]

	/**
	 * @brief [AI] Internal removal method for the first element, wraps a deletion and triggers any necessary cleanup.
	 * @details [AI] This corresponds to cleaning up audio/actions that were previously started.
	 */
	void FUN_10071fa0();

	/**
	 * @brief [AI] Removes all elements, triggers associated clean-up actions, and stops background audio.
	 * @details [AI] Call this to reset/clear scheduled or active actions and to halt background processes in Act 3 cutscenes.
	 */
	void Clear();

	/**
	 * @brief [AI] Removes an element either by objectId or from the front of the list, and updates queue state bookkeeping. 
	 * @param p_objectId Object ID to remove, or if zero, removes the head. [AI]
	 * @details [AI] Also reactivates or begins queued actions if others remain after removal.
	 */
	void FUN_100720d0(MxU32 p_objectId);

private:
	undefined4 m_unk0x0c; ///< @brief [AI] Guard or lock field to indicate if a modification is ongoing (prevents recursion or reentrancy issues). [AI_SUGGESTED_NAME: m_locked]
};

/**
 * @class Act3State
 * @brief [AI] Holds persistent state and status variables for Act 3 mission, saved between world reloads and possibly serialized.
 * 
 * Derives from LegoState, storing progress flags and custom state transitions for Act 3 cutscenes or mini-games.
 * SIZE 0x0c
 */
class Act3State : public LegoState {
public:
	/**
	 * @brief [AI] Initializes additional persistent status fields.
	 */
	Act3State() { m_unk0x08 = 0; }

	/**
	 * @brief [AI] Indicates whether this state is serializable to disk or not.
	 * @return [AI] Always FALSE for this subclass.
	 */
	MxBool IsSerializable() override { return FALSE; }

	/**
	 * @brief [AI] Returns class name for RTTI string matching.
	 * @return [AI] "Act3State"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "Act3State";
	}

	/**
	 * @brief [AI] Checks if the class name matches a given string or any parent class.
	 * @param p_name Name to check [AI].
	 * @return [AI] True if p_name matches this class or a base class.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Act3State::ClassName()) || LegoState::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1000e3c0
	// Act3State::`scalar deleting destructor'

	/**
	 * @brief [AI] Getter for the (unknown) main status variable.
	 * @return [AI] Internal status/instruction code or flag.
	 */
	undefined4 GetUnknown0x08() { return m_unk0x08; }

	/**
	 * @brief [AI] Unknown persistent field holding an instruction/state flag.
	 */
	undefined4 m_unk0x08; // 0x08
};

/**
 * @class Act3
 * @brief [AI] Controls all main logic and progression of Act 3 in LEGO Island, including objects, cutscenes, enemy and player actors, and event scheduling.
 * 
 * Derives from LegoWorld. Manages state progression, scripted events, player/AI interaction, special actions, win/loss logic, and event synchronization.
 * Acts as a controller for main sequence, tracks and manages special actors (cop, brickster, shark, helicopter), their states, and all in-world objects like pizzas/donuts.
 * 
 * SIZE 0x4274
 */
class Act3 : public LegoWorld {
public:
	/**
	 * @brief [AI] Initializes all mission-critical actors, resets world state, and sets up notification and navigation.
	 */
	Act3();

	/**
	 * @brief [AI] Cleans up world and unregisters from notifications, frees all owned data.
	 */
	~Act3() override;

	/**
	 * @brief [AI] Handles notifications from other systems (animation, transition, audio, etc.).
	 * @param p_param Notification payload and type. [AI]
	 * @return [AI] Return value is used to indicate if Act3 handled the event.
	 * @details [AI] Used especially for synchronization between cutscenes, user input state, and state transitions.
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Main tick/update—called on each game loop iteration to update state, advance animations, and sync objects.
	 * @return [AI] SUCCESS always, but actual return type expresses state of tick.
	 */
	MxResult Tickle() override;               // vtable+0x08

	/**
	 * @brief [AI] Always returns TRUE, notifies higher-level logic that Act 3 is always enabled for handing VTable0x5c queries.
	 * @return [AI] TRUE
	 */
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/**
	 * @brief [AI] Returns the class name string.
	 * @return [AI] "Act3"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "Act3";
	}

	/**
	 * @brief [AI] Checks if the class name matches this class or any parent class.
	 * @param p_name Class name to check for. [AI]
	 * @return [AI] TRUE if matches this class or any LegoWorld class.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Act3::ClassName()) || LegoWorld::IsA(p_name);
	}

	/**
	 * @brief [AI] World instancing method; sets up actors and notifies managers of state change. Also handles Act 2 → Act 3 logic.
	 * @param p_dsAction Scripted action/context used during creation. [AI]
	 * @return [AI] SUCCESS or FAILURE
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Teardown logic for Act 3, unregisters from world and resets navigation/input.
	 * @param p_fromDestructor TRUE if called from the destructor path. [AI]
	 */
	void Destroy(MxBool p_fromDestructor) override;   // vtable+0x1c

	/**
	 * @brief [AI] Called when transitioning into Act 3; triggers state setup and intro animation/missions.
	 */
	void ReadyWorld() override;                       // vtable+0x50

	/**
	 * @brief [AI] Empty implementation for Act3-specific state logic; present for interface fulfillment.
	 */
	void VTable0x60() override;                       // vtable+0x60

	/**
	 * @brief [AI] Handles "escape" action (user attempts to leave/quit Act 3); cleans up state and halts audio/animation.
	 * @return [AI] TRUE, always considered successful.
	 */
	MxBool Escape() override;                         // vtable+0x64

	/**
	 * @brief [AI] Enables/Disables the world, handling time shifting/resume logic for all major actors in Act3.
	 * @param p_enable TRUE to enable, FALSE to pause/freeze. [AI]
	 * @details [AI] Syncs/holds actor clocks, registers/deregisters input, and handles background music.
	 */
	void Enable(MxBool p_enable) override;            // vtable+0x68

	/**
	 * @brief [AI] Sets helicopter reference for main mission.
	 * @param p_copter Helicopter instance pointer. [AI]
	 */
	void SetHelicopter(Helicopter* p_copter) { m_copter = p_copter; }

	/**
	 * @brief [AI] Sets Act3Shark reference for the current encounter.
	 * @param p_shark Shark entity pointer. [AI]
	 */
	void SetShark(Act3Shark* p_shark) { m_shark = p_shark; }

	/**
	 * @brief [AI] Sets the destination area/location for the next world switch.
	 * @param p_destLocation GameState Area enumeration [AI].
	 */
	void SetDestLocation(LegoGameState::Area p_destLocation) { m_destLocation = p_destLocation; }

	// SYNTHETIC: LEGO1 0x10072630
	// Act3::`scalar deleting destructor'

	/**
	 * @brief [AI] Simulates eating (removing) a pizza from the world at the given index.
	 * @param p_index Index of pizza in list [AI].
	 */
	void EatPizza(MxS32 p_index);

	/**
	 * @brief [AI] Simulates eating (removing) a donut from the world at the given index.
	 * @param p_index Index of donut in list [AI].
	 */
	void EatDonut(MxS32 p_index);

	/**
	 * @brief [AI] Removes given pizza actor and performs associated logic.
	 * @param p_p Pizza ammo reference [AI].
	 */
	void RemovePizza(Act3Ammo& p_p);

	/**
	 * @brief [AI] Removes given donut actor and performs associated logic.
	 * @param p_p Donut ammo reference [AI].
	 */
	void RemoveDonut(Act3Ammo& p_p);

	/**
	 * @brief [AI] Attempts to launch a pizza as a projectile using the given controller and initial transform.
	 * @param p_controller Path controller providing trajectory. [AI]
	 * @param p_location World location to spawn at. [AI]
	 * @param p_direction World direction vector. [AI]
	 * @param p_up World up vector. [AI]
	 * @return [AI] SUCCESS if a slot was available and launched, FAILURE otherwise.
	 */
	MxResult ShootPizza(LegoPathController* p_controller, Vector3& p_location, Vector3& p_direction, Vector3& p_up);

	/**
	 * @brief [AI] Attempts to launch a donut as a projectile using the given controller and initial transform.
	 * @param p_controller Path controller for movement. [AI]
	 * @param p_location Spawn location. [AI]
	 * @param p_direction Launch direction. [AI]
	 * @param p_up Up vector for the spawn. [AI]
	 * @return [AI] SUCCESS if launched, FAILURE otherwise.
	 */
	MxResult ShootDonut(LegoPathController* p_controller, Vector3& p_location, Vector3& p_direction, Vector3& p_up);

	/**
	 * @brief [AI] Triggers special sequence actions or sounds depending on the provided param; cycles through queues.
	 * @param p_param1 Selection index for the particular action series. [AI]
	 */
	void FUN_10072ad0(undefined4 p_param1);

	/**
	 * @brief [AI] Triggers script/animation effects on the brickster for pizzas that impact him.
	 * @param p_ammo Reference to impacting ammo. [AI] 
	 * @param p_param2 Impact point/direction. [AI]
	 * @return [AI] SUCCESS
	 */
	MxResult FUN_10073360(Act3Ammo& p_ammo, const Vector3& p_param2);

	/**
	 * @brief [AI] Triggers script/animation effects on cops for donuts that impact them.
	 * @param p_ammo Reference to impacting ammo. [AI]
	 * @param p_param2 Impact point/direction. [AI]
	 * @return [AI] SUCCESS
	 */
	MxResult FUN_10073390(Act3Ammo& p_ammo, const Vector3& p_param2);

	/**
	 * @brief [AI] Sets the reference to the Brickster actor in this Act3 instance.
	 * @param p_brickster Brickster pointer. [AI]
	 */
	void SetBrickster(Act3Brickster* p_brickster);

	/**
	 * @brief [AI] Registers a new cop, assigning to cop1 or cop2 as appropriate.
	 * @param p_cop Cop pointer. [AI]
	 */
	void AddCop(Act3Cop* p_cop);

	/**
	 * @brief [AI] Moves Act3 and its state to next step/action in custom sequence (used for in-game cutscene transitions).
	 */
	void FUN_10073400();

	/**
	 * @brief [AI] Moves Act3 and its state to a different step/action in custom sequence (used for in-game cutscene transitions).
	 */
	void FUN_10073430();

	/**
	 * @brief [AI] Handles victory logic for Act3 (good ending); disables enemy actors, clears lists, triggers copter animation to destination.
	 * @param p_destination Matrix specifying world destination for copter. [AI]
	 */
	void GoodEnding(const Matrix4& p_destination);

	/**
	 * @brief [AI] Handles loss logic for Act3 (bad ending); disables enemy actors, clears lists, triggers copter animation.
	 * @param p_destination Matrix for bad ending copter path. [AI]
	 */
	void BadEnding(const Matrix4& p_destination);

	/**
	 * @brief [AI] Removes one helicopter dot from the HUD, used when the copter progresses or an event is triggered.
	 */
	void FUN_10073a60();

	// BETA indicates that the following classes access certain members directly.
	friend class Act3Ammo;
	friend class Act3Brickster;
	friend class Act3Cop;
	friend class Act3Shark;

protected:
	/**
	 * @brief [AI] Handles logic when a world/area transition is completed.
	 * @return [AI] Typically 1 to indicate transition handling complete.
	 */
	MxLong HandleTransitionEnd();

	/**
	 * @brief [AI] Debug utility, outputs formatted diagnostic messages for Act3 copter and world state.
	 * @param p_format printf-like format string [AI].
	 * @param ... Variadic arguments for format [AI].
	 */
	static void DebugPrintf(const char* p_format, ...);

	/**
	 * @brief [AI] Debugs world matrices and quaternion transforms for helicopter camera/final animation.
	 * @param p_copter Copter matrix [AI].
	 * @param p_destination Destination matrix [AI].
	 * @param p_startPosition Start pos matrix [AI].
	 * @param p_endPosition End pos matrix [AI].
	 * @param p_quatTransform Quaternion transformer [AI].
	 */
	static void DebugCopter(
		const Matrix4& p_copter,
		const Matrix4& p_destination,
		const Matrix4& p_startPosition,
		const Matrix4& p_endPosition,
		const MxQuaternionTransformer& p_quatTransform
	);

	Act3State* m_state;                 ///< @brief [AI] Current persistent Act3 state (progress flags, etc.).
	Act3Ammo m_pizzas[MAX_PIZZAS];      ///< @brief [AI] All possible pizza projectiles/instances in flight for this sequence.
	Act3Ammo m_donuts[MAX_DONUTS];      ///< @brief [AI] All possible donuts in flight/active for Act3's special logic.
	undefined m_unk0x41fc;              ///< @brief [AI] General flag, possibly "started" or "initialized". [AI_SUGGESTED_NAME: m_started]
	Act3Cop* m_cop1;                    ///< @brief [AI] First cop involved in sequence (player/AI).
	Act3Cop* m_cop2;                    ///< @brief [AI] Second cop, instantiated when both are present.
	Act3Brickster* m_brickster;         ///< @brief [AI] Main antagonist.
	Helicopter* m_copter;               ///< @brief [AI] Player's helicopter, main vehicle.
	Act3Shark* m_shark;                 ///< @brief [AI] Shark entity in the world, for special chase/attack scenes.
	MxFloat m_time;                     ///< @brief [AI] Used to track the time when Act3 was paused, and for actor resynchronization.
	MxU8 m_unk0x4218;                   ///< @brief [AI] Index/counter for the first event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex1]
	MxU8 m_unk0x4219;                   ///< @brief [AI] Index/counter for the second event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex2]
	MxU8 m_unk0x421a;                   ///< @brief [AI] Index/counter for third event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex3]
	MxU8 m_unk0x421b;                   ///< @brief [AI] Index/counter for fourth event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex4]
	MxU8 m_unk0x421c;                   ///< @brief [AI] Index/counter for fifth event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex5]
	MxU8 m_unk0x421d;                   ///< @brief [AI] Index/counter for sixth event-queue or script sequence. [AI_SUGGESTED_NAME: m_scriptIndex6]
	undefined m_unk0x421e;              ///< @brief [AI] Stores number of helicopter "dot" items to show on the HUD, decremented for bad/good ending. [AI_SUGGESTED_NAME: m_helicopterDotCount]
	Act3List m_unk0x4220;               ///< @brief [AI] Main queue/list for triggering and removing queued scripted actions. [AI_SUGGESTED_NAME: m_actionQueue]
	MxPresenter* m_helicopterDots[15];  ///< @brief [AI] Visual indicators for helicopter progress/UI.
	Act3Script::Script m_unk0x426c;     ///< @brief [AI] Current animation or script in progress (for intro/finale). [AI_SUGGESTED_NAME: m_currentScript]
	LegoGameState::Area m_destLocation; ///< @brief [AI] Target world/area to switch to upon transition. Used for story progression.
};

#endif // ACT3_H
