#ifndef LEGOLOCOMOTIONANIMPRESENTER_H
#define LEGOLOCOMOTIONANIMPRESENTER_H

#include "legoloopinganimpresenter.h"
#include "legoroimaplist.h"

class LegoAnimActor;

// VTABLE: LEGO1 0x100d9170
// SIZE 0xd8
/**
 * @brief [AI] Specialized presenter class for handling locomotion animation playback and state in the LEGO Island game engine.
 * 
 * @details [AI] LegoLocomotionAnimPresenter is a subclass of LegoLoopingAnimPresenter, designed to manage animation sequences that are associated with locomotion (movement) of game entities. It manages additional internal lists for ROI (real-time object instance) mapping and controls the tickle/process state flow for animations bound to moving actors. It integrates with the variable table to dynamically assign variables used during animation binding.
 */
class LegoLocomotionAnimPresenter : public LegoLoopingAnimPresenter {
public:
	/**
	 * @brief [AI] Constructs a new LegoLocomotionAnimPresenter and initializes internal members.
	 */
	LegoLocomotionAnimPresenter();
	/**
	 * @brief [AI] Destructor. Cleans up resources, memory, and state used by this presenter instance.
	 */
	~LegoLocomotionAnimPresenter() override;

	/**
	 * @brief [AI] Gets the handler class name for this presenter type.
	 * @return Pointer to a static string literal representing this presenter's handler class name. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f06e4
		return "LegoLocomotionAnimPresenter";
	}

	/**
	 * @brief [AI] Gets the class name for run-time type identification.
	 * @return Static string literal of this class' name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if the given name matches the class (or any ancestor) for run-time type queries.
	 * @param p_name Class name to compare against. [AI]
	 * @return Whether this instance matches or is derived from the given class name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || LegoLoopingAnimPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Called during the ready tickle state to prepare for animation processing and add itself to the world if necessary.
	 */
	void ReadyTickle() override;                          // vtable+0x18
	/**
	 * @brief [AI] Called during the starting tickle state to dequeue and process any pending animation data chunks.
	 */
	void StartingTickle() override;                       // vtable+0x1c
	/**
	 * @brief [AI] Called during the streaming state to manage lifecycle and check if further processing is required.
	 */
	void StreamingTickle() override;                      // vtable+0x20
	/**
	 * @brief [AI] Registers this presenter with manager systems and initializes additional ROI mapping state.
	 * @return Result code, FAILURE if unable to allocate resources. [AI]
	 */
	MxResult AddToManager() override;                     // vtable+0x34
	/**
	 * @brief [AI] Completely cleans up and deletes this presenter's resources. Should not be called directly—use Destroy() instead.
	 */
	void Destroy() override;                              // vtable+0x38
	/**
	 * @brief [AI] Ends the bound action/animation for this presenter, finalizing any running videos or related resources.
	 */
	void EndAction() override;                            // vtable+0x40
	/**
	 * @brief [AI] Called to process/queue a frame for this presenter's active animation playback.
	 */
	void PutFrame() override;                             // vtable+0x6c
	/**
	 * @brief [AI] Creates an animation sequence from a stream chunk and initializes playback.
	 * @param p_chunk Pointer to a stream chunk containing animation data. [AI]
	 * @return Result of creating the animation, propagates parent return unless successful. [AI]
	 */
	MxResult CreateAnim(MxStreamChunk* p_chunk) override; // vtable+0x88

	// SYNTHETIC: LEGO1 0x1006cfe0
	// LegoLocomotionAnimPresenter::`scalar deleting destructor'

	/**
	 * @brief [AI] Binds a LegoAnimActor to the internal animation context and ROI mapping.
	 * @param p_actor The animation actor to associate. [AI]
	 * @param p_value An animation phase or weight value to use for the association. [AI]
	 * @details [AI] Internally, this updates the variable table to match the actor's ROI name with the animation, invokes mapping/finalization routines for ROI binding, and may invoke additional actor update routines.
	 */
	void FUN_1006d680(LegoAnimActor* p_actor, MxFloat p_value);

	/**
	 * @brief [AI] Decrements the reference/lightweight counter controlling an internal streaming/cleanup state.
	 */
	void DecrementUnknown0xd4()
	{
		if (m_unk0xd4) {
			--m_unk0xd4;
		}
	}

	/**
	 * @brief [AI] Accessor for m_unk0xd4, a lightweight counter used internally to gate certain state transitions.
	 * @return Value of m_unk0xd4. [AI]
	 */
	undefined2 GetUnknown0xd4() { return m_unk0xd4; }

private:
	/**
	 * @brief [AI] Initializes all internal members to their starting state, nulls pointers, and resets counters.
	 */
	void Init();
	/**
	 * @brief [AI] Final cleanup for destruction, including memory, ROI mapping, and optionally notifies parent destruction.
	 * @param p_fromDestructor When TRUE, only cleans this object; when FALSE, also destroys parent state. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	undefined4 m_unk0xc0;         ///< [AI] Unknown: part of internal bookkeeping, cleared on Init/Destroy. [AI]
	undefined4* m_unk0xc4;        ///< [AI] Unknown: appears to be a dynamically allocated array, deleted in Destroy. [AI]
	LegoROIMapList* m_roiMapList; ///< [AI] List of ROI map objects corresponding to active animation bindings and instantiations.
	MxS32 m_unk0xcc;              ///< [AI] Unknown: initialized to -1 in Init, likely a sentinel or state code.
	MxS32 m_unk0xd0;              ///< [AI] Unknown: initialized to -1, likely another status, index, or parameter.
	undefined2 m_unk0xd4;         ///< [AI] Counter for in-progress streaming/processing state. Incremented/decremented during tickle/evolution.
};

#endif // LEGOLOCOMOTIONANIMPRESENTER_H