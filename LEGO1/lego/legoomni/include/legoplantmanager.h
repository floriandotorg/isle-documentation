#ifndef LEGOPLANTMANAGER_H
#define LEGOPLANTMANAGER_H

#include "decomp.h"
#include "legomain.h"
#include "mxcore.h"

class LegoEntity;
class LegoPathBoundary;
struct LegoPlantInfo;
class LegoROI;
class LegoStorage;
class LegoWorld;

// VTABLE: LEGO1 0x100d6758
// SIZE 0x2c
/**
 * @brief [AI] Manages the lifecycle, state, and properties for all plant objects (flowers, trees, bushes, palms) on LEGO Island.
 * 
 * This class handles creation, removal, animation scheduling, color/variant/mood/sound switching, serialization,
 * and in-world management of plants/entities considered as static environmental decorations, but with some
 * interactability and state.
 *
 * It also provides support functions for customizing and storing their state, and integrates with tickle management 
 * for scheduled behavior.
 *
 * @details [AI] The manager is responsible for all plants present in the current world, ties plant information 
 * with entity/ROI, schedules animations (growth, custom actions), and facilitates saving/loading plant state.
 */
class LegoPlantManager : public MxCore {
public:
	/**
	 * @brief [AI] Structure for scheduling plant ROI/entity animations (i.e. "wobble" when interacted or animated growth).
	 * 
	 * Holds pointer to entity, corresponding ROI, and a target time value for when the animation should end.
	 * 
	 * @details [AI] Used for batching and sequencing per-plant animation via the tickle system; when the animation
	 * is due, performs the needed transformation/cleanup.
	 */
	struct AnimEntry {
		LegoEntity* m_entity; ///< [AI] Pointer to the plant entity being animated [AI]
		LegoROI* m_roi;       ///< [AI] ROI of the animated plant entity [AI]
		MxLong m_time;        ///< [AI] When the animation should end (absolute time) [AI]
	};

	/**
	 * @brief [AI] Constructs the plant manager and initializes its bookkeeping to match the plant info array.
	 */
	LegoPlantManager();

	/**
	 * @brief [AI] Destructor. Cleans up any allocated entries and resets static animation file string.
	 */
	~LegoPlantManager() override; // vtable+0x00

	/**
	 * @brief [AI] Tickle handler for processing scheduled plant animation entries.
	 * 
	 * Periodically animates plants by updating their transformation matrices and visibility,
	 * synchronizing with the tickle system.
	 * 
	 * @details [AI] If all current entries complete, unregisters from tickle.
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief [AI] Returns the class name "LegoPlantManager". Used for RTTI and debugging.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// While this class exists in BETA10, it didn't have a ClassName().
		// I suppose it did not inherit from MxCore back then and likely did not have a VTABLE.
		// STRING: LEGO1 0x100f318c
		return "LegoPlantManager";
	}

	/**
	 * @brief [AI] Zeroes out state, resets world ID, and copies default plant info to runtime plant info array.
	 *
	 * @details [AI] Also called from constructor to ensure fresh state across world loads/restarts.
	 */
	void Init();

	/**
	 * @brief [AI] Loads all plant objects/entities for the requested world, instantiates requisite ROIs and entities.
	 * 
	 * @param p_worldId Index of the current world. [AI]
	 * @details [AI] For each entry in the plant info array, creates an entity and links it for in-world presence if
	 * the plant exists in that world. Sets up pointers and registers initial state.
	 */
	void LoadWorldInfo(LegoOmni::World p_worldId);

	/**
	 * @brief [AI] Completely resets (removes) all plant objects for the supplied world.
	 * 
	 * @param p_worldId World which is being reset. [AI]
	 * 
	 * @details [AI] Destroys any entities/ROIs for plants in the specified world and reverts world ID.
	 */
	void Reset(LegoOmni::World p_worldId);

	/**
	 * @brief [AI] Serializes persistent plant state (color, variant, mood, animation, etc) to storage for save games or transitions.
	 * 
	 * @param p_storage Where to write the serialized plant property data. [AI]
	 * @details [AI] Loops over all plants and saves only the relevant dynamic state, not entity or ROI objects.
	 */
	MxResult Write(LegoStorage* p_storage);

