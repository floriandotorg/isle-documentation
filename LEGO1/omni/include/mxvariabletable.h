#ifndef MXVARIABLETABLE_H
#define MXVARIABLETABLE_H

#include "mxhashtable.h"
#include "mxtypes.h"
#include "mxvariable.h"

// VTABLE: LEGO1 0x100dc1c8
// VTABLE: BETA10 0x101c1c78
// SIZE 0x28

/**
 * @brief MxVariableTable is a specialized hash table for storing key/value string variables used by the LEGO Island engine.
 * [AI]
 * @details [AI]
 * MxVariableTable manages a table of MxVariable pointers, each storing a string key and a string value.
 * It provides methods to set and get variables by key, and uses custom hash and comparison functions for efficient lookups.
 * The engine uses this system as the "variable table" found on MxOmni and scripting components, usually for storing game, script or global state variables at runtime.
 */
class MxVariableTable : public MxHashTable<MxVariable*> {
public:
	/**
	 * @brief Constructs an MxVariableTable and sets up the element destroy function. [AI]
	 */
	MxVariableTable() { SetDestroy(Destroy); }
	
	/**
	 * @brief Sets a variable by key and value, replacing or updating if it exists. [AI]
	 * @param p_key Variable key. [AI]
	 * @param p_value Variable value. [AI]
	 * @details [AI] If a variable with the specified key already exists, its value will be replaced. Otherwise, a new variable entry is created and inserted.
	 */
	void SetVariable(const char* p_key, const char* p_value);

	/**
	 * @brief Sets the given MxVariable pointer in the table, deleting any existing entry with the same key. [AI]
	 * @param p_var Pointer to an MxVariable object to be inserted or replaced in the table. [AI]
	 * @details [AI] If a variable with the same key already exists, it will be removed and deleted. The new variable is then inserted.
	 */
	void SetVariable(MxVariable* p_var);

	/**
	 * @brief Returns the value for the variable with a given key, or an empty string if not found. [AI]
	 * @param p_key Key to look up. [AI]
	 * @return const char* Value string of the variable, or "" if the key is not defined. [AI]
	 * @details [AI] Ownership of the returned string remains with the table, do not free.
	 */
	const char* GetVariable(const char* p_key);

	/**
	 * @brief Destroys an instance of MxVariable, calling its Destroy method. [AI]
	 * @param p_obj Pointer to the MxVariable to destroy. [AI]
	 * @details [AI] Used by the hash table to clean up elements automatically on removal or destruction.
	 * Note: This does not delete p_obj itself; the object should be deleted separately as needed.
	 */
	static void Destroy(MxVariable* p_obj) { p_obj->Destroy(); }

	/**
	 * @brief Implements the virtual table comparison for two MxVariable pointers.
	 * [AI]
	 * @param [in] [AI] First MxVariable pointer.
	 * @param [in] [AI] Second MxVariable pointer.
	 * @return MxS8 Result of the comparison: usually <0, 0, >0 as per standard compare.
	 * @details [AI] Compares the key strings via MxString::Compare. Used to determine equality or ordering in the hash table.
	 */
	MxS8 Compare(MxVariable*, MxVariable*) override; // vtable+0x14

	/**
	 * @brief Hashes the key of the given variable for use in the table. [AI]
	 * @param [in] [AI] Pointer to MxVariable to hash.
	 * @return MxU32 The calculated hash value based on its key. [AI]
	 * @details [AI] Sums the ASCII values of all characters in the key string.
	 */
	MxU32 Hash(MxVariable*) override; // vtable+0x18

	// SYNTHETIC: destructor and other template methods managed by base class
};

// VTABLE: LEGO1 0x100dc1b0
// VTABLE: BETA10 0x101c1cd0
// class MxCollection<MxVariable *>

// VTABLE: LEGO1 0x100dc1e8
// VTABLE: BETA10 0x101c1cb0
// class MxHashTable<MxVariable *>

// VTABLE: LEGO1 0x100dc680
// VTABLE: BETA10 0x101c1b48
// class MxHashTableCursor<MxVariable *>

// TEMPLATE: LEGO1 0x100afcd0
// TEMPLATE: BETA10 0x10132950
// MxCollection<MxVariable *>::Compare

// TEMPLATE: LEGO1 0x100afce0
// TEMPLATE: BETA10 0x10132a00
// MxCollection<MxVariable *>::~MxCollection<MxVariable *>

// TEMPLATE: LEGO1 0x100afd30
// TEMPLATE: BETA10 0x10132a70
// MxCollection<MxVariable *>::Destroy

// SYNTHETIC: LEGO1 0x100afd40
// SYNTHETIC: BETA10 0x10132a80
// MxCollection<MxVariable *>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100afdc0
// TEMPLATE: BETA10 0x10132ac0
// MxHashTable<MxVariable *>::Hash

// TEMPLATE: LEGO1 0x100b0bd0
// TEMPLATE: BETA10 0x10132ae0
// MxHashTable<MxVariable *>::~MxHashTable<MxVariable *>

// SYNTHETIC: LEGO1 0x100b0ca0
// SYNTHETIC: BETA10 0x10132b70
// MxHashTable<MxVariable *>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100b7680
// TEMPLATE: BETA10 0x1012a990
// MxHashTableCursor<MxVariable *>::~MxHashTableCursor<MxVariable *>

// SYNTHETIC: LEGO1 0x100b76d0
// SYNTHETIC: BETA10 0x1012a9f0
// MxHashTableCursor<MxVariable *>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100b7ab0
// TEMPLATE: BETA10 0x1012adc0
// MxHashTable<MxVariable *>::Resize

// TEMPLATE: LEGO1 0x100b7b80
// TEMPLATE: BETA10 0x1012af10
// MxHashTable<MxVariable *>::NodeInsert

// TEMPLATE: BETA10 0x1012a900
// MxHashTableCursor<MxVariable *>::MxHashTableCursor<MxVariable *>

// TEMPLATE: BETA10 0x1012aae0
// MxHashTable<MxVariable *>::Add

// TEMPLATE: BETA10 0x1012abd0
// MxHashTableCursor<MxVariable *>::Current

// TEMPLATE: BETA10 0x1012ac20
// MxHashTableCursor<MxVariable *>::DeleteMatch

// TEMPLATE: BETA10 0x1012ad00
// MxHashTableCursor<MxVariable *>::Find

// TEMPLATE: BETA10 0x1012af90
// MxHashTableNode<MxVariable *>::MxHashTableNode<MxVariable *>

// TEMPLATE: BETA10 0x10132890
// MxHashTable<MxVariable *>::MxHashTable<MxVariable *>

// TEMPLATE: BETA10 0x10130ed0
// MxCollection<MxVariable *>::SetDestroy

// SYNTHETIC: BETA10 0x10130f60
// MxVariableTable::~MxVariableTable

// SYNTHETIC: BETA10 0x10132970
// MxCollection<MxVariable *>::MxCollection<MxVariable *>

// TEMPLATE: BETA10 0x10132bb0
// MxHashTable<MxVariable *>::DeleteAll

#endif // MXVARIABLETABLE_H
