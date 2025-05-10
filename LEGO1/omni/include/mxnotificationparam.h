#ifndef MXNOTIFICATIONPARAM_H
#define MXNOTIFICATIONPARAM_H

#include "compat.h"
#include "mxparam.h"
#include "mxtypes.h"

class MxCore;

/// Several of those should be defined in LegoOmni
/// @enum NotificationId
/// @brief [AI] Enumerates the various types of notifications used within the engine, corresponding to specific events such as action starts, ends, user input events, presenter updates, streaming events, and object lifecycle transitions.
/// @details [AI] The values in this enum are used to identify the type of notification/message being sent between components, typically encapsulated by `MxNotificationParam` and passed through the notification system.
/// @note [AI] Some entries are annotated with comments referencing offsets in the decomp, which help to trace their usage and occurrence.
enum NotificationId {
	c_notificationType0 = 0,                  ///< [AI] Undefined/Generic notification type [AI]
	c_notificationStartAction = 1,            ///< [AI] Indicates the start of an action [AI]
	c_notificationEndAction = 2,              ///< [AI] Indicates the end of an action [AI]
	c_notificationType4 = 4,                  ///< [AI] Unspecified notification type [AI]
	c_notificationPresenter = 5,              ///< [AI] Update or event from a Presenter [AI]
	c_notificationStreamer = 6,               ///< [AI] Event related to a Streamer [AI]
	c_notificationKeyPress = 7,               ///< [AI] Keyboard key press detected [AI]
	c_notificationButtonUp = 8,               ///< [AI] Mouse/gamepad button release [AI]
	c_notificationButtonDown = 9,             ///< [AI] Mouse/gamepad button press [AI]
	c_notificationMouseMove = 10,             ///< [AI] Mouse movement event [AI]
	c_notificationClick = 11,                 ///< [AI] Mouse click event [AI]
	c_notificationDragStart = 12,             ///< [AI] Start of a drag event (mouse/touch) [AI]
	c_notificationDrag = 13,                  ///< [AI] Ongoing drag/move event [AI]
	c_notificationDragEnd = 14,               ///< [AI] End of drag event [AI]
	c_notificationTimer = 15,                 ///< [AI] Timer-related event [AI]
	c_notificationControl = 17,               ///< [AI] UI control event [AI]
	c_notificationEndAnim = 18,               ///< [AI] End of an animation [AI]
	c_notificationPathStruct = 19,            ///< [AI] Data related to a path structure [AI]
	c_notificationType20 = 20,                ///< [AI] Unspecified notification type [AI]
	c_notificationNewPresenter = 21,          ///< [AI] Notification about a new Presenter object [AI]
	c_notificationType22 = 22,                ///< [AI] Unspecified notification type [AI]
	c_notificationType23 = 23,                ///< [AI] Unspecified notification type [AI]
	c_notificationTransitioned = 24           ///< [AI] Object has transitioned states or locations [AI]
};

/// @class MxNotificationParam
/// @brief [AI] Parameter object representing a single notification or event, carrying an identifier and sender pointer.
/// @details [AI] Used throughout the notification system to pass event information (such as event type and source) to subscribers/handlers. Typically delivered to components via MxOmni or similar dispatcher.
/// @see NotificationId
/// @note [AI] Inherits from MxParam. This enables it to be handled by notification/message passing infrastructure shared by other param types.
/// @size 0x0c [AI]
class MxNotificationParam : public MxParam {
public:
	/// @brief [AI] Constructs a default notification parameter with type c_notificationType0 and no sender.
	MxNotificationParam() : m_type(c_notificationType0), m_sender(NULL) {}

	/// @brief [AI] Constructs a notification parameter with a specific type and sender.
	/// @param p_type [AI] The notification/event identifier (see NotificationId).
	/// @param p_sender [AI] The MxCore instance that is the source of this notification.
	MxNotificationParam(NotificationId p_type, MxCore* p_sender) : MxParam(), m_type(p_type), m_sender(p_sender) {}

	/// @brief [AI] Creates a copy of this notification parameter object on the heap.
	/// @details [AI] Used by the messaging infrastructure to duplicate the notification when dispatching to multiple receivers.
	/// @return [AI] Pointer to a cloned MxNotificationParam of the same type and sender.
	virtual MxNotificationParam* Clone() const { return new MxNotificationParam(m_type, m_sender); } // vtable+0x04

	/// @brief [AI] Retrieves the current notification type of this parameter.
	/// @return [AI] NotificationId enumeration specifying the type of this notification.
	NotificationId GetNotification() const { return m_type; }

	/// @brief [AI] Retrieves the sender pointer associated with this notification.
	/// @return [AI] A pointer to the MxCore object that originated this notification.
	MxCore* GetSender() const { return m_sender; }

	/// @brief [AI] Sets the notification type for this parameter object.
	/// @param p_type [AI] The new notification/event type identifier.
	void SetNotification(NotificationId p_type) { m_type = p_type; }

	/// @brief [AI] Sets the sender pointer for this notification parameter.
	/// @param p_sender [AI] Pointer to the MxCore that will be considered as sender/originator.
	void SetSender(MxCore* p_sender) { m_sender = p_sender; }

protected:
	NotificationId m_type; ///< [AI] Type of notification/event carried by this object (see NotificationId).
	MxCore* m_sender;      ///< [AI] Pointer to the MxCore instance that sent or originated this notification.
};

// SYNTHETIC: LEGO1 0x10010430
// SYNTHETIC: BETA10 0x100136c0
// MxNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100104a0
// SYNTHETIC: BETA10 0x10013740
// MxNotificationParam::~MxNotificationParam

#endif // MXNOTIFICATIONPARAM_H
