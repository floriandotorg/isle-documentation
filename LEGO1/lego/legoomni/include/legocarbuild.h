#ifndef LEGOCARBUILD_H
#define LEGOCARBUILD_H

#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "mxgeometry/mxquaternion.h"

class LegoCarBuildAnimPresenter;
class LegoControlManagerNotificationParam;
class LegoEventNotificationParam;
class MxControlPresenter;
class MxStillPresenter;
class MxSoundPresenter;
class MxActionNotificationParam;

// VTABLE: LEGO1 0x100d66e0
// VTABLE: BETA10 0x101bb910
// SIZE 0x50
/**
 * @brief [AI] Represents the persistent state of the LEGO vehicle build world, tracking animation and part placement state. Used for all build subtypes (car, copter, dune car, jetski).
 * @details [AI] Derived from LegoState, this class maintains the class name, current animation state, flags, and number of parts placed. The class also serializes build progress and animation.
 */
class LegoVehicleBuildState : public LegoState {
public:
	/**
	 * @brief [AI] Enumerates the possible animation states for the build process.
	 */
	enum AnimationState {
		e_unknown0 = 0,   ///< [AI] Default/uninitialized state. Meaning unclear.
		e_entering = 1,   ///< [AI] Transition/Entering the build area.
		e_unknown2 = 2,   ///< [AI] Likely a 'ready' or transitional state before a cutscene.
		e_cutscene = 3,   ///< [AI] Indicates that the build is in a cutscene (camera or instructions animation).
		e_unknown4 = 4,   ///< [AI] Indicates transition to exit (possibly ready for world exit or next act).
		e_exiting = 6     ///< [AI] Build area is in the process of ending/exiting.
	};

	/**
	 * @brief [AI] Constructs a LegoVehicleBuildState with a specified class type string, which identifies the build-type (e.g., RaceCar/Copter).
	 * @param p_classType Build state type name ("LegoRaceCarBuildState", "LegoCopterBuildState", etc.) [AI]
	 */
	LegoVehicleBuildState(const char* p_classType);

	/**
	 * @brief [AI] Returns the class name (run-time type string) for this object.
	 * @return const char* Pointer to string of class name. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if the provided type name matches this class or any base class.
	 * @param p_name Class/type name for comparison. [AI]
	 * @return MxBool TRUE if matches, FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Serialize or deserialize the build state to/from a storage object for save/load.
	 * @param p_storage A pointer to the LegoStorage for reading or writing the state. [AI]
	 * @return MxResult Success or failure status. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	Playlist m_unk0x08[4]; ///< [AI] Unused/unknown playlists per build? [AI_SUGGESTED_NAME: m_playlists] Unclear, but likely reserved space for per-vehicle actions or steps.

	/**
	 * @brief [AI] Class name string ("LegoRaceCarBuildState", etc), used for identifying the build state type.
	 */
	MxString m_className; // 0x38

	/**
	 * @brief [AI] Current animation state within the build area.
	 */
	AnimationState m_animationState; // 0x48

	MxU8 m_unk0x4c;                  ///< [AI] Number of completed actions or animation steps, incremented through build progress.
	MxBool m_unk0x4d;                ///< [AI] Persists transition or completion flag across world reloads.
	MxBool m_unk0x4e;                ///< [AI] Unknown. Flag—purpose unclear.
	MxU8 m_placedPartCount;          ///< [AI] Number of parts (bricks) placed during the build.
};

/**
 * @brief [AI] Typedefs to support all vehicle variants using a single base build state class. Do not instantiate these directly, always use LegoVehicleBuildState.
 */
typedef LegoVehicleBuildState LegoRaceCarBuildState;
typedef LegoVehicleBuildState LegoCopterBuildState;
typedef LegoVehicleBuildState LegoDuneCarBuildState;
typedef LegoVehicleBuildState LegoJetskiBuildState;

