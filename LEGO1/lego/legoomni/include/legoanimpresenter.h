#ifndef LEGOANIMPRESENTER_H
#define LEGOANIMPRESENTER_H

#include "legoroilist.h"
#include "mxatom.h"
#include "mxvideopresenter.h"

/**
 * @brief [AI] Forward declaration for the LegoAnim animation object. 
 *
 * @details [AI] Represents a full animation resource for complex articulated objects or characters. Used by LegoAnimPresenter for animation playback state.
 */
class LegoAnim;

/**
 * @brief [AI] Forward declaration for world context in which animation takes place.
 *
 * @details [AI] Represents a complete simulation space, home to all Lego entities, animation, and logic. LegoAnimPresenter ties its lifecycle to a LegoWorld.
 */
class LegoWorld;

/**
 * @brief [AI] Forward declaration for path-boundary, used for actor placement and animation.
 *
 * @details [AI] Represents an area or a path within the simulation where actors can be bound or moved. Used by VTable0x98 specialization.
 */
class LegoPathBoundary;

class MxMatrix;
class Vector3;

/**
 * @brief [AI] Comparator for anim struct maps using string (char*) keys.
 *
 * @details [AI] This comparator is used in maps with const char* keys to provide ordering via C-style strcmp. Ensures consistent lookup and avoids pointer alias issues.
 */
struct LegoAnimStructComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const { return strcmp(p_a, p_b) < 0; }
};

/**
 * @brief [AI] Comparator for substition map lookups using string (char*) keys.
 *
 * @details [AI] Used as the comparator in LegoAnimSubstMap to order animation variable substitution keys consistently.
 */
struct LegoAnimSubstComparator {
	MxBool operator()(const char* const& p_a, const char* const& p_b) const { return strcmp(p_a, p_b) < 0; }
};

/**
 * @brief [AI] Maps an ROI and index for animation nodes/actors.
 * 
 * @details [AI] Used for associating a named animation resource or actor instance with its model (ROI) and a 1-based index. 
 * This is critical for matching animation channels to scene objects.
 */
struct LegoAnimStruct {
	LegoROI* m_roi; ///< Associated LEGO Region of Interest (ROI) for animation [AI]
	MxU32 m_index;  ///< Index value for lookup or ordering [AI]
};

/**
 * @brief [AI] Mapping from string names to LegoAnimStruct. 
 * 
 * @details [AI] Used for quick lookup of actors and their ROIs during animation building and frame evaluation in the presenter.
 */
typedef map<const char*, LegoAnimStruct, LegoAnimStructComparator> LegoAnimStructMap;

/**
 * @brief [AI] Mapping for macro or variable substitutions in animation resource parsing.
 * 
 * @details [AI] Used to swap symbolic names in animation resources for real runtime values, e.g., unit/actor names or parameters.
 */
typedef map<const char*, const char*, LegoAnimSubstComparator> LegoAnimSubstMap;

/**
 * @class LegoAnimPresenter
 * @brief [AI] Handles playback and synchronization of animated LEGO objects, including variable substitution, ROI mapping, and direct control over animation tick cycle.
 * 
 * @details [AI] The LegoAnimPresenter class is a specialized presenter for animated sequences in LEGO Island.
 * It extends MxVideoPresenter and supports advanced operations including variable substitution, actor/ROI mapping, 
 * direct control of streaming and tickling, as well as integration with LegoWorld and other engine modules.
 * 
 * This presenter is responsible for:
 * - Resource loading and parsing (including variable/macro substition).
 * - Proper mapping of animation nodes to scene ROIs.
 * - Applying transformations, updating positions/orientation, controlling visibility, etc.
 * - Handling specialized callbacks, tickle state transitions (Ready, Starting, Streaming, etc.) and variable overrides.
 * - Integrating with composite presenters, variable tables, path boundaries, and world notification system.
 *
 * State and resource management are handled using a combination of protected helper functions and public tickle hooks.
 * 
 * Size: 0xbc bytes. Part of the LEGO1 main engine codebase.
 */
