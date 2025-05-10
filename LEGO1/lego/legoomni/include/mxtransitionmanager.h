#ifndef MXTRANSITIONMANAGER_H
#define MXTRANSITIONMANAGER_H

#include "decomp.h"
#include "mxcore.h"

#include <ddraw.h>

class MxVideoPresenter;

/// @brief [AI] Handles screen transitions and animations (such as dissolve, mosaic, wipe, etc.) between scenes or active states.
/// @details [AI] MxTransitionManager manages visual transition effects in LEGO Island, coordinating animation speed, screen buffer management, integration with DirectDraw surfaces, and handling notification to relevant world objects when transitions complete. It also manages wait indicators and controls interplay between game logic, audio, and rendering during complex state changes. Handles session-level singleton transition animations while maintaining the effect's operational state and the associated temporary resources.
class MxTransitionManager : public MxCore {
public:
	/// @brief [AI] Initializes MxTransitionManager and resets all transition states and working buffers.
	MxTransitionManager();

	/// @brief [AI] Cleans up resources for the transition manager, deletes animation memory, notifies tickle manager, and removes wait indicator if present.
	~MxTransitionManager() override; // vtable+0x00

	/// @brief [AI] Sets or resets the visual wait indicator presented during blocking transitions.
	/// @param p_waitIndicator The new wait indicator (usually a movie clip such as a spinning brick) [AI]
	void SetWaitIndicator(MxVideoPresenter* p_waitIndicator);

	/// @brief [AI] Performs per-frame advancement of the current transition animation, advancing its state if necessary and drawing frames.
	/// @details [AI] Called by the tickle system; executes one increment of the active transition effect and manages notification, redraw and resource. If animation is complete, cleans up. [AI]
	MxResult Tickle() override; // vtable+0x08

	/// @brief [AI] Returns the class name of this object.
	/// @return The class name string "MxTransitionManager". [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return "MxTransitionManager";
	}

	/// @brief [AI] Determines if the class name matches with this type or its parents.
	/// @param p_name The class name to check [AI]
	/// @return TRUE if the class name matches (directly or by inheritance) [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxTransitionManager::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Retrieves the primary DirectDraw surface to render transitions onto, querying via the video manager.
	/// @details [AI] Called at the start of transitions to ensure the correct DirectDraw surface-vram pointer is acquired/locked. [AI]
	virtual MxResult GetDDrawSurfaceFromVideoManager(); // vtable+0x14

	/// @brief [AI] Enumerates all supported transition effect types.
	enum TransitionType {
		e_idle = 0,     ///< [AI] No transition is active.
		e_noAnimation,  ///< [AI] Instant clear/fill screen, no animated effect.
		e_dissolve,     ///< [AI] Black "pixels" dissolve across the screen in random order.
		e_mosaic,       ///< [AI] Complex mosaic block-out effect.
		e_wipeDown,     ///< [AI] Vertical wipe (top-down) fill.
		e_windows,      ///< [AI] Animated shrinking "window" effect from full screen edges inward.
		e_broken        ///< [AI] Invalid/buggy mode, causes hang, used for diagnostics or internal testing.
	};

	/// @brief [AI] Begins a new transition animation of type p_animationType at the specified speed, optionally copying the wait indicator, and managing audio appropriately.
	/// @param p_animationType Which transition style/animation to use [AI]
	/// @param p_speed Delay between animation frames, in ms (lower=faster) [AI]
	/// @param p_doCopy If TRUE, the wait indicator is visually presented/copied-on [AI]
	/// @param p_playMusicInAnim If TRUE, music continues, otherwise is stopped during animation [AI]
	/// @return SUCCESS if started, FAILURE if already busy [AI]
	MxResult StartTransition(TransitionType p_animationType, MxS32 p_speed, MxBool p_doCopy, MxBool p_playMusicInAnim);

	/// @brief [AI] Returns the currently active transition type.
	TransitionType GetTransitionType() { return m_mode; }

	// SYNTHETIC: LEGO1 0x1004b9e0
	// MxTransitionManager::`scalar deleting destructor'

private:
	/// @brief [AI] Called to finalize a transition and, if requested, notify the world that the transition is over.
	/// @param p_notifyWorld Whether to signal the world of transition completion. [AI]
	void EndTransition(MxBool p_notifyWorld);

	/// @brief [AI] Executes instant "no-animation" transition: instantly clears the screen and ends the transition.
	void NoTransition();

	/// @brief [AI] Executes one animation frame ("tick") of the dissolve effect, blacking out randomized screen pixels progressively.
	void DissolveTransition();

	/// @brief [AI] Executes one "tick" of the mosaic transition, which fills 10x10 screen blocks with a dominant color in randomly-ordered progression for a mosaic effect.
	void MosaicTransition();

	/// @brief [AI] Executes one "tick" of wipe-down (vertical bar) transition, blacking out two successive scanlines per frame from the top down.
	void WipeDownTransition();

	/// @brief [AI] Executes one "tick" of the expanding "window" transition, filling from screen edges inwards in a frame effect.
	void WindowsTransition();

	/// @brief [AI] Placeholder for a nonfunctional/experimental (buggy) transition; purposely does not finish or clear, causing the game to hang.
	void BrokenTransition();

	/// @brief [AI] Blits/copies the wait indicator visual to the DirectDraw surface if transition effect requires it.
	/// @param p_ddsc Locked DirectDraw surface descriptor for drawing [AI]
	void SubmitCopyRect(LPDDSURFACEDESC p_ddsc);

	/// @brief [AI] Reads from the current surface back-buffer and prepares the copy region to be presented as the wait indicator, capturing the indicator bitmap.
	/// @param p_ddsc Locked DirectDraw surface descriptor [AI]
	void SetupCopyRect(LPDDSURFACEDESC p_ddsc);

	MxVideoPresenter* m_waitIndicator; ///< [AI] Wait animation visual shown between transitions (e.g., spinning brick)
	RECT m_copyRect;                   ///< [AI] Rectangle region describing the indicator's current location for drawing/copying
	MxU8* m_copyBuffer;                ///< [AI] Buffer containing pixel data of the indicator, for reblitting
	FlagBitfield m_copyFlags;          ///< [AI] Bitfield controlling copy region presence and validity (bit0: enabled)
	undefined4 m_unk0x24;              ///< [AI] [AI_SUGGESTED_NAME: m_paddingOrReserved] Purpose unknown, possibly padding or reserved transitional data.
	FlagBitfield m_unk0x28;            ///< [AI] Secondary flag field used for additional transition state, specific meaning unknown.

	TransitionType m_mode; ///< [AI] Current transition animation state (which transition style is running, e.g., mosaic, dissolve, etc.)

	LPDIRECTDRAWSURFACE m_ddSurface; ///< [AI] Main DirectDraw VRAM surface pointer used for rendering transitions to the screen.
	MxU16 m_animationTimer;          ///< [AI] Animation frame/tick index, incremented each frame to drive progress in animation.
	MxU16 m_columnOrder[640];        ///< [AI] Column shuffle array for randomized animation order (used in dissolve/mosaic effects).
	MxU16 m_randomShift[480];        ///< [AI] Row-wise shuffle amount for pixel effect randomization in dissolve/mosaic.
	MxULong m_systemTime;            ///< [AI] Timestamp for next expected animation update (used for frame scheduling based on tick speed).
	MxS32 m_animationSpeed;          ///< [AI] Interval in ms between animation updates/ticks (higher = slower transition).
};

#endif // MXTRANSITIONMANAGER_H