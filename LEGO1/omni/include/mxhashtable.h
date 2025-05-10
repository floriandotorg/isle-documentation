#ifndef MXHASHTABLE_H
#define MXHASHTABLE_H

#include "mxcollection.h"
#include "mxcore.h"
#include "mxtypes.h"

#define HASH_TABLE_INIT_SIZE 128

/**
 * @class MxHashTableNode
 * @brief [AI] Node used within the MxHashTable to store an individual object and associated hash, for organizing elements in a bucketed linked list.
 * @details [AI] Each hash table slot contains a linked list of these nodes. Each node stores an object of type T and the corresponding hash, as well as pointers to previous and next nodes in the bucket's list.
 * @tparam T [AI] Type of object stored in the hash table node.
 */
template <class T>
class MxHashTableCursor;

template <class T>
class MxHashTableNode {
public:
	/**
	 * @brief [AI] Constructor for a new hash node with its associated object, hash value, and linkage pointers.
	 * @param p_obj [AI] The object value held by this node.
	 * @param p_hash [AI] The precomputed hash for the stored object.
	 * @param p_prev [AI] The node preceding this one in the bucket's linked list (can be nullptr).
	 * @param p_next [AI] The node following this one in the bucket's linked list (can be nullptr).
	 */
	MxHashTableNode<T>(T p_obj, MxU32 p_hash, MxHashTableNode* p_prev, MxHashTableNode* p_next)
	{
		m_obj = p_obj;
		m_hash = p_hash;
		m_prev = p_prev;
		m_next = p_next;
	}

	// DECOMP: Should use getter and setter methods here per the style guide.
	// However, LEGO1D (with no functions inlined) does not use them.

	/// @brief [AI] The actual object value this node represents.
	T m_obj;
	/// @brief [AI] The hash value for m_obj, used for placement/search in the table.
	MxU32 m_hash;
	/// @brief [AI] Previous node in the linked list chain within the current bucket.
	MxHashTableNode* m_prev;
	/// @brief [AI] Next node in the linked list chain within the current bucket.
	MxHashTableNode* m_next;
};

/**
 * @class MxHashTable
 * @brief [AI] Generic hash table collection implementing chained (bucketed) hashing, used for efficient lookup and storage of objects by key or value.
 * @details [AI] Inherits collection semantics from MxCollection<T> but also manages resizing, hash calculation, and separate chaining (via MxHashTableNode). Provides insert, deletion, and all-bucket purge operations. Resizing policies can be controlled via Option.
 * @tparam T [AI] Type of object managed by the hash table.
 */
template <class T>
class MxHashTable : protected MxCollection<T> {
public:
	/**
	 * @brief [AI] Enum describing the strategy for resizing the hash table when load increases.
	 */
	enum Option {
		e_noExpand = 0,    ///< [AI] Never resize (table will not expand regardless of load).
		e_expandAll,       ///< [AI] Fixed amount of slots added on resize.
		e_expandMultiply,  ///< [AI] Table size is multiplied by a factor on resize.
	};

	/**
	 * @brief [AI] Default constructor. Initializes hash table with HASH_TABLE_INIT_SIZE slots and configures resizing behavior.
	 */
	MxHashTable()
	{
		m_numSlots = HASH_TABLE_INIT_SIZE;
		MxU32 unused = 0;
		m_slots = new MxHashTableNode<T>*[m_numSlots];
		memset(m_slots, 0, sizeof(MxHashTableNode<T>*) * m_numSlots);
		m_resizeOption = e_noExpand;
	}

	/**
	 * @brief [AI] Destructor. Purges all contained nodes and releases bucket array.
	 */
	~MxHashTable() override;

	/**
	 * @brief [AI] Expand/recreates the hash table according to the current resizing policy.
	 * @details [AI] Moves nodes from the old bucket array to a newly sized one based on m_resizeOption, re-bucketing all nodes.
	 */
	void Resize();

