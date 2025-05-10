#ifndef ISLE_H
#define ISLE_H

#include "actionsfwd.h"
#include "legogamestate.h"
#include "legonamedplane.h"
#include "legostate.h"
#include "legoworld.h"
#include "radio.h"

class Ambulance;
class Bike;
class DuneBuggy;
class Helicopter;
class Jetski;
class JukeBoxEntity;
class LegoNamedTexture;
class Motocycle;
class LegoPathStructNotificationParam;
class Pizza;
class Pizzeria;
class RaceCar;
class SkateBoard;
class TowTrack;

/// @class Act1State
/// @brief [AI] Holds state and transient gameplay data for the first act on Lego Island. Manages elevator floor logic, cutscene dialogue cycling, and serialization of all vehicle/named planes for state restoration. Closely tied to "Isle" and used per-"Act" state management.
/// @details [AI] Responsible for saving/loading the locations and statuses of various actors/vehicles during Act 1, as well as for session gameplay variables such as which elevator floor is active and which cutscene dialogue is being played.
class Act1State : public LegoState {
public:
	/// @brief [AI] Floor numbers for the info center elevator.
	enum ElevatorFloor {
		c_floor1 = 1, ///< [AI] 1st floor
		c_floor2,     ///< [AI] 2nd floor
		c_floor3      ///< [AI] 3rd floor
	};

	/// @brief [AI] Constructs a new instance and resets default state, including initializing cutscene playlist and vehicle pointers. [AI]
	Act1State();

	/// @brief [AI] Returns class name as string literal for run-time type checking. [AI]
	const char* ClassName() const override; // vtable+0x0c

	/// @brief [AI] Returns whether the provided name matches this class or a parent class.
	/// @param p_name [AI] Name of the class to check against.
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/// @brief [AI] Resets all internal state, including planes, pointers, vehicle flags, and clears dynamic memory for re-use or unload. [AI]
	MxBool Reset() override;

	/// @brief [AI] Serializes all vehicle/named plane and other gameplay state to/from given persistent storage.
	/// @param p_storage [AI] Persistent storage object to serialize to (write mode) or from (read mode).
	MxResult Serialize(LegoStorage* p_storage) override;

	/// @brief [AI] Starts the "Captain Click" dialogue cutscene/playlist with audio and triggers background music fade. [AI]
	void PlayCptClickDialogue();

	/// @brief [AI] Stops the "Captain Click" dialogue cutscene if playing and resets background music. [AI]
	void StopCptClickDialogue();

	/// @brief [AI] Serializes all current actor locations and status, disassociating them from the world for later restoration. [AI]
	void RemoveActors();

	/// @brief [AI] Places all actors/vehicles in the world at their previously-serialized locations and attaches them to the world. [AI]
	void PlaceActors();

	/// @brief [AI] Retrieves the internal state variable at offset 0x018 (purpose: current major state, e.g. current minigame/spot)
	MxU32 GetUnknown18() { return m_unk0x018; }

	/// @brief [AI] Retrieves the current elevator floor the player is on, as an enum. [AI]
	ElevatorFloor GetElevatorFloor() { return (ElevatorFloor) m_elevFloor; }

	/// @brief [AI] Returns the internal state variable at 0x021 (unknown, seems to control transitions).
	MxU8 GetUnknown21() { return m_unk0x021; }

	/// @brief [AI] Sets the gameplay progress variable at 0x018 (controls state transitions, gameplay mode changes, e.g. minigames).
	void SetUnknown18(MxU32 p_unk0x18) { m_unk0x018 = p_unk0x18; }

	/// @brief [AI] Sets the current elevator floor the player is on.
	void SetElevatorFloor(ElevatorFloor p_elevFloor) { m_elevFloor = p_elevFloor; }

	/// @brief [AI] Sets the state flag at offset 0x021 (purpose: controls certain transitions and checks).
	void SetUnknown21(MxU8 p_unk0x21) { m_unk0x021 = p_unk0x21; }

	/// @brief [AI] Playlist object which cycles and holds available "Captain Click" audio scripts for the info center.
	Playlist m_cptClickDialogue;                  // 0x008

