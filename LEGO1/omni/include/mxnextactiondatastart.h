#ifndef MXNEXTACTIONDATASTART_H
#define MXNEXTACTIONDATASTART_H

#include "mxcore.h"

// VTABLE: LEGO1 0x100dc9a0
// VTABLE: BETA10 0x101c26a8
// SIZE 0x14

/**
 * @brief [AI] Contains data for scheduling the next action in a process, storing an object id, a parameter, and an associated data value.
 * @details [AI] MxNextActionDataStart is a simple data-holder class derived from MxCore, used to store information about the start of a future action/command within the LEGO Island action sequence system. It maintains references for the object the action applies to, a secondary parameter (purpose not fully understood in decompiled code), and an additional data field. [AI]
 */
class MxNextActionDataStart : public MxCore {
public:
	/**
	 * @brief [AI] Constructs an MxNextActionDataStart object and initializes its fields.
	 * @param p_objectId [AI] The primary ID for the action's target object (stored in m_objectId).
	 * @param p_unk0x24 [AI] Secondary parameter, possibly an action subtype or control value (stored in m_unk0x24). [AI_SUGGESTED_NAME: actionParameter]
	 * @param p_data [AI] Value used as extra information for the action's execution (stored in m_data).
	 */
	MxNextActionDataStart(MxU32 p_objectId, MxS16 p_unk0x24, MxU32 p_data)
	{
		m_objectId = p_objectId;
		m_unk0x24 = p_unk0x24;
		m_data = p_data;
	}

	/**
	 * @brief [AI] Returns the class name as a constant string.
	 * @return [AI] "MxNextActionDataStart"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025a0
		return "MxNextActionDataStart";
	}

	/**
	 * @brief [AI] Performs runtime type check against class name and all ancestors.
	 * @param p_name [AI] Name to check.
	 * @retval TRUE [AI] If p_name matches this class or MxCore.
	 * @retval FALSE [AI] Otherwise.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxNextActionDataStart::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief [AI] Gets the identifier for the object the action applies to.
	 */
	MxU32 GetObjectId() const { return m_objectId; }

	/**
	 * @brief [AI] Gets the unknown parameter or code for the action (purpose unclear in decompilation output). [AI_SUGGESTED_NAME: GetActionParameter]
	 */
	MxS16 GetUnknown24() const { return m_unk0x24; }

	/**
	 * @brief [AI] Retrieves the extra data associated with the action dispatch.
	 */
	MxU32 GetData() const { return m_data; }

	/**
	 * @brief [AI] Sets the data value for this action instance.
	 * @param p_data [AI] New value for the data field (m_data).
	 */
	void SetData(MxU32 p_data) { m_data = p_data; }

	// SYNTHETIC: LEGO1 0x100c1990
	// MxNextActionDataStart::`scalar deleting destructor'

private:
	MxU32 m_objectId; ///< @brief [AI] Stores the ID of the target object or entity for the next action. [AI]
	MxS16 m_unk0x24;  ///< @brief [AI] Secondary action parameter or metadata (meaning not determined; possibly action type or reference). [AI_SUGGESTED_NAME: m_actionParameter]
	MxU32 m_data;     ///< @brief [AI] Arbitrary data value attached to this action instruction. [AI]
};

#endif // MXNEXTACTIONDATASTART_H