// VTABLE: LEGO1 0x100d6658
// VTABLE: BETA10 0x101bb880
// SIZE 0x34c
/**
 * @brief [AI] World implementation for the LEGO vehicle builder (Racecar, Copter, Dune Car, Jetski), handling UI, input, 3D vehicle assembly, part placement, and all vehicle-specific interactions.
 * @details [AI] Inherits from LegoWorld. Maintains state about currently manipulated vehicle/part, responds to input (mouse/key/click), handles animation state transitions, manages presenters for vehicle builder UI and sound, and synchronizes with game/area state.
 */
class LegoCarBuild : public LegoWorld {
public:
	/**
	 * @brief [AI] Lookup table for animation/action IDs for vehicle types. Used for mapping actions to the correct per-vehicle scripts.
	 */
	struct LookupTableActions {
		undefined4 m_unk0x00; ///< [AI] Script/action ID for animation 0.
		undefined4 m_unk0x04; ///< [AI] Script/action ID for animation 1.
		undefined4 m_unk0x08; ///< [AI] Script/action ID for animation 2.
		undefined4 m_unk0x0c; ///< [AI] Script/action ID for animation 3.
		undefined4 m_unk0x10; ///< [AI] Script/action ID for animation 4.
		undefined4 m_unk0x14; ///< [AI] Script/action ID for animation 5.
		undefined4 m_unk0x18; ///< [AI] Script/action ID for animation 6.
	};

	/**
	 * @brief [AI] Special constants for internal state tracking of the build world.
	 */
	enum Unknown0xf8 {
		c_unknownminusone = -1, ///< [AI] Default/uninitialized
		c_unknown8 = 8          ///< [AI] Internal marker
	};

	/**
	 * @brief [AI] Constructs a new LegoCarBuild world and initializes all references/UI.
	 */
	LegoCarBuild();

	/**
	 * @brief [AI] Cleans up presenters, unregisters input/notification handlers, and resets world build state.
	 */
	~LegoCarBuild() override;

	/**
	 * @brief [AI] Always returns TRUE; signals that this world can be entered. Used for world transitions.
	 * @return MxBool Always TRUE. [AI]
	 */
	MxBool VTable0x5c() override;

	/**
	 * @brief [AI] Returns the type string for this object.
	 * @return const char* "LegoCarBuild". [AI]
	 */
	const char* ClassName() const override;

	/**
	 * @brief [AI] Handles notifications (input, state, animation, world events) for the build world.
	 * @param p_param Notification/event parameter. [AI]
	 * @return MxLong Result of notification handling. [AI]
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief [AI] Tickle function (called every frame/tick); processes build logic and part animation.
	 * @return MxResult Success or error code. [AI]
	 */
	MxResult Tickle() override;

	/**
	 * @brief [AI] Checks run-time type compatibility.
	 * @param p_name Type/class name to check. [AI]
	 * @return MxBool TRUE if matches, otherwise calls base class. [AI]
	 */
	MxBool IsA(const char* p_name) const override;

	/**
	 * @brief [AI] Creates world from script action; initializes build and assigns state according to area/car type.
	 * @param p_dsAction Data source action with world creation parameters. [AI]
	 * @return MxResult Success (creates world + build state) or failure. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Prepares UI and scripting when world is ready. Introspects audio, shows start animation if enabled.
	 */
	void ReadyWorld() override;

	/**
	 * @brief [AI] Escapes from the build UI (initiates transition to outside world/menu).
	 * @return MxBool TRUE if escape logic ran. [AI]
	 */
	MxBool Escape() override;

	/**
	 * @brief [AI] Enables or disables the world, handling both visual and audio states and input registration.
	 * @param p_enable If TRUE, enable inputs and reset world state; otherwise, cleans up resources. [AI]
	 */
	void Enable(MxBool p_enable) override;

	/**
	 * @brief [AI] Internal logic, used during part drag/drop and animation (possibly for placing or updating a part coordinate).
	 */
	virtual void VTable0x6c();

