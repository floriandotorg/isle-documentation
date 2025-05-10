#ifndef LEGOMAIN_H
#define LEGOMAIN_H

#include "compat.h"
#include "mxdsaction.h"
#include "mxomni.h"

/**
 * @class LegoOmni
 * @brief [AI] Central hub singleton for the LEGO Island game engine, managing all core game systems, state, world switching, and providing high-level access to all major engine subsystems. Handles initialization, teardown, world registry, notification dispatching, and singleton instance management.
 *
 * @details [AI] LegoOmni extends MxOmni to provide high-level game coordination, resource and manager ownership, dynamic world and entity management, script/action handling, background audio, global state, and event notification. It encapsulates systems for animation, input, world/ROI lookup, tickling, building/plants, and more. The class also provides interface entry points for interacting with video, audio, presenter logic, and game state—making it effectively the "heart" of the LEGO Island runtime architecture.
 */
class Isle;
class LegoAnimationManager;
class LegoBuildingManager;
class LegoCharacterManager;
class LegoEntity;
class LegoGameState;
class LegoInputManager;
class LegoNavController;
class LegoPathActor;
class LegoPathBoundary;
class LegoPlantManager;
class LegoROI;
class LegoSoundManager;
class LegoTextureContainer;
class LegoVideoManager;
class LegoWorld;
class LegoWorldList;
class MxAtomId;
class MxBackgroundAudioManager;
class MxTransitionManager;
class ViewLODListManager;

/**
 * @class LegoOmni
 * @brief [AI] Engine singleton managing LEGO Island's subsystems and game state. [AI]
 */
class LegoOmni : public MxOmni {
public:
	/**
	 * @enum
	 * @brief [AI] Internal flags for enabling/disabling input, 3D rendering, or screen clearing for coordinated game state changes. [AI]
	 */
	enum {
		c_disableInput = 0x01,   ///< [AI] When set, disables input processing. [AI]
		c_disable3d = 0x02,      ///< [AI] When set, disables 3D rendering. [AI]
		c_clearScreen = 0x04     ///< [AI] When set, clears the display surface. [AI]
	};

	/**
	 * @enum World
	 * @brief [AI] Identifiers for all unique, script-driven world environments in LEGO Island. Used for dynamic lookup, registry, and scheduling. [AI]
	 * @details [AI] Each enum value corresponds to a logical world space, typically associated with a key, script, and AtomId. e_numWorlds is the total. [AI]
	 */
	enum World {
		e_undefined = -1,   ///< [AI] No world specified. [AI]
		e_act1 = 0,         ///< [AI] Act 1 main world. [AI]
		e_imain,            ///< [AI] Information main building. [AI]
		e_icube,            ///< [AI] Information cube building. [AI]
		e_ireg,             ///< [AI] Information registration/building. [AI]
		e_ielev,            ///< [AI] Information elevator. [AI]
		e_iisle,            ///< [AI] Information Isle room. [AI]
		e_hosp,             ///< [AI] Hospital. [AI]
		e_police,           ///< [AI] Police station. [AI]
		e_gmain,            ///< [AI] Garage. [AI]
		e_bldh,             ///< [AI] Helicopter building. [AI]
		e_bldd,             ///< [AI] Dune car building. [AI]
		e_bldj,             ///< [AI] Jet ski building. [AI]
		e_bldr,             ///< [AI] Race car building. [AI]
		e_racc,             ///< [AI] Car race area/world. [AI]
		e_racj,             ///< [AI] Jet race area/world. [AI]
		e_act2,             ///< [AI] Act 2. [AI]
		e_act3,             ///< [AI] Act 3. [AI]
		e_test,             ///< [AI] Test world. [AI]
		e_numWorlds = e_test + 2 ///< [AI] Number of worlds (includes undefined, test, or unused). [AI]
	};

	/**
	 * @struct WorldContainer
	 * @brief [AI] Associates a world enum, key, and AtomId for dynamic world lookup, Atom-based registry, and key-string identification. [AI]
	 * @details [AI] Used internally in LegoOmni as a world table for fast world script and Atom lookup by enum, string, or AtomId. [AI]
	 */
	struct WorldContainer {
		/**
		 * @brief [AI] Default constructor. Sets world to undefined and AtomId to NULL.
		 */
		WorldContainer()
		{
			m_id = e_undefined;
			m_atomId = NULL;
		}

