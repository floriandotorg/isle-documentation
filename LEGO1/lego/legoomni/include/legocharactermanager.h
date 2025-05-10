#ifndef LEGOCHARACTERMANAGER_H
#define LEGOCHARACTERMANAGER_H

#include "decomp.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"
#include "mxvariable.h"
#include "roi/legoroi.h"

class LegoActor;
class LegoExtraActor;
class LegoStorage;
class LegoROI;

#pragma warning(disable : 4237)

/**
 * @struct LegoCharacterComparator
 * @brief [AI] Comparator for character names, performing case-insensitive comparison using strcmpi.
 *
 * Used as the sorting predicate in LegoCharacterMap to order character name keys.
 * [AI]
 */
struct LegoCharacterComparator {
	/**
	 * @brief [AI] Function call operator to compare two character name strings case-insensitively.
	 * @param p_a First string to compare. [AI]
	 * @param p_b Second string to compare. [AI]
	 * @return true if p_a compares less than p_b ignoring case. [AI]
	 */
	MxBool operator()(const char* const& p_a, const char* const& p_b) const { return strcmpi(p_a, p_b) < 0; }
};

/**
 * @struct LegoCharacter
 * @brief [AI] Holds a LegoROI pointer and reference count for a character instance managed by LegoCharacterManager.
 *
 * Used to manage lifetime and reference tracking for character ROI objects, with automatic deletion of the ROI
 * when the reference count reaches zero.
 * [AI]
 *
 * SIZE: 0x08 bytes.
 */
struct LegoCharacter {
	/**
	 * @brief [AI] Constructs a LegoCharacter with an initial reference count of 1 and assigns the ROI pointer.
	 * @param p_roi The LegoROI representing this character. [AI]
	 */
	LegoCharacter(LegoROI* p_roi)
	{
		m_roi = p_roi;
		m_refCount = 1;
	}
	/**
	 * @brief [AI] Destructor that deletes the associated ROI. [AI]
	 */
	~LegoCharacter() { delete m_roi; }

	/**
	 * @brief [AI] Increments the internal reference count for this character. [AI]
	 */
	void AddRef() { m_refCount++; }

	/**
	 * @brief [AI] Decrements the internal reference count. If the count reaches zero, the character should be destroyed.
	 * @return The new reference count. [AI]
	 */
	MxU32 RemoveRef()
	{
		if (m_refCount != 0) {
			m_refCount--;
		}
		return m_refCount;
	}

	LegoROI* m_roi;   ///< [AI] Pointer to the character's ROI object.
	MxU32 m_refCount; ///< [AI] Reference count tracking how many owners the character ROI has.
};

/**
 * @typedef LegoCharacterMap
 * @brief [AI] Map from character name strings to LegoCharacter pointers.
 *
 * Key: char* (ownership managed by the map/manager, dynamically allocated).
 * Value: LegoCharacter* (manages reference counts and ROI lifetime).
 * Comparator: LegoCharacterComparator (case-insensitive string comparison).
 * [AI]
 */
typedef map<char*, LegoCharacter*, LegoCharacterComparator> LegoCharacterMap;

/**
 * @class CustomizeAnimFileVariable
 * @brief [AI] MxVariable subclass used to represent and propagate changes to the character customization animation file.
 *
 * When the value is set, triggers updates to customization animation files for Characters, Plants, and Buildings.
 * Used by the variable table for runtime customization support.
 * [AI]
 *
 * VTABLE: LEGO1 0x100da878
 * SIZE: 0x24 bytes
 */
class CustomizeAnimFileVariable : public MxVariable {
public:
	/**
	 * @brief [AI] Constructs the variable and sets its key (converted to uppercase).
	 * @param p_key The name of the variable. [AI]
	 */
	CustomizeAnimFileVariable(const char* p_key);

	/**
	 * @brief [AI] Sets the variable value and propagates customization file changes to relevant managers.
	 * @param p_value The new value. [AI]
	 * @details If the key is "CUSTOMIZE_ANIM_FILE", updates customization animation files in CharacterManager, PlantManager, and BuildingManager. [AI]
	 */
	void SetValue(const char* p_value) override; // vtable+0x04
};