	/**
	 * @brief [AI] Computes screen-projected coordinates for picking/placing parts and updates internal pixel locations.
	 */
	virtual void VTable0x70();

	/**
	 * @brief [AI] Adjusts transformation for part manipulation based on mouse/drag locations below the "default" part reference.
	 * @param p_param1 2D pixel coordinates array. [AI]
	 * @param p_param2 3D transform delta to be updated. [AI]
	 */
	virtual void VTable0x74(MxFloat p_param1[2], MxFloat p_param2[3]);

	/**
	 * @brief [AI] Adjusts transformation for part manipulation when within the vertical bounds of the reference points.
	 * @param p_param1 2D pixel coordinates array. [AI]
	 * @param p_param2 3D transform delta to be updated. [AI]
	 */
	virtual void VTable0x78(MxFloat p_param1[2], MxFloat p_param2[3]);

	/**
	 * @brief [AI] Adjusts transformation for part manipulation above the "default" reference.
	 * @param p_param1 2D pixel coordinates array. [AI]
	 * @param p_param2 3D transform delta to be updated. [AI]
	 */
	virtual void VTable0x7c(MxFloat p_param1[2], MxFloat p_param2[3]);

	/**
	 * @brief [AI] Used for conversions between projected and real pixel/world space. Applies linear transformation based on part location.
	 * @param p_param1 Source array for calculation. [AI]
	 * @param p_param2 Additional mapping array. [AI]
	 * @param p_param3 Parameter for interpolation or location. [AI]
	 * @param p_param4 Out: Destination array for result. [AI]
	 */
	virtual void VTable0x80(
		MxFloat p_param1[2],
		MxFloat p_param2[2],
		MxFloat p_param3,
		MxFloat p_param4[2]
	);

	/**
	 * @brief [AI] Gets number of parts currently placed in build progress.
	 * @return MxS16 Number of placed parts, or 0 if build state invalid. [AI]
	 */
	MxS16 GetPlacedPartCount();

	/**
	 * @brief [AI] Sets the number of placed parts in the build state.
	 * @param p_placedPartCount New value. [AI]
	 */
	void SetPlacedPartCount(MxU8 p_placedPartCount);

	/**
	 * @brief [AI] Finds and initializes all presenters (UI and sound) used in the car build area.
	 */
	void InitPresenters();

	/**
	 * @brief [AI] Internal: handles transition when moving a placed part, possibly triggering state change.
	 */
	void FUN_10022f00();

	/**
	 * @brief [AI] Internal: logic for finalizing or dropping a part at build location, updates sound and UI.
	 */
	void FUN_10022f30();

	/**
	 * @brief [AI] Internal: handles interaction when dragging part along projected axis.
	 * @param p_x X position in pixels. [AI]
	 * @param p_y Y position in pixels. [AI]
	 */
	void FUN_10023130(MxLong p_x, MxLong p_y);

	/**
	 * @brief [AI] Internal: launches the finalization of all parts if build is completed; triggers further game progression or cutscene.
	 */
	void FUN_100236d0();

	/**
	 * @brief [AI] Handles keyboard event notifications, most notably the Space key for canceling animations or sounds.
	 * @param p_param Keyboard notification parameter. [AI]
	 * @return undefined4 Result code. [AI]
	 */
	undefined4 FUN_10024250(LegoEventNotificationParam* p_param);

	/**
	 * @brief [AI] Handles the transition to the next act/location when building is complete.
	 */
	void FUN_100243a0();

	/**
	 * @brief [AI] Handles animation end notification action (e.g., volume restoration, state reset, triggers exit logic).
	 * @param p_param Action notification parameter. [AI]
	 * @return undefined4 Status/result code. [AI]
	 */
	undefined4 FUN_10024480(MxActionNotificationParam* p_param);

	/**
	 * @brief [AI] Handles mouse click/button down notifications to pick parts or trigger color/decal tools.
	 * @param p_x X position of click. [AI]
	 * @param p_y Y position of click. [AI]
	 * @return undefined4 Status/result code. 1 on part touched, 0 otherwise. [AI]
	 */
	undefined4 FUN_100244e0(MxLong p_x, MxLong p_y);

