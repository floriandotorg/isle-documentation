#ifndef LEGOANIMATIONMANAGER_H
#define LEGOANIMATIONMANAGER_H

#include "decomp.h"
#include "legolocations.h"
#include "legomain.h"
#include "legostate.h"
#include "legotraninfolist.h"
#include "mxcore.h"
#include "mxgeometry/mxquaternion.h"

class LegoAnimPresenter;
class LegoEntity;
class LegoExtraActor;
class LegoFile;
class LegoPathActor;
class LegoPathBoundary;
class LegoROIList;
struct LegoUnknown100db7f4;
class LegoWorld;
class MxDSAction;

/// @struct ModelInfo
/// @brief [AI] Contains information about a model used in an animation, including name and orientation.
/// @details [AI] ModelInfo provides positional (location), directional and "up" vectors, as well as internal flags. Used for animation definition.
///
struct ModelInfo {
	char* m_name;         ///< Name of the model. [AI]
	MxU8 m_unk0x04;       ///< Unknown byte flag. [AI]
	float m_location[3];  ///< Location/origin for the model in 3D space. [AI]
	float m_direction[3]; ///< Forward/direction vector. [AI]
	float m_up[3];        ///< Up vector for the model orientation. [AI]
	MxU8 m_unk0x2c;       ///< Unknown purpose, acts as a boolean/flag. [AI]
};

/// @struct AnimInfo
/// @brief [AI] Describes a specific animation, containing animation parameters, model list, and related metadata used by the animation system.
/// @details [AI] Includes storage for animation name, references to models, and position/direction data; also contains state flag fields related to animation progression and selection.
///
struct AnimInfo {
	char* m_name;          ///< Animation name. [AI]
	MxU32 m_objectId;      ///< Object ID corresponding to this animation; used as a unique key. [AI]
	MxS16 m_location;      ///< Location index if relevant (−1 for omni/global). [AI]
	MxBool m_unk0x0a;      ///< Boolean to control startup/behavioral logic. [AI]
	MxU8 m_unk0x0b;        ///< Purpose unknown; animation-related flag. [AI]
	MxU8 m_unk0x0c;        ///< Bitmask related to actor/vehicle ability to use this animation (see g_unk0x100d8b28). [AI]
	MxU8 m_unk0x0d;        ///< Additional animation state flag. [AI]
	float m_unk0x10[4];    ///< Animation parameters: start/target position and radius. [AI]
	MxU8 m_modelCount;     ///< Number of models referenced in m_models array. [AI]
	MxU16 m_unk0x22;       ///< Use-count or instance count for this animation. [AI]
	ModelInfo* m_models;   ///< Array of ModelInfo structs for the animation's involved models. [AI]
	MxS8 m_characterIndex; ///< Index into g_characters for the owning character (-1 if not set). [AI]
	MxBool m_unk0x29;      ///< Animation is active/available/playable. [AI]
	MxS8 m_unk0x2a[3];     ///< Vehicle indices or similar (max 3), for use by certain actors. [AI]
};

/// @class AnimState
/// @brief [AI] Persistent serializable animation state for resuming animations and restoring global animation progress.
/// @details [AI] AnimState holds state info such as used animation counts and world/character state required for saving and resetting. It is derived from LegoState to be managed by the game's global state system.
///
class AnimState : public LegoState {
public:
	AnimState(); ///< Constructor. [AI]
	~AnimState() override; ///< Destructor, releases animation tracking arrays. [AI]

	/// @brief [AI] Gets the class name ("AnimState").
	const char* ClassName() const override;

	/// @brief [AI] Checks if this or a parent is the given class.
	MxBool IsA(const char* p_name) const override;

	/// @brief [AI] Resets all tracked animation usage to default.
	MxBool Reset() override;

	/// @brief [AI] Serialize state to or from disk for save/load. [AI]
	/// @param p_storage Storage to read from or write to. [AI]
	MxResult Serialize(LegoStorage* p_storage) override;

	/// @brief [AI] Writes tracked usage data to animations. [AI]
	/// @param p_anims Animation array to copy to. [AI]
	/// @param p_outExtraCharacterId (output) Last used extra character. [AI]
	void CopyToAnims(MxU32, AnimInfo* p_anims, MxU32& p_outExtraCharacterId);

