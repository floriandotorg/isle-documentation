#ifndef MXMEDIAMANGER_H
#define MXMEDIAMANGER_H

#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxpresenterlist.h"
#include "mxtypes.h"

class MxThread;

// VTABLE: LEGO1 0x100dc6b0
// SIZE 0x2c
/**
 * @brief [AI] Central class for managing the lifecycle and thread-safety of MxPresenter objects for audio/video playback.
 * 
 * [AI] The MxMediaManager is responsible for keeping track of all currently active MxPresenter objects, 
 * providing registration/unregistration, and ticking each presenter as necessary. It ensures 
 * thread-safe access to its collections via an internal MxCriticalSection. 
 * This class is typically instantiated and owned by the engine singleton (MxOmni), 
 * and provides high-level media dispatching/coordination for cutscenes, sound and possibly video output.
 */
class MxMediaManager : public MxCore {
public:
	/**
	 * @brief [AI] Constructor. Initializes the manager to default values.
	 */
	MxMediaManager();

	/**
	 * @brief [AI] Destructor. Ensures destruction of all managed presenters and cleanup.
	 */
	~MxMediaManager() override;

	/**
	 * @brief [AI] Called by the tickle manager to step through and update all presenters, and process their output data.
	 * @details [AI] First, Tickle() calls the Tickle() method of each registered presenter to advance their playback or state. Then, in a separate pass, it calls PutData() on each presenter to request media data to be rendered/output. Both passes are performed under thread synchronization. 
	 * @return [AI] Returns SUCCESS after all presenters have been processed, or FAILURE on internal error.
	 */
	MxResult Tickle() override;                                 // vtable+08

	/**
	 * @brief [AI] Allocates and initializes the internal presenter list for this manager, ensuring thread safety.
	 * @details [AI] This must be called before the manager is used. Returns FAILURE if allocation fails, destroying internal state accordingly. Called internally by the constructor.
	 * @return [AI] SUCCESS on allocation, FAILURE on memory error.
	 */
	virtual MxResult Create();                                  // vtable+14

	/**
	 * @brief [AI] Destroys all registered presenters and resets the internal state, ensuring safe resource disposal.
	 * @details [AI] Safe to call multiple times. This method deletes the internal presenter list and re-initializes all pointer members, releasing any system resource. 
	 */
	virtual void Destroy();                                     // vtable+18

	/**
	 * @brief [AI] Register a new presenter for tickle management and playback coordination.
	 * @param p_presenter [AI] Presenter to register. Must be non-null and remain valid until unregistered or destroyed.
	 * @details [AI] Adds the presenter to the internal list so that it will participate in tickling (update/output). This should be called when a presenter becomes active.
	 */
	virtual void RegisterPresenter(MxPresenter& p_presenter);   // vtable+1c

	/**
	 * @brief [AI] Remove a presenter from tickle and managed output lists.
	 * @param p_presenter [AI] Presenter to unregister. Will be located and safely removed (if present).
	 * @details [AI] This should be called by presenters that are being destroyed or no longer need to participate in media output.
	 */
	virtual void UnregisterPresenter(MxPresenter& p_presenter); // vtable+20

	/**
	 * @brief [AI] Stops/ends the action on all registered presenters, typically halting all playback and output.
	 * @details [AI] Calls EndAction() on each presenter, signaling them to stop playback or transition to an idle state.
	 */
	virtual void StopPresenters();                              // vtable+24

	/**
	 * @brief [AI] Initializes all internal members to their default values.
	 * @details [AI] Called from the constructor and Destroy(). Zeros out pointers.
	 * @return [AI] Always returns SUCCESS.
	 */
	MxResult Init();

	// SYNTHETIC: LEGO1 0x100b8540
	// MxMediaManager::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Pointer to list of currently registered (active) presenters. List is thread-safe.
	 */
	MxPresenterList* m_presenters;       // 0x08

	/**
	 * @brief [AI] Optional pointer to a worker thread used for media dispatch/IO (if multi-threaded operation is used, otherwise NULL).
	 */
	MxThread* m_thread;                  // 0x0c

	/**
	 * @brief [AI] Critical section object used for guarding access to the presenter list and internal members for thread safety.
	 */
	MxCriticalSection m_criticalSection; // 0x10
};

#endif // MXMEDIAMANGER_H