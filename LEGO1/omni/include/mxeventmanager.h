#ifndef MXEVENTMANAGER_H
#define MXEVENTMANAGER_H

#include "decomp.h"
#include "mxmediamanager.h"

// VTABLE: LEGO1 0x100dc900
// SIZE 0x2c

/**
 * @brief MxEventManager is a subclass of MxMediaManager responsible for managing timed event delivery, either via cooperative thread or tickle-based mechanism. [AI]
 * @details [AI] MxEventManager coordinates the delivery of "tickles" (periodic updates) to its clients. It supports both threaded and non-threaded operation modes. When in threaded mode, it creates a dedicated MxTickleThread to drive regular tickles at the specified frequency. In non-threaded mode, it registers itself with the global MxTickleManager for update calls. MxEventManager provides initialization, teardown, and resource-control logic, aiming to abstract event (tick) management for the application subsystems, usually presenting media or handling real-time updates. [AI]
 */
class MxEventManager : public MxMediaManager {
public:
	/**
	 * @brief Constructor for MxEventManager. [AI]
	 * @details [AI] Initializes the event manager, setting up internal state and preparing for possible event handling logic. The Init() function is called during construction. [AI]
	 */
	MxEventManager();

	/**
	 * @brief Destructor for MxEventManager. [AI]
	 * @details [AI] Cleans up any allocated resources or threads and deregisters itself from tickle management if necessary. Calls Destroy(TRUE). [AI]
	 */
	~MxEventManager() override;

	/**
	 * @brief Tears down the event manager and releases resources/thread/registration. [AI]
	 * @details [AI] Calls the internal Destroy(FALSE) routine, which will properly release the tickle thread, deregister from the tickle manager, and destroy base class objects if not from the destructor context. [AI]
	 */
	void Destroy() override;                                             // vtable+18

	/**
	 * @brief Initializes the MxEventManager to periodically handle events using a thread or registration with the tickle manager. [AI]
	 * @param p_frequencyMS Frequency, in milliseconds, at which to issue tickles/updates. [AI]
	 * @param p_createThread If TRUE, creates a dedicated thread for event ticks. If FALSE, registers with tickle manager to be tickled at specified frequency. [AI]
	 * @return Returns SUCCESS or FAILURE, depending on resource allocation success and thread or registration initialization. [AI]
	 * @details [AI] If p_createThread is TRUE, locks the critical section and begins a new MxTickleThread instance to handle tickling. If FALSE, registers this instance as a client with the singleton tickle manager. Destroys instance if initialization fails. [AI]
	 */
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread); // vtable+28

	// SYNTHETIC: LEGO1 0x100c03d0
	// MxEventManager::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes member variables or performs per-constructor logic. [AI]
	 * @details [AI] (Currently, Init is intentionally left blank but reserved for future use or subclass initialization. Called by the constructor.) [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Performs full destruction and cleanup, optionally called from a destructor context. [AI]
	 * @param p_fromDestructor If TRUE, called from destructor; avoids calling base destroy. [AI]
	 * @details [AI] If managing a tickle thread, terminates and deletes it. If not threaded, unregisters from the tickle manager. Calls the base class destroy only if not in destructor context. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXEVENTMANAGER_H