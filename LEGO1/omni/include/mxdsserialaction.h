#ifndef MXDSSERIALACTION_H
#define MXDSSERIALACTION_H

#include "decomp.h"
#include "mxdsmultiaction.h"

// VTABLE: LEGO1 0x100dcf38
// VTABLE: BETA10 0x101c2940
// SIZE 0xa8

/**
 * @brief [AI] Represents a serial (sequential) action group for data-driven sequence execution in LEGO Island. Actions within this group are processed one at a time, in the order they appear.
 * @details [AI] This class inherits from MxDSMultiAction and extends its functionality to enforce serial execution of contained actions. It utilizes an internal cursor to keep track of traversal state. Care should be taken when copying serial actions, as concurrent traversal of the action list can result in conflicts (as signaled by debug warnings in CopyFrom).
 */
class MxDSSerialAction : public MxDSMultiAction {
public:
	/**
	 * @brief [AI] Constructs an empty serial action, setting up the cursor and type.
	 */
	MxDSSerialAction();

	/**
	 * @brief [AI] Copy constructor. Creates a deep copy from another MxDSSerialAction, including action list and cursor state.
	 * @param p_dsSerialAction [AI] Source serial action to copy from.
	 */
	MxDSSerialAction(MxDSSerialAction& p_dsSerialAction);

	/**
	 * @brief [AI] Destructor. Cleans up internal cursor.
	 */
	~MxDSSerialAction() override;

	/**
	 * @brief [AI] Copies the state of another MxDSSerialAction into this one, including duplication warnings if the source cursor is active.
	 * @details [AI] Will log a warning if the source is currently being traversed or in use.
	 * @param p_dsSerialAction [AI] Source serial action to copy from.
	 */
	void CopyFrom(MxDSSerialAction& p_dsSerialAction);

	/**
	 * @brief [AI] Assignment operator. Overwrites this serial action's state with another's.
	 * @param p_dsSerialAction [AI] Source serial action to assign from.
	 * @return Reference to this, now updated, object. [AI]
	 */
	MxDSSerialAction& operator=(MxDSSerialAction& p_dsSerialAction);

	/**
	 * @brief [AI] Gets the class name of this object.
	 * @details [AI] Used for run-time type identification and class hierarchies. Returns "MxDSSerialAction".
	 * @return Pointer to static string literal representing the class name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f75dc
		return "MxDSSerialAction";
	}

	/**
	 * @brief [AI] Checks if this class is of a given type or its parent types.
	 * @param p_name [AI] Class name string to check against.
	 * @retval TRUE if match for "MxDSSerialAction" or parent classes; FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSerialAction::ClassName()) || MxDSMultiAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Calculates and retrieves the total duration of this serial action.
	 * @details [AI] If an explicit duration is set, returns that. Otherwise, computes the total by summing up each contained action's duration, their start times, and any media action sustain times.
	 */
	MxLong GetDuration() override;

	/**
	 * @brief [AI] Sets an explicit duration value for the entire serial action sequence. If set, GetDuration() will return this value without computation.
	 * @param p_duration [AI] New total duration (in gameplay ticks or ms, units engine-specific).
	 */
	void SetDuration(MxLong p_duration) override;

	/**
	 * @brief [AI] Clones (deep copies) this serial action, including its list of contained actions and configuration.
	 * @return A pointer to the duplicated serial action object. [AI]
	 */
	MxDSAction* Clone() override;

	// SYNTHETIC: LEGO1 0x100cabf0
	// SYNTHETIC: BETA10 0x1015b330
	// MxDSSerialAction::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Cursor object for traversing the serial actions' action list in sequence, tracking serial progress.
	 */
	MxDSActionListCursor* m_cursor; // 0x9c

	/**
	 * @brief [AI] Unknown internal value, possibly used for traversal or mutation state.
	 * @remarks [AI] Writing/mutating actions while traversed may set this flag to avoid corruption.
	 */
	undefined4 m_unk0xa0;           // 0xa0

	/**
	 * @brief [AI] Unknown internal value, reserved for future or state tracking usage.
	 */
	undefined4 m_unk0xa4;           // 0xa4
};

#endif // MXDSSERIALACTION_H
