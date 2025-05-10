#ifndef MXCRITICALSECTION_H
#define MXCRITICALSECTION_H

#include <windows.h>

/**
 * @brief [AI] Provides a critical section object for mutual exclusion with optional use of OS mutex.
 * @details [AI] MxCriticalSection encapsulates synchronization for threads, primarily using a Windows CRITICAL_SECTION, but with an optional fallback to a mutex depending on the runtime global setting. This is useful for cross-process synchronization or for debugging/compatibility scenarios where mutexes are required instead of critical sections (process-local). The mechanism is selected per process via SetDoMutex(). [AI]
 */
class MxCriticalSection {
public:
	/**
	 * @brief [AI] Constructs the critical section object.
	 * @details [AI] Initializes either a CRITICAL_SECTION or a mutex depending on the global g_useMutex flag. If mutex is activated, uses a Windows kernel mutex instead of the faster, process-local CRITICAL_SECTION. [AI]
	 */
	MxCriticalSection();

	/**
	 * @brief [AI] Destroys the critical section object.
	 * @details [AI] Deallocates any OS resources tied to the mutex or CRITICAL_SECTION, ensuring proper cleanup and deadlock protection. [AI]
	 */
	~MxCriticalSection();

	/**
	 * @brief [AI] Globally enforces the use of mutexes for all subsequent MxCriticalSection allocation.
	 * @details [AI] If called before instantiating MxCriticalSection instances, all new instances use OS mutexes rather than CRITICAL_SECTIONs. This is useful for debugging deadlocks or forcing cross-process mutual exclusion when required. [AI]
	 */
	static void SetDoMutex();

	/**
	 * @brief [AI] Acquires/gains entry to the critical section or mutex, blocking if not available.
	 * @details [AI] Waits (potentially blocks) until the section can be entered.  If using a mutex, will abort the process and log to DEADLOCK.TXT if a timeout or failure occurs, to aid diagnosing deadlocks. [AI]
	 */
	void Enter();

	/**
	 * @brief [AI] Releases/leaves the critical section or mutex.
	 * @details [AI] Signals that the calling thread has exited the protected area; resource is made available to the next thread waiting (if any). [AI]
	 */
	void Leave();

private:
	CRITICAL_SECTION m_criticalSection; ///< @brief [AI] Win32 critical section, used if not in mutex mode. [AI]
	HANDLE m_mutex;                     ///< @brief [AI] Win32 mutex object, NULL if not in mutex mode. [AI]
};

#endif // MXCRITICALSECTION_H