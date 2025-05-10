#ifndef MXIO_H
#define MXIO_H

#include "mxtypes.h"

// mmsystem.h requires inclusion of windows.h before
// clang-format off
#include <windows.h>
#include <mmsystem.h>
// clang-format on

#if defined(_M_IX86) || defined(__i386__)
#define MXIO_MINFO_MFILE
#endif

// SIZE 0x48

/**
 * @brief [AI] A wrapper for low-level file I/O, abstracting MMIOINFO functionality, and providing additional buffer and chunk management geared toward wave and RIFF file manipulation.
 * @details [AI] MXIOINFO manages opening, reading, writing, seeking, and closing files at a low level, optionally using an internal buffer for efficiency. It also provides chunk-based access, suitable for managing hierarchical file formats like RIFF (common for audio/video assets). This class also manages chunk and pad byte considerations when traversing file structures.
 */
class MXIOINFO {
public:
	/**
	 * @brief [AI] Constructs a new MXIOINFO instance and initializes all struct members to zero.
	 */
	MXIOINFO();

	/**
	 * @brief [AI] Destructor, closes the file and releases all memory associated with buffers if necessary.
	 */
	~MXIOINFO();

	/**
	 * @brief [AI] Opens a file for buffered/unbuffered I/O, initializing MMIOINFO and (optionally) internal buffer based on flags.
	 * @param p_filename The filename (path) to open. [AI]
	 * @param p_flags Flags determining mode (MMIO_ALLOCBUF, MMIO_READ, MMIO_WRITE, etc). [AI]
	 * @return MMIOERR_CANNOTOPEN (failed) or MMSYSERR_NOERROR (success). [AI]
	 */
	MxU16 Open(const char* p_filename, MxULong p_flags);

	/**
	 * @brief [AI] Closes the file and releases its resources, including buffer memory if owned.
	 * @param p_unused Reserved/ignored. [AI]
	 * @return MMSYSERR_NOERROR on success. [AI]
	 */
	MxU16 Close(MxLong p_unused);

	/**
	 * @brief [AI] Reads a number of bytes from the file or buffer into the destination buffer.
	 * @param p_buf Pointer to the buffer to read data into. [AI]
	 * @param p_len Number of bytes to read. [AI]
	 * @return The number of bytes actually read; 0 on error or end of file. [AI]
	 */
	MxLong Read(void* p_buf, MxLong p_len);

	/**
	 * @brief [AI] Writes data to the file or internal buffer.
	 * @param p_buf Buffer containing data to write. [AI]
	 * @param p_len Number of bytes to write. [AI]
	 * @return The number of bytes actually written, or 0 on error. [AI]
	 */
	MxLong Write(void* p_buf, MxLong p_len);

	/**
	 * @brief [AI] Seeks to a specific position in the file (or file buffer).
	 * @param p_offset Byte offset to seek to (absolute or relative as determined by p_origin). [AI]
	 * @param p_origin One of SEEK_SET/SEEK_CUR/SEEK_END. [AI]
	 * @return The resulting absolute file position, or -1 on failure. [AI]
	 */
	MxLong Seek(MxLong p_offset, MxLong p_origin);

	/**
	 * @brief [AI] Changes the buffer used for internal I/O (applies and releases old buffer if owned).
	 * @param p_buf Pointer to new buffer. [AI]
	 * @param p_len Length of buffer, in bytes. [AI]
	 * @param p_unused Ignored. [AI]
	 * @return MMSYSERR_NOERROR on success. [AI]
	 */
	MxU16 SetBuffer(char* p_buf, MxLong p_len, MxLong p_unused);

	/**
	 * @brief [AI] Flushes contents of the buffer to disk if necessary (e.g., if data is dirty).
	 * @param p_unused Ignored. [AI]
	 * @return Status code; MMIOERR_CANNOTWRITE if a write failed. [AI]
	 */
	MxU16 Flush(MxU16 p_unused);

	/**
	 * @brief [AI] Advances the buffer state for reading/writing the next block, committing dirty writes and loading/refreshing as necessary.
	 * @param p_option Indicates MMIO_READ or MMIO_WRITE operation. [AI]
	 * @return MMSYSERR_NOERROR on success. [AI]
	 */
	MxU16 Advance(MxU16 p_option);

	/**
	 * @brief [AI] Descends into a specific RIFF or LIST chunk in a hierarchical file, reading chunk headers and updating MMCKINFO accordingly.
	 * @param p_chunkInfo The chunk information structure to fill. [AI]
	 * @param p_parentInfo The parent chunk, or NULL for top-level. [AI]
	 * @param p_descend MMIO_FINDLIST, MMIO_FINDRIFF, or 0 for untyped. [AI]
	 * @return Status code; MMIOERR_CANNOTREAD, MMIOERR_CHUNKNOTFOUND, or success. [AI]
	 */
	MxU16 Descend(MMCKINFO* p_chunkInfo, const MMCKINFO* p_parentInfo, MxU16 p_descend);

	/**
	 * @brief [AI] Ascends from a chunk in a hierarchical file, correcting chunk size and finishing the chunk correctly.
	 * @param p_chunkInfo Chunk structure to ascend out from (also receives size fixup). [AI]
	 * @param p_ascend Not used; reserved for future/protocol compatibility. [AI]
	 * @return MMSYSERR_NOERROR on success. [AI]
	 */
	MxU16 Ascend(MMCKINFO* p_chunkInfo, MxU16 p_ascend);

	/**
	 * @brief [AI] Creates a new hierarchical chunk (RIFF or LIST or other type), writing initial chunk header.
	 * @param p_chunkInfo Chunk structure to initialize. [AI]
	 * @param p_create MMIO_CREATERIFF, MMIO_CREATELIST, or default. [AI]
	 * @return MMSYSERR_NOERROR on success. [AI]
	 */
	MxU16 CreateChunk(MMCKINFO* p_chunkInfo, MxU16 p_create);

	/**
	 * @brief [AI] Underlying MMIOINFO structure used for buffered and low-level file I/O.
	 * @details [AI] In MXIOINFO, 'hmmio' (in MMIOINFO) is used as an HFILE rather than an HMMIO, supporting custom I/O operations.
	 */
	MMIOINFO m_info;

#ifndef MXIO_MINFO_MFILE
	/**
	 * @brief [AI] File handle used when MMIOINFO is not used as a file (HFILE abstraction).
	 */
	HFILE m_file;
#endif
};

#endif // MXIO_H