#ifndef ACT3ACTORS_H
#define ACT3ACTORS_H

#include "legoanimactor.h"

// File name verified by multiple assertions, e.g. BETA10 0x10018391 [AI]

class Act3Ammo;
struct LegoBuildingInfo;
struct LegoPlantInfo;
class LegoWorld;

// VTABLE: LEGO1 0x100d7920 LegoPathActor [AI]
// VTABLE: LEGO1 0x100d79f0 LegoAnimActor [AI]
// SIZE 0x1a8 [AI]
/**
 * @brief [AI] Represents the shark actor for Act 3 of the LEGO Island game. The shark can "eat" pizzas (Act3Ammo), animates the eating, and interacts visually in the cutscene logic.
 * 
 * Inherits from LegoAnimActor for animation and path logic.
 */
class Act3Shark : public LegoAnimActor {
public:
	/**
	 * @brief [AI] Constructs a new Act3Shark object, initializing internal state.
	 */
	Act3Shark();

	/**
	 * @brief [AI] Handles additional parsing logic for shark-specific actions, such as animation triggers.
	 * @param p_extra Action string to parse [AI]
	 */
	void ParseAction(char*) override;    // vtable+0x20

	/**
	 * @brief [AI] Handles per-frame animation updates for the shark, synchronizing animation with pizza consumption and ROI visibility.
	 * @param p_time The current game time, in milliseconds [AI]
	 */
	void Animate(float p_time) override; // vtable+0x70

	/**
	 * @brief [AI] Called when the shark "eats" a pizza. Registers the ammo for later animation/effects.
	 * @param p_ammo The ammo (pizza object) to be marked as eaten [AI]
	 * @return SUCCESS if registered, otherwise error [AI]
	 */
	virtual MxResult EatPizza(Act3Ammo* p_ammo); // vtable+0x10

	/**
	 * @brief [AI] Returns the class name string for debugging/instancing.
	 * @return Always returns "Act3Shark" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// Does not exist in BETA10 [AI]
		// STRING: LEGO1 0x100f03a0 [AI]
		return "Act3Shark";
	}

	/**
	 * @brief [AI] Gets the timestamp or value representing current animation time progress or state. Usage is related to pizza eating animation.
	 * @return Value of member m_unk0x2c [AI]
	 */
	MxFloat GetUnknown0x2c() { return m_unk0x2c; }

	/**
	 * @brief [AI] Sets the timestamp or value representing animation progress/state.
	 * @param p_unk0x2c New value to set [AI]
	 */
	void SetUnknown0x2c(MxFloat p_unk0x2c) { m_unk0x2c = p_unk0x2c; }

	// SYNTHETIC: LEGO1 0x10043030 [AI]
	// Act3Shark::`scalar deleting destructor' [AI]

private:
	list<Act3Ammo*> m_eatPizzas;    ///< @brief [AI] FIFO queue of pizzas scheduled to be eaten/animated
	Act3Ammo* m_nextPizza;          ///< @brief [AI] Pointer to the next pizza to animate as eaten
	MxFloat m_unk0x2c;              ///< @brief [AI] Time for the start of the current pizza-eating animation [AI_SUGGESTED_NAME: pizzaEatStartTime]
	LegoWorld* m_world;             ///< @brief [AI] The parent world object the shark operates in
	LegoAnimActorStruct* m_unk0x34; ///< @brief [AI] Pointer to the shark's animation data structure [AI_SUGGESTED_NAME: eatAnimation]
	LegoROI* m_unk0x38;             ///< @brief [AI] ROI associated with the pizza effect (updated for visual state)
	Mx3DPointFloat m_unk0x3c;       ///< @brief [AI] Position of the pizza or animation target in world space
};

// VTABLE: LEGO1 0x100d7668 LegoPathActor [AI]
// VTABLE: LEGO1 0x100d7738 LegoAnimActor [AI]
// VTABLE: BETA10 0x101b8a98 LegoPathActor [AI]
// VTABLE: BETA10 0x101b8b88 LegoAnimActor [AI]
// SIZE 0x178 [AI]
/**
 * @brief [AI] Represents a generic animatable actor in Act 3, supporting path following and custom animation triggers.
 * 
 * Provides domain events for actor collision and transformation; forms the base for cops and the Brickster.
 */
class Act3Actor : public LegoAnimActor {
public:
	/**
	 * @brief [AI] Constructs a new Act3Actor, initializing state.
	 */
	Act3Actor();

