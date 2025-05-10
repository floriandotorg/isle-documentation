#ifndef MXDSBUFFER_H
#define MXDSBUFFER_H

#include "decomp.h"
#include "mxcore.h"

/**
 * @brief [AI] Forward declaration of MxStreamController. Controls the streaming of media data.
 */
class MxStreamController; // [AI]

/**
 * @brief [AI] Forward declaration of MxDSAction. Represents a data stream action, e.g., for presenting media.
 */
class MxDSAction; // [AI]

/**
 * @brief [AI] Forward declaration of MxDSStreamingAction. Used for actions that require streaming data.
 */
class MxDSStreamingAction; // [AI]

/**
 * @brief [AI] Forward declaration of MxStreamChunk. Represents a chunk of media stream data.
 */
class MxStreamChunk; // [AI]

/**
 * @brief [AI] Forward declaration of MxDSChunk. Represents a generic chunk of data in a stream.
 */
class MxDSChunk; // [AI]

/**
 * @brief [AI] Buffer for managing streamed DS (Data Stream) chunks and actions.
 * 
 * This class manages memory for streaming SI file chunks and objects. It keeps track of memory usage,
 * references, and supports allocation and appending of streamed data. It also serves as a unit to 
 * bridge stream controller data with presenters/actions/subscribers and mediates actions related to 
 * chunk parsing and presenter startup.
 * 
 * @details [AI] This buffer handles operations such as allocating memory, tracking offsets/remaining bytes,
 * handling reference counting for chunk retention (i.e., for streaming), parsing complex hierarchical/file
 * block formats (e.g., RIFF/LIST/MxCh/MxOb) from media streams, and managing the lifecycle of streaming
 * actions related to playing back/chunking large media resources.
 * 
 * @ingroup StreamResourceManagement [AI]
 */
// VTABLE: LEGO1 0x100dcca0
// VTABLE: BETA10 0x101c2898
// SIZE 0x34
class MxDSBuffer : public MxCore {
public:
	/**
	 * @brief [AI] Buffer memory management type.
	 */
	enum Type {
		e_chunk = 0,        ///< [AI] Chunk-managed memory (from Streamer pool).
		e_allocate = 1,     ///< [AI] Newly allocated memory with new[].
		e_preallocated = 2, ///< [AI] Preallocated memory passed in from outside.
		e_unknown = 3,      ///< [AI] Unknown/other (may be unused or special).
	};

	/**
	 * @brief [AI] Constructs a buffer object and initializes all internal pointers and counters.
	 */
	MxDSBuffer(); // [AI]

	/**
	 * @brief [AI] Destructor: Releases memory appropriately based on buffer management mode and asserts no references.
	 */
	~MxDSBuffer() override; // [AI]

	/**
	 * @brief [AI] Returns the runtime class name for serialization/reflection.
	 * @return The constant string "MxDSBuffer".
	 */
	const char* ClassName() const override; // [AI]

	/**
	 * @brief [AI] Allocates a buffer of a given size and memory mode.
	 * 
	 * @param p_bufferSize Size, in bytes, to allocate.
	 * @param p_mode Memory allocation mode.
	 * @return SUCCESS if allocation was successful, FAILURE otherwise.
	 */
	MxResult AllocateBuffer(MxU32 p_bufferSize, Type p_mode); // [AI]

	/**
	 * @brief [AI] Sets a buffer pointer and records its size.
	 * Sets this buffer to use externally provided memory.
	 * 
	 * @param p_buffer Pointer to memory.
	 * @param p_size Size of memory block.
	 * @return SUCCESS if pointer setup successful.
	 */
	MxResult SetBufferPointer(MxU8* p_buffer, MxU32 p_size); // [AI]

	/**
	 * @brief [AI] Executes streaming action startup and object creation loop from an initial SI chunk.
	 *
	 * This method is called for each streaming SI data block, processing it to start and attach presenters/actions as needed. 
	 * Handles splitting, reference counting, and action list updates.
	 *
	 * @param p_controller The stream controller managing streaming logic.
	 * @param p_action The parent action.
	 * @param p_streamingAction On success, set to created streaming action (output param, may be overwritten/reset).
	 * @return SUCCESS on successful operation, FAILURE otherwise.
	 */
	MxResult FUN_100c67b0(
		MxStreamController* p_controller,
		MxDSAction* p_action,
		MxDSStreamingAction** p_streamingAction
	); // [AI]

	/**
	 * @brief [AI] Creates a presenter/action object by deserializing a data block.
	 *
	 * Depending on the FourCC, dispatches to deserialize a chunk or action object
	 * and launches a presenter as appropriate.
	 *
	 * @param p_controller The stream controller to operate on.
	 * @param p_data Pointer to start of object data (FourCC-driven).
	 * @param p_action The parent action.
	 * @param p_streamingAction Output pointer for streaming action.
	 * @return Presenter creation status.
	 */
	MxResult CreateObject(
		MxStreamController* p_controller,
		MxU32* p_data,
		MxDSAction* p_action,
		MxDSStreamingAction** p_streamingAction
	); // [AI]

