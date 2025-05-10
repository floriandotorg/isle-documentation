#ifndef __LEGOSTORAGE_H
#define __LEGOSTORAGE_H

#include "legotypes.h"
#include "mxgeometry/mxgeometry3d.h"
#include "mxstring.h"

#include <stdio.h>

// VTABLE: LEGO1 0x100d7d80
// SIZE 0x08
/**
 * @brief Abstract base class providing an interface for file-like storage with binary and text read/write operations. [AI]
 * @details Used as a polymorphic abstraction over file-backed and memory-backed streams for reading and writing primary built-in data types (strings, numbers, vectors) in LEGO Island. [AI]
 */
class LegoStorage {
public:
	/**
	 * @brief File open mode flags for storage operations. [AI]
	 * @details c_read = Open for reading, c_write = Open for writing, c_text = Open as text file (else binary). [AI]
	 */
	enum OpenFlags {
		c_read = 1,  ///< Open for read operations. [AI]
		c_write = 2, ///< Open for write operations. [AI]
		c_text = 4   ///< Open in text mode, otherwise binary. [AI]
	};

	/**
	 * @brief Default constructor initializing mode to zero. [AI]
	 */
	LegoStorage() : m_mode(0) {}

	/**
	 * @brief Virtual destructor for safe polymorphic destruction. [AI]
	 */
	virtual ~LegoStorage() {}

	/**
	 * @brief Read bytes from storage into buffer. [AI]
	 * @param p_buffer Destination buffer [AI]
	 * @param p_size Number of bytes to read [AI]
	 * @return See implementation for SUCCESS/FAILURE [AI]
	 */
	virtual LegoResult Read(void* p_buffer, LegoU32 p_size) = 0;        // vtable+0x04

	/**
	 * @brief Write bytes from buffer into storage. [AI]
	 * @param p_buffer Source buffer [AI]
	 * @param p_size Number of bytes to write [AI]
	 * @return See implementation for SUCCESS/FAILURE [AI]
	 */
	virtual LegoResult Write(const void* p_buffer, LegoU32 p_size) = 0; // vtable+0x08

	/**
	 * @brief Get current read/write position in stream. [AI]
	 * @param p_position Reference to receive current position [AI]
	 * @return See implementation for SUCCESS/FAILURE [AI]
	 */
	virtual LegoResult GetPosition(LegoU32& p_position) = 0;            // vtable+0x0c

	/**
	 * @brief Set current read/write position in stream. [AI]
	 * @param p_position New position to set [AI]
	 * @return See implementation for SUCCESS/FAILURE [AI]
	 */
	virtual LegoResult SetPosition(LegoU32 p_position) = 0;             // vtable+0x10

	/**
	 * @brief Returns TRUE if object was opened in write mode. [AI]
	 * @return TRUE if mode is write, FALSE otherwise [AI]
	 */
	virtual LegoBool IsWriteMode() { return m_mode == c_write; } // vtable+0x14

	/**
	 * @brief Returns TRUE if object was opened in read mode. [AI]
	 * @return TRUE if mode is read, FALSE otherwise [AI]
	 */
	virtual LegoBool IsReadMode() { return m_mode == c_read; } // vtable+0x18

