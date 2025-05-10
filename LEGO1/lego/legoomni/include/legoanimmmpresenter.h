#ifndef LEGOANIMMMPRESENTER_H
#define LEGOANIMMMPRESENTER_H

// MxDSActionListCursor needs to be included before std::list
// clang-format off
#include "mxdsmultiaction.h"
// clang-format on
#include "mxcompositepresenter.h"

class LegoAnimPresenter;
class LegoWorld;
class LegoROI;
struct LegoTranInfo;
class MxMatrix;

// VTABLE: LEGO1 0x100d7de8
// SIZE 0x74

/**
 * @brief [AI] Composite presenter class that manages a multi-media animation sequence. It can coordinate several subordinate presenters, orchestrate animations, and manage presenter communications and world/ROI associations for multi-part scripted Lego animation events.
 * @details [AI] Inherits from MxCompositePresenter, allowing multiple subordinate presenters to be managed as part of a composite animation or sequence. Used for "multi-media" (MM) complex Lego animation handling, it coordinates the "tickle" progress, observers, notifications, and resource mapping.
 */
class LegoAnimMMPresenter : public MxCompositePresenter {
public:
	/// @brief [AI] States/steps for a staged tickle sequence through the complex animation.
	enum {
		e_unk0,   ///< [AI] Initial state for staged tickling.
		e_unk1,   ///< [AI] Step 1 in tickle progression.
		e_unk2,   ///< [AI] Step 2 in tickle progression.
		e_unk3,   ///< [AI] Step 3 in tickle progression.
		e_unk4,   ///< [AI] Step 4 in tickle progression.
		e_unk5,   ///< [AI] Step 5 in tickle progression.
		e_unk6,   ///< [AI] Step 6 in tickle progression.
		e_unk7    ///< [AI] Final state for staged tickling.
	};

	/**
	 * @brief [AI] Constructs a LegoAnimMMPresenter, initializing all members.
	 */
	LegoAnimMMPresenter();

	/**
	 * @brief [AI] Destructor. Cleans up world registration and supporting objects.
	 */
	~LegoAnimMMPresenter() override;

	/**
	 * @brief [AI] Handles notifications for the presenter.
	 * @details [AI] Reacts to end-of-action notifications and forwards others to the base composite presenter.
	 * @param p_param The notification parameter structure. [AI]
	 * @return See MxCompositePresenter::Notify for result semantics. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Gets the class handler name for this presenter type.
	 * @return The string "LegoAnimMMPresenter". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f046c
		return "LegoAnimMMPresenter";
	}

	/**
	 * @brief [AI] Returns the runtime class name.
	 * @return Handler class name (HandlerClassName()). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Returns whether this instance is of the given class or inherits from it.
	 * @details [AI] Accepts either "LegoAnimMMPresenter" or any class accepted by MxCompositePresenter::IsA
	 * @param p_name Class name string to test. [AI]
	 * @return True if this is or inherits from class p_name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoAnimMMPresenter::ClassName()) || MxCompositePresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Tickle callback for the ready state. Prepares presenter state and transitions tickle sequence.
	 */
	void ReadyTickle() override;                                                           // vtable+0x18

	/**
	 * @brief [AI] Tickle callback for the starting state. Prepares action timing and advances to the streaming state.
	 */
	void StartingTickle() override;                                                        // vtable+0x1c

	/**
	 * @brief [AI] Tickle callback for the streaming state. Drives the staged tickle progression and manages transition logic.
	 */
	void StreamingTickle() override;                                                       // vtable+0x20

	/**
	 * @brief [AI] Tickle callback for the repeating state. Advances towards freezing/completion once conditions are met.
	 */
	void RepeatingTickle() override;                                                       // vtable+0x24

	/**
	 * @brief [AI] Tickle callback for the done state. No default operation; completion logic may be customized in subclasses.
	 */
	void DoneTickle() override;                                                            // vtable+0x2c

	/**
	 * @brief [AI] Parses the "Extra" field from the current action to extract TranInfo and animation manager ID for this presenter.
	 * @details [AI] Looks for "ANIMMAN_ID" in the extra and acquires TranInfo and related references.
	 */
	void ParseExtra() override;                                                            // vtable+0x30

