#ifndef MXDSOBJECTACTION_H
#define MXDSOBJECTACTION_H

#include "mxdsmediaaction.h"

// VTABLE: LEGO1 0x100dccf8
// VTABLE: BETA10 0x101c2a90
// SIZE 0xb8

/**
 * @brief [AI] Represents an extracted SI file action of type "ObjectAction".
 * @details [AI] This class is a specialized DSAction that represents an object action extracted from an SI file, forming part of the game's script object hierarchy. It doesn't add extra members but enables polymorphic handling and type discrimination of DSMediaActions which be associated with objects or scripted entities in LEGO Island. [AI]
 */
class MxDSObjectAction : public MxDSMediaAction {
public:
	/**
	 * @brief [AI] Constructs an uninitialized MxDSObjectAction object.
	 * @details [AI] Sets m_type to e_objectAction to mark this instance as an object action for later differentiation within the action system. [AI]
	 */
	MxDSObjectAction();

	/**
	 * @brief [AI] Copy-constructor for MxDSObjectAction.
	 * @details [AI] Constructs a new MxDSObjectAction as a copy of the provided one, duplicating all relevant members. [AI]
	 * @param p_dsObjectAction The object to copy from. [AI]
	 */
	MxDSObjectAction(MxDSObjectAction& p_dsObjectAction);

	/**
	 * @brief [AI] Destroys the MxDSObjectAction object.
	 * @details [AI] Destructor for proper cleanup of MxDSObjectAction. [AI]
	 */
	~MxDSObjectAction() override;

	/**
	 * @brief [AI] Assignment operator for MxDSObjectAction.
	 * @details [AI] Copies the contents from another MxDSObjectAction into this instance, using base and member-wise assignment and copying all relevant data. [AI]
	 * @param p_dsObjectAction The object to assign from. [AI]
	 * @return Reference to this MxDSObjectAction. [AI]
	 */
	MxDSObjectAction& operator=(MxDSObjectAction& p_dsObjectAction);

	/**
	 * @brief [AI] Returns the class name for run-time type identification.
	 * @details [AI] Used by the internal type-checking system, returns the type name string "MxDSObjectAction". [AI]
	 * @return Constant string literal representing the class name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025c4
		return "MxDSObjectAction";
	}

	/**
	 * @brief [AI] Checks whether this object matches the provided type name.
	 * @details [AI] Enables run-time polymorphic type checks. Checks if the given name matches this class or any parent class in the hierarchy. [AI]
	 * @param p_name Class name to check against. [AI]
	 * @return True if the object conforms to the given type, otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSObjectAction::ClassName()) || MxDSMediaAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates a polymorphic clone (deep copy) of this action.
	 * @details [AI] Implements the clone protocol for script actions, returning a new heap-allocated instance with all properties copied. [AI]
	 */
	MxDSAction* Clone() override;                              // vtable+0x2c

	/**
	 * @brief [AI] Copies all relevant members from another object of the same type.
	 * @details [AI] Used internally for cloning and assignment; copies any extended fields from the source, if applicable. [AI]
	 * @param p_dsObjectAction Source object to copy from. [AI]
	 */
	virtual void CopyFrom(MxDSObjectAction& p_dsObjectAction); // vtable+0x44

	// SYNTHETIC: LEGO1 0x100c8a00
	// SYNTHETIC: BETA10 0x1015c720
	// MxDSObjectAction::`scalar deleting destructor'
};

#endif // MXDSOBJECTACTION_H
