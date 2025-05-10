#ifndef MXSTREAMPROVIDER_H
#define MXSTREAMPROVIDER_H

#include "decomp.h"
#include "mxcore.h"

class MxStreamController;
class MxDSAction;
class MxDSFile;

/// @brief [AI] Abstract base class for stream resource providers in the LEGO Island engine.
/// @details [AI] MxStreamProvider is responsible for interfacing with various data sources, such as RAM or disk, and providing access to the underlying SI file data and its buffered form to MxStreamController. It provides abstract methods for querying the source file size, number of buffers used for streaming, and buffer access for streaming whole DWORDs. Derived classes implement specifics for RAM or disk-backed streams. [AI]
/// @see MxRAMStreamProvider, MxDiskStreamProvider [AI]
///
/// @note [AI] Implements run-time class identification via ClassName/IsA, allowing dynamic queries of its type. [AI]
class MxStreamProvider : public MxCore {
public:
	/// @brief [AI] Default constructor. Initializes stream provider with no lookup or file resource attached. [AI]
	MxStreamProvider() : m_pLookup(NULL), m_pFile(NULL) {}

	/// @brief [AI] Returns the name identifier for this class. [AI]
	/// @return [AI] Static string "MxStreamProvider".
	const char* ClassName() const override // vtable+0x0c
	{
		return "MxStreamProvider";
	}

	/// @brief [AI] Checks if this object is of the requested class name, or a subclass thereof. [AI]
	/// @param p_name Name of the class to check inheritance against. [AI]
	/// @return [AI] True if this object's class or one of its bases matches p_name.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxStreamProvider::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Attaches a stream controller as the resource to provide data for. [AI]
	/// @param p_pLookup Stream controller requesting resource data. [AI]
	/// @return [AI] Returns SUCCESS after assigning the controller. [AI]
	virtual MxResult SetResourceToGet(MxStreamController* p_pLookup)
	{
		m_pLookup = p_pLookup;
		return SUCCESS;
	} // vtable+0x14

	/// @brief [AI] Gets the file size, in bytes, of the underlying SI file resource. [AI]
	/// @return [AI] The file size in bytes. [AI]
	virtual MxU32 GetFileSize() = 0;         // vtable+0x18
	
	/// @brief [AI] Returns the number of stream buffers internally maintained for this resource. [AI]
	/// @return [AI] The number of stream buffers. [AI]
	virtual MxS32 GetStreamBuffersNum() = 0; // vtable+0x1c

	/// @brief [AI] Virtual hook for subclasses to react to new stream actions being queued. [AI]
	/// @details [AI] Unused and empty in base. Derived implementations may use this for notification when new actions are dispatched. [AI]
	/// @param p_action Action being processed. [AI]
	virtual void VTable0x20(MxDSAction* p_action) {} // vtable+0x20

	/// @brief [AI] Gets the full buffer length, interpreted as a DWORD-count, for direct buffer streaming. [AI]
	/// @return [AI] The length in DWORDs. [AI]
	virtual MxU32 GetLengthInDWords() = 0;   // vtable+0x24
	
	/// @brief [AI] Returns a pointer to the underlying buffer, cast as an array of DWORDs, for streaming purposes. [AI]
	/// @return [AI] Pointer to a DWORD-aligned buffer. [AI]
	virtual MxU32* GetBufferForDWords() = 0; // vtable+0x28

protected:
	MxStreamController* m_pLookup; ///< [AI] The stream controller using this provider as its data source. [AI]
	MxDSFile* m_pFile;             ///< [AI] Pointer to the loaded SI file associated with this provider. [AI]
};

// SYNTHETIC: LEGO1 0x100d0870
// MxStreamProvider::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100d08e0
// MxStreamProvider::~MxStreamProvider

#endif // MXSTREAMPROVIDER_H
