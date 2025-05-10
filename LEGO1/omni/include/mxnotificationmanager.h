#ifndef MXNOTIFICATIONMANAGER_H
#define MXNOTIFICATIONMANAGER_H

#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"

class MxNotificationParam;

/**
 * @brief [AI] Carries a notification to be sent to a target MxCore object. This encapsulates a notification target and a notification parameter instance.
 * @details [AI] Used internally by the notification manager to represent a single pending notification for asynchronous delivery to a game object.
 */
class MxNotification {
public:
	/**
	 * @brief [AI] Constructor for MxNotification.
	 * @param p_target The MxCore object to which this notification is addressed. [AI]
	 * @param p_param Reference to the notification parameter object (the manager will clone this parameter). [AI]
	 * @details [AI] The notification takes ownership of a cloned copy of the parameter to ensure thread safety.
	 */
	MxNotification(MxCore* p_target, const MxNotificationParam& p_param);

	/**
	 * @brief [AI] Destructor for MxNotification. Destroys the internally cloned parameter. [AI]
	 */
	~MxNotification();

	/**
	 * @brief [AI] Returns the target of this notification.
	 * @return MxCore* [AI]
	 */
	MxCore* GetTarget() { return m_target; }

	/**
	 * @brief [AI] Returns the notification parameter (cloned by the notification). 
	 * @return MxNotificationParam* [AI]
	 */
	MxNotificationParam* GetParam() { return m_param; }

private:
	MxCore* m_target;             ///< [AI] Target object that will receive the notification
	MxNotificationParam* m_param; ///< [AI] Cloned parameter object sent in the notification
};

/**
 * @brief [AI] List of object IDs used to track registered notification listeners. [AI]
 * @details [AI] Used by MxNotificationManager to identify registered recipients.
 */
class MxIdList : public list<MxU32> {};

/**
 * @brief [AI] List of notification pointers used to queue notifications for delivery. [AI]
 * @details [AI] Used internally in the notification manager for asynchronous processing.
 */
class MxNotificationPtrList : public list<MxNotification*> {};

// VTABLE: LEGO1 0x100dc078

/**
 * @brief [AI] Central registry and dispatcher of asynchronous notifications between MxCore objects. [AI]
 * @details [AI] Manages an internal queue of notifications, a thread lock for concurrency, and the registration of observers (listeners).
 *              Responsible for routing queued notifications to the correct object on each tick.
 */
class MxNotificationManager : public MxCore {
private:
	MxNotificationPtrList* m_queue;    ///< [AI] Primary notification queue, holds pending notifications for dispatch
	MxNotificationPtrList* m_sendList; ///< [AI] Temporary list used when dispatching queued notifications during Tickle()
	MxCriticalSection m_lock;          ///< [AI] Internal lock for thread safety on notification queue
	MxS32 m_unk0x2c;                   ///< [AI] [Unknown meaning, possibly internal state or reserved]
	MxIdList m_listenerIds;            ///< [AI] Registered target MxCore IDs that may receive notifications
	MxBool m_active;                   ///< [AI] Controls whether notifications may be queued or dispatched

public:
	/**
	 * @brief [AI] Constructs a new NotificationManager, initializing all state to defaults. [AI]
	 */
	MxNotificationManager();

	/**
	 * @brief [AI] Destroys the NotificationManager. Flushes notifications, cleans up memory, and unregisters itself from the tickle manager. [AI]
	 */
	~MxNotificationManager() override; // vtable+0x00 (scalar deleting destructor)