	/// @brief [AI] Reads usage state from animations and stores it in this AnimState.
	/// @param p_animsLength Number of animation entries. [AI]
	/// @param p_anims Animation array to read from. [AI]
	/// @param p_extraCharacterId Last extra character ID. [AI]
	void InitFromAnims(MxU32 p_animsLength, AnimInfo* p_anims, MxU32 p_extraCharacterId);

private:
	MxU32 m_extraCharacterId;       ///< Used for persistently tracking the next extra character to spawn. [AI]
	MxU32 m_unk0x0c;                ///< Number of entries in m_unk0x10. [AI]
	MxU16* m_unk0x10;               ///< Array of usage counters for each animation (matches AnimInfo::m_unk0x22). [AI]
	MxU32 m_locationsFlagsLength;   ///< Number of entries in m_locationsFlags. [AI]
	MxBool* m_locationsFlags;       ///< Array of flags per location, tied to random animation logic. [AI]
};

/// @class LegoAnimationManager
/// @brief [AI] Animation manager handling all world and character animation state, loading, and logic for extras and transitions.
/// @details [AI] Coordinates the active animations, their states, extra characters (extras), model loads, world animation loading, and camera/transition animation logic. Called as part of the engine's tickle/tick system and notification handling.
///
class LegoAnimationManager : public MxCore {
public:
	/// @struct Character
	/// @brief [AI] Static definition of a character, its animation settings, flags, and world identity.
	struct Character {
		const char* m_name;    ///< Character's name/identifier (must be unique). [AI]
		MxBool m_inExtras;     ///< True if this character is currently active as an 'extra'. [AI]
		MxS8 m_vehicleId;      ///< Index into the vehicle array for this character's vehicle, −1 if not relevant. [AI]
		undefined m_unk0x06;   ///< [AI_SUGGESTED_NAME: unusedPadding] Currently unused byte. [AI]
		MxBool m_unk0x07;      ///< Flag for reuse/destruction logic; meaning: pending return to actor pool. [AI]
		MxBool m_unk0x08;      ///< Boolean, TRUE if this character is eligible for "extra" animation. [AI]
		MxBool m_unk0x09;      ///< Boolean, TRUE if this character is ever to be placed as an extra at all. [AI]
		MxS32 m_unk0x0c;       ///< Minimum idle time before main animation for this character (milliseconds). [AI]
		MxS32 m_unk0x10;       ///< Maximum idle time before main animation for this character (milliseconds). [AI]
		MxBool m_active;       ///< Runtime flag; TRUE if animation for this character is currently activated (in any mode). [AI]
		MxU8 m_unk0x15;        ///< Probability (0–100) used for random vehicle assignment. [AI]
		MxS8 m_unk0x16;        ///< Index in g_cycles, used for finding correct main/alternative cycle animations for this character. [AI]
	};

	/// @struct Vehicle
	/// @brief [AI] Static definition of a vehicle, including its name and state flags.
	struct Vehicle {
		const char* m_name;    ///< Vehicle's name (corresponds to a ROI/model name). [AI]
		MxBool m_unk0x04;      ///< TRUE if this vehicle is to be used in the next animation cycle. [AI]
		MxBool m_unk0x05;      ///< TRUE if this vehicle is reserved by an actor present as an extra. [AI]
	};

	/// @struct Extra
	/// @brief [AI] Tracks a currently active extra (non-player) actor in the world, with associated parameters.
	struct Extra {
		LegoROI* m_roi;      ///< ROI object for this extra; NULL if slot unused. [AI]
		MxS32 m_characterId; ///< Index into g_characters, currently loaded actor type. [AI]
		MxLong m_unk0x08;    ///< Last time this extra was updated or used, ms. [AI]
		MxBool m_unk0x0c;    ///< Used to signal waiting for an animation activation. [AI]
		MxBool m_unk0x0d;    ///< Indicates that this extra is to be purged/removed at next tick. [AI]
		float m_speed;       ///< Animation speed for the extra; negative to indicate not set. [AI]
		MxBool m_unk0x14;    ///< TRUE if this extra is currently in a vehicle animation. [AI]
	};