	/// @brief [AI] Currently playing island script for the cutscene/voiceover event initiated by Captain Click.
	IsleScript::Script m_currentCptClickDialogue; // 0x014

	/// @brief [AI] Internal gameplay state variable; see Get/SetUnknown18 for usage. [AI]
	MxU32 m_unk0x018;                             // 0x018

	/// @brief [AI] Current floor of the elevator, using enum ElevatorFloor.
	MxS16 m_elevFloor;                            // 0x01c

	/// @brief [AI] Temporary flag for info center elevator; used to determine if elevator is currently active/transitioning. [AI]
	MxBool m_unk0x01e;                            // 0x01e

	/// @brief [AI] Temporary flag for info center elevator; often used as a "ready for transition" check. [AI]
	MxBool m_unk0x01f;                            // 0x01f

	/// @brief [AI] Indicates that the airplane cutscene is currently active (info center window). [AI]
	MxBool m_planeActive;                         // 0x020

	/// @brief [AI] Internal state/transition flag, possibly for initializing/handling world entry. [AI]
	undefined m_unk0x021;                         // 0x021

	/// @brief [AI] Temporary state variable; persists through serialization, often used for logic gating. [AI]
	MxBool m_unk0x022;                            // 0x022

	/// @brief [AI] State variable for plane/channel transitions; exact meaning unknown. [AI]
	undefined m_unk0x023;                         // 0x023

	/// @brief [AI] Serialized/deserialized world placement state for motorcycle.
	LegoNamedPlane m_motocyclePlane;              // 0x024

	/// @brief [AI] Serialized/deserialized world placement state for bike.
	LegoNamedPlane m_bikePlane;                   // 0x070

	/// @brief [AI] Serialized/deserialized world placement state for skateboard.
	LegoNamedPlane m_skateboardPlane;             // 0x0bc

	/// @brief [AI] Serialized/deserialized world placement state for helicopter.
	LegoNamedPlane m_helicopterPlane;             // 0x108

	/// @brief [AI] Named texture for helicopter windshield (needed for state restoration, texture streaming). [AI]
	LegoNamedTexture* m_helicopterWindshield;     // 0x154

	/// @brief [AI] Named texture for left jet on helicopter (needed for restoration/streaming). [AI]
	LegoNamedTexture* m_helicopterJetLeft;        // 0x158

	/// @brief [AI] Named texture for right jet on helicopter (needed for restoration/streaming). [AI]
	LegoNamedTexture* m_helicopterJetRight;       // 0x15c

	/// @brief [AI] Serializable pointer to current helicopter object (NULL when not held in state). [AI]
	Helicopter* m_helicopter;                     // 0x160

	/// @brief [AI] Placement state for jetski in world (serializable). [AI]
	LegoNamedPlane m_jetskiPlane;                 // 0x164

	/// @brief [AI] Named texture for jetski front (state restoration, streaming). [AI]
	LegoNamedTexture* m_jetskiFront;              // 0x1b0

	/// @brief [AI] Named texture for jetski windshield (state restoration, streaming). [AI]
	LegoNamedTexture* m_jetskiWindshield;         // 0x1b4

	/// @brief [AI] Serializable pointer to current jetski object (NULL when not held in state). [AI]
	Jetski* m_jetski;                             // 0x1b8

	/// @brief [AI] Placement state for dune buggy in world (serializable). [AI]
	LegoNamedPlane m_dunebuggyPlane;              // 0x1bc

	/// @brief [AI] Named texture for dune buggy front (state restoration, streaming). [AI]
	LegoNamedTexture* m_dunebuggyFront;           // 0x208

	/// @brief [AI] Serializable pointer to current dune buggy object (NULL when not held in state). [AI]
	DuneBuggy* m_dunebuggy;                       // 0x20c

	/// @brief [AI] Placement state for racecar in world (serializable). [AI]
	LegoNamedPlane m_racecarPlane;                // 0x210

