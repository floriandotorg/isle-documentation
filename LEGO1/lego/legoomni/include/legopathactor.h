#ifndef LEGOPATHACTOR_H
#define LEGOPATHACTOR_H

#include "legoactor.h"
#include "misc/legounknown.h"
#include "mxtypes.h"

struct LegoEdge;
struct LegoNamedPlane;
class LegoPathBoundary;
class LegoPathController;
struct LegoPathEdgeContainer;
struct LegoUnknown100db7f4;
class LegoWEEdge;

extern MxLong g_unk0x100f3308; ///< @brief [AI] Timer for wall hit sound playback throttling in navigation [AI]
extern const char* g_strHIT_WALL_SOUND; ///< @brief [AI] Variable table name for the wall hit sound [AI]

/**
 * @class LegoPathActor
 * @brief [AI] An actor that moves along a predefined path, supporting boundary transitions, navigation and collisions.
 * 
 * This class represents an actor that follows a path within the world, controlled either by the user or by AI. It manages interaction with path boundaries, position interpolation and collision with geometry or other path actors. It integrates with navigation controllers, keeps track of animation states and interpolates transforms, enabling smooth transitions, orientation, and switching between boundaries when needed.
 * 
 * @details [AI] Key responsibilities include:
 * - Transitioning between path boundaries/edges based on movement and collision.
 * - Allowing user-controlled or AI-controlled navigation (m_userNavFlag).
 * - Interpolating position and orientation along path segments.
 * - Handling actor-specific state/flags, such as disabling collision, handling collision boxes, and wall hit sound timing.
 * - Serving as a bridge between path-following actors and the underlying world presentation.
 */
class LegoPathActor : public LegoActor {
public:
	/// @brief [AI] State and flags for a LegoPathActor during navigation along a path. [AI]
	enum ActorState {
		// States
		c_initial = 0,         ///< @brief [AI] Default state upon creation or reset. [AI]
		c_one = 1,
		c_two = 2,
		c_three = 3,
		c_disabled = 4,        ///< @brief [AI] Marks as disabled or inactive for path follow logic. [AI]
		c_maxState = 255,      ///< @brief [AI] Max actor state (reserved for logic). [AI]

		// Flags
		c_noCollide = 0x100    ///< @brief [AI] Disables collision for this actor (e.g. ghosts, debug). [AI]
	};

	LegoPathActor();  ///< @brief [AI] Initializes the path actor, setting up default state and references. [AI]
	~LegoPathActor() override; ///< @brief [AI] Destructor, cleans up allocated containers. [AI]

	/**
	 * @brief [AI] Parses a set of key-value action commands and configures path navigation and collision for this actor.
	 * @details [AI] Recognizes commands including "PERMIT_NAVIGATE", "PATH", "COLLIDEBOX", and issues configuration changes, triggers navigation, or boundary placement, etc.
	 * @param p_extra Key-value string with action commands. [AI]
	 */
	void ParseAction(char* p_extra) override;                              // vtable+0x20

