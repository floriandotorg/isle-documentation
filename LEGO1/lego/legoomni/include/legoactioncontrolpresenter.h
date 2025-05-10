#ifndef LEGOACTIONCONTROLPRESENTER_H
#define LEGOACTIONCONTROLPRESENTER_H

#include "decomp.h"
#include "extra.h"
#include "mxmediapresenter.h"
#include "mxstring.h"

// VTABLE: LEGO1 0x100d5118
// SIZE 0x68

/**
 * @brief [AI] Presenter for controlling action logic (e.g., invoking named actions such as "RUN", "EXIT") through parsed SI script extra data.
 * @details [AI] LegoActionControlPresenter reads additional action instructions from SI file chunks (Extra data), parses key action commands, and communicates them (such as to composite presenters or game logic) via ActionType and string parameters. It manages state transitions and registration to the tickle system for time-based updates.
 *
 * It supports a protocol for parsing "ACTION" key-value pairs and triggers the corresponding engine-side actions, supporting extensible script-based control inside media tracks, typically for transition or entity invocation.
 */
class LegoActionControlPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs the presenter, initializing the parsed action as 'none'.
	 */
	LegoActionControlPresenter() : m_unk0x50(Extra::ActionType::e_none) {}

	/**
	 * @brief [AI] Destructor which unregisters from the tickle manager and performs resource cleanup.
	 * @param [AI] [p_fromDestructor=TRUE via vtable]
	 */
	~LegoActionControlPresenter() override { Destroy(TRUE); } // vtable+0x00

	/**
	 * @brief [AI] Returns the name of this presenter handler class.
	 * @details [AI] Used for presenter dispatch—matches SI file handler type to implementation.
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f05bc
		return "LegoActionControlPresenter";
	}

	/**
	 * @brief [AI] Returns the class name for dynamic type checking and dispatch.
	 * @details [AI] Used in game code for class hierarchy introspection.
	 * @return [AI] "LegoActionControlPresenter"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Runtime type check for casting/querying class type.
	 * @details [AI] Returns true if the parameter matches this class name or one of its base classes.
	 * @param p_name [AI] Class name queried for
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoActionControlPresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles tickle at the 'ready' state: parses and prepares for action invocation.
	 * @details [AI] This function checks for new chunks, parses associated Extra action data, and advances to 'starting' if an action is queued.
	 */
	void ReadyTickle() override;                   // vtable+0x18

	/**
	 * @brief [AI] Handles tickle at the 'repeating' state to invoke parsed actions.
	 * @details [AI] Invokes the parsed action (as set by ParseExtra) including associated data, then marks the presenter as 'done'.
	 */
	void RepeatingTickle() override;               // vtable+0x24

	/**
	 * @brief [AI] Parses the Extra field (from SI) for action commands and parameters.
	 * @details [AI] Interprets the Extra string for commands such as "ACTION:RUN;file;entity;" and sets up state for invocation.
	 */
	void ParseExtra() override;                    // vtable+0x30

	/**
	 * @brief [AI] Registers this presenter as a tickle client with the TickleManager.
	 * @details [AI] Ensures periodic updates for action processing; called before activation.
	 */
	MxResult AddToManager() override;              // vtable+0x34

	/**
	 * @brief [AI] Unregisters the presenter from the tickle manager and performs cleanup.
	 * @details [AI] If called not from the destructor, also destroys the base presenter.
	 * @param p_fromDestructor [AI] True if called from destructor context, false for manual destruction.
	 */
	virtual void Destroy(MxBool p_fromDestructor); // vtable+0x5c

private:
	Extra::ActionType m_unk0x50; ///< @brief [AI] Type of the parsed action (RUN, EXIT, etc.) [SI parsed].
	MxString m_unk0x54;          ///< @brief [AI] Parsed entity or file name (lowercased for lookup) from SI Extra data.
	undefined4 m_unk0x64;        ///< @brief [AI] Additional parameter for action (typically entity ID or numeric arg, from extra).
};

// SYNTHETIC: LEGO1 0x1000d1d0
// LegoActionControlPresenter::`scalar deleting destructor'

#endif // LEGOACTIONCONTROLPRESENTER_H
