#ifndef LEGORACERS_H
#define LEGORACERS_H

// clang-format off
#include "legoracespecial.h"
// clang-format on
#include "legoracemap.h"

/**
 * @def LEGORACECAR_UNKNOWN_0
 * @brief [AI] User state identifier for LegoRaceCar (unknown purpose—likely "neutral/idle").
 */
#define LEGORACECAR_UNKNOWN_0 0

/**
 * @def LEGORACECAR_UNKNOWN_1
 * @brief [AI] User state identifier for LegoRaceCar (unknown purpose—likely "in kick/transition state").
 */
#define LEGORACECAR_UNKNOWN_1 1

/**
 * @def LEGORACECAR_KICK1
 * @brief [AI] User state identifier for LegoRaceCar in "kick1" action/animation state.
 */
#define LEGORACECAR_KICK1 2 // name guessed

/**
 * @def LEGORACECAR_KICK2
 * @brief [AI] User state identifier for LegoRaceCar in "kick2" action/animation state.
 */
#define LEGORACECAR_KICK2 4 // name validated by BETA10 0x100cb659

/**
 * @struct EdgeReference
 * @brief [AI] Associates a named edge (string) to a LegoPathBoundary, used within skeleton kick phases to assign kick behavior to boundaries.
 * @details [AI] Used in race car skeleton kick logic to reference specific path boundaries by name for triggering animations or actions.
 */
struct EdgeReference {
	const char* m_name; ///< @brief [AI] Name of the edge to be resolved to an actual boundary in the current world instance.
	LegoPathBoundary* m_b; ///< @brief [AI] Boundary pointer; set to NULL until mapped by ParseAction or similar initialization.
};

/**
 * @struct SkeletonKickPhase
 * @brief [AI] Represents a phase of the skeleton kick animation/action, delimiting animation intervals along a boundary.
 * @details [AI] Used in LegoRaceCar logic to determine when to switch user state based on animation progress.
 */
struct SkeletonKickPhase {
	EdgeReference* m_edgeRef; ///< @brief [AI] Pointer to the EdgeReference describing which boundary this phase is associated with.
	float m_lower;            ///< @brief [AI] Lower normalized bound of animation phase where this skeleton kick is applicable. (Fraction, e.g., 0.1)
	float m_upper;            ///< @brief [AI] Upper normalized bound of animation phase where this skeleton kick is applicable. (Fraction, e.g., 0.2)
	MxU8 m_userState;         ///< @brief [AI] State to switch to if currently within this phase. LEGORACECAR_KICK1 or LEGORACECAR_KICK2.
};

/**
 * @class LegoJetski
 * @brief [AI] Represents a Jetski actor in the race, combining behavior from LegoJetskiRaceActor and LegoRaceMap.
 * @details [AI] Handles custom world speed, animation phases, boundary switching, hit logic, and event notification within Jetski races.
 */
class LegoJetski : public LegoJetskiRaceActor, public LegoRaceMap {
public:
	LegoJetski();
	~LegoJetski() override;

	/**
	 * @brief [AI] Processes notifications/events for the LegoJetski instance (see MxCore).
	 * @param p_param [AI] Notification parameters (engine event details).
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns the runtime class name ("LegoJetski").
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoJetski";
	}

	/**
	 * @brief [AI] Determines if this object is of the given class type or derives from it.
	 * @param p_name [AI] Name string of the class to check.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoJetski::ClassName()) || LegoJetskiRaceActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Parses an action string to configure or trigger Jetski behaviors such as switching race boundaries.
	 * @param p_extra [AI] Null-terminated string with action parameters/commands.
	 */
	void ParseAction(char* p_extra) override;          // vtable+0x20

	/**
	 * @brief [AI] Sets world speed for the jetski, influencing both physics and animation logic.
	 * @param p_worldSpeed [AI] Target world speed.
	 */
	void SetWorldSpeed(MxFloat p_worldSpeed) override; // vtable+0x30