	/// @enum PlayMode
	/// @brief [AI] Animation play modes, possibly for controlling explicit or random playback.
	enum PlayMode {
		e_unk0 = 0, ///< [AI] Unknown/unspecified play mode
		e_unk1,     ///< [AI] Unknown/unspecified play mode
		e_unk2      ///< [AI] Unknown/unspecified play mode
	};

	LegoAnimationManager(); ///< Default constructor. [AI]
	~LegoAnimationManager() override; ///< Destructor, cleans up all allocations and deregisters from tickle/notify. [AI]

	/// @brief [AI] Handles system/game notifications, e.g. end of animation events.
	/// @param p_param Notification parameter. [AI]
	MxLong Notify(MxParam& p_param) override;

	/// @brief [AI] Called by tick manager, processes world/time-based animation logic, including spawning extras and updating transitions.
	MxResult Tickle() override;

	/// @brief [AI] Gets the class name ("LegoAnimationManager").
	const char* ClassName() const override;

	/// @brief [AI] Checks if this or a parent is the given class.
	MxBool IsA(const char* p_name) const override;

	/// @brief [AI] Resets all internal state; optionally resets animation state too.
	/// @param p_und If TRUE, animation state is reset. [AI]
	void Reset(MxBool p_und);

	/// @brief [AI] Suspends all activity, saving out transition/animation state, and disables extra processing.
	void Suspend();

	/// @brief [AI] Resumes animation manager from suspension, restoring all previously suspended state.
	void Resume();

	/// @brief [AI] Enables or disables extras (extra actors). If disabling, purges all extras.
	/// @param p_unk0x400 TRUE to enable extras, FALSE to disable and remove all extras. [AI]
	void FUN_1005f6d0(MxBool p_unk0x400);

	/// @brief [AI] Sets whether camera-based queued animations are enabled for the world.
	/// @param p_enableCamAnims TRUE to enable, FALSE to disable. [AI]
	void EnableCamAnims(MxBool p_enableCamAnims);

	/// @brief [AI] Loads all world animation and extra info. Called on world change.
	/// @param p_worldId The world identifier. [AI]
	MxResult LoadWorldInfo(LegoOmni::World p_worldId);

	/// @brief [AI] Looks up a vehicle by name, returning its index if found.
	/// @param p_name Vehicle name to search for. [AI]
	/// @param p_index (output) Found vehicle index. [AI]
	MxBool FindVehicle(const char* p_name, MxU32& p_index);

	/// @brief [AI] Reads an AnimInfo entry from file storage, building model list and parsing parameters.
	/// @param p_storage Input file reader. [AI]
	/// @param p_info Populated AnimInfo. [AI]
	MxResult ReadAnimInfo(LegoStorage* p_storage, AnimInfo* p_info);

	/// @brief [AI] Reads a single ModelInfo out of storage. Used for parsing animation's model details.
	/// @param p_storage File input. [AI]
	/// @param p_info ModelInfo structure to fill. [AI]
	MxResult ReadModelInfo(LegoStorage* p_storage, ModelInfo* p_info);

	/// @brief [AI] Marks characters in the global character list (g_characters) as available for animation according to an input list.
	/// @param p_characterNames Array of names to enable. [AI]
	/// @param p_numCharacterNames Number of entries in array. [AI]
	void FUN_10060480(const LegoChar* p_characterNames[], MxU32 p_numCharacterNames);

	/// @brief [AI] Sets the m_unk0x08 flag for all characters. [AI]
	/// @param p_unk0x08 Value to set for all characters (TRUE/FALSE). [AI]
	void FUN_100604d0(MxBool p_unk0x08);

	/// @brief [AI] Enables/disables certain animations by object id list (sets m_unk0x29 flag in AnimInfo).
	/// @param p_objectIds Array of object IDs. [AI]
	/// @param p_numObjectIds Count of object IDs. [AI]
	void FUN_100604f0(MxS32 p_objectIds[], MxU32 p_numObjectIds);

	/// @brief [AI] Sets the 'enabled for random camera animation' flag for all animations.
	/// @param p_unk0x29 TRUE/FALSE to set. [AI]
	void FUN_10060540(MxBool p_unk0x29);

