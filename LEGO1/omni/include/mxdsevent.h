#ifndef MXDSEVENT_H
#define MXDSEVENT_H

#include "mxdsmediaaction.h"

// VTABLE: LEGO1 0x100dce18
// VTABLE: BETA10 0x101c2bb0

/**
 * @brief [AI] Represents an event media action (a discrete event) parsed from script/scene data (SI files).
 * @details [AI] This class extends MxDSMediaAction to provide event functionality (used for signaling or discrete scriptable events) in the LEGO Island engine's data-driven object system. The event action can be cloned and supports polymorphic type identification.
 */
class MxDSEvent : public MxDSMediaAction {
public:
	/**
	 * @brief [AI] Default constructor. Sets the DS object type to e_event.
	 */
	MxDSEvent();

	/**
	 * @brief [AI] Copy constructor. Initializes the MxDSEvent instance from another.
	 * @param p_dsEvent [AI] Source event to copy from.
	 */
	MxDSEvent(MxDSEvent& p_dsEvent);

	/**
	 * @brief [AI] Virtual destructor.
	 */
	~MxDSEvent() override;

	/**
	 * @brief [AI] Copies state from another MxDSEvent into this object.
	 * @param p_dsEvent [AI] Source event to copy state from.
	 */
	void CopyFrom(MxDSEvent& p_dsEvent);

	/**
	 * @brief [AI] Assigns the content of another MxDSEvent to this object.
	 * @param p_dsEvent [AI] Source event for assignment.
	 * @return Reference to this object. [AI]
	 */
	MxDSEvent& operator=(MxDSEvent& p_dsEvent);

	/**
	 * @brief [AI] Returns the class name string ("MxDSEvent").
	 * @return const char* to static string literal. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025f0
		return "MxDSEvent";
	}

	/**
	 * @brief [AI] Checks if object is of given class name or derives from it.
	 * @param p_name [AI] Name to check against ("MxDSEvent").
	 * @return True if class matches or derives; otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSEvent::ClassName()) || MxDSMediaAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates a new copy of this event (deep clone).
	 * @details [AI] The clone is a newly-allocated copy of this event, with all state duplicated.
	 * @return New MxDSAction pointer (caller-owns). [AI]
	 */
	MxDSAction* Clone() override; // vtable+0x2c

	// SYNTHETIC: LEGO1 0x100c9780
	// SYNTHETIC: BETA10 0x1015da90
	// MxDSEvent::`scalar deleting destructor'
};

#endif // MXDSEVENT_H
