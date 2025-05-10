#ifndef MXLIST_H
#define MXLIST_H

#include "mxcollection.h"
#include "mxcore.h"
#include "mxtypes.h"

/// [AI] Forward declaration for MxList.
template <class T>
class MxList; // [AI] Used for type-safe linked list implementation.

/// [AI] Forward declaration for MxListCursor.
template <class T>
class MxListCursor; // [AI] Iterator-like class for traversing/operating on MxList.

/// [AI]
/// @brief Represents a node in a doubly-linked list. [AI]
/// @details [AI] Contains value, next and previous node pointers for building a doubly-linked list. Used internally by MxList and its derivatives. [AI]
template <class T>
class MxListEntry {
public:
	/// [AI] Default constructor.
	MxListEntry() {}

	/// [AI]
	/// @brief Construct a list entry with value and previous pointer. [AI]
	/// @param p_obj Value to store in the node. [AI]
	/// @param p_prev Previous node pointer. [AI]
	MxListEntry(T p_obj, MxListEntry* p_prev)
	{
		m_obj = p_obj;
		m_prev = p_prev;
		m_next = NULL;
	}

	/// [AI]
	/// @brief Construct a list entry with value, previous, and next pointer. [AI]
	/// @param p_obj Value to store in the node. [AI]
	/// @param p_prev Previous node pointer. [AI]
	/// @param p_next Next node pointer. [AI]
	MxListEntry(T p_obj, MxListEntry* p_prev, MxListEntry* p_next)
	{
		m_obj = p_obj;
		m_prev = p_prev;
		m_next = p_next;
	}

	/// [AI]
	/// @brief Returns the value stored in this node. [AI]
	/// @return The value contained in the entry. [AI]
	T GetValue() { return this->m_obj; }

	/// [AI]
	/// @brief Returns the next node in the list. [AI]
	/// @return The next list entry. [AI]
	MxListEntry* GetNext() { return m_next; }

	/// [AI]
	/// @brief Returns the previous node in the list. [AI]
	/// @return The previous list entry. [AI]
	MxListEntry* GetPrev() { return m_prev; }

	/// [AI]
	/// @brief Sets the value stored in this node. [AI]
	/// @param p_obj The value to set. [AI]
	void SetValue(T p_obj) { m_obj = p_obj; }

	/// [AI]
	/// @brief Sets the next pointer for this node. [AI]
	/// @param p_next The new next node. [AI]
	void SetNext(MxListEntry* p_next) { m_next = p_next; }

	/// [AI]
	/// @brief Sets the previous pointer for this node. [AI]
	/// @param p_prev The new previous node. [AI]
	void SetPrev(MxListEntry* p_prev) { m_prev = p_prev; }

private:
	T m_obj;                ///< [AI] Data stored in the node. [AI]
	MxListEntry* m_prev;    ///< [AI] Pointer to previous node. [AI]
	MxListEntry* m_next;    ///< [AI] Pointer to next node. [AI]
};

// SIZE 0x18
/// [AI]
/// @brief Doubly-linked list implementation. [AI]
/// @details [AI] Provides linked-list functionality with element insertion/removal, traversal support, and ownership semantics (via associated destructors). Supports safe iteration and element access. [AI]
template <class T>
class MxList : protected MxCollection<T> {
public:
	/// [AI] Constructor. Initializes the list pointers to null (empty list). [AI]
	MxList() { m_first = m_last = NULL; }

	/// [AI] Destructor. Deletes all entries in the list and manages resource ownership. [AI]
	~MxList() override { DeleteAll(); }

	/// [AI]
	/// @brief Appends an element at the end of the list. [AI]
	/// @param p_obj Element to append. [AI]
	void Append(T p_obj) { InsertEntry(p_obj, this->m_last, NULL); }

	/// [AI]
	/// @brief Prepends an element to the beginning of the list. [AI]
	/// @param p_obj Element to prepend. [AI]
	void Prepend(T p_obj) { InsertEntry(p_obj, NULL, this->m_first); }

	/// [AI]
	/// @brief Deletes all entries and calls the configured destructor for each element. [AI]
	void DeleteAll();

	/// [AI]
	/// @brief Clears all entries, but does NOT call destructors on contained objects. [AI]
	void Empty();

	/// [AI]
	/// @brief Returns the number of elements present in the list. [AI]
	/// @return Element count. [AI]
	MxU32 GetNumElements() { return this->m_count; }

	/// [AI] Allows the cursor to access protected members for traversal. [AI]
	friend class MxListCursor<T>;
	/// [AI] Import SetDestroy from MxCollection (controls destructor/ownership semantics). [AI]
	using MxCollection<T>::SetDestroy;

protected:
	MxListEntry<T>* m_first; ///< [AI] Pointer to the first entry in the list. [AI]
	MxListEntry<T>* m_last;  ///< [AI] Pointer to the last entry in the list. [AI]

	/// [AI]
	/// @brief Deletes a single entry from the list, adjusting pointers; does not invoke value destructor. [AI]
	/// @param p_match Entry to delete. [AI]
	void DeleteEntry(MxListEntry<T>*);

	/// [AI]
	/// @brief Inserts a new entry into the list, adjusting previous/next pointers accordingly. [AI]
	/// @param p_newobj Value to insert. [AI]
	/// @param p_prev Node to insert after (may be NULL for first). [AI]
	/// @param p_next Node to insert before (may be NULL for last). [AI]
	/// @return Pointer to the newly inserted entry. [AI]
	MxListEntry<T>* InsertEntry(T, MxListEntry<T>*, MxListEntry<T>*);
};