	/**
	 * @brief [AI] Thin override that delegates path boundary-related animation calculation to base implementation.
	 * @param p_boundary [AI] Path boundary reference.
	 * @param p_v1 [AI] Vector parameter 1 (animation context).
	 * @param p_v2 [AI] Vector parameter 2 (animation context).
	 * @param p_f1 [AI] Float param 1 (animation context).
	 * @param p_f2 [AI] Float param 2 (animation context).
	 * @param p_v3 [AI] Vector parameter 3 (animation context).
	 * @details [AI] Used for advanced animation steering—see base classes.
	 */
	MxU32 VTable0x6c(LegoPathBoundary* p_boundary, Vector3& p_v1, Vector3& p_v2, float p_f1, float p_f2, Vector3& p_v3)
		override
	{
		return LegoJetskiRaceActor::VTable0x6c(p_boundary, p_v1, p_v2, p_f1, p_f2, p_v3);
	} // vtable+0x6c

	/**
	 * @brief [AI] Updates jetski animation for the current frame.
	 * @param p_time [AI] The time at which to evaluate animation.
	 */
	void Animate(float p_time) override;                               // vtable+0x70

	/**
	 * @brief [AI] Handles collision/hit logic between this jetski and another race actor.
	 * @param p_actor [AI] Actor with which the collision is detected.
	 * @param p_bool [AI] Hit context (usually whether the actor was hit by the player or vice versa).
	 * @details [AI] Handles sound playback, user state change and collision response.
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/**
	 * @brief [AI] Switches the current boundary and tracking edge based on race logic.
	 * @param p_boundary [AI] Boundary to switch to.
	 * @param p_edge [AI] Edge to switch to.
	 * @param p_unk0xe4 [AI] Additional tracking parameter (purpose unclear).
	 */
	void SwitchBoundary(LegoPathBoundary*& p_boundary, LegoUnknown100db7f4*& p_edge, float& p_unk0xe4) override
	{
		LegoJetskiRaceActor::SwitchBoundary(p_boundary, p_edge, p_unk0xe4);
	} // vtable+0x98

	/**
	 * @brief [AI] Used for post-animation logic (purpose inferred as clean up or ready-check; see base classes).
	 */
	MxResult VTable0x9c() override { return LegoJetskiRaceActor::VTable0x9c(); } // vtable+0x9c

	/**
	 * @brief [AI] Custom world speed handler for clamping or setting maximum velocity for the jetski.
	 * @param p_worldSpeed [AI] The world speed value to set.
	 */
	virtual void FUN_100136f0(float p_worldSpeed);

	/**
	 * @brief [AI] Initializes static indices for jetski-specific sound arrays to randomized starting positions.
	 */
	static void InitSoundIndices();

	// SYNTHETIC: LEGO1 0x10013e30
	// LegoJetski::`scalar deleting destructor'
};


/**
 * @class LegoRaceCar
 * @brief [AI] Represents a Race Car actor in the game, combining advanced pathing, skeleton kick logic, event and animation handling.
 * @details [AI] Handles user-controlled and AI-controlled racing car logic, including boundary handling, multi-phase animation, sound management, and rich notification integration.
 */
class LegoRaceCar : public LegoCarRaceActor, public LegoRaceMap {
public:
	LegoRaceCar();
	~LegoRaceCar() override;

	/**
	 * @brief [AI] Processes notifications/events for the LegoRaceCar (see MxCore).
	 * @param p_param [AI] Notification parameters (engine event details).
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns the runtime class name ("LegoRaceCar").
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoRaceCar";
	}

	/**
	 * @brief [AI] Determines if this object is of the given class type or derives from it.
	 * @param p_name [AI] Name string of the class to check.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoRaceCar::ClassName()) || LegoCarRaceActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Parses an action string to configure or trigger car behaviors (e.g., updates kick animation references).
	 * @param p_extra [AI] Null-terminated string with action info.
	 * @details [AI] Sets up skeleton kick animations and path boundaries if controlled by the user.
	 */
	void ParseAction(char* p_extra) override;          // vtable+0x20

	/**
	 * @brief [AI] Sets world speed for the race car, either for user nav or animation context.
	 * @param p_worldSpeed [AI] New speed to apply.
	 */
	void SetWorldSpeed(MxFloat p_worldSpeed) override; // vtable+0x30

