#ifndef MXDISKSTREAMCONTROLLER_H
#define MXDISKSTREAMCONTROLLER_H

#include "decomp.h"
#include "mxdsbuffer.h"
#include "mxstl/stlcompat.h"
#include "mxstreamcontroller.h"
#include "mxtypes.h"

#include <string.h>

class MxDSStreamingAction;

// VTABLE: LEGO1 0x100dccb8
// VTABLE: BETA10 0x101c2818
// SIZE 0xc8
/**
 * @brief [AI] Controller for streaming from disk-based SI resources, manages buffers and streaming actions. Extends MxStreamController.
 * @details [AI] The MxDiskStreamController handles streaming of resources (usually from disk) via SI (Script/Resource) files.
 *              Manages various buffers and actions to allow for asynchronous streaming, buffer reuse, and action lifecycle.
 *              Synchronizes access using critical sections for thread safety, and incorporates a tickle-based update mechanism.
 */
class MxDiskStreamController : public MxStreamController {
public:
	MxDiskStreamController(); ///< @brief [AI] Constructor. Initializes internal state and buffer counters.
	~MxDiskStreamController() override; ///< @brief [AI] Destructor. Cleans up streaming actions, buffers, and provider. Unregisters from tickle manager.

	MxResult Tickle() override; // vtable+0x08
	/// @brief [AI] Update the controller, handling buffer processing and queued actions. Invoked regularly (see tickle mechanism).
	/// @details [AI] Frees unused buffers, handles scheduled streaming actions, and launches new buffer loads as necessary.

	// FUNCTION: LEGO1 0x100c7360
	// FUNCTION: BETA10 0x10155c00
	/**
	 * @brief [AI] Returns the class name as a string literal.
	 * @return "MxDiskStreamController" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102144
		return "MxDiskStreamController";
	}

	// FUNCTION: LEGO1 0x100c7370
	/**
	 * @brief [AI] Checks whether the provided string matches the class name or any ancestor's class name.
	 * @param p_name Name to compare. [AI]
	 * @return True if the class matches or is a subclass; otherwise, false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDiskStreamController::ClassName()) || MxStreamController::IsA(p_name);
	}

	MxResult Open(const char* p_filename) override;       // vtable+0x14
	/// @brief [AI] Opens the given resource file for streaming. Prepares provider/stream for reading actions and registers for tickling.
	/// @param p_filename Name of the resource file to open (without path/extension). [AI]
	/// @return [AI] Success on successful setup, otherwise failure status.

	MxResult VTable0x18(undefined4, undefined4) override; // vtable+0x18
	/// @brief [AI] Placeholder/overridden method—purpose unknown from context.

	MxResult VTable0x20(MxDSAction* p_action) override;   // vtable+0x20
	/// @brief [AI] Start or queue the streaming action for the given action, potentially using buffer reuse and streaming mechanics.
	/// @param p_action The action to process. [AI]

	MxResult VTable0x24(MxDSAction* p_action) override;   // vtable+0x24
	/// @brief [AI] Marks an action as completed and cleans up associated resources.
	/// @param p_action The completed action. [AI]

	MxDSStreamingAction* VTable0x28() override;           // vtable+0x28
	/// @brief [AI] Pops a queued (ready) streaming action and prepares it for buffer assignment. [AI]

	MxResult VTable0x30(MxDSAction* p_action) override;   // vtable+0x30
	/// @brief [AI] Cleans up/aborts all queued streaming actions associated with the specified action.
	/// @param p_action The action whose streaming actions to remove. [AI]

	virtual MxResult VTable0x34(undefined4);              // vtable+0x34
	/// @brief [AI] Placeholder/overridden method—purpose unknown from context.

	/**
	 * @brief [AI] Return value of m_unk0xc4, indicating if more action chunks/processing is in progress.
	 * @return Boolean processing flag. [AI]
	 */
	MxBool GetUnk0xc4() const { return m_unk0xc4; }

