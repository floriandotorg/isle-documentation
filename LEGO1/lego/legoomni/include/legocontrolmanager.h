#ifndef LEGOCONTROLMANAGER_H
#define LEGOCONTROLMANAGER_H

#include "legoeventnotificationparam.h"
#include "legoinputmanager.h"
#include "mxcore.h"
#include "mxpresenterlist.h"

class MxControlPresenter;

/**
 * @brief [AI] Notification parameter for the LegoControlManager, used to propagate information about control events (like clicks) to listeners.
 * @details [AI] This class extends LegoEventNotificationParam and adds additional info about the control object involved (such as the object ID and a related 'atom' string). Used by LegoControlManager to notify interested parties about control-related actions, e.g. UI button clicks. The class also provides setters to customize notification details before broadcasting. [AI]
 */
class LegoControlManagerNotificationParam : public LegoEventNotificationParam {
public:
	/**
	 * @brief [AI] Default constructor initializing members to their default invalid states.
	 * @details [AI] Sets m_clickedObjectId to -1 to indicate no object, and m_clickedAtom to NULL. [AI]
	 */
	LegoControlManagerNotificationParam() : LegoEventNotificationParam()
	{
		m_clickedObjectId = -1;
		m_clickedAtom = NULL;
	}

	/**
	 * @brief [AI] Returns the atom string associated with the control event.
	 * @return [AI] Pointer to the atom string of the clicked control (may be NULL if unset).
	 */
	const char* GetClickedAtom() const { return m_clickedAtom; }

	/**
	 * @brief [AI] Sets the object ID of the clicked control/presenter.
	 * @param p_clickedObjectId [AI] The object ID to set.
	 */
	void SetClickedObjectId(MxS32 p_clickedObjectId) { m_clickedObjectId = p_clickedObjectId; }

	/**
	 * @brief [AI] Sets the atom string that identifies the clicked control.
	 * @param p_clickedAtom [AI] The null-terminated string to set as the atom.
	 */
	void SetClickedAtom(const char* p_clickedAtom) { m_clickedAtom = p_clickedAtom; }

	/**
	 * @brief [AI] Sets the value of the unknown field at offset 0x28.
	 * @param p_unk0x28 [AI] Value to set.
	 * @details [AI] The purpose of this field is undetermined at this time.
	 */
	void SetUnknown0x28(MxS16 p_unk0x28) { m_unk0x28 = p_unk0x28; }

	MxS32 m_clickedObjectId;   ///< @brief [AI] Object ID of the clicked control/presenter (or -1 if not set). [AI]
	const char* m_clickedAtom; ///< @brief [AI] Atom string for the clicked control (unique string identifier; may be NULL). [AI]
	MxS16 m_unk0x28;           ///< @brief [AI] Undetermined; settable via SetUnknown0x28. [AI]
};

// SYNTHETIC: LEGO1 0x10028bf0
// LegoControlManagerNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10028c60
// LegoControlManagerNotificationParam::~LegoControlManagerNotificationParam

/**
 * @brief [AI] Manages control presenters and dispatches notifications for control/input events within the LEGO Island engine.
 * @details [AI] This class tracks active presenters (such as GUI controls), mediates click and button down/up events, and notifies registered listeners when user interactions occur. It maintains state for ongoing UI operations and acts as a central hub for input events that need to be broadcast within the game engine. [AI]
 */
class LegoControlManager : public MxCore {
public:
	/**
	 * @brief [AI] Constructs a LegoControlManager instance and registers it for tickle updates with the global tickle manager.
	 */
	LegoControlManager();

	/**
	 * @brief [AI] Destructor; unregisters this manager from tickle management.
	 */
	~LegoControlManager() override;

	/**
	 * @brief [AI] Performs periodic processing on the control manager, advancing internal event state and dispatching notifications as needed.
	 * @details [AI] Called by the tickle manager. This manages button up event processing and invokes click event resolutions if needed.
	 * @return [AI] Always returns 0 (success).
	 */
	MxResult Tickle() override;

	/**
	 * @brief [AI] Returns the class name identifier for this handler.
	 * @return [AI] String literal "LegoControlManager".
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f31b8
		return "LegoControlManager";
	}

	/**
	 * @brief [AI] Returns the class name for this object.
	 * @return [AI] Class name string "LegoControlManager".
	 */
	const char* ClassName() const override;

	/**
	 * @brief [AI] Checks if this class or one of its ancestors matches the given name.
	 * @param p_name [AI] Class name to check.
	 * @return [AI] True if p_name matches this class or a parent, false otherwise.
	 */
	MxBool IsA(const char* p_name) const override;