	/**
	 * @brief [AI] Rehydrates plant state from storage, restoring color/variant/mood/move properties.
	 * 
	 * @param p_storage Source of the plant save data. [AI]
	 * @details [AI] After reading, also recalculates each plant position based on variant/growth state.
	 */
	MxResult Read(LegoStorage* p_storage);

	/**
	 * @brief [AI] Returns the total number of plant records referenced by this manager.
	 */
	MxS32 GetNumPlants();

	/**
	 * @brief [AI] Cycles the color attribute for the plant and updates its LOD/appearance.
	 * 
	 * @param p_entity Target plant entity. [AI]
	 * @details [AI] Updates color value modulo the possible color variants (white, black, yellow, red, green),
	 * reconstructs LOD and visuals accordingly.
	 */
	MxBool SwitchColor(LegoEntity* p_entity);

	/**
	 * @brief [AI] Cycles the variant/type for a plant (flower, tree, bush, palm) and updates appearance.
	 * 
	 * @param p_entity Target plant entity. [AI]
	 * @details [AI] Only allow variant switch if plant 'growth' state allows, reassigns LOD after.
	 */
	MxBool SwitchVariant(LegoEntity* p_entity);

	/**
	 * @brief [AI] Cycles the sound effect variant for a plant. [AI]
	 * @param p_entity Target plant entity. [AI]
	 * @details [AI] Increments sound index for this plant, wraps around if exceeding max.
	 */
	MxBool SwitchSound(LegoEntity* p_entity);

	/**
	 * @brief [AI] Cycles the movement/animation type for a plant. [AI]
	 * @param p_entity Target plant entity. [AI]
	 * @details [AI] Increments the move index (i.e. animation), wraps at maximum allowed for current variant.
	 */
	MxBool SwitchMove(LegoEntity* p_entity);

	/**
	 * @brief [AI] Cycles the plant's "mood" state property (e.g., for appearance/hidden states) [AI]
	 * @param p_entity Target plant entity. [AI]
	 * @details [AI] Rolls through mood values 0..3.
	 */
	MxBool SwitchMood(LegoEntity* p_entity);

	/**
	 * @brief [AI] Returns the current animation ID for the given plant, based on its variant and move type. [AI]
	 * @param p_entity Target plant entity. [AI]
	 */
	MxU32 GetAnimationId(LegoEntity* p_entity);

	/**
	 * @brief [AI] Returns the sound ID for a plant, used for localized SFX depending on mood/state. [AI]
	 * @param p_entity Target plant entity. [AI]
	 * @param p_state Selects sound type (mood vs sound property). [AI]
	 * @details [AI] Picks sound based on whether it is state-dependent or not.
	 */
	MxU32 GetSoundId(LegoEntity* p_entity, MxBool p_state);

	/**
	 * @brief [AI] Returns pointer to plant info array and populates its size. Triggers boundary check/correction if needed.
	 * @param p_length Set to array length on output. [AI]
	 * @details [AI] Ensures boundary/plane alignment check is performed before returning the array. [AI]
	 */
	LegoPlantInfo* GetInfoArray(MxS32& p_length);

	/**
	 * @brief [AI] Instantiates an entity and ROI for the plant at given index in world (if appropriate).
	 * @param p_index The index into the plant info array. [AI]
	 * @param p_world Target world pointer for this plant's entity. [AI]
	 * @param p_worldId World enum/ID for filtering plants that exist in this world. [AI]
	 * @details [AI] Creates only if plant meets world and activation criteria and hasn't already been made.
	 */
	LegoEntity* CreatePlant(MxS32 p_index, LegoWorld* p_world, LegoOmni::World p_worldId);

	/**
	 * @brief [AI] Triggers a growth decrement or similar on a plant entity, and updates accordingly if possible.
	 * @param p_entity Plant entity to update. [AI]
	 * @return If the underlying property could be decremented and plant was updated. [AI]
	 * @details [AI] Underlying plant property is likely its 'growth' counter or health, using index lookup.
	 */
	MxBool FUN_10026c50(LegoEntity* p_entity);

	/**
	 * @brief [AI] Schedules an animation for the given plant, adding an entry to the internal tickle array.
	 * @param p_entity Plant to animate. [AI]
	 * @param p_length Length (ms) that the animation should persist. [AI]
	 * @details [AI] Will register itself to tickle manager if first animation entry.
	 */
	void ScheduleAnimation(LegoEntity* p_entity, MxLong p_length);

