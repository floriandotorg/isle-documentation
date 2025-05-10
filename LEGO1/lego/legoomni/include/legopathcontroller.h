#ifndef LEGOPATHCONTROLLER_H
#define LEGOPATHCONTROLLER_H

#include "decomp.h"
#include "geom/legounkown100db7f4.h"
#include "legopathactor.h"
#include "legopathboundary.h"
#include "legopathstruct.h"
#include "mxstl/stlcompat.h"

/**
 * @class LegoPathCtrlEdge
 * @brief [AI] Controller-specific edge used in path navigation. Inherits geometry and connectivity from LegoUnknown100db7f4, representing a directed edge with additional controller metadata. [AI]
 */
struct LegoPathCtrlEdge : public LegoUnknown100db7f4 {};

/**
 * @struct LegoPathCtrlEdgeCompare
 * @brief [AI] Comparator functor for LegoPathCtrlEdge pointer sets. Used to order edges deterministically in containers. [AI]
 */
struct LegoPathCtrlEdgeCompare {
	MxU32 operator()(const LegoPathCtrlEdge* p_lhs, const LegoPathCtrlEdge* p_rhs) const
	{
		return (COMPARE_POINTER_TYPE) p_lhs < (COMPARE_POINTER_TYPE) p_rhs;
	}
};

/**
 * @typedef LegoPathCtrlEdgeSet
 * @brief [AI] Set of pointers to control edges, ordered using LegoPathCtrlEdgeCompare. Used for efficient lookups during actor navigation. [AI]
 */
typedef set<LegoPathCtrlEdge*, LegoPathCtrlEdgeCompare> LegoPathCtrlEdgeSet;

class LegoAnimPresenter;
class LegoWorld;
class MxAtomId;
class Vector3;

/**
 * @class LegoPathController
 * @brief [AI] Manager for controlling actors' movement along predefined geometric paths. Handles path boundaries, connectivity, and the logic for actor transitions and obstacle detection. Registered as a tickle client for per-frame updates. [AI]
 * 
 * @details [AI] This class provides and maintains the runtime representation of path boundaries (track segments), structural triggers, and linkage edges. It manages actor attachments, movement placement along the path network, and supplies special path information to enable complex transitions between segments. Path data is read from script storage and is essential for AI pathfinding and animation coordination. [AI]
 *
 * @note [AI] Used heavily for high-level navigation in LEGO Island, such as vehicle/train movement, NPC walking, and special camera paths. [AI]
 */
class LegoPathController : public MxCore {
public:
	/**
	 * @struct CtrlBoundary
	 * @brief [AI] Helper structure for rapid lookups of controller-boundary pairs, often used for global or indexed access patterns across controllers. [AI]
	 */
	struct CtrlBoundary {
		/**
		 * @brief [AI] Initializes structure by nullifying pointers. [AI]
		 */
		CtrlBoundary()
		{
			m_controller = NULL;
			m_boundary = NULL;
		}

		LegoPathController* m_controller; ///< @brief [AI] Pointer to owning path controller. [AI]
		LegoPathBoundary* m_boundary;     ///< @brief [AI] Associated path boundary within the controller. [AI]
	};

	/**
	 * @struct CtrlEdge
	 * @brief [AI] Helper structure pairing controllers with edge references for global or fast access. [AI]
	 */
	struct CtrlEdge {
		/**
		 * @brief [AI] Initializes structure by nullifying pointers. [AI]
		 */
		CtrlEdge()
		{
			m_controller = NULL;
			m_edge = NULL;
		}

		LegoPathController* m_controller;  ///< @brief [AI] Pointer to owning path controller. [AI]
		LegoUnknown100db7f4* m_edge;       ///< @brief [AI] Reference to a specific edge, typically a segment connector or trigger. [AI]
	};

	/**
	 * @brief [AI] Constructs a LegoPathController, initializing boundary and edge pointers to NULL and counts to zero. [AI]
	 */
	LegoPathController();

	/**
	 * @brief [AI] Destructor, unregisters itself from the tickle manager and releases all dynamically allocated path data. [AI]
	 */
	~LegoPathController() override { Destroy(); }