	/// @brief [AI] Sets whether the manager should immediately trigger camera transition animations in quick succession.
	/// @param p_unk0x1a TRUE to enable, FALSE to clear. [AI]
	void FUN_10060570(MxBool p_unk0x1a);

	/// @brief [AI] Starts a DSAction for a specific entity, managing controller/actor logic if relevant.
	/// @param p_dsAction The action to start. [AI]
	/// @param p_entity Entity for this action (must not be NULL). [AI]
	MxResult StartEntityAction(MxDSAction& p_dsAction, LegoEntity* p_entity);

	/// @brief [AI] Helper for starting a specific animation, including world matrix and camera settings.
	/// @param ... Parameters for start; see implementation for detailed logic. [AI]
	MxResult FUN_10060dc0(
		MxU32 p_objectId,
		MxMatrix* p_matrix,
		MxBool p_param3,
		MxU8 p_param4,
		LegoROI* p_roi,
		MxBool p_param6,
		MxBool p_param7,
		MxBool p_param8,
		MxBool p_param9
	);

	/// @brief [AI] Triggers a camera animation based on user and location state. [AI]
	/// @param p_actor User actor. [AI]
	/// @param ... See implementation for exact call logic. [AI]
	void CameraTriggerFire(LegoPathActor* p_actor, MxBool, MxU32 p_location, MxBool p_bool);

	/// @brief [AI] Cancels all camera/transition animations and resets camera after completion.
	/// @param p_und TRUE to fully stop, FALSE to only end visuals. [AI] 
	void FUN_10061010(MxBool p_und);

	/// @brief [AI] Retrieves an active transition info, or NULL if not found.
	/// @param p_index Index into tranInfo list to locate. [AI]
	LegoTranInfo* GetTranInfo(MxU32 p_index);

	/// @brief [AI] Initializes sound transitions if not already active for the current world.
	void FUN_10062770();

	/// @brief [AI] Removes all extras matching current world/time criteria (but not the player's current character).
	/// @param p_und TRUE to purge, FALSE for timed/policy cleanup. [AI]
	void PurgeExtra(MxBool p_und);

	/// @brief [AI] Spawns a new extra actor at a boundary or location, if capacity and logic allow.
	/// @param p_location Index (−1 for random). [AI]
	/// @param p_und TRUE for forced placement, else timed. [AI]
	void AddExtra(MxS32 p_location, MxBool p_und);

	/// @brief [AI] Handles "extras" onboarding by evaluating visibility and position for presenter-based animation.
	/// @param p_list ROI list of extras to present. [AI]
	/// @param p_presenter Animation presenter. [AI]
	void FUN_10063270(LegoROIList* p_list, LegoAnimPresenter* p_presenter);

	/// @brief [AI] Examines an ROI list and adds all actors of type to internal "pending" list for extras.
	/// @param p_list List to check. [AI]
	void FUN_10063780(LegoROIList* p_list);

	/// @brief [AI] Activates special triggered animation in response to player position near given point.
	/// @param p_position World position to test proximity. [AI]
	MxResult FUN_10064670(Vector3* p_position);

	/// @brief [AI] Similar to FUN_10064670, but triggers a different special animation event for secondary location or characters.
	/// @param p_position World position. [AI]
	MxResult FUN_10064740(Vector3* p_position);

	/// @brief [AI] Updates the configuration values (global) for animation manager's allowed number of extras, performance settings etc.
	/// @param p_legoAnimationManagerConfig Config value (usually 1 or 2). [AI]
	static void configureLegoAnimationManager(MxS32 p_legoAnimationManagerConfig);

	/// @brief [AI] Updates specified character's extra animation idle/play time values for active extras.
	/// @param p_name Name of extra. [AI]
	/// @param p_unk0x0c Minimum idle time. [AI]
	/// @param p_unk0x10 Maximum idle time. [AI]
	MxResult FUN_10064880(const char* p_name, MxS32 p_unk0x0c, MxS32 p_unk0x10);

	/// @brief [AI] Determines if any currently running animation is assigned to the given objectId, and queries its presenter.
	/// @param p_objectId Animation object id. [AI]
	MxBool FUN_10064ee0(MxU32 p_objectId);