	/// @brief [AI] Named texture for racecar front (state restoration, streaming). [AI]
	LegoNamedTexture* m_racecarFront;             // 0x25c

	/// @brief [AI] Named texture for racecar back (state restoration, streaming). [AI]
	LegoNamedTexture* m_racecarBack;              // 0x260

	/// @brief [AI] Named texture for racecar tail (state restoration, streaming). [AI]
	LegoNamedTexture* m_racecarTail;              // 0x264

	/// @brief [AI] Serializable pointer to current racecar object (NULL when not held in state). [AI]
	RaceCar* m_racecar;                           // 0x268
};

/// @class Isle
/// @brief [AI] Represents the main overworld (LEGO Island) in the game, acting as the central hub and state machine for act transitions, minigames, elevators, mouse input, and audio/trigger/dialogue management. Derived from LegoWorld. [AI]
/// @details [AI] Holds all pointers to world-placed vehicles, audio systems, state transitions. Handles notifications, transitions, cutscenes, and state loading for entire "island" world.
class Isle : public LegoWorld {
public:
	/// @brief [AI] Bitmask options controlling various world behaviors.
	enum {
		c_playCamAnims = 0x20,///< [AI] If set, enables camera animation sequences.
		c_playMusic = 0x40    ///< [AI] If set, background music plays.
	};

	/// @brief [AI] Creates a new Isle world, initializing all vehicle pointers, radio, and registering for notifications.
	Isle();

	/// @brief [AI] Cleans up Isle world, unregistering notifications and releasing allocated resources/pointer state. [AI]
	~Isle() override;

	/// @brief [AI] Handles incoming notifications from various event sources, dispatches to specialized handlers where required. [AI]
	/// @param p_param [AI] Parameter containing notification event and data.
	MxLong Notify(MxParam& p_param) override;

	/// @brief [AI] Returns TRUE, marks Isle as valid for 0x5c world-table vtable slot (possibly is-player-world check).
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// @brief [AI] Returns class name as string literal for RTTI.
	const char* ClassName() const override;

	/// @brief [AI] Returns whether this or a base class matches the string argument.
	/// @param p_name [AI] Name of class to check against.
	MxBool IsA(const char* p_name) const override;

	/// @brief [AI] Sets up the Isle world based on the given MxDSAction (content/scene/act loading entry). Registers input, resets palette, loads act state.
	/// @param p_dsAction [AI] Action reference for initializing world (e.g., loaded script/scene).
	MxResult Create(MxDSAction& p_dsAction) override;

	/// @brief [AI] Prepares the world for play, switching areas if needed and handling music, cutscene, and actor restoration.
	void ReadyWorld() override;

	/// @brief [AI] Adds an object/actor to the Isle world, binding pointers for special-cased vehicles or entities.
	/// @param p_object [AI] Object (vehicle, character, etc.) to add to the world.
	void Add(MxCore* p_object) override;

	/// @brief [AI] Stub function slot; no operation in current implementation. [AI]
	void VTable0x60() override;

	/// @brief [AI] Handles exiting from this world (Escape key, area transition, etc.). Manages background audio/scene/actor deactivation.
	MxBool Escape() override;

	/// @brief [AI] Enables or disables Isle world objects/logic, forcibly setting input and world activation status, and (re)placing actors as needed.
	/// @param p_enable [AI] TRUE to enable world and initialize, FALSE to disable/reset world.
	void Enable(MxBool p_enable) override;

	/// @brief [AI] Removes a path-based actor (vehicle, etc.) from the Isle world and unbinds pointers as needed.
	/// @param p_actor [AI] Actor to remove from world and pointer table.
	virtual void VTable0x6c(LegoPathActor* p_actor);

	/// @brief [AI] Sets destination location for world transitions (are used after certain cutscenes/buttons).
	/// @param p_destLocation [AI] The next intended world/area to transition to.
	void SetDestLocation(LegoGameState::Area p_destLocation) { m_destLocation = p_destLocation; }

	/// @brief [AI] Returns TRUE if the helicopter is currently present and assigned in this world.
	MxBool HasHelicopter() { return m_helicopter != NULL; }

