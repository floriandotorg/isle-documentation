#ifndef MXACTIONNOTIFICATIONPARAM_H
#define MXACTIONNOTIFICATIONPARAM_H

#include "mxdsaction.h"
#include "mxnotificationparam.h"

class MxPresenter;

/// @class MxActionNotificationParam
/// @brief [AI] Notification parameter class that contains information about an MxDSAction, used for inter-object notifications related to dynamic script (SI) actions. It can optionally own/reallocate its action. [AI]
/// @details [AI] Derived from MxNotificationParam, this class extends notifications to carry an action and "realloc" flag, typically signaling start/end/progress of script actions. It supports cloning and optional deep copy creation of the action. [AI]
// VTABLE: LEGO1 0x100d8350
// SIZE 0x14
class MxActionNotificationParam : public MxNotificationParam {
public:
	/// @brief [AI] Constructs the action notification parameter, optionally cloning the action if requested. [AI]
	/// @param p_type Notification type that identifies the notification event. [AI]
	/// @param p_sender The object sending the notification. [AI]
	/// @param p_action The MxDSAction associated with the notification. [AI]
	/// @param p_reallocAction If TRUE, clones the input action for ownership; if FALSE, just references it. [AI]
	MxActionNotificationParam(NotificationId p_type, MxCore* p_sender, MxDSAction* p_action, MxBool p_reallocAction)
		: MxNotificationParam(p_type, p_sender)
	{
		MxDSAction* oldAction = p_action;
		m_realloc = p_reallocAction;

		if (p_reallocAction) {
			m_action = new MxDSAction();
		}
		else {
			m_action = oldAction;
			return;
		}

		m_action->SetAtomId(oldAction->GetAtomId());
		m_action->SetObjectId(oldAction->GetObjectId());
		m_action->SetUnknown24(oldAction->GetUnknown24());
	}

	/// @brief [AI] Destructor releases the action if this object owns it (realloc flag set). [AI]
	~MxActionNotificationParam() override
	{
		if (!m_realloc) {
			return;
		}

		if (m_action) {
			delete m_action;
		}
	}

	/// @brief [AI] Creates a clone of this notification parameter with the same state. [AI]
	/// @return A new MxActionNotificationParam allocated on the heap. [AI]
	MxNotificationParam* Clone() const override
	{
		return new MxActionNotificationParam(m_type, m_sender, m_action, m_realloc);
	} // vtable+0x04

	/// @brief [AI] Direct access to the underlying action. [AI]
	/// @return Pointer to the contained MxDSAction (may or may not be owned). [AI]
	MxDSAction* GetAction() { return m_action; }

protected:
	MxDSAction* m_action; ///< @brief [AI] Associated action (owned if m_realloc is true). [AI]
	MxBool m_realloc;     ///< @brief [AI] TRUE if this object owns and should free m_action. [AI]
};

/// @class MxStartActionNotificationParam
/// @brief [AI] Notification parameter marking the start of an action, specialization of MxActionNotificationParam. [AI]
// VTABLE: LEGO1 0x100dc210
// SIZE 0x14
class MxStartActionNotificationParam : public MxActionNotificationParam {
public:
	/// @brief [AI] Constructs a start-action notification param. [AI]
	/// @param p_type Notification type corresponding to action start. [AI]
	/// @param p_sender Notification sender object. [AI]
	/// @param p_action Associated action. [AI]
	/// @param p_reallocAction Whether to clone the action. [AI]
	MxStartActionNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxDSAction* p_action,
		MxBool p_reallocAction
	)
		: MxActionNotificationParam(p_type, p_sender, p_action, p_reallocAction)
	{
	}

	/// @brief [AI] Returns a clone of this notification parameter. [AI]
	MxNotificationParam* Clone() const override; // vtable+0x04
};

/// @class MxEndActionNotificationParam
/// @brief [AI] Notification parameter marking the end of an action, specialization of MxActionNotificationParam. [AI]
// VTABLE: LEGO1 0x100d8358
// SIZE 0x14
class MxEndActionNotificationParam : public MxActionNotificationParam {
public:
	/// @brief [AI] Constructs an end-action notification param. [AI]
	/// @param p_type Notification type for action end events. [AI]
	/// @param p_sender Notification sender object. [AI]
	/// @param p_action Associated action. [AI]
	/// @param p_reallocAction Whether to clone the action. [AI]
	MxEndActionNotificationParam(NotificationId p_type, MxCore* p_sender, MxDSAction* p_action, MxBool p_reallocAction)
		: MxActionNotificationParam(p_type, p_sender, p_action, p_reallocAction)
	{
	}

	/// @brief [AI] Returns a clone of this notification parameter, specializing the type for end-action. [AI]
	MxNotificationParam* Clone() const override
	{
		return new MxEndActionNotificationParam(c_notificationEndAction, m_sender, m_action, m_realloc);
	} // vtable+0x04
};

/// @class MxType4NotificationParam
/// @brief [AI] Specialized notification parameter, used for notification type 4, extending MxActionNotificationParam with a presenter pointer. [AI]
/// @details [AI] This is used for advanced/engine-internal actions that may require an associated MxPresenter. [AI]
// VTABLE: LEGO1 0x100dc208
// SIZE 0x18
class MxType4NotificationParam : public MxActionNotificationParam {
public:
	/// @brief [AI] Constructs a type 4 notification parameter carrying an action and a presenter pointer. [AI]
	/// @param p_sender Notification sender object. [AI]
	/// @param p_action Associated action. [AI]
	/// @param p_unk0x14 Additional pointer, likely to an associated presenter. [AI_SUGGESTED_NAME: p_presenter] [AI]
	MxType4NotificationParam(MxCore* p_sender, MxDSAction* p_action, MxPresenter* p_unk0x14)
		: MxActionNotificationParam(c_notificationType4, p_sender, p_action, FALSE)
	{
		m_unk0x14 = p_unk0x14;
	}

	/// @brief [AI] Returns a clone of this notification parameter. [AI]
	MxNotificationParam* Clone() const override; // vtable+0x04

private:
	MxPresenter* m_unk0x14; ///< @brief [AI] Pointer to a related presenter for handling this notification. [AI_SUGGESTED_NAME: m_presenter] [AI]
};

// SYNTHETIC: LEGO1 0x100511e0
// MxActionNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100513a0
// MxEndActionNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10051410
// MxEndActionNotificationParam::~MxEndActionNotificationParam

// SYNTHETIC: LEGO1 0x100b0430
// MxStartActionNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100b04a0
// MxStartActionNotificationParam::~MxStartActionNotificationParam

// SYNTHETIC: LEGO1 0x100b05c0
// MxType4NotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100b0630
// MxType4NotificationParam::~MxType4NotificationParam

#endif