	/**
	 * @brief [AI] Handles mouse button up events; initiates part-finalization or validated placement.
	 * @param p_x X position of click. [AI]
	 * @param p_y Y position of click. [AI]
	 * @return undefined4 Status/result code. 1 if part dropped/finalized, 0 otherwise. [AI]
	 */
	undefined4 FUN_100246e0(MxLong p_x, MxLong p_y);

	/**
	 * @brief [AI] Handles mouse move notifications for drag-to-place part. Moves the part.
	 * @param p_x X pixel position. [AI]
	 * @param p_y Y pixel position. [AI]
	 * @return MxS32 1 if moved, 0 otherwise. [AI]
	 */
	MxS32 FUN_10024850(MxLong p_x, MxLong p_y);

	/**
	 * @brief [AI] Handles UI input/control presenter notifications.
	 * @param p_param Control/action notification parameter. [AI]
	 * @return undefined4 Always 1. [AI]
	 */
	undefined4 FUN_10024890(MxParam* p_param);

	/**
	 * @brief [AI] Handles the core event when the build is completed and creation should be finalized.
	 * @param p_param Event notification parameter. [AI]
	 * @return undefined4 Status/result code. [AI]
	 */
	undefined4 FUN_10024c20(LegoEventNotificationParam* p_param);

	/**
	 * @brief [AI] Starts the cutscene or music intro for the build with necessary state adjustment.
	 */
	void FUN_10024ef0();

	/**
	 * @brief [AI] Internal: Logic for the shelf-up UI animation/response.
	 */
	void FUN_10024f30();

	/**
	 * @brief [AI] Internal: Handles part rotation/y-axis interaction.
	 */
	void FUN_10024f50();

	/**
	 * @brief [AI] Enables/Disables color/decal presenters depending on selected part and part name.
	 * @param p_enabled Whether to enable (TRUE) or disable (FALSE) applicable presenters. [AI]
	 */
	void FUN_10024f70(MxBool p_enabled);

	/**
	 * @brief [AI] Controls common set of UI presenters' enabled state at once.
	 * @param p_enabled Whether to enable or disable them. [AI]
	 */
	void SetPresentersEnabled(MxBool p_enabled);

	/**
	 * @brief [AI] Toggles enabled/disabled state for all main presenters (color/decal tools).
	 */
	void TogglePresentersEnabled();

	/**
	 * @brief [AI] Enables/Disables only the presenter set related to current part, using name pattern.
	 * @param p_param Determines enable/disable. [AI]
	 */
	void FUN_100250e0(MxBool p_param);

	/**
	 * @brief [AI] Handles color/decal actions by object ID, mapping click to appropriate color or updating variables.
	 * @param p_objectId Identifier of the clicked object. [AI]
	 */
	void FUN_10025350(MxS32 p_objectId);

	/**
	 * @brief [AI] Updates part transformation matrices and records old/new world/projected positions for drag/drop and manip.
	 */
	void FUN_10025450();

	/**
	 * @brief [AI] Initiates the next world/cutscene/animation step, based on internal build progress and car ID.
	 * @param p_param1 Internal state/cutscene ID. [AI]
	 */
	void FUN_10025720(undefined4 p_param1);

	/**
	 * @brief [AI] Starts/stops an animation action for the specified parameter (e.g., cutscene transition, per-action).
	 * @param p_param Animation/cutscene ID. [AI]
	 */
	void FUN_10025d10(MxS32 p_param);

	/**
	 * @brief [AI] Gets next animation/cutscene ID depending on current build stage value.
	 * @return MxS32 Cutscene/animation ID. [AI]
	 */
	MxS32 FUN_10025d70();

