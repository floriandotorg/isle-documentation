#ifndef ISLEPATHACTOR_H
#define ISLEPATHACTOR_H

#include "legogamestate.h"
#include "legopathactor.h"
#include "mxtypes.h"
#include "roi/legoroi.h"

class LegoControlManagerNotificationParam;
class LegoEndAnimNotificationParam;
class LegoWorld;
class LegoPathStructNotificationParam;

// VTABLE: LEGO1 0x100d4398
// VTABLE: BETA10 0x101b9090
// SIZE 0x160
/**
 * @brief Derived path actor type for handling player transitions and activities on LEGO Island. [AI]
 * @details [AI] IslePathActor manages the player character as it moves between different locations in the open world,
 * handles entering and exiting areas, player spawning at registered locations, and the associated notifications for animation and control.
 * It integrates with world state, boundaries, and the visual ROI system.
 */
class IslePathActor : public LegoPathActor {
public:
	enum {
		c_LOCATIONS_NUM = 29 ///< [AI] Maximum number of spawn locations. [AI]
	};

	enum {
		c_spawnBit1 = 0x01,  ///< [AI] Bit flag to trigger additional camera/animation sequence during spawn. [AI]
		c_playMusic = 0x02,  ///< [AI] Bit flag to trigger background music playback on spawn. [AI]
		c_spawnBit3 = 0x04   ///< [AI] Unused/reserved extra spawn bit in flag set. [AI]
	};

	/**
	 * @brief Information for each player spawn location on LEGO Island. [AI]
	 * @details [AI] This struct aggregates all information required for spawning the player character at a specific
	 * location: area identifier, script linkage, entity association, visual/logic identifiers, scale, world location token,
	 * and music to trigger on arrival.
	 */
	struct SpawnLocation {
		/// @brief [AI] Default constructor.
		SpawnLocation() {}

		/**
		 * @brief [AI] Initializes a SpawnLocation with full data for area, entity, transform and music.
		 * @param p_area [AI] The in-game area enumeration for the spawn.
		 * @param p_script [AI] The script AtomId that defines further logic for the spawn.
		 * @param p_entityId [AI] Internal entity id tied to this spawn.
		 * @param p_name [AI] Name identifier of the spawn point.
		 * @param p_src [AI] Source index or transform token for placing the actor.
		 * @param p_srcScale [AI] Placement scaling value for the source point.
		 * @param p_dest [AI] Destination index for additional placement behavior.
		 * @param p_destScale [AI] Placement scaling for the destination.
		 * @param p_location [AI] Optional location mask or trigger for special-casing spawn handling.
		 * @param p_music [AI] Jukebox script enum specifying music to play on this spawn.
		 */
		SpawnLocation(
			LegoGameState::Area p_area,
			MxAtomId* p_script,
			MxS32 p_entityId,
			const char* p_name,
			MxS16 p_src,
			float p_srcScale,
			MxS16 p_dest,
			float p_destScale,
			MxU32 p_location,
			JukeboxScript::Script p_music
		)
		{
			m_area = p_area;
			m_script = p_script;
			m_entityId = p_entityId;
			strcpy(m_name, p_name);
			m_src = p_src;
			m_srcScale = p_srcScale;
			m_dest = p_dest;
			m_destScale = p_destScale;
			m_location = p_location;
			m_music = p_music;
		}

		/**
		 * @brief [AI] Assignment operator, deep copies fields (including string buffer). [AI]
		 * @param p_location [AI] The source to copy.
		 * @return Reference to this.
		 */
		SpawnLocation& operator=(const SpawnLocation& p_location)
		{
			m_area = p_location.m_area;
			m_script = p_location.m_script;
			m_entityId = p_location.m_entityId;
			strcpy(m_name, p_location.m_name);
			m_src = p_location.m_src;
			m_srcScale = p_location.m_srcScale;
			m_dest = p_location.m_dest;
			m_destScale = p_location.m_destScale;
			m_location = p_location.m_location;
			m_music = p_location.m_music;
			return *this;
		}

		LegoGameState::Area m_area;    ///< [AI] Which overall map are the spawn is located in. [AI]
		MxAtomId* m_script;            ///< [AI] Pointer to the atom id of the script associated with this location. [AI]
		MxS32 m_entityId;              ///< [AI] Entity id used by world placement. [AI]
		char m_name[20];               ///< [AI] String identifier of this spawn (safe up to 19 chars, zero-terminated). [AI]
		MxS16 m_src;                   ///< [AI] Integer for input boundary or index at the source. [AI]
		float m_srcScale;              ///< [AI] Fractional scale for placement at the source. [AI]
		MxS16 m_dest;                  ///< [AI] Destination boundary/index. [AI]
		float m_destScale;             ///< [AI] Fractional scale for placement at the destination. [AI]
		MxU32 m_location;              ///< [AI] Optional location code (used for certain logic branches or animation). [AI]
		JukeboxScript::Script m_music; ///< [AI] What music Jukebox Script enum to play on spawn. [AI]
	};

	/**
	 * @brief [AI] Constructs a new IslePathActor and resets its world state. [AI]
	 */
	IslePathActor();

