#ifndef ACT2ACTOR_H
#define ACT2ACTOR_H

#include "legoanimactor.h"

// VTABLE: LEGO1 0x100d6078 LegoPathActor
// VTABLE: LEGO1 0x100d6148 LegoAnimActor
// VTABLE: BETA10 0x101b80c0 LegoPathActor
// VTABLE: BETA10 0x101b81b0 LegoAnimActor
// SIZE 0x1a8

/**
 * @brief [AI] Act2 mission-specific actor class, with custom state and animation handling for Act 2 of the story mode. [AI]
 * @details [AI] Act2Actor is a specialized subclass of LegoAnimActor used for the story segment "Act 2" in LEGO Island. 
 * It adds fields and logic for interacting with escapee plants/buildings, triggering story progress, and custom animation/audio logic.
 */
class Act2Actor : public LegoAnimActor {
public:

	/**
	 * @brief [AI] Encapsulates the positional and directional data for potential target locations in the Act 2 sequence. [AI]
	 * @details [AI] Used to define the starting position, orientation, and boundary (path) for spawned/destructible objects during this segment. [AI]
	 */
	struct Location {
		MxFloat m_position[3];  ///< [AI] 3D world position for the location (x, y, z). [AI]
		MxFloat m_direction[3]; ///< [AI] Forward direction vector for the location. [AI]
		const char* m_boundary; ///< [AI] Name of the path boundary or area associated (for motion/pathing). [AI]
		MxBool m_unk0x1c;       ///< [AI] Used to track whether a location has been previously used/marked. [AI]
	};

	/**
	 * @brief [AI] Constructs an Act2Actor and initializes all mission-related state. [AI]
	 */
	Act2Actor();

	/**
	 * @brief [AI] Sets the ROI (rendered object instance) for this actor and disables its visibility immediately. [AI]
	 * @param p_roi The new ROI to associate with this actor. [AI]
	 * @param p_bool1 First base parameter, passed to LegoAnimActor::SetROI. [AI]
	 * @param p_bool2 Second base parameter, passed to LegoAnimActor::SetROI. [AI]
	 */
	void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2) override; // vtable+0x24

	/**
	 * @brief [AI] Sets the "world speed" (movement, animation, or activity speed) for the actor and resets speed timer. [AI]
	 * @param p_worldSpeed New speed to apply. [AI]
	 */
	void SetWorldSpeed(MxFloat p_worldSpeed) override; // vtable+0x30

	/**
	 * @brief [AI] Handles a virtual motion logic interaction, but disables base behavior if actor is in 'inactive' state. [AI]
	 * @param p_v1 First input vector (purpose per base class). [AI]
	 * @param p_v2 Second input vector. [AI]
	 * @param p_v3 Third input vector. [AI]
	 * @return 0 if actor is in an inactive state, otherwise result from LegoAnimActor. [AI]
	 */
	MxS32 VTable0x68(Vector3& p_v1, Vector3& p_v2, Vector3& p_v3) override; // vtable+0x68

	/**
	 * @brief [AI] Orchestrates all Act2-specific animation logic and state switching each tick. [AI]
	 * @param p_time Absolute, game-time timestamp for the tick. [AI]
	 * @details [AI] Manages mission progression, detection of interactions with the player (Pepper), destruction triggers, and special effects. [AI]
	 */
	void Animate(float p_time) override; // vtable+0x70

	/**
	 * @brief [AI] Handles being "hit" by another actor—used to trigger mission state transitions, mark as finished/destroyed, and play SFX. [AI]
	 * @param SecondActor The actor responsible (e.g., player or projectile). [AI]
	 * @param IsProjectile True if interaction is with a projectile, otherwise false. [AI]
	 * @return Result of handling, typically SUCCESS if interaction accepted. [AI]
	 */
	MxResult HitActor(LegoPathActor*, MxBool) override; // vtable+0x94

	/**
	 * @brief [AI] Handles per-frame mission resolution, cleanup, or ending logic for the Act2Actor. [AI]
	 * @return Result status: may trigger further mission events or actor deletion. [AI]
	 */
	MxResult VTable0x9c() override; // vtable+0x9c

	/**
	 * @brief [AI] Selects and moves the actor to a new random, valid mission location. [AI]
	 * @return Indicates if a valid relocation target was found and update was performed. [AI]
	 */
	MxS32 VTable0xa0() override; // vtable+0xa0

	/**
	 * @brief [AI] Searches animation maps for a "shoot" animation, and prepares the mission audio effect. [AI]
	 * @details [AI] Must be called during initialization/mission start. [AI]
	 */
	void FUN_10018980();

	/**
	 * @brief [AI] Sets current speed and schedules a timed speed change for mission event purposes. [AI]
	 * @param p_speed New speed to set. [AI]
	 * @param p_param2 Time (absolute value) after which speed changes again. [AI]
	 */
	void FUN_10019250(MxFloat p_speed, MxFloat p_param2);

	/**
	 * @brief [AI] Triggers major mission state transition: switches to "escape" mode and moves to special location 10. [AI]
	 * @details [AI] Used for handling Act 2 ending consequences or special cutscene triggers. [AI]
	 */
	void FUN_10019520();

	/**
	 * @brief [AI] Triggers mission state transition: switches to "destroyed" mode and moves to special location 9. [AI]
	 */
	void FUN_10019560();

	/**
	 * @brief [AI] Handles main shoot animation event and plant/building destruction, manages associated SFX and mission logic. [AI]
	 * @param p_param Current animation/game time in ms. [AI]
	 * @return TRUE if no target is left to destroy, otherwise FALSE. [AI]
	 */
	MxU32 FUN_10019700(MxFloat p_param);

	/**
	 * @brief [AI] Plays a specific voice-over cue depending on context and mission state. [AI]
	 * @param p_param Selector for which voice type to trigger (head, behind, interrupt). [AI]
	 */
	void FUN_100199f0(MxS8 p_param);

	/**
	 * @brief [AI] Relocates actor to a selected location by generating a path container for new destination. [AI]
	 * @param p_location Index of the location to jump/move to. [AI]
	 */
	void FUN_100192a0(undefined4 p_location);

	/**
	 * @brief [AI] Searches for the next building or plant entity to destroy for mission progression at current location. [AI]
	 * @param p_param Out parameter: TRUE if next target is a building, FALSE if plant. [AI]
	 * @return Pointer to the next LegoEntity to destroy, or nullptr if none left. [AI]
	 */
	LegoEntity* FUN_10019b90(MxBool* p_param);

	// SYNTHETIC: LEGO1 0x1001a0a0
	// Act2Actor::`scalar deleting destructor'

	// GLOBAL: LEGO1 0x100d6070
	// GLOBAL: BETA10 0x101b80b0
	// `vbtable'