/**
 * @class LegoCharacterManager
 * @brief [AI] Manages reference-counted characters and provides character creation, switching, and property update functionality.
 *
 * Handles creation and deletion of LegoROI-based character objects, manages reference counts to avoid redundant copies,
 * supports property switching for sound, color, variant, mood, animation, reading/writing state to storage,
 * and provides runtime customization features (e.g., runtime selection of animation files).
 *
 * Used for runtime management of all interactive/actor-type Lego characters and "automatic" ROI objects tied to characters (by name).
 * [AI]
 *
 * SIZE: 0x08 bytes
 */
class LegoCharacterManager {
public:
	/**
	 * @brief [AI] Constructs the character manager, initializing tables and the customizable animation variable.
	 */
	LegoCharacterManager();

	/**
	 * @brief [AI] Destroys the manager, cleaning up all managed characters and animation customization state.
	 */
	~LegoCharacterManager();

	/**
	 * @brief [AI] Writes the persistent character info data to a storage object.
	 * @param p_storage Storage object to serialize to. [AI]
	 * @return Operation result (SUCCESS/FAILURE). [AI]
	 * @details Serializes out the dynamic properties of LegoActorInfo for each actor, such as sound, move, mood, etc. [AI]
	 */
	MxResult Write(LegoStorage* p_storage);

	/**
	 * @brief [AI] Reads character info data from a storage object.
	 * @param p_storage Storage object to read from. [AI]
	 * @return Operation result (SUCCESS/FAILURE). [AI]
	 * @details Reads the dynamic properties back into LegoActorInfo structures. [AI]
	 */
	MxResult Read(LegoStorage* p_storage);

	/**
	 * @brief [AI] Returns the actor name for the given actor index (lookup in global g_actorInfo table).
	 * @param p_index Index into the actor info array. [AI]
	 * @return Name string of the actor, or NULL if out of range. [AI]
	 */
	const char* GetActorName(MxS32 p_index);

	/**
	 * @brief [AI] Returns the number of actors registered in global g_actorInfo. [AI]
	 */
	MxU32 GetNumActors();

	/**
	 * @brief [AI] Returns a LegoROI for the given character name, creating and registering the actor if necessary.
	 * @param p_name Name of the actor. [AI]
	 * @param p_createEntity Whether to create and attach an entity if one doesn't exist. [AI]
	 * @return Pointer to the character's LegoROI, or NULL on failure. [AI]
	 */
	LegoROI* GetActorROI(const char* p_name, MxBool p_createEntity);

	/**
	 * @brief [AI] Initializes all actor info structures based on their templates/defaults.
	 * [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Sets the value of the customization animation file variable, propagating to all relevant subsystems.
	 * @param p_value The new animation file to use. [AI]
	 * @details Also updates PlantManager and BuildingManager. [AI]
	 */
	static void SetCustomizeAnimFile(const char* p_value);

	/**
	 * @brief [AI] Checks if the given name matches an actor in the global actor table (case-insensitive).
	 * @param p_name Name string to check. [AI]
	 * @return TRUE if the actor exists, FALSE otherwise. [AI]
	 */
	static MxBool IsActor(const char* p_name);

	/**
	 * @brief [AI] Releases all actors associated with this manager, unregistering/releasing references until destroyed.
	 */
	void ReleaseAllActors();

	/**
	 * @brief [AI] Returns whether a character with the given name exists in the manager.
	 * @param p_name Name of the character. [AI]
	 * @return TRUE if exists, FALSE otherwise. [AI]
	 */
	MxBool Exists(const char* p_name);

	/**
	 * @brief [AI] Returns the reference count for a given LegoROI* tracked by the manager.
	 * @param p_roi ROI to query. [AI]
	 * @return Reference count for the ROI, or 0 if not managed. [AI]
	 */
	MxU32 GetRefCount(LegoROI* p_roi);

	/**
	 * @brief [AI] Releases a character/ROI by name, decrementing its reference count and deleting if zero.
	 * @param p_name Name of the character to release. [AI]
	 */
	void ReleaseActor(const char* p_name);

	/**
	 * @brief [AI] Releases a character/ROI object, handling reference count and eventual deletion.
	 * @param p_roi ROI to release. [AI]
	 */
	void ReleaseActor(LegoROI* p_roi);

