#ifndef MXDSSELECTACTION_H
#define MXDSSELECTACTION_H

#include "decomp.h"
#include "mxdsparallelaction.h"
#include "mxstringlist.h"

// VTABLE: LEGO1 0x100dcfc8
// VTABLE: BETA10 0x101c29d0
// SIZE 0xb0
/**
 * @brief [AI] Represents a "select" action within a DS (Script/Scene) file, deserialized from SI files to select from a set of available actions at runtime based on a variable or random value.
 *
 * MxDSSelectAction introduces selection logic to the standard parallel action, determining which child action to activate based on the input value/variable or randomized choice. The list of possible choices and their associated variable/token are managed internally.
 * 
 * Upon deserialization, the action will parse either a variable name or a random range (RANDOM_x), populate the choice list, and select the matching (or random) action to append to its executable subactions.
 * 
 * Inherits from MxDSParallelAction, and extends it to include variable-driven or random action selection. [AI]
 */
class MxDSSelectAction : public MxDSParallelAction {
public:
	/**
	 * @brief [AI] Default constructor. Initializes the object as a select action and allocates the choice string list m_unk0xac.
	 */
	MxDSSelectAction();

	/**
	 * @brief [AI] Copy constructor. Deep-copies the source select action, including string and choice list. [AI]
	 * @param p_dsSelectAction The source select action to copy from. [AI]
	 */
	MxDSSelectAction(MxDSSelectAction& p_dsSelectAction);

	/**
	 * @brief [AI] Destructor. Frees any allocated memory for the internal choice list. [AI]
	 */
	~MxDSSelectAction() override;

	/**
	 * @brief [AI] Copies all internal data from another MxDSSelectAction including string list and selection variable. [AI]
	 * @param p_dsSelectAction The source object to copy from. [AI]
	 */
	void CopyFrom(MxDSSelectAction& p_dsSelectAction);

	/**
	 * @brief [AI] Assignment operator; performs a deep copy of the source select action, including all sub-actions and strings. [AI]
	 * @param p_dsSelectAction The source object to copy from. [AI]
	 * @return Reference to this (assigned) object. [AI]
	 */
	MxDSSelectAction& operator=(MxDSSelectAction& p_dsSelectAction);

	/**
	 * @brief [AI] Returns the class name string for runtime type identification. [AI]
	 * @return Always "MxDSSelectAction". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x1010261c
		return "MxDSSelectAction";
	}

	/**
	 * @brief [AI] Determines if the object is of the specified type or derives from it. [AI]
	 * @param p_name Type/class name to compare against. [AI]
	 * @return True if type matches or is derived, false otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSelectAction::ClassName()) || MxDSParallelAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Computes the total size needed to serialize this object to disk, including selection strings and all choices. [AI]
	 * @details [AI] Sums the base class size, the selection variable/random string, and all items in the string (choice) list.
	 */
	MxU32 GetSizeOnDisk() override;

	/**
	 * @brief [AI] Loads (deserializes) this action from a binary source buffer. [AI]
	 * @details [AI] Parses the selection string, determines selection mechanism (variable or randomized/range), loads the associated list of choices, and then deserializes only the selected child action.
	 * @param p_source Cursor to the start of serialized data. Updated by method. [AI]
	 * @param p_unk0x24 Flags or extra context for deserialization. [AI]
	 */
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;

	/**
	 * @brief [AI] Creates a deep copy ("clone") of this select action, including its internal strings and selected child action(s). [AI]
	 * @return Pointer to the newly allocated clone object. [AI]
	 */
	MxDSAction* Clone() override;

	// SYNTHETIC: LEGO1 0x100cb840
	// SYNTHETIC: BETA10 0x1015b4e0
	// MxDSSelectAction::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Parses from SI chunk: the string name of the selection variable or "RANDOM_n" indicating random selection range.
	 *
	 * For "RANDOM_n", used to generate a random number from 0 to n-1 to select the child action. For other names, consults the VariableTable for a value to match against the choices. [AI]
	 */
	MxString m_unk0x9c;

	/**
	 * @brief [AI] Holds the list of possible choice strings (indices or names) loaded from the SI file.
	 *
	 * Each string corresponds to a key for which there is a corresponding child action in the serialized stream; only the matching action (by value or random) is actually kept as subaction, the rest are deleted. [AI]
	 */
	MxStringList* m_unk0xac;
};

// SYNTHETIC: LEGO1 0x100cbbd0
// SYNTHETIC: BETA10 0x1015bb60
// MxStringListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100cbc40
// TEMPLATE: BETA10 0x1015bba0
// MxListCursor<MxString>::~MxListCursor<MxString>

// SYNTHETIC: LEGO1 0x100cbc90
// SYNTHETIC: BETA10 0x1015bc00
// MxListCursor<MxString>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x100cbd00
// FUNCTION: BETA10 0x1015bc40
// MxStringListCursor::~MxStringListCursor

#endif // MXDSSELECTACTION_H