	/**
	 * @brief [AI] Controls global UI presentations actions (such as blinking or activation), based on progress in animation.
	 * @param p_param1 Presenter name string/ID. [AI]
	 * @param p_param2 Animation progress delta. [AI]
	 */
	void FUN_10025db0(const char* p_param1, undefined4 p_param2);

	/**
	 * @brief [AI] Re-applies enabled/disabled flags on presenters, resetting the last-toggled presenter if needed.
	 */
	void FUN_10025e40();

	/**
	 * @brief [AI] Gets the appropriate jukebox/music action ID for the current car type, used when leaving the build.
	 * @param p_param1 CarId/vehicle type. [AI]
	 * @return MxS32 Jukebox/music script ID. [AI]
	 */
	MxS32 FUN_10025ee0(undefined4 p_param1);

	/**
	 * @brief [AI] Directly sets the animation presenter for this build world.
	 * @param p_unk0x258 Animation presenter for part actions. [AI]
	 */
	void SetUnknown0x258(LegoCarBuildAnimPresenter* p_unk0x258) { m_unk0x258 = p_unk0x258; }

private:
	/**
	 * @brief [AI] Returns animation lookup index (0-3) depending on car type being built.
	 * @return MxU32 Index into action lookup table. [AI]
	 */
	MxU32 Beta0x10070520();

	/**
	 * @brief [AI] Stops currently running action/animation in m_unk0x344 if active.
	 */
	void StopActionIn0x344();

	Unknown0xf8 m_unk0xf8; ///< [AI] Internal state switch for tickle/animation progress tracking.
	MxS16 m_unk0xfc;       ///< [AI] Animation index or flag for last-started animation.
	MxS32 m_unk0x100;      ///< [AI] Main state switch for build/drag/exit/animation actions.
	undefined4 m_unk0x104; ///< [AI] Not used for build logic—likely a state flag, reserved or internal.

	MxS8 m_numAnimsRun;    ///< [AI] Number of currently active custom animations (notifies when all finished).

	MxU8 m_unk0x109;           ///< [AI] Click count/interaction debounce counter for placing part.
	MxU16 m_unk0x10a;          ///< [AI] Current animation action ID (for running/queued script by type).
	DWORD m_unk0x10c;          ///< [AI] Time that the current animation started.
	LegoROI* m_unk0x110;       ///< [AI] Currently selected or manipulated part's ROI pointer.
	BoundingSphere m_unk0x114; ///< [AI] Last bounding sphere (for intersection testing when dropping part).
	MxMatrix m_unk0x12c;       ///< [AI] Copy of part transformation when picked up.
	undefined m_unk0x174;      ///< [AI] Flag that tracks build completion/act2/etc, passed into buildstate.
	MxMatrix m_unk0x178;       ///< [AI] Working transform for current part (dragged and spatially interpolated).
	MxMatrix m_unk0x1c0;       ///< [AI] Previous or initial transform for transition interpolation.
	MxMatrix m_unk0x208;       ///< [AI] End transform when moving between snap positions on a build.

	MxS32 m_unk0x250[2]; ///< [AI] Last click or part pick-up location in pixel space.

	LegoCarBuildAnimPresenter* m_unk0x258; ///< [AI] Animation presenter for part placement, drag, and feedback.

	MxQuaternionTransformer m_unk0x25c;    ///< [AI] Used for smoothly spinning or moving a part between two states.

	MxS32 m_unk0x290[2]; ///< [AI] Saved/projected pixel location for currently manipulated part.
	MxS32 m_unk0x298[2]; ///< [AI] Saved/projected pixel location for destination/interpolation.

	MxFloat m_unk0x2a0;        ///< [AI] Distance between projected part points (for drag/placement).
	Mx4DPointFloat m_unk0x2a4; ///< [AI] World/projected 4D coordinates for dragged part.
	Mx4DPointFloat m_unk0x2bc; ///< [AI] World/projected 4D coordinates for destination.
	MxBool m_unk0x2d4;         ///< [AI] TRUE if part being dragged is already placed, triggers intersection logic.

	// Main presenters for color/decal tools and feedback