	/**
	 * @brief [AI] Releases an "auto" ROI, used for dynamically created ROI objects by this manager.
	 * @param p_roi ROI to release. [AI]
	 * @details This is specifically for ROIs created via CreateAutoROI.
	 */
	void ReleaseAutoROI(LegoROI* p_roi);

	/**
	 * @brief [AI] Replaces the head LOD of a character ROI with a new LOD list built using the provided texture.
	 * @param p_roi ROI to update. [AI]
	 * @param p_texture New texture to use for the head LOD. [AI]
	 * @return TRUE if operation succeeded, FALSE otherwise. [AI]
	 */
	MxBool FUN_100849a0(LegoROI* p_roi, LegoTextureInfo* p_texture);

	/**
	 * @brief [AI] Returns an extra actor associated with a given character name, or NULL if not found.
	 * @param p_name Character name [AI]
	 * @return Extra actor pointer. [AI]
	 */
	LegoExtraActor* GetExtraActor(const char* p_name);

	/**
	 * @brief [AI] Returns the actor info struct for the character of the given name, or NULL if not found.
	 * @param p_name Character name [AI]
	 * @return Pointer to actor info struct. [AI]
	 */
	LegoActorInfo* GetActorInfo(const char* p_name);

	/**
	 * @brief [AI] Returns actor info struct for the character associated with a given ROI pointer.
	 * @param p_roi ROI to match [AI]
	 * @return Pointer to actor info struct, or NULL [AI]
	 */
	LegoActorInfo* GetActorInfo(LegoROI* p_roi);

	/**
	 * @brief [AI] Changes the color of a part of a character's ROI, updating its part info index and updating ROI color.
	 * @param p_roi Character ROI [AI]
	 * @param p_targetROI ROI for the part to change (may be determined based on target name). [AI]
	 * @return TRUE if color was switched, FALSE if not applicable. [AI]
	 */
	MxBool SwitchColor(LegoROI* p_roi, LegoROI* p_targetROI);

	/**
	 * @brief [AI] Cycles through part variants (e.g. hat) for the character's ROI, updating the model as appropriate.
	 * @param p_roi Character ROI [AI]
	 * @return TRUE if variant switched. [AI]
	 */
	MxBool SwitchVariant(LegoROI* p_roi);

	/**
	 * @brief [AI] Cycles the sound type for the actor, updating the per-actor info. [AI]
	 * @param p_roi Character ROI [AI]
	 * @return TRUE if sound switched.
	 */
	MxBool SwitchSound(LegoROI* p_roi);

	/**
	 * @brief [AI] Cycles the move type for the actor, updating the per-actor info. [AI]
	 * @param p_roi Character ROI [AI]
	 * @return TRUE if move switched.
	 */
	MxBool SwitchMove(LegoROI* p_roi);

	/**
	 * @brief [AI] Cycles the mood type for the actor, updating the per-actor info. [AI]
	 * @param p_roi Character ROI [AI]
	 * @return TRUE if mood switched.
	 */
	MxBool SwitchMood(LegoROI* p_roi);

	/**
	 * @brief [AI] Returns an animation ID corresponding to the ROI's move index. [AI]
	 * @param p_roi Character ROI [AI]
	 * @return Animation ID value, or 0 if not found.
	 */
	MxU32 GetAnimationId(LegoROI* p_roi);

	/**
	 * @brief [AI] Returns the sound ID for the ROI's current sound/mood selection. [AI]
	 * @param p_roi Character ROI [AI]
	 * @param p_und If true, returns alternate mood-based sound id. [AI]
	 * @return Sound ID, or 0 on failure.
	 */
	MxU32 GetSoundId(LegoROI* p_roi, MxBool p_und);

	/**
	 * @brief [AI] Returns the current mood value (0-3) for the actor associated with the ROI. [AI]
	 * @param p_roi Character ROI [AI]
	 * @return Mood value.
	 */
	MxU8 GetMood(LegoROI* p_roi);

	/**
	 * @brief [AI] Creates an "auto" ROI object with the given name, LOD name, and optional entity creation. [AI]
	 * @param p_name Name for the new ROI (or NULL for auto-generated). [AI]
	 * @param p_lodName LOD name to use to build ROI/model. [AI]
	 * @param p_createEntity If TRUE, also creates and registers a new LegoEntity. [AI]
	 * @return Created ROI pointer, or NULL if failed.
	 */
	LegoROI* CreateAutoROI(const char* p_name, const char* p_lodName, MxBool p_createEntity);

