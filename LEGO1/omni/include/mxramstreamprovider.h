#ifndef MXRAMSTREAMPROVIDER_H
#define MXRAMSTREAMPROVIDER_H

#include "mxstreamprovider.h"

// VTABLE: LEGO1 0x100dd0d0
// VTABLE: BETA10 0x101c2ca8
// SIZE 0x24
/**
 * @brief [AI] Provides RAM-backed stream data access. Handles loading entire SI files into memory buffers for fast reading and easy chunk combination. Subclass of MxStreamProvider.
 * @details [AI] The MxRAMStreamProvider loads the whole referenced SI file either from the HDD or CD to a dedicated memory buffer, and provides methods to access the buffer directly in various formats (raw bytes, DWORDs). It is essential for efficient in-memory streaming access, especially for objects that don't require disk streaming.
 */
class MxRAMStreamProvider : public MxStreamProvider {
public:
	/**
	 * @brief [AI] Constructs a new MxRAMStreamProvider and initializes the buffer members to defaults/nullptr.
	 */
	MxRAMStreamProvider();

	/**
	 * @brief [AI] Destroys the MxRAMStreamProvider, releasing all memory buffers.
	 */
	~MxRAMStreamProvider() override;

	/**
	 * @brief [AI] Returns the runtime class name string for this object.
	 * @return [AI] "MxRAMStreamProvider"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102864
		return "MxRAMStreamProvider";
	}

	/**
	 * @brief [AI] Runtime type check against this and parent class.
	 * @param p_name Name to check type against (case-sensitive/classname) [AI]
	 * @return [AI] Returns true if p_name matches this class or any parent.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxRAMStreamProvider::ClassName()) || MxStreamProvider::IsA(p_name);
	}

	/**
	 * @brief [AI] Loads the requested resource (SI file) fully into memory, prepares internal buffers for fast access. Tries HDD, then CD for the file.
	 * @param p_resource Stream controller providing atom name and linkage. [AI]
	 * @return [AI] SUCCESS if resource could be loaded, FAILURE if not.
	 */
	MxResult SetResourceToGet(MxStreamController* p_resource) override; // vtable+0x14

	/**
	 * @brief [AI] Returns the loaded file's full byte size. Returns 0 if nothing loaded.
	 */
	MxU32 GetFileSize() override; // vtable+0x18

	/**
	 * @brief [AI] Returns number of stream buffers contained (always 1 for RAM provider). [AI]
	 */
	MxS32 GetStreamBuffersNum() override; // vtable+0x1c

	/**
	 * @brief [AI] Returns length (number) of 32-bit words in buffer (DWORD units).
	 */
	MxU32 GetLengthInDWords() override; // vtable+0x24

	/**
	 * @brief [AI] Returns pointer to the buffer as array of 32bit values (DWORDs), for data accessing aligned to 4 bytes.
	 */
	MxU32* GetBufferForDWords() override; // vtable+0x28

	/**
	 * @brief [AI] Returns pointer to raw file buffer as byte array.
	 */
	MxU8* GetBufferOfFileSize() { return m_pBufferOfFileSize; }

protected:
	MxU32 m_bufferSize;        ///< [AI] Actual size in bytes of the buffer allocated for file (may match or exceed file size).
	MxU32 m_fileSize;          ///< [AI] Size in bytes of the loaded resource file.
	MxU8* m_pBufferOfFileSize; ///< [AI] Pointer to full byte buffer with loaded SI file contents.
	MxU32 m_lengthInDWords;    ///< [AI] Number of DWORD (4 byte) entries in buffer.
	MxU32* m_bufferForDWords;  ///< [AI] Pointer to DWORD buffer for 4-byte-aligned access to SI chunk data.
};

// SYNTHETIC: LEGO1 0x100d0a30
// MxRAMStreamProvider::`scalar deleting destructor'

/**
 * @brief [AI] Rearranges split and unordered chunks within a memory buffer for SI resource files, and merges related ones to create a contiguous buffer. Also fixes DS_CHUNK_SPLIT flags where necessary.
 * @param p_fileSizeBuffer [AI] Buffer containing the file data (after being loaded by MxRAMStreamProvider).
 * @param p_fileSize [AI] The size in bytes of p_fileSizeBuffer.
 * @return [AI] The size in bytes of the output contiguous (merged) buffer.
 * @details [AI] This is a global helper for SI file chunk merging as used by MxRAMStreamProvider on load.
 */
MxU32 ReadData(MxU8* p_fileSizeBuffer, MxU32 p_fileSize);

#endif // MXRAMSTREAMPROVIDER_H