		/**
		 * @brief [AI] Construct a WorldContainer from enum id, string key, and AtomId pointer.
		 * @param p_id [AI] World enum identifier for this container.
		 * @param p_key [AI] String key associated with the world (e.g. "ACT1").
		 * @param p_atomId [AI] AtomId pointer for script identification.
		 */
		WorldContainer(World p_id, const char* p_key, MxAtomId* p_atomId)
		{
			m_id = p_id;

			if (p_key) {
				strcpy(m_key, p_key);
			}

			m_atomId = p_atomId;
		}

		/**
		 * @brief [AI] Copy assignment operator.
		 * @param p_container [AI] Container to copy from.
		 * @return [AI] Reference to self.
		 */
		WorldContainer& operator=(const WorldContainer& p_container)
		{
			m_id = p_container.m_id;
			strcpy(m_key, p_container.m_key);
			m_atomId = p_container.m_atomId;
			return *this;
		}

		/**
		 * @brief [AI] Returns world identifier.
		 * @return [AI] World enum of this container.
		 */
		World GetId() { return m_id; }

		/**
		 * @brief [AI] Returns world string key.
		 * @return [AI] Key string used for registry and lookup.
		 */
		const char* GetKey() { return m_key; }

		World m_id;         ///< [AI] World enum identifier.
		char m_key[20];     ///< [AI] String key for this world (used for script/world lookup). 
		MxAtomId* m_atomId; ///< [AI] AtomId pointer for this world's script.
	};

	/**
	 * @brief [AI] Constructs the LegoOmni singleton and initializes all internal pointers to NULL/default state. Begins game system setup.
	 */
	LegoOmni();

	/**
	 * @brief [AI] Tears down LegoOmni, deleting or unregistering all major owned game systems and registry lists.
	 */
	~LegoOmni() override;

	/**
	 * @brief [AI] Handles notification messages sent to the engine, including EndAction notifications for quitting, etc.
	 * @param p_param [AI] Parameter describing the notification context.
	 * @return [AI] Dispatch result from MxOmni::Notify.
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns a static string identifying this class for runtime type checking.
	 * @return [AI] String "LegoOmni".
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoOmni";
	}

	/**
	 * @brief [AI] Performs runtime type checking, supporting inheritance. Returns true if input string is "LegoOmni" or matches a parent type.
	 * @param p_name [AI] Class name to test.
	 * @return [AI] TRUE if class name matches or inherits from it.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoOmni::ClassName()) || MxOmni::IsA(p_name);
	}

	/**
	 * @brief [AI] Performs LegoOmni member and subsystem initialization. [AI]
	 */
	void Init() override;

	/**
	 * @brief [AI] Creates and initializes all subsystems for the game, wiring up all managers and attaching Lego-specific logic.
	 * @param p_param [AI] Creation parameter block with flags and resource hints.
	 * @return [AI] Result code: SUCCESS, or FAILURE if allocation/creation fails.
	 */
	MxResult Create(MxOmniCreateParam& p_param) override;

	/**
	 * @brief [AI] Shuts down and deletes all owned game managers, variable tables, registry lists and Lego subsystems.
	 */
	void Destroy() override;

	/**
	 * @brief [AI] Begins executing the specified DSAction/script in the context of the current world/state.
	 * @param p_dsAction [AI] DSAction instance indicating the next action sequence/script.
	 * @return [AI] Start result status.
	 */
	MxResult Start(MxDSAction* p_dsAction) override;

