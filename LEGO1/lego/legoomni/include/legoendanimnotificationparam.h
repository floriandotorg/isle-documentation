#ifndef LEGOENDANIMNOTIFICATIONPARAM_H
#define LEGOENDANIMNOTIFICATIONPARAM_H

#include "decomp.h"
#include "mxnotificationparam.h"

// VTABLE: LEGO1 0x100d7e80
// SIZE 0x10

/**
 * @brief Notification parameter for signaling the end of an animation in the LEGO Island engine. [AI]
 * @details [AI] 
 * This class extends MxNotificationParam to include specific information (the index of the animation) about which animation's end event is being reported. 
 * It is typically posted by an animation system to notify subscribers that a particular animation (as identified by the index) has finished. 
 * This mechanism is central to decoupling animation playback from logical responses within the engine (such as triggering follow-up actions or state changes). 
 * [AI] 
 */
class LegoEndAnimNotificationParam : public MxNotificationParam {
public:
	/**
	 * @brief Constructor. [AI]
	 * @param p_type The notification type, used by the MxNotificationParam base. [AI]
	 * @param p_sender Pointer to the sending MxCore object. [AI]
	 * @param p_index Integer that identifies which animation ended. [AI]
	 * @details [AI]
	 * The index typically refers to the animation resource or sequence, allowing receivers to know exactly which animation finished.
	 */
	LegoEndAnimNotificationParam(NotificationId p_type, MxCore* p_sender, MxU32 p_index)
		: MxNotificationParam(p_type, p_sender), m_index(p_index)
	{
	}

	/**
	 * @brief Creates a copy of this notification parameter object. [AI]
	 * @details [AI]
	 * Used to safely propagate notification parameters through the event/notification system,
	 * ensuring unique ownership and proper polymorphic behavior.
	 * @return A dynamically-allocated clone (caller takes ownership). [AI]
	 */
	MxNotificationParam* Clone() const override
	{
		return new LegoEndAnimNotificationParam(m_type, m_sender, m_index);
	} // vtable+0x04

	/**
	 * @brief Retrieves the index associated with this end-animation notification. [AI]
	 * @details [AI]
	 * This index typically maps to the specific animation or sequence whose end event is being signaled.
	 * Receivers can use the index to identify or react to the specific animation completion.
	 * @return Animation index value for this notification. [AI]
	 */
	MxU32 GetIndex() { return m_index; }

protected:
	/**
	 * @brief Index of the finished animation. [AI]
	 * @details [AI] 
	 * Used by listeners to identify what animation ended.
	 */
	MxU32 m_index; // 0x0c
};

// SYNTHETIC: LEGO1 0x1004b080
// LegoEndAnimNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1004b0f0
// LegoEndAnimNotificationParam::~LegoEndAnimNotificationParam

#endif // LEGOENDANIMNOTIFICATIONPARAM_H
