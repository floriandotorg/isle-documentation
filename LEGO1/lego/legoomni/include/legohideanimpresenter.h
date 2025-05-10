#ifndef LEGOHIDEANIMPRESENTER_H
#define LEGOHIDEANIMPRESENTER_H

#include "decomp.h"
#include "legoloopinganimpresenter.h"

class LegoPathBoundary;

/// [AI] Comparator for string keys in map for use with LegoHideAnimStruct.
/// Compares two C-style strings using strcmp.
struct LegoHideAnimStructComparator {
	/// [AI] Operator comparison using strcmp for strict-weak ordering.
	/// @param p_a First string [AI]
	/// @param p_b Second string [AI]
	/// @return True if p_a is lexicographically less than p_b [AI]
	MxBool operator()(const char* const& p_a, const char* const& p_b) const { return strcmp(p_a, p_b) < 0; }
};

/// [AI] Structure associating a path boundary with an index. Used during presenter setup to map animation node names to world boundaries.
/// SIZE 0x08 [AI]
struct LegoHideAnimStruct {
	LegoPathBoundary* m_boundary; ///< [AI] Pointer to a LegoPathBoundary found by name from animation node
	MxU32 m_index; ///< [AI] Index assigned to this boundary in the map and used for node-to-boundary association
};

/// [AI] Map associating string (name) keys to LegoHideAnimStruct, using custom comparator for C strings.
/// Used for resolving boundary nodes in the scene by name during animation setup.
typedef map<const char*, LegoHideAnimStruct, LegoHideAnimStructComparator> LegoHideAnimStructMap;

/// [AI] Presenter class responsible for controlling animations that hide or show actors based on animation nodes.
/// Extends LegoLoopingAnimPresenter to synchronise the visibility state of ROI and boundaries according to animation data.
/// During setup, this presenter maps animation node names to relevant world boundaries, and on tick, updates visibility.
/// VTABLE: LEGO1 0x100d9278
/// SIZE 0xc4 [AI]
class LegoHideAnimPresenter : public LegoLoopingAnimPresenter {
public:
	/// [AI] Constructor. Initializes boundary mapping.
	LegoHideAnimPresenter();
	/// [AI] Destructor. Destroys presenter and cleans up boundary mapping.
	~LegoHideAnimPresenter() override;

	// FUNCTION: LEGO1 0x1006d860
	/// [AI] Virtual method, no-op in this class. [AI_SUGGESTED_NAME: OnCustomTick]
	void VTable0x8c() override {} // vtable+0x8c

	// FUNCTION: LEGO1 0x1006d870
	/// [AI] Virtual method, no-op in this class. [AI_SUGGESTED_NAME: OnPostAnimationTick]
	void VTable0x90() override {} // vtable+0x90

	// FUNCTION: BETA10 0x1005d4a0
	/// [AI] Returns the class name string for this presenter type. Used by PresenterNameDispatch.
	/// @return Static string identifier "LegoHideAnimPresenter" [AI]
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f06cc
		return "LegoHideAnimPresenter";
	}

	// FUNCTION: LEGO1 0x1006d880
	// FUNCTION: BETA10 0x1005d470
	/// [AI] Returns the runtime class name of the object.
	/// @return String name from HandlerClassName [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	// FUNCTION: LEGO1 0x1006d890
	/// [AI] Checks if object is of the given class or a parent class (runtime type checking).
	/// @param p_name Name of the class to check [AI]
	/// @return True if class matches, otherwise delegate to parent [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || LegoAnimPresenter::IsA(p_name);
	}

	/// [AI] Called when presenter is in the Ready state; maps boundaries to animation nodes and adds presenter to world update list if required.
	void ReadyTickle() override;      // vtable+0x18
	/// [AI] Called during the Starting state tick; if streaming state is reached, prepares boundary mappings and sets frame visibilities.
	void StartingTickle() override;   // vtable+0x18
	/// [AI] Adds the presenter to the tickle manager; delegates to base animation presenter registration.
	MxResult AddToManager() override; // vtable+0x34
	/// [AI] Destroys the presenter, optionally from destructor; cleans up resources and removes from world.
	void Destroy() override;          // vtable+0x38
	/// [AI] Called when the associated DSAction has ended, cleans up and removes presenter from the world.
	void EndAction() override;        // vtable+0x40
	/// [AI] Advances the animation by one frame (no-op here; implemented in other presenter classes).
	void PutFrame() override;         // vtable+0x6c

	/// [AI]
	/// Traverses the animation node hierarchy starting at the root and synchronizes visibility
	/// flags for all associated ROI and boundary nodes according to current animation frame time.
	/// @param p_time The time/frame whose visibilities should be applied [AI]
	void FUN_1006db40(LegoTime p_time);