	/**
	 * @brief [AI] Delegates advanced animation calculation to base class; see base for logic.
	 * @param p_boundary [AI]
	 * @param p_v1 [AI]
	 * @param p_v2 [AI]
	 * @param p_f1 [AI]
	 * @param p_f2 [AI]
	 * @param p_v3 [AI]
	 */
	MxU32 VTable0x6c(LegoPathBoundary* p_boundary, Vector3& p_v1, Vector3& p_v2, float p_f1, float p_f2, Vector3& p_v3)
		override
	{
		return LegoCarRaceActor::VTable0x6c(p_boundary, p_v1, p_v2, p_f1, p_f2, p_v3);
	} // vtable+0x6c

	/**
	 * @brief [AI] Main animation tick function; handles skeleton kick special states when user-controlled.
	 * @param p_time [AI] Animation time.
	 * @details [AI] Handles engine sound effects, speed/RPM variable calculation and "can't stop" nag sound playback.
	 */
	void Animate(float p_time) override;                               // vtable+0x70

	/**
	 * @brief [AI] Handles player/AI actor collision—score, animation, and sound effects, as well as respawn logic for targeted actors.
	 * @param p_actor [AI] Other actor involved in the collision.
	 * @param p_bool [AI] Whether the collision was initiated by this car.
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/**
	 * @brief [AI] Delegates boundary/edge switch operation to base race car logic.
	 * @param p_boundary [AI]
	 * @param p_edge [AI]
	 * @param p_unk0xe4 [AI]
	 */
	void SwitchBoundary(LegoPathBoundary*& p_boundary, LegoUnknown100db7f4*& p_edge, float& p_unk0xe4) override
	{
		LegoCarRaceActor::SwitchBoundary(p_boundary, p_edge, p_unk0xe4);
	} // vtable+0x98

	/**
	 * @brief [AI] Finalizes animation phase/post-kick state machine.
	 * @details [AI] Handles advanced state reset on boundary change or skeleton kick animation phase switching.
	 */
	MxResult VTable0x9c() override; // vtable+0x9c

	/**
	 * @brief [AI] Sets the maximum linear velocity the car is allowed to attain (and can force 0 for "despawn" effect).
	 * @param p_maxLinearVelocity [AI] Maximum speed, or negative for reset/stop.
	 */
	virtual void SetMaxLinearVelocity(float p_maxLinearVelocity);

	/**
	 * @brief [AI] Handles skeleton kick transition logic for given time; switches state as needed.
	 * @param p_param [AI] Animation/current time.
	 */
	virtual void FUN_10012ff0(float p_param);

	/**
	 * @brief [AI] Handles transition between skeleton kick phases based on animation time and current boundary.
	 * @param p_param1 [AI] Animation/current time.
	 * @return [AI] TRUE if a skeleton kick phase was detected/handled, else FALSE (if out of phase).
	 */
	virtual MxU32 HandleSkeletonKicks(float p_param1);

	/**
	 * @brief [AI] Resets static sound state variables for the car (last sound time, stopped flag, etc).
	 */
	static void FUN_10012de0();

	/**
	 * @brief [AI] Initializes sound playback array indices for collision sounds to randomized values.
	 */
	static void InitSoundIndices();

	// SYNTHETIC: LEGO1 0x10014240
	// LegoRaceCar::`scalar deleting destructor'

private:
	undefined m_userState;    ///< @brief [AI] Current skeleton kick/user state identifier (see LEGORACECAR_* flags).
	float m_unk0x58;          ///< @brief [AI] Last animation time parameter used in skeleton kick phase logic.
	Mx3DPointFloat m_unk0x5c; ///< @brief [AI] Helper vector (possibly offset/reuse in respawn/collision logic).
	LegoAnimActorStruct* m_skelKick1Anim; ///< @brief [AI] Animation data struct for skeleton kick phase 1.
	LegoAnimActorStruct* m_skelKick2Anim; ///< @brief [AI] Animation data struct for skeleton kick phase 2.
	LegoPathBoundary* m_kick1B; ///< @brief [AI] Path boundary reference for kick phase 1.
	LegoPathBoundary* m_kick2B; ///< @brief [AI] Path boundary reference for kick phase 2.
};

#endif // LEGORACERS_H
