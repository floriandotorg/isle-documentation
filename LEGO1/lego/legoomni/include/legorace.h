#ifndef LEGORACE_H
#define LEGORACE_H

#include "decomp.h"
#include "legogamestate.h"
#include "legoraceactor.h"
#include "legoracemap.h"
#include "legostate.h"
#include "legoworld.h"
#include "mxgeometry.h"
#include "mxtypes.h"

class Act1State;
class LegoEventNotificationParam;
class LegoPathActor;
class MxEndActionNotificationParam;
class MxNotificationParam;
class LegoPathStructNotificationParam;

// VTABLE: LEGO1 0x100d5e30
// VTABLE: BETA10 0x101be270
// SIZE 0x2c
/**
 * @brief [AI] Maintains persistent information about race progress, results, and high scores for up to five races. Used as a state class for the race area in LEGO Island. Handles serialization of results and maintains race-specific entries.
 *
 * Inherits from LegoState. [AI]
 */
class RaceState : public LegoState {
public:
	// SIZE 0x06
	/**
	 * @brief [AI] Entry for an individual race event/state, holding its identifier, unknown field, and score.
	 * [AI] Serializes its state to/from a provided LegoStorage backend.
	 */
	struct Entry {
	public:
		/**
		 * @brief [AI] Default constructor that initializes all fields to zero.
		 */
		Entry()
		{
			m_id = 0;
			m_unk0x02 = 0;
			m_score = 0;
		}

		/**
		 * @brief [AI] Gets the unknown 0x02 field associated with this entry.
		 * @return Value of m_unk0x02. [AI]
		 */
		MxS16 GetUnknown0x02() { return m_unk0x02; }

		/**
		 * @brief [AI] Retrieves the race entry's current high score.
		 * @return Value of m_score. [AI]
		 */
		MxS16 GetHighScore() { return m_score; }

		/**
		 * @brief [AI] Serializes or deserializes the entry using the specified LegoStorage. Coordinates field-wise load or save based on mode.
		 * @param p_storage Storage handler for reading/writing state. [AI]
		 * @return SUCCESS if completed, FAILURE otherwise. [AI]
		 */
		MxResult Serialize(LegoStorage* p_storage)
		{
			if (p_storage->IsReadMode()) {
				p_storage->ReadU8(m_id);
				p_storage->ReadS16(m_unk0x02);
				p_storage->ReadS16(m_score);
			}
			else if (p_storage->IsWriteMode()) {
				p_storage->WriteU8(m_id);
				p_storage->WriteS16(m_unk0x02);
				p_storage->WriteS16(m_score);
			}
			else {
				return FAILURE;
			}

			return SUCCESS;
		}

		// TODO: Possibly private [AI]
		MxU8 m_id;       ///< [AI] Unique race or entry ID (1-based, up to 5).
		MxS16 m_unk0x02; ///< [AI] Unknown field (usage unclear).
		MxS16 m_score;   ///< [AI] High score for this race/entry.
	};

	/**
	 * @brief [AI] Constructs a RaceState, initializing all races with default values and IDs (1 through 5). [AI]
	 */
	RaceState();

	/**
	 * @brief [AI] Returns the class name of the RaceState object ("RaceState").
	 * @return String literal "RaceState". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f07d0
		// STRING: BETA10 0x101f1d20
		return "RaceState";
	}

	/**
	 * @brief [AI] Checks if the object is exactly a RaceState or derived thereof, using class name string comparison (including parent LegoState).
	 * @param p_name Name of type for comparison. [AI]
	 * @return TRUE if this or ancestor class matches p_name, FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, RaceState::ClassName()) || LegoState::IsA(p_name);
	}

	/**
	 * @brief [AI] Serializes all race state entries to or from the given storage object. [AI]
	 * @param p_storage Storage for reading/writing state. [AI]
	 * @return SUCCESS if serialization completed. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	/**
	 * @brief [AI] Fetches a race state entry matching the given entry ID, or NULL if not found in the array.
	 * @param p_id The ID to search for (should be 1-5). [AI]
	 * @return Pointer to the corresponding Entry, or NULL if not present. [AI]
	 */
	Entry* GetState(MxU8 p_id);

	// SYNTHETIC: LEGO1 0x1000f6f0
	// RaceState::~RaceState

	// SYNTHETIC: LEGO1 0x100160d0
	// RaceState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA. [AI]

	Entry m_state[5];     ///< [AI] Entries for each tracked race/state (IDs 1..5).
	undefined4 m_unk0x28; ///< [AI] Unknown extra field, always initialized to zero.
};

// VTABLE: LEGO1 0x100d5db0
// VTABLE: BETA10 0x101be1e0
// SIZE 0x144
/**
 * @brief [AI] Base class for all race-type LegoWorlds. Implements common world logic for the game's various races (e.g., race event areas). Handles notification dispatch, enabling/disabling race logic, storing map state, and specialization for notification handlers.
 *
 * Inherits from LegoWorld. [AI]
 */
class LegoRace : public LegoWorld {
public:
	/**
	 * @brief [AI] Default constructor. Initializes all members and registers to notification and control managers. [AI]
	 */
	LegoRace();

