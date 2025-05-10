#ifndef LEGORACEACTOR_H
#define LEGORACEACTOR_H

#include "legoanimactor.h"

class Matrix4;

// VTABLE: LEGO1 0x100d5b78 LegoAnimActor
// VTABLE: LEGO1 0x100d5b88 LegoPathActor
// VTABLE: LEGO1 0x100d5c54 LegoRaceActor
// VTABLE: BETA10 0x101be380 LegoAnimActor
// VTABLE: BETA10 0x101be398 LegoPathActor
// VTABLE: BETA10 0x101be488 LegoRaceActor
// SIZE 0x180

/**
 * @brief [AI] Represents an actor that participates in races (usually vehicles or racers) on LEGO Island.
 * @details [AI] This is a specialized subclass of LegoAnimActor with race-specific logic for collisions and state machine,
 * providing interaction logic (such as hitting other race actors), animation control, and managing a special race state timer. 
 * Used in the race mini-games or missions to handle additional race state and transitions. [AI]
 */
class LegoRaceActor : public virtual LegoAnimActor {
public:
	/**
	 * @brief [AI] Constructor for the LegoRaceActor class.
	 * @details [AI] Initializes the actor, including its race-specific timer and state values. [AI]
	 */
	LegoRaceActor();

	/**
	 * @brief [AI] Returns the runtime class name for this class.
	 * @return The string literal "LegoRaceActor". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0bf4
		return "LegoRaceActor";
	}

	/**
	 * @brief [AI] Determines whether this object is of a class with a given name.
	 * @param p_name The class name to compare against. [AI]
	 * @return True if p_name matches this class or any parent class; otherwise, false. [AI]
	 * @details [AI] Supports dynamic type checking by name down the inheritance hierarchy. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoRaceActor::ClassName()) || LegoAnimActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles collision/interaction queries between the actor and the environment or other actors.
	 * @param p_v1 Vector for position or collision input/output. [AI]
	 * @param p_v2 Vector for position or collision input/output. [AI]
	 * @param p_v3 Vector for position or collision input/output. [AI]
	 * @return Result code indicating success or details of the outcome. [AI]
	 * @details [AI] This override implements additional logic for race actor-specific feedback, such as playing a hit sound
	 * if the user is controlling the actor and a collision occurs, using a timer to avoid repeated sound triggers. [AI]
	 */
	MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3) override; // vtable+0x68

	/**
	 * @brief [AI] Updates the actor's state and transformation for a given simulation time.
	 * @param p_time Simulation time (may be in milliseconds or arbitrary ticks). [AI]
	 * @param p_matrix Transformation matrix representing the actor's pose. [AI]
	 * @return Status flag indicating completion or continuation of the current animation/state. [AI]
	 * @details [AI] This method implements a small state machine: after certain interactions, e.g. a hit, it enters a timed 
	 * spin or stun state, updating position or transformation over time, and restores normal behavior when the time elapses. [AI]
	 */
	MxU32 VTable0x90(float p_time, Matrix4& p_matrix) override;             // vtable+0x90

	/**
	 * @brief [AI] Handles logic when this actor is hit by another actor (e.g., collision interaction).
	 * @param p_actor The other actor involved in the collision. [AI]
	 * @param p_bool Whether to trigger the actual hit/state change (vs. just a check). [AI]
	 * @return Result status indicating if the operation succeeded or failed. [AI]
	 * @details [AI] Performs additional logic if the hit actor is in an idle state; updates both actors' positions and states,
	 * including moving the hit actor slightly and transitioning it into a "stunned" or "pushed" state. [AI]
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override;      // vtable+0x94

	/**
	 * @brief [AI] Additional race-specific behavior stub.
	 * @return Result code (always returns success in current implementation). [AI]
	 * @details [AI] This placeholder function exists for future race interaction logic and is called in some code paths. [AI]
	 */
	virtual MxResult FUN_10014aa0();

	// SYNTHETIC: LEGO1 0x10012c10
	// LegoRaceActor::`vbase destructor'

	// SYNTHETIC: LEGO1 0x10014ac0
	// LegoRaceActor::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Time marker or timer for race-specific state transitions (e.g., stun/spin until this time).
	 * @details [AI] Used to track how long the actor remains in a post-collision (e.g., hit) state before resuming normal activity. [AI]
	 */
	MxFloat m_unk0x08; // 0x08

	/**
	 * @brief [AI] Race interaction offset or vector constant for hit separation/movement. [AI]
	 * @details [AI] Used when an actor is hit—provides the Z offset applied after collision. [AI]
	 */
	static Mx3DPointFloat g_unk0x10102b08;
};

// GLOBAL: LEGO1 0x100d5b68
// LegoRaceActor::`vbtable'{for `LegoRaceActor'}

// GLOBAL: LEGO1 0x100d5b60
// LegoRaceActor::`vbtable'{for `LegoAnimActor'}

#endif // LEGORACEACTOR_H