	/**
	 * @brief [AI] Adds a streaming action to the list (m_list0x80) and possibly processes buffer allocation.
	 * @param p_action Streaming action to add. [AI]
	 */
	MxResult FUN_100c7890(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Destroys the given streaming action and any associated buffers.
	 * @param p_action Streaming action to destroy. [AI]
	 */
	void FUN_100c7cb0(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Adds a streaming action to m_list0x64 for processing.
	 * @param p_streamingaction Streaming action to add. [AI]
	 */
	void FUN_100c7f40(MxDSStreamingAction* p_streamingaction);

	/**
	 * @brief [AI] Cleans up an action and all associated resources, notifies provider.
	 * @param p_action Action to clean up. [AI]
	 */
	void FUN_100c8120(MxDSAction* p_action);

	/**
	 * @brief [AI] Inserts a buffer to the buffer reuse list (m_list0x74).
	 * @param p_buffer Buffer to enqueue for later potential reuse or cleanup. [AI]
	 */
	void InsertToList74(MxDSBuffer* p_buffer);

	/**
	 * @brief [AI] Pushes an action to a private list (m_list0xb8) for later cleanup.
	 * @param p_streamingAction The streaming action to defer deletion. [AI]
	 */
	void FUN_100c8670(MxDSStreamingAction* p_streamingAction);

private:
	MxDSObjectList m_list0x64;      ///< @brief [AI] List of MxDSStreamingAction awaiting buffer processing and/or streaming. 
	MxBool m_unk0x70;               ///< @brief [AI] Processing flag, triggers buffer load/streaming if set. 
	list<MxDSBuffer*> m_list0x74;   ///< @brief [AI] List of currently allocated but inactive (potentially reusable) buffers.
	MxDSObjectList m_list0x80;      ///< @brief [AI] List of actions awaiting buffer assignment/streaming start. 
	undefined2 m_unk0x8c;           ///< @brief [AI] Buffer counter, used to limit number of buffers in use.
	MxDSObjectList m_list0x90;      ///< @brief [AI] List of actions currently reading or awaiting completion.
	MxCriticalSection m_critical9c; ///< @brief [AI] Secondary critical section for protecting m_list0xb8 (cleanup queue).
	MxDSObjectList m_list0xb8;      ///< @brief [AI] Pending deletion list for streaming actions; cleaned up safely each tick.
	MxBool m_unk0xc4;               ///< @brief [AI] Set when at least one streaming action/processing is active.

	/**
	 * @brief [AI] Internal stub, no observed effect in codebase. May represent future or legacy functionality.
	 */
	void FUN_100c7970();

	/**
	 * @brief [AI] Buffer and streaming allocation/launch. Tries to pair an open buffer and action.
	 */
	void FUN_100c7ce0(MxDSBuffer* p_buffer);

	/**
	 * @brief [AI] Finds and processes the next streaming action, launching required read operations.
	 */
	MxResult FUN_100c7d10();

	/**
	 * @brief [AI] Attempts to launch a new buffer streaming operation if requirements are met.
	 */
	void FUN_100c7980();

	/**
	 * @brief [AI] Tries to find a queued streaming action matching available data. Used to process next streaming task.
	 * @return Matching streaming action or NULL if no matching request is ready. [AI]
	 */
	MxDSStreamingAction* FUN_100c7db0();

	/**
	 * @brief [AI] Finalizes buffer processing for a streaming action, transfers buffer/data if necessary, and cleans up.
	 */
	MxResult FUN_100c8360(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Frees unused buffers and deferred actions. Cleans up actions and buffers safely.
	 */
	void FUN_100c8540();

	/**
	 * @brief [AI] Cleans up any actions pushed for deferred deletion, emptying the m_list0xb8 queue.
	 */
	void FUN_100c8720();
};

#endif // MXDISKSTREAMCONTROLLER_H