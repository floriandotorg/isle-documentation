#ifndef MXDSSUBSCRIBER_H
#define MXDSSUBSCRIBER_H

#include "decomp.h"
#include "mxcore.h"
#include "mxstreamchunklist.h"
#include "mxutilitylist.h"

class MxDSObject;
class MxDSSubscriber;
class MxStreamController;

/// @brief [AI] List container for pointers to MxDSSubscriber objects, with utility methods.
/// [AI] Inherits from MxUtilityList and provides additional search capabilities.
class MxDSSubscriberList : public MxUtilityList<MxDSSubscriber*> {
public:
	/// @brief [AI] Searches for a subscriber corresponding to the provided MxDSObject.
	/// @param p_object [AI] The object to match by ObjectId and Unknown24 (usually type/instance identifiers).
	/// @return [AI] A matching MxDSSubscriber pointer if found, otherwise NULL.
	MxDSSubscriber* Find(MxDSObject* p_object); // [AI]
};

/// @brief [AI] Handles the receipt, queuing, and batch management of data chunks streamed by a MxStreamController.
/// @details [AI] Acts as a client for an active stream; maintains a unique ObjectId and facilitates buffering, consumption,
/// and freeing of received media data chunks. Used internally by the media subsystem for dynamic, on-demand resource consumption.
/// [AI] SIZE: 0x4c
class MxDSSubscriber : public MxCore {
public:
	MxDSSubscriber(); ///< @brief [AI] Initializes internal member pointers and state.
	~MxDSSubscriber() override; ///< @brief [AI] Destructor, unregisters and frees associated memory/buffers.

	// FUNCTION: LEGO1 0x100b7d50
	// FUNCTION: BETA10 0x10135180
	/// @brief [AI] Returns the class name as a string ("MxDSSubscriber").
	/// @return [AI] Pointer to class name static string.
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101020f8
		return "MxDSSubscriber";
	}

	// FUNCTION: LEGO1 0x100b7d60
	/// @brief [AI] Checks if this object is of the provided type name or is derived from it.
	/// @param p_name [AI] Null-terminated class name string.
	/// @return [AI] TRUE if this class is or derives from p_name; otherwise, FALSE.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSubscriber::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Initializes subscription to a streaming controller, sets identifiers, and establishes chunk cursors.
	/// @param p_controller [AI] Pointer to the MxStreamController providing data.
	/// @param p_objectId [AI] Unique identifier for the object/resource being streamed to.
	/// @param p_unk0x48 [AI] Stream-type specific field for finer-grained distinction, often media format related.
	/// @return [AI] SUCCESS if initialization of subscription and cursors succeeded, FAILURE otherwise.
	MxResult Create(MxStreamController* p_controller, MxU32 p_objectId, MxS16 p_unk0x48); // [AI]

	/// @brief [AI] Frees and detaches all currently managed/pending/consumed data chunks from both lists;
	/// intended to thoroughly clean after stream termination or error.
	void DestroyData(); // [AI]

	/// @brief [AI] Appends or prepends a new data chunk to the pending stream buffer.
	/// @param p_chunk [AI] Pointer to the data chunk to be queued.
	/// @param p_append [AI] If TRUE, will append to end; if FALSE, prepends to front of queue.
	/// @return [AI] Always returns SUCCESS as allocation occurs externally.
	MxResult AddData(MxStreamChunk* p_chunk, MxBool p_append); // [AI]

	/// @brief [AI] Pops the next available pending data chunk for consumption, moving it to the consumed list.
	/// @return [AI] Pointer to the popped chunk, or NULL if no chunk is available.
	MxStreamChunk* PopData(); // [AI]

	/// @brief [AI] Returns but does not remove the first pending data chunk ("peek" operation).
	/// @return [AI] Pointer to the next available data chunk, or NULL if none left.
	MxStreamChunk* PeekData(); // [AI]

	/// @brief [AI] Frees (deletes) a data chunk if it's found in the consumed data list; also forcibly deletes single-use chunks.
	/// @param p_chunk [AI] Pointer to the chunk to free. [AI_SUGGESTED_NAME: FreeConsumedDataChunk]
	void FreeDataChunk(MxStreamChunk* p_chunk); // [AI]

	// FUNCTION: BETA10 0x101354f0
	/// @brief [AI] Returns the object identifier associated with this subscriber.
	MxU32 GetObjectId() { return m_objectId; } // [AI]

	// FUNCTION: BETA10 0x10135510
	/// @brief [AI] Returns the member field sometimes used for disambiguating media (purpose context-specific).
	MxS16 GetUnknown48() { return m_unk0x48; } // [AI]

private:
	MxStreamChunkList m_pendingChunks;              ///< @brief [AI] List of incoming (unconsumed) data chunks.
	MxStreamChunkListCursor* m_pendingChunkCursor;  ///< @brief [AI] Cursor for traversal within pending chunk list.
	MxStreamChunkList m_consumedChunks;             ///< @brief [AI] List of previously consumed stream data.
	MxStreamChunkListCursor* m_consumedChunkCursor; ///< @brief [AI] Cursor for traversing consumed data list.
	MxStreamController* m_controller;               ///< @brief [AI] Active controller providing data into this subscriber.
	MxU32 m_objectId;                               ///< @brief [AI] Object ID for which data consumption is managed.
	MxS16 m_unk0x48;                                ///< @brief [AI] Type-specific field (usage varies based on context; often subtype).
};

// SYNTHETIC: LEGO1 0x100b7de0
// MxDSSubscriber::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100b7d00
// MxStreamChunkList::~MxStreamChunkList

// TEMPLATE: BETA10 0x10150a70
// MxUtilityList<MxDSSubscriber *>::PopFront

#endif // MXDSSUBSCRIBER_H