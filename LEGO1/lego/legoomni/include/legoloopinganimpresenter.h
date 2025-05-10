#ifndef LEGOLOOPINGANIMPRESENTER_H
#define LEGOLOOPINGANIMPRESENTER_H

#include "legoanimpresenter.h"

// VTABLE: LEGO1 0x100d4900
// SIZE 0xc0
/**
 * @brief [AI] Presenter for looping animated sequences in the LEGO Island engine. [AI]
 *
 * This class specializes the LegoAnimPresenter to support looping behavior for animations, automatically
 * repeating the animation sequence and synchronizing presenter state with the encompassing composite presenter.
 * Used for animated objects where the animation should restart seamlessly. [AI]
 */
class LegoLoopingAnimPresenter : public LegoAnimPresenter {
public:
	/**
	 * @brief [AI] Returns the name of the handler class as a static string. [AI]
	 *
	 * This is used by the PresenterNameDispatch mechanism to identify this handler. [AI]
	 * @return Class handler name, always "LegoLoopingAnimPresenter". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0700
		return "LegoLoopingAnimPresenter";
	}

	/**
	 * @brief [AI] Returns the actual class name for runtime type identification. [AI]
	 *
	 * Used in IsA() for hierarchy checks. [AI]
	 * @return The class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if this object is or derives from a class of the given name. [AI]
	 * @param p_name Name of class to check against. [AI]
	 * @return True if class matches or is in hierarchy, false otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || LegoAnimPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Called every streaming tickle to update looping/animation progress. [AI]
	 *
	 * Handles input data streaming, internal state transitions (Loop/Done), and notifies the composite presenter if the sequence is completed.
	 * Transitions to 'done' state if the animation reaches its full duration for non-looping scenarios. [AI]
	 * See implementation for transition logic. [AI]
	 */
	void StreamingTickle() override; // vtable+0x20

	/**
	 * @brief [AI] Advances animation to the correct frame, applying looping time logic. [AI]
	 *
	 * Calculates the animation frame taking into account the elapsed time and start time, looping within the duration.
	 * Also updates all controlled animatable objects with the correct transformation matrices for this time instant,
	 * doing vector/matrix math for correct placement in the scene. [AI]
	 * Updates camera relationships if relevant. [AI]
	 */
	void PutFrame() override;        // vtable+0x6c

private:
	/**
	 * @brief [AI] Internal state or flag for looping animation completion [AI_SUGGESTED_NAME: m_loopDoneFlag]
	 *
	 * Likely used to indicate completion of the looping animation sequence and to signal finishing behavior. [AI]
	 */
	undefined4 m_unk0xbc; // 0xbc
};

// SYNTHETIC: LEGO1 0x1006d000
// LegoLoopingAnimPresenter::~LegoLoopingAnimPresenter

// SYNTHETIC: LEGO1 0x1000f440
// LegoLoopingAnimPresenter::`scalar deleting destructor'

#endif // LEGOLOOPINGANIMPRESENTER_H