	/**
	 * @brief [AI] Processes and dispatches all queued notifications to their targets. [AI]
	 * @details [AI] Called by the tickle loop to flush the notification queue, invoking Notify(param) on each registered target. Thread-safe.
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief [AI] Initializes the notification manager, setting up queues and optionally registering with the tickle manager. [AI]
	 * @param p_frequencyMS The tick frequency (ms) to process notifications. [AI]
	 * @param p_createThread Whether to create an internal thread for processing. [AI]
	 * @return SUCCESS if initialized, FAILURE otherwise. [AI]
	 */
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread); // vtable+0x14

	/**
	 * @brief [AI] Registers a listener object to receive notifications. [AI]
	 * @param p_listener Pointer to the MxCore-derived listener object to register.
	 * @details [AI] Registers the object's ID; only registered listeners may be sent notifications. Thread-safe.
	 */
	void Register(MxCore* p_listener);

	/**
	 * @brief [AI] Removes a previously registered listener and flushes any pending notifications for it. [AI]
	 * @param p_listener Pointer to the listener object (to remove by ID). [AI]
	 * @details [AI] Also flushes any queued (but undelivered) notifications intended for this object. Thread-safe.
	 */
	void Unregister(MxCore* p_listener);

	/**
	 * @brief [AI] Queues a notification to be sent to a specific registered listener. [AI]
	 * @param p_listener Target listener object (must be registered) [AI]
	 * @param p_param Notification parameter (will be cloned inside the notification) [AI]
	 * @return SUCCESS if enqueued, FAILURE otherwise (e.g., not registered or queue inactive) [AI]
	 */
	MxResult Send(MxCore* p_listener, const MxNotificationParam& p_param);

	/**
	 * @brief [AI] Returns a pointer to the current notification queue (for debug/inspection). [AI]
	 * @return Pointer to queue list structure. [AI]
	 */
	MxNotificationPtrList* GetQueue() { return m_queue; }

	/**
	 * @brief [AI] Sets the notification manager active or inactive. [AI]
	 * @param p_active If FALSE, prevents notifications from being queued or dispatched. [AI]
	 */
	void SetActive(MxBool p_active) { m_active = p_active; }

	/**
	 * @brief [AI] Returns whether the notification queue is empty. [AI]
	 * @return TRUE if empty or no queue exists, FALSE otherwise. [AI]
	 */
	MxBool IsEmpty() const { return m_queue ? m_queue->empty() : TRUE; }

	// SYNTHETIC: LEGO1 0x100ac390
	// MxNotificationManager::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Flushes any notifications (in queue or in process) related to the provided object. [AI]
	 * @param p_listener Listener whose pending notifications (both to and from) will be forcibly processed/discarded. [AI]
	 * @details [AI] Used to ensure no notifications for a deleted object remain. [AI]
	 */
	void FlushPending(MxCore* p_listener);
};

// TEMPLATE: LEGO1 0x100ac320
// list<unsigned int,allocator<unsigned int> >::~list<unsigned int,allocator<unsigned int> >

// FUNCTION: LEGO1 0x100ac3b0
// MxIdList::~MxIdList

// TEMPLATE: LEGO1 0x100ac400
// List<unsigned int>::~List<unsigned int>

// TEMPLATE: LEGO1 0x100ac540
// List<MxNotification *>::~List<MxNotification *>

// TEMPLATE: LEGO1 0x100ac590
// list<MxNotification *,allocator<MxNotification *> >::~list<MxNotification *,allocator<MxNotification *> >

// TEMPLATE: LEGO1 0x100acbf0
// list<MxNotification *,allocator<MxNotification *> >::begin

// TEMPLATE: LEGO1 0x100acc00
// list<MxNotification *,allocator<MxNotification *> >::insert

// TEMPLATE: LEGO1 0x100acc50
// list<MxNotification *,allocator<MxNotification *> >::erase

// TEMPLATE: LEGO1 0x100acca0
// list<MxNotification *,allocator<MxNotification *> >::_Buynode

// SYNTHETIC: LEGO1 0x100accd0
// MxNotificationPtrList::~MxNotificationPtrList

// TEMPLATE: BETA10 0x10129670
// list<MxNotification *,allocator<MxNotification *> >::empty

#endif // MXNOTIFICATIONMANAGER_H
