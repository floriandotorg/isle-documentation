#ifndef LEGOPATHBOUNDARY_H
#define LEGOPATHBOUNDARY_H

#include "geom/legowegedge.h"
#include "legoanimpresenter.h"
#include "legopathactor.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"

#if defined(_M_IX86) || defined(__i386__)
#define COMPARE_POINTER_TYPE MxS32
#else
#define COMPARE_POINTER_TYPE MxS32*
#endif

/**
 * @struct LegoPathActorSetCompare
 * @brief [AI] Comparison functor used to order LegoPathActor pointers for set containers, using their pointer value.
 * @details [AI] This comparison ensures that the set of actor pointers has a stable and unique order.
 */
struct LegoPathActorSetCompare {
	MxU32 operator()(const LegoPathActor* p_lhs, const LegoPathActor* p_rhs) const
	{
		return (COMPARE_POINTER_TYPE) p_lhs < (COMPARE_POINTER_TYPE) p_rhs;
	}
};

/**
 * @struct LegoAnimPresenterSetCompare
 * @brief [AI] Comparison functor used to order LegoAnimPresenter pointers for set containers, using their pointer value.
 * @details [AI] Ensures a unique ordering of animation presenters in presenter sets.
 */
struct LegoAnimPresenterSetCompare {
	MxU32 operator()(const LegoAnimPresenter* p_lhs, const LegoAnimPresenter* p_rhs) const
	{
		return (COMPARE_POINTER_TYPE) p_lhs < (COMPARE_POINTER_TYPE) p_rhs;
	}
};

/**
 * @typedef LegoPathActorSet
 * @brief [AI] Defines a set of LegoPathActor pointers, ordered by pointer value using LegoPathActorSetCompare.
 */
typedef set<LegoPathActor*, LegoPathActorSetCompare> LegoPathActorSet;

/**
 * @typedef LegoAnimPresenterSet
 * @brief [AI] Defines a set of LegoAnimPresenter pointers, ordered by pointer value using LegoAnimPresenterSetCompare.
 */
typedef set<LegoAnimPresenter*, LegoAnimPresenterSetCompare> LegoAnimPresenterSet;

// VTABLE: LEGO1 0x100d8618
// SIZE 0x74
/**
 * @class LegoPathBoundary
 * @brief [AI] Represents a path segment or boundary in the navigation network for actors (vehicles, NPCs).
 * @details [AI] Inherits from LegoWEGEdge, connecting multiple path edges and managing the set of actors present on this path segment as well as relevant animation presenters. Provides API for actor entry, removal, intersection testing, and traversal between boundaries.
 */
class LegoPathBoundary : public LegoWEGEdge {
public:
	/**
	 * @brief [AI] Constructs a LegoPathBoundary, initializing internal actor/presenter storage.
	 */
	LegoPathBoundary();

	/**
	 * @brief [AI] Destructor. Cleans up actors and removes their boundary association.
	 */
	~LegoPathBoundary() override;

	/**
	 * @brief [AI] Adds the given actor to this path boundary and sets its boundary pointer.
	 * @param p_actor Pointer to LegoPathActor to add. [AI]
	 * @return Result code (SUCCESS on success, or error code). [AI]
	 */
	MxResult AddActor(LegoPathActor* p_actor);

	/**
	 * @brief [AI] Removes the actor from this boundary's actor set.
	 * @param p_actor Pointer to actor to remove. [AI]
	 * @return Result code (SUCCESS on success, or error code). [AI]
	 */
	MxResult RemoveActor(LegoPathActor* p_actor);

	/**
	 * @brief [AI] Handles processing path triggers along this boundary as an actor moves from p_point1 to p_point2.
	 * @details [AI] Checks all triggers if the movement between points crosses their threshold, calling the appropriate trigger handler per trigger direction.
	 * @param p_point1 Starting position of movement. [AI]
	 * @param p_point2 Ending position of movement. [AI]
	 * @param p_actor Actor moving along the path. [AI]
	 */
	void FUN_100575b0(Vector3& p_point1, Vector3& p_point2, LegoPathActor* p_actor);

	/**
	 * @brief [AI] Switches the boundary that the actor is associated with based on edge traversal.
	 * @details [AI] Handles neighbor boundary search and traversal logic with respect to actor navigation flags and edge properties.
	 * @param p_actor The actor potentially switching boundaries. [AI]
	 * @param p_boundary Reference to the actor's current boundary, will be updated if switch occurs. [AI]
	 * @param p_edge Reference to the edge across which the switch may occur; updates during process. [AI]
	 * @param p_unk0xe4 Value representing fractional progress/tangent or orientation for traversal; may be adjusted. [AI]
	 */
	void SwitchBoundary(
		LegoPathActor* p_actor,
		LegoPathBoundary*& p_boundary,
		LegoUnknown100db7f4*& p_edge,
		float& p_unk0xe4
	);

	/**
	 * @brief [AI] Tests for intersection between a path and this boundary; finds the first edge hit and intersection point.
	 * @details [AI] Used for navigation/pathfinding. If the segment crosses an edge, calculates where it intersects and on which subedge.
	 * @param p_scale Scaling factor, typically unused in current impl. [AI]
	 * @param p_point1 Segment start position. [AI]
	 * @param p_point2 Segment end position. [AI]
	 * @param p_point3 Output: the computed intersection point. [AI]
	 * @param p_edge Output: pointer to the edge crossed/found. [AI]
	 * @return 0 if no intersection, 1 or 2 depending on tangent or corner intersection. [AI]
	 */
	MxU32 Intersect(
		float p_scale,
		Vector3& p_point1,
		Vector3& p_point2,
		Vector3& p_point3,
		LegoUnknown100db7f4*& p_edge
	);

	/**
	 * @brief [AI] Adds an animation presenter to the set if within region, based on spatial bounds.
	 * @details [AI] Inserts specific subclass instances (e.g., LegoLocomotionAnimPresenter*). Used for assigning control to presenters within range.
	 * @param p_presenter Animation presenter instance. [AI]
	 * @return 1 if added, 0 if not. [AI]
	 */
	MxU32 FUN_10057fe0(LegoAnimPresenter* p_presenter);

	/**
	 * @brief [AI] Removes an animation presenter from the set, or if nullptr resets all presenters' world association.
	 * @param p_presenter Animation presenter to remove, or NULL for batch removal. [AI]
	 * @return 1 if removed, 0 if not found or batch reset. [AI]
	 */
	MxU32 FUN_100586e0(LegoAnimPresenter* p_presenter);

	/**
	 * @brief [AI] Direct access to the actor set for this boundary.
	 * @return Reference to the internal actor set. [AI]
	 */
	LegoPathActorSet& GetActors() { return m_actors; }

	/**
	 * @brief [AI] Direct access to the animation presenter set for this boundary.
	 * @return Reference to the internal presenter set. [AI]
	 */
	LegoAnimPresenterSet& GetPresenters() { return m_presenters; }

	// SYNTHETIC: LEGO1 0x10047a80
	// LegoPathBoundary::`vector deleting destructor'

private:
	/**
	 * @var m_actors
	 * @brief [AI] Set of actors currently within or traveling across this path boundary.
	 */
	LegoPathActorSet m_actors;         // 0x54

	/**
	 * @var m_presenters
	 * @brief [AI] Set of animation presenters attached to or relevant for this boundary, e.g., for animating objects/entities tied to the region.
	 */
	LegoAnimPresenterSet m_presenters; // 0x64
};

#endif // LEGOPATHBOUNDARY_H