	/**
	 * @brief [AI] Initializes auto-ROI with bounding volume and transformation.
	 * @param p_roi ROI to initialize. [AI]
	 * @return SUCCESS/FAILURE.
	 * @details Sets up bounding box/sphere and invokes VTable0x14 for derived setup. [AI]
	 */
	MxResult FUN_10085870(LegoROI* p_roi);

	/**
	 * @brief [AI] Helper function that delegates to CreateAutoROI.
	 * @param p_name Name for the new ROI. [AI]
	 * @param p_lodName LOD name. [AI]
	 * @param p_createEntity Entity creation flag. [AI]
	 * @return ROI pointer (see CreateAutoROI).
	 */
	LegoROI* FUN_10085a80(const char* p_name, const char* p_lodName, MxBool p_createEntity);

	/**
	 * @brief [AI] Gets the value of the customize animation file variable. [AI]
	 * @return Current customize animation file string (global pointer, managed elsewhere). [AI]
	 */
	static const char* GetCustomizeAnimFile() { return g_customizeAnimFile; }

private:
	/**
	 * @brief [AI] Creates a LegoROI for a given actor from templates, sets up lods, bounding volumes, and parts.
	 * @param p_key Name of the actor (character) to create. [AI]
	 * @return Created ROI or NULL on failure.
	 */
	LegoROI* CreateActorROI(const char* p_key);

	/**
	 * @brief [AI] Removes a given ROI from the 3D scene and all management tables. [AI]
	 * @param p_roi ROI to remove. [AI]
	 */
	void RemoveROI(LegoROI* p_roi);

	/**
	 * @brief [AI] Finds a child ROI by name under the given parent ROI. [AI]
	 * @param p_roi Parent ROI to search within [AI]
	 * @param p_name Name to match (case-insensitive). [AI]
	 * @return Pointer to child ROI if found, otherwise NULL.
	 */
	LegoROI* FindChildROI(LegoROI* p_roi, const char* p_name);

	static char* g_customizeAnimFile; ///< [AI] Global (static) value for customization animation file path.
	static MxU32 g_maxMove;           ///< [AI] Maximum move index; bounds for SwitchMove, etc.
	static MxU32 g_maxSound;          ///< [AI] Maximum sound index; bounds for SwitchSound, etc.

	LegoCharacterMap* m_characters;                 ///< [AI] Map from character name (string) to reference-counted ROI wrappers.
	CustomizeAnimFileVariable* m_customizeAnimFile; ///< [AI] Variable instance for customize animation file integration with variable table.
};

// clang-format off
// TEMPLATE: LEGO1 0x1001a690
// list<ROI *,allocator<ROI *> >::_Buynode

// TEMPLATE: LEGO1 0x10035790
// ?_Construct@@YAXPAPAVROI@@ABQAV1@@Z

// TEMPLATE: LEGO1 0x10082b90
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::~_Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >

// TEMPLATE: LEGO1 0x10082c60
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::iterator::_Inc

// TEMPLATE: LEGO1 0x10082ca0
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::erase

// TEMPLATE: LEGO1 0x100830f0
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Erase

// TEMPLATE: LEGO1 0x10083130
// map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::~map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >

// TEMPLATE: LEGO1 0x10083840
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::iterator::_Dec

// TEMPLATE: LEGO1 0x10083890
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Insert

// TEMPLATE: LEGO1 0x10085500
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::insert

// TEMPLATE: LEGO1 0x10085790
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Buynode

// TEMPLATE: LEGO1 0x100857b0
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Lrotate

// TEMPLATE: LEGO1 0x10085810
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Rrotate

// GLOBAL: LEGO1 0x100fc508
// _Tree<char *,pair<char * const,LegoCharacter *>,map<char *,LegoCharacter *,LegoCharacterComparator,allocator<LegoCharacter *> >::_Kfn,LegoCharacterComparator,allocator<LegoCharacter *> >::_Nil
// clang-format on

#endif // LEGOCHARACTERMANAGER_H
