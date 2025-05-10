#ifndef MXDSSTILL_H
#define MXDSSTILL_H

#include "mxdsmediaaction.h"

// VTABLE: LEGO1 0x100dce60
// VTABLE: BETA10 0x101c2bf8
// SIZE 0xb8

/**
 * @brief [AI] Represents a "still" media action in the LEGO Island SI script system. [AI]
 * 
 * This class (MxDSStill) is a specialized type of MxDSMediaAction for non-animated (static) images or visual objects 
 * that do not change over time. Its type is set to 'e_still' in the constructor to denote this role. [AI]
 * 
 * It features copying, assignment, runtime class checking, and cloning for duplication within the script and media system. [AI]
 * 
 * @details [AI] MxDSStill objects may be used to handle still image sections in SI (script) files within the LEGO Island engine. [AI]
 */
class MxDSStill : public MxDSMediaAction {
public:
	/**
	 * @brief [AI] Default constructor. Sets the action type to static (still). [AI]
	 */
	MxDSStill();

	/**
	 * @brief [AI] Copy constructor. Performs a deep copy from another MxDSStill. [AI]
	 * @param p_dsStill Reference to the source MxDSStill to copy from. [AI]
	 */
	MxDSStill(MxDSStill& p_dsStill);

	/**
	 * @brief [AI] Destructor. Cleans up resources used by this action. [AI]
	 */
	~MxDSStill() override;

	/**
	 * @brief [AI] Copies the data from another MxDSStill into this instance. [AI]
	 * @param p_dsStill Reference to the source MxDSStill to copy from. [AI]
	 */
	void CopyFrom(MxDSStill& p_dsStill);

	/**
	 * @brief [AI] Assignment operator. Deeply assigns the values from another MxDSStill. [AI]
	 * @param p_dsStill Reference to the source MxDSStill to assign from. [AI]
	 * @return Reference to this updated MxDSStill object (for operator chaining). [AI]
	 */
	MxDSStill& operator=(MxDSStill& p_dsStill);

	/**
	 * @brief [AI] Returns the runtime class name for this object. [AI]
	 * @return String constant: "MxDSStill". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025fc
		return "MxDSStill";
	}

	/**
	 * @brief [AI] Runtime type check against a string name, supports hierarchy checking. [AI]
	 * @param p_name Class name to compare against. [AI]
	 * @return True if this object or its base matches the given class name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSStill::ClassName()) || MxDSMediaAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates a dynamically allocated deep copy of this MxDSStill. [AI]
	 * @details [AI] Used in situations where a duplicate static media action is required, e.g. branching logic in a script. [AI]
	 * @return Pointer to the cloned MxDSStill, or NULL on failure. [AI]
	 */
	MxDSAction* Clone() override; // vtable+0x2c

	// SYNTHETIC: LEGO1 0x100c9a50
	// SYNTHETIC: BETA10 0x1015db50
	// MxDSStill::`scalar deleting destructor'
};

#endif // MXDSSTILL_H