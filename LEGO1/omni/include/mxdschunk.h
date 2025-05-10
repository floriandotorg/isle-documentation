#ifndef MXDSCHUNK_H
#define MXDSCHUNK_H

#include "decomp.h"
#include "mxcore.h"
#include "mxtypes.h"

/// @def DS_CHUNK_BIT1
/// @brief [AI] Flag bit indicating that the data should be released (freed) when the chunk is destroyed. Used internally for resource management in MxDSChunk. [AI]
#define DS_CHUNK_BIT1 0x01

/// @def DS_CHUNK_END_OF_STREAM
/// @brief [AI] Flag bit indicating this chunk is the last in its stream. Used for parsing/streaming indication. [AI]
#define DS_CHUNK_END_OF_STREAM 0x02

/// @def DS_CHUNK_BIT3
/// @brief [AI] Unknown bit flag, marked as BIT3 in decompilation. Usage is unclear. [AI]
#define DS_CHUNK_BIT3 0x04

/// @def DS_CHUNK_SPLIT
/// @brief [AI] Flag indicating this chunk is split (i.e., fragmented and needs reassembling). Used by RAM/disk stream controller when reading chunked media. [AI]
#define DS_CHUNK_SPLIT 0x10

/// @def DS_CHUNK_BIT16
/// @brief [AI] Unspecified bit flag that may be used for platform- or feature- specific logic. [AI]
#define DS_CHUNK_BIT16 0x8000

/// @class MxDSChunk
/// @brief [AI] Represents a chunk of data extracted from a stream (typically from a Mindscape/Mx SI file or streaming media resource). [AI]
/// @details [AI] This class encapsulates a block of raw data together with metadata such as its object id, timestamp, length, and flags. Chunks are used as the standard means of interoperation between the file/disk/ram streaming layer and the other subsystems, including media presentation and game object instantiation. [AI]
///
/// DS "chunks" are a core primitive for all streamed or serialized data in the LEGO Island engine. [AI]
///
/// @see MxCore, MxDSBuffer, MxDSFile [AI]
// VTABLE: LEGO1 0x100dc7f8
// VTABLE: BETA10 0x101c23d0
// SIZE 0x1c
class MxDSChunk : public MxCore {
public:
	/// @brief [AI] Constructs a new, empty chunk. All members initialized to safe defaults. [AI]
	MxDSChunk();

	/// @brief [AI] Virtual destructor. Cleans up any owned chunk data if flagged by DS_CHUNK_BIT1. [AI]
	~MxDSChunk() override;

	/// @brief [AI] Returns the class name ("MxDSChunk") for runtime type identification. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10101e6c
		return "MxDSChunk";
	}

	/// @brief [AI] Checks if this object or any parent class matches the provided class name string. [AI]
	/// @param p_name Name of the class to compare to. [AI]
	/// @return True if this class matches the provided name, or is a subclass thereof. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSChunk::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Returns the fixed size of the chunk header, typically used for parsing binary streams. [AI]
	/// @return Size in bytes of the chunk header. [AI]
	static MxU32 GetHeaderSize();

	/// @brief [AI] Returns the total size (header + data) of a chunk from a raw buffer pointer. Used when parsing binary memory blocks. [AI]
	/// @param p_buffer Pointer to the start of the chunk buffer. [AI]
	/// @return Total size (in bytes) of the chunk, including header. [AI]
	static MxU32 Size(MxU8* p_buffer) { return (*(MxU32*) (p_buffer + 4) & 1) + *(MxU32*) (p_buffer + 4) + 8; }

	/// @brief [AI] Returns a pointer to the end of this chunk for sequential iteration through a chunked buffer. [AI]
	/// @param p_buffer Pointer to the start of the chunk. [AI]
	/// @return Pointer to the byte immediately after this chunk. [AI]
	static MxU8* End(MxU8* p_buffer) { return p_buffer + Size(p_buffer); }

	/// @brief [AI] Sets all chunk header flag bits. [AI]
	/// @param p_flags New flags (see DS_CHUNK_* defines above). [AI]
	void SetChunkFlags(MxU16 p_flags) { m_flags = p_flags; }

	/// @brief [AI] Sets the object id for this chunk (links chunk data to logical entity, resource, or action). [AI]
	/// @param p_objectid New object id for the chunk. [AI]
	void SetObjectId(undefined4 p_objectid) { m_objectId = p_objectid; }

	/// @brief [AI] Sets the time (timestamp/tick/frame) associated with this chunk. [AI]
	/// @param p_time Relative or absolute time value for this chunk. [AI]
	void SetTime(MxLong p_time) { m_time = p_time; }

	/// @brief [AI] Sets the payload data length for this chunk. [AI]
	/// @param p_length Length in bytes of the chunk data. [AI]
	void SetLength(MxU32 p_length) { m_length = p_length; }

	/// @brief [AI] Sets the pointer to the raw payload data (may or may not be owned by chunk object). [AI]
	/// @param p_data Data pointer. If DS_CHUNK_BIT1 is set in flags, this pointer is owned and deleted by this object. [AI]
	void SetData(MxU8* p_data) { m_data = p_data; }

	/// @brief [AI] Returns the chunk's flag bitfield. [AI]
	MxU16 GetChunkFlags() { return m_flags; }

	/// @brief [AI] Returns the object id of this chunk. [AI] 
	undefined4 GetObjectId() { return m_objectId; }

	/// @brief [AI] Returns the time (timestamp or tick) associated with this chunk. [AI]
	MxLong GetTime() { return m_time; }

	/// @brief [AI] Returns the length in bytes of the data payload. [AI]
	MxU32 GetLength() { return m_length; }

	/// @brief [AI] Returns a pointer to the start of the data payload. [AI]
	MxU8* GetData() { return m_data; }

	/// @brief [AI] Releases (deletes) data payload if present, regardless of flags; call to explicitly free memory and avoid leaks, especially when chunk objects are reused. [AI]
	void Release()
	{
		if (m_data) {
			delete[] m_data;
		}
	}

	// SYNTHETIC: LEGO1 0x100be150
	// SYNTHETIC: BETA10 0x101474c0
	// MxDSChunk::`scalar deleting destructor'

protected:
	MxU16 m_flags;    ///< @brief [AI] Flag bitfield indicating properties/status of the chunk. See DS_CHUNK_* defines. [AI]
	MxU32 m_objectId; ///< @brief [AI] Logical id field linking chunk to a resource, action, or entity. [AI]
	MxLong m_time;    ///< @brief [AI] Timestamp (tick/frame) value for the chunk. Used for ordering, sequencing, and synchronization. [AI]
	MxU32 m_length;   ///< @brief [AI] Number of bytes of data in this chunk's payload. [AI]
	MxU8* m_data;     ///< @brief [AI] Pointer to chunk's raw data buffer. Ownership is determined by DS_CHUNK_BIT1 flag and usage context. [AI]
};

#endif // MXDSCHUNK_H