	/**
	 * @brief [AI] Launches a presenter for the given action if not already present.
	 *
	 * Copies required attributes from the original action, registers it, and 
	 * notifies the controller to set up the action in the stream.
	 *
	 * @param p_controller The stream controller.
	 * @param p_action1 Source action to copy information from.
	 * @param p_action2 The deserialized action to execute.
	 * @return SUCCESS or FAILURE. 
	 */
	MxResult StartPresenterFromAction(MxStreamController* p_controller, MxDSAction* p_action1, MxDSAction* p_action2); // [AI]

	/**
	 * @brief [AI] Parses an MxStreamChunk for logical streaming actions, nested chunks, EoS, and splitting.
	 *
	 * Handles chunk splitting if necessary, end-of-stream repeats and loop-control, 
	 * and delegates dispatch to subscribers as appropriate.
	 *
	 * @param p_controller Stream controller.
	 * @param p_data Data pointer.
	 * @param p_action Parent MxDSAction.
	 * @param p_streamingAction (Output) streaming action pointer.
	 * @param p_header Parsed chunk header.
	 * @return Status based on chunk and playback logic (could include internal signal).
	 */
	MxResult ParseChunk(
		MxStreamController* p_controller,
		MxU32* p_data,
		MxDSAction* p_action,
		MxDSStreamingAction** p_streamingAction,
		MxStreamChunk* p_header
	); // [AI]

	/**
	 * @brief [AI] Scans this buffer forward to the next valid object or chunk and returns a pointer to its start.
	 * 
	 * Advances internal cursor until the next MxOb (object) or MxCh (chunk) in buffer,
	 * or nullptr if there is none left.
	 *
	 * @return Pointer to start of next chunk/object, or nullptr if at end.
	 */
	MxU8* SkipToData(); // [AI]

	/**
	 * @brief [AI] Decrement the buffer's chunk reference count.
	 *
	 * @param chunk Pointer to the chunk for which to release a reference.
	 * @return Always returns 0.
	 */
	MxU8 ReleaseRef(MxDSChunk*); // [AI]

	/**
	 * @brief [AI] Increment reference count for this buffer (ownership by a chunk).
	 *
	 * Used for split streaming objects, to avoid premature deallocation.
	 *
	 * @param p_chunk The chunk gaining a reference.
	 */
	void AddRef(MxDSChunk* p_chunk); // [AI]

	/**
	 * @brief [AI] Calculates pending bytes remaining to be streamed, updates buffer state accordingly.
	 *
	 * Handles chunk offsets/headers and ensures only requested data is marked as remaining.
	 * Used to guide further dequeue/transfer operations.
	 *
	 * @param p_data Pointer to chunk data in external memory.
	 * @return SUCCESS if calculation/recording succeeded, FAILURE otherwise (out of memory, etc.).
	 */
	MxResult CalcBytesRemaining(MxU8* p_data); // [AI]

	/**
	 * @brief [AI] Sets the buffer's internal streaming position to the given write offset.
	 *
	 * Updates internal pointers so next SkipToData()/processing resumes at the given offset.
	 *
	 * @param p_writeOffset The offset (in bytes) to advance buffer pointers.
	 */
	void FUN_100c6f80(MxU32 p_writeOffset); // [AI] [AI_SUGGESTED_NAME: SetStreamingOffset]

	/**
	 * @brief [AI] Finds the next chunk boundary in the buffer, starting from an optional pointer.
	 *
	 * Advances through RIFF/LIST/MxDa/MxOb/MxCh/MxHd blocks as per SI file format to locate the next significant chunk.
	 * 
	 * @param p_data (Optional) Pointer to start searching from. If nullptr, searches from buffer start.
	 * @return Pointer to the next chunk boundary, or nullptr if none found.
	 */
	MxU8* FUN_100c6fa0(MxU8* p_data); // [AI] [AI_SUGGESTED_NAME: NextChunkBoundary]

	/**
	 * @brief [AI] Copies buffer data and selected internal state from another buffer, if space allows.
	 *
	 * Used for chunk/A/V buffer transfer.
	 *
	 * @param p_buf Source buffer.
	 * @return SUCCESS if operation complete, FAILURE otherwise.
	 */
	MxResult FUN_100c7090(MxDSBuffer* p_buf); // [AI] [AI_SUGGESTED_NAME: CopyFromBuffer]