	/**
	 * @brief [AI] Handles transformation updates for the actor. Involves state changes if various animation ticks are met.
	 * @param p_time Current simulation time [AI]
	 * @param p_transform Matrix to update with new transform [AI]
	 * @return TRUE if state transition occurred, otherwise FALSE [AI]
	 */
	MxU32 VTable0x90(float p_time, Matrix4& p_transform) override;     // vtable+0x90

	/**
	 * @brief [AI] Called when this actor is hit/collided by another actor, such as a projectile or another character.
	 * @param p_actor Actor that hit this one [AI]
	 * @param p_bool Whether the hit should be processed (i.e. only TRUE processes real hits) [AI]
	 * @return Resulting status (SUCCESS/FAILURE) [AI]
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/**
	 * @brief [AI] Returns the class name string for debugging/instancing.
	 * @return Always returns "Act3Actor" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03ac [AI]
		return "Act3Actor";
	}

	/**
	 * @brief [AI] Gets the custom time marker or value for animation/transformation logic.
	 * @return Value of member m_unk0x1c [AI]
	 */
	MxFloat GetUnknown0x1c() { return m_unk0x1c; }

	/**
	 * @brief [AI] Sets the custom time marker or value.
	 * @param p_unk0x1c New value to set [AI]
	 */
	void SetUnknown0x1c(MxFloat p_unk0x1c) { m_unk0x1c = p_unk0x1c; }

	// SYNTHETIC: LEGO1 0x10043330 [AI]
	// Act3Actor::`scalar deleting destructor' [AI]

	// SYNTHETIC: LEGO1 0x10040fa0 [AI]
	// Act3Actor::~Act3Actor [AI]

private:
	static Mx3DPointFloat g_unk0x10104ef0; ///< @brief [AI] Used for transforms/offset calculations (fixed offset vector for collision/landing spots etc.)

	MxFloat m_unk0x1c; ///< @brief [AI] State variable storing target time or animation progress for state switches
};

// VTABLE: LEGO1 0x100d7750 LegoPathActor [AI]
// VTABLE: LEGO1 0x100d7820 LegoAnimActor [AI]
// SIZE 0x188 [AI]
/**
 * @brief [AI] Represents a police officer actor in Act 3, supporting specific cop AI actions, path findings, and collision logic.
 * 
 * Cop actors seek donuts, can "eat" them, and interact with the Brickster for possible endings. Provides additional destination data for scene logic.
 */
class Act3Cop : public Act3Actor {
public:
	/**
	 * @brief [AI] Structure containing cop destination information for patrol paths, boundaries, and navigation points.
	 */
	struct Act3CopDest {
		const char* m_bName; ///< @brief [AI] Path boundary name used for seeking path destinations
		LegoPathBoundary* m_boundary; ///< @brief [AI] Cached pointer to the boundary object after resolving m_bName
		MxFloat m_unk0x08[3]; ///< @brief [AI] World coordinates for the destination or checkpoint [AI_SUGGESTED_NAME: destinationPos]
		MxFloat m_unk0x14[3]; ///< @brief [AI] Direction or reference vector for this destination [AI_SUGGESTED_NAME: destinationDir]
	};

	/**
	 * @brief [AI] Constructs a new police officer actor, initializing references and default patrol states.
	 */
	Act3Cop();

	/**
	 * @brief [AI] Parses incoming action command strings for cop-specific data and registers itself with the world, finding patrol destinations.
	 * @param p_extra Action string containing cop instructions [AI]
	 */
	void ParseAction(char* p_extra) override;           // vtable+0x20

	/**
	 * @brief [AI] Per-frame animation update, handles cop AI state switching to seek donuts, interact with Brickster or perform scene actions.
	 * @param p_time Current time in milliseconds [AI]
	 */
	void Animate(float p_time) override;                // vtable+0x70

	/**
	 * @brief [AI] Processes collision with another actor, especially for handling donut pickups and Brickster interaction.
	 * @param p_actor The actor that hit this cop [AI]
	 * @param p_bool Whether to process the hit [AI]
	 * @return Result of the hit event (success/failure) [AI]
	 */
	MxResult HitActor(LegoPathActor*, MxBool) override; // vtable+0x94

	/**
	 * @brief [AI] Performs path container recalculation for cop AI movement. Used for re-pathing after updates or state transitions.
	 * @return SUCCESS if update performed, otherwise base call [AI]
	 */
	MxResult VTable0x9c() override;                     // vtable+0x9c