	// -- internal/private methods and members follow -- [AI]
private:
	void Init(); ///< Internal initializer, called from ctor and after deletes. [AI]

	MxResult FUN_100605e0(
		MxU32 p_index,
		MxBool p_unk0x0a,
		MxMatrix* p_matrix,
		MxBool p_bool1,
		LegoROI* p_roi,
		MxBool p_bool2,
		MxBool p_bool3,
		MxBool p_bool4,
		MxBool p_bool5
	);

	MxResult FUN_100609f0(MxU32 p_objectId, MxMatrix* p_matrix, MxBool p_und1, MxBool p_und2);

	/// @brief [AI] Deletes all loaded animations, models, and frees related memory.
	void DeleteAnimations();

	void FUN_10061530();

	/// @brief [AI] Retrieves indices into global animation array for location-bounded animations.
	MxResult FUN_100617c0(MxS32 p_unk0x08, MxU16& p_unk0x0e, MxU16& p_unk0x10);

	MxU16 FUN_10062110(
		LegoROI* p_roi,
		Vector3& p_direction,
		Vector3& p_position,
		LegoPathBoundary* p_boundary,
		float p_speed,
		MxU8 p_unk0x0c,
		MxBool p_unk0x14
	);

	/// @brief [AI] Looks for character's index in g_characters given name (case-insensitive compare on first 2 letters).
	MxS8 GetCharacterIndex(const char* p_name);

	/// @brief [AI] Determines if any non-player actor is in range of position/radius for targeted animation (obstruction check).
	MxBool FUN_100623a0(AnimInfo& p_info);

	/// @brief [AI] Checks if a given model is included in an animation's model list.
	MxBool ModelExists(AnimInfo& p_info, const char* p_name);

	/// @brief [AI] Removes extra actors used in a given animation.
	void FUN_10062580(AnimInfo& p_info);

	/// @brief [AI] Spatial collision check for actor to model for camera animation eligibility.
	MxBool FUN_10062650(Vector3& p_position, float p_und, LegoROI* p_roi);

	/// @brief [AI] Tests current-game actor's eligibility for a given animation (vehicle/mask compatibility).
	MxBool FUN_10062710(AnimInfo& p_info);

	/// @brief [AI] Attempts to assign an extra (ROI) to a presenter-based camera animation, including controller logic.
	MxBool FUN_10062e20(LegoROI* p_roi, LegoAnimPresenter* p_presenter);

	void FUN_10063950(LegoROI* p_roi);
	void FUN_10063aa0();

	/// @brief [AI] Binds an animation presenter to a world/extra actor according to desired mood/vehicle. Also activates vehicle if needed.
	/// @param p_world Current world. [AI]
	/// @param p_actor Actor ROI. [AI]
	/// @param p_mood Integer mood type for animation selection. [AI]
	/// @param p_characterId Index into g_characters. [AI]
	MxBool FUN_10063b90(LegoWorld* p_world, LegoExtraActor* p_actor, MxU8 p_mood, MxU32 p_characterId);

	void FUN_10063d10();
	void FUN_10063e40(LegoAnimPresenter* p_presenter);

	/// @brief [AI] Checks a world boundary (navigation) for availability to place an extra actor.
	MxBool FUN_10063fb0(LegoLocation::Boundary* p_boundary, LegoWorld* p_world);

	/// @brief [AI] Checks if animation can be played given the edge and destination scaling.
	MxBool FUN_10064010(LegoPathBoundary* p_boundary, LegoUnknown100db7f4* p_edge, float p_destScale);

	/// @brief [AI] Fills in a random boundary for placing extras in a world (either clockwise or counter-clockwise based on bools).
	MxBool FUN_10064120(LegoLocation::Boundary* p_boundary, MxBool p_bool1, MxBool p_bool2);

	/// @brief [AI] Places/choreographs an extra at the specified location, animates, and updates extra slot state arrays.
	MxResult FUN_10064380(
		const char* p_name,
		const char* p_boundaryName,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale,
		MxU32 p_undIdx1,
		MxS32 p_unk0x0c,
		MxU32 p_undIdx2,
		MxS32 p_unk0x10,
		float p_speed
	);

	/// @brief [AI] Handles camera animation matrix interpolation for camera flyby's and transition events.
	void FUN_100648f0(LegoTranInfo* p_tranInfo, MxLong p_unk0x404);

