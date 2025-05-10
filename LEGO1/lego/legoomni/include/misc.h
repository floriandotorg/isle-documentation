#ifndef MISC_H
#define MISC_H

#include "compat.h"
#include "decomp.h"
// Long include path due to dependency of misc library on LegoOmni
#include "lego/legoomni/include/actions/actionsfwd.h"
#include "mxtypes.h"

class LegoAnimationManager;
class LegoBuildingManager;
class LegoCharacterManager;
class LegoControlManager;
class LegoGameState;
class LegoInputManager;
class LegoNavController;
class LegoOmni;
class LegoPathActor;
class LegoPlantManager;
class LegoROI;
class LegoSoundManager;
class LegoTextureContainer;
class LegoVideoManager;
class LegoWorld;
class MxAtomId;
class MxBackgroundAudioManager;
class MxDSAction;
class MxTransitionManager;
class ViewLODListManager;
class ViewManager;

/// Global variable indicating whether the current LegoWorld is considered active.
/// Used to block user/camera control and can be checked by presenters to block tickle calls (e.g. for freezing cutscenes or scripted world events).
extern MxBool g_isWorldActive; ///< [AI] True if the world should be considered "active" for user or presenter logic

/// @brief [AI] Retrieves the global LegoOmni singleton instance, providing access to core subsystems.
/// @return Pointer to LegoOmni instance. [AI]
LegoOmni* Lego();

/// @brief [AI] Accessor for the game's LegoSoundManager subsystem from the global LegoOmni instance. [AI]
LegoSoundManager* SoundManager();

/// @brief [AI] Accessor for the game's LegoVideoManager subsystem. Used for managing 3D/video hardware. [AI]
LegoVideoManager* VideoManager();

/// @brief [AI] Accessor for the background audio manager. Used for background music and ambient sounds. [AI]
MxBackgroundAudioManager* BackgroundAudioManager();

/// @brief [AI] Accessor for the input manager, which handles keyboard, mouse, and controller input. [AI]
LegoInputManager* InputManager();

/// @brief [AI] Accessor for the control manager through the input manager; manages higher-level user/game controls. [AI]
LegoControlManager* ControlManager();

/// @brief [AI] Accessor for the game's central game state controller. [AI]
LegoGameState* GameState();

/// @brief [AI] Accessor for the animation manager, which controls Lego character/world animation state. [AI]
LegoAnimationManager* AnimationManager();

/// @brief [AI] Accessor for the navigation controller, managing player/camera navigation. [AI]
LegoNavController* NavController();

/// @brief [AI] Accessor for the user (player-controllable) LegoPathActor. [AI]
LegoPathActor* UserActor();

/// @brief [AI] Accessor for the currently active LegoWorld instance. [AI]
LegoWorld* CurrentWorld();

/// @brief [AI] Accessor for the character manager, which manages in-game characters/NPCs. [AI]
LegoCharacterManager* CharacterManager();

/// @brief [AI] Accessor for the current ViewManager, managing rendering views/cameras. [AI]
ViewManager* GetViewManager();

/// @brief [AI] Accessor for the plant manager, handling in-game foliage and plants. [AI]
LegoPlantManager* PlantManager();

/// @brief [AI] Accessor for the building manager, handles constructible buildings and structures. [AI]
LegoBuildingManager* BuildingManager();

/// @brief [AI] Accessor for the texture container used for global texture management. [AI]
LegoTextureContainer* TextureContainer();

/// @brief [AI] Returns the global ViewLODListManager for view LOD (Level of Detail) resources. [AI]
ViewLODListManager* GetViewLODListManager();

/// @brief [AI] Utility for enabling or disabling functionality in LegoOmni based on certain flags. Internal use. [AI]
/// @param p_disable [AI] If true, disables the feature/subsystem identified by p_flags.
/// @param p_flags [AI] Flags determining the feature/subsystem to affect.
void FUN_10015820(MxBool p_disable, MxU16 p_flags);

/// @brief [AI] Looks up a LegoROI (Real-time Object Instance) by name in the current world or global registry.
/// @param p_name [AI] The name of the ROI object to search for.
/// @return Pointer to found LegoROI, or NULL if not found. [AI]
LegoROI* FindROI(const char* p_name);

/// @brief [AI] Utility for setting the visibility flag of a named ROI object. [AI]
/// @param p_name [AI] Name of the ROI to affect.
/// @param p_visible [AI] If true, ROI is set visible; otherwise, hidden.
void SetROIVisible(const char* p_name, MxBool p_visible);

/// @brief [AI] Sets the user-controlled LegoPathActor in the engine. [AI]
/// @param p_userActor [AI] The actor to set as the player-controllable entity.
void SetUserActor(LegoPathActor* p_userActor);

/// @brief [AI] Triggers a DSAction if a certain unknown flag (0x13c) is set.
/// @details [AI] Underlying logic checks the LegoOmni subsystem for special conditions before starting the action.
/// @param p_dsAction [AI] The action data to attempt to start.
/// @return SUCCESS or FAILURE depending on conditions. [AI]
MxResult StartActionIfUnknown0x13c(MxDSAction& p_dsAction);

/// @brief [AI] Deletes (or cancels) the currently running DSAction/cutscene/event logic. [AI]
void DeleteAction();

/// @brief [AI] Searches for or retrieves a LegoWorld instance based on an atom id and entity id.
/// @param p_atom [AI] The atom (unique) id representing the world/resource to search for.
/// @param p_entityid [AI] Entity id to further qualify the search.
/// @return Pointer to the found LegoWorld or NULL if not found. [AI]
LegoWorld* FindWorld(const MxAtomId& p_atom, MxS32 p_entityid);

/// @brief [AI] Accessor for the currently running MxDSAction (e.g. current cutscene logic/event). [AI]
/// @return Reference to the current MxDSAction. [AI]
MxDSAction& GetCurrentAction();

/// @brief [AI] Sets the current LegoWorld used for all world/scene logic. [AI]
/// @param p_world [AI] The new world to activate.
void SetCurrentWorld(LegoWorld* p_world);

/// @brief [AI] Accessor for the MxTransitionManager, handling level transitions, fades, and world changes. [AI]
MxTransitionManager* TransitionManager();

/// @brief [AI] Starts music playback by scripting the background audio manager to play the music piece referenced by the script/object id. [AI]
/// @param p_objectId [AI] The jukebox script object id representing the music track to play.
void PlayMusic(JukeboxScript::Script p_objectId);

/// @brief [AI] Toggles whether the world should be considered active (enables/disables camera/user control etc). [AI]
/// @param p_isWorldActive [AI] True = world and user controls active; False = blocked/frozen (e.g. during cutscenes).
void SetIsWorldActive(MxBool p_isWorldActive);

/// @brief [AI] Batch deletes objects, given by atom id, and within the entity id range [p_first, p_last].
/// @param p_id [AI] The atom id representing the type/group of objects.
/// @param p_first [AI] The first entity id to delete.
/// @param p_last [AI] The last entity id (inclusive) to delete.
void DeleteObjects(MxAtomId* p_id, MxS32 p_first, MxS32 p_last);

#endif // MISC_H