	/**
	 * @brief [AI] Repairs/updates all plant boundary references and vertical position to match world boundaries/planes.
	 * @details [AI] Used to synchronize per-plant Y position against world boundaries (for collision/placement correction).
	 */
	MxResult FUN_10026410();

	/**
	 * @brief [AI] Resets all growth/activity/animation state for all plants in the manager.
	 * @details [AI] Used to return plants to their initial/hidden or unevolved states, e.g. on world load.
	 */
	void FUN_10027120();

	/**
	 * @brief [AI] Propagates all plants' current growth/activity state to their restore points.
	 * @details [AI] Used for state rollback or prepping snapshot for future restoration.
	 */
	void FUN_10027200();

	/**
	 * @brief [AI] Sets the global file path or name to use for plant customization animations.
	 * 
	 * @param p_value String containing file name/path for custom animation. Can be null to clear. [AI]
	 * @details [AI] String is copied and managed as a global static resource.
	 */
	static void SetCustomizeAnimFile(const char* p_value);

	/**
	 * @brief [AI] Gets the current file name/path for plant customization animation file. [AI]
	 * @return String pointer; NULL if unset. [AI]
	 */
	static const char* GetCustomizeAnimFile() { return g_customizeAnimFile; }

	// SYNTHETIC: LEGO1 0x100262a0
	// LegoPlantManager::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Removes and deletes a plant entity from world, cleaning up its ROI. [AI]
	 * 
	 * @param p_index Index of plant in manager table. [AI]
	 * @param p_worldId Target world to prune. [AI]
	 * @details [AI] Called by Reset to clean out all plants for a world.
	 */
	void RemovePlant(MxS32 p_index, LegoOmni::World p_worldId);

	/**
	 * @brief [AI] Updates a plant's vertical position based on the difference between current grow state and initial state.
	 * @param p_index Plant index to adjust. [AI]
	 * @details [AI] Adjusts the y-coordinate depending on 'growth' or current state.
	 */
	void FUN_10026860(MxS32 p_index);

	/**
	 * @brief [AI] Finds the info array slot struct for a given plant entity pointer.
	 * @param p_entity Plant entity pointer to search for. [AI]
	 * @return Pointer to matching LegoPlantInfo slot if found, or NULL. [AI]
	 * @details [AI] Used internally for all entity-to-info mapping. O(n) on all plants.
	 */
	LegoPlantInfo* GetInfo(LegoEntity* p_entity);

	/**
	 * @brief [AI] Decrements growth/activity counter on plant at index, hiding or adjusting as appropriate.
	 * @param p_index Plant info index. [AI]
	 * @details [AI] Internal helper for FUN_10026c50(), processes 'shrink' or de-animate logic.
	 */
	MxBool FUN_10026c80(MxS32 p_index);

	/**
	 * @brief [AI] Adjusts the growth/activity/growth counter on a specific plant based on the adjustment amount.
	 * @param p_entity Plant entity (target). [AI]
	 * @param p_adjust Signed amount to adjust the state by. [AI]
	 * @details [AI] Will update counter, possibly hiding the plant if growth exhausted.
	 */
	void FUN_100271b0(LegoEntity* p_entity, MxS32 p_adjust);

	static char* g_customizeAnimFile; ///< [AI] Global path to custom animation file for plant customization (user or script set). [AI]
	static MxS32 g_maxMove[4];        ///< [AI] Maximum allowed movement animation count per plant variant [AI]
	static MxU32 g_maxSound;          ///< [AI] Maximum allowed sound ID per plant [AI]

	LegoOmni::World m_worldId;   ///< [AI] Current world being managed (mask used for CreatePlant/RemovePlant) [AI]
	undefined m_unk0x0c;         ///< [AI] [AI_SUGGESTED_NAME: m_infoAlignmentValid] Used as flag to indicate if info plane/boundary fixup is completed. [AI]
	AnimEntry* m_entries[5];     ///< [AI] Pointers to all currently scheduled plant AnimEntries being animated [AI]
	MxS8 m_numEntries;           ///< [AI] How many animation entries in-use in m_entries. [AI]
	LegoWorld* m_world;          ///< [AI] Last world pointer used for animation check (animation aborts on world change) [AI]
};

#endif // LEGOPLANTMANAGER_H