	/**
	 * @brief [AI] Gets a cop-specific timer used for movement or eating actions.
	 * @return m_unk0x20 [AI]
	 */
	MxFloat GetUnknown0x20() { return m_unk0x20; }

	/**
	 * @brief [AI] Sets the cop timer for eating/movement delays.
	 * @param p_unk0x20 New timer value [AI]
	 */
	void SetUnknown0x20(MxFloat p_unk0x20) { m_unk0x20 = p_unk0x20; }

	/**
	 * @brief [AI] Triggers the cop to attempt to intercept or react to a thrown donut. Calls re-path finding if the AI logic requires.
	 * @param p_ammo Donut (Act3Ammo) being thrown/interacted with [AI]
	 * @param Vector3& Reference position for the action (destination) [AI]
	 * @return Result of the handling [AI]
	 */
	MxResult FUN_10040350(Act3Ammo& p_ammo, const Vector3&);

	/**
	 * @brief [AI] Internal: recalculates cop movement/path container target.
	 * @return SUCCESS if path found [AI]
	 */
	MxResult FUN_10040360();

	// SYNTHETIC: LEGO1 0x10043120 [AI]
	// Act3Cop::`scalar deleting destructor' [AI]

private:
	MxFloat m_unk0x20;  ///< @brief [AI] Cop timer for state transitions, e.g. donut eating or chasing [AI_SUGGESTED_NAME: eatDelayOrChaseTime]
	LegoWorld* m_world; ///< @brief [AI] Parent LEGO world reference
	LegoAnimActorStruct* m_eatAnim; ///< @brief [AI] Animation struct for the eating animation data [AI_SUGGESTED_NAME: eatAnim]
	undefined4 m_unk0x2c; ///< @brief [AI] Unknown, possibly animation or state variable
};

// VTABLE: LEGO1 0x100d7838 LegoPathActor [AI]
// VTABLE: LEGO1 0x100d7908 LegoAnimActor [AI]
// SIZE 0x1b4 [AI]
/**
 * @brief [AI] Represents the Brickster actor in Act 3, with AI and scene logic for stealing pizzas and causing endgame actions.
 * 
 * Handles AI for seeking pizzas/buildings, managing states and animations for "bad" outcomes, and shot/planted/scene logic.
 */
class Act3Brickster : public Act3Actor {
public:
	/**
	 * @brief [AI] Constructs a Brickster character, setting default animation and navigation state.
	 */
	Act3Brickster();

	/**
	 * @brief [AI] Frees Brickster resources, implemented for correct inheritance.
	 */
	~Act3Brickster() override;

	/**
	 * @brief [AI] Parses Brickster-specific commands from action strings; sets its world reference and triggers the correct animation set.
	 * @param p_extra String containing action info [AI]
	 */
	void ParseAction(char* p_extra) override;                          // vtable+0x20

	/**
	 * @brief [AI] Main logic for Brickster's per-frame AI behavior: handles pizza seeking, plant/building attacks, state transitions, and special cutscene triggers.
	 * @param p_time Current simulation time [AI]
	 */
	void Animate(float p_time) override;                               // vtable+0x70

