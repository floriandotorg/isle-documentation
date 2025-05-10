#ifndef MXATOM_H
#define MXATOM_H

#include "mxstl/stlcompat.h"
#include "mxstring.h"
#include "mxtypes.h"

// [AI] MxAtom, MxAtomId and supporting structures are used for efficient string-to-identifier mapping (atomization), 
// tracking the existence and use-counts of strings for reuse across the application.

// Counts the number of existing MxAtomId objects based
// on the matching char* string. A <map> seems fit for purpose here:
// We have an MxString as a key and MxU16 as the value.
// And yet a <set> is the best match. The malloc in MxOmni::Create
// for the _Nil node asks for more bytes than a regular node if a <map>
// is used, but all nodes are 20 bytes wide with a <set>.
// Also: the increment/decrement methods suggest a custom type was used
// for the combined key_value_pair, which doesn't seem possible with <map>.

// SIZE 0x14
/**
 * @brief [AI] Key-value pair representing a unique string (atom) and its reference count.
 *
 * MxAtom is used to atomize strings by acting as a string (the key part) that registers how many times 
 * the same atomization key is in use (the value part, which functions as a reference counter). 
 * When used via MxAtomId, the reference count is incremented or decremented depending on the MxAtomId's lifecycle. 
 * MxAtom objects are managed in a globally accessible set for uniqueness.
 * 
 * @details [AI] The combination of MxString and a usage count (MxU16) enables memory-efficient reuse of string values 
 * that act as IDs or keys and effective cleanup when no longer referenced. The inlined constructor always initializes 
 * the usage count to zero.
 */
class MxAtom {
public:
	// always inlined
	// FUNCTION: BETA10 0x10123720
	/**
	 * @brief [AI] Constructs an MxAtom with the given string as the key.
	 * @param p_str [AI] String to be used as the unique key for this atom.
	 */
	MxAtom(const char* p_str)
	{
		m_key = p_str;
		m_value = 0;
	}

	/**
	 * @brief [AI] Increments the usage count for this atom, indicating one more client is using it.
	 * @details [AI] Used by MxAtomId when new IDs referencing this atom are created.
	 */
	void Inc();

	/**
	 * @brief [AI] Decrements the usage count for this atom.
	 * @details [AI] When the count reaches zero, this atom may be considered unused and ready for cleanup.
	 */
	void Dec();

	// FUNCTION: BETA10 0x101236d0
	/**
	 * @brief [AI] Gets the atom key (the string stored in this atom).
	 * @return MxString& Reference to the internal string key. [AI]
	 */
	MxString& GetKey() { return m_key; }

	// SYNTHETIC: BETA10 0x10124a50
	// MxAtom::`scalar deleting destructor'

private:
	MxString m_key; ///< [AI] The unique string key for this atom.
	MxU16 m_value;  ///< [AI] Usage count indicating how many references are using this atom.
};

/**
 * @brief [AI] Functor for comparing two MxAtom pointers based on their keys (strings).
 * @details [AI] Used as the comparator for sets of MxAtom pointers (e.g., in MxAtomSet),
 * ensuring uniqueness in the atom set and enabling efficient lookup.
 */
struct MxAtomCompare {
	// FUNCTION: LEGO1 0x100ad120
	// FUNCTION: BETA10 0x10123980
	/**
	 * @brief [AI] Compares two atom pointers lexicographically by their string keys.
	 * @param p_val0 [AI] First atom pointer.
	 * @param p_val1 [AI] Second atom pointer.
	 * @return int [AI] Returns true if p_val0 is ordered after p_val1 (for std::set ordering).
	 */
	int operator()(MxAtom* const& p_val0, MxAtom* const& p_val1) const
	{
		return strcmp(p_val0->GetKey().GetData(), p_val1->GetKey().GetData()) > 0;
	}
};

/**
 * @brief [AI] Set of unique atom pointers, managed with custom comparison for atomization and fast lookup.
 * @details [AI] Used as the backing container for all unique strings (atoms) in the application.
 */
class MxAtomSet : public set<MxAtom*, MxAtomCompare> {};

/**
 * @brief [AI] Lookup mode used to control case sensitivity and normalization when atomizing strings.
 * @details [AI] Indicates what transformations (such as uppercase, lowercase, or none) should be performed
 * when generating or comparing atom IDs.
 */
enum LookupMode {
	e_exact = 0,      ///< [AI] Match the string exactly, no case change.
	e_lowerCase,      ///< [AI] Convert the string to lower case before matching/creating.
	e_upperCase,      ///< [AI] Convert the string to upper case before matching/creating.
	e_lowerCase2,     ///< [AI] Alternative or legacy lower case mode, functionally equivalent to e_lowerCase.
};

