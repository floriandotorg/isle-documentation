#ifndef MXCONTROLPRESENTER_H
#define MXCONTROLPRESENTER_H

#include "decomp.h"
#include "mxcompositepresenter.h"

class LegoControlManagerNotificationParam;

// VTABLE: LEGO1 0x100d7b88
// VTABLE: BETA10 0x101bf5d0
// SIZE 0x5c
/**
 * @brief [AI] Presenter for UI controls, supporting toggles, grids, and "map" style controls with multiple interactive regions. Subclass of MxCompositePresenter that manages multiple visual states and user interactions for a complex control (like a button grid or regioned bitmap). [AI]
 * 
 * @details [AI] MxControlPresenter is responsible for handling user input, state switching, and tickle management for complex GUI controls in LEGO Island. It supports three main modes: toggle, grid, or map (which maps pixel color/values to states for hit detection), and can parse parameters from 'extra' data to configure itself. Clicking or interacting with the control will fire notifications and may change the controlled presenter's state accordingly. [AI]
 */
class MxControlPresenter : public MxCompositePresenter {
public:
	/**
	 * @brief [AI] Constructs an uninitialized control presenter with default state.
	 */
	MxControlPresenter();
	/**
	 * @brief [AI] Destructor, cleans up internal state memory.
	 */
	~MxControlPresenter() override;

	// FUNCTION: LEGO1 0x10043fd0
	/**
	 * @brief [AI] Override of idle/repeating tickle; does nothing by default in this implementation. [AI]
	 */
	void RepeatingTickle() override {} // vtable+0x24

	// FUNCTION: LEGO1 0x10043fe0
	/**
	 * @brief [AI] Virtual stub, returns current enabled flag for the presenter. [AI]
	 * @param p_undefined [AI] Unused/meaningless argument; ignored.
	 * @return TRUE if control is enabled, FALSE otherwise. [AI]
	 */
	MxBool VTable0x64(undefined4 p_undefined) override { return m_unk0x50; } // vtable+0x64

	// FUNCTION: LEGO1 0x10043ff0
	/**
	 * @brief [AI] Changes the enabled state flag. [AI]
	 * @param p_unk0x50 [AI] New enabled flag value.
	 */
	virtual void VTable0x68(MxBool p_unk0x50) { m_unk0x50 = p_unk0x50; } // vtable+0x68

	// FUNCTION: LEGO1 0x10044000
	// FUNCTION: BETA10 0x100ebf80
	/**
	 * @brief [AI] Returns the class name string. [AI]
	 * @return Pointer to "MxControlPresenter". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0514
		return "MxControlPresenter";
	}

	// FUNCTION: LEGO1 0x10044010
	/**
	 * @brief [AI] Checks class ancestry for runtime type information by comparing with this class and parent class names. [AI]
	 * @param p_name [AI] String to compare against.
	 * @return TRUE if p_name matches this or any parent class name, otherwise FALSE. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxControlPresenter::ClassName()) || MxCompositePresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles transition into the 'ready' tickle state; disables tickling and advances state. [AI]
	 */
	void ReadyTickle() override;                                     // vtable+0x18
	/**
	 * @brief [AI] Parses any configuration/customization provided in the extra data for the action, e.g., style, grid or map definitions, and sets up internal state for the control accordingly. [AI]
	 */
	void ParseExtra() override;                                      // vtable+0x30
	/**
	 * @brief [AI] Registers this presenter with the tickle manager and prepares for input handling. [AI]
	 * @return Always returns SUCCESS.
	 */
	MxResult AddToManager() override;                                // vtable+0x34
	/**
	 * @brief [AI] Starts a new UI control action, configuring sub-presenters as required and enabling/disabling them based on parsed state logic. [AI]
	 * @param p_controller [AI] Stream controller for action.
	 * @param p_action [AI] Action to be started.
	 * @return Result of MxCompositePresenter's StartAction, usually SUCCESS.
	 */
	MxResult StartAction(MxStreamController*, MxDSAction*) override; // vtable+0x3c
	/**
	 * @brief [AI] Handles ending of a control's action; may fire notifications and update internal flags. [AI]
	 */
	void EndAction() override;                                       // vtable+0x40
	/**
	 * @brief [AI] Checks if a specific tickle state has passed for the currently active sub-presenter, based on the presenter's current control index. [AI]
	 * @param p_tickleState [AI] Tickle state to check.
	 * @return TRUE if tickle state has passed, FALSE otherwise.
	 */
	MxBool HasTickleStatePassed(TickleState p_tickleState) override; // vtable+0x48
	/**
	 * @brief [AI] Enables or disables the control; delegates enable to correct sub-presenter based on current state/index. [AI]
	 * @param p_enable [AI] TRUE to enable, FALSE to disable.
	 */
	void Enable(MxBool p_enable) override;                           // vtable+0x54
	/**
	 * @brief [AI] Selects a state/sub-control by index, or advances the currently selected state if -1 is provided. Notifies the action and sets tickle/enable state in all sub-presenters. [AI]
	 * @param p_unk0x4e [AI] A state index; if -1, advances state; otherwise, selects the given one. [AI_SUGGESTED_NAME: SetSelectedState]
	 */
	virtual void VTable0x6c(MxS16 p_unk0x4e);                        // vtable+0x6c