	/**
	 * @brief [AI] Implements the tickle (per-frame update) callback for the controller. [AI]
	 * @details [AI] Updates animation state for managed actors along the path. [AI]
	 * @return [AI] Always returns SUCCESS. [AI]
	 */
	MxResult Tickle() override;

	/**
	 * @brief [AI] Returns the class name for runtime type identification. [AI]
	 * @return [AI] Static string: "LegoPathController". [AI]
	 */
	const char* ClassName() const override;

	/**
	 * @brief [AI] Checks inheritance by class name for type introspection. [AI]
	 * @param p_name Class name to check. [AI]
	 * @return [AI] TRUE if class matches or inherited, else FALSE. [AI]
	 */
	MxBool IsA(const char* p_name) const override;

	/**
	 * @brief [AI] Initializes the path controller from the provided binary data at the specified location, applying a trigger. [AI]
	 * @param p_data [AI] Pointer to memory containing path controller serialized data.
	 * @param p_location [AI] The world position for relocation of controller-linked objects.
	 * @param p_trigger [AI] Atom ID used for signaling or associating with relevant path structures.
	 * @return [AI] Result code indicating success or failure during data parsing/initialization.
	 */
	virtual MxResult Create(MxU8* p_data, const Vector3& p_location, const MxAtomId& p_trigger);

	/**
	 * @brief [AI] Deinitializes path controller, releases all owned resources and unregisters from tickle manager. [AI]
	 */
	virtual void Destroy();

