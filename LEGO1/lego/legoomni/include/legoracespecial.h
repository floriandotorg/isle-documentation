#ifndef LEGOCARRACEACTOR_H
#define LEGOCARRACEACTOR_H

#include "legoraceactor.h"

/// @brief [AI] Global variable storing the name of the race state variable (used for checking or setting state within the race logic). [AI]
extern const char* g_raceState;

/// @brief [AI] Global variable storing the name of the fuel variable (used for managing the actor's fuel in gameplay logic). [AI]
extern const char* g_fuel;

/// @brief [AI] Global variable storing the name of the racing state (used to check if the race is currently ongoing). [AI]
extern const char* g_racing;

// VTABLE: LEGO1 0x100da0c0 LegoRaceActor
// VTABLE: LEGO1 0x100da0c8 LegoAnimActor
// VTABLE: LEGO1 0x100da0d8 LegoPathActor
// VTABLE: LEGO1 0x100da1a8 LegoCarRaceActor
// VTABLE: BETA10 0x101bea74 LegoRaceActor
// VTABLE: BETA10 0x101bea78 LegoAnimActor
// VTABLE: BETA10 0x101bea90 LegoPathActor
// VTABLE: BETA10 0x101beb80 LegoCarRaceActor
// SIZE 0x1a0

/// @brief [AI] Specialized actor class for car-based racing in LEGO Island racing sequences. Supports additional logic for acceleration, handling, and boundary switching during a race. [AI]
class LegoCarRaceActor : public virtual LegoRaceActor {
public:
	/// @brief [AI] Constructor, sets up initial movement parameters and starting variable values. [AI]
	LegoCarRaceActor();

	/// @brief [AI] Returns the class name for this actor type. [AI]
	/// @return [AI] "LegoCarRaceActor"
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0568
		return "LegoCarRaceActor";
	}

	/// @brief [AI] Checks if the object is a given class name (used for runtime type identification). [AI]
	/// @param p_name Class name to check. [AI]
	/// @return [AI] True for "LegoCarRaceActor", also queries parents. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoCarRaceActor::ClassName()) || LegoRaceActor::IsA(p_name);
	}

	/// @brief [AI] Performs collision detection and/or special logic while moving the car actor along a boundary. [AI]
	/// @param p_boundary Path boundary being tested. [AI]
	/// @param p_v1 World position vector (start). [AI]
	/// @param p_v2 World position vector (end). [AI]
	/// @param p_f1 First interpolation/scalar parameter. [AI]
	/// @param p_f2 Second interpolation/scalar parameter. [AI]
	/// @param p_v3 Output vector for collision/hit information. [AI]
	/// @details [AI] Used for boundary interaction logic with other animators or path actors.[AI]
	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;

	/// @brief [AI] Main per-frame update for the car racer, controls activation of animation and state switching based on global variable values. [AI]
	/// @param p_time The current time or frame tick. [AI]
	void Animate(float p_time) override;

	/// @brief [AI] Handles switching from one path boundary to another, updating relevant edge and position parameters. [AI]
	/// @param p_boundary Reference to the new boundary pointer (for updating). [AI]
	/// @param p_edge Reference to the new edge pointer (for updating). [AI]
	/// @param p_unk0xe4 Reference to the lerp parameter (for updating position along the edge). [AI]
	void SwitchBoundary(LegoPathBoundary*& p_boundary, LegoUnknown100db7f4*& p_edge, float& p_unk0xe4)
		override;

	/// @brief [AI] Handles the transition at key animation logic points, such as the end/start of edges and boundaries. Calls boundary/edge switch and path logic. [AI]
	/// @return [AI] Returns SUCCESS after state check and potential state transitions. [AI]
	MxResult VTable0x9c() override;

	// LegoCarRaceActor vtable

	/// @brief [AI] Adjusts the target and acceleration for the car based on path, player position, and time step. [AI]
	/// @param p_time Current time/frame value to inform logic for acceleration and speed adjustment. [AI]
	virtual void FUN_10080590(float p_time); // vtable+0x00

	/// @brief [AI] Sets the car acceleration or acceleration-related value. [AI]
	/// @param p_unk0x14 New acceleration/related parameter. [AI]
	virtual void FUN_10012bb0(float p_unk0x14) { m_unk0x14 = p_unk0x14; } // vtable+0x04

	/// @brief [AI] Returns the current value of the acceleration or acceleration-related parameter. [AI]
	virtual float FUN_10012bc0() { return m_unk0x14; } // vtable+0x08

	/// @brief [AI] Sets a parameter likely related to speed multipliers when going straight. [AI]
	/// @param p_unk0x10 New parameter value. [AI]
	virtual void FUN_10012bd0(float p_unk0x10) { m_unk0x10 = p_unk0x10; } // vtable+0x0c

	/// @brief [AI] Returns the current value of the straight path speed multiplier parameter. [AI]
	virtual float FUN_10012be0() { return m_unk0x10; } // vtable+0x10

	/// @brief [AI] Sets a parameter likely affecting dynamic velocity or similar adjustment factor. [AI]
	/// @param p_unk0x18 New value for the parameter. [AI]
	virtual void FUN_10012bf0(float p_unk0x18) { m_unk0x18 = p_unk0x18; } // vtable+0x14

	/// @brief [AI] Retrieves the current value of the velocity-related/dynamic adjustment parameter. [AI]
	virtual float FUN_10012c00() { return m_unk0x18; } // vtable+0x18

	/// @brief [AI] Handles logic for state transitions at control edges, updating actor state if needed based on path position. [AI]
	/// @param p_boundary The current boundary being traversed. [AI]
	/// @param p_edge The current or upcoming path edge for transition. [AI]
	/// @return [AI] 0 or 1 depending on transition result. [AI]
	virtual MxS32 VTable0x1c(LegoPathBoundary* p_boundary, LegoEdge* p_edge);

	// SYNTHETIC: LEGO1 0x10012c30
	// LegoCarRaceActor::`vbase destructor'

	// SYNTHETIC: LEGO1 0x10081620
	// LegoCarRaceActor::`scalar deleting destructor'

	// SYNTHETIC: LEGO1 0x10012d80
	// LegoCarRaceActor::~LegoCarRaceActor

