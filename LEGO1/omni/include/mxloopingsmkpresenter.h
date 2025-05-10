#ifndef MXLOOPINGSMKPRESENTER_H
#define MXLOOPINGSMKPRESENTER_H

#include "decomp.h"
#include "mxsmkpresenter.h"

// VTABLE: LEGO1 0x100dc540
// SIZE 0x724
/**
 * @brief [AI] Presenter for looping Smacker video resources. Handles playback and repeat logic for SMK video streams, managing frame/state progression and reset for looping animations. [AI]
 * @details [AI] Extends MxSmkPresenter by adding logic for repeating/looping a video resource. Implements special handling for frame progression and timing, including repeating tickle states, loop duration management, and palette resets. Used for videos in SI scripts that should play in a loop. [AI]
 */
class MxLoopingSmkPresenter : public MxSmkPresenter {
public:
	/**
	 * @brief [AI] Constructs a looping SMK presenter and initializes resources and state. [AI]
	 */
	MxLoopingSmkPresenter();

	/**
	 * @brief [AI] Destructor, releases internal resources and calls cleanup as needed. [AI]
	 */
	~MxLoopingSmkPresenter() override; // vtable+0x00

	/**
	 * @brief [AI] Returns the handler class name used in presenter dispatching: "MxLoopingSmkPresenter". [AI]
	 * @return Pointer to literal class name string. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x10101e08
		return "MxLoopingSmkPresenter";
	}

	/**
	 * @brief [AI] Returns the class name string, used for type identification and debugging. [AI]
	 * @return Pointer to literal class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Processes the repeating tickle state, manages looping frame/time logic and state transitions for repeating video playback. [AI]
	 * @details [AI] When in repeating tickle state, advances frames, handles end/beginning of the video, and resets palettes and timing as needed to achieve a loop. [AI]
	 */
	void RepeatingTickle() override;  // vtable+0x24

	/**
	 * @brief [AI] Adds this presenter to its manager, handling resource/thread safety and registration. [AI]
	 * @details [AI] Acquires a lock for thread safety and delegates to the base class for actual addition. [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] General object destruction routine, releases resources and unregisters presenter from the manager if appropriate. [AI]
	 * @details [AI] Calls Destroy with p_fromDestructor=FALSE, which may perform additional cleanup beyond basic object teardown. [AI]
	 */
	void Destroy() override;          // vtable+0x38

	/**
	 * @brief [AI] Advances to the next frame of the video, managing end of stream logic and frame reloading for looping playback. [AI]
	 * @details [AI] When end of stream is reached, the tickle state advances to repeating, otherwise loads current frame, loops, and adjusts timing based on video FPS. [AI]
	 */
	void NextFrame() override;        // vtable+0x64

	/**
	 * @brief [AI] Handles palette resets and frame control at the logical end of a loop. [AI]
	 * @details [AI] If the current frame reaches the total frame count, resets current frame and clears the video palette to begin a new loop cycle. [AI]
	 */
	void VTable0x88() override;       // vtable+0x88

	/**
	 * @brief [AI] Processes looped frame loading and tickle state progression during loop playback. [AI]
	 * @details [AI] If the elapsed duration exceeds the intended loop duration, tickle state is advanced to freezing; otherwise, it continues looping through the video frames, adjusting elapsed time. [AI]
	 * @note [AI] Virtual: meant to allow further refinement of frame looping strategy in subclasses. [AI]
	 */
	virtual void VTable0x8c();        // vtable+0x8c

private:
	/**
	 * @brief [AI] Initializes the looping presenter, resetting all internal state and flags for a new playback cycle. [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Cleans up internal state, resets for destruction or new cycles. If not called from destructor, also destroys base resources. [AI]
	 * @param p_fromDestructor Whether this destroy call is due to destructor logic. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Duration in milliseconds of elapsed playback within the current loop cycle. Used for tracking progress toward end of loop and state transitions for repeating/freeze. [AI]
	 */
	MxLong m_elapsedDuration; // 0x720
};

// SYNTHETIC: LEGO1 0x100b4930
// MxLoopingSmkPresenter::`scalar deleting destructor'

#endif // MXLOOPINGSMKPRESENTER_H
