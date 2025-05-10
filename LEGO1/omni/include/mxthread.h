#ifndef MXTHREAD_H
#define MXTHREAD_H

#include "compat.h"
#include "mxsemaphore.h"
#include "mxtypes.h"

class MxCore;

// VTABLE: LEGO1 0x100dc860
// SIZE 0x1c
/**
 * @brief [AI] Abstract thread class providing a platform-independent interface for thread management.
 * @details [AI] MxThread encapsulates thread creation, synchronization, and control, allowing derived classes
 * to implement their own logic in the Run() function. Used for background processing such as streaming or resource loading.
 */
class MxThread {
public:
	/**
	 * @brief [AI] Virtual function executed when the thread runs.
	 * @details [AI] This method is expected to be overridden by derived classes to implement specific thread logic.
	 * The base implementation simply releases the semaphore and returns SUCCESS.
	 * @return [AI] Success or failure status.
	 */
	virtual MxResult Run();

	/**
	 * @brief [AI] Starts the thread with a given stack size and creation flags.
	 * @details [AI] Initializes the semaphore and creates a new thread in the system using the specified stack size and flags.
	 * The thread executes ThreadProc, which calls Run() on this instance. The method is platform-specific (Windows).
	 * @param p_stackSize Amount of stack to allocate for the thread (in 4-byte units). [AI]
	 * @param p_flag Pass-through flag to the underlying thread creation API. [AI]
	 * @return [AI] Returns SUCCESS if the thread was started successfully, otherwise FAILURE.
	 */
	MxResult Start(MxS32 p_stackSize, MxS32 p_flag);

	/**
	 * @brief [AI] Signals the thread to terminate.
	 * @details [AI] Sets the m_running flag to FALSE and blocks until the semaphore is released, ensuring 
	 * that the thread finishes execution gracefully.
	 */
	void Terminate();

	/**
	 * @brief [AI] Sleeps the current thread for the given duration in milliseconds.
	 * @details [AI] This is a wrapper over the OS sleep API. The current executing thread (not necessarily this MxThread) is paused.
	 * @param p_milliseconds How long to sleep in milliseconds. [AI]
	 */
	void Sleep(MxS32 p_milliseconds);

	/**
	 * @brief [AI] Returns whether the thread is currently running.
	 * @details [AI] Returns the value of m_running, which should be TRUE if the thread is running and FALSE if it has been terminated.
	 * @return [AI] TRUE if running, FALSE otherwise.
	 */
	MxBool IsRunning() { return m_running; }

	// SYNTHETIC: LEGO1 0x100bf580
	// MxThread::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Protected constructor for MxThread.
	 * @details [AI] Initializes thread handles and running state. Should only be constructed by derived classes.
	 */
	MxThread();

public:
	/**
	 * @brief [AI] Virtual destructor for MxThread.
	 * @details [AI] Cleans up system resources associated with the thread, if any exist.
	 */
	virtual ~MxThread();

private:
	/**
	 * @brief [AI] Static thread entry point compatible with system thread APIs.
	 * @details [AI] Calls the instance's Run() method. Used as the function pointer for new thread creation.
	 * @param p_thread Pointer to the MxThread object for which the thread should run. [AI]
	 * @return [AI] The return value of Run().
	 */
	static unsigned ThreadProc(void* p_thread);

	MxULong m_hThread;       ///< [AI] System thread handle/resource or identifier (Windows HANDLE). Used for thread management. Offset 0x04.
	MxU32 m_threadId;        ///< [AI] System-level thread identifier for this thread. Offset 0x08.
	MxBool m_running;        ///< [AI] Indicates whether the thread is actively running (TRUE) or should terminate (FALSE). Offset 0x0c.
	MxSemaphore m_semaphore; ///< [AI] Semaphore for synchronization; used for blocking and signaling thread start/stop. Offset 0x10.

protected:
	MxCore* m_target; ///< [AI] Pointer to the target object (optional, typically the object being processed by the thread). Offset 0x18
};

#endif // MXTHREAD_H
