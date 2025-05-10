#ifndef MXAUTOLOCK_H
#define MXAUTOLOCK_H

/// @brief [AI] Macro for automatic locking using the MxAutoLock class. This macro instantiates an MxAutoLock object named "lock" for the given critical section, ensuring lock is acquired on entry and released on scope exit. [AI]
#define AUTOLOCK(CS) MxAutoLock lock(&CS)

class MxCriticalSection;

/// @class MxAutoLock
/// @brief [AI] Provides automatic RAII-style locking and unlocking for a critical section. When an instance is created, it enters the provided critical section, and on destruction, it leaves it. This pattern ensures exception-safe critical section management and reduces the likelihood of forgetting to unlock.
/// @details [AI] The constructor immediately enters the critical section if it is not null. The destructor leaves the section if still valid. Intended for use with the AUTOLOCK macro on code blocks that need mutual exclusion. [AI]
class MxAutoLock {
public:
	/// @brief [AI] Constructs an auto locker and acquires the lock on the given critical section. [AI]
	/// @param p_criticalSection [AI] The critical section to be locked by this object. Must not be deleted while this object exists. [AI]
	MxAutoLock(MxCriticalSection* p_criticalSection);

	/// @brief [AI] Destructor releases (leaves) the critical section if it was acquired. [AI]
	~MxAutoLock();

private:
	MxCriticalSection* m_criticalSection; ///< @brief [AI] The critical section currently guarded by this object. [AI]
};

#endif // MXAUTOLOCK_H