private:
	/// [AI] Initializes presenter state and internal mapping.
	void Init();
	/// [AI] Destroys internal resources; deletes boundary array and resets state. Calls public Destroy if not in destructor context.
	/// @param p_fromDestructor True if called from the destructor to avoid recursive destruction [AI]
	void Destroy(MxBool p_fromDestructor);

	/// [AI] Helper to recursively apply visibility (or other) state to ROI and boundary objects for each animation node for a given frame.
	/// @param p_node Current animation tree node to process [AI]
	/// @param p_time The animation frame time [AI]
	void FUN_1006db60(LegoTreeNode* p_node, LegoTime p_time);

	/// [AI]
	/// Rebuilds the mapping from animation node names to world path boundaries.
	/// Recursively traverses the animation tree and fills boundary map using names for quick lookup in per-frame update.
	void FUN_1006dc10();

	/// [AI]
	/// Recursively traverses the animation tree and populates the boundary name->struct map, associating animation node names with boundary objects.
	/// @param p_map Reference to boundary mapping structure [AI]
	/// @param p_node Current node in the animation tree [AI]
	void FUN_1006e3f0(LegoHideAnimStructMap& p_map, LegoTreeNode* p_node);

	/// [AI]
	/// Adds a mapping between an animation node and a world path boundary (by name) into the map if not present;
	/// assigns a unique index for mapping during runtime.
	/// @param p_map Reference to boundary struct map [AI]
	/// @param p_data Animation node data [AI]
	/// @param p_name Name of the animation node/boundary [AI]
	/// @param p_boundary Path boundary instance to associate [AI]
	void FUN_1006e470(
		LegoHideAnimStructMap& p_map,
		LegoAnimNodeData* p_data,
		const char* p_name,
		LegoPathBoundary* p_boundary
	);

	LegoPathBoundary** m_boundaryMap; ///< [AI] Array mapping node indices to boundary pointers. Rebuilt each time scene/animation changes, used for fast per-frame visibility/state synchronization.
};

// clang-format off
// SYNTHETIC: LEGO1 0x1006d9d0
// LegoHideAnimPresenter::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1006ddb0
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::~_Tree<char const *,pair<ch

// TEMPLATE: LEGO1 0x1006de80
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::iterator::_Inc

// TEMPLATE: LEGO1 0x1006dec0
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::erase

// TEMPLATE: LEGO1 0x1006e310
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Erase

// TEMPLATE: LEGO1 0x1006e350
// Map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator>::~Map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator>

// TEMPLATE: LEGO1 0x1006e3a0
// map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::~map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >

// TEMPLATE: LEGO1 0x1006e6d0
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::iterator::_Dec

// TEMPLATE: LEGO1 0x1006e720
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Insert

// GLOBAL: LEGO1 0x100f768c
// _Tree<char const *,pair<char const * const,LegoHideAnimStruct>,map<char const *,LegoHideAnimStruct,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Kfn,LegoHideAnimStructComparator,allocator<LegoHideAnimStruct> >::_Nil
// clang-format on

#endif // LEGOHIDEANIMPRESENTER_H