	/**
	 * @brief [AI] Starts a composite action, creating subordinate presenters for each child action.
	 * @param p_controller Stream controller supplying data for the animation. [AI]
	 * @param p_action The multi-action that this presenter is to execute. [AI]
	 * @return SUCCESS if setup completed, FAILURE otherwise. [AI]
	 */
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) override; // vtable+0x3c

	/**
	 * @brief [AI] Ends the composite action, unregisters and resets relevant state.
	 */
	void EndAction() override;                                                             // vtable+0x40

	/**
	 * @brief [AI] (Internal use) Handles a state transfer/notification from a child presenter to this composite presenter.
	 * @param p_presenter Child presenter invoking this handler. [AI]
	 */
	void VTable0x60(MxPresenter* p_presenter) override;                                    // vtable+0x60

	/**
	 * @brief [AI] Returns true if the presenter state has reached or surpassed e_unk6.
	 * @return True if the state is at least e_unk6. [AI]
	 */
	MxBool FUN_1004b830();

	/**
	 * @brief [AI] Helper routine to end all actions except the central one, handle action teardown, and trigger animation progression.
	 */
	void FUN_1004b840();

	/**
	 * @brief [AI] Returns a boolean based on TranInfo, typically whether a specific transition flag is set.
	 * @return Value from TranInfo transition state field, or TRUE if not present. [AI]
	 */
	MxBool FUN_1004b8b0();

	/**
	 * @brief [AI] Calls the state transition handler, forcing the presenter's tickle progression for special handling.
	 */
	void FUN_1004b8c0();

	/**
	 * @brief [AI] Returns the main subordinate LegoAnimPresenter currently managed by this MM presenter.
	 * @return Pointer to the current LegoAnimPresenter. [AI]
	 */
	LegoAnimPresenter* GetPresenter() { return m_presenter; }

private:

	/**
	 * @brief [AI] Advances the state-machine for the complex "staged" tickle sequence, driving the entire animation MM process.
	 * @return True if tickle state has reached/finished the end state, false otherwise. [AI]
	 */
	MxBool FUN_1004b450();

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk0, calculating ROI mapping and invoking main presenter sync.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always (this state is always successful). [AI]
	 */
	MxBool FUN_1004b530(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk1. Present implementation is a no-op.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always. [AI]
	 */
	MxBool FUN_1004b570(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk2. Handles timing-based wait depending on TranInfo.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE if condition/time reached, otherwise FALSE. [AI]
	 */
	MxBool FUN_1004b580(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk3. Applies local transforms to all mapped ROIs, syncing them with the main animation.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always. [AI]
	 */
	MxBool FUN_1004b5b0(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk4. Currently a no-op.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always. [AI]
	 */
	MxBool FUN_1004b600(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk5. Updates tickle states of subordinate presenters and transitions overall composite state if necessary.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always. [AI]
	 */
	MxBool FUN_1004b610(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for tickle sub-state e_unk6. Waits for the primary presenter to reach idle, then records time and returns.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE if primary presenter has entered idle state; otherwise FALSE. [AI]
	 */
	MxBool FUN_1004b6b0(MxLong p_time);

	/**
	 * @brief [AI] Executes processing for final/exit sub-state e_unk7. Handles repositioning of the user actor and final ROI transformations after animation ends.
	 * @param p_time Time delta since start of streaming, in milliseconds. [AI]
	 * @return TRUE always. [AI]
	 */
	MxBool FUN_1004b6d0(MxLong p_time);

	/**
	 * @brief [AI] The main LegoAnimPresenter managed by this MM presenter during composite animation.
	 */
	LegoAnimPresenter* m_presenter; // 0x4c

	/**
	 * @brief [AI] Records a timestamp for streaming tickle state transitions.
	 */
	MxLong m_unk0x50;               // 0x50

	/**
	 * @brief [AI] Used as working variable for state-machine tickle sequencing, e.g. timing.
	 */
	undefined4 m_unk0x54;           // 0x54

	/**
	 * @brief [AI] Tickle sub-state identifier to drive the staged animation sequence. Used as index in the state progression.
	 */
	MxU8 m_unk0x58;                 // 0x58

	/**
	 * @brief [AI] Value copied from m_tranInfo->m_unk0x10 (often controls timing/routing of certain MM steps).
	 */
	MxU8 m_unk0x59;                 // 0x59

	/**
	 * @brief [AI] Animation Manager (AnimMan) ID, extracted from the action extra field. Used to look up animation and TranInfo.
	 */
	MxU32 m_animmanId;              // 0x5c

	/**
	 * @brief [AI] TranInfo structure (transition info for the animation), after parsing from the action extra.
	 */
	LegoTranInfo* m_tranInfo;       // 0x60

	/**
	 * @brief [AI] Pointer to the current world. Set to the active LegoWorld after action starts.
	 */
	LegoWorld* m_world;             // 0x64

	/**
	 * @brief [AI] Array of matrices for mapped ROIs. Populated during tickle sequencing for complex animation transforms.
	 */
	MxMatrix* m_unk0x68;            // 0x68

	/**
	 * @brief [AI] Array of pointers to LegoROI, comprising the current ROI map for this multi-part animation.
	 */
	LegoROI** m_roiMap;             // 0x6c

	/**
	 * @brief [AI] Number of entries in m_roiMap (ROI mapping count).
	 */
	MxU32 m_roiMapSize;             // 0x70
};

#endif // LEGOANIMMMPRESENTER_H