	/**
	 * @brief [AI] Assigns the active presenter list to this control manager.
	 * @param p_presenterList [AI] The list of presenters to manage. [AI]
	 * @details [AI] This method resets tracked object/atom click state as part of the assignment.
	 */
	void FUN_10028df0(MxPresenterList* p_presenterList);

	/**
	 * @brief [AI] Adds a listener to be notified of control events.
	 * @param p_listener [AI] Object to receive control event notifications. Must implement Notify(). [AI]
	 */
	void Register(MxCore* p_listener);

	/**
	 * @brief [AI] Removes a listener so it no longer receives control events.
	 * @param p_listener [AI] Listener to remove.
	 */
	void Unregister(MxCore* p_listener);

	/**
	 * @brief [AI] Handles event notification logic, taking an event and possibly updating the manager/presenter state.
	 * @param p_param [AI] Event notification param to process and possibly broadcast.
	 * @param p_presenter [AI] Presenter related to the event.
	 * @return [AI] True if the event was processed and relevant actions were triggered, false otherwise.
	 * @details [AI] Used for centralized evaluation of button up/down events and event state coordination among controls.
	 */
	MxBool FUN_10029210(LegoEventNotificationParam& p_param, MxPresenter* p_presenter);

	/**
	 * @brief [AI] Dispatches a presenter event for the given object and atom parameters.
	 * @param p_objectId [AI] Object ID to match against the presenter's action.
	 * @param p_atom [AI] Atom string to match.
	 * @param p_unk0x4e [AI] Argument passed to the presenter.
	 * @details [AI] Finds the matching presenter and invokes a specific presenter callback.
	 */
	void FUN_100293c0(MxU32 p_objectId, const char* p_atom, MxS16 p_unk0x4e);

	/**
	 * @brief [AI] Finds the topmost control presenter at the given screen coordinates.
	 * @param p_x [AI] X coordinate (screen-space).
	 * @param p_y [AI] Y coordinate (screen-space).
	 * @return [AI] Pointer to the control presenter if found, else NULL.
	 */
	MxControlPresenter* FUN_100294e0(MxS32 p_x, MxS32 p_y);

	/**
	 * @brief [AI] Handles "button down" logic for the input system over presenters.
	 * @return [AI] True if a presenter handled the event and notifies listeners, false otherwise.
	 * @details [AI] Iterates each control, sends the event, and if an interaction is processed, broadcasts notification via the notify list.
	 */
	MxBool FUN_10029630();

	/**
	 * @brief [AI] Handles "button up" click resolution logic for the UI system.
	 * @return [AI] True if a complete click event was processed, false otherwise.
	 * @details [AI] Used to finalize control interaction with object/atom.
	 */
	MxBool FUN_10029750();

	/**
	 * @brief [AI] Notifies all registered listeners with the current control event.
	 * @details [AI] Traverses all in m_notifyList and invokes Notify(m_event) for each.
	 */
	void FUN_100292e0();

	/**
	 * @brief [AI] Gets the internal flag at offset 0x0c.
	 * @return [AI] The value of m_unk0x0c.
	 * @details [AI] The precise purpose of this flag is unknown.
	 */
	undefined4 GetUnknown0x0c() { return m_unk0x0c; }

	/**
	 * @brief [AI] Gets the internal flag at offset 0x10.
	 * @return [AI] The value of m_unk0x10.
	 * @details [AI] The precise purpose of this flag is unknown, but from code analysis, it seems to act as a boolean for button press state.
	 */
	undefined GetUnknown0x10() { return m_unk0x10; }

	// SYNTHETIC: LEGO1 0x10028d40
	// LegoControlManager::`scalar deleting destructor'

private:
	undefined4 m_unk0x08;                        ///< @brief [AI] Internal state for tracking event processing stage; see Tickle and event logic. [AI]
	undefined4 m_unk0x0c;                        ///< @brief [AI] Second internal event state; see IsA(), click tracking logic in FUN_10029210. [AI]
	MxBool m_unk0x10;                            ///< @brief [AI] Tracks if a button is currently pressed and a click event is in progress. [AI_SUGGESTED_NAME: m_isButtonDown]
	MxPresenter* m_unk0x14;                      ///< @brief [AI] Presenter currently involved in the ongoing control operation. [AI]
	LegoControlManagerNotificationParam m_event; ///< @brief [AI] Last or current event parameter, reused and passed to listeners. [AI]
	MxPresenterList* m_presenterList;            ///< @brief [AI] List of all control presenters managed by this manager. [AI]
	LegoNotifyList m_notifyList;                 ///< @brief [AI] List of registered clients (MxCore) that receive notifications on control events. [AI]
};

#endif // LEGOCONTROLMANAGER_H
