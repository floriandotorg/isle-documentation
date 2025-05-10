#ifndef MXENTITY_H
#define MXENTITY_H

#include "decomp.h"
#include "mxatom.h"
#include "mxcore.h"
#include "mxdsaction.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d5390 [AI]
// VTABLE: BETA10 0x101b93e8 [AI]
// SIZE 0x10 [AI]

/**
 * @brief MxEntity is a base class for game entities which are uniquely identified
 * by an integer ID and an AtomId. [AI]
 * @details [AI] MxEntity provides a unified interface for all world entities and 
 * supplies mechanisms for type information, unique identity, and entity initialization
 * from basic parameters or from a data action (MxDSAction). Used as an ancestor for 
 * most LEGO Island actor and entity classes.
 */
class MxEntity : public MxCore {
public:
	/**
	 * @brief Default constructor. Initializes entity ID to -1 (invalid). [AI]
	 */
	// FUNCTION: LEGO1 0x1001d190 [AI]
	MxEntity() { m_entityId = -1; }

	/**
	 * @brief Virtual destructor for MxEntity. [AI]
	 */
	// FUNCTION: LEGO1 0x1000c110 [AI]
	~MxEntity() override {}

	/**
	 * @brief Returns the class name for type introspection. [AI]
	 * @return String literal "MxEntity" [AI]
	 */
	// FUNCTION: LEGO1 0x1000c180 [AI]
	// FUNCTION: BETA10 0x10012700 [AI]
	const char* ClassName() const override // vtable+0x0c [AI]
	{
		// STRING: LEGO1 0x100f0070 [AI]
		return "MxEntity";
	}

	/**
	 * @brief Checks if the object is of the given class name or a parent type. [AI]
	 * @param p_name The class name to compare against. [AI]
	 * @details [AI] Returns true if the name matches the MxEntity class or matches any
	 * parent class via MxCore::IsA.
	 */
	// FUNCTION: LEGO1 0x1000c190 [AI]
	// FUNCTION: BETA10 0x10012610 [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10 [AI]
	{
		return !strcmp(p_name, MxEntity::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief Initializes the entity from a given entity ID and AtomId. [AI]
	 * @param p_entityId The integer entity ID to assign. [AI]
	 * @param p_atomId The AtomId to assign. [AI]
	 * @return SUCCESS on completion. [AI]
	 */
	// FUNCTION: LEGO1 0x10001070 [AI]
	// FUNCTION: BETA10 0x1000f3a0 [AI]
	virtual MxResult Create(MxS32 p_entityId, const MxAtomId& p_atomId)
	{
		m_entityId = p_entityId;
		m_atomId = p_atomId;
		return SUCCESS;
	} // vtable+0x14 [AI]

	/**
	 * @brief Initializes the entity from a MxDSAction object. [AI]
	 * @param p_dsAction Reference to action with object identification data. [AI]
	 * @return SUCCESS on completion. [AI]
	 * @details [AI] Sets m_entityId and m_atomId to the values from the DSAction.
	 */
	MxResult Create(MxDSAction& p_dsAction)
	{
		m_entityId = p_dsAction.GetObjectId();
		m_atomId = p_dsAction.GetAtomId();
		return SUCCESS;
	}

	/**
	 * @brief Returns the current entity ID. [AI]
	 */
	// FUNCTION: BETA10 0x10031c60 [AI]
	MxS32 GetEntityId() { return m_entityId; }

	/**
	 * @brief Returns a reference to the entity AtomId. [AI]
	 */
	MxAtomId& GetAtomId() { return m_atomId; }

	/**
	 * @brief Sets the entity ID to the given value. [AI]
	 * @param p_entityId New ID value to set. [AI]
	 */
	void SetEntityId(MxS32 p_entityId) { m_entityId = p_entityId; }
	
	/**
	 * @brief Sets the AtomId to the given value. [AI]
	 * @param p_atomId Value to assign to m_atomId. [AI]
	 */
	void SetAtomId(const MxAtomId& p_atomId) { m_atomId = p_atomId; }

	// SYNTHETIC: LEGO1 0x1000c210 [AI]
	// MxEntity::`scalar deleting destructor' [AI]

protected:
	/**
	 * @brief The unique entity ID, typically used for lookup and reference. [AI]
	 */
	MxS32 m_entityId;  // 0x08 [AI]

	/**
	 * @brief The AtomId associated with this entity, used for resource and script identification. [AI]
	 */
	MxAtomId m_atomId; // 0x0c [AI]
};

#endif // MXENTITY_H
