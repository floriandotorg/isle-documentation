#ifndef _MxStopWatch_h
#define _MxStopWatch_h

#include "assert.h"

#include <limits.h> // ULONG_MAX
#include <math.h>
#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
//
// MxStopWatch
//
// NOTE:	MxStopWatch measures elapsed (wall clock) time.
//

#define HUGE_VAL_IMMEDIATE 1.7976931348623157e+308

// SIZE 0x18
/**
 * @brief Measures elapsed wall clock time using high resolution performance counters. [AI]
 * @details [AI] MxStopWatch uses Windows performance counters (QueryPerformanceCounter) to measure elapsed real-time as precisely as possible. 
 *               It can be used to profile code execution, update timing, or collect precise time intervals in the game engine.
 */
class MxStopWatch {
public:
	/**
	 * @brief Default constructor. Initializes the stopwatch and internal state. [AI]
	 * @details [AI] The stopwatch is reset and the number of ticks per second is queried from the OS. This sets up high-precision timing.
	 */
	MxStopWatch();

	/**
	 * @brief Destructor. [AI]
	 */
	~MxStopWatch() {}

	/**
	 * @brief Starts (or resumes) timing from the current moment. [AI]
	 * @details [AI] Records the current performance counter value. Call Stop() to capture the elapsed time increment.
	 */
	void Start();

	/**
	 * @brief Stops timing and accumulates the elapsed interval to m_elapsedSeconds. [AI]
	 * @details [AI] Uses the current and previous start tick to compute the time interval. If the interval cannot be represented by 32 bits, sets to HUGE_VAL_IMMEDIATE. 
	 */
	void Stop();

	/**
	 * @brief Resets the stopwatch to zero. [AI]
	 * @details [AI] Clears the start tick and accumulated elapsed time.
	 */
	void Reset();

	/**
	 * @brief Returns the total accumulated elapsed time in seconds. [AI]
	 */
	double ElapsedSeconds() const;

protected:
	/**
	 * @brief Queries and returns the number of performance counter ticks per second. [AI]
	 * @details [AI] Uses QueryPerformanceFrequency. Returns ULONG_MAX if frequency can't fit in 32 bits.
	 */
	unsigned long TicksPerSeconds() const;

private:
	LARGE_INTEGER m_startTick;        ///< @brief [AI] Last start tick as returned by QueryPerformanceCounter (LowPart/HighPart). Used as reference for measuring intervals.
	// ??? when we provide LARGE_INTEGER arithmetic, use a
	//     LARGE_INTEGER m_elapsedTicks rather than m_elapsedSeconds

	double m_elapsedSeconds;          ///< @brief [AI] Total accumulated elapsed time in seconds.
	unsigned long m_ticksPerSeconds;  ///< @brief [AI] Performance counter ticks per second, cached to avoid repeated queries.
};

// SYNTHETIC: LEGO1 0x100a6fc0
// SYNTHETIC: BETA10 0x100d8e70
// MxStopWatch::~MxStopWatch

//////////////////////////////////////////////////////////////////////////////
//
// MxFrequencyMeter
//

// SIZE 0x20
/**
 * @brief Utility for measuring the frequency (operations per second) of a repeated operation. [AI]
 * @details [AI] Wraps a MxStopWatch and an operation counter to determine how often something occurs per unit time—very useful for profiling, frame/tick rate monitoring, or rate-limited subsystems.
 */
class MxFrequencyMeter {
public:
	/**
	 * @brief Constructs a new MxFrequencyMeter with zeroed counters. [AI]
	 */
	MxFrequencyMeter();

	/**
	 * @brief Marks the beginning of a measured operation. [AI]
	 * @details [AI] Internally starts its stopwatch.
	 */
	void StartOperation();

	/**
	 * @brief Marks the end of a measured operation and increments the count. [AI]
	 * @details [AI] Stops the stopwatch to accumulate elapsed time for this operation and increments the operation count.
	 */
	void EndOperation();

	/**
	 * @brief Returns the measured frequency (operations per elapsed second). [AI]
	 * @details [AI] Returns HUGE_VAL if at least one operation occurred but elapsed time is zero; returns 0 if no operations. 
	 */
	double Frequency() const;

	/**
	 * @brief Resets the operation counter and stopwatch to zero. [AI]
	 */
	void Reset();

	/**
	 * @brief Returns the total number of completed operations. [AI]
	 */
	unsigned long OperationCount() const;

	/**
	 * @brief Returns the total elapsed seconds since the last Reset(). [AI]
	 */
	double ElapsedSeconds() const;

	/**
	 * @brief Increases the operation count by the specified delta. [AI]
	 * @param delta Amount to increase the operation count by. [AI]
	 */
	void IncreaseOperationCount(unsigned long delta);

private:
	unsigned long m_operationCount;   ///< @brief [AI] Number of operations measured so far since last reset.
	MxStopWatch m_stopWatch;          ///< @brief [AI] Stopwatch used to time the duration over which frequency is measured.
};

// SYNTHETIC: LEGO1 0x100abd10
// SYNTHETIC: BETA10 0x1017de40
// MxFrequencyMeter::~MxFrequencyMeter

#endif /* _MxStopWatch_h */