	/**
	 * @brief [AI] Checks for collision/intersection with boundaries, geometry, and other actors along a traced segment; assists in advanced pathfinding by propagation.
	 * @param p_v1 Start position in world space. [AI]
	 * @param p_v2 End position in world space. [AI]
	 * @param p_v3 Output: Collision/contact point if found. [AI]
	 * @return >0 if collision occurred, 0 otherwise, <0 on error. [AI]
	 */
	virtual MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3); // vtable+0x68

	/**
	 * @brief [AI] Trace movement or collision through presenters (edge test), then through other actors. Designed for advanced collision testing and animation triggers. [AI]
	 * @param p_boundary Boundary to check within. [AI]
	 * @param p_v1 Segment start. [AI]
	 * @param p_v2 Segment end. [AI]
	 * @param p_f1 Scalar for test segment length. [AI]
	 * @param p_f2 Scalar for radius or additional space. [AI]
	 * @param p_v3 Output: Resulting intersection position, if any. [AI]
	 * @return 1 if presenter handled event, 2 if actor collision, 0 if no collision/event. [AI]
	 */
	virtual MxU32 VTable0x6c(
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3
	);                                             // vtable+0x6c

	/**
	 * @brief [AI] Per-frame animation update. Applies movement, linear velocity, adjusts transforms, and updates navigation/camera state. [AI]
	 * @param p_time Current animation time. [AI]
	 */
	virtual void Animate(float p_time);            // vtable+0x70

	/**
	 * @brief [AI] Updates the ROI's transformation (typically matrix) with new values, applies world position/orientation changes. [AI]
	 * @param p_transform Transformation matrix to apply. [AI]
	 */
	virtual void VTable0x74(Matrix4& p_transform); // vtable+0x74

	/**
	 * @brief [AI] Sets whether the actor is controlled by user navigation. [AI]
	 * @param p_userNavFlag TRUE if user navigation is enabled. [AI]
	 */
	virtual void SetUserNavFlag(MxBool p_userNavFlag) { m_userNavFlag = p_userNavFlag; } // vtable+0x78

	/**
	 * @brief [AI] Returns user navigation state (whether actor follows player input). [AI]
	 * @return TRUE if actor is user controlled. [AI]
	 */
	virtual MxBool GetUserNavFlag() { return m_userNavFlag; } // vtable+0x7c

	/**
	 * @brief [AI] Calculates path interpolation for a set of points, updates state for path animation, and computes Bezier arc duration. [AI]
	 * @param p_point1 Segment or control point 1. [AI]
	 * @param p_point2 Segment or control point 2. [AI]
	 * @param p_point3 Segment or control point 3. [AI]
	 * @param p_point4 Segment or control point 4. [AI]
	 * @return SUCCESS on update, FAILURE if arc length is degenerate. [AI]
	 */
	virtual MxResult VTable0x80(
		const Vector3& p_point1,
		Vector3& p_point2,
		Vector3& p_point3,
		Vector3& p_point4
	); // vtable+0x80

	/**
	 * @brief [AI] Moves actor to a destination edge. Handles placement, orientation update, assignment of new boundary and edge, updates transformation matrix. [AI]
	 * @param p_boundary Destination boundary. [AI]
	 * @param p_time Current/target time. [AI]
	 * @param p_p1 Start position. [AI]
	 * @param p_p4 Target direction/offset. [AI]
	 * @param p_destEdge Destination edge on boundary. [AI]
	 * @param p_destScale Location scale on destination edge (relative position). [AI]
	 * @return SUCCESS if placed, FAILURE if path/edge is not valid. [AI]
	 */
	virtual MxResult VTable0x84(
		LegoPathBoundary* p_boundary,
		float p_time,
		Vector3& p_p1,
		Vector3& p_p4,
		LegoUnknown100db7f4& p_destEdge,
		float p_destScale
	); // vtable+0x84

	/**
	 * @brief [AI] Moves the actor between two edges across a boundary, recalculates placement and orientation. Used for path transition logic when traversing to a new edge. [AI]
	 * @param p_boundary Target boundary. [AI]
	 * @param p_time Current time. [AI]
	 * @param p_srcEdge Source edge (previous). [AI]
	 * @param p_srcScale Relative position on the source edge. [AI]
	 * @param p_destEdge Destination edge (next). [AI]
	 * @param p_destScale Relative position on the destination edge. [AI]
	 * @return SUCCESS on placement, FAILURE if invalid. [AI]
	 */
	virtual MxResult VTable0x88(
		LegoPathBoundary* p_boundary,
		float p_time,
		LegoEdge& p_srcEdge,
		float p_srcScale,
		LegoUnknown100db7f4& p_destEdge,
		float p_destScale
	);                                                            // vtable+0x88

	/**
	 * @brief [AI] Advance actor's position/state along the path for a given timeslice. Handles navigation calculations, collision, and transforms. [AI]
	 * @param p_time Time to simulate up to. [AI]
	 * @param p_transform Matrix output with updated local transformation. [AI]
	 * @return 0 on success, 1 if collision occurred, -1 if error/stop. [AI]
	 */
	virtual MxS32 VTable0x8c(float p_time, Matrix4& p_transform); // vtable+0x8c

	/**
	 * @brief [AI] Placeholder for custom logic during per-timestep simulation for non-user-controlled animation. [AI_SUGGESTED_NAME: PerTickSimulationFallback]
	 * @param - [AI]
	 * @return Always FALSE (not handled). [AI]
	 */
	virtual MxU32 VTable0x90(float, Matrix4&) { return FALSE; } // vtable+0x90

	/**
	 * @brief [AI] Handles logic when this actor hits (collides with) another path actor; can be overridden for custom interaction. [AI]
	 * @param - [AI]
	 * @return Always 0 (no-op base class). [AI]
	 */
	virtual MxResult HitActor(LegoPathActor*, MxBool) { return 0; } // vtable+0x94

	/**
	 * @brief [AI] Switches current path boundary and destination edge, typically called on transitions or respawns. [AI]
	 * @param p_boundary Reference: will be updated to next boundary. [AI]
	 * @param p_edge Reference: updated to next destination edge. [AI]
	 * @param p_unk0xe4 Reference: updated position scalar. [AI]
	 */
	virtual void SwitchBoundary(
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	);                             // vtable+0x98

	/**
	 * @brief [AI] Handles exit transition and next-edge search logic; also used for collision reaction and fallback. [AI]
	 * @return SUCCESS if handled, FAILURE otherwise. [AI]
	 */
	virtual MxResult VTable0x9c(); // vtable+0x9c

	/**
	 * @brief [AI] Placeholder for custom extension. Returns 0 by default. [AI]
	 * @return 0 [AI]
	 */
	virtual MxS32 VTable0xa0() { return 0; } // vtable+0xa0

	/**
	 * @brief [AI] Returns information depending on actor type. Used for animation/sound/camera variants. [AI]
	 * @param p_und1 Output: TRUE/FALSE depending on actor type. [AI]
	 * @param p_und2 Output: Integer variant for this actor type. [AI]
	 */
	virtual void VTable0xa4(MxBool& p_und1, MxS32& p_und2); // vtable+0xa4

	/**
	 * @brief [AI] Re-applies transform to ROI, updates camera if needed, and processes per-actor tick actions. [AI]
	 */
	virtual void VTable0xa8();                              // vtable+0xa8

	/**
	 * @brief [AI] Sets the maximum linear velocity for actor navigation. [AI]
	 * @param p_maxLinearVel Maximum allowed navigation speed. [AI]
	 */
	virtual void SetMaxLinearVel(MxFloat p_maxLinearVel) { m_maxLinearVel = p_maxLinearVel; } // vtable+0xac

	/**
	 * @brief [AI] Gets the maximum allowed navigation speed for this actor. [AI]
	 * @return Max linear velocity (navigation speed). [AI]
	 */
	virtual MxFloat GetMaxLinearVel() { return m_maxLinearVel; } // vtable+0xb0

	/**
	 * @brief [AI] Returns an internal value used in fallback collision/velocity calculation (proportional fudge factor). [AI]
	 * @return Scalar parameter used for bump resolution. [AI]
	 */
	virtual MxFloat VTable0xb4() { return m_unk0x140; } // vtable+0xb4

	/**
	 * @brief [AI] Returns a damping/multiplier factor used for velocity reduction after collisions. [AI]
	 */
	virtual MxFloat VTable0xb8() { return m_unk0x144; } // vtable+0xb8

	/**
	 * @brief [AI] Sets the fudge parameter for fallback collision push-back. [AI]
	 * @param p_unk0x140 Value to set. [AI]
	 */
	virtual void VTable0xbc(MxFloat p_unk0x140) { m_unk0x140 = p_unk0x140; } // vtable+0xbc

	/**
	 * @brief [AI] Sets the velocity damping factor after bump. [AI]
	 * @param p_unk0x144 Value to set. [AI]
	 */
	virtual void VTable0xc0(MxFloat p_unk0x144) { m_unk0x144 = p_unk0x144; } // vtable+0xc0

	/**
	 * @brief [AI] Empty handler for optional custom per-tick transition logic. [AI]
	 */
	virtual void VTable0xc4() {} // vtable+0xc4

	/**
	 * @brief [AI] Sets the rolling state (animation index, mainly for camera turning/curves). [AI]
	 * @param p_unk0x148 Rolling angle state. [AI]
	 */
	virtual void VTable0xc8(MxU8 p_unk0x148) { m_unk0x148 = p_unk0x148; } // vtable+0xc8

	/**
	 * @brief [AI] Returns the class name string for RTTI-style checks. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoPathActor";
	}

	/**
	 * @brief [AI] RTTI-like check, matches against own or base class name for IsA hierarchy checks. [AI]
	 * @param p_name Class name to compare. [AI]
	 * @return TRUE if matches type. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoPathActor::ClassName()) || LegoActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Retrieves the current path boundary associated with this actor. [AI]
	 * @return Pointer to the actor's current boundary. [AI]
	 */
	LegoPathBoundary* GetBoundary() { return m_boundary; }

	/**
	 * @brief [AI] Gets the current navigation/animation state of the actor. [AI]
	 */
	MxU32 GetActorState() { return m_actorState; }

	/**
	 * @brief [AI] Retrieves pointer to the path controller which governs this actor's movement. [AI]
	 */
	LegoPathController* GetController() { return m_pathController; }

	/**
	 * @brief [AI] Gets the actor's collision box flag (if TRUE, actor uses a precise collision shape). [AI]
	 */
	MxBool GetCollideBox() { return m_collideBox; }

	/**
	 * @brief [AI] Gets the previous animation time value from last simulation tick. [AI]
	 */
	MxFloat GetLastTime() { return m_lastTime; }

	/**
	 * @brief [AI] Returns the current animation time of the actor. [AI]
	 */
	MxFloat GetActorTime() { return m_actorTime; }

	/**
	 * @brief [AI] Assigns a new boundary for the actor (for path switching). [AI]
	 * @param p_boundary New boundary to set. [AI]
	 */
	void SetBoundary(LegoPathBoundary* p_boundary) { m_boundary = p_boundary; }

	/**
	 * @brief [AI] Sets the navigation/path state of the actor. [AI]
	 * @param p_actorState Actor state constant. [AI]
	 */
	void SetActorState(MxU32 p_actorState) { m_actorState = p_actorState; }

	/**
	 * @brief [AI] Assigns a new path controller (used for actor transitions between paths). [AI]
	 * @param p_pathController New path controller to use. [AI]
	 */
	void SetController(LegoPathController* p_pathController) { m_pathController = p_pathController; }

	/**
	 * @brief [AI] Sets the time value for the last performed simulation tick. [AI]
	 * @param p_lastTime Last time value to set. [AI]
	 */
	void SetLastTime(MxFloat p_lastTime) { m_lastTime = p_lastTime; }

	/**
	 * @brief [AI] Sets the global actor animation time value, adjusting how far along the animation is. [AI]
	 * @param p_actorTime New time to set. [AI]
	 */
	void SetActorTime(MxFloat p_actorTime) { m_actorTime = p_actorTime; }

	/**
	 * @brief [AI] Updates a named plane to match this actor's world position, direction, and up vector. [AI]
	 * @param p_namedPlane Named plane object to update. [AI]
	 */
	void UpdatePlane(LegoNamedPlane& p_namedPlane);

	/**
	 * @brief [AI] Places this actor into the world at the given plane's name, location, and orientation. [AI]
	 * @param p_namedPlane Info describing location/orientation and which boundary. [AI]
	 */
	void PlaceActor(LegoNamedPlane& p_namedPlane);