	/**
	 * @brief [AI] Deletes an entity or world referenced by the given DSAction (by object and Atom), cascading to removal in current world.
	 * @param p_dsAction [AI] DSAction describing which entity/world to delete.
	 */
	void DeleteObject(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Checks if the entity described by the DSAction does NOT exist in worlds (true if not found, false if found).
	 * @param p_dsAction [AI] DSAction describing entity.
	 * @return [AI] TRUE if entity does not exist/was removed, FALSE if still present.
	 */
	MxBool DoesEntityExist(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Adds an entity presenter to the specified world (by id or current). Intended for dynamic entity loading.
	 * @param p_id [AI] World id string or "current".
	 * @param p_entityId [AI] Entity id number for lookup.
	 * @param p_presenter [AI] Presenter object to attach (e.g. for video, sound, model).
	 * @return [AI] Pointer to the LegoWorld the presenter was added to, or NULL if not found.
	 */
	MxEntity* AddToWorld(const char* p_id, MxS32 p_entityId, MxPresenter* p_presenter) override;

	/**
	 * @brief [AI] Sends notification to the currently active world. Used for propagating input/events.
	 * @param p_param [AI] Notification parameter struct.
	 */
	void NotifyCurrentEntity(const MxNotificationParam& p_param) override;

	/**
	 * @brief [AI] Pauses the engine/game state and sets busy cursor. [AI]
	 */
	void Pause() override;

	/**
	 * @brief [AI] Resumes engine/game state and sets default cursor. [AI]
	 */
	void Resume() override;

	/**
	 * @brief [AI] Finds and returns the LegoWorld by AtomId and/or entity id.
	 * @param p_atom [AI] AtomId for the world.
	 * @param p_entityid [AI] Entity id (or -1 to skip id check).
	 * @return [AI] Pointer to LegoWorld if found, else NULL.
	 */
	LegoWorld* FindWorld(const MxAtomId& p_atom, MxS32 p_entityid);

	/**
	 * @brief [AI] Finds a top-level LegoROI (region of interest/3D object) by name string.
	 * @param p_name [AI] Name of the ROI.
	 * @return [AI] Pointer to LegoROI if found, else NULL.
	 */
	LegoROI* FindROI(const char* p_name);

	/**
	 * @brief [AI] Appends a LegoWorld to the active world list, acquiring ownership.
	 * @param p_world [AI] The LegoWorld to add.
	 */
	void AddWorld(LegoWorld* p_world);

	/**
	 * @brief [AI] Deletes (and removes from registry) a LegoWorld, deleting all resources.
	 * @param p_world [AI] The world to be deleted.
	 */
	void DeleteWorld(LegoWorld* p_world);

	/**
	 * @brief [AI] Enables or disables input/3d/screen clearing in a single call, based on flags. Used for game-wide state gating.
	 * @param p_disable [AI] TRUE disables (according to flags); FALSE enables.
	 * @param p_flags [AI] Bit field of c_disableInput, c_disable3d, c_clearScreen.
	 */
	void FUN_1005b4f0(MxBool p_disable, MxU16 p_flags);

	/**
	 * @brief [AI] Initializes background audio manager and starts music using global script.
	 */
	void CreateBackgroundAudio();

	/**
	 * @brief [AI] Removes worlds by Atom and/or id, deleting matching entries from the world list and freeing resources.
	 * @param p_atom [AI] AtomId to match, or NULL to match any.
	 * @param p_objectId [AI] Object id to match, or -1 for all.
	 */
	void RemoveWorld(const MxAtomId& p_atom, MxLong p_objectId);

	/**
	 * @brief [AI] Registers all builtin worlds/scripts into the world's Atom/registry list (m_worlds).
	 * @return [AI] SUCCESS if all worlds registered, FAILURE otherwise.
	 */
	MxResult RegisterWorlds();

	/**
	 * @brief [AI] Looks up and returns the registered world key for a world id.
	 * @param p_id [AI] World enum.
	 * @return [AI] String key of world or NULL if not found.
	 */
	const char* GetWorldName(LegoOmni::World p_id);

	/**
	 * @brief [AI] Looks up and returns the AtomId of a world by its enum id.
	 * @param p_id [AI] World enum id.
	 * @return [AI] AtomId pointer or NULL if not found.
	 */
	MxAtomId* GetWorldAtom(LegoOmni::World p_id);

	/**
	 * @brief [AI] Looks up a World enum id from its string key.
	 * @param p_key [AI] Key string (case-insensitive).
	 * @return [AI] World enum if found, e_undefined otherwise.
	 */
	World GetWorldId(const char* p_key);

	/**
	 * @brief [AI] Deletes and clears the current DSAction used for world/entity tracking.
	 */
	void DeleteAction();

	/**
	 * @brief [AI] Static utility for retrieving current path boundary and info from the current world.
	 * @param p_path [AI] Output: pointer to path boundary.
	 * @param p_value [AI] Output: integer info.
	 * @return [AI] FAILURE if no world, else world-specific result.
	 */
	static MxS32 GetCurrPathInfo(LegoPathBoundary**, MxS32&);

	/**
	 * @brief [AI] Allocates and sets up a new LegoOmni singleton instance, replacing the previous one if any.
	 */
	static void CreateInstance();

	/**
	 * @brief [AI] Returns the current LegoOmni singleton pointer, cast from MxOmni.
	 * @return [AI] Singleton pointer.
	 */
	static LegoOmni* GetInstance();

	/**
	 * @brief [AI] Returns the active video manager, cast to LegoVideoManager.
	 * @return [AI] Video manager.
	 */
	LegoVideoManager* GetVideoManager() { return (LegoVideoManager*) m_videoManager; }

	/**
	 * @brief [AI] Returns the sound manager, cast to LegoSoundManager.
	 * @return [AI] Sound manager instance.
	 */
	LegoSoundManager* GetSoundManager() { return (LegoSoundManager*) m_soundManager; }

	/**
	 * @brief [AI] Returns the input manager.
	 * @return [AI] Input manager.
	 */
	LegoInputManager* GetInputManager() { return m_inputManager; }

	/**
	 * @brief [AI] Returns the global texture container (all loaded textures).
	 * @return [AI] Texture container pointer.
	 */
	LegoTextureContainer* GetTextureContainer() { return m_textureContainer; }

	/**
	 * @brief [AI] Returns the LOD list manager for handling refcounted LOD data in the scene.
	 * @return [AI] ViewLODListManager instance.
	 */
	ViewLODListManager* GetViewLODListManager() { return m_viewLODListManager; }

	/**
	 * @brief [AI] Returns the pointer to the currently active world.
	 * @return [AI] The current LegoWorld instance.
	 */
	LegoWorld* GetCurrentWorld() { return m_currentWorld; }

	/**
	 * @brief [AI] Returns the navigation controller (handles player navigation and camera logic).
	 * @return [AI] Nav controller pointer.
	 */
	LegoNavController* GetNavController() { return m_navController; }

	/**
	 * @brief [AI] Returns the player-controlled ("user") actor.
	 * @return [AI] User path actor pointer.
	 */
	LegoPathActor* GetUserActor() { return m_userActor; }

	/**
	 * @brief [AI] Returns active plant manager, which tracks in-world plants/objects.
	 * @return [AI] Plant manager pointer.
	 */
	LegoPlantManager* GetPlantManager() { return m_plantManager; }

	/**
	 * @brief [AI] Returns animation manager for managing character/world animations.
	 * @return [AI] Animation manager pointer.
	 */
	LegoAnimationManager* GetAnimationManager() { return m_animationManager; }

	/**
	 * @brief [AI] Returns building manager (handles in-world structures and their logic).
	 * @return [AI] Building manager pointer.
	 */
	LegoBuildingManager* GetBuildingManager() { return m_buildingManager; }

	/**
	 * @brief [AI] Returns pointer to world and script registry list.
	 * @return [AI] LegoWorldList pointer.
	 */
	LegoWorldList* GetWorldList() { return m_worldList; }

	/**
	 * @brief [AI] Returns the global game state tracker.
	 * @return [AI] Game state pointer.
	 */
	LegoGameState* GetGameState() { return m_gameState; }

	/**
	 * @brief [AI] Returns handle to the background audio manager (jukebox/music/ambience).
	 * @return [AI] Background audio manager pointer.
	 */
	MxBackgroundAudioManager* GetBackgroundAudioManager() { return m_bkgAudioManager; }

	/**
	 * @brief [AI] Returns transition manager for handling UI/game state transitions/fades.
	 * @return [AI] Transition manager.
	 */
	MxTransitionManager* GetTransitionManager() { return m_transitionManager; }

	/**
	 * @brief [AI] Returns the actual DSAction used for the current/pending event.
	 * @return [AI] Current action reference.
	 */
	MxDSAction& GetCurrentAction() { return m_action; }

	/**
	 * @brief [AI] Returns character manager, handling population and logic for all in-world characters.
	 * @return [AI] Character manager pointer.
	 */
	LegoCharacterManager* GetCharacterManager() { return m_characterManager; }

	/**
	 * @brief [AI] Sets the navigation controller.
	 * @param p_navController [AI] Nav controller to use.
	 */
	void SetNavController(LegoNavController* p_navController) { m_navController = p_navController; }

	/**
	 * @brief [AI] Sets the user actor pointer (player).
	 * @param p_userActor [AI] User actor to use.
	 */
	void SetUserActor(LegoPathActor* p_userActor) { m_userActor = p_userActor; }

	/**
	 * @brief [AI] Sets the current world pointer for global context.
	 * @param p_currentWorld [AI] World to use.
	 */
	void SetCurrentWorld(LegoWorld* p_currentWorld) { m_currentWorld = p_currentWorld; }

	/**
	 * @brief [AI] Signals the engine to exit/game quit procedure.
	 * @param p_exit [AI] TRUE to begin exit process.
	 */
	void SetExit(MxBool p_exit) { m_exit = p_exit; }

	/**
	 * @brief [AI] Starts action if the unknown0x13c member is set; otherwise returns success. Helper for rare logic.
	 * @param p_dsAction [AI] Action to start.
	 * @return [AI] Start result or SUCCESS if not started.
	 */
	MxResult StartActionIfUnknown0x13c(MxDSAction& p_dsAction) { return m_unk0x13c ? Start(&p_dsAction) : SUCCESS; }

	/**
	 * @brief [AI] Sets the unknown0x13c flag (purpose not fully documented in reverse). [AI]
	 * @param p_unk0x13c [AI] Value to set.
	 */
	void SetUnknown13c(MxBool p_unk0x13c) { m_unk0x13c = p_unk0x13c; }

	/**
	 * @brief [AI] Posts a close (exit) message to the main window handle, triggering shutdown.
	 */
	void CloseMainWindow() { PostMessageA(m_windowHandle, WM_CLOSE, 0, 0); }

	// SYNTHETIC: LEGO1 0x10058b30
	// LegoOmni::`scalar deleting destructor'

private:
	WorldContainer* m_worlds;                    ///< [AI] World registry table mapping enum to script keys and AtomIds. [AI]
	ViewLODListManager* m_viewLODListManager;    ///< [AI] Manager for all loaded/rendered LOD lists in scene. [AI]
	LegoInputManager* m_inputManager;            ///< [AI] Handles all keyboard/mouse/gamepad input logic. [AI]
	LegoTextureContainer* m_textureContainer;    ///< [AI] Manages storage/ownership of loaded textures. [AI]
	LegoWorldList* m_worldList;                  ///< [AI] List of all active LegoWorld objects (scene registry). [AI]
	LegoWorld* m_currentWorld;                   ///< [AI] Currently active world. [AI]
	MxBool m_exit;                               ///< [AI] Flag controlling engine exit/main loop. [AI]
	LegoNavController* m_navController;          ///< [AI] Handles navigation/camera system. [AI]
	LegoPathActor* m_userActor;                  ///< [AI] Main player actor. [AI]
	LegoCharacterManager* m_characterManager;    ///< [AI] Manages all in-game NPCs/characters. [AI]
	LegoPlantManager* m_plantManager;            ///< [AI] Plant (flora/object) manager in map. [AI]
	LegoAnimationManager* m_animationManager;    ///< [AI] Handles all engine animation subsystems. [AI]
	LegoBuildingManager* m_buildingManager;      ///< [AI] Building/structure management. [AI]
	LegoGameState* m_gameState;                  ///< [AI] Tracks act, time, player stats, etc. [AI]
	MxDSAction m_action;                         ///< [AI] DSAction currently active in the engine. [AI]
	MxBackgroundAudioManager* m_bkgAudioManager; ///< [AI] Background ambient music manager. [AI]
	MxTransitionManager* m_transitionManager;    ///< [AI] In-game fade/transition/cutscene manager. [AI]

public:
	MxBool m_unk0x13c; ///< [AI] Unknown flag used in rare start-action cases. [AI]
};

#endif // LEGOMAIN_H
