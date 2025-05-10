#ifndef MXTICKLEMANAGER_H
#define MXTICKLEMANAGER_H

#include "mxcore.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"

// SIZE 0x10
/**
 * @brief [AI] Associates an MxCore object with tickle timing/interval information.
 *
 * This class acts as a record holding which MxCore-derived object should be tickled (i.e. have its Tickle() called), 
 * how often this should happen (interval), when it was last tickled, and additional flags.
 * Used by MxTickleManager to trigger periodic updates in registered objects.
 * @details [AI] 
 * The tickle mechanism forms the basis of the engine's periodic update ("game loop") logic, allowing registered 
 * objects to update themselves at specified time intervals managed centrally.
 */
class MxTickleClient {
public:
	/**
	 * @brief [AI] Constructs a tickle client for the given object and interval.
	 * @param p_client MxCore-derived object to be tickled. [AI]
	 * @param p_interval Time in milliseconds between tickles for this object. [AI]
	 */
	MxTickleClient(MxCore* p_client, MxTime p_interval);

	/**
	 * @brief [AI] Returns the managed MxCore object.
	 */
	MxCore* GetClient() const { return m_client; }

	/**
	 * @brief [AI] Returns the tickle interval in milliseconds.
	 */
	MxTime GetTickleInterval() const { return m_interval; }

	/**
	 * @brief [AI] Returns the timestamp of the last tickle.
	 */
	MxTime GetLastUpdateTime() const { return m_lastUpdateTime; }

	/**
	 * @brief [AI] Returns the internal flags for this tickle client.
	 */
	MxU16 GetFlags() const { return m_flags; }

	/**
	 * @brief [AI] Sets the tickle interval for this client.
	 * @param p_interval New interval in milliseconds. [AI]
	 */
	void SetTickleInterval(MxTime p_interval) { m_interval = p_interval; }

	/**
	 * @brief [AI] Sets the last tickle time (updates the timestamp).
	 * @param p_lastUpdateTime Time in milliseconds. [AI]
	 */
	void SetLastUpdateTime(MxTime p_lastUpdateTime) { m_lastUpdateTime = p_lastUpdateTime; }

	/**
	 * @brief [AI] Sets the flags for this client (e.g., destruction flag).
	 * @param p_flags Bitmask flags. [AI]
	 */
	void SetFlags(MxU16 p_flags) { m_flags = p_flags; }

private:
	MxCore* m_client;        ///< [AI] The object to tickle (call Tickle() on periodically). [AI]
	MxTime m_interval;       ///< [AI] How often to tickle the client (in ms). [AI]
	MxTime m_lastUpdateTime; ///< [AI] The last time the client was tickled. [AI]
	MxU16 m_flags;           ///< [AI] Bitflags for client status/intent. 0x01 indicates pending destruction. [AI]
};

/// @brief [AI] List type for holding multiple MxTickleClient pointers (the tickle registry). [AI]
typedef list<MxTickleClient*> MxTickleClientPtrList;

// VTABLE: LEGO1 0x100d86d8
// VTABLE: BETA10 0x101bc9d0
// SIZE 0x14
/**
 * @brief [AI] Manages ticking ("tickling") a set of MxCore objects at specified intervals.
 *
 * MxTickleManager maintains a list of MxTickleClient entries—each representing a client object and its tickle interval.
 * On each Tickle() call, the manager updates all registered clients, invoking their Tickle() method as needed 
 * (if the interval has elapsed). Used throughout the engine to provide periodic updates for animation, streaming, 
 * and other time-dependent logic.
 * @details [AI]
 * Intended to be used as a centralized update/ticking system for polymorphic objects, decoupling specific
 * object update logic from the main game/application loop.
 */
class MxTickleManager : public MxCore {
public:
	/**
	 * @brief [AI] Constructs an empty tickle manager. [AI]
	 */
	MxTickleManager() {}

	/**
	 * @brief [AI] Destroys the tickle manager, unregistering and freeing all clients.
	 * @details [AI] Calls delete on every registered MxTickleClient. [AI]
	 */
	~MxTickleManager() override;

	/**
	 * @brief [AI] Iterates over registered clients and invokes their Tickle() methods as needed.
	 * @details [AI]
	 * For each client whose tickle interval has elapsed, MxTickleManager calls their Tickle() 
	 * method and updates their last-tickled timestamp. Clients flagged for destruction are dropped.
	 * @return SUCCESS if the tickle pass completes. [AI]
	 */
	MxResult Tickle() override;                                                // vtable+0x08

	/**
	 * @brief [AI] Registers an MxCore object to receive periodic tickles.
	 * @param p_client Object to manage. [AI]
	 * @param p_interval Time in ms between tickles. [AI]
	 * @details [AI] If the client is not already registered, adds it to the list. [AI]
	 */
	virtual void RegisterClient(MxCore* p_client, MxTime p_interval);          // vtable+0x14

	/**
	 * @brief [AI] Unregisters (marks for destruction) a previously registered client.
	 * @param p_client Object to remove. [AI]
	 * @details [AI]
	 * Sets a destruction flag on the tickle client entry, causing it to be deleted on the next tickle pass.
	 */
	virtual void UnregisterClient(MxCore* p_client);                           // vtable+0x18

	/**
	 * @brief [AI] Changes the tickle interval of an already registered client.
	 * @param p_client Object to update. [AI]
	 * @param p_interval New interval in ms. [AI]
	 * @details [AI] Only updates if client is not marked for destruction. [AI]
	 */
	virtual void SetClientTickleInterval(MxCore* p_client, MxTime p_interval); // vtable+0x1c

	/**
	 * @brief [AI] Looks up the tickle interval of a registered client.
	 * @param p_client The object to query. [AI]
	 * @return The interval in ms, or TICKLE_MANAGER_NOT_FOUND if not found. [AI]
	 */
	virtual MxTime GetClientTickleInterval(MxCore* p_client);                  // vtable+0x20

	// SYNTHETIC: LEGO1 0x1005a510
	// SYNTHETIC: BETA10 0x100962f0
	// MxTickleManager::`scalar deleting destructor'

private:
	MxTickleClientPtrList m_clients; ///< [AI] The current set of registered tickle clients. [AI]
};

#define TICKLE_MANAGER_NOT_FOUND 0x80000000 ///< [AI] Returned by GetClientTickleInterval when the client is not found. [AI]

// TEMPLATE: LEGO1 0x1005a4a0
// list<MxTickleClient *,allocator<MxTickleClient *> >::~list<MxTickleClient *,allocator<MxTickleClient *> >

// TEMPLATE: BETA10 0x10093870
// List<MxTickleClient *>::List<MxTickleClient *>

// TEMPLATE: LEGO1 0x1005a530
// TEMPLATE: BETA10 0x10096340
// List<MxTickleClient *>::~List<MxTickleClient *>

#endif // MXTICKLEMANAGER_H
