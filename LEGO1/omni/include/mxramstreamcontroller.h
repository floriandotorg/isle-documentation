#ifndef MXRAMSTREAMCONTROLLER_H
#define MXRAMSTREAMCONTROLLER_H

#include "mxdsbuffer.h"
#include "mxstreamcontroller.h"

class MxDSStreamingAction;

// VTABLE: LEGO1 0x100dc728
// VTABLE: BETA10 0x101c2390
// SIZE 0x98
/**
 * @brief Derived stream controller that manages media streaming from memory buffers as opposed to disk. [AI]
 * @details [AI] MxRAMStreamController is responsible for managing streamed resource access from memory, rather than file-based (disk) access.
 * It is used by the game engine to handle in-memory SI file resources and routed through the generic MxStreamController interface. [AI]
 *
 * This enables the engine to operate on data that has already been loaded into RAM for more efficient access, 
 * supporting streaming, deserialization, and synchronization with the rest of the system. [AI]
 */
class MxRAMStreamController : public MxStreamController {
public:
	MxRAMStreamController() {}

	/**
	 * @brief Returns the class name for use in RTTI and type queries. [AI]
	 * @return Pointer to the class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102118
		return "MxRAMStreamController";
	}

	/**
	 * @brief Checks if this object matches or inherits the named class. [AI]
	 * @param p_name Name of the class to compare. [AI]
	 * @return TRUE if the object is of the provided class name, or a parent; otherwise FALSE. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxRAMStreamController::ClassName()) ||
			   !strcmp(p_name, MxStreamController::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief Opens and prepares a resource from a memory buffer for streaming. [AI]
	 * @details [AI] This function overrides the base implementation and orchestrates the creation of a RAM stream provider,
	 * loads the resource data into memory (using MxRAMStreamProvider), and initializes the internal buffer with the file contents.
	 * Essential for supporting streaming directly from in-memory SI files. [AI]
	 * @param p_filename The resource identifier (typically SI file name, path-like). [AI]
	 * @return SUCCESS on success, FAILURE otherwise. [AI]
	 */
	MxResult Open(const char* p_filename) override;

	/**
	 * @brief Custom stream controller dispatch, likely for initial action activation or stream setup (unknown semantics). [AI]
	 * @param p_action The DS Action to operate on. [AI]
	 * @return Returns SUCCESS on successful deserialization; FAILURE otherwise. [AI]
	 */
	MxResult VTable0x20(MxDSAction* p_action) override;

	/**
	 * @brief Custom stream controller dispatch, likely for ending, cleanup, or secondary phase action (unknown semantics). [AI]
	 * @param p_action The DS Action to operate on. [AI]
	 * @return Always returns SUCCESS. [AI]
	 */
	MxResult VTable0x24(MxDSAction* p_action) override;

private:
	/**
	 * @brief In-memory stream buffer used for resource access and chunk deserialization. [AI]
	 * @details [AI] This buffer stores the entire content of the resource file loaded into RAM, enabling random access for streaming and deserialization of media/actions. [AI]
	 */
	MxDSBuffer m_buffer; // 0x64

	/**
	 * @brief Deserializes a streamed action object from the in-memory buffer. [AI]
	 * @details [AI] This function processes the current streaming action, seeking to the correct position in the buffer and using buffer utility routines to instantiate required objects. Used as a helper for VTable0x20. [AI]
	 * @param p_action The streaming action to deserialize. [AI]
	 * @return SUCCESS if deserialization is complete and valid, otherwise FAILURE. [AI]
	 */
	MxResult DeserializeObject(MxDSStreamingAction& p_action);
};

// SYNTHETIC: LEGO1 0x100b94f0
// MxRAMStreamController::`scalar deleting destructor'

#endif // MXRAMSTREAMCONTROLLER_H
