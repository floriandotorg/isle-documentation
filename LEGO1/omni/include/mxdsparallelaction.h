#ifndef MXDSPARALLELACTION_H
#define MXDSPARALLELACTION_H

#include "mxdsmultiaction.h"

// VTABLE: LEGO1 0x100dcf80
// VTABLE: BETA10 0x101c2988
// SIZE 0x9c
/**
 * @brief [AI] Represents an action that can play multiple MxDSActions in parallel. This is the parallel-composite derived from MxDSMultiAction that specifically models simultaneous execution of its contained actions within the LEGO Island SI system.
 * @details [AI] Each child action will play simultaneously (on the timeline) when this parallel action is executed by the DS engine. Handles aggregation of durations, including handling special duration rules for media actions with sustain times, and applies looping logic if needed. Used in scripts compiled from SI files for orchestration of several "tracks" of actions.
 */
class MxDSParallelAction : public MxDSMultiAction {
public:
	/**
	 * @brief [AI] Constructs a parallel action object. Sets the type field to e_parallelAction.
	 */
	MxDSParallelAction();

	/**
	 * @brief [AI] Copy constructor for parallel actions. Calls CopyFrom to handle deep copying of any member data.
	 * @param p_dsParallelAction [AI] The other MxDSParallelAction to copy from.
	 */
	MxDSParallelAction(MxDSParallelAction& p_dsParallelAction);

	/**
	 * @brief [AI] Destroys the parallel action.
	 */
	~MxDSParallelAction() override;

	/**
	 * @brief [AI] Copies all member data from another parallel action into this one. Use when duplicating or assigning actions to ensure state is correctly replicated.
	 * @param p_dsParallelAction [AI] The other MxDSParallelAction whose value should be copied.
	 */
	void CopyFrom(MxDSParallelAction& p_dsParallelAction);

	/**
	 * @brief [AI] Assignment operator. Ensures proper deep copy from another parallel action.
	 * @param p_dsParallelAction [AI] The source parallel action to assign from.
	 * @return Reference to this MxDSParallelAction for chaining.
	 */
	MxDSParallelAction& operator=(MxDSParallelAction& p_dsParallelAction);

	/**
	 * @brief [AI] Returns the class name identifier for runtime type checking and SI parsing.
	 * @details [AI] Used by IsA and SI logic for detecting the action type hierarchy at runtime.
	 * @return "MxDSParallelAction".
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102608
		return "MxDSParallelAction";
	}

	/**
	 * @brief [AI] Performs runtime type checking, including base classes. Determines if the current object is of the type named in p_name.
	 * @details [AI] Used in SI and action scripting system for type-safe downcasting and script event checking.
	 * @param p_name [AI] Name of the class type to check.
	 * @return True if this object is or inherits the requested type.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSParallelAction::ClassName()) || MxDSMultiAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Fetches the total duration in ticks of the parallel action, including all contained child actions and looping/bit3 logic.
	 * @details [AI] Computes the max duration across all child actions, factoring in media sustain time and looping, following SI semantics.
	 */
	MxLong GetDuration() override; // vtable+0x24

	/**
	 * @brief [AI] Sets the explicit duration for this action, overriding the computed aggregate.
	 * @param p_duration [AI] Duration, in SI time units/ticks, to be used for this action.
	 */
	void SetDuration(MxLong p_duration) override { m_duration = p_duration; } // vtable+0x28

	/**
	 * @brief [AI] Produces a complete copy (clone) of this parallel action, including deep-copied data members.
	 * @details [AI] Used for duplicating actions within the track/tree or during parallel/branching script evaluation.
	 * @return A pointer to the new MxDSParallelAction object cloned from this.
	 */
	MxDSAction* Clone() override; // vtable+0x2c

	// SYNTHETIC: LEGO1 0x100cb020
	// SYNTHETIC: BETA10 0x1015b420
	// MxDSParallelAction::`scalar deleting destructor'
};

#endif // MXDSPARALLELACTION_H
