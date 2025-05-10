#ifndef LEGOANIMACTOR_H
#define LEGOANIMACTOR_H

#include "decomp.h"
#include "legopathactor.h"

class LegoAnim;

/// \struct LegoAnimActorStruct
/// \brief [AI] Holds per-animation instance data for a LegoAnimActor. Binds an animation tree, a mapping of ROI pointers, and a time parameter.
/// \details [AI] Each LegoAnimActorStruct encapsulates all the data needed to represent a concrete animation map for a LegoAnimActor, including duration parameter for animation LOD/selection, a pointer to the animation tree, a mapping from animation nodes to LegoROI objects for mesh assignment, and extra state vectors used in animation.
///
struct LegoAnimActorStruct {
	/// \brief [AI] Constructs a LegoAnimActorStruct, associating animation tree and ROI map. See source for param meanings.
	/// \param p_unk0x00 Animation selection/duration threshold [AI]
	/// \param p_AnimTreePtr Pointer to the animation root (LegoAnim tree) [AI]
	/// \param p_roiMap Mapping of animation tree nodes to LegoROI pointers [AI]
	/// \param p_numROIs Number of ROI pointers in the map [AI]
	LegoAnimActorStruct(float p_unk0x00, LegoAnim* p_AnimTreePtr, LegoROI** p_roiMap, MxU32 p_numROIs); ///< [AI]

	/// \brief [AI] Destructor: Deallocates dynamic vector data associated with the animation entry.
	~LegoAnimActorStruct();

	/// \brief [AI] Gets the length, in seconds, of the animation (delegates to anim tree).
	/// \details [AI] Calls GetDuration() on m_AnimTreePtr.
	float GetDuration();

	/// \brief [AI] Gets the selection/duration/animation threshold value associated with this entry.
	float GetUnknown0x00() { return m_unk0x00; }

	/// \brief [AI] Returns the root animation tree node for this mapping.
	LegoAnim* GetAnimTreePtr() { return m_AnimTreePtr; }

	/// \brief [AI] Returns the mapping of tree nodes to LegoROI pointers (array of pointers, one per mesh/node).
	LegoROI** GetROIMap() { return m_roiMap; }

	// TODO: Possibly private
	float m_unk0x00;              ///< [AI] Animation activation/duration threshold (used to decide which animation is active) [AI]
	LegoAnim* m_AnimTreePtr;      ///< [AI] Root of animation tree for this animation [AI]
	LegoROI** m_roiMap;           ///< [AI] Mapping of animation nodes to LEGO ROIs (meshes) [AI]
	MxU32 m_numROIs;              ///< [AI] Number of entries in ROI map [AI]
	vector<undefined*> m_unk0x10; ///< [AI] Holds per-instance temporary or auxiliary animation data [AI_SUGGESTED_NAME: tempAnimationData]
};

/// \class LegoAnimActor
/// \brief [AI] Path-based actor which supports skeletal/mesh animation via an animation tree and multiple animation to mesh mappings.
/// \details [AI] Inherits from LegoPathActor and adds support for multiple animation mappings, switching animation sets according to speed, and advanced animation-ROI mapping. Animations are selected based on movement speed and are applied by transforming mesh nodes according to the animation tree.
///
class LegoAnimActor : public virtual LegoPathActor {
public:
	/// \brief [AI] Initializes LegoAnimActor and sets the current animation index to -1.
	LegoAnimActor() { m_curAnim = -1; } ///< [AI]

	/// \brief [AI] Destructor cleans up all animation map structures.
	~LegoAnimActor() override; ///< [AI]

	/// \brief [AI] Handles extra action strings, looks for animation assignments and delegates to presenters (overrides parent).
	/// \details [AI] Parses key-value action strings (e.g., "ANIMATION:...") and configures animation properties accordingly. [AI]
	/// \param p_extra Extra action string, may contain animation info [AI]
	void ParseAction(char* p_extra) override;          // vtable+0x20

	/// \brief [AI] Sets the current world speed and chooses which animation (from the animation map list) should be used; see source for selection logic.
	/// \param p_worldSpeed Current world speed, typically as set by entity movement [AI]
	void SetWorldSpeed(MxFloat p_worldSpeed) override; // vtable+0x30

	/// \brief [AI] Performs per-frame update; applies the appropriate animation to mesh ROIs based on speed and state.
	/// \details [AI] Applies transforms to ROI meshes using selected animation tree; falls back to parent behavior if not in appropriate state. [AI]
	/// \param p_time Current time or frame time [AI]
	void Animate(float p_time) override;               // vtable+0x70

	/// \brief [AI] Applies the current animation's transforms to the provided matrix, propagates to mesh hierarchies. [AI]
	/// \param p_transform Reference to output transform matrix [AI]
	void VTable0x74(Matrix4& p_transform) override;    // vtable+0x74

	/// \brief [AI] Computes the animation phase offset within the current animation, adjusts for looping.
	/// \param p_und (out) Animation time/phase delta from start or looppoint [AI]
	/// \return MxResult indicating success or failure [AI]
	virtual MxResult FUN_1001c1f0(float& p_und); ///< [AI_SUGGESTED_NAME: ComputeAnimationPhase]

	/// \brief [AI] Applies the animation transform for the current animation at the given phase, writes to matrix.
	/// \param p_und Animation phase within loop [AI]
	/// \param p_transform Transform/output to apply results [AI]
	/// \return MxResult indicating success or failure [AI]
	virtual MxResult FUN_1001c360(float p_und, Matrix4& p_transform); ///< [AI_SUGGESTED_NAME: ApplyAnimationTransform]

	/// \brief [AI] Adds a new animation mapping (LegoAnimActorStruct) with a tree, threshold, and mesh mapping.
	/// \param p_AnimTreePtr Pointer to the animation tree [AI]
	/// \param p_unk0x00 Selection threshold/timing parameter [AI]
	/// \param p_roiMap Mesh objects to bind to nodes [AI]
	/// \param p_numROIs Number of mesh bindings [AI]
	/// \return MxResult indicating if successfully inserted [AI]
	virtual MxResult FUN_1001c450(LegoAnim* p_AnimTreePtr, float p_unk0x00, LegoROI** p_roiMap, MxU32 p_numROIs); ///< [AI_SUGGESTED_NAME: AddAnimationMap]

	/// \brief [AI] Deallocates all animation map structures and selects no animation; resets current animation index.
	virtual void ClearMaps(); ///< [AI]

	/// \brief [AI] Returns the class name string for RTTI and type checking.
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoAnimActor";
	}

	/// \brief [AI] Checks for runtime type equality ("IsA" support); matches for this class or parent.
	/// \param p_name Class name string [AI]
	/// \details [AI] Returns true if p_name matches LegoAnimActor or any parent type.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoAnimActor::ClassName()) || LegoPathActor::IsA(p_name);
	}

protected:
	vector<LegoAnimActorStruct*> m_animMaps; ///< [AI] List of animation structures, each representing a valid animation for different speed/phase ranges. [AI]
	MxS16 m_curAnim;                         ///< [AI] Index of currently selected animation map (-1 if none active). [AI]
};

#endif // LEGOANIMACTOR_H