	/**
	 * @brief Writes a length-prefixed string to storage. [AI]
	 * @details String is prefixed by a 16-bit length, then content without null terminator. [AI]
	 * @param p_data Null-terminated string to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteString(const char* p_data)
	{
		LegoS16 length = strlen(p_data);
		WriteS16(length);
		Write(p_data, length);
		return this;
	}

	/**
	 * @brief Writes an 8-bit unsigned value to storage. [AI]
	 * @param p_data Value to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteU8(LegoU8 p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a 16-bit signed value to storage. [AI]
	 * @param p_data Value to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteS16(LegoS16 p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a 16-bit unsigned value to storage. [AI]
	 * @param p_data Value to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteU16(LegoU16 p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a 32-bit signed value to storage. [AI]
	 * @param p_data Value to write [AI]
	 * @return this for chaining [AI]
	 * @details [AI] Note: Parameter type may be incompatible with LegoS32.
	 */
	LegoStorage* WriteS32(MxS32 p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a 32-bit unsigned value to storage. [AI]
	 * @param p_data Value to write [AI]
	 * @return this for chaining [AI]
	 * @details [AI] Note: Parameter type may be incompatible with LegoU32.
	 */
	LegoStorage* WriteU32(MxU32 p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a floating-point (single-precision) value to storage. [AI]
	 * @param p_data Floating-point value to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteFloat(LegoFloat p_data)
	{
		Write(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Writes a 3D vector (three floats) to storage. [AI]
	 * @param p_data Vector to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteVector(Mx3DPointFloat p_data)
	{
		WriteFloat(p_data[0]);
		WriteFloat(p_data[1]);
		WriteFloat(p_data[2]);
		return this;
	}

	/**
	 * @brief Writes a length-prefixed MxString to storage. [AI]
	 * @param p_data String to write [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* WriteMxString(MxString p_data)
	{
		WriteString(p_data.GetData());
		return this;
	}

	/**
	 * @brief Reads a length-prefixed string from storage. [AI]
	 * @details Reads string length, then chars (not null terminated), then writes '\0' at end. [AI]
	 * @param p_data Output character buffer (must be large enough for string + null terminator). [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadString(char* p_data)
	{
		LegoS16 length;
		ReadS16(length);
		Read(p_data, length);
		p_data[length] = '\0';
		return this;
	}

	/**
	 * @brief Reads an 8-bit unsigned value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadU8(LegoU8& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a 16-bit signed value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadS16(LegoS16& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a 16-bit unsigned value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadU16(LegoU16& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a 32-bit signed value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 * @details [AI] Note: Parameter type may be incompatible with LegoS32.
	 */
	LegoStorage* ReadS32(MxS32& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a 32-bit unsigned value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 * @details [AI] Note: Parameter type may be incompatible with LegoU32.
	 */
	LegoStorage* ReadU32(MxU32& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a floating-point (single-precision) value from storage. [AI]
	 * @param p_data Output variable to receive value [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadFloat(LegoFloat& p_data)
	{
		Read(&p_data, sizeof(p_data));
		return this;
	}

	/**
	 * @brief Reads a 3D vector (three floats) from storage. [AI]
	 * @param p_data Output variable to receive vector [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadVector(Mx3DPointFloat& p_data)
	{
		ReadFloat(p_data[0]);
		ReadFloat(p_data[1]);
		ReadFloat(p_data[2]);
		return this;
	}

	/**
	 * @brief Reads a length-prefixed string and stores it in an MxString object. [AI]
	 * @param p_data Output MxString to hold the read text [AI]
	 * @return this for chaining [AI]
	 */
	LegoStorage* ReadMxString(MxString& p_data)
	{
		LegoS16 length;
		ReadS16(length);

		char* text = new char[length + 1];
		Read(text, length);

		text[length] = '\0';
		p_data = text;
		delete[] text;
		return this;
	}

	// SYNTHETIC: LEGO1 0x10045b00
	// LegoStorage::`scalar deleting destructor'

protected:
	/**
	 * @brief File open/access mode. See OpenFlags enum. [AI]
	 */
	LegoU8 m_mode; // 0x04
};

// VTABLE: LEGO1 0x100db710
// SIZE 0x10
/**
 * @brief Implementation of LegoStorage for memory-backed buffers. [AI]
 * @details Provides read/write operations on a raw memory buffer, keeping track of the current offset. [AI]
 */
class LegoMemory : public LegoStorage {
public:
	/**
	 * @brief Constructor setting internal buffer pointer and resets position. [AI]
	 * @param p_buffer Pointer to memory buffer for storage [AI]
	 */
	LegoMemory(void* p_buffer);

	/**
	 * @brief Reads bytes from memory buffer at current position. [AI]
	 * @param p_buffer Output buffer to receive bytes [AI]
	 * @param p_size Number of bytes to read [AI]
	 * @return SUCCESS if operation completed, FAILURE otherwise [AI]
	 */
	LegoResult Read(void* p_buffer, LegoU32 p_size) override;        // vtable+0x04

	/**
	 * @brief Writes bytes to memory buffer at current position. [AI]
	 * @param p_buffer Input buffer containing bytes to write [AI]
	 * @param p_size Number of bytes to write [AI]
	 * @return SUCCESS if operation completed, FAILURE otherwise [AI]
	 */
	LegoResult Write(const void* p_buffer, LegoU32 p_size) override; // vtable+0x08

	/**
	 * @brief Gets the current offset into the memory buffer. [AI]
	 * @param p_position Reference to store position [AI]
	 * @return SUCCESS [AI]
	 */
	LegoResult GetPosition(LegoU32& p_position) override // vtable+0x0c
	{
		p_position = m_position;
		return SUCCESS;
	}

	/**
	 * @brief Sets the current offset into the memory buffer. [AI]
	 * @param p_position New position [AI]
	 * @return SUCCESS [AI]
	 */
	LegoResult SetPosition(LegoU32 p_position) override // vtable+0x10
	{
		m_position = p_position;
		return SUCCESS;
	}

	// SYNTHETIC: LEGO1 0x10045a80
	// LegoMemory::~LegoMemory

	// SYNTHETIC: LEGO1 0x100990f0
	// LegoMemory::`scalar deleting destructor'

protected:
	/**
	 * @brief Pointer to target memory buffer for reading/writing. [AI]
	 */
	LegoU8* m_buffer;   // 0x04

	/**
	 * @brief Current read/write offset in buffer. [AI]
	 */
	LegoU32 m_position; // 0x08
};

// VTABLE: LEGO1 0x100db730
// SIZE 0x0c
/**
 * @brief Implementation of LegoStorage for file-backed storage using stdio FILE*. [AI]
 * @details Provides read/write operations using C file I/O, tracks current file pointer position. [AI]
 */
class LegoFile : public LegoStorage {
public:
	/**
	 * @brief Default constructor initializes with NULL file pointer. [AI]
	 */
	LegoFile();

	/**
	 * @brief Destructor. Closes file if open. [AI]
	 */
	~LegoFile() override;

	/**
	 * @brief Reads bytes from file at current position. [AI]
	 * @param p_buffer Output buffer to receive bytes [AI]
	 * @param p_size Number of bytes to read [AI]
	 * @return SUCCESS if all requested bytes read, FAILURE otherwise [AI]
	 */
	LegoResult Read(void* p_buffer, LegoU32 p_size) override;        // vtable+0x04

	/**
	 * @brief Writes bytes to file at current position. [AI]
	 * @param p_buffer Input buffer containing bytes to write [AI]
	 * @param p_size Number of bytes to write [AI]
	 * @return SUCCESS if all requested bytes written, FAILURE otherwise [AI]
	 */
	LegoResult Write(const void* p_buffer, LegoU32 p_size) override; // vtable+0x08

	/**
	 * @brief Gets the current file pointer position relative to beginning. [AI]
	 * @param p_position Reference to store file position [AI]
	 * @return SUCCESS if file is open, FAILURE otherwise [AI]
	 */
	LegoResult GetPosition(LegoU32& p_position) override;            // vtable+0x0c

	/**
	 * @brief Sets the current file pointer position. [AI]
	 * @param p_position New absolute file pointer position [AI]
	 * @return SUCCESS if successful, FAILURE otherwise [AI]
	 */
	LegoResult SetPosition(LegoU32 p_position) override;             // vtable+0x10

	/**
	 * @brief Opens a file with given name and mode, closing existing file if needed. [AI]
	 * @param p_name Path to file [AI]
	 * @param p_mode Bitwise OR of OpenFlags bits indicating mode [AI]
	 * @details See OpenFlags for allowed modes: c_read, c_write, c_text. [AI]
	 * @return SUCCESS if file was opened successfully, FAILURE if not [AI]
	 */
	LegoResult Open(const char* p_name, LegoU32 p_mode);

	// SYNTHETIC: LEGO1 0x10099230
	// LegoFile::`scalar deleting destructor'

protected:
	/**
	 * @brief C runtime file pointer backing storage. [AI]
	 */
	FILE* m_file; // 0x08
};

#endif // __LEGOSTORAGE_H