class LegoAnimPresenter : public MxVideoPresenter {
public:
	/**
	 * @brief [AI] Animation presenter flags
	 * 
	 * @details [AI] c_hideOnStop: Hides animated ROIs when playback stops.
	 * c_mustSucceed: Animation must successfully bind/match all targets before starting.
	 */
	enum {
		c_hideOnStop = 0x01, ///< Hide animated objects after stopping [AI]
		c_mustSucceed = 0x02 ///< Require all animation targets be satisfied [AI]
	};

	/**
	 * @brief [AI] Constructor for LegoAnimPresenter. Initializes all internal structures and states.
	 */
	LegoAnimPresenter();

	/**
	 * @brief [AI] Destructor for LegoAnimPresenter. Finalizes and releases all held resources, actors, and variables.
	 */
	~LegoAnimPresenter() override;

	/**
	 * @brief [AI] Returns the class name for this presenter ("LegoAnimPresenter"). Used for RTTI and dispatch.
	 * @return Static string representing the handler class name [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] RTTI name for the presenter ("LegoAnimPresenter"), used for string-based identification.
	 * @return Class name string [AI]
	 */
	const char* ClassName() const override;

	/**
	 * @brief [AI] Checks if this or a parent class matches the given type name for RTTI.
	 * @param p_name Type name string for checking [AI]
	 * @return True if type matches or is a parent type; false otherwise [AI]
	 */
	MxBool IsA(const char* p_name) const override;

	/**
	 * @brief [AI] Called when the presenter is in the "Ready" tickle state. Handles loading animation resource and progressing to Start.
	 */
	void ReadyTickle() override;

	/**
	 * @brief [AI] Called at the "Starting" tickle state. Applies substitutions, constructs ROI/actor maps, and prepares the animation to begin streaming.
	 */
	void StartingTickle() override;

	/**
	 * @brief [AI] Tickle function during streaming (active animation). Advances animation, releases frames, and checks streaming completion.
	 */
	void StreamingTickle() override;

	/**
	 * @brief [AI] Called when animation streaming completes; triggers notification and wraps up state.
	 */
	void DoneTickle() override;

	/**
	 * @brief [AI] Extra data parser for animation presenter. Reads named options (substitution, world binding, etc) from resource chunk.
	 */
	void ParseExtra() override;

	/**
	 * @brief [AI] Adds this presenter instance to the relevant presenter/notification manager.
	 * @return Result indicating success or failure. [AI]
	 */
	MxResult AddToManager() override;

	/**
	 * @brief [AI] Releases all internal resources, actors, maps, and presenter state.
	 */
	void Destroy() override;

