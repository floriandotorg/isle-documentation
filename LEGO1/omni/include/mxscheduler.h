#ifndef MXSCHEDULER_H
#define MXSCHEDULER_H

#include "mxtypes.h"

/// @brief [AI] Singleton class for managing and starting multitasking functionality in the system. [AI]
/// @details [AI] MxScheduler provides an interface for controlling multitasking features at a possibly system-specific or engine-specific level. Most likely designed as an OS abstraction for background/asynchronous operations by the LEGO Island engine, but its actual use in the game is minimal (intentionally empty in implementation). [AI]
class MxScheduler {
public:
	/// @brief [AI] Retrieves the singleton instance of the scheduler. [AI]
	/// @return Pointer to the single global scheduler instance (nullptr in current implementation). [AI]
	static MxScheduler* GetInstance();

	/// @brief [AI] Initiates support for multitasking with the specified configuration. [AI]
	/// @param p_flags Bit field or value indicating the desired multitasking mode or attributes. [AI]
	/// @details [AI] The actual implementation is empty, suggesting it was intended for future use, testing, or platform abstraction. [AI]
	void StartMultiTasking(MxULong p_flags);
};

#endif // MXSCHEDULER_H