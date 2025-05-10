#ifndef EXTRA_H
#define EXTRA_H

/**
 * @brief [AI] Items related to the Extra string of key-value pairs found in MxOb. 
 *        This structure defines possible action types that can be represented 
 *        in the Extra string, which appear to be operational instructions or 
 *        triggers for objects within the system, such as starting, stopping,
 *        or handling disk and RAM operations.
 * @details [AI] The Extra struct is used as a namespace for ActionType,
 *          which enumerates recognized commands (such as start, run, enable, etc)
 *          for objects that reference an "Extra" field, typically from SI file MxOb elements. 
 */
struct Extra {
	/**
	 * @brief [AI] Enumerates the possible operation types that may appear
	 *        as actions in the "Extra" key-value string of an MxOb.
	 * @details [AI] These actions serve as symbolic instructions for how to process or
	 *          interact with the object which owns the Extra field, for instance
	 *          to trigger resource loading (opendisk/openram), playback
	 *          (start/run/stop), resource or process shutdown (close/exit),
	 *          toggling internal states (enable/disable/notify), or placeholder/unrecognized
	 *          entries (none/unknown).
	 */
	enum ActionType {
		e_none = 0,      ///< [AI] No action / default value [AI]
		e_opendisk,      ///< [AI] Open resource from disk [AI]
		e_openram,       ///< [AI] Open resource from RAM [AI]
		e_close,         ///< [AI] Close the resource or action [AI]
		e_start,         ///< [AI] Start an activity or playback [AI]
		e_stop,          ///< [AI] Stop an activity or playback [AI]
		e_run,           ///< [AI] Run (execute) an operation [AI]
		e_exit,          ///< [AI] Exit an activity, context or resource [AI]
		e_enable,        ///< [AI] Enable a capability or flag [AI]
		e_disable,       ///< [AI] Disable a capability or flag [AI]
		e_notify,        ///< [AI] Notify observers or listeners [AI]
		e_unknown,       ///< [AI] Unrecognized or unclassified action [AI]
	};
};

#endif // EXTRA_H