// SIZE 0x18
/// [AI]
/// @brief Pointer-based linked-list, with optional ownership handling for the objects. [AI]
/// @details [AI] When ownership is enabled, the destructor deletes owned pointer objects; otherwise it only manages the list entries. [AI]
template <class T>
class MxPtrList : public MxList<T*> {
public:
	/// [AI]
	/// @brief Constructs a pointer list with ownership semantics. [AI]
	/// @param p_ownership If true, list will delete contained pointers on removal. [AI]
	MxPtrList(MxBool p_ownership) { SetOwnership(p_ownership); }

	/// [AI]
	/// @brief Static deletion utility for pointer ownership. [AI]
	/// @param p_obj Pointer to the object to delete. [AI]
	static void Destroy(T* p_obj) { delete p_obj; }

	/// [AI]
	/// @brief Sets the list to own and destroy objects, or not. [AI]
	/// @param p_ownership If true, enables object deletion via Destroy; else disables. [AI]
	void SetOwnership(MxBool p_ownership)
	{
		MxCollection<T*>::SetDestroy(p_ownership ? MxPtrList<T>::Destroy : MxCollection<T*>::Destroy);
	}
};

// SIZE 0x10
/// [AI]
/// @brief Iterator for traversing and operating on elements within a MxList. [AI]
/// @details [AI] Supports navigation, search, element removal, and reset. Encapsulates state about the current match and operates on a target MxList<T>. [AI]
template <class T>
class MxListCursor : public MxCore {
public:
	/// [AI]
	/// @brief Constructs a cursor for a target list. [AI]
	/// @param p_list Pointer to the list to traverse. [AI]
	MxListCursor(MxList<T>* p_list)
	{
		m_list = p_list;
		m_match = NULL;
	}

	/// [AI]
	/// @brief Search for the first occurrence of an element matching p_obj. [AI]
	/// @param p_obj The value to look for. [AI]
	/// @return True if found, match pointer is set to entry. [AI]
	MxBool Find(T p_obj);

	/// [AI]
	/// @brief Remove the currently matched entry from the list, but do not call destructor on the value. [AI]
	void Detach();

	/// [AI]
	/// @brief Remove the currently matched entry and destroy the value (invoking destructor). [AI]
	void Destroy();

	/// [AI]
	/// @brief Move the cursor to the next entry. [AI]
	/// @return True if there is a next (match updated), otherwise false. [AI]
	MxBool Next();

	/// [AI]
	/// @brief Move to the next entry and provide its value. [AI]
	/// @param p_obj Output: Value at the new position. [AI]
	/// @return True if next entry exists, otherwise false. [AI]
	MxBool Next(T& p_obj);

	/// [AI]
	/// @brief Move cursor to previous entry in the list. [AI]
	/// @return True if previous exists. [AI]
	MxBool Prev();

	/// [AI]
	/// @brief Move to previous entry, provide its value via argument. [AI]
	/// @param p_obj Output: Value at the new position. [AI]
	/// @return True if previous exists, otherwise false. [AI]
	MxBool Prev(T& p_obj);

	/// [AI]
	/// @brief Access value of the current match. [AI]
	/// @param p_obj Output: Value at the current match position. [AI]
	/// @return True if there is a current match. [AI]
	MxBool Current(T& p_obj);

	/// [AI]
	/// @brief Move to the first entry and retrieve its value. [AI]
	/// @param p_obj Output: Value at the first entry. [AI]
	/// @return True if list is not empty. [AI]
	MxBool First(T& p_obj);

	/// [AI]
	/// @brief Move to last entry and retrieve its value. [AI]
	/// @param p_obj Output: Value at the last entry. [AI]
	/// @return True if list is not empty. [AI]
	MxBool Last(T& p_obj);

	/// [AI]
	/// @brief Returns true if the cursor currently points to a match. [AI]
	/// @return True if there is a current match. [AI]
	MxBool HasMatch() { return m_match != NULL; }

	/// [AI]
	/// @brief Change the value at the cursor's current match position. [AI]
	/// @param p_obj The value to set. [AI]
	void SetValue(T p_obj);

	/// [AI]
	/// @brief Move cursor to head (first) entry in the list. [AI]
	/// @return True if cursor is now positioned on valid entry. [AI]
	MxBool Head()
	{
		m_match = m_list->m_first;
		return m_match != NULL;
	}

	/// [AI]
	/// @brief Move cursor to tail (last) entry. [AI]
	/// @return True if positioned on valid entry. [AI]
	MxBool Tail()
	{
		m_match = m_list->m_last;
		return m_match != NULL;
	}

	/// [AI]
	/// @brief Resets the cursor to no match (invalid state). [AI]
	void Reset() { m_match = NULL; }

	/// [AI]
	/// @brief Insert a value before the current match. [AI]
	/// @param p_newobj Value to insert. [AI]
	void Prepend(T p_newobj);

private:
	MxList<T>* m_list;           ///< [AI] Target list being traversed. [AI]
	MxListEntry<T>* m_match;     ///< [AI] Current match/position within the list. [AI]
};

// SIZE 0x10
/// [AI]
/// @brief Cursor for traversing pointer-based lists. [AI]
/// @details [AI] Specialization for MxPtrList. [AI]
template <class T>
class MxPtrListCursor : public MxListCursor<T*> {
public:
	/// [AI]
	/// @brief Constructor that sets the pointer list to traverse. [AI]
	/// @param p_list Pointer to a pointer-list instance. [AI]
	MxPtrListCursor(MxPtrList<T>* p_list) : MxListCursor<T*>(p_list) {}
};

#endif // MXLIST_H
