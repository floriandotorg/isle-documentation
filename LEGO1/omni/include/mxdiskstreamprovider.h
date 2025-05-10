#ifndef MXDISKSTREAMPROVIDER_H
#define MXDISKSTREAMPROVIDER_H

#include "compat.h"
#include "decomp.h"
#include "mxcriticalsection.h"
#include "mxdsaction.h"
#include "mxstreamprovider.h"
#include "mxthread.h"

/**
 * @class MxDiskStreamProviderThread
 * @brief [AI] Thread to handle disk-based streaming for MxDiskStreamProvider, running as a worker for disk streaming actions.
 * @details [AI] This class extends MxThread and encapsulates logic to execute and synchronize background streaming requests for MxDiskStreamProvider,
 * ensuring file data is loaded as needed.
 * SIZE: 0x1c [AI]
 */
class MxDiskStreamProvider;
class MxDSStreamingAction;

class MxDiskStreamProviderThread : public MxThread {
public:
	/**
	 * @brief [AI] Constructs a streaming worker thread for disk streaming provider.
	 * @details [AI] Sets the target to nullptr, preparing to run with a streaming provider as the source of work.
	 */
	MxDiskStreamProviderThread() : MxThread() { m_target = NULL; }

	/**
	 * @brief [AI] Entry point for the streaming thread, called to begin the thread's workload.
	 * @details [AI] Executes wait and processing logic for its assigned MxDiskStreamProvider.
	 * @return [AI]
	 */
	MxResult Run() override;

	/**
	 * @brief [AI] Starts the thread with a specific MxDiskStreamProvider as its target.
	 * @param p_target The disk streaming provider instance owning this thread. [AI]
	 * @return [AI]
	 */
	MxResult StartWithTarget(MxDiskStreamProvider* p_target);

protected:
	/** 
	 * @brief [AI] Target provider instance for this worker thread.
	 * [AI_SUGGESTED_NAME: m_target] 
	 */
	MxDiskStreamProvider* m_target;
};

/**
 * @class MxDiskStreamProvider
 * @brief [AI] Disk-based stream provider for resource loading using background streaming and multithreading.
 * @details [AI] Handles asynchronous loading and management of resources from disk by employing internal buffering,
 * file/stream semantics, synchronization, and thread-based execution. Supports the LEGO SI file streaming system.
 * SIZE: 0x60 [AI]
 */
class MxDiskStreamProvider : public MxStreamProvider {
public:
	/**
	 * @brief [AI] Constructs a disk stream provider, initializing critical members and preparing for disk-based streaming.
	 */
	MxDiskStreamProvider();
	/**
	 * @brief [AI] Cleans up the disk stream provider, including terminating the worker thread and releasing file and action resources.
	 */
	~MxDiskStreamProvider() override;

	/**
	 * @brief [AI] Returns the runtime class name.
	 * @return "MxDiskStreamProvider" [AI]
	 */
	const char* ClassName() const override;

	/**
	 * @brief [AI] Tests if the object is of, or derives from, the supplied class name.
	 * @param p_name The class name to check against. [AI]
	 * @return [AI]
	 */
	MxBool IsA(const char* p_name) const override;

	/**
	 * @brief [AI] Blocks until all scheduled streaming work is finished (used by the streaming worker thread).
	 * @details [AI] Repeatedly waits on the busy semaphore and delegates to PerformWork as needed until remaining work is done.
	 * @return [AI]
	 */
	MxResult WaitForWorkToComplete();

	/**
	 * @brief [AI] Schedules a streaming action to read data (SI chunk) from disk and buffers it asynchronously.
	 * @param p_action The streaming action to schedule. [AI]
	 * @return [AI]
	 */
	MxResult FUN_100d1780(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Performs a single unit of scheduled streaming work, i.e., loading data for queued actions.
	 * @details [AI] Used internally by the worker thread to process actions on the work queue, handling buffer/finalization and controller callbacks.
	 */
	void PerformWork();

	/**
	 * @brief [AI] Returns whether a streaming action can be processed (buffer conditions met).
	 * @param p_action The streaming action to test. [AI]
	 * @return [AI]
	 */
	static MxBool FUN_100d1af0(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Finalizes merging of streaming buffers and updates streamed data for a given action.
	 * @param p_action The streaming action to finalize/merge. [AI]
	 * @return [AI]
	 */
	MxResult FUN_100d1b20(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Opens and prepares a resource for streaming from disk based on the controller's atom (resource key).
	 * @details [AI] Tries to open the resource from hard disk, then falls back to CD. Initializes queues and starts the thread.
	 * @param p_resource The stream controller resource descriptor. [AI]
	 * @return [AI]
	 */
	MxResult SetResourceToGet(MxStreamController* p_resource) override;

	/**
	 * @brief [AI] Gets the size, in bytes, of the open file/buffer to be streamed.
	 * @return [AI]
	 */
	MxU32 GetFileSize() override;

	/**
	 * @brief [AI] Gets the number of stream buffers/splits for the file, used to drive parallel reads.
	 * @return [AI]
	 */
	MxS32 GetStreamBuffersNum() override;

	/**
	 * @brief [AI] Cancels or reclaims outstanding streaming actions based on object ID, returning associated actions to free buffer.
	 * @param p_action The DS action (can be a kill-all or single-object). [AI]
	 */
	void VTable0x20(MxDSAction* p_action) override;

	/**
	 * @brief [AI] Returns file length as dword-count for bulk/integer-based streaming use cases.
	 * @return [AI]
	 */
	MxU32 GetLengthInDWords() override;

	/**
	 * @brief [AI] Returns a pointer to the buffer for raw dword access (SI file data block).
	 * @return [AI]
	 */
	MxU32* GetBufferForDWords() override;

protected:
	/**
	 * @brief [AI] Thread object handling streaming actions asynchronously.
	 */
	MxDiskStreamProviderThread m_thread; // 0x10

	/**
	 * @brief [AI] Semaphore used to synchronize and signal work for the background thread.
	 */
	MxSemaphore m_busySemaphore;         // 0x2c

	/**
	 * @brief [AI] Indicates whether more streaming work remains for the thread.
	 */
	MxBool m_remainingWork;              // 0x34

	/**
	 * @brief [AI] Internal flag signaling available work for the thread or shutdown in progress.
	 */
	MxBool m_unk0x35;                    // 0x35

	/**
	 * @brief [AI] Synchronizes access to the work item queue (m_list).
	 */
	MxCriticalSection m_criticalSection; // 0x38

	/**
	 * @brief [AI] List of streaming actions to be processed/completed by the thread.
	 */
	MxDSObjectList m_list;               // 0x54
};

#endif // MXDISKSTREAMPROVIDER_H
