#ifndef MXSTREAMCHUNK_H
#define MXSTREAMCHUNK_H

#include "mxdschunk.h"

class MxDSBuffer;
class MxDSSubscriberList;

// VTABLE: LEGO1 0x100dc2a8
// VTABLE: BETA10 0x101c1d20
// SIZE 0x20
/**
 * @brief [AI] Represents a streamable chunk of data, typically sourced from a media buffer and designed for
 * notification and streaming within Lego Island's resource system. Derived from MxDSChunk, it is used to facilitate chunk-based streaming,
 * particularly in video and audio playback pipelines.
 * @details [AI] Holds meta-data and a reference to an MxDSBuffer containing the raw data, and can parse
 * and propagate its chunk to a list of stream subscribers.
 */
class MxStreamChunk : public MxDSChunk {
public:
	/**
	 * @brief [AI] Constructs a new MxStreamChunk with a null buffer pointer.
	 */
	MxStreamChunk() : m_buffer(NULL) {}

	/**
	 * @brief [AI] Cleans up the stream chunk, releasing its associated buffer if any.
	 */
	~MxStreamChunk() override;

	/**
	 * @brief [AI] Returns the class name identifier for runtime type checking and reflection.
	 * @return Pointer to string "MxStreamChunk". [AI] 
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10101e5c
		return "MxStreamChunk";
	}

	/**
	 * @brief [AI] Performs runtime type checking against this or parent class names.
	 * @param p_name The class name string to compare against. [AI]
	 * @return TRUE if p_name matches this class or ancestors; FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxStreamChunk::ClassName()) || MxDSChunk::IsA(p_name);
	}

	/**
	 * @brief [AI] Retrieves the buffer associated with this chunk.
	 * @return Pointer to the MxDSBuffer for this chunk, or NULL if unset. [AI]
	 */
	MxDSBuffer* GetBuffer() { return m_buffer; }

	/**
	 * @brief [AI] Reads the chunk's header and initializes from a chunk data buffer of a streamed data segment.
	 * @param p_buffer The buffer to associate with this stream chunk. [AI]
	 * @param p_chunkData Pointer to raw chunk data; expects the "MxCh" identifier in the first 4 bytes. [AI]
	 * @return Returns SUCCESS if properly initialized and associated; otherwise FAILURE. [AI]
	 */
	MxResult ReadChunk(MxDSBuffer* p_buffer, MxU8* p_chunkData);

	/**
	 * @brief [AI] Reads this chunk's header fields from the provided chunk data.
	 * @param p_chunkData Pointer to the start of header bytes within a chunk. [AI]
	 * @return Number of bytes read from the header. [AI]
	 */
	MxU32 ReadChunkHeader(MxU8* p_chunkData);

	/**
	 * @brief [AI] Dispatches this stream chunk to a list of subscribers matching certain criteria.
	 * @param p_subscriberList The list of subscribers eligible to receive this chunk. [AI]
	 * @param p_append Whether the chunk data should be appended to existing data. [AI]
	 * @param p_obj24val Additional identity or filtering parameter (typically corresponds to object state/ID). [AI]
	 * @return SUCCESS if at least one eligible subscriber received the chunk; otherwise FAILURE. [AI]
	 */
	MxResult SendChunk(MxDSSubscriberList& p_subscriberList, MxBool p_append, MxS16 p_obj24val);

	/**
	 * @brief [AI] Sets the buffer reference for this chunk, without incrementing the reference count.
	 * @param p_buffer The buffer to associate with this chunk. [AI]
	 */
	void SetBuffer(MxDSBuffer* p_buffer);

	/**
	 * @brief [AI] Utility to cast a chunk header buffer into the flags field pointer, facilitating direct parsing.
	 * @param p_buffer Pointer to start of a chunk header. [AI]
	 * @return Pointer to the MxU16 flags within the header. [AI]
	 */
	static MxU16* IntoFlags(MxU8* p_buffer);

	/**
	 * @brief [AI] Utility to cast a chunk header buffer into the objectId field pointer, facilitating direct parsing.
	 * @param p_buffer Pointer to start of a chunk header. [AI]
	 * @return Pointer to the MxU32 objectId within the header. [AI]
	 */
	static MxU32* IntoObjectId(MxU8* p_buffer);

	/**
	 * @brief [AI] Utility to cast a chunk header buffer into the time field pointer, facilitating direct parsing.
	 * @param p_buffer Pointer to start of a chunk header. [AI]
	 * @return Pointer to the MxLong time field within the header. [AI]
	 */
	static MxLong* IntoTime(MxU8* p_buffer);

	/**
	 * @brief [AI] Utility to cast a chunk header buffer into the data length field pointer, facilitating direct parsing.
	 * @param p_buffer Pointer to start of a chunk header. [AI]
	 * @return Pointer to the MxU32 length field within the header. [AI]
	 */
	static MxU32* IntoLength(MxU8* p_buffer);

private:
	MxDSBuffer* m_buffer; ///< @brief [AI] Reference to the media buffer holding the actual chunk data for streaming operations.
};

// SYNTHETIC: LEGO1 0x100b20a0
// MxStreamChunk::`scalar deleting destructor'

#endif // MXSTREAMCHUNK_H
