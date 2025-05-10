#ifndef MXLOOPINGMIDIPRESENTER_H
#define MXLOOPINGMIDIPRESENTER_H

#include "mxmidipresenter.h"

// VTABLE: LEGO1 0x100dc240
// SIZE 0x58

/**
 * @brief [AI] Handles playback and management of looping MIDI actions, extending MIDI presentation functionality for repeated/looped music in the game. [AI]
 * @details [AI] MxLoopingMIDIPresenter is a concrete subclass of MxMIDIPresenter that is responsible for proper MIDI playback when a MIDI track requires looping for a specified number of times, or infinitely. It interprets the loop count contained in the action, controls tickle states according to loop status, and interacts with the central music system for (re)initializing MIDI playback. [AI]
 */
class MxLoopingMIDIPresenter : public MxMIDIPresenter {
public:
	/**
	 * @brief [AI] Returns the concrete handler class name string for dynamic type identification and lookup, required for the presenter's type dispatch system.
	 * @return [AI] Static string literal: "MxLoopingMIDIPresenter"
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x10101de0
		return "MxLoopingMIDIPresenter";
	}

	/**
	 * @brief [AI] Returns the dynamic class name string, used for reflection within the game engine.
	 * @details [AI] Returns the same value as HandlerClassName(), as would be expected for the lowest-derived class.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Runtime type-check supporting engine reflection and inheritance hierarchy matching.
	 * @details [AI] Returns true if the queried name is "MxLoopingMIDIPresenter" or if an ancestor class returns true for the same query. Used by the Omni engine for dynamic type safety. [AI]
	 * @param p_name Class name string to check against hierarchy [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxLoopingMIDIPresenter::ClassName()) || MxMIDIPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Called every game tick while in streaming state, manages progression and looping for MIDI playback. [AI]
	 * @details [AI] Handles chunk management and decides if playback should proceed, loop, or advance state according to elapsed time and loop count. [AI]
	 * @see MxPresenter::StreamingTickle [AI]
	 */
	void StreamingTickle() override; // vtable+0x20

	/**
	 * @brief [AI] Called every game tick in the "done" state, finalizes action and increments loop if required.
	 * @details [AI] If looping, passes control to base; otherwise, ends the playback action. [AI]
	 * @see MxPresenter::DoneTickle [AI]
	 */
	void DoneTickle() override;      // vtable+0x2c

	/**
	 * @brief [AI] Initializes MIDI playback, setting volume and ensuring looping properties are applied.
	 * @details [AI] Called during tickling; ensures the MIDI chunk is played with correct loop count, using game music manager.
	 * @return [AI] Result code for operation success/failure (typically SUCCESS). [AI]
	 */
	MxResult PutData() override;     // vtable+0x4c
};

// SYNTHETIC: LEGO1 0x100b19c0
// MxLoopingMIDIPresenter::`scalar deleting destructor'

#endif // MXLOOPINGMIDIPRESENTER_H