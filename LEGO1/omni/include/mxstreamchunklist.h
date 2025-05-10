#ifndef MXSTREAMCHUNKLIST_H
#define MXSTREAMCHUNKLIST_H

#include "decomp.h"
#include "mxlist.h"
#include "mxstreamchunk.h"

// VTABLE: LEGO1 0x100dc5d0
// class MxCollection<MxStreamChunk *>

// VTABLE: LEGO1 0x100dc5e8
// class MxList<MxStreamChunk *>

// VTABLE: LEGO1 0x100dc600
// SIZE 0x18
/**
 * @brief [AI] A list for managing collections of pointers to MxStreamChunk objects, used for organizing and managing the chunks of a data stream within the engine.
 * @details [AI] This class specializes the MxList template for objects of type MxStreamChunk*, and provides comparison and destruction methods optimized for chunk objects.
 */
class MxStreamChunkList : public MxList<MxStreamChunk*> {
public:
	/**
	 * @brief [AI] Constructs a MxStreamChunkList and sets a custom destructor for contained objects.
	 * @details [AI] Ensures that destroying the list will delete the chunk pointers held within, by assigning the Destroy callback to m_customDestructor.
	 */
	MxStreamChunkList() { m_customDestructor = Destroy; }

	/**
	 * @brief [AI] Compares two MxStreamChunk pointers for list ordering.
	 * @param p_a First MxStreamChunk pointer to compare. [AI]
	 * @param p_b Second MxStreamChunk pointer to compare. [AI]
	 * @details [AI] Returns 0 if pointers are equal, -1 if p_a < p_b, and 1 otherwise. Used to maintain order or detect duplicates in the collection.
	 */
	MxS8 Compare(MxStreamChunk* p_a, MxStreamChunk* p_b) override
	{
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14

	/**
	 * @brief [AI] Deletes a MxStreamChunk object pointer, used as the destructor callback for the list.
	 * @param p_chunk Pointer to MxStreamChunk to be deleted. [AI]
	 * @details [AI] This static method is called during destruction/cleanup of the list to free associated memory.
	 */
	static void Destroy(MxStreamChunk* p_chunk) { delete p_chunk; }

	// SYNTHETIC: LEGO1 0x100b5a30
	// MxStreamChunkList::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dc510
// SIZE 0x10
/**
 * @brief [AI] Cursor for iterating over a MxStreamChunkList.
 * @details [AI] Provides pointer-based traversal through the list of stream chunks, encapsulating navigation logic for external users.
 */
class MxStreamChunkListCursor : public MxListCursor<MxStreamChunk*> {
public:
	/**
	 * @brief [AI] Constructs a cursor for a specific MxStreamChunkList.
	 * @param p_list Pointer to the MxStreamChunkList to iterate over. [AI]
	 * @details [AI] Allows iteration mechanics as defined by the parent MxListCursor logic.
	 */
	MxStreamChunkListCursor(MxStreamChunkList* p_list) : MxListCursor<MxStreamChunk*>(p_list) {}
};

// VTABLE: LEGO1 0x100dc528
// class MxListCursor<MxStreamChunk *>

// TEMPLATE: LEGO1 0x100b5930
// MxCollection<MxStreamChunk *>::Compare

// TEMPLATE: LEGO1 0x100b5940
// MxCollection<MxStreamChunk *>::~MxCollection<MxStreamChunk *>

// TEMPLATE: LEGO1 0x100b5990
// MxCollection<MxStreamChunk *>::Destroy

// TEMPLATE: LEGO1 0x100b59a0
// MxList<MxStreamChunk *>::~MxList<MxStreamChunk *>

// SYNTHETIC: LEGO1 0x100b5aa0
// MxCollection<MxStreamChunk *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100b5b10
// MxList<MxStreamChunk *>::`scalar deleting destructor'

#endif // MXSTREAMCHUNKLIST_H
