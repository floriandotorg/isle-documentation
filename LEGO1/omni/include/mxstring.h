#ifndef MXSTRING_H
#define MXSTRING_H

#include "mxcore.h"

// VTABLE: LEGO1 0x100dc110
// VTABLE: BETA10 0x101c1be0
// SIZE 0x10

/**
 * @brief  Mindscape custom string class for managing dynamic C-strings within the game engine. [AI]
 * @details Provides operations like construction from C-strings or other MxString instances, mutation utilities (reverse, uppercase, lowercase), and concatenation and comparison. Handles dynamic memory for string contents. [AI]
 */
class MxString : public MxCore {
public:
	/**
	 * @brief Default constructor which creates an empty string. [AI]
	 * @details Allocates memory for a null-terminated string of zero length. [AI]
	 */
	MxString();

	/**
	 * @brief Copy constructor. [AI]
	 * @param p_str Reference to another MxString to copy. [AI]
	 */
	MxString(const MxString& p_str);

	/**
	 * @brief Constructs MxString from a C-style string. [AI]
	 * @param p_str Null-terminated input string. [AI]
	 */
	MxString(const char* p_str);

	/**
	 * @brief Constructs MxString from a C-style string with maximum length. [AI]
	 * @param p_str Null-terminated input string. [AI]
	 * @param p_maxlen Maximum number of characters to copy. [AI]
	 * @details If the input string is longer than p_maxlen, only the first p_maxlen characters are used. [AI]
	 */
	MxString(const char* p_str, MxU16 p_maxlen);

	/**
	 * @brief Destructor. [AI]
	 * @details Releases allocated memory for string buffer. [AI]
	 */
	~MxString() override;

	/**
	 * @brief Reverses the contents of the string in-place. [AI]
	 */
	void Reverse();

	/**
	 * @brief Converts the string contents to uppercase in-place. [AI]
	 */
	void ToUpperCase();

	/**
	 * @brief Converts the string contents to lowercase in-place. [AI]
	 */
	void ToLowerCase();

	/**
	 * @brief Assignment operator from another MxString. [AI]
	 * @param p_str Source MxString to copy from. [AI]
	 * @details Allocates a new buffer and copies the string data. Handles self-assignment check. [AI]
	 */
	MxString& operator=(const MxString& p_str);

	/**
	 * @brief Assignment operator from a null-terminated C-string. [AI]
	 * @param p_str Source C-string to copy from. [AI]
	 * @details Allocates a new buffer and copies the input string. Handles self-assignment check. [AI]
	 */
	const MxString& operator=(const char* p_str);

	/**
	 * @brief Concatenation operator for two MxString instances. [AI]
	 * @param p_str Input string to concatenate. [AI]
	 * @details Returns a new MxString containing the concatenation result. [AI]
	 */
	MxString operator+(const MxString& p_str) const;

	/**
	 * @brief Concatenation operator for MxString and a C-string. [AI]
	 * @param p_str C-style string to append to this instance. [AI]
	 * @details Returns a new MxString containing the concatenation result. [AI]
	 */
	MxString operator+(const char* p_str) const;

	/**
	 * @brief Append a C-string to this MxString. [AI]
	 * @param p_str C-style null-terminated string to append. [AI]
	 * @details Adjusts the internal buffer and length. [AI]
	 */
	MxString& operator+=(const char* p_str);

	/**
	 * @brief Utility to swap the values of two characters. [AI]
	 * @param p_a Pointer to first character. [AI]
	 * @param p_b Pointer to second character. [AI]
	 * @details Used internally for string reversal. [AI]
	 */
	static void CharSwap(char* p_a, char* p_b);

	/**
	 * @brief Returns a pointer to the internal character buffer. [AI]
	 * @details The returned pointer is owned by MxString and should not be freed by the caller. [AI]
	 */
	char* GetData() const { return m_data; }

	/**
	 * @brief Returns the length of the string (number of characters, not including null terminator). [AI]
	 */
	const MxU16 GetLength() const { return m_length; }

	/**
	 * @brief Compares this string to another for equality. [AI]
	 * @param p_str String to compare against. [AI]
	 * @retval TRUE if the contents are exactly equal, FALSE otherwise ([AI], returns MxBool). [AI]
	 */
	MxBool Equal(const MxString& p_str) const { return strcmp(m_data, p_str.m_data) == 0; }

	/**
	 * @brief Performs lexicographical comparison to another string. [AI]
	 * @param p_str String to compare against. [AI]
	 * @return 0 if equal; <0 if this < p_str; >0 if this > p_str (using strcmp convention). [AI]
	 */
	MxS8 Compare(const MxString& p_str) const { return strcmp(m_data, p_str.m_data); }

	// SYNTHETIC: LEGO1 0x100ae280
	// SYNTHETIC: BETA10 0x1012c9d0
	// MxString::`scalar deleting destructor'

private:
	char* m_data;   ///< @brief Internal pointer to the dynamically allocated character buffer. [AI]
	MxU16 m_length; ///< @brief Length of the string, not including the null terminator. [AI]
};

#endif // MXSTRING_H
