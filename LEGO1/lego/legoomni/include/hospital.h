#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "actionsfwd.h"
#include "decomp.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;
class MxEndActionNotificationParam;
class MxStillPresenter;

// VTABLE: LEGO1 0x100d97a0
// VTABLE: BETA10 0x101b9ad8
// SIZE 0x18
/**
 * @brief [AI] State-holding class for the hospital area; persists area-specific progress and variables between game sessions. [AI]
 * @details [AI] HospitalState tracks progress and counters for each main actor in the hospital, along with a status indicator used to represent finite state machine progress (e.g. script step/phase). It inherits persistence and polymorphic type information methods from LegoState. [AI]
 */
class HospitalState : public LegoState {
public:
	/**
	 * @brief [AI] Constructs a new HospitalState object and initializes all progression counters to zero. [AI]
	 */
	HospitalState();

	/**
	 * @brief [AI] Default virtual destructor. [AI] 
	 */
	~HospitalState() override {}

	/**
	 * @brief [AI] Retrieves the class name string for run-time type identification. [AI]
	 * @return Pointer to static string "HospitalState". [AI] 
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0480
		return "HospitalState";
	}

	/**
	 * @brief [AI] Checks if the object matches the class name or any parent type. [AI]
	 * @param p_name Name of the class to check against. [AI]
	 * @return TRUE if matches this or parent class; otherwise FALSE. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, HospitalState::ClassName()) || LegoState::IsA(p_name);
	}

	/**
	 * @brief [AI] (De)serializes this state to or from the provided LegoStorage handler. [AI]
	 * @param p_storage The LegoStorage context object (controls read/write and underlying storage). [AI]
	 * @details [AI] All main member variables are read from or written to the save file, depending on mode. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage) override; // vtable+0x1c

	// SYNTHETIC: LEGO1 0x100764c0
	// HospitalState::`scalar deleting destructor'

	// TODO: Most likely getters/setters are not used according to BETA.

	/**
	 * @brief [AI] State machine/counter variable determining narrative step or branch. [AI_SUGGESTED_NAME: m_status] [AI]
	 * @details [AI] Values used internally to indicate current step in the hospital FSM/state sequence. [AI]
	 */
	undefined4 m_unk0x08; // 0x08

	/**
	 * @brief [AI] General area progress/counter for current actor (mirrors one of the counters below depending on which actor is active). [AI_SUGGESTED_NAME: m_progressCounter] [AI]
	 * @details [AI] Set from the relevant actor field and used to determine action branching. [AI]
	 */
	MxS16 m_unk0x0c;      // 0x0c

	/**
	 * @brief [AI] Progress counter for PEPPER character's hospital actions or visit. Ranges at least 0-5. [AI_SUGGESTED_NAME: m_pepperProgress] [AI]
	 */
	MxS16 m_unk0x0e;      // 0x0e

	/**
	 * @brief [AI] Progress counter for MAMA character's hospital actions or visit. Ranges at least 0-5. [AI_SUGGESTED_NAME: m_mamaProgress] [AI]
	 */
	MxS16 m_unk0x10;      // 0x10

	/**
	 * @brief [AI] Progress counter for PAPA character's hospital actions or visit. Ranges at least 0-5. [AI_SUGGESTED_NAME: m_papaProgress] [AI]
	 */
	MxS16 m_unk0x12;      // 0x12

	/**
	 * @brief [AI] Progress counter for NICK character's hospital actions or visit. Ranges at least 0-5. [AI_SUGGESTED_NAME: m_nickProgress] [AI]
	 */
	MxS16 m_unk0x14;      // 0x14

	/**
	 * @brief [AI] Progress counter for LAURA character's hospital actions or visit. Ranges at least 0-5. [AI_SUGGESTED_NAME: m_lauraProgress] [AI]
	 */
	MxS16 m_unk0x16;      // 0x16
};


// VTABLE: LEGO1 0x100d9730
// VTABLE: BETA10 0x101b9a60
// SIZE 0x12c
/**
 * @brief [AI] Implements the main 3D area and logic flow for the Hospital location/scene in LEGO Island. [AI]
 * @details [AI] Manages per-area scripts and state transitions, controls interactive objects specific to the Hospital, and handles notification dispatch and tick updates for the hospital gameplay phase. Inherits rendering, area management and entity management from LegoWorld. [AI]
 */
class Hospital : public LegoWorld {
public:
	/**
	 * @brief [AI] Constructs a Hospital world, zeroes state, registers for notifications. [AI]
	 */
	Hospital();

	/**
	 * @brief [AI] Tears down Hospital world handlers, unregisters from input/notification/tickle systems and resets HospitalState progress step. [AI]
	 */
	~Hospital() override; // vtable+0x00

	/**
	 * @brief [AI] Receives notifications (such as keypresses, control input, and completion of scripted actions) and dispatches to internal event handlers if the world is loaded. [AI]
	 * @param p_param The notification parameter object describing the event. [AI]
	 * @details [AI] Routes EndAction, KeyPress, ButtonDown, Control, and area transition signals while the world is started. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Advances the hospital's world logic per tick; animates cop/pizza LED icons, handles script step transitions. [AI]
	 * @details [AI] Responsible for timing/cycling the LED indicators and decrementing a global transition counter. [AI]
	 */
	MxResult Tickle() override;               // vtable+0x08