	/**
	 * @brief [AI] Places an actor on a boundary at given source/destination edge indices, commonly for track segment transitions (e.g., for vehicles). [AI]
	 * @param p_actor [AI] Pointer to the path actor to move.
	 * @param p_name [AI] Name of the path boundary to use as source/destination.
	 * @param p_src [AI] Index of the source edge on the boundary.
	 * @param p_srcScale [AI] Scaled offset on the source edge (0..1), for fine placement.
	 * @param p_dest [AI] Index of destination edge on the boundary.
	 * @param p_destScale [AI] Scaled offset on the destination edge (0..1), for fine placement.
	 * @return [AI] SUCCESS if actor was successfully placed, FAILURE otherwise.
	 */
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		const char* p_name,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale
	);

	/**
	 * @brief [AI] Places an actor using an animation presenter and direct position/direction data. Used for initial placement or precise positioning by external systems. [AI]
	 * @param p_actor [AI] Pointer to the actor.
	 * @param p_presenter [AI] Animation presenter used for visual/behavior state.
	 * @param p_position [AI] Starting position in world coordinates.
	 * @param p_direction [AI] Direction vector for initial movement or facing.
	 * @return [AI] SUCCESS if placement succeeded, FAILURE if no boundary fits requirements.
	 */
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		LegoAnimPresenter* p_presenter,
		Vector3& p_position,
		Vector3& p_direction
	);

	/**
	 * @brief [AI] Registers an actor as controlled by this path controller without moving it to a specific boundary location, e.g., after controller change. [AI]
	 * @param p_actor [AI] The actor to register.
	 * @return [AI] SUCCESS after registration.
	 */
	MxResult PlaceActor(LegoPathActor* p_actor);

	/**
	 * @brief [AI] Removes an actor from the controller, detaches it from controlled boundaries, and clears associations. [AI]
	 * @param p_actor [AI] Actor to remove.
	 * @return [AI] SUCCESS if the actor was detached from at least one boundary, FAILURE otherwise.
	 */
	MxResult RemoveActor(LegoPathActor* p_actor);

	/**
	 * @brief [AI] Processes all boundaries except those with bit3 set, invoking FUN_10057fe0 for the provided animation presenter. [AI]
	 * @param p_presenter [AI] Pointer to an animation presenter. [AI]
	 */
	void FUN_100468f0(LegoAnimPresenter* p_presenter);

	/**
	 * @brief [AI] Invokes FUN_100586e0 for each boundary, with the provided animation presenter. [AI]
	 * @param p_presenter [AI] Pointer to the animation presenter. [AI]
	 */
	void FUN_10046930(LegoAnimPresenter* p_presenter);

	/**
	 * @brief [AI] Provides current array of boundaries and count as output parameters, for external queries. [AI]
	 * @param p_boundaries [AI] Output: pointer set to internal array of boundaries. [AI]
	 * @param p_numL [AI] Output: count of path boundaries. [AI]
	 * @return [AI] Always returns SUCCESS.
	 */
	MxResult FUN_10046b30(LegoPathBoundary*& p_boundaries, MxS32& p_numL);

	/**
	 * @brief [AI] Searches for a path boundary by name among owned boundaries. [AI]
	 * @param p_name [AI] Name to search for (case-insensitive). [AI]
	 * @return [AI] Pointer to boundary or NULL if not found. [AI]
	 */
	LegoPathBoundary* GetPathBoundary(const char* p_name);

	/**
	 * @brief [AI] Enables or disables the controller's registration with the tickle manager, controlling per-frame updates. [AI]
	 * @param p_enable [AI] TRUE to enable, FALSE to disable. [AI]
	 */
	void Enable(MxBool p_enable);

	/**
	 * @brief [AI] Assigns the provided world pointer to all struct triggers owned by this path controller. [AI]
	 * @param p_world [AI] Pointer to the LegoWorld object, set in all structs. [AI]
	 */
	void FUN_10046bb0(LegoWorld* p_world);

	/**
	 * @brief [AI] Complex function performing path transition resolution; computes possible edge transition sequences for an actor moving between boundaries. [AI]
	 * @param p_grec [AI] Edge container holding the resulting transition sequence.
	 * @param p_oldPosition [AI] Source position.
	 * @param p_oldDirection [AI] Source direction.
	 * @param p_oldBoundary [AI] Boundary actor is moving from.
	 * @param p_newPosition [AI] Destination position.
	 * @param p_newDirection [AI] Destination direction.
	 * @param p_newBoundary [AI] Boundary actor is moving to.
	 * @param p_mask [AI] Path mask for allowed transitions (bitmask).
	 * @param p_param9 [AI] Out: will contain shortest path distance if provided.
	 * @return [AI] SUCCESS if a route is computed, FAILURE otherwise.
	 */
	MxResult FUN_10048310(
		LegoPathEdgeContainer* p_grec,
		const Vector3& p_oldPosition,
		const Vector3& p_oldDirection,
		LegoPathBoundary* p_oldBoundary,
		const Vector3& p_newPosition,
		const Vector3& p_newDirection,
		LegoPathBoundary* p_newBoundary,
		LegoU8 p_mask,
		MxFloat* p_param9
	);

	/**
	 * @brief [AI] Computes path vector and orientation for an actor given a transition along the resolved edge container sequence. [AI]
	 * @param p_grec [AI] Edge transition container (LegoPathEdgeContainer).
	 * @param p_v1 [AI] Output: next position vector for the actor.
	 * @param p_v2 [AI] Output: next direction vector for the actor.
	 * @param p_f1 [AI] Interpolation parameter or normalized distance along the transition.
	 * @param p_edge [AI] Output: pointer to the next transition edge taken.
	 * @param p_boundary [AI] Output: pointer to the target boundary.
	 * @return [AI] 1 if the edge container is empty, 0 if a transition step was advanced.
	 */
	MxS32 FUN_1004a240(
		LegoPathEdgeContainer& p_grec,
		Vector3& p_v1,
		Vector3& p_v2,
		float p_f1,
		LegoUnknown100db7f4*& p_edge,
		LegoPathBoundary*& p_boundary
	);

	/**
	 * @brief [AI] Finds earliest intersection and placement on a valid boundary for the provided vectors and updates parameters as needed. [AI]
	 * @param p_param1 [AI] Reference vector for placement update.
	 * @param p_param2 [AI] Reference direction for placement update.
	 * @param p_param3 [AI] Array of three 3D float points used in intersection calculation.
	 * @param p_boundary [AI] Output: chosen boundary for intersection, if any.
	 * @param p_param5 [AI] In/out intersection parameter: updated if intersection found.
	 * @return [AI] SUCCESS if intersection found, FAILURE otherwise.
	 */
	MxResult FUN_1004a380(
		Vector3& p_param1,
		Vector3& p_param2,
		Mx3DPointFloat* p_param3,
		LegoPathBoundary*& p_boundary,
		MxFloat& p_param5
	);

	/**
	 * @brief [AI] Checks whether an actor is contained in the controller's actor set.
	 * @param p_actor [AI] Pointer to the actor to query.
	 * @return [AI] TRUE if actor exists, FALSE otherwise.
	 */
	MxBool ActorExists(LegoPathActor* p_actor) { return m_actors.find(p_actor) == m_actors.end() ? FALSE : TRUE; }

	/**
	 * @brief [AI] Static initializer for global controller boundary/edge arrays. Allocates the global lookup tables for controller-bounded objects.
	 * @return [AI] SUCCESS on allocation, FAILURE if already initialized.
	 */
	static MxResult Init();

	/**
	 * @brief [AI] Resets (cleans up) global controller boundary/edge arrays allocated by Init().
	 * @return [AI] SUCCESS if cleanup was performed, FAILURE otherwise.
	 */
	static MxResult Reset();

	/**
	 * @brief [AI] Provides static access to the edge at a given index in g_ctrlEdgesA.
	 * @param p_index [AI] The index of the control edge to retrieve.
	 * @return [AI] Pointer to the corresponding LegoUnknown100db7f4 object.
	 */
	static LegoUnknown100db7f4* GetControlEdgeA(MxS32 p_index) { return g_ctrlEdgesA[p_index].m_edge; }

	/**
	 * @brief [AI] Provides static access to the boundary at given index in g_ctrlBoundariesA.
	 * @param p_index [AI] The index of the control boundary to retrieve.
	 * @return [AI] Pointer to the corresponding LegoPathBoundary.
	 */
	static LegoPathBoundary* GetControlBoundaryA(MxS32 p_index) { return g_ctrlBoundariesA[p_index].m_boundary; }

	/**
	 * @brief [AI] Provides static access to the edge at a given index in g_ctrlEdgesB.
	 * @param p_index [AI] The index of the control edge to retrieve.
	 * @return [AI] Pointer to the corresponding LegoUnknown100db7f4 object.
	 */
	static LegoUnknown100db7f4* GetControlEdgeB(MxS32 p_index) { return g_ctrlEdgesB[p_index].m_edge; }

	/**
	 * @brief [AI] Provides static access to the boundary at given index in g_ctrlBoundariesB.
	 * @param p_index [AI] The index of the control boundary to retrieve.
	 * @return [AI] Pointer to the corresponding LegoPathBoundary.
	 */
	static LegoPathBoundary* GetControlBoundaryB(MxS32 p_index) { return g_ctrlBoundariesB[p_index].m_boundary; }