private:
	/**
	 * @brief [AI] Miscellaneous per-actor state variable. Used as a flag for proximity/interaction logic. [AI]
	 */
	undefined m_unk0x1c;              // 0x1c

	/**
	 * @brief [AI] Current location index (0-8), used to choose which scenario/location the actor is managing. [AI]
	 */
	MxS8 m_unk0x1d;                   // 0x1d

	/**
	 * @brief [AI] Current state of Act2Actor's mission script (0=normal, 1=waiting, 2=shoot sequence, 3=outro/cutscene, etc.). [AI]
	 */
	undefined m_unk0x1e;              // 0x1e

	/**
	 * @brief [AI] Flag marking if actor is currently in transition/disabled after being hit or destroyed. [AI]
	 */
	MxBool m_unk0x1f;                 // 0x1f

	/**
	 * @brief [AI] Timer used to track duration since last state transition (e.g., since being hit or destroyed). [AI]
	 */
	MxFloat m_unk0x20;                // 0x20

	/**
	 * @brief [AI] Timestamp for latest mission event (last hit, movement advance, etc). [AI]
	 */
	MxFloat m_unk0x24;                // 0x24

	/**
	 * @brief [AI] Tracks how many targets at this location have been used/nullified. Unlocks final scenario if at threshold. [AI]
	 */
	MxS8 m_unk0x28;                   // 0x28

	/**
	 * @brief [AI] Absolute time when the current shoot/destroy sequence finishes. [AI]
	 */
	MxFloat m_unk0x2c;                // 0x2c

	/**
	 * @brief [AI] Absolute time when to start destruction sound effect/animation of target ("windshield/rear" etc). [AI]
	 */
	MxFloat m_unk0x30;                // 0x30

	/**
	 * @brief [AI] Pointer to animation data structure for the shoot/destruction event. [AI]
	 */
	LegoAnimActorStruct* m_shootAnim; // 0x34

	/**
	 * @brief [AI] Cached pointer to a relevant destruction sound effect, loaded by animation or cutscene. [AI]
	 */
	LegoCacheSound* m_unk0x38;        // 0x38

	/**
	 * @brief [AI] Miscellaneous state data (potential structure for overlays, cutscene triggers, or camera targets). [AI]
	 */
	undefined4 m_unk0x3c;             // 0x3c

	/**
	 * @brief [AI] Boolean—Set to 1 during the first update, resets special sequence variables after animation. [AI]
	 */
	undefined m_unk0x40;              // 0x40

	/**
	 * @brief [AI] Next absolute time when the actor's world speed should be changed, or 0 for no scheduled change. [AI]
	 */
	MxFloat m_unk0x44;                // 0x44

	/**
	 * @brief [AI] Counter, incremented when locations are exhausted. Used to trigger escape/finale. [AI]
	 */
	MxS8 m_unk0x48;                   // 0x48

	/**
	 * @brief [AI] Pointer to the target building/plant entity currently being destroyed (nullptr if none left). [AI]
	 */
	LegoEntity* m_unk0x4c;            // 0x4c
};

// TEMPLATE: LEGO1 0x100194f0
// list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >::list<LegoBoundaryEdge,allocator<LegoBoundaryEdge> >

#endif // ACT2ACTOR_H