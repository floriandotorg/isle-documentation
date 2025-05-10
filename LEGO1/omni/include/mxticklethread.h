#ifndef MXTICKLETHREAD_H
#define MXTICKLETHREAD_H

#include "mxthread.h"

// VTABLE: LEGO1 0x100dc6d8
// SIZE 0x20

/**
 * @brief MxTickleThread periodically calls Tickle() on a target MxCore object in a separate thread. [AI]
 * @details [AI] This thread class is used to 'tickle' (update/poll) a target MxCore object at a fixed interval (specified in milliseconds).
 * The Tickle mechanism is central to frame updating and ticking logic in LEGO Island's event loop. The thread executes until IsRunning() is false,
 * after which it delegates to the base MxThread::Run(). [AI]
 */
class MxTickleThread : public MxThread {
public:
	/**
	 * @brief [AI] Constructs a MxTickleThread to tickle a target MxCore object at a fixed interval.
	 * @param p_target [AI] Pointer to the MxCore object that should be tickled periodically.
	 * @param p_frequencyMS [AI] The tickling frequency in milliseconds, i.e., the interval between calls to Tickle().
	 */
	MxTickleThread(MxCore* p_target, MxS32 p_frequencyMS);

	/**
	 * @brief [AI] Thread entry point. Starts the tickling loop, calling Tickle() on m_target at the specified interval.
	 * @details [AI] Repeatedly calculates elapsed time and sleeps as needed to maintain the requested tickle frequency.
	 * Handles clock wrap-around. Exits when IsRunning() returns false and then calls the base class Run(). [AI]
	 */
	MxResult Run() override;

	// SYNTHETIC: LEGO1 0x100b8c20
	// MxTickleThread::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Stores the tickling period in milliseconds. Used to schedule the Tickle() calls.
	 */
	MxS32 m_frequencyMS; // 0x1c
};

#endif // MXTICKLETHREAD_H
