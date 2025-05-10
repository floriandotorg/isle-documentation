#ifndef MXCOMPOSITEPRESENTER_H
#define MXCOMPOSITEPRESENTER_H

#include "mxpresenter.h"
#include "mxstl/stlcompat.h"

class MxEndActionNotificationParam;
class MxNotificationParam;

/// @brief [AI] STL list of MxPresenter pointers, used to manage multiple child presenters under composite control.
class MxCompositePresenterList : public list<MxPresenter*> {}; // [AI]

/// @brief [AI] Composite presenter that manages a collection of child presenters, orchestrating their actions and notifications as a group.
/// @details [AI] MxCompositePresenter orchestrates a collection of presenters (typically corresponding to sub-actions in an SI file).
/// It handles dispatching StartAction to each, managing their lifecycles, and relaying notifications such as action-completion,
/// grouping parallel or serial media actions. Used for MxDSMultiAction and derived SI actions.
/// Child presenters are pushed into m_list, and removed as they complete; when all are finished, composite cleanups and forwards notifications.
class MxCompositePresenter : public MxPresenter {
public:
	/// @brief [AI] Default constructor; registers the composite presenter with the notification manager.
	MxCompositePresenter();

	/// @brief [AI] Destructor, unregisters the presenter from the notification manager and properly cleans up contained presenters.
	~MxCompositePresenter() override; // vtable+0x00

	/// @brief [AI] Notifies the composite presenter of a particular event (such as end of sub-action or notification from a child presenter).
	/// @param p_param [AI] Reference to a notification parameter, typically specifies sender, notification type, and any action involved.
	/// @return [AI] Always returns 0. Dispatches to relevant virtual handlers based on the notification.
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// @brief [AI] Returns the handler class name ("MxCompositePresenter").
	/// @return [AI] Static string identifier for this presenter. Used during SI media dispatch and factory creation.
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0774
		return "MxCompositePresenter";
	}

	/// @brief [AI] Returns the dynamic class name; used for runtime type identification.
	/// @return [AI] Class name string for this type.
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/// @brief [AI] Runtime type checking for presenter class hierarchy, supporting parent/child class checks.
	/// @param p_name [AI] The name to compare this class against.
	/// @return [AI] True if p_name matches this class or any super class in presenter hierarchy.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxCompositePresenter::ClassName()) || MxPresenter::IsA(p_name);
	}

	/// @brief [AI] Starts a composite action by creating child presenters for each action in a MxDSMultiAction list and starting them.
	/// @param p_controller [AI] The controlling stream controller.
	/// @param p_action [AI] The composite multi-action (should be or derive from MxDSMultiAction).
	/// @return [AI] SUCCESS if all child presenters are created and started, FAILURE on error.
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) override; // vtable+0x3c

	/// @brief [AI] Ends the composite action, terminating all child presenters and clearing action lists. Sends end notifications if needed.
	void EndAction() override; // vtable+0x40

	/// @brief [AI] Change the tickle state of this composite presenter and propagate to each child. Used for sequencing execution (e.g., idle, ready).
	/// @param p_tickleState [AI] New tickle state to set for all managed presenters.
	void SetTickleState(TickleState p_tickleState) override; // vtable+0x44

	/// @brief [AI] Checks if all child presenters have advanced past the given tickle state.
	/// @param p_tickleState [AI] State to check against for all children.
	/// @return [AI] TRUE if every child has passed this state, FALSE otherwise.
	MxBool HasTickleStatePassed(TickleState p_tickleState) override; // vtable+0x48

	/// @brief [AI] Enables or disables this presenter and all child presenters.
	/// @param p_enable [AI] TRUE to enable, FALSE to disable (pause).
	void Enable(MxBool p_enable) override; // vtable+0x54

	/// @brief [AI] Handler for "end action" notification, invoked when one of the child presenters finishes its assigned sub-action.
	/// @details [AI] Removes the corresponding presenter and action, cleans up, and may trigger continuation logic or end itself if all sub-actions done.
	/// @param p_param [AI] EndActionNotification containing sender and finished action information.
	virtual void VTable0x58(MxEndActionNotificationParam& p_param); // vtable+0x58

	/// @brief [AI] Handler for generic presenter notification, such as state change. Also used for signaling further sequencing in serial actions.
	/// @param p_param [AI] Notification parameter with sender and type.
	virtual void VTable0x5c(MxNotificationParam& p_param); // vtable+0x5c

	/// @brief [AI] Advance sequencing for serial multi-actions: promotes the next presenter in sequence to e_ready state after predecessor finishes.
	/// @param p_presenter [AI] The presenter that triggered the next-in-serial logic.
	virtual void VTable0x60(MxPresenter* p_presenter); // vtable+0x60

	/// @brief [AI] Delegated state/mode checking. If this presenter is part of another composite, defers the check to parent.
	/// @param p_undefined [AI] Value is opaque; passed along a potential hierarchy. [AI_SUGGESTED_NAME: stateCheckReason]
	/// @return [AI] TRUE if allowable for tickle/check to proceed, otherwise composite-specific result.
	virtual MxBool VTable0x64(undefined4 p_undefined)
	{
		if (m_compositePresenter) {
			return m_compositePresenter->VTable0x64(p_undefined);
		}
		return TRUE;
	} // vtable+0x64

	/// @brief [AI] Returns reference to the internal list of child presenters managed by this composite.
	/// @return [AI] Pointer to the composite's presenter list (owned by this).
	MxCompositePresenterList* GetList() { return &m_list; }

protected:
	/// @brief [AI] List of owned child presenters that are managed by this MxCompositePresenter. Actions are created/shutdown with this list.
	MxCompositePresenterList m_list; // 0x40 [AI]
};

#endif // MXCOMPOSITEPRESENTER_H
