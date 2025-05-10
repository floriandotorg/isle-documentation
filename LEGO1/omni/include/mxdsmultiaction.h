#ifndef MXDSMULTIACTION_H
#define MXDSMULTIACTION_H

#include "mxdsaction.h"
#include "mxdsactionlist.h"

// VTABLE: LEGO1 0x100dcef0
// VTABLE: BETA10 0x101c28b0
// SIZE 0x9c
/**
 * @brief [AI] Represents a container for multiple MxDSAction objects, facilitating the grouping and management of several actions as a single entity.
 * @details [AI] MxDSMultiAction acts as a composite DS action that can hold and execute a list of sub-actions (subclassed from MxDSAction). It handles serialization, deserialization, cloning, merging, and id management centrally for all contained actions. Used for composite instructions in the LEGO Island scripting system. [AI]
 */
class MxDSMultiAction : public MxDSAction {
public:
	/**
	 * @brief [AI] Constructs an MxDSMultiAction, initializing its type and instantiating an empty action list.
	 */
	MxDSMultiAction();

	/**
	 * @brief [AI] Copy constructor for MxDSMultiAction, performing a deep copy of all actions in the source list.
	 * @param p_dsMultiAction The source MxDSMultiAction to copy from. [AI]
	 */
	MxDSMultiAction(MxDSMultiAction& p_dsMultiAction);

	/**
	 * @brief [AI] Destructor. Deletes all underlying MxDSAction objects in the contained list.
	 */
	~MxDSMultiAction() override;

	/**
	 * @brief [AI] Deeply copies all actions from another MxDSMultiAction.
	 * @param p_dsMultiAction Source for the deep copy operation. [AI]
	 * @details [AI] Any existing actions are deleted and replaced with deep clones of those in the source. Used by assignment and copy construction. [AI]
	 */
	void CopyFrom(MxDSMultiAction& p_dsMultiAction);

	/**
	 * @brief [AI] Assignment operator, deeply copies all state and actions from another MxDSMultiAction.
	 * @param p_dsMultiAction The source of the assignment. [AI]
	 * @return Reference to this instance (for chaining). [AI]
	 * @details [AI] Differs from a shallow copy: also duplicates each contained MxDSAction by cloning. Avoids self-assignment. [AI]
	 */
	MxDSMultiAction& operator=(MxDSMultiAction& p_dsMultiAction);

	/**
	 * @brief [AI] Returns the class name for this object ("MxDSMultiAction").
	 * @return Class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10101dbc
		return "MxDSMultiAction";
	}

	/**
	 * @brief [AI] Checks whether a given class name matches this or any parent class.
	 * @param p_name Name of the class to check. [AI]
	 * @return True if the name matches MxDSMultiAction or any superclass, otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSMultiAction::ClassName()) || MxDSAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Hook for vtable entry 0x14. Implementation is mostly unknown.
	 * @return Undefined 4-byte value [AI]
	 * @details [AI] Implementation iterates over all actions, invoking VTable0x14 on each and aggregating the results. [AI]
	 */
	undefined4 VTable0x14() override;

	/**
	 * @brief [AI] Calculates the total disk size occupied by this multi-action and all its subactions.
	 * @return Combined file storage size in bytes. [AI]
	 * @details [AI] Iterates through the contained action list, summing each subaction's disk size plus metadata. [AI]
	 */
	MxU32 GetSizeOnDisk() override;

	/**
	 * @brief [AI] Reads the object's data from a raw byte buffer.
	 * @param p_source Reference to pointer for source byte stream (advanced during read) [AI]
	 * @param p_unk0x24 Context/flags coming from caller. [AI]
	 * @details [AI] Deserializes the action's own data, then the list of sub-actions in sequence using the dispatch mechanism. [AI]
	 */
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;

	/**
	 * @brief [AI] Propagates the given AtomId to this and all subactions.
	 * @param p_atomId The AtomId to set. [AI]
	 */
	void SetAtomId(MxAtomId p_atomId) override;

	/**
	 * @brief [AI] Constructs a deep clone of this multi-action, including all subactions.
	 * @return Pointer to the new deep copy clone. [AI]
	 */
	MxDSAction* Clone() override;

	/**
	 * @brief [AI] Propagates a merge operation from the provided MxDSAction to all subactions, as well as self.
	 * @param p_dsAction The source action for merging. [AI]
	 * @details [AI] Useful for accumulating/deserializing multiple actions into a single structure hierarchically. [AI]
	 */
	void MergeFrom(MxDSAction& p_dsAction) override;

	/**
	 * @brief [AI] Returns whether this action or any contained subaction matches the provided object id.
	 * @param p_objectId The unique id to check. [AI]
	 * @return True if found, otherwise false. [AI]
	 */
	MxBool HasId(MxU32 p_objectId) override;

	/**
	 * @brief [AI] Propagates an unknown value to this and all subactions.
	 * @param p_unk0x90 The value to set (purpose unclear, but typically a state or context value). [AI]
	 */
	void SetUnknown90(MxLong p_unk0x90) override;

	/**
	 * @brief [AI] Returns the internal action list holding all subactions of this multi-action.
	 * @return Pointer to the contained MxDSActionList. [AI]
	 */
	MxDSActionList* GetActionList() const { return m_actionList; }

	// SYNTHETIC: LEGO1 0x100ca040
	// SYNTHETIC: BETA10 0x1015b210
	// MxDSMultiAction::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Stores the last-computed disk storage size for m_actionList and metadata.
	 * @details [AI] Updated when GetSizeOnDisk() is called. Used to optimize serialization. [AI]
	 */
	MxU32 m_sizeOnDisk;           // 0x94

	/**
	 * @brief [AI] List of contained actions (ownership: this owns and deletes subactions).
	 */
	MxDSActionList* m_actionList; // 0x98

};

// SYNTHETIC: LEGO1 0x1004ad10
// SYNTHETIC: BETA10 0x1004dc50
// MxDSActionListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1004ad80
// TEMPLATE: BETA10 0x1004dca0
// MxListCursor<MxDSAction *>::~MxListCursor<MxDSAction *>

// SYNTHETIC: LEGO1 0x1004add0
// SYNTHETIC: BETA10 0x1004dd20
// MxListCursor<MxDSAction *>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1004ae40
// FUNCTION: BETA10 0x1004dd70
// MxDSActionListCursor::~MxDSActionListCursor

#endif // MXDSMULTIACTION_H
