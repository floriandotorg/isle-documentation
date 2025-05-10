#ifndef MXDSFILE_H
#define MXDSFILE_H

#include "mxdssource.h"
#include "mxio.h"
#include "mxstring.h"
#include "mxtypes.h"

#include <windows.h>

/**
 * @brief [AI] Represents a source file handler for SI (Streamer Interface) files, providing buffered access for reading SI file data and managing chunks.
 * 
 * This class is responsible for opening, reading, and managing SI files compliant with major version 2 and minor version 2, and makes header and data chunk information available to OMNI engine subsystems.
 * 
 * The MxDSFile can be instructed to defer chunk reading until explicitly requested (via the m_skipReadingChunks flag).
 * 
 * Inherits from MxDSSource.
 */
class MxDSFile : public MxDSSource {
public:
	/**
	 * @brief [AI] Constructs an MxDSFile object with the specified filename and chunk-read behavior.
	 * @param p_filename Path to the SI file to open. [AI]
	 * @param p_skipReadingChunks If nonzero, chunk reading is skipped until explicitly called through ReadChunks. [AI]
	 */
	MxDSFile(const char* p_filename, MxULong p_skipReadingChunks);

#ifdef ISLE_APP
	/**
	 * @brief [AI] Destructor. Automatically closes the file and releases associated resources. [AI]
	 */
	~MxDSFile() override { Close(); }
#else
	/**
	 * @brief [AI] Destructor (exported for DLL builds). Automatically closes the file and releases associated resources. [AI]
	 */
	__declspec(dllexport) ~MxDSFile() override { Close(); }
#endif

	/**
	 * @brief [AI] Class identification.
	 * @return Returns this object's class name ("MxDSFile"). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102594
		return "MxDSFile";
	}

	/**
	 * @brief [AI] Type comparison with other class names (for dynamic type identification).
	 * @param p_name The name of the class for comparison. [AI]
	 * @return True if the provided name matches this or a parent class, otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSFile::ClassName()) || MxDSSource::IsA(p_name);
	}

	/**
	 * @brief [AI] Opens the SI file for reading or writing with the specified style flags.
	 * @param [in] p_uStyle Flags for file access mode (e.g. read/write). [AI]
	 * @details [AI] Also optionally reads SI chunks immediately, unless m_skipReadingChunks is enabled.
	 */
	MxResult Open(MxULong) override;                 // vtable+0x14
	
	/**
	 * @brief [AI] Closes the file and releases internal file buffers. [AI]
	 * @details [AI] Resets file state and deletes memory buffer of loaded chunk data.
	 */
	MxResult Close() override;                       // vtable+0x18

	/**
	 * @brief [AI] Reads up to the specified number of bytes from the file into a buffer.
	 * @param p_buf Buffer to read into. [AI]
	 * @param p_nbytes Number of bytes to read. [AI]
	 */
	MxResult Read(unsigned char*, MxULong) override; // vtable+0x20

	/**
	 * @brief [AI] Seeks to an absolute or relative position in the file.
	 * @param p_lOffset Offset to seek to (from origin). [AI]
	 * @param p_iOrigin One of SEEK_SET, SEEK_CUR, or SEEK_END. [AI]
	 */
	MxResult Seek(MxLong, MxS32) override;           // vtable+0x24

	/**
	 * @brief [AI] Returns the SI chunk's buffer size, as obtained from the SI file header. [AI]
	 */
	MxULong GetBufferSize() override;                // vtable+0x28

	/**
	 * @brief [AI] Returns the number of streaming buffers, as specified in the SI file header. [AI]
	 */
	MxULong GetStreamBuffersNum() override;          // vtable+0x2c

	/**
	 * @brief [AI] Sets the SI file's name.
	 * @param p_filename New filename to use for this object. [AI]
	 */
	void SetFileName(const char* p_filename) { m_filename = p_filename; }

	/**
	 * @brief [AI] Calculates and returns the file size by querying the system (Windows GetFileSize).
	 * @return The file's size, or an error code from GetFileSize. [AI]
	 */
	MxS32 CalcFileSize() { return GetFileSize(m_io.m_info.hmmio, NULL); }

	// SIZE 0x0c
	/**
	 * @brief [AI] Represents the SI file stream's header chunk, containing versioning and SI buffer info. [AI]
	 */
	struct ChunkHeader {
		/**
		 * @brief [AI] Default constructor. Initializes all fields to zero. [AI]
		 */
		ChunkHeader() : m_majorVersion(0), m_minorVersion(0), m_bufferSize(0), m_streamBuffersNum(0) {}

		MxS16 m_majorVersion;     ///< [AI] Major SI file version (e.g., 2 for LEGO Island SI files).
		MxS16 m_minorVersion;     ///< [AI] Minor SI file version (e.g., 2 for LEGO Island SI files).
		MxULong m_bufferSize;     ///< [AI] Buffer size defined for the SI stream (bytes).
		MxS16 m_streamBuffersNum; ///< [AI] Number of streaming buffers for this SI file.
		MxS16 m_reserved;         ///< [AI] Reserved for potential SI formatting/extensions.
	};

private:
	/**
	 * @brief [AI] Reads SI RIFF and chunk data sections from the file and fills the internal data buffer.
	 * @details [AI] Finds the OMNI RIFF, then the header and object chunk, reads and verifies version, fills buffer. [AI]
	 * @return SUCCESS if chunks were read and parsed correctly, else FAILURE. [AI]
	 */
	MxResult ReadChunks();

	MxString m_filename;  ///< [AI] SI file name/path string. [AI]
	MXIOINFO m_io;        ///< [AI] Structure managing buffered I/O for this stream. [AI]
	ChunkHeader m_header; ///< [AI] Parsed SI file header. [AI]

	/**
	 * @brief [AI] If false, SI chunks are read immediately on open; if true, chunks are deferred until ReadChunks is explicitly called. [AI]
	 */
	MxULong m_skipReadingChunks; // 0x78
};

#endif // MXDSFILE_H