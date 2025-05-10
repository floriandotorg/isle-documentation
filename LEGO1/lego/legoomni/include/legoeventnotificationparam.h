#ifndef LEGOEVENTNOTIFICATIONPARAM_H
#define LEGOEVENTNOTIFICATIONPARAM_H

#include "mxnotificationparam.h"
#include "mxtypes.h"

#include <stdlib.h>

class LegoROI;

// VTABLE: LEGO1 0x100d6aa0
// SIZE 0x20
/**
 * @brief Notification parameter class for LEGO event notifications such as mouse events and modifier keys. [AI]
 * @details [AI] Handles mouse position, button/modifier state, key events, and optionally associates with a LegoROI
 * for the event. Used to pass user input details through the event/notification systems of the LEGO Island engine.
 */
class LegoEventNotificationParam : public MxNotificationParam {
public:

	/**
	 * @brief Modifier and mouse button state bit-flag values for user input. [AI]
	 * @details [AI] Used in m_modifier: left/right mouse buttons and up to two modifier keys can be represented.
	 * c_lButtonState: Indicates (bit 0) left mouse button is pressed.
	 * c_rButtonState: Indicates (bit 1) right mouse button is pressed.
	 * c_modKey1: Indicates (bit 2) a modifier key (e.g., Shift) is pressed.
	 * c_modKey2: Indicates (bit 3) another modifier key (e.g., Ctrl) is pressed.
	 */
	enum {
		c_lButtonState = 1,
		c_rButtonState = 2,
		c_modKey1 = 4,
		c_modKey2 = 8,
	};

	/**
	 * @brief Creates a deep copy of this notification parameter object. [AI]
	 * @details [AI] Returns a new LegoEventNotificationParam with identical members, including the associated ROI pointer.
	 * Used for forwarding or queuing input events. [AI]
	 * @return A heap-allocated clone of this instance as MxNotificationParam*. [AI]
	 */
	MxNotificationParam* Clone() const override
	{
		LegoEventNotificationParam* clone =
			new LegoEventNotificationParam(m_type, m_sender, m_modifier, m_x, m_y, m_key);
		clone->m_roi = m_roi;
		return clone;
	} // vtable+0x04

	/**
	 * @brief Default constructor. Sets type to c_notificationType0 and sender to NULL; all data to default/zero. [AI]
	 */
	LegoEventNotificationParam() : MxNotificationParam(c_notificationType0, NULL) {}

	/**
	 * @brief Constructor with all parameter fields for event reporting. [AI]
	 * @param p_type Notification type (event type enum, e.g. mouse, key event) [AI]
	 * @param p_sender Pointer to the sender object (usually the input handler or direct control object) [AI]
	 * @param p_modifier Modifier bitmask (from enum, combines l/r mouse and modifiers) [AI]
	 * @param p_x Mouse X coordinate [AI]
	 * @param p_y Mouse Y coordinate [AI]
	 * @param p_key Keycode for the key event; 0 if unused [AI]
	 */
	LegoEventNotificationParam(
		NotificationId p_type,
		MxCore* p_sender,
		MxU8 p_modifier,
		MxS32 p_x,
		MxS32 p_y,
		MxU8 p_key
	)
		: MxNotificationParam(p_type, p_sender), m_modifier(p_modifier), m_x(p_x), m_y(p_y), m_key(p_key), m_roi(NULL)
	{
	}

	/**
	 * @brief Returns the ROI (3D Object) associated with this event, if any. [AI]
	 * @details [AI] May be null. Used if the event occurred on a specific world object. [AI]
	 */
	LegoROI* GetROI() { return m_roi; }
	/**
	 * @brief Returns modifier bitmask for this event (mouse/keyboard state). [AI]
	 * @details [AI] Bitmask with possible bit flags from enum {c_lButtonState, ...}. [AI]
	 */
	MxU8 GetModifier() { return m_modifier; }
	/**
	 * @brief Returns the keycode for this event, or 0 if not used. [AI]
	 * @details [AI] Represents keyboard input; if not a key event, will be 0. [AI]
	 */
	MxU8 GetKey() const { return m_key; }

	/**
	 * @brief Returns X (horizontal) coordinate for the event, usually screen-relative in pixels. [AI]
	 */
	MxS32 GetX() const { return m_x; }

	/**
	 * @brief Returns Y (vertical) coordinate for the event, usually screen-relative in pixels. [AI]
	 */
	MxS32 GetY() const { return m_y; }

	/**
	 * @brief Sets the ROI reference (object involved in the event). [AI]
	 * @param p_roi Pointer to a LegoROI to associate; can be NULL. [AI]
	 */
	void SetROI(LegoROI* p_roi) { m_roi = p_roi; }

	/**
	 * @brief Sets the modifier state bitmask for the event. [AI]
	 * @param p_modifier Modifier mask (from enum) to set. [AI]
	 */
	void SetModifier(MxU8 p_modifier) { m_modifier = p_modifier; }

	/**
	 * @brief Sets the keycode for the event. [AI]
	 * @param p_key Keycode to assign. [AI]
	 */
	void SetKey(MxU8 p_key) { m_key = p_key; }

	/**
	 * @brief Sets the X (horizontal) coordinate for the event. [AI]
	 * @param p_x New X coordinate. [AI]
	 */
	void SetX(MxS32 p_x) { m_x = p_x; }

	/**
	 * @brief Sets the Y (vertical) coordinate for the event. [AI]
	 * @param p_y New Y coordinate. [AI]
	 */
	void SetY(MxS32 p_y) { m_y = p_y; }

protected:
	/**
	 * @brief Bitmask of button/modifier state at the time of the event. [AI]
	 * @details [AI] See enum above for interpretation: lButton, rButton, modKey1, modKey2. [AI]
	 */
	MxU8 m_modifier; // 0x0c

	/**
	 * @brief X position (horizontal pixel coordinate) for event, typically relative to window/screen. [AI]
	 */
	MxS32 m_x;       // 0x10

	/**
	 * @brief Y position (vertical pixel coordinate) for event, typically relative to window/screen. [AI]
	 */
	MxS32 m_y;       // 0x14

	/**
	 * @brief Key code of event, if any (else 0). [AI]
	 */
	MxU8 m_key;      // 0x18

	/**
	 * @brief Reference to involved world object (ROI), if any (else NULL). [AI]
	 */
	LegoROI* m_roi;  // 0x1c
};

// SYNTHETIC: LEGO1 0x10028770
// LegoEventNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100287e0
// LegoEventNotificationParam::~LegoEventNotificationParam

#endif // LEGOEVENTNOTIFICATIONPARAM_H