	/**
	 * @brief [AI] Handles Brickster being hit by an actor (e.g., cop, pizza ammo), processes pizza counters and determines state transitions.
	 * @param p_actor Actor that hit the Brickster [AI]
	 * @param p_bool Should this hit be applied? [AI]
	 * @return SUCCESS or FAILURE depending on game logic [AI]
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/**
	 * @brief [AI] Switches navigation/path boundary for Brickster and updates edge and offset (stateful for when escaping or maneuvering cops).
	 * @param p_boundary Reference for updated path boundary [AI]
	 * @param p_edge Reference for updated edge [AI]
	 * @param p_unk0xe4 Reference for updated progress along the edge [-] [AI]
	 */
	void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	) override;                     // vtable+0x98

	/**
	 * @brief [AI] Handles AI updates post pathfinding/state transition recalculation.
	 * @return Result of recalculation (SUCCESS, else parent call) [AI]
	 */
	MxResult VTable0x9c() override; // vtable+0x9c

	/**
	 * @brief [AI] Gets a custom timer or marker for the Brickster state machine.
	 * @return m_unk0x20 [AI]
	 */
	MxFloat GetUnknown0x20() { return m_unk0x20; }
	/**
	 * @brief [AI] Gets another stateful marker (delays, cooldown, or pizza effect timer).
	 * @return m_unk0x24 [AI]
	 */
	MxFloat GetUnknown0x24() { return m_unk0x24; }
	/**
	 * @brief [AI] Gets the duration/target for building/plant attack animation.
	 * @return m_unk0x50 [AI]
	 */
	MxFloat GetUnknown0x50() { return m_unk0x50; }

	/**
	 * @brief [AI] Sets custom Brickster timers/markers (see getters).
	 * @param p_unk0x20 Value for m_unk0x20 [AI]
	 */
	void SetUnknown0x20(MxFloat p_unk0x20) { m_unk0x20 = p_unk0x20; }
	void SetUnknown0x24(MxFloat p_unk0x24) { m_unk0x24 = p_unk0x24; }
	void SetUnknown0x50(MxFloat p_unk0x50) { m_unk0x50 = p_unk0x50; }

	/**
	 * @brief [AI] Triggers the Brickster to react to a thrown pizza. Used for AI transitions when a pizza is received.
	 * @param p_ammo The pizza thrown/interacted with [AI]
	 * @param Vector3& Position reference for additional logic [AI]
	 * @return Result of handling [AI]
	 */
	MxResult FUN_100417a0(Act3Ammo& p_ammo, const Vector3&);

	/**
	 * @brief [AI] Recalculates Brickster's navigation to a new plant/building/target as dictated by AI logic.
	 * @return Result of the attempted recalculation [AI]
	 */
	MxResult FUN_100417c0();

	// SYNTHETIC: LEGO1 0x10043250 [AI]
	// Act3Brickster::`scalar deleting destructor' [AI]

private:
	/**
	 * @brief [AI] Internal: recalculates position relative to both cops for escape and cutscene logic.
	 * @return Always returns -1 [AI]
	 */
	MxS32 FUN_10042300();

	MxFloat m_unk0x20;                ///< @brief [AI] Timer or marker used for specific Brickster states (cooldowns/transition delays)
	MxFloat m_unk0x24;                ///< @brief [AI] Additional timer or event trigger (e.g. related to movement) [AI_SUGGESTED_NAME: secondaryTimer]
	LegoWorld* m_world;               ///< @brief [AI] Pointer to the game world context
	LegoPlantInfo* m_pInfo;           ///< @brief [AI] Points to current plant info if Brickster is attacking a plant [AI_SUGGESTED_NAME: targetPlant]
	LegoBuildingInfo* m_bInfo;        ///< @brief [AI] Building info if Brickster is attacking a building [AI_SUGGESTED_NAME: targetBuilding]
	LegoAnimActorStruct* m_shootAnim; ///< @brief [AI] Animation struct for the "shoot" (attack) animation on plant/building [AI_SUGGESTED_NAME: shootAnim]
	undefined4 m_unk0x38;             ///< @brief [AI] State indicator used to switch Brickster AI behaviors [AI_SUGGESTED_NAME: aiState]
	Mx3DPointFloat m_unk0x3c;         ///< @brief [AI] Last attacked/world coordinate for effects or nav
	MxFloat m_unk0x50;                ///< @brief [AI] Timer/marker for animation duration or next phase [AI_SUGGESTED_NAME: actionEndTime]
	MxFloat m_unk0x54;                ///< @brief [AI] Timer for event scheduling (e.g., scene/firing delay) [AI_SUGGESTED_NAME: delayUntilNextEvent]
	MxU8 m_unk0x58;                   ///< @brief [AI] Pizza eat counter for Brickster (limits AI state transitions)
};

// FUNCTION: LEGO1 0x1003ff10 [AI]
// Act3Actor::`vbase destructor' [AI]

// TEMPLATE: LEGO1 0x10042c20
// list<Act3Ammo *,allocator<Act3Ammo *> >::~list<Act3Ammo *,allocator<Act3Ammo *> > [AI]

// TEMPLATE: LEGO1 0x10042c90
// List<Act3Ammo *>::~List<Act3Ammo *> [AI]

// TEMPLATE: LEGO1 0x10042ee0
// list<Act3Ammo *,allocator<Act3Ammo *> >::erase [AI]

// GLOBAL: LEGO1 0x100d7660
// Act3Actor::`vbtable' [AI]

// GLOBAL: LEGO1 0x100d7748
// Act3Cop::`vbtable' [AI]

// GLOBAL: LEGO1 0x100d7830
// Act3Brickster::`vbtable' [AI]

// GLOBAL: LEGO1 0x100d7918
// Act3Shark::`vbtable' [AI]

#endif // ACT3ACTORS_H