protected:
	/**
	 * @brief [AI] Recursively checks boundaries for collisions or collision path propagation up to a certain recursion depth. [AI]
	 * @param p_boundaries List of boundaries already visited. [AI]
	 * @param p_boundary Current boundary to check. [AI]
	 * @param p_v1 World-space segment start. [AI]
	 * @param p_v2 World-space direction/normalized vector. [AI]
	 * @param p_f1 Segment length. [AI]
	 * @param p_f2 Segment radius (collision threshold). [AI]
	 * @param p_v3 Output: Hit position (if found). [AI]
	 * @param p_und Recursion depth; stops after 2. [AI]
	 * @return >0 on collision, 0 if none, propagates result. [AI]
	 */
	inline MxU32 FUN_1002edd0(
		list<LegoPathBoundary*>& p_boundaries,
		LegoPathBoundary* p_boundary,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		float p_f2,
		Vector3& p_v3,
		MxS32 p_und
	);

	MxFloat m_BADuration;                 ///< @brief [AI] Duration of current Bezier arc (distance along path/current edge). [AI]
	MxFloat m_unk0x7c;                    ///< @brief [AI] Interpolator/progress state along curve segment. [AI]
	MxFloat m_actorTime;                  ///< @brief [AI] Animation time for current path segment. [AI]
	MxFloat m_lastTime;                   ///< @brief [AI] Time of last update (used for delta calculations). [AI]
	LegoPathBoundary* m_boundary;         ///< @brief [AI] Current boundary the actor is navigating on. [AI]
	LegoUnknown m_unk0x8c;                ///< @brief [AI] Helper object for path curve interpolation and evaluation. [AI]
	MxU32 m_actorState;                   ///< @brief [AI] State and flags bitfield for path following logic. [AI]
	LegoUnknown100db7f4* m_destEdge;      ///< @brief [AI] Current or target edge for path traversal. [AI]
	MxFloat m_unk0xe4;                    ///< @brief [AI] Position scalar on destination edge (0-1 across the edge). [AI]
	MxBool m_collideBox;                  ///< @brief [AI] Use bounding-box for more accurate collision. [AI]
	MxBool m_unk0xe9;                     ///< @brief [AI] Stores latest intersection/collision status/type. [AI]
	MxBool m_userNavFlag;                 ///< @brief [AI] TRUE if this actor is currently user/player controlled. [AI]
	MxMatrix m_unk0xec;                   ///< @brief [AI] World-to-local transformation matrix for this actor/ROI. [AI]
	LegoPathEdgeContainer* m_grec;        ///< @brief [AI] Edge/boundary helper for tracking transitions and stateful animation. [AI]
	LegoPathController* m_pathController; ///< @brief [AI] Path controller/manages permitted boundaries for transitions. [AI]
	MxFloat m_maxLinearVel;               ///< @brief [AI] Maximum speed of actor while moving along path. [AI]
	MxFloat m_unk0x140;                   ///< @brief [AI] Scaling factor for fallback/collision response logic. [AI]
	MxFloat m_unk0x144;                   ///< @brief [AI] Damping factor for velocity after collision ("bounce" friction). [AI]
	MxU8 m_unk0x148;                      ///< @brief [AI] Angle/animation mode for rolling/camera tilting. [AI]
	MxS32 m_unk0x14c;                     ///< @brief [AI] Rolling angle delta (variant for camera logic). [AI]
	MxFloat m_unk0x150;                   ///< @brief [AI] Scalar factor for camera turn velocity logic. [AI]
};

#endif // LEGOPATHACTOR_H
