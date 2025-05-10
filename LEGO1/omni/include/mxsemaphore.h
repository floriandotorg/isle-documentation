#ifndef MXSEMAPHORE_H
#define MXSEMAPHORE_H

#include "mxtypes.h"

#include <windows.h>

// VTABLE: LEGO1 0x100dccf0
// SIZE 0x08

/**
 * @brief Implements a lightweight wrapper for Windows semaphores, allowing safe synchronization between threads. [AI]
 * @details [AI] MxSemaphore provides methods for initializing, waiting on, and releasing a Windows semaphore object, supporting cross-thread signaling and limiting concurrent execution. Used as a utility for resource management, thread pool gates, and similar concurrency control. [AI]
 */
class MxSemaphore {
public:
	/**
	 * @brief Constructs the MxSemaphore object; initializes internal handle to NULL. [AI]
	 */
	MxSemaphore();

	/**
	 * @brief Destructor, closes the semaphore handle if open. [AI]
	 * @details [AI] This cleans up OS resources, preventing handle leaks.
	 */
	~MxSemaphore() { CloseHandle(m_hSemaphore); }

	/**
	 * @brief Initializes the semaphore with both initial and maximum counts. [AI]
	 * @param p_initialCount The initial count for the semaphore (i.e., how many Wait() calls will succeed before blocking). [AI]
	 * @param p_maxCount The maximum value the semaphore count can reach. [AI]
	 * @return SUCCESS on success, FAILURE otherwise. [AI]
	 * @details [AI] Allocates the Windows semaphore resource and prepares it for use. Subsequent Wait and Release calls must only occur after successful initialization. [AI]
	 */
	virtual MxResult Init(MxU32 p_initialCount, MxU32 p_maxCount);

	/**
	 * @brief Waits on the semaphore for the specified timeout (in milliseconds). [AI]
	 * @param p_timeoutMS Timeout in milliseconds to wait before the operation is considered unsuccessful. [AI]
	 * @details [AI] Decrements the semaphore counter if it is positive, otherwise blocks for up to the specified timeout unless Release is called from another thread. [AI]
	 */
	void Wait(MxU32 p_timeoutMS);

	/**
	 * @brief Increases the semaphore count, unblocking waiting threads if any. [AI]
	 * @param p_releaseCount Increment amount for the semaphore's internal counter; typically 1 for single-release. [AI]
	 * @details [AI] Allows up to p_releaseCount threads blocked in Wait to proceed. [AI]
	 */
	void Release(MxU32 p_releaseCount);

private:
	HANDLE m_hSemaphore; ///< Windows handle to the semaphore object used for OS-level synchronization. [AI]
};

#endif // MXSEMAPHORE_H