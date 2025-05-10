#ifndef MXLOOPINGFLCPRESENTER_H
#define MXLOOPINGFLCPRESENTER_H

#include "decomp.h"
#include "mxflcpresenter.h"

// VTABLE: LEGO1 0x100dc480
// SIZE 0x6c

/**
 * @brief [AI] Presents a looping FLC (Autodesk Animator FLIC) animation, extending the core FLC presenter to support frame looping behavior. [AI]
 * @details [AI] The MxLoopingFlcPresenter is responsible for handling the playback of FLC animations that loop, commonly used for endlessly repeating cutscenes or animated elements in the game. In addition to normal playback, it manages looping state, repeated updates via Tickle manager, and the correct looping of individual animation chunks. [AI]
 */
class MxLoopingFlcPresenter : public MxFlcPresenter {
public:
	/**
	 * @brief [AI] Constructs the looping FLC presenter and initializes internal state. [AI]
	 */
	MxLoopingFlcPresenter();

	/**
	 * @brief [AI] Destructor. Cleans up and optionally destroys internal state depending on usage context. [AI]
	 */
	~MxLoopingFlcPresenter() override;

	/**
	 * @brief [AI] Gets the handler class name string for dynamic presenter dispatch. [AI]
	 * @return Static string identifying this class for presenter name dispatch ("MxLoopingFlcPresenter"). [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x10101e20
		return "MxLoopingFlcPresenter";
	}

	/**
	 * @brief [AI] Returns the class name used for runtime type identification. [AI]
	 * @details [AI] Override to match HandlerClassName, facilitating RTTI and scripting. [AI]
	 * @return The class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Called during the repeating tickle state in the tickle loop to handle animation looping logic. [AI]
	 * @details [AI] Advances through animation chunks, resets them if needed, and applies timing adjustments for continuous repetition. [AI]
	 */
	void RepeatingTickle() override;  // vtable+0x24

	/**
	 * @brief [AI] Adds this presenter to the tickle manager for updates. [AI]
	 * @details [AI] Ensures internal critical section is used to avoid race conditions when adding. [AI]
	 * @return MxResult indicating SUCCESS or FAILURE of the operation. [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Destroys the presenter, cleaning up resources and unregistering from tickle managers if needed. [AI]
	 * @details [AI] Overridden to separate destruction from the destructor and optionally destroy the base when not from object destructor context. [AI]
	 */
	void Destroy() override;          // vtable+0x38

	/**
	 * @brief [AI] Loads and advances to the next animation frame, updating loop counters and timing. [AI]
	 * @details [AI] Handles chunk loading, looping, and updates elapsed duration for timing control of the loop. [AI]
	 */
	void NextFrame() override;        // vtable+0x64

	/**
	 * @brief [AI] Custom virtual function at vtable offset 0x88, responsible for updating current looping frame or moving to freezing state based on elapsed duration. [AI]
	 * @details [AI] Checks if total elapsed duration has exceeded the configured action duration, and advances frame or freezes as appropriate. [AI]
	 */
	virtual void VTable0x88();        // vtable+0x88

	// SYNTHETIC: LEGO1 0x100b4390
	// MxLoopingFlcPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes the looping FLC presenter and its internal state. [AI]
	 * @details [AI] Sets loop counters and internal flags for a new or reset animation run. [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Cleans up and resets the object state, optionally cascading destruction to base class if not called from destructor. [AI]
	 * @param p_fromDestructor Whether the call is from the object destructor (if FALSE, destroys base as well). [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Number of ticks (milliseconds) elapsed in the current animation loop run. [AI]
	 * @details [AI] Used to track how long the animation has been playing and when to freeze/stop or repeat based on configured action duration. [AI]
	 */
	MxLong m_elapsedDuration; // 0x68
};

#endif // MXLOOPINGFLCPRESENTER_H