	/**
	 * @brief [AI] Handles a click event for interaction with this actor. [AI]
	 * @return Always 0 (not handled here, placeholder). [AI]
	 */
	virtual MxLong HandleClick() { return 0; } // vtable+0xcc

	/**
	 * @brief [AI] Handles custom notification type 0 for this actor. [AI]
	 * @return Always 0 (not handled here). [AI]
	 */
	virtual MxLong HandleNotification0() { return 0; } // vtable+0xd0

	/**
	 * @brief [AI] Handles in-game player controls notifications for this actor. [AI]
	 * @param param [AI] The control notification info.
	 * @return Always 0 (no direct handling in base implementation). [AI]
	 */
	virtual MxLong HandleControl(LegoControlManagerNotificationParam&) { return 0; } // vtable+0xd4

	/**
	 * @brief [AI] Handles end-of-animation notifications for this actor. [AI]
	 * @param param [AI] End animation notification parameter.
	 * @return Always 0 (no direct handling in base implementation). [AI]
	 */
	virtual MxLong HandleEndAnim(LegoEndAnimNotificationParam&) { return 0; } // vtable+0xd8

	/**
	 * @brief [AI] Handles structure/path-related notifications for this actor. [AI]
	 * @param param [AI] Path structure notification parameter.
	 * @return Always 0 (no direct handling in base implementation). [AI]
	 */
	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) { return 0; } // vtable+0xdc

	/**
	 * @brief [AI] Called when the actor is made active in a new area or context, setting navigation and visibility state. [AI]
	 */
	virtual void Enter();                                                                        

	/**
	 * @brief [AI] Called when the actor is deactivated or moved out of player control, restoring previous actor if available. [AI]
	 */
	virtual void Exit();                                                                         

	/**
	 * @brief [AI] Spawns the player in a specific area/location, potentially triggering music and animation.
	 * @param p_area [AI] Target area to spawn in.
	 * @param p_enter [AI] If TRUE, automatically enters control context (calls Enter()).
	 * @param p_flags [AI] Bitmask: c_spawnBit1, c_playMusic, c_spawnBit3 for extra behaviors.
	 */
	virtual void SpawnPlayer(LegoGameState::Area p_area, MxBool p_enter, MxU8 p_flags);          

	/**
	 * @brief [AI] Places this actor in the current world with a given transformation, resets input if requested.
	 * @param p_transform [AI] Transformation matrix to apply to the ROI.
	 * @param p_boundary [AI] Path boundary to add actor to.
	 * @param p_reset [AI] If TRUE, calls Enter() after placement.
	 */
	virtual void VTable0xec(MxMatrix p_transform, LegoPathBoundary* p_boundary, MxBool p_reset); 

	/**
	 * @brief [AI] Destructor; performs resource cleanup by delegating to Destroy(TRUE). [AI]
	 * @param none [AI]
	 */
	~IslePathActor() override { IslePathActor::Destroy(TRUE); }

	/**
	 * @brief [AI] Dispatches notifications to specialized handlers based on notification type.
	 * @param p_param [AI] The parameter object, usually a derived MxNotificationParam.
	 * @details [AI] Handles notification types: click, control, end animation, path struct, and type 0.
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief [AI] Get class name string for RTTI/comparison.
	 * @return Pointer to static string "IslePathActor".
	 */
	const char* ClassName() const override
	{
		return "IslePathActor";
	}

	/**
	 * @brief [AI] Checks if class or any superclass matches the given type string.
	 * @param p_name [AI] Name to check for RTTI-style comparison.
	 * @return TRUE if this class or a superclass matches.
	 */
	MxBool IsA(const char* p_name) const override
	{
		return !strcmp(p_name, IslePathActor::ClassName()) || LegoPathActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Initialize this actor from a DSAction. [AI]
	 * @param p_dsAction [AI] The data source action for initialization.
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Cleans up the actor and associated resources. [AI]
	 * @param p_fromDestructor [AI] Is this called from destructor.
	 */
	void Destroy(MxBool p_fromDestructor) override;

	/**
	 * @brief [AI] Synchronizes the actor's world transformation and ROI. [AI]
	 * @details [AI] Updates transformation based on current ROI, direction, and up vectors.
	 */
	void FUN_1001b660();

	/**
	 * @brief [AI] Sets the current world this actor belongs to, updating its reference for placement. [AI]
	 * @param p_world [AI] Pointer to the LegoWorld to assign.
	 */
	void SetWorld(LegoWorld* p_world) { m_world = p_world; }

	/**
	 * @brief [AI] Static: Registers all known player spawn locations into the global location table. [AI]
	 * @details [AI] Populates global static array with SpawnLocation data for later lookup.
	 */
	static void RegisterSpawnLocations();

	// SYNTHETIC: LEGO1 0x10002ff0
	// IslePathActor::`scalar deleting destructor'

protected:
	LegoWorld* m_world;             ///< [AI] Pointer to the current world instance actor is existing in. [AI]
	LegoPathActor* m_previousActor; ///< [AI] The last active path actor before this one; for restoration after exit. [AI]
	MxFloat m_previousVel;          ///< [AI] Stores previous navigation velocity for actor/handoffs. [AI]
};

#endif // ISLEPATHACTOR_H
