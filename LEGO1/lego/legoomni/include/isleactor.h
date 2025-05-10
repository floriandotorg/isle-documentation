#ifndef ISLEACTOR_H
#define ISLEACTOR_H

#include "legoactor.h"

class LegoControlManagerNotificationParam;
class LegoPathStructNotificationParam;
class LegoWorld;
class MxEndActionNotificationParam;
class MxNotificationParam;

/// @brief [AI] Represents an actor instance specifically used within LEGO Island, extending LegoActor with notification and action-related behaviors. [AI]
/// @details [AI] IsleActor provides the interface and some implementation for notification handling, user interactions (clicks, button presses), as well as integration with the world context (LegoWorld) and animation/end-action callback mechanisms. This specialization enables game-specific interactivity and logic, over the base LegoActor behavior. [AI]
/// @see LegoActor [AI]
class IsleActor : public LegoActor {
public:
	/// @brief [AI] Handles notification messages sent to this actor and dispatches to the appropriate handler based on the notification type. [AI]
	/// @param p_param Reference to the parameter describing the notification. [AI]
	/// @details [AI] Switches over the notification type (such as button up/down, clicks, end-animation, end-action etc), and calls the corresponding handler virtual. [AI]
	MxLong Notify(MxParam& p_param) override;         // vtable+0x04

	/// @brief [AI] Initializes this IsleActor with a given action. [AI]
	/// @param p_dsAction Reference to the DS action descriptor. [AI]
	/// @details [AI] Initializes the actor using the base class implementation. Additionally attempts to set the m_world pointer to the current active LegoWorld; if that is not possible, marks creation as failed. [AI]
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// @brief [AI] Handles a click event on this actor. [AI]
	/// @details [AI] Default implementation returns 0, meant to be overridden by derived classes for specific click handling logic. [AI]
	virtual MxLong HandleClick() { return 0; } // vtable+0x68

	/// @brief [AI] Handles a custom notification type mapped to vtable slot 0x6c. [AI]
	/// @details [AI] Default implementation returns 0; specific meaning/context must be defined in derived types. [AI]
	virtual MxLong VTable0x6c() { return 0; } // vtable+0x6c

	/// @brief [AI] Handles the notification that an animation on this actor has finished. [AI]
	/// @details [AI] Default implementation returns 0. Derived actors may perform logic when an animation sequence ends. [AI]
	virtual MxLong HandleEndAnim() { return 0; } // vtable+0x70

	/// @brief [AI] Handles the notification that a media or scripted action has ended. [AI]
	/// @param param Reference to end-action notification structure. [AI]
	/// @details [AI] Default returns 0. Allows derived classes to handle cleanup or state changes after an action completes. [AI]
	virtual MxLong HandleEndAction(MxEndActionNotificationParam&) { return 0; } // vtable+0x74

	/// @brief [AI] Handles a button press (down) event, typically from user input, routed via the control manager. [AI]
	/// @param param Button down notification. [AI]
	/// @details [AI] Default returns 0. Derived classes may respond to input via this mechanism. [AI]
	virtual MxLong HandleButtonDown(LegoControlManagerNotificationParam&) { return 0; } // vtable+0x78

	/// @brief [AI] Handles a button release (up) event routed via the control manager. [AI]
	/// @param param Button up notification. [AI]
	/// @details [AI] Default returns 0. Derived classes override to respond to control events. [AI]
	virtual MxLong HandleButtonUp(LegoControlManagerNotificationParam&) { return 0; } // vtable+0x7c

	/// @brief [AI] Handles notifications relating to actor path or path structure changes (for movement, traversal, etc). [AI]
	/// @param param Path structure notification. [AI]
	/// @details [AI] Default returns 0. Derived actors can use this to update their position, behavior, or tracking when assigned new routes or boundaries. [AI]
	virtual MxLong HandlePathStruct(LegoPathStructNotificationParam&) { return 0; } // vtable+0x80

	/// @brief [AI] Returns the class name string of this type (“IsleActor”). [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return "IsleActor";
	}

	/// @brief [AI] Checks if this instance is of the specified class, or inherits from it. [AI]
	/// @param p_name Null-terminated ASCII class name string to compare. [AI]
	/// @details [AI] Returns true if p_name matches directly, or via the base class IsA implementation. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, IsleActor::ClassName()) || LegoActor::IsA(p_name);
	}

protected:
	/// @brief [AI] Pointer to the LegoWorld this actor currently resides in. May be null if not fully initialized. [AI]
	LegoWorld* m_world; // 0x78
};

// SYNTHETIC: LEGO1 0x1000e940
// IsleActor::~IsleActor

// SYNTHETIC: LEGO1 0x1000e990
// IsleActor::`scalar deleting destructor'

#endif // ISLEACTOR_H
