#ifndef LEGOBUILDINGMANAGER_H
#define LEGOBUILDINGMANAGER_H

#include "decomp.h"
#include "misc/legotypes.h"
#include "mxcore.h"

class LegoEntity;
class LegoROI;
class LegoStorage;
class LegoWorld;
class LegoCacheSound;
class LegoPathBoundary;

/// @struct LegoBuildingInfo
/// @brief [AI] Describes the state, configuration, and world placement of a single LEGO building entity, including its animation, sound, mood, and boundary location properties.
/// @details [AI] This structure is used by LegoBuildingManager to store and manage information for each building in the world. It contains various fields relating to each building's current variant, position, boundary, and behavioral state. [AI]
struct LegoBuildingInfo {
	enum {
		c_hasVariants = 0x01,  ///< [AI] This building has multiple variant models (for switching appearance) [AI]
		c_hasSounds = 0x02,    ///< [AI] This building supports multiple sounds [AI]
		c_hasMoves = 0x04,     ///< [AI] This building supports animation cycling [AI]
		c_hasMoods = 0x08      ///< [AI] This building supports mood changes [AI]
	};

	LegoEntity* m_entity;         ///< [AI] Associated entity in the world for this building [AI]
	const char* m_variant;        ///< [AI] Name of the building's current variant (model name/ID) [AI]
	MxU32 m_sound;                ///< [AI] Index or ID of current sound selection [AI]
	MxU32 m_move;                 ///< [AI] Index or ID of current animation state [AI]
	MxU8 m_mood;                  ///< [AI] Current mood index (0-3) [AI]
	MxS8 m_unk0x11;               ///< [AI] Counter or state value for construction/demolition progress [AI]
	MxS8 m_initialUnk0x11;        ///< [AI] Initial value for m_unk0x11, used for state resets or persistence [AI]
	MxU8 m_flags;                 ///< [AI] Bitfield of building properties (see enum above) [AI]
	float m_unk0x14;              ///< [AI] World height or vertical offset for this building [AI]
	const char* m_boundaryName;   ///< [AI] Name label of the boundary zone for this building (used to find LegoPathBoundary) [AI]
	float m_x;                    ///< [AI] World X coordinate for the building's ground placement [AI]
	float m_y;                    ///< [AI] World Y coordinate for the building's ground placement [AI]
	float m_z;                    ///< [AI] World Z coordinate for the building's ground placement [AI]
	LegoPathBoundary* m_boundary; ///< [AI] Pointer to the world boundary (collision/trigger volume) [AI]
};

/// @class LegoBuildingManager
/// @brief [AI] Manages LEGO buildings in the world, including their state, animation, switching, saving/loading, and scheduling of animations.
/// @details [AI] This manager handles all building-related logic for LEGO Island, providing per-building state storage (via LegoBuildingInfo) and operations for visual/audio/mood switching, construction/demolition sequence, and animation/physics scheduling. It also implements serialization into LegoStorage and exposes relevant configuration and access APIs. [AI]
// VTABLE: LEGO1 0x100d6f50
// SIZE 0x30
class LegoBuildingManager : public MxCore {
public:
	/// @struct AnimEntry
	/// @brief [AI] Tracks and schedules a single animation entry for a building with sound and timer information, for use with the tickling/animation update system.
	/// @details [AI] Each AnimEntry corresponds to a scheduled animation effect for a building entity (often triggered by construction/demolition), linking the entity, its ROI, timing, the current animation Y offset, and whether sound should play during the event. [AI]
	struct AnimEntry {
		LegoEntity* m_entity; ///< [AI] The building entity being animated [AI]
		LegoROI* m_roi;       ///< [AI] ROI used for transformations and updates [AI]
		MxLong m_time;        ///< [AI] Target future time when the animation should complete [AI]
		float m_unk0x0c;      ///< [AI] Internal Y offset for vertical bouncy animation (demolition effect) [AI]
		MxBool m_muted;       ///< [AI] TRUE if sound should be muted for this animation [AI]
	};

	/// @brief [AI] Constructor. Initializes state and building info array (see Init()).
	LegoBuildingManager();

	/// @brief [AI] Destructor. Cleans up scheduled animation file string and resets manager state.
	~LegoBuildingManager() override;

