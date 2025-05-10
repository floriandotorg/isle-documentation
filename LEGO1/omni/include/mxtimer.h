#ifndef MXTIMER_H
#define MXTIMER_H

#include "mxcore.h"

// VTABLE: LEGO1 0x100dc0e0
// VTABLE: BETA10 0x101c1bb0
// SIZE 0x10

/**
 * @brief Timer class for measuring elapsed time or frame time. [AI]
 * @details [AI] MxTimer implements a timer utility based on timeGetTime (Windows tick count). It allows measuring elapsed times from a start point, pausing/resuming, and retrieving accumulated times in various formats. It maintains both per-instance state (timer started, running, etc.) and static global values for last calculated/started time. [AI]
 */
class MxTimer : public MxCore {
public:
	/**
	 * @brief Constructs and initializes the timer to the current tick count, and resets static globals. [AI]
	 * @details [AI] m_isRunning is initialized to FALSE, m_startTime is set to the OS tick count (timeGetTime), and g_lastTimeCalculated is set to m_startTime via InitLastTimeCalculated. [AI] 
	 */
	MxTimer();

	/**
	 * @brief Starts the timer and records the real time when started. [AI]
	 * @details [AI] Sets m_isRunning to TRUE and updates g_lastTimeTimerStarted with the elapsed time via GetRealTime. If already running, has no additional effect. [AI]
	 */
	void Start();

	/**
	 * @brief Stops the timer, updating internal counters to reflect elapsed time until now. [AI]
	 * @details [AI] Sets m_isRunning to FALSE, and adjusts m_startTime so that future queries (while stopped) return the total elapsed time up to the call. Implementation is based on the difference between the real time and the last time the timer was started, with a slight adjustment (-5) for original engine logic. [AI]
	 */
	void Stop();

	/**
	 * @brief Retrieves the elapsed real time (in ms) since timer construction or last reset. [AI]
	 * @details [AI] Updates g_lastTimeCalculated with the current OS tick (timeGetTime) and returns the difference from m_startTime. [AI]
	 */
	MxLong GetRealTime();

	/**
	 * @brief Initializes the static 'last time calculated' field to the timer's start time. [AI]
	 * @details [AI] Used to synchronize the static counter (g_lastTimeCalculated) with the current timer's moment of construction or reset. [AI]
	 */
	void InitLastTimeCalculated() { g_lastTimeCalculated = m_startTime; }

	/**
	 * @brief Returns the current timer value in ms, depending on running state. [AI]
	 * @details [AI] If the timer is running, returns g_lastTimeTimerStarted (static, records tick count at last Start); otherwise returns the difference between g_lastTimeCalculated and m_startTime (i.e., elapsed ticks so far). In BETA10, only the second branch is present. [AI]
	 */
	MxLong GetTime()
	{
		// Note that the BETA10 implementation differs - it only consists of the second branch of this `if` call
		if (m_isRunning) {
			return g_lastTimeTimerStarted;
		}
		else {
			return g_lastTimeCalculated - m_startTime;
		}
	}

	// SYNTHETIC: LEGO1 0x100ae0d0
	// SYNTHETIC: BETA10 0x1012bf80
	// MxTimer::`scalar deleting destructor'

private:
	MxLong m_startTime; ///< @brief Timer tick value (in ms) recorded at construction/reset. Internal reference for elapsed time computation. [AI]
	MxBool m_isRunning; ///< @brief Whether the timer is actively running (TRUE if started, FALSE if stopped). [AI]

	static MxLong g_lastTimeCalculated;   ///< @brief Globally records the last tick count returned by GetRealTime. Used for consistency across timers. [AI]
	static MxLong g_lastTimeTimerStarted; ///< @brief Globally records the time value at which a timer was last started. Used for elapsed time computation while running. [AI]
};

// SYNTHETIC: BETA10 0x1012bfc0
// MxTimer::~MxTimer

#endif // MXTIMER_H