	/**
	 * @brief [AI] Inserts a new item into the hash table, possibly resizing if automatic resize is enabled and load threshold is exceeded.
	 * @param [AI] p_newobj The item to insert.
	 */
	void Add(T);

	/**
	 * @brief [AI] Removes and destructs all nodes in all hash buckets, clearing the table.
	 */
	void DeleteAll();

	/**
	 * @brief [AI] Computes the hash of the given object. Should be overridden for meaningful hash computation.
	 * @param [AI] (unnamed) The object to compute the hash for.
	 * @return [AI] Hash value appropriate for placing the object in a bucket.
	 */
	virtual MxU32 Hash(T) { return 0; } // [AI] To be overridden by subclasses.

	friend class MxHashTableCursor<T>;

protected:
	/**
	 * @brief [AI] Inserts a given node into the relevant hash bucket according to the node's hash value.
	 * @param p_node [AI] Node (already allocated) to insert into appropriate bucket.
	 */
	void NodeInsert(MxHashTableNode<T>*);

	/// @brief [AI] Array of pointers to bucket heads; each slot is a chain of nodes (linked list) holding objects with equal (modulo table size) hashes.
	MxHashTableNode<T>** m_slots; // 0x10

	/// @brief [AI] Number of hash buckets in the table; controls how hash values are mapped to buckets.
	MxU32 m_numSlots;             // 0x14

	/// @brief [AI] Ratio at which the table will auto-resize (load factor denominator).
	MxU32 m_autoResizeRatio;      // 0x18

	/// @brief [AI] Strategy currently in use for resizing the table when needed.
	Option m_resizeOption;        // 0x1c

	/**
	 * @brief [AI] Union holding the setting for table expansion:
	 * - m_increaseAmount (when using e_expandAll): slots to add on resize.
	 * - m_increaseFactor (when using e_expandMultiply): multiplicative factor for resizing (e.g. double the table).
	 * Purpose is determined by m_resizeOption.
	 */
	union {
		MxU32 m_increaseAmount;  // 0x20
		double m_increaseFactor; // 0x20
	};
};

/**
 * @class MxHashTableCursor
 * @brief [AI] Non-intrusive search-and-edit cursor for navigating, querying, or deleting a specific entry in an MxHashTable.
 * @details [AI] Used to locate and possibly remove or edit a single object in the hash table by value, based on its hash and value equality.
 * @tparam T [AI] The object type in the associated hash table.
 */
template <class T>
class MxHashTableCursor : public MxCore {
public:
	/**
	 * @brief [AI] Constructs a cursor operating on the supplied table; initially not referencing any match.
	 * @param p_table [AI] Hash table in which searches/operations will be performed.
	 */
	MxHashTableCursor(MxHashTable<T>* p_table)
	{
		m_table = p_table;
		m_match = NULL;
	}

	/**
	 * @brief [AI] Finds and focuses the cursor on the first node matching the given object by hash and value; supports set-by-value semantics.
	 * @param p_obj [AI] Value to search for in table using table's Compare and Hash functions.
	 * @retval TRUE [AI] If a match was found and cursor now points to it.
	 * @retval FALSE [AI] If no such object exists in table.
	 */
	MxBool Find(T p_obj);

	/**
	 * @brief [AI] Retrieves the object at the current match position, if valid.
	 * @param p_obj [AI] (out parameter) Receives the matching object value if cursor is positioned on a node.
	 * @retval TRUE [AI] If match exists, FALSE otherwise.
	 */
	MxBool Current(T& p_obj);

	/**
	 * @brief [AI] If the cursor points to a match, removes it from table and destroys the node.
	 */
	void DeleteMatch();

private:
	/// @brief [AI] The hash table this cursor is operating upon.
	MxHashTable<T>* m_table;

	/// @brief [AI] Currently matched node (from a find), or nullptr if not positioned.
	MxHashTableNode<T>* m_match;
};