private:
	/**
	 * @brief [AI] Internal per-frame update; animates all active actors managed by this controller. [AI]
	 */
	void FUN_10046970();

	/**
	 * @brief [AI] Loads the path controller state from storage, including structure, edge, and boundary arrays. [AI]
	 * @param p_storage [AI] Pointer to LegoStorage input source. [AI]
	 * @return [AI] SUCCESS if all elements loaded correctly, else FAILURE.
	 */
	MxResult Read(LegoStorage* p_storage);

	/**
	 * @brief [AI] Reads and initializes path structure triggers from storage. [AI]
	 * @param p_storage [AI] Source for the triggers. [AI]
	 * @return [AI] SUCCESS if successful, FAILURE otherwise.
	 */
	MxResult ReadStructs(LegoStorage* p_storage);

	/**
	 * @brief [AI] Reads and initializes path edges array from storage, constructing connectivity graph. [AI]
	 * @param p_storage [AI] Source for edges. [AI]
	 * @return [AI] SUCCESS if successful, FAILURE otherwise.
	 */
	MxResult ReadEdges(LegoStorage* p_storage);

	/**
	 * @brief [AI] Reads and initializes path boundaries from storage, building all edges, triggers, and supporting data. [AI]
	 * @param p_storage [AI] Storage instance to read from.
	 * @return [AI] SUCCESS if successful, FAILURE otherwise.
	 */
	MxResult ReadBoundaries(LegoStorage* p_storage);

	/**
	 * @brief [AI] Reads a 3D float vector from storage into given reference. [AI]
	 * @param p_storage [AI] Storage to read from.
	 * @param p_vec [AI] Vector to fill.
	 * @return [AI] SUCCESS if the vector was loaded.
	 */
	static MxResult ReadVector(LegoStorage* p_storage, Mx3DPointFloat& p_vec);

	/**
	 * @brief [AI] Reads a 4D float vector from storage into given reference. [AI]
	 * @param p_storage [AI] Storage to read from.
	 * @param p_vec [AI] Vector to fill.
	 * @return [AI] SUCCESS if the vector was loaded.
	 */
	static MxResult ReadVector(LegoStorage* p_storage, Mx4DPointFloat& p_vec);

	/**
	 * @brief [AI] Utility to check if a value is numerically between two endpoints (inclusive), handling reversed order. [AI]
	 * @param p_v [AI] Value to check.
	 * @param p_a [AI] Endpoint A.
	 * @param p_b [AI] Endpoint B.
	 * @return [AI] TRUE if p_v is between p_a and p_b, else FALSE.
	 */
	static MxU32 IsBetween(MxFloat p_v, MxFloat p_a, MxFloat p_b);

	/**
	 * @brief [AI] Utility comparing two values each known to be between two endpoints; handles directionality of the interval. [AI]
	 * @param p_v1 [AI] First value.
	 * @param p_v2 [AI] Second value.
	 * @param p_a [AI] Endpoint A.
	 * @param p_b [AI] Endpoint B.
	 * @return [AI] TRUE if p_v1 < p_v2 (or > for reversed), else FALSE.
	 */
	static MxU32 FUN_100c17a0(MxFloat p_v1, MxFloat p_v2, MxFloat p_a, MxFloat p_b);

	LegoPathBoundary* m_boundaries; ///< @brief [AI] Dynamically allocated array of path boundaries (segments) managed by the controller. [AI]
	LegoPathCtrlEdge* m_edges;      ///< @brief [AI] Dynamically allocated array of control edges, specifying connectivity between boundaries. [AI]
	Mx3DPointFloat* m_unk0x10;      ///< @brief [AI] Array of 3D float points; typically used as edge endpoints or other geometry anchors. [AI]
	LegoPathStruct* m_structs;      ///< @brief [AI] Array of path trigger structs (for events and special behaviors at boundaries). [AI]
	MxU16 m_numL;                   ///< @brief [AI] Number of boundaries. [AI]
	MxU16 m_numE;                   ///< @brief [AI] Number of edges. [AI]
	MxU16 m_numN;                   ///< @brief [AI] Number of nodes/points in m_unk0x10. [AI]
	MxU16 m_numT;                   ///< @brief [AI] Number of trigger structs in m_structs. [AI]
	LegoPathCtrlEdgeSet m_pfsE;     ///< @brief [AI] Set of pointers to control edges, for efficient lookup and filtering. [AI]
	LegoPathActorSet m_actors;      ///< @brief [AI] Set of actors currently managed by this controller. [AI]

	// Names verified by BETA10

	static CtrlBoundary* g_ctrlBoundariesA; ///< @brief [AI] Global static boundary lookup for preset boundary slots (group A). [AI]
	static CtrlEdge* g_ctrlEdgesA;          ///< @brief [AI] Global static control edge lookup for preset slots (group A). [AI]
	static const char* g_unk0x100f42f0[];   ///< @brief [AI] Table of known boundary names used as lookups for group A controls. [AI]
	static const char* g_unk0x100f4330[];   ///< @brief [AI] Table of known boundary names for group B controls. [AI]
	static CtrlBoundary* g_ctrlBoundariesB; ///< @brief [AI] Global static boundary lookup for preset boundary slots (group B). [AI]
	static CtrlEdge* g_ctrlEdgesB;          ///< @brief [AI] Global static control edge lookup for preset slots (group B). [AI]
};

#endif // LEGOPATHCONTROLLER_H