	/// @brief [AI] Performs world cleanup related to transitions and resets (see source for transition/actor logic).
	void FUN_10033350();

	friend class Act1State;

protected:
	/// @brief [AI] Processes notifications marking the end of actions (animations, audio, transitions), dispatches handling for major sub-states (e.g. ambulance, pizza, radio).
	/// @param p_param [AI] Notification parameter describing the finished action.
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/// @brief [AI] Processes control notifications (e.g., elevator, arrow buttons, environment toggles), calling appropriate actions and state transitions.
	/// @param p_param [AI] Notification parameter for control operation.
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);

	/// @brief [AI] Dispatches Lego path structure notifications (actor/path region completed, unique triggers) to vehicles/entities, triggering animations as needed.
	/// @param p_param [AI] Path struct notification param (contains data ID for case switches).
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);

	/// @brief [AI] Handles transitions for all destination logic (scene swaps with audio/video cut, cursor, user actor restoration, post-transition event logic).
	MxLong HandleTransitionEnd();

	/// @brief [AI] Handles the completion of elevator actions, progressing the game/area as appropriate for the current floor.
	void HandleElevatorEndAction();

	/// @brief [AI] Updates the globe UI in the observation area, enabling the correct presenter's bitmap representing the current sun position.
	void UpdateGlobe();

	/// @brief [AI] Internal utility to setup camera/actor state after some transitions (e.g., resets view and spawns appropriate IslePathActor in race/exterior spots).
	void FUN_10032620();

	/// @brief [AI] Reinstantiates/reset the play state in all child objects (radio, vehicles, pizzeria, etc.) and recreates missing Act1State if needed.
	void CreateState();

	/// @brief [AI] Facilitates transitions with visual and audio state, camera positioning and palette reset for the given script/music/camera area.
	/// @param p_script [AI] Script to invoke for cutscene/transition.
	/// @param p_music [AI] Music to play for the transition.
	/// @param p_cameraLocation [AI] Camera string for positioning (may be NULL).
	/// @param p_und [AI] TRUE to reset camera to world default, FALSE for explicit transition.
	void FUN_10032d30(
		IsleScript::Script p_script,
		JukeboxScript::Script p_music,
		const char* p_cameraLocation,
		MxBool p_und
	);

	/// @brief [AI] Points to active Act1State, holding currently serialized vehicle and gameplay data.
	Act1State* m_act1state;             // 0xf8

	/// @brief [AI] Pointer to pizza actor.
	Pizza* m_pizza;                     // 0xfc

	/// @brief [AI] Pointer to pizzeria scene.
	Pizzeria* m_pizzeria;               // 0x100

	/// @brief [AI] Pointer to tow track actor.
	TowTrack* m_towtrack;               // 0x104

	/// @brief [AI] Pointer to ambulance actor.
	Ambulance* m_ambulance;             // 0x108

	/// @brief [AI] Pointer to in-world jukebox entity.
	JukeBoxEntity* m_jukebox;           // 0x10c

	/// @brief [AI] Pointer to helicopter actor (if present).
	Helicopter* m_helicopter;           // 0x110

	/// @brief [AI] Pointer to bike actor.
	Bike* m_bike;                       // 0x114

	/// @brief [AI] Pointer to dune buggy actor.
	DuneBuggy* m_dunebuggy;             // 0x118

	/// @brief [AI] Pointer to motorcycle actor.
	Motocycle* m_motocycle;             // 0x11c

	/// @brief [AI] Pointer to skateboard actor.
	SkateBoard* m_skateboard;           // 0x120

	/// @brief [AI] Pointer to racecar actor.
	RaceCar* m_racecar;                 // 0x124

	/// @brief [AI] Pointer to jetski actor.
	Jetski* m_jetski;                   // 0x128

	/// @brief [AI] In-world radio/audio playback manager.
	Radio m_radio;                      // 0x12c

	/// @brief [AI] Next requested world/area to transition to after animation/dialogue/cutscene currently in progress.
	LegoGameState::Area m_destLocation; // 0x13c
};

#endif // ISLE_H