	/// @brief [AI] Applies the in-progress transition animation camera/view? for a given time.
	void FUN_10064b50(MxLong p_time);

	LegoOmni::World m_worldId;          ///< Current loaded world. [AI]
	MxU16 m_animCount;                  ///< Number of active AnimInfo entries. [AI]
	MxU16 m_unk0x0e;                    ///< Lower index of animations used for random/camera event. [AI]
	MxU16 m_unk0x10;                    ///< Upper index of animations for random/camera. [AI]
	AnimInfo* m_anims;                  ///< List of loaded animations. [AI]
	undefined2 m_unk0x18;               ///< Internal counter for batch animation cycle. [AI]
	MxBool m_unk0x1a;                   ///< Tick: whether a special campaign animation sequence is running. [AI]
	MxU32 m_unk0x1c;                    ///< Latest transaction/animation sequence index. [AI]
	LegoTranInfoList* m_tranInfoList;   ///< Active animations in progress (main). [AI]
	LegoTranInfoList* m_tranInfoList2;  ///< Staged/secondary animation progress list (pending cleanup). [AI]
	MxPresenter* m_unk0x28[2];          ///< Animation-synchronized sound presenters used for crossfades. [AI]
	MxLong m_unk0x30[2];                ///< Sound presentation fade/delay parameters. [AI]
	MxBool m_unk0x38;                   ///< TRUE if sound presenters have been initialized. [AI]
	MxBool m_animRunning;               ///< Animation in progress. [AI]
	MxBool m_enableCamAnims;            ///< TRUE if random/camera animations are enabled for current world. [AI]
	Extra m_extras[40];                 ///< Table of up to 40 extra actors as world background/ambient characters. [AI]
	MxU32 m_lastExtraCharacterId;       ///< Last used characterId for cycling extras round robin. [AI]
	MxBool m_unk0x400;                  ///< TRUE if extras enabled for current tick loop. [AI]
	MxBool m_unk0x401;                  ///< TRUE signals pending removal of all extras at next tick. [AI]
	MxBool m_unk0x402;                  ///< TRUE if animation world data fully loaded. [AI]
	MxLong m_unk0x404;                  ///< Last animation event start time (ms). [AI]
	MxLong m_unk0x408;                  ///< Time when last extra/camera animation was processed. [AI]
	MxLong m_unk0x40c;                  ///< Time for last secondary effect or actor update. [AI]
	MxLong m_unk0x410;                  ///< Next extra/camera animation scheduling interval (rand). [AI]
	MxU32 m_unk0x414;                   ///< Current number of active extras. [AI]
	MxU32 m_numAllowedExtras;           ///< Maximum concurrent extras allowed for perf. [AI]
	undefined4 m_unk0x41c;              ///< Extra/config/state bytes (used as alternate max extras at higher setting). [AI]
	AnimState* m_animState;             ///< Animation persistent state for save/load. [AI]
	LegoROIList* m_unk0x424;            ///< List of eligible extras/pending actors for animation injection. [AI]
	MxBool m_suspendedEnableCamAnims;   ///< If suspended, original cam animation enable state. [AI]
	MxBool m_unk0x429;                  ///< If suspended, stored m_unk0x400. [AI]
	MxBool m_unk0x42a;                  ///< If suspended, stored m_unk0x402. [AI]
	MxBool m_suspended;                 ///< TRUE if manager is currently suspended by system. [AI]
	LegoTranInfo* m_unk0x42c;           ///< Animation info for an in-progress transition. [AI]
	MxBool m_unk0x430;                  ///< TRUE if transition animation is active. [AI]
	MxLong m_unk0x434;                  ///< Transition animation time (start). [AI]
	MxLong m_unk0x438;                  ///< Transition animation time (end). [AI]
	MxMatrix m_unk0x43c;                ///< Camera matrix at start of transition. [AI]
	MxMatrix m_unk0x484;                ///< Camera matrix at end of transition. [AI]
	MxQuaternionTransformer m_unk0x4cc; ///< Quaternion transformer for interpolating camera transitions. [AI]
};

#endif // LEGOANIMATIONMANAGER_H