	/**
	 * @brief [AI] Reads an SI file object/chunk at given position in a buffer.
	 * 
	 * Depending on the FourCC, deserializes appropriate object type. Normally returns either an MxDSObject or MxDSChunk.
	 * 
	 * @param p_buffer Buffer to read from.
	 * @param p_chunkData Pointer to chunk header/FourCC.
	 * @param p_flags Flags to drive the deserialization logic.
	 * @return Pointer to MxCore-derived object parsed from data (may be MxDSObject or MxDSChunk, or nullptr).
	 */
	static MxCore* ReadChunk(MxDSBuffer* p_buffer, MxU32* p_chunkData, MxU16 p_flags); // [AI]

	/**
	 * @brief [AI] Appends one chunk/data stream buffer to another, adjusting sizes/headers.
	 *
	 * @param p_buffer1 Destination buffer. Its length fields are updated.
	 * @param p_buffer2 Source buffer. Payload is copied (header area skipped).
	 * @return SUCCESS if append was performed, FAILURE if failed.
	 */
	static MxResult Append(MxU8* p_buffer1, MxU8* p_buffer2); // [AI]

	/**
	 * @brief [AI] Returns a pointer to the managed chunk data buffer.
	 * @return pointer to buffer.
	 */
	MxU8* GetBuffer(); // [AI]

	/**
	 * @brief [AI] Returns the internal value at offset 0x14.
	 * @return value of m_unk0x14.
	 */
	undefined4 GetUnknown14(); // [AI] [AI_SUGGESTED_NAME: GetCustomMeta1]

	/**
	 * @brief [AI] Checks whether there are any active references to this buffer.
	 * @retval TRUE If referenceCount > 0, FALSE if not.
	 */
	MxBool HasRef(); // [AI]

	/**
	 * @brief [AI] Returns the current buffer reference count.
	 */
	MxU16 GetRefCount(); // [AI]

	/**
	 * @brief [AI] Returns the current buffer management mode.
	 */
	Type GetMode(); // [AI]

	/**
	 * @brief [AI] Returns the current buffer write offset (number of bytes with valid data).
	 */
	MxU32 GetWriteOffset(); // [AI]

	/**
	 * @brief [AI] Returns the number of bytes remaining to stream in this buffer.
	 */
	MxU32 GetBytesRemaining(); // [AI]

	/**
	 * @brief [AI] Sets the unknown value at offset 0x14.
	 * @param p_unk0x14 Value to set for m_unk0x14.
	 */
	void SetUnknown14(undefined4 p_unk0x14); // [AI] [AI_SUGGESTED_NAME: SetCustomMeta1]

	/**
	 * @brief [AI] Sets the unknown value at offset 0x1c.
	 * @param p_unk0x1c Value to set for m_unk0x1c.
	 */
	void SetUnknown1c(undefined4 p_unk0x1c); // [AI] [AI_SUGGESTED_NAME: SetCustomMeta2]

	/**
	 * @brief [AI] Sets the buffer memory management mode.
	 * @param p_mode The buffer management type.
	 */
	void SetMode(Type p_mode); // [AI]

	/**
	 * @brief [AI] Sets the pointer to the currently relevant streaming action for this buffer.
	 * @param p_unk0x30 Pointer to the streaming action.
	 */
	void SetUnk30(MxDSStreamingAction* p_unk0x30); // [AI] [AI_SUGGESTED_NAME: SetCurrentStreamingAction]

	// SYNTHETIC: LEGO1 0x100c6510
	// SYNTHETIC: BETA10 0x10158530
	// MxDSBuffer::`scalar deleting destructor'

private:
	MxU8* m_pBuffer;                ///< [AI] Pointer to start of memory block holding stream data. [AI]
	MxU8* m_pIntoBuffer;            ///< [AI] Internal pointer for scan/skip-to-data (parsing position). [AI]
	MxU8* m_pIntoBuffer2;           ///< [AI] Alternate/internal secondary data cursor. [AI]
	undefined4 m_unk0x14;           ///< [AI] Custom/unknown metadata 1, may be used as user-defined tag. [AI]
	undefined4 m_unk0x18;           ///< [AI] Custom/unknown metadata 2, ambiguous usage. [AI]
	undefined4 m_unk0x1c;           ///< [AI] Possibly metadata or synchronization counter. [AI]
	MxU16 m_referenceCount;         ///< [AI] Reference counter for chunk usage/retention (prevent free). [AI]
	Type m_mode;                    ///< [AI] How this buffer's memory is managed (owning/pooled/external). [AI]
	MxU32 m_writeOffset;            ///< [AI] Number of bytes currently written/valid in buffer (like end-of-data pointer). [AI]
	MxU32 m_bytesRemaining;         ///< [AI] Bytes left to fulfill/stream before operation complete. [AI]
	MxDSStreamingAction* m_unk0x30; ///< [AI] Pointer to streaming action this buffer is currently tied to. [AI]
};

#endif // MXDSBUFFER_H