template <class T>
MxBool MxHashTableCursor<T>::Find(T p_obj)
{
	MxU32 hash = m_table->Hash(p_obj);

	for (MxHashTableNode<T>* t = m_table->m_slots[hash % m_table->m_numSlots]; t; t = t->m_next) {
		if (t->m_hash == hash && !m_table->Compare(t->m_obj, p_obj)) {
			m_match = t;
		}
	}

	return m_match != NULL;
}

template <class T>
MxBool MxHashTableCursor<T>::Current(T& p_obj)
{
	if (m_match) {
		p_obj = m_match->m_obj;
	}

	return m_match != NULL;
}

template <class T>
void MxHashTableCursor<T>::DeleteMatch()
{
	// Cut the matching node out of the linked list
	// by updating pointer references.
	if (m_match) {
		if (m_match->m_prev) {
			m_match->m_prev->m_next = m_match->m_next;
		}
		else {
			// No "prev" node, so move "next" to the head of the list.
			m_table->m_slots[m_match->m_hash % m_table->m_numSlots] = m_match->m_next;
		}

		if (m_match->m_next) {
			m_match->m_next->m_prev = m_match->m_prev;
		}

		m_table->m_customDestructor(m_match->m_obj);
		delete m_match;
		m_table->m_count--;
	}
}

template <class T>
MxHashTable<T>::~MxHashTable()
{
	DeleteAll();
	delete[] m_slots;
}

template <class T>
void MxHashTable<T>::DeleteAll()
{
	for (MxS32 i = 0; i < m_numSlots; i++) {
		MxHashTableNode<T>* next;
		for (MxHashTableNode<T>* t = m_slots[i]; t != NULL; t = next) {
			next = t->m_next;
			this->m_customDestructor(t->m_obj);
			delete t;
		}
	}

	this->m_count = 0;
	memset(m_slots, 0, sizeof(MxHashTableNode<T>*) * m_numSlots);
}

template <class T>
inline void MxHashTable<T>::Resize()
{
	// Save a reference to the current table
	// so we can walk nodes and re-insert
	MxU32 oldSize = m_numSlots;
	MxHashTableNode<T>** oldTable = m_slots;

	switch (m_resizeOption) {
	case e_expandAll:
		m_numSlots += m_increaseAmount;
		break;
	case e_expandMultiply:
		m_numSlots *= m_increaseFactor;
		break;
	}

	MxU32 unused = 0;
	m_slots = new MxHashTableNode<T>*[m_numSlots];
	memset(m_slots, 0, sizeof(MxHashTableNode<T>*) * m_numSlots);
	this->m_count = 0;

	for (MxS32 i = 0; i < oldSize; i++) {
		MxHashTableNode<T>* next;
		for (MxHashTableNode<T>* t = oldTable[i]; t != NULL; t = next) {
			next = t->m_next;
			NodeInsert(t);
		}
	}

	delete[] oldTable;
}

template <class T>
inline void MxHashTable<T>::NodeInsert(MxHashTableNode<T>* p_node)
{
	MxS32 bucket = p_node->m_hash % m_numSlots;

	p_node->m_next = m_slots[bucket];

	if (m_slots[bucket]) {
		m_slots[bucket]->m_prev = p_node;
	}

	m_slots[bucket] = p_node;
	this->m_count++;
}

template <class T>
inline void MxHashTable<T>::Add(T p_newobj)
{
	if (m_resizeOption && ((this->m_count + 1) / m_numSlots) > m_autoResizeRatio) {
		MxHashTable<T>::Resize();
	}

	MxU32 hash = Hash(p_newobj);
	MxU32 unused = 0;

	MxHashTableNode<T>* node = new MxHashTableNode<T>(p_newobj, hash, NULL, NULL);

	MxHashTable<T>::NodeInsert(node);
}

#undef HASH_TABLE_INIT_SIZE

#endif // MXHASHTABLE_H