	/**
	 * @brief [AI] Begin playback action using a stream and a given action descriptor. Also resets displayZ for 3D layer.
	 * @param p_controller Stream controller, provides actual data source (RAM or disk). [AI]
	 * @param p_action DS Action data, describes animation meta. [AI]
	 * @return Result indicating success or error. [AI]
	 */
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) override;

	/**
	 * @brief [AI] Completes playback action, triggers world notification and resets/hides all animated actors depending on flags.
	 */
	void EndAction() override;

	/**
	 * @brief [AI] Called once per frame to push updated animation information (transform, position, etc.) to the ROIs.
	 */
	void PutFrame() override;

	/**
	 * @brief [AI] Creates/loads the LegoAnim resource instance from a stream chunk buffer.
	 * @param p_chunk Animation data chunk (streamed or loaded). [AI]
	 * @return Result indicating success of the parsing/loading operation. [AI]
	 */
	virtual MxResult CreateAnim(MxStreamChunk* p_chunk);

	/**
	 * @brief [AI] Virtual callback for future expansion. Unused in current base. [AI]
	 */
	virtual void VTable0x8c();

	/**
	 * @brief [AI] Virtual callback for future expansion. Unused in current base. [AI]
	 */
	virtual void VTable0x90();

	/**
	 * @brief [AI] Tests if a swept segment (defined by v1, v2, f1, f2) collides any of this presenter's animated ROIs.
	 * Used for advanced hit-testing.
	 * @param p_v1 Start vector [AI]
	 * @param p_v2 Direction vector [AI]
	 * @param p_f1 Distance along the direction [AI]
	 * @param p_f2 Tolerance/radius [AI]
	 * @param p_v3 Output intersection or closest point [AI]
	 * @return TRUE if hit, FALSE otherwise [AI]
	 */
	virtual MxU32 VTable0x94(Vector3& p_v1, Vector3& p_v2, float p_f1, float p_f2, Vector3& p_v3);

	/**
	 * @brief [AI] Adds all actor ROIs, associated with this animation, to the provided path boundary for grouping or path following.
	 * @param p_boundary Path boundary to receive actors [AI]
	 * @return SUCCESS if all actors are added, FAILURE otherwise [AI]
	 */
	virtual MxResult VTable0x98(LegoPathBoundary* p_boundary);

	/**
	 * @brief [AI] Returns the mapping array from animation node index to LegoROI*. Used to accelerate transform updates.
	 * @param p_roiMapSize Output, number of elements in the roiMap array [AI]
	 * @return Internal ROI map [AI]
	 */
	virtual LegoROI** GetROIMap(MxU32& p_roiMapSize);

	/**
	 * @brief [AI] Sets the baseline transform for the animation. May be used to drive/override animation root node origin.
	 * @param p_matrix Matrix with the new baseline transformation [AI]
	 */
	virtual void VTable0xa0(Matrix4& p_matrix);

	/**
	 * @brief [AI] Fills a matrix array with each node's local-to-world transform after animation advance (for state change / blending).
	 * @param p_matrix Output: matrix array (1-based index, size = mapSize+1) [AI]
	 * @param p_und Animation time or interpolation parameter [AI]
	 * @return SUCCESS if filled; FAILURE on allocation or missing ROI [AI]
	 */
	MxResult FUN_1006afc0(MxMatrix*& p_matrix, float p_und);

	/**
	 * @brief [AI] Calculates a blended transformation for a target ROI and applies as base transform for this animation.
	 * @param p_roi Target ROI to align with animation [AI]
	 * @return SUCCESS if transform arrived at, FAILURE otherwise [AI]
	 */
	MxResult FUN_1006b140(LegoROI* p_roi);

	/**
	 * @brief [AI] Immediately completes this animation, updates all ROIs to their final pose. [AI]
	 */
	void FUN_1006c7a0();

	/**
	 * @brief [AI] Gets the name of the object associated with the current animation action.
	 * @return Object name, as string pointer [AI]
	 */
	const char* GetActionObjectName();

	/**
	 * @brief [AI] Sets the world used by this presenter for actor placement and notification.
	 * @param p_currentWorld World to be associated. [AI]
	 */
	void SetCurrentWorld(LegoWorld* p_currentWorld) { m_currentWorld = p_currentWorld; }

	/**
	 * @brief [AI] Sets the value of internal flag m_unk0x9c to 1. Related to transform blending/handoff.
	 */
	void SetUnknown0x0cTo1() { m_unk0x9c = 1; }

	/**
	 * @brief [AI] Sets a pointer to the baseline animation transform.
	 * @param p_unk0xa0 Matrix pointer, assumed granted to presenter [AI]
	 */
	void SetUnknown0xa0(Matrix4* p_unk0xa0) { m_unk0xa0 = p_unk0xa0; }

	/**
	 * @brief [AI] Returns the current animation resource in use.
	 * @return Pointer to LegoAnim object [AI]
	 */
	LegoAnim* GetAnimation() { return m_anim; }

protected:
	/**
	 * @brief [AI] Allocates and resets all internal presenter state. Helper for constructor and re-init.
	 */
	void Init();

	/**
	 * @brief [AI] Releases all dynamic memory, unbinds actors from animation, and resets references.
	 * @param p_fromDestructor True if called by destructor, false for explicit destroy [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] [Internal] String construction utility used in actor/ROI naming substitution. Used when an actor string begins with a marker.
	 * @param p_und1 Source actor string, possibly with marker. [AI]
	 * @return Newly allocated string with substituted or resolved value [AI]
	 */
	LegoChar* FUN_10069150(const LegoChar* p_und1);

	/**
	 * @brief [AI] Populates m_unk0x74 with all relevant ROIs/actors for this animation by iterating actors in the animation resource.
	 */
	void FUN_100692b0();

	/**
	 * @brief [AI] Scans the world view compound objects to find and collect relevant ROIs for animation, populating m_unk0x70.
	 */
	void FUN_100695c0();

	/**
	 * @brief [AI] Returns a composed name string for combining variable substitution and direct actor references for name lookup.
	 * @param p_und1 Source string [AI]
	 * @param p_und2 Optional prefix, NULL if unused [AI]
	 * @return Newly allocated string encoding full actor/ROI name [AI]
	 */
	LegoChar* FUN_100697c0(const LegoChar* p_und1, const LegoChar* p_und2);

	/**
	 * @brief [AI] Locates (and adds to m_unk0x70) an ROI in a compound object by substituted name, matching either direct or indirect name reference.
	 * @param p_rois CompoundObject: the object list to search [AI]
	 * @param p_und2 Name string for matching [AI]
	 * @return TRUE if found/matched, FALSE otherwise [AI]
	 */
	LegoBool FUN_100698b0(const CompoundObject& p_rois, const LegoChar* p_und2);

	/**
	 * @brief [AI] Looks up an ROI in m_unk0x70 by substituted name.
	 * @param p_und Substituted name string [AI]
	 * @return ROI pointer if found, NULL otherwise [AI]
	 */
	LegoROI* FUN_100699e0(const LegoChar* p_und);

	/**
	 * @brief [AI] Builds mapping from animation node data names to ROIs, fills m_roiMap and m_roiMapSize.
	 */
	void FUN_10069b10();

	/**
	 * @brief [AI] Recursive helper for building ROI map: walks animation node tree, matching names to ROIs at each node level.
	 * @param p_map Output: current name-to-struct map [AI]
	 * @param p_node Current tree node [AI]
	 * @param p_roi Current ROI being matched [AI]
	 */
	void FUN_1006a3c0(LegoAnimStructMap& p_map, LegoTreeNode* p_node, LegoROI* p_roi);

	/**
	 * @brief [AI] Helper to insert an animation node's data into the map (adding new struct if not already inserted).
	 * @param p_map Output: current name-to-struct map [AI]
	 * @param p_data Animation node data for current entry [AI]
	 * @param p_und Substituted name string [AI]
	 * @param p_roi ROI being matched [AI]
	 */
	void FUN_1006a4f0(LegoAnimStructMap& p_map, LegoAnimNodeData* p_data, const LegoChar* p_und, LegoROI* p_roi);

	/**
	 * @brief [AI] Releases all actors in m_unk0x74 via CharacterManager, respecting state flag m_unk0x96.
	 */
	void FUN_1006aa60();

	/**
	 * @brief [AI] Invokes end-of-animation logic via AnimationManager, depending on mode flag m_unk0x96.
	 */
	void FUN_1006ab70();

	/**
	 * @brief [AI] Returns TRUE if every animation actor/ROI node is bound successfully. Used as precondition if c_mustSucceed set.
	 */
	LegoBool FUN_1006aba0();

	/**
	 * @brief [AI] Recursively validates correct ROI matching/binding in animation tree (helper for FUN_1006aba0).
	 * @param p_node Animation node [AI]
	 * @param p_roi Currently considered ROI [AI]
	 * @return TRUE if matched through all children, FALSE otherwise [AI]
	 */
	MxBool FUN_1006abb0(LegoTreeNode* p_node, LegoROI* p_roi);

	/**
	 * @brief [AI] Applies all queued variable substitutions in the animation resource by setting corresponding VariableTable entries.
	 */
	void SubstituteVariables();

	/**
	 * @brief [AI] Steps animation nodes to 'p_time' using transform 'p_matrix', using fast path for tree traversal. Helper for incremental frame advance.
	 * @param p_anim Animation resource [AI]
	 * @param p_time Animation time [AI]
	 * @param p_matrix Optional transform [AI]
	 */
	void FUN_1006b900(LegoAnim* p_anim, MxLong p_time, Matrix4* p_matrix);

	/**
	 * @brief [AI] Like FUN_1006b900, but also processes associated camera animation if present.
	 * @param p_anim Animation resource [AI]
	 * @param p_time Animation time [AI]
	 * @param p_matrix Optional transform [AI]
	 */
	void FUN_1006b9a0(LegoAnim* p_anim, MxLong p_time, Matrix4* p_matrix);

	/**
	 * @brief [AI] Enables or disables internal state (LegoEntity c_altBit1) on all animated entities.
	 * @param p_bool True to set, false to clear [AI]
	 */
	void FUN_1006c8a0(MxBool p_bool);

	/** 
	 * @brief [AI] Animation resource currently being played back.
	 * @details [AI] Owns the loaded LegoAnim animation, which may be swapped for each new media action.
	 */
	LegoAnim* m_anim;             

	/**
	 * @brief [AI] Lookup array to map animation node indices to scene ROIs (1-based index).
	 * @details [AI] Used for fast node transform updates and collision checks.
	 */
	LegoROI** m_roiMap;           

	/**
	 * @brief [AI] Number of valid entries in m_roiMap (excluding 0th index).
	 */
	MxU32 m_roiMapSize;           

	/**
	 * @brief [AI] List of ROIs used during preprocessing, actor matching, or variable substitution (purpose varies).
	 */
	LegoROIList* m_unk0x70;       

	/**
	 * @brief [AI] List of actors/ROIs created or acquired for this animation instance.
	 * @details [AI] Used for cleanup, visibility toggling, and releasing actors at the end.
	 */
	LegoROIList* m_unk0x74;       

	/**
	 * @brief [AI] Pointer to root/offset MxMatrix used for transform computations.
	 * @details [AI] Used for overall local-to-world transform; may be updated on each action/tickle segment.
	 */
	Matrix4* m_unk0x78;           

	/**
	 * @brief [AI] Animation presenter flags (hide-on-stop, must-succeed, etc).
	 */
	MxU32 m_flags;                

	/**
	 * @brief [AI] Reference to the world in which this presenter is currently placed/active.
	 * @details [AI] Updated on tickle and used for actor placement/scenes.
	 */
	LegoWorld* m_currentWorld;    

	/**
	 * @brief [AI] String identifier for the target world (if set in animation resource via extra data).
	 */
	MxAtomId m_worldAtom;         

	/**
	 * @brief [AI] Numeric world ID for world selection/lookup.
	 * @details [AI] -1 means no explicit world.
	 */
	MxS32 m_worldId;              

	/**
	 * @brief [AI] Lookup array for secondary ROI objects (used for e.g. camera animation attached ROIs by name).
	 */
	LegoROI** m_unk0x8c;          

	/**
	 * @brief [AI] Array of char* names used for selecting camera attached ROIs (from ptatcam extra parameter).
	 */
	char** m_unk0x90;             

	/**
	 * @brief [AI] Count of valid camera attached ROI names in m_unk0x90 / m_unk0x8c.
	 */
	MxU8 m_unk0x94;               

	/**
	 * @brief [AI] Boolean: indicates streaming/animation is finished and presenter should progress to Done state.
	 */
	MxBool m_unk0x95;             

	/**
	 * @brief [AI] Boolean/mode: influences actor release vs animation manager cleanup selection (see FUN_1006ab70).
	 */
	MxBool m_unk0x96;             

	/**
	 * @brief [AI] Unknown/unused byte, for possible explicit alignment or hidden flag. [AI_SUGGESTED_NAME: m_padding0x97]
	 */
	undefined m_unk0x97;          

	/**
	 * @brief [AI] Table of macro/variable substitutions to apply before animation begins (from resource "subst" field).
	 */
	LegoAnimSubstMap* m_substMap; 

	/**
	 * @brief [AI] Int16 state flag, set via SetUnknown0x0cTo1(). Related to animation handoff/transform alignment.
	 */
	MxS16 m_unk0x9c;              

	/**
	 * @brief [AI] Optional pointer to a matrix storing a blended/baseline local-to-world transform.
	 */
	Matrix4* m_unk0xa0;           

public:
	/**
	 * @brief [AI] Animation touch radius for path boundary checks and state (set from resource).
	 */
	float m_unk0xa4;          

	/**
	 * @brief [AI] 3D float property, used for animation base position offset.
	 */
	Mx3DPointFloat m_unk0xa8; 
};

#endif // LEGOANIMPRESENTER_H
