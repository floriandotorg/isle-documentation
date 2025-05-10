#ifndef MXVARIABLE_H
#define MXVARIABLE_H

#include "mxcore.h"
#include "mxstring.h"

// VTABLE: LEGO1 0x100d7498
// VTABLE: BETA10 0x101bc038
// SIZE 0x24

/**
 * @brief [AI] Represents a key-value variable as used in the variable table for the LEGO Island engine. Keys are always stored in uppercase to ease case-insensitive lookups. [AI]
 * 
 * @details [AI] This class encapsulates a variable with a string key and string value. It is used as the primary storage element for the game's variable table system (see MxVariableTable), with utility methods for setting and getting the variable's value. Keys are always uppercased when set to ensure consistency throughout the engine. [AI]
 */
class MxVariable {
public:
	/**
	 * @brief [AI] Constructs an empty variable with no key or value. [AI]
	 */
	MxVariable() {}

	/**
	 * @brief [AI] Constructs a variable with the specified key and value. The key is uppercased. [AI]
	 * @param p_key The variable name or key. [AI]
	 * @param p_value The variable value. [AI]
	 * @details [AI] The variable name is converted to uppercase to support case-insensitive storage and lookup. [AI]
	 */
	MxVariable(const char* p_key, const char* p_value)
	{
		m_key = p_key;
		m_key.ToUpperCase();
		m_value = p_value;
	}

	/**
	 * @brief [AI] Constructs a variable with the specified key and no value. The key is uppercased. [AI]
	 * @param p_key The variable name or key. [AI]
	 * @details [AI] The variable name is converted to uppercase. The value will be empty. [AI]
	 */
	MxVariable(const char* p_key)
	{
		m_key = p_key;
		m_key.ToUpperCase();
	}

	/**
	 * @brief [AI] Retrieves a pointer to the variable's value. [AI]
	 * @return Pointer to the value string. [AI]
	 * @details [AI] Returns a pointer so that value manipulation can occur directly. [AI]
	 */
	virtual MxString* GetValue() { return &m_value; } // vtable+0x00

	/**
	 * @brief [AI] Sets the variable's value. [AI]
	 * @param p_value New value to assign. [AI]
	 * @details [AI] The value is replaced, not appended. [AI]
	 */
	virtual void SetValue(const char* p_value) { m_value = p_value; } // vtable+0x04

	/**
	 * @brief [AI] Destroys the variable, deleting the object. [AI]
	 * @details [AI] Used to delete the dynamically allocated MxVariable. [AI]
	 */
	virtual void Destroy() { delete this; } // vtable+0x08

	/**
	 * @brief [AI] Provides read-only access to the variable's key/name. [AI]
	 * @return Pointer to the key string. [AI]
	 */
	const MxString* GetKey() const { return &m_key; }

protected:
	/**
	 * @brief [AI] The variable's key (name), always stored in uppercase. [AI]
	 */
	MxString m_key;   // 0x04

	/**
	 * @brief [AI] The variable's value. [AI]
	 */
	MxString m_value; // 0x14
};

// SYNTHETIC: LEGO1 0x1003bf40
// MxVariable::~MxVariable

#endif // MXVARIABLE_H
