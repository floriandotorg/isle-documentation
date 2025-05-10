#ifndef LEGOEXTRAACTOR_H
#define LEGOEXTRAACTOR_H

#include "legoanimactor.h"

// VTABLE: LEGO1 0x100d6c00 LegoAnimActor
// VTABLE: LEGO1 0x100d6c10 LegoPathActor
// VTABLE: LEGO1 0x100d6cdc LegoExtraActor
// VTABLE: BETA10 0x101bc2a0 LegoAnimActor
// VTABLE: BETA10 0x101bc2b8 LegoPathActor
// VTABLE: BETA10 0x101bc3a8 LegoExtraActor
// SIZE 0x1dc

/**
 * @brief Represents a special actor in the world with additional animation state machines and complex interactions.
 * [AI]
 * 
 * This class extends LegoAnimActor and adds extra animation states and transitions triggered by collisions
 * or scripted events, supporting alternate animation tracks such as "disassembly" and "assembly".
 * Used for breakable or multi-state objects/characters in the world.
 * [AI]
 */
class LegoExtraActor : public virtual LegoAnimActor {
public:
	/**
	 * @brief Used to specify the axis for orientation or effect direction during animation or collision. [AI]
	 */
	enum Axis {
		e_posz, ///< +Z axis [AI]
		e_negz, ///< -Z axis [AI]
		e_posx, ///< +X axis [AI]
		e_negx  ///< -X axis [AI]
	};

	/**
	 * @brief Constructs a LegoExtraActor with default state and null animation references. [AI]
	 */
	LegoExtraActor();

	/**
	 * @brief Destructor, cleans up allocated animation structures. [AI]
	 */
	~LegoExtraActor() override;

	/**
	 * @brief Returns the class name as "LegoExtraActor". Used for runtime type checks and introspection. [AI]
	 * @return Name string of this class. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief Checks if the provided type name matches this class or any parent class. [AI]
	 * @param p_name Type name string to check. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief Sets the world speed for this actor, factoring in its current animation/interaction state.
	 * If the current animation is at rest and speed is set positive, transitions to an active state. [AI]
	 * @param p_worldSpeed Target world speed value. [AI]
	 */
	void SetWorldSpeed(MxFloat p_worldSpeed) override;                                  // vtable+0x30

	/**
	 * @brief (Inherited implementation) Delegates edge update logic to LegoPathActor. [AI]
	 * @param p_point1 Point parameter for edge. [AI]
	 * @param p_point2 Point parameter for edge. [AI]
	 * @param p_point3 Point parameter for edge. [AI]
	 * @return S32 result on edge-tick operation. [AI]
	 */
	MxS32 VTable0x68(Vector3& p_point1, Vector3& p_point2, Vector3& p_point3) override; // vtable+0x68