	MxStillPresenter* m_ColorBook_Bitmap; ///< [AI] Main bitmap of the color selection UI.
	MxControlPresenter* m_Yellow_Ctl;     ///< [AI] UI presenter for "yellow" color (control).
	MxControlPresenter* m_Red_Ctl;        ///< [AI] UI presenter for "red" color (control).
	MxControlPresenter* m_Blue_Ctl;       ///< [AI] UI presenter for "blue" color (control).
	MxControlPresenter* m_Green_Ctl;      ///< [AI] UI presenter for "green" color (control).
	MxControlPresenter* m_Gray_Ctl;       ///< [AI] UI presenter for "gray/white" color (control).
	MxControlPresenter* m_Black_Ctl;      ///< [AI] UI presenter for "black" color (control).
	MxSoundPresenter* m_Shelf_Sound;      ///< [AI] Sound presenter for shelf-up action.
	MxSoundPresenter* m_PlaceBrick_Sound; ///< [AI] Sound presenter for placing a brick/part.
	MxSoundPresenter* m_GetBrick_Sound;   ///< [AI] Sound presenter for getting a part.
	MxSoundPresenter* m_Paint_Sound;      ///< [AI] Sound presenter for painting a part.
	MxSoundPresenter* m_Decal_Sound;      ///< [AI] Sound presenter for decal application.
	MxStillPresenter* m_Decal_Bitmap;     ///< [AI] Presenter for the current decal bitmap.
	MxControlPresenter* m_Decals_Ctl;     ///< [AI] UI presenter for first decal set.
	MxControlPresenter* m_Decals_Ctl1;    ///< [AI] UI presenter for decal control 1.
	MxControlPresenter* m_Decals_Ctl2;    ///< [AI] UI presenter for decal control 2.
	MxControlPresenter* m_Decals_Ctl3;    ///< [AI] UI presenter for decal control 3.
	MxControlPresenter* m_Decals_Ctl4;    ///< [AI] UI presenter for decal control 4.
	MxControlPresenter* m_Decals_Ctl5;    ///< [AI] UI presenter for decal control 5.
	MxControlPresenter* m_Decals_Ctl6;    ///< [AI] UI presenter for decal control 6.
	MxControlPresenter* m_Decals_Ctl7;    ///< [AI] UI presenter for decal control 7.

	LegoVehicleBuildState* m_buildState;  ///< [AI] Reference to persistent build state (for this area). Tracks placed parts and which world act/build we're in.

	undefined4 m_carId; ///< [AI] Vehicle type ID (helicopter, dune buggy, jetski, racecar).

	LegoGameState::Area m_destLocation; ///< [AI] The next area to which world transitions after build/cutscene.

	MxPresenter* m_unk0x338;        ///< [AI] Sound/music presenter handle for currently playing music.
	MxControlPresenter* m_unk0x33c; ///< [AI] Recently toggled/activated UI presenter (for blinking or focus).
	undefined4 m_unk0x340;          ///< [AI] Miscellaneous, likely script/cutscene or action in progress.
	undefined4 m_unk0x344;          ///< [AI] Currently active animation action/cutscene/task ID.
	MxU8 m_presentersEnabled;       ///< [AI] State flag for whether presenters/UI controls are enabled.

	/**
	 * @brief [AI] Global static: UI state for ColorBook blinking presenter.
	 */
	static MxS16 g_unk0x100f11cc;

	/**
	 * @brief [AI] Global static: Rotation step for Y-axis rotation in part placement.
	 */
	static MxFloat g_unk0x100d65a4;

	/**
	 * @brief [AI] Global static: Default incremental angle for rotating part around Y axis.
	 */
	static MxFloat g_rotationAngleStepYAxis;

	/**
	 * @brief [AI] Global static: Lookup action table, indexed by vehicle type, in the order (dune, jetski, copter, racecar).
	 */
	static LookupTableActions g_unk0x100d65b0[];
};

#endif // LEGOCARBUILD_H
