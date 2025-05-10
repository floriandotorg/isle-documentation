#ifndef MXDSSOURCE_H
#define MXDSSOURCE_H

#include "mxcore.h"
#include "mxdsbuffer.h"

// VTABLE: LEGO1 0x100dc8c8
// VTABLE: BETA10 0x101c2450
// SIZE 0x14
/**
 * @brief [AI] Abstract base class representing a source of streamable data, providing an interface for reading,
 *        seeking, and buffer management used for audio/video/other resource streaming in the LEGO Island engine.
 *        Handles internal buffer memory, length in double words (DWORDs), and position management.
 *        Derived classes implement low-level IO such as file- or memory-backed streams.
 * @details [AI] Used as a parent for data sources (such as SI files, memory buffers, etc.) that can be consumed
 * by higher-level deserialization or playback mechanisms (e.g., MxDSFile, MxDSMPEG, etc.). Not intended
 * for external use directly; to be subclassed for data-specific sources. Manages a buffer (allocated as an array of MxU32)
 * and an internal length for data integrity and direct access.
 */
class MxDSSource : public MxCore {
public:
	/**
	 * @brief [AI] Constructor, initializes buffer pointer to NULL, position to -1 and lengthInDWords to 0.
	 */
	MxDSSource() : m_lengthInDWords(0), m_pBuffer(NULL), m_position(-1) {}

	/**
	 * @brief [AI] Virtual destructor, frees internal buffer if allocated.
	 */
	~MxDSSource() override { delete[] m_pBuffer; }

	/**
	 * @brief [AI] Returns the class name string ("MxDSSource"). Used for runtime type checks.
	 * @return [AI] String literal "MxDSSource".
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102588
		return "MxDSSource";
	}

	/**
	 * @brief [AI] Runtime type information check.
	 * Returns true if the object's class name matches p_name or matches a parent class.
	 * Used for type-safe downcasting.
	 * @param p_name Name of the type to check.
	 * @return TRUE if this object is a MxDSSource or matches parent; FALSE otherwise.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSource::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief [AI] Opens the source (e.g., a file, memory buffer, etc).
	 * The meaning of the parameter depends on the implementation.
	 * @param p_param [AI] Implementation-specific parameter (may be a filename handle, a memory buffer, etc).
	 * @return Implementation-defined result; generally, negative on failure.
	 */
	virtual MxLong Open(MxULong p_param) = 0; // vtable+0x14

	/**
	 * @brief [AI] Closes the source and releases any resources held.
	 * @return Implementation-defined result; generally, negative on failure.
	 */
	virtual MxLong Close() = 0; // vtable+0x18

	/**
	 * @brief [AI] Reads from this source into a provided MxDSBuffer up to the buffer's current write offset.
	 * @param p_buffer [AI] Target buffer to read data into.
	 * @return Result indicating success or nature of failure.
	 */
	virtual MxResult ReadToBuffer(MxDSBuffer* p_buffer)
	{
		return Read(p_buffer->GetBuffer(), p_buffer->GetWriteOffset());
	} // vtable+0x1c

	/**
	 * @brief [AI] Read a specified number of bytes into user-supplied buffer, starting at the current position.
	 * Implemented by each derived class.
	 * @param p_dest [AI] Destination buffer.
	 * @param p_count [AI] Number of bytes to read.
	 * @return Result indicating success or failure.
	 */
	virtual MxResult Read(unsigned char* p_dest, MxULong p_count) = 0; // vtable+0x20

	/**
	 * @brief [AI] Seek to a specific position in the source, relative to the start, current, or end.
	 * @param p_offset [AI] Seek offset.
	 * @param p_origin [AI] Reference position (`SEEK_SET`, `SEEK_CUR`, or `SEEK_END`).
	 * @return New position or negative on failure.
	 */
	virtual MxLong Seek(MxLong p_offset, MxS32 p_origin) = 0; // vtable+0x24

	/**
	 * @brief [AI] Returns the total buffer size in bytes (implementation-dependent).
	 */
	virtual MxULong GetBufferSize() = 0; // vtable+0x28

	/**
	 * @brief [AI] Returns the number of buffers the stream is internally segmented into (for multi-buffered streaming).
	 */
	virtual MxULong GetStreamBuffersNum() = 0; // vtable+0x2c

	/**
	 * @brief [AI] Gets the length of the data in DWORDs (32-bit units). This is often used to determine streamable length.
	 * @return [AI] Length in DWORDs.
	 */
	virtual MxLong GetLengthInDWords() { return m_lengthInDWords; } // vtable+0x30

	/**
	 * @brief [AI] Returns a pointer to the internal buffer as a DWORD (32-bit) pointer.
	 * Useful for direct access to loaded or mapped data.
	 * @return [AI] Pointer to buffer, or NULL if not allocated.
	 */
	virtual MxU32* GetBuffer() { return m_pBuffer; } // vtable+0x34

	/**
	 * @brief [AI] Returns the current per-source seek/read/write position.
	 * @return Current position (implementation meaning: byte offset, index, etc). -1 if not set.
	 */
	MxLong GetPosition() const { return m_position; }

protected:
	MxULong m_lengthInDWords; ///< @brief [AI] Length of valid data in the stream, in DWORDs (32-bit units). Used for sizing and range checking.
	MxU32* m_pBuffer;         ///< @brief [AI] Pointer to allocated buffer, or NULL if uninitialized. Contains the raw read/streamed data.
	MxLong m_position;        ///< @brief [AI] Current seek/read/write position in the source. -1 if uninitialized, otherwise logical/physical offset.
};

// SYNTHETIC: LEGO1 0x100c00a0
// MxDSSource::`scalar deleting destructor'

#endif // MXDSSOURCE_H