	/**
	 * @brief Tests for and handles collision with other path actors during simulation.
	 * Checks both animated presenters and actor boundaries for potential collisions, triggers HitActor and animation state transitions where appropriate.
	 * @param p_boundary The path boundary to check against. [AI]
	 * @param p_v1 Origin vector. [AI]
	 * @param p_v2 Velocity vector. [AI]
	 * @param p_f1 Animation/collision t-min. [AI]
	 * @param p_f2 Animation/collision t-max. [AI]
	 * @param p_v3 Out parameter for impact point. [AI]
	 * @return 0: No collision, 1: presenter collision, 2: actor collision (with state changes) [AI]
	 */
	inline MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	) override;                                                        // vtable+0x6c

	/**
	 * @brief Performs animation updates for the actor, handling alternate animations and transitions after collisions or scripted triggers. [AI]
	 * @param p_time Simulation time or animation tick. [AI]
	 */
	void Animate(float p_time) override;                               // vtable+0x70

	/**
	 * @brief Updates object transformation if special animation is not active, otherwise delegates to parent class.
	 * Used for position/orientation updates. [AI]
	 * @param p_transform Output transform matrix. [AI]
	 */
	void VTable0x74(Matrix4& p_transform) override;                    // vtable+0x74

	/**
	 * @brief Core animation & state tick: handles scheduled events (e.g., switching state after timed delay post-collision) and applies transforms/animations.
	 * Triggers rotation and deactivation/reactivation. [AI]
	 * @param p_time Current time. [AI]
	 * @param p_matrix Transform matrix to apply. [AI]
	 * @return 1 if state transition occurs, 0 otherwise. [AI]
	 */
	MxU32 VTable0x90(float p_time, Matrix4& p_matrix) override;        // vtable+0x90

	/**
	 * @brief Processes a collision ("hit") with another actor, updating internal animation state and triggering sound effects as needed.
	 * Handles special collision/animation scheduling for breaking/assembling objects. [AI]
	 * @param p_actor The colliding actor. [AI]
	 * @param p_bool TRUE for direct hit, FALSE for overlap. [AI]
	 * @return SUCCESS or FAILURE, depending on whether further collision/animation is allowed. [AI]
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/**
	 * @brief Called when crossing path boundaries, manages transitions to special in-between animation states and disables movement as needed.
	 * If interaction is ongoing (e.g., post-collision), animates "frozen" state until boundary-relation changes. [AI]
	 * @return Result of the base class boundary-crossing logic. [AI]
	 */
	MxResult VTable0x9c() override;                                    // vtable+0x9c

	/**
	 * @brief Determines secondary state outputs for randomization or specific internal state flags, used for controlling sub-logic for the extra actor.
	 * @param p_und1 Output: BOOL result for a given in-state. [AI]
	 * @param p_und2 Output: Int branch or random result depending on state. [AI]
	 */
	void VTable0xa4(MxBool& p_und1, MxS32& p_und2) override;           // vtable+0xa4

	/**
	 * @brief Handles special cleanup or reset behavior for extra actors, often related to secondary animation state. [AI]
	 */
	void VTable0xc4() override;                                        // vtable+0xc4

	/**
	 * @brief Handles boundary edge changes and swapping the actor's edge, updating direction and orientation accordingly.
	 * Used when actor needs to switch to another path edge (i.e., after collision or path completion).
	 * @return Always SUCCESS. [AI]
	 */
	virtual MxResult FUN_1002aae0();

	/**
	 * @brief Checks whether this actor's previous boundary was "blocked" and re-enables movement if allowed; called after animation freeze at boundary. [AI]
	 */
	void Restart();

	/**
	 * @brief Loads or assigns the alternate ("assembly" and "disassembly") animations to this actor as needed.
	 * Called on-demand when state changes require new animations. [AI]
	 */
	inline void FUN_1002ad8a();

	/**
	 * @brief Sets the internal unknown flag (possible randomization/collision state controller). [AI]
	 * @param p_unk0x0c Value to set. [AI]
	 */
	void SetUnknown0x0c(undefined p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

	// SYNTHETIC: LEGO1 0x1002b760
	// LegoExtraActor::`scalar deleting destructor'

private:
	/**
	 * @brief Time until which a scheduled event (such as an animation transition or delay) is set to occur.[AI]
	 */
	MxFloat m_scheduledTime;        // 0x08 [AI]

	/**
	 * @brief Unknown flag, possibly controls some randomization or animation sub-state. [AI]
	 */
	undefined m_unk0x0c;            // 0x0c [AI]

	/**
	 * @brief Stores which axis is currently affected (collision, rotation or transform axis). [AI]
	 */
	MxU8 m_axis;                    // 0x0d [AI]

	/**
	 * @brief Unknown, appears to store a "frozen" or "waiting" animation state for event completion. [AI]
	 */
	undefined m_unk0x0e;            // 0x0e [AI]

	/**
	 * @brief Stores the previous world speed, used when recovering from an animated "frozen" state.[AI]
	 */
	MxFloat m_prevWorldSpeed;       // 0x10 [AI]

	/**
	 * @brief Indicates which alternate animation (0=none, 1=disassembly, 2=assembly) is active. [AI]
	 */
	MxU8 m_whichAnim;               // 0x14 [AI]

	/**
	 * @brief Internal collision/animation timer counter, decremented each frame when active. [AI]
	 */
	MxU8 m_unk0x15;                 // 0x15 [AI]

	/**
	 * @brief Stores transform matrix for restoring world position/orientation after special animations finish. [AI]
	 */
	MxMatrix m_unk0x18;             // 0x18 [AI]

	/**
	 * @brief Pointer to the "assembly" animation data structure (may be lazily loaded). [AI]
	 */
	LegoAnimActorStruct* m_assAnim; // 0x60 [AI]

	/**
	 * @brief Pointer to the "disassembly/destruction" animation data (may be lazily loaded). [AI]
	 */
	LegoAnimActorStruct* m_disAnim; // 0x64 [AI]
};

// GLOBAL: LEGO1 0x100d6be8
// LegoExtraActor::`vbtable'{for `LegoAnimActor'}

// GLOBAL: LEGO1 0x100d6bf0
// LegoExtraActor::`vbtable'{for `LegoExtraActor'}

// TEMPLATE: LEGO1 0x1002b200
// vector<unsigned char *,allocator<unsigned char *> >::vector<unsigned char *,allocator<unsigned char *> >

// TEMPLATE: LEGO1 0x1002b270
// vector<unsigned char *,allocator<unsigned char *> >::size

// TEMPLATE: LEGO1 0x1002b720
// ?uninitialized_copy@@YAPAPAEPAPAE00@Z

#endif // LEGOEXTRAACTOR_H