	/**
	 * @brief [AI] Processes a notification param and presenter, reacting to input or click events; sets notification and updates state/target. [AI]
	 * @param p_param [AI] Notification parameter object (event/click, etc).
	 * @param p_presenter [AI] The target presenter for the input event.
	 * @return TRUE if event resulted in a state change or handled input, FALSE otherwise.
	 */
	MxBool FUN_10044480(LegoControlManagerNotificationParam* p_param, MxPresenter* p_presenter);

	/**
	 * @brief [AI] Tests if an input event at position (x, y) targets the supplied presenter's region as defined by the control's style (toggle/grid/map). Updates hit-state index used by VTable0x6c. [AI]
	 * @param p_x [AI] X-coordinate of the event.
	 * @param p_y [AI] Y-coordinate of the event.
	 * @param p_presenter [AI] The presenter involved in hit-testing.
	 * @return TRUE if the region is hit/active, FALSE otherwise.
	 */
	MxBool FUN_10044270(MxS32 p_x, MxS32 p_y, MxPresenter* p_presenter);

	/**
	 * @brief [AI] Returns the current selected/control state index. [AI_SUGGESTED_NAME: GetSelectedState]
	 * @return Current state index (usually which button/region/sub-presenter is selected).
	 */
	MxS16 GetUnknown0x4e() { return m_unk0x4e; }

private:
	MxS16 m_unk0x4c;   ///< [AI] Style/mode field: 0=default, 1=toggle, 2=grid, 3=map. [AI_SUGGESTED_NAME: m_style]
	MxS16 m_unk0x4e;   ///< [AI] Current selected/active region or state index within sub-presenters. -1 for none, otherwise sub-presenter index. [AI_SUGGESTED_NAME: m_selectedState]
	MxBool m_unk0x50;  ///< [AI] Enable flag; TRUE if control is enabled, else FALSE. [AI_SUGGESTED_NAME: m_enabledFlag]
	MxS16 m_unk0x52;   ///< [AI] For 'grid' style, the number of grid columns. [AI_SUGGESTED_NAME: m_gridColumns]
	MxS16 m_unk0x54;   ///< [AI] For 'grid' style, number of grid rows. [AI_SUGGESTED_NAME: m_gridRows]
	MxS16 m_unk0x56;   ///< [AI] Transient: last hit region/state index resulting from click/hit-test operation. [AI_SUGGESTED_NAME: m_lastHitState]
	MxS16* m_states;   ///< [AI] Used in 'map' style; holds legal pixel values or "states" for hit-testing a bitmap region. m_states[0]=count, m_states[1..N]=allowed state values.
};

// SYNTHETIC: LEGO1 0x100440f0
// MxControlPresenter::`scalar deleting destructor'

#endif // MXCONTROLPRESENTER_H
