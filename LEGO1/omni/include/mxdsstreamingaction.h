#ifndef MXDSSTREAMINGACTION_H
#define MXDSSTREAMINGACTION_H

#include "mxdsaction.h"

class MxDSBuffer;

// VTABLE: LEGO1 0x100dd088
// VTABLE: BETA10 0x101c2850
// SIZE 0xb4

/**
 * @brief [AI] Represents an action that streams data from a buffer within a DirectScript (DS) media timeline.
 * @details [AI] MxDSStreamingAction specializes MxDSAction to support incremental reading ("streaming") from a buffer, as used for video and audio media. It manages buffer offsets, internal buffer objects, and potentially a sub-action that represents the actual payload action. Commonly used in scenarios where DS media format requires data to be loaded in parts rather than all at once. It maintains ownership of two buffers and its internal action. [AI]
 */
class MxDSStreamingAction : public MxDSAction {
public:
	/**
	 * @brief [AI] Constructs a streaming action from a base DS action with a given offset into the media buffer.
	 * @param p_dsAction [AI] The source MxDSAction to copy base parameters from.
	 * @param p_offset [AI] Offset (in bytes or frames) in the buffer from which streaming should start.
	 */
	MxDSStreamingAction(MxDSAction& p_dsAction, MxU32 p_offset);

	/**
	 * @brief [AI] Copy constructor, creates a new streaming action from an existing streaming action.
	 * @param p_dsStreamingAction [AI] The source MxDSStreamingAction to copy from.
	 */
	MxDSStreamingAction(MxDSStreamingAction& p_dsStreamingAction);

	/**
	 * @brief [AI] Destructor. Cleans up internal buffers and internal action if set.
	 */
	~MxDSStreamingAction() override;

	/**
	 * @brief [AI] Copies fields from another MxDSStreamingAction, deeply cloning the internal action if needed.
	 * @param p_dsStreamingAction [AI] Source from which to copy.
	 * @return Pointer to this action instance. [AI]
	 */
	MxDSStreamingAction* CopyFrom(MxDSStreamingAction& p_dsStreamingAction);

	/**
	 * @brief [AI] Determines if this action or its internal action correspond to the given object ID.
	 * @param p_objectId [AI] Object id to test.
	 * @return TRUE if found; otherwise FALSE. [AI]
	 */
	MxBool HasId(MxU32 p_objectId) override; // vtable+0x34

	/**
	 * @brief [AI] Initializes default values for members. Called by constructors and reset. [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Sets or replaces the internal action held by this streaming action (ownership is transferred).
	 * @param p_dsAction [AI] The new internal sub-action; previously assigned action is deleted if present.
	 */
	void SetInternalAction(MxDSAction* p_dsAction);

	/**
	 * @brief [AI] Updates duration, loop count, and accumulates advanced streaming time for repeated playback.
	 * @details [AI] Used by time management; decrements loop count and advances total duration. Skips if duration is -1 (infinite). [AI]
	 */
	void FUN_100cd2d0();

	/**
	 * @brief [AI] Gets the streaming offset or status value at 0x94.
	 */
	MxU32 GetUnknown94() { return m_unk0x94; }

	/**
	 * @brief [AI] Retrieves an internal integer—purpose unknown—held at 0x9c.
	 */
	MxS32 GetUnknown9c() { return m_unk0x9c; }

	/**
	 * @brief [AI] Returns a pointer to the first streaming buffer (possibly current read buffer).
	 */
	MxDSBuffer* GetUnknowna0() { return m_unk0xa0; }

	/**
	 * @brief [AI] Returns a pointer to the second streaming buffer (possibly for prefetch or double buffering).
	 */
	MxDSBuffer* GetUnknowna4() { return m_unk0xa4; }

	/**
	 * @brief [AI] Accumulated streaming duration, used for repeat or seek calculations.
	 */
	MxLong GetUnknowna8() { return m_unk0xa8; }

	/**
	 * @brief [AI] Returns the internal sub-action representing the actual user-level action being streamed.
	 */
	MxDSAction* GetInternalAction() { return m_internalAction; }

	/**
	 * @brief [AI] Gets the buffer offset where streaming is currently positioned.
	 */
	MxU32 GetBufferOffset() { return m_bufferOffset; }

	/**
	 * @brief [AI] Sets the streaming offset/status at 0x94.
	 * @param p_unk0x94 [AI] Value to set.
	 */
	void SetUnknown94(MxU32 p_unk0x94) { m_unk0x94 = p_unk0x94; }

	/**
	 * @brief [AI] Sets the unknown integer at 0x9c.
	 * @param p_unk0x9c [AI] Value to set.
	 */
	void SetUnknown9c(MxS32 p_unk0x9c) { m_unk0x9c = p_unk0x9c; }

	/**
	 * @brief [AI] Assigns a streaming buffer to this action (ownership rules apply).
	 * @param p_unk0xa0 [AI] New buffer.
	 */
	void SetUnknowna0(MxDSBuffer* p_unk0xa0) { m_unk0xa0 = p_unk0xa0; }

	/**
	 * @brief [AI] Assigns a secondary streaming buffer to this action.
	 * @param p_unk0xa4 [AI] New buffer.
	 */
	void SetUnknowna4(MxDSBuffer* p_unk0xa4) { m_unk0xa4 = p_unk0xa4; }

	/**
	 * @brief [AI] Sets the current buffer read offset.
	 * @param p_bufferOffset [AI] New buffer offset to use in streaming operations.
	 */
	void SetBufferOffset(MxU32 p_bufferOffset) { m_bufferOffset = p_bufferOffset; }

	/**
	 * @brief [AI] Clears/deallocates (sets to NULL) the current buffer pointer (a0).
	 */
	void ClearUnknowna0() { m_unk0xa0 = NULL; }

	// SYNTHETIC: LEGO1 0x100cd0b0
	// SYNTHETIC: BETA10 0x101565f0
	// MxDSStreamingAction::`scalar deleting destructor'

private:
	MxU32 m_unk0x94;              ///< [AI] Streaming position/status or offset relating to buffer. [AI]
	MxU32 m_bufferOffset;         ///< [AI] Current offset into streaming buffer (number of bytes/frames read so far). [AI]
	MxS32 m_unk0x9c;              ///< [AI] Internal state (unknown purpose, possibly an error code or progress counter). [AI]
	MxDSBuffer* m_unk0xa0;        ///< [AI] Primary buffer object for streamed media data. [AI]
	MxDSBuffer* m_unk0xa4;        ///< [AI] Secondary buffer (may be used for double buffering or prefetching). [AI]
	MxLong m_unk0xa8;             ///< [AI] Accumulated duration or position (used for loop/time management). [AI]
	undefined2 m_unk0xac;         ///< [AI] Internal field for state; value 2 on init—exact purpose unknown. [AI]
	MxDSAction* m_internalAction; ///< [AI] Optional sub-action representing the payload user task performed by this stream. [AI]
};

#endif // MXDSSTREAMINGACTION_H