	/**
	 * @brief [AI] Destructor. Cleans up registration and resets user actor if set. [AI]
	 */
	~LegoRace() override; // vtable+0x00

	/**
	 * @brief [AI] Notification callback, dispatches events to various race handlers (click, end action, map struct, etc.) if the world is running. Switches area on specific event type. [AI]
	 * @param p_param Notification/event parameter. [AI]
	 * @return Event handler result (per dispatcher). [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Gets the handler class name string for this class ("LegoRace"). [AI]
	 * @return "LegoRace". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f07c4
		return "LegoRace";
	}

	/**
	 * @brief [AI] Creates and initializes LegoRace world/logic for a DS action. Registers the world, sets up user path actors, and provides Act1State linkage. [AI]
	 * @param p_dsAction Reference to MxDSAction for race setup. [AI]
	 * @return SUCCESS if successfully created. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Handles user click events within the race area. Must be implemented by concrete subclasses. [AI]
	 * @param event Notification parameter describing the click context. [AI]
	 * @return Handler result code. [AI]
	 */
	virtual MxLong HandleClick(LegoEventNotificationParam&) = 0; // vtable+0x6c

	/**
	 * @brief [AI] Handles "path struct" notifications (such as map changes or logic triggers for race boundaries).
	 * @param param Details about the path struct event. [AI]
	 * @return Handler result. [AI]
	 */
	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) { return 0; } // vtable+0x70

	/**
	 * @brief [AI] Handles "end action" (e.g., finish line reached, cutscene ended) events for the race state logic. [AI]
	 * @param p_param Notification parameter for the event. [AI]
	 * @return Handler result (0 = default/ignore). [AI]
	 */
	virtual MxLong HandleEndAction(MxEndActionNotificationParam&) { return 0; } // vtable+0x74

	/**
	 * @brief [AI] Handles Escape input, which is intentionally disabled in race states for legacy reasons. [AI]
	 * @return Always returns FALSE (escape not handled). [AI]
	 */
	MxBool Escape() override { return FALSE; } // vtable+0x64

	/**
	 * @brief [AI] Returns the runtime class name ("LegoRace") for type checks. [AI]
	 * @return "LegoRace". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Runtime type check for this class (or parent LegoWorld). [AI]
	 * @param p_name Runtime type string.
	 * @return TRUE if this is a LegoRace or ancestor. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoRace::ClassName()) || LegoWorld::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles notification of type 0 (specific logic event), can be overridden for custom event processing.
	 * @param param Notification parameters describing the event. [AI]
	 * @return Handler result, always 0 by default. [AI]
	 */
	virtual MxLong HandleType0Notification(MxNotificationParam&) { return 0; } // vtable+0x78

	/**
	 * @brief [AI] Associates a race map instance to the maps array at the given index. Allows switching maps at runtime.
	 * @param p_map Map to assign to the slot. [AI]
	 * @param p_index Index to set in array (0..2). [AI]
	 */
	virtual void VTable0x7c(LegoRaceMap* p_map, MxU32 p_index) // vtable+0x7c
	{
		m_maps[p_index] = p_map;
	}

	/**
	 * @brief [AI] Indicates that custom "VTable0x5c" logic is enabled (always TRUE for LegoRace, possibly to indicate tickle or update registration). [AI]
	 * @return TRUE. [AI]
	 */
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/**
	 * @brief [AI] Enables or disables the race world and detaches the user actor if switching away. [AI]
	 * @param p_enable TRUE to enable; FALSE disables and detaches user actor from the race. [AI]
	 */
	void Enable(MxBool p_enable) override; // vtable+0x68

	// SYNTHETIC: LEGO1 0x10015cc0
	// LegoRace::`scalar deleting destructor'

protected:
	MxS32 m_unk0xf8;                    ///< [AI] Unknown (race-specific state/control variable).
	MxS32 m_unk0xfc;                    ///< [AI] Unknown (race-specific state/control variable).
	MxS32 m_unk0x100;                   ///< [AI] Unknown (race-specific state/control variable).
	MxS32 m_unk0x104;                   ///< [AI] Unknown (race-specific state/control variable).
	MxS32 m_unk0x108;                   ///< [AI] Unknown (race-specific state/control variable).
	MxS32 m_unk0x10c;                   ///< [AI] Unknown (race-specific state/control variable).
	LegoRaceMap* m_maps[3];             ///< [AI] Map objects used by this race (main, alternate, or lap variants).
	LegoGameState::Area m_destLocation; ///< [AI] Destination location (area to switch to after race/transition).
	LegoPathActor* m_pathActor;         ///< [AI] User's path actor for the race event.
	Act1State* m_act1State;             ///< [AI] Pointer to Act1State (first act/sequence logic).
	MxStillPresenter* m_unk0x128;       ///< [AI] Unknown, likely for presenting stills during race transitions or cutscenes.
	MxStillPresenter* m_unk0x12c;       ///< [AI] Unknown, likely for presenting stills during race transitions or cutscenes.
	MxRect32 m_unk0x130;                ///< [AI] Unknown 32-bit rectangle, possible HUD/viewport region.
	RaceState* m_raceState;             ///< [AI] Stores persistent race state/results for the race world instance.
};

#endif // LEGORACE_H