	/**
	 * @brief [AI] Indicates this world supports a custom feature flag for internal purposes; always TRUE. [AI] [AI_SUGGESTED_NAME: HasAdvancedControl()]
	 * @return Always TRUE. [AI]
	 */
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/**
	 * @brief [AI] Returns the class name for run-time type identification. [AI]
	 * @return Pointer to static string "Hospital". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0490
		return "Hospital";
	}

	/**
	 * @brief [AI] Checks if the object matches the class name or any parent type. [AI]
	 * @param p_name Name of the class to check against. [AI]
	 * @return TRUE if matches this or parent class; otherwise FALSE. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Hospital::ClassName()) || LegoWorld::IsA(p_name);
	}

	/**
	 * @brief [AI] Loads/sets up this world using the provided data-driven action. Registers input/control, creates state, and sets area. [AI]
	 * @param p_dsAction The action holding script/object IDs and data. [AI]
	 * @details [AI] Ensures there is a HospitalState in the GameState, sets the hospital as the current area, enables input/control, resets internal progress variables. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Initializes the hospital gameplay; loads area animations, resets scores/progress for the current actor, and selects initial area scripts. [AI]
	 * @details [AI] Determines which script to play and how to increment the current actor's visit/score counter. [AI]
	 */
	void ReadyWorld() override;                       // vtable+0x50

	/**
	 * @brief [AI] Cleans up objects and switches the main menu or outside area, if requested; used for ESC or Info/Door button. [AI]
	 * @details [AI] Requests deletion of all present hospital actions, sets destination area appropriately for area transition. [AI]
	 * @return Always TRUE. [AI]
	 */
	MxBool Escape() override;                         // vtable+0x64

	/**
	 * @brief [AI] Enables or disables the hospital world; hooks/unhooks input, marks world active state. [AI]
	 * @param p_enable TRUE to enable, FALSE to disable. [AI]
	 */
	void Enable(MxBool p_enable) override;            // vtable+0x68

	/**
	 * @brief [AI] Triggers a new MxDSAction for the specified script object (e.g. hospital animation), and lowers audio volume. [AI]
	 * @param p_objectId The script/object id to play. [AI]
	 */
	inline void PlayAction(MxU32 p_objectId);

	// SYNTHETIC: LEGO1 0x100747d0
	// Hospital::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Handles a key press event (i.e. VK_SPACE to skip narrative when step allows). [AI]
	 * @param p_key Virtual key code of the pressed key. [AI]
	 * @return 1 if handled/skipped, otherwise 0. [AI]
	 */
	MxLong HandleKeyPress(MxS8 p_key);

	/**
	 * @brief [AI] Handles notification that a script/action has finished, performing state transitions and action branching. [AI]
	 * @param p_param End action event information, including which action ended. [AI]
	 * @return 1 if handled; otherwise 0. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/**
	 * @brief [AI] Handles when a clickable interactable/hotspot is clicked (button down event): e.g. actor selection. [AI]
	 * @param p_param Mouse input and ROI information. [AI]
	 * @return 1 if handled; otherwise 0. [AI]
	 */
	MxLong HandleButtonDown(LegoControlManagerNotificationParam& p_param);

	/**
	 * @brief [AI] Processes interactive control events for custom hospital UI objects (door, info, etc.). [AI]
	 * @param p_param Control event details. [AI]
	 * @return TRUE if the control was handled. [AI]
	 */
	MxBool HandleControl(LegoControlManagerNotificationParam& p_param);

	/**
	 * @brief [AI] ID of the currently-selected/active actor (Pepper, Mama, Papa, Nick, Laura). [AI]
	 */
	MxS16 m_currentActorId;                 // 0xf8

	/**
	 * @brief [AI] Area to transition to after leaving this hospital (set when exiting or clicking doors/info button). [AI]
	 */
	LegoGameState::Area m_destLocation;     // 0xfc

	/**
	 * @brief [AI] State flag used for multi-step hot spot interaction handling and phase progression. [AI]
	 */
	undefined2 m_unk0x100;                  // 0x100

	/**
	 * @brief [AI] Pointer to the persistent HospitalState object for tracking save/load of hospital progress. [AI]
	 */
	HospitalState* m_hospitalState;         // 0x104

	/**
	 * @brief [AI] Controls whether an action/animation is in progress (enables/disables new actions). [AI]
	 */
	undefined2 m_unk0x108;                  // 0x108

	/**
	 * @brief [AI] Enum/script ID of the currently running area script action/animation. [AI]
	 */
	HospitalScript::Script m_currentAction; // 0x10c

	/**
	 * @brief [AI] Presenter/bitmap for the "cop led" visual indicator (used in certain script steps). [AI]
	 */
	MxStillPresenter* m_copLedBitmap;       // 0x110

	/**
	 * @brief [AI] Presenter/bitmap for the "pizza led" visual indicator (used in certain script steps). [AI]
	 */
	MxStillPresenter* m_pizzaLedBitmap;     // 0x114

	/**
	 * @brief [AI] Animation logic flag used to enable cop/pizza LED blinking. [AI]
	 */
	undefined m_unk0x118;                   // 0x118

	/**
	 * @brief [AI] Timestamp for the cop LED animation last frame (ms since level start). [AI]
	 */
	MxLong m_copLedAnimTimer;               // 0x11c

	/**
	 * @brief [AI] Timestamp for the pizza LED animation last frame (ms since level start). [AI]
	 */
	MxLong m_pizzaLedAnimTimer;             // 0x120

	/**
	 * @brief [AI] Time marker for current script step or animation phase. Used for delays and transitions. [AI]
	 */
	MxLong m_time;                          // 0x124

	/**
	 * @brief [AI] Progression flag guarding one-time transitions (prevents repeated transitions). [AI]
	 */
	undefined m_unk0x128;                   // 0x128
};

#endif // HOSPITAL_H