protected:
	MxFloat m_unk0x08; ///< @brief [AI] Used for initial movement adjustment or normalization; always set to 1.0f in constructor. [AI]
	MxU8 m_unk0x0c;    ///< @brief [AI] State variable/fsm controlling the actor's current animation/logic state. [AI]

	/// @brief [AI] Likely a multiplier for maximum speed when on a straight portion of the track. [AI_SUGGESTED_NAME: m_straightSpeedMultiplier]
	MxFloat m_unk0x10;

	/// @brief [AI] Could represent car acceleration or change-in-speed envelope. [AI_SUGGESTED_NAME: m_acceleration]
	MxFloat m_unk0x14;

	MxFloat m_unk0x18; ///< @brief [AI] General movement/velocity adjustment parameter, possibly for handling or group speed adjustment. [AI]

	/// @brief [AI] Used for storing timestamps for time-based actor movement updates. [AI_SUGGESTED_NAME: m_lastUpdateTimestamp]
	MxFloat m_unk0x1c;

	/// @brief [AI] Static value used as a global reference for minimum or target speed under specific circumstances. [AI]
	static MxFloat g_unk0x100f7aec;
};

// VTABLE: LEGO1 0x100da208 LegoCarRaceActor
// VTABLE: LEGO1 0x100da228 LegoRaceActor
// VTABLE: LEGO1 0x100da230 LegoAnimActor
// VTABLE: LEGO1 0x100da240 LegoPathActor
// VTABLE: BETA10 0x101bd348 LegoCarRaceActor
// VTABLE: BETA10 0x101bd370 LegoRaceActor
// VTABLE: BETA10 0x101bd378 LegoAnimActor
// VTABLE: BETA10 0x101bd390 LegoPathActor
// SIZE 0x1a8

/// @brief [AI] A racing actor subclass representing jetski (water-based) vehicles. Modifies car parameters and control logic for water-based racing. [AI]
class LegoJetskiRaceActor : public virtual LegoCarRaceActor {
public:
	/// @brief [AI] Constructor initializing jetski movement and acceleration parameters. [AI]
	LegoJetskiRaceActor();

	/// @brief [AI] Returns the class name for this actor type. [AI]
	/// @return [AI] "LegoJetskiRaceActor"
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0554
		return "LegoJetskiRaceActor";
	}

	/// @brief [AI] Checks if the object is a given class name (used for runtime type identification). [AI]
	/// @param p_name Class name to check. [AI]
	/// @return [AI] True for "LegoJetskiRaceActor", also queries parents. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoJetskiRaceActor::ClassName()) || LegoCarRaceActor::IsA(p_name);
	}

	/// @brief [AI] Collision and path interaction routine specialized for jetski actors. [AI]
	/// @param p_boundary Path boundary being traversed. [AI]
	/// @param p_v1 World position vector (start). [AI]
	/// @param p_v2 World position vector (end). [AI]
	/// @param p_f1 First interpolation/scalar parameter. [AI]
	/// @param p_f2 Second interpolation/scalar parameter. [AI]
	/// @param p_v3 Output vector for collision/hit information. [AI]
	/// @details [AI] Used for per-frame boundary collision, presenter and actor interaction. [AI]
	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;

	/// @brief [AI] Per-frame logic and animation for jetski racing - enables racing state and syncs with variables. [AI] 
	void Animate(float p_time) override;

	/// @brief [AI] Handles state transitions for jetski racing at control edges or waterway turns. [AI]
	/// @param p_boundary Current path boundary traversed. [AI]
	/// @param p_edge Current or upcoming path edge for transition. [AI]
	/// @return [AI] 0 or 1 depending on transition result. [AI]
	MxS32 VTable0x1c(LegoPathBoundary* p_boundary, LegoEdge* p_edge) override;

	// SYNTHETIC: LEGO1 0x10013a80
	// LegoJetskiRaceActor::`vbase destructor'

	// SYNTHETIC: LEGO1 0x10081d50
	// LegoJetskiRaceActor::`scalar deleting destructor'

	// SYNTHETIC: LEGO1 0x10013ba0
	// LegoJetskiRaceActor::~LegoJetskiRaceActor
};

// GLOBAL: LEGO1 0x100da0b0
// LegoCarRaceActor::`vbtable'

// GLOBAL: LEGO1 0x100da0a8
// LegoCarRaceActor::`vbtable'{for `LegoAnimActor'}

// GLOBAL: LEGO1 0x100da098
// LegoCarRaceActor::`vbtable'{for `LegoRaceActor'}

// GLOBAL: LEGO1 0x100da1f0
// LegoJetskiRaceActor::`vbtable'{for `LegoJetskiRaceActor'}

// GLOBAL: LEGO1 0x100da1e8
// LegoJetskiRaceActor::`vbtable'{for `LegoAnimActor'}

// GLOBAL: LEGO1 0x100da1d8
// LegoJetskiRaceActor::`vbtable'{for `LegoRaceActor'}

// GLOBAL: LEGO1 0x100da1c8
// LegoJetskiRaceActor::`vbtable'{for `LegoCarRaceActor'}

#endif // LEGOCARRACEACTOR_H