	/// @brief [AI] Tick updates for scheduled animation: animates buildings scheduled in m_entries, triggers sound, does hiding or motion, then unregisters self if no more animations remain.
	MxResult Tickle() override; // vtable+0x08

	/// @brief [AI] Returns the runtime class name for this manager.
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoBuildingManager";
	}

	/// @brief [AI] Configure static settings for the LegoBuildingManager globally.
	/// @param p_buildingManagerConfig [AI] New configuration value (affects switching and initialization behavior).
	static void configureLegoBuildingManager(MxS32 p_buildingManagerConfig);

	/// @brief [AI] Sets the global filename for a custom "customize animation" SMK/FLC file.
	/// @param p_value [AI] C-string path, or NULL to clear.
	static void SetCustomizeAnimFile(const char* p_value);

	/// @brief [AI] Initializes all manager fields, resets animation tracking, and loads the default building info array.
	void Init();

	/// @brief [AI] Loads/creates building models for the current world, sets up variants appropriately for current config, and manages building visibility.
	void LoadWorldInfo();

	/// @brief [AI] Spawns and configures a building entity and its ROI based on world/array index.
	/// @param p_index [AI] The index into static building info array.
	/// @param p_world [AI] The LegoWorld to place the building in.
	void CreateBuilding(MxS32 p_index, LegoWorld* p_world);

	/// @brief [AI] Removes all building-state links to world entities and cancels/cleans any scheduled animation entries.
	void Reset();

	/// @brief [AI] Serializes current building state to the given storage.
	/// @param p_storage [AI] The storage to write to.
	/// @return [AI] SUCCESS, or FAILURE on error
	MxResult Write(LegoStorage* p_storage);

	/// @brief [AI] Restores data from serialized building state in the given storage.
	/// @param p_storage [AI] The storage to read from.
	/// @return [AI] SUCCESS or FAILURE
	MxResult Read(LegoStorage* p_storage);

	/// @brief [AI] Locates the building info entry for a specific building entity.
	/// @param p_entity [AI] Building entity pointer (LegoEntity)
	/// @return [AI] Pointer to the corresponding LegoBuildingInfo, or NULL if not found.
	LegoBuildingInfo* GetInfo(LegoEntity* p_entity);

	/// @brief [AI] Attempts to switch the building variant for the specified entity (e.g. changes type of house). Returns TRUE on success. Does nothing if config disables variants or not eligible.
	/// @param p_entity [AI] Building entity
	/// @return [AI] TRUE if switched, FALSE otherwise.
	MxBool SwitchVariant(LegoEntity* p_entity);

	/// @brief [AI] Cycles the current active sound for a building (if sounds available).
	/// @param p_entity [AI] Building entity
	/// @return [AI] TRUE if sound switched, FALSE otherwise.
	MxBool SwitchSound(LegoEntity* p_entity);

	/// @brief [AI] Cycles the current move/animation state for a building (if moves available).
	/// @param p_entity [AI] Building entity
	/// @return [AI] TRUE if move switched, FALSE otherwise.
	MxBool SwitchMove(LegoEntity* p_entity);

	/// @brief [AI] Cycles the current mood state for a building (if moods available, mood in 0..3).
	/// @param p_entity [AI] Building entity
	/// @return [AI] TRUE if mood switched, FALSE otherwise.
	MxBool SwitchMood(LegoEntity* p_entity);

	/// @brief [AI] Returns the animation id for a building entity, factoring in base animation id and move offset.
	/// @param p_entity [AI] Building entity
	/// @return [AI] Animation id, or 0 if building doesn't support moves.
	MxU32 GetAnimationId(LegoEntity* p_entity);

	/// @brief [AI] Returns the sound id for a building entity, using either mood or active sound state. If p_state is TRUE, returns the mood-related sound id, else uses current sound slot.
	/// @param p_entity [AI] Building entity
	/// @param p_state [AI] TRUE for mood, FALSE for main sound
	/// @return [AI] Sound id or 0 if not available.
	MxU32 GetSoundId(LegoEntity* p_entity, MxBool p_state);

	/// @brief [AI] Attempts to "progress" demolition/animation of a building entity by calling FUN_10030030 on its array index.
	/// @param p_entity [AI] Building entity
	MxBool FUN_10030000(LegoEntity* p_entity);

	/// @brief [AI] Internal: progresses the demolition/animation state/counter of the indexed building, moves ROI if appropriate, otherwise hides the entity when done.
	/// @param p_index [AI] Index in the building info array
	MxBool FUN_10030030(MxS32 p_index);

	/// @brief [AI] Forwards to FUN_10030030 with lookup by pointer; used for pointer-based demolition/motion triggers.
	/// @param p_data [AI] Pointer to LegoBuildingInfo
	MxBool FUN_10030110(LegoBuildingInfo* p_data);

	/// @brief [AI] Schedules an animation bounce/effect for a given building entity (updates AnimEntry tracking and triggers Tickle registration).
	/// @param p_entity [AI] The entity to animate
	/// @param p_length [AI] Duration of the animation (in ms)
	/// @param p_haveSound [AI] Whether sound should play at peak event [AI]
	/// @param p_unk0x28 [AI] Whether to immediately set demolition state to zero at finish.
	void ScheduleAnimation(LegoEntity* p_entity, MxLong p_length, MxBool p_haveSound, MxBool p_unk0x28);

	/// @brief [AI] Resets all buildings' construction/demolition status to "unbuilt" (-1), updates heights/visibilities, and resets entity transform.
	void FUN_10030590();

	/// @brief [AI] Adjusts (recalculates) a building's world Y position based on its current demo/build counter, which offsets Y lower as more damage occurs.
	/// @param p_index [AI] The index into g_buildingInfo
	void AdjustHeight(MxS32 p_index);

	/// @brief [AI] Performs a boundary existence/consistency check for each building, resolving path boundaries and snapping Y if necessary.
	/// @return [AI] SUCCESS or FAILURE (invalid boundary)
	MxResult FUN_10030630();

	/// @brief [AI] Returns the full set of LegoBuildingInfo entries, checks/initializes boundary data if needed.
	/// @param p_length [AI] Set to the count of entries returned.
	/// @return [AI] Pointer to building info array (of size p_length)
	LegoBuildingInfo* GetInfoArray(MxS32& p_length);

	/// @brief [AI] Adjusts the construction/demolition counter for a building entity, incrementing or decrementing by a fixed adjust amount.
	/// @param p_entity [AI] Building entity
	/// @param p_adjust [AI] Value to increment (positive) or decrement (negative)
	void FUN_100307b0(LegoEntity* p_entity, MxS32 p_adjust);

	/// @brief [AI] Copies the current m_unk0x11 demo/counter into m_initialUnk0x11 for all buildings (for persistent saving).
	void FUN_10030800();

	/// @brief [AI] Gets the current static filename for custom "customize" animations.
	/// @return [AI] C-string filename, owned by class, or NULL if none set.
	static const char* GetCustomizeAnimFile() { return g_customizeAnimFile; }

	// SYNTHETIC: LEGO1 0x1002f940
	// LegoBuildingManager::`scalar deleting destructor'

private:
	/// @brief [AI] Static filename for user-customized "customize animation" SMK/FLC cutscene.
	static char* g_customizeAnimFile;

	/// @brief [AI] Maximum move state count per-building (indexed by g_buildingInfo slot).
	static MxS32 g_maxMove[16];

	/// @brief [AI] Maximum number of available sound slots for buildings.
	static MxU32 g_maxSound;

	MxU8 m_nextVariant;      ///< [AI] Index of selected building variant for demo house/cycling (for variant switching, 0...N) [AI]
	MxBool m_unk0x09;        ///< [AI] TRUE if boundary data is validated and ready. [AI]
	AnimEntry* m_entries[5]; ///< [AI] Entries for scheduled animation/demolition effects (max 5 concurrent). [AI]
	MxS8 m_numEntries;       ///< [AI] Number of valid entries in m_entries. [AI]
	LegoCacheSound* m_sound; ///< [AI] The sound resource ("bcrash") for active animations.
	MxBool m_unk0x28;        ///< [AI] Used during animation scheduling for immediate hiding at finish.
	LegoWorld* m_world;      ///< [AI] The world context where animation is currently being performed.
};

#endif // LEGOBUILDINGMANAGER_H