// SIZE 0x04
/**
 * @brief [AI] Atomized (unique) string identifier, managed by reference counting.
 *
 * MxAtomId refers to a unique key in the global atom set, and increments/decrements the reference count
 * on construction/destruction and assignment. It abstracts away pointer- or string-based identifier usage, 
 * guarantees uniqueness and lifetime management, and can be compared for equality.
 *
 * @details [AI] Used throughout the engine to efficiently manage string IDs for resources, scripts, events, and more. 
 * The internal value (m_internal) is a const char* to the internal string, guaranteed to remain valid as long as at least 
 * one MxAtomId refers to it.
 */
class MxAtomId {
public:
	/**
	 * @brief [AI] Constructs an atom ID for the given string and lookup mode, increments atom reference count.
	 * @param [in] char* The string value to atomize.
	 * @param [in] LookupMode Lookup mode (case normalization, etc.).
	 */
	MxAtomId(const char*, LookupMode);

	/**
	 * @brief [AI] Destructor for atom ID. Decrements the reference count for the referenced atom.
	 */
	~MxAtomId();

	/**
	 * @brief [AI] Copy assignment operator. 
	 * Decreases reference to current atom if needed, increases reference for the new atom.
	 * @param p_atomId [AI] The source to assign from.
	 * @return MxAtomId& Reference to this atom ID after assignment. [AI]
	 */
	MxAtomId& operator=(const MxAtomId& p_atomId);

	// FUNCTION: BETA10 0x100178d0
	/**
	 * @brief [AI] Tests for equality with another atom ID based on the internal string pointer.
	 * @param p_atomId [AI] Atom ID to compare to.
	 * @return MxBool True if atom IDs refer to the same string atom. [AI]
	 */
	MxBool operator==(const MxAtomId& p_atomId) const { return this->m_internal == p_atomId.m_internal; }

#ifdef COMPAT_MODE
	// Required for modern compilers.
	// MSVC 4.20 uses a synthetic function from INCLUDE/UTILITY that inverts operator==
	/**
	 * @brief [AI] Tests for inequality with another atom ID.
	 * @param p_atomId [AI] Atom ID to compare to.
	 * @return MxBool True if atom IDs refer to different string atoms. [AI]
	 */
	MxBool operator!=(const MxAtomId& p_atomId) const { return this->m_internal != p_atomId.m_internal; }
#endif

	// TODO:
	// BETA10 0x1007dc20 operator==
	// BETA10 0x10096970 operator!=

	// FUNCTION: BETA10 0x10146dd0
	/**
	 * @brief [AI] Tests equality against a raw string, using a direct string comparison.
	 * @param p_internal [AI] String to compare to the atom's internal string.
	 * @return MxBool True if the atom's stored string matches p_internal. [AI]
	 */
	MxBool operator==(const char* p_internal) const { return p_internal && !strcmp(m_internal, p_internal); }

	// FUNCTION: BETA10 0x10025d40
	/**
	 * @brief [AI] Constructs a null/empty atom ID.
	 * @details [AI] Initializes the atom id to not refer to any atomized string.
	 */
	MxAtomId() { this->m_internal = 0; }

	/**
	 * @brief [AI] Disassociates the atom ID from any atom (decrements reference count, sets internal pointer to NULL).
	 */
	void Clear();

	// FUNCTION: BETA10 0x100735e0
	/**
	 * @brief [AI] Returns a pointer to the internal string, or nullptr if not set.
	 * @return const char* Internal string pointer. [AI]
	 */
	const char* GetInternal() const { return m_internal; }

private:
	// FUNCTION: BETA10 0x101236f0
	/**
	 * @brief [AI] Assigns this atom id from an MxString, adjusting reference counts accordingly.
	 * @param p_key [AI] The string to use as the new key.
	 * @return MxAtomId& Reference to this atom ID. [AI]
	 */
	MxAtomId& operator=(const MxString& p_key)
	{
		m_internal = p_key.GetData();
		return *this;
	}

	/**
	 * @brief [AI] Looks up or creates an atom for the given string and lookup mode.
	 * @param [in] char* String to atomize.
	 * @param [in] LookupMode Lookup mode (case sensitivity/normalization).
	 * @return MxAtom* Pointer to the found or created atom. [AI]
	 */
	MxAtom* GetAtom(const char*, LookupMode);

	/**
	 * @brief [AI] Decreases reference on the currently held atom. Called before reassignment/destruction/clearing.
	 */
	void Destroy();

	const char* m_internal; ///< [AI] Pointer to the internal atomized string, guaranteed unique.
};

#endif // MXATOM_H
