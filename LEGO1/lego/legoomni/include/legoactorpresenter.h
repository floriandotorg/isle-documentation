#ifndef LEGOACTORPRESENTER_H
#define LEGOACTORPRESENTER_H

#include "legoentitypresenter.h"

// VTABLE: LEGO1 0x100d5320
// SIZE 0x50
/**
 * @brief [AI] Handles presentation logic specific to LegoActor entities, such as their instantiation, animation tickling, state-managed updates, and parsing script-based actions.
 * @details [AI] This presenter creates LegoActor entity instances based on the currently bound action, sets their position and orientation, drives their state machine (ready/starting/streaming/etc.), and parses extra actor command strings on activation. The tickle pattern enables frame-based control over entity state initialization and execution.
 */
class LegoActorPresenter : public LegoEntityPresenter {
public:
	// LegoActorPresenter() {}

	/**
	 * @brief [AI] Destructor for LegoActorPresenter.
	 * @details [AI] Ensures proper destruction of derived presenter resources; no special cleanup required at this level beyond base cleanup.
	 */
	~LegoActorPresenter() override {}

	/**
	 * @brief [AI] Returns the run-time handler class name for this presenter type.
	 * @details [AI] Used for run-time type dispatch and for "PresenterNameDispatch"-style factory methods.
	 * @return [AI] The string literal "LegoActorPresenter".
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f06a4
		return "LegoActorPresenter";
	}

	/**
	 * @brief [AI] Returns the class name used for IsA run-time checks.
	 * @details [AI] Required for reflection and safe downcasting in the scripting and presenter system.
	 * @return [AI] Class name string for LegoActorPresenter.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if this object inherits from or matches the given class name.
	 * @param p_name Name to test for inheritance or equivalence. [AI]
	 * @details [AI] Supports safe RTTI-style checks (ClassName or base).
	 * @retval TRUE if the class name matches (directly or via base), FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoActorPresenter::ClassName()) || LegoEntityPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Implements the "ready" tickle state for setting up the LegoActor entity.
	 * @details [AI] Responsible for creating the LegoActor instance, initializing its position, and forwarding state to "starting".
	 */
	void ReadyTickle() override;    // vtable+0x18

	/**
	 * @brief [AI] Implements the "starting" tickle state, finalizing initialization and transitioning to streaming.
	 * @details [AI] Waits until the actor's ROI (real object instance) is valid, then parses any extra action commands and advances the tickle state.
	 */
	void StartingTickle() override; // vtable+0x1c

	/**
	 * @brief [AI] Parses extra script data attached to the action, passing it to the entity for command execution.
	 * @details [AI] Used to read script commands like movement, sound, or mood triggered at actor instantiation time.
	 */
	void ParseExtra() override;     // vtable+0x30
};

// SYNTHETIC: LEGO1 0x1000cc30
// LegoActorPresenter::`scalar deleting destructor'

#endif // LEGOACTORPRESENTER_H
