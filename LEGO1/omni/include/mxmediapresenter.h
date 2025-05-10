#ifndef MXMEDIAPRESENTER_H
#define MXMEDIAPRESENTER_H

#include "decomp.h"
#include "mxpresenter.h"
#include "mxstreamchunklist.h"

class MxDSSubscriber;

// VTABLE: LEGO1 0x100d4cd8
// SIZE 0x50

/**
 * @brief [AI] Abstract base class for presenters that play back continuous media streams such as video or audio.
 * [AI] Handles streaming of media chunks, looping, action control, and communicates with a MxDSSubscriber for data provisioning.
 */
class MxMediaPresenter : public MxPresenter {
public:
	/**
	 * @brief [AI] Constructs the presenter, initializing all member variables.
	 */
	MxMediaPresenter() { Init(); }

	/**
	 * @brief [AI] Destructor; cleans up and optionally destroys all internal resources as well as the MxDSSubscriber and chunk list/cursor.
	 * @details [AI] If called from destructor, does not call base class Destroy to avoid double-destruction.
	 */
	~MxMediaPresenter() override { Destroy(TRUE); }

	/**
	 * @brief [AI] Cleans up internal resources and resets the presenter to an uninitialized state.
	 * @details [AI] This variant is called by the engine or directly to destroy; does NOT call base class destroy (useful for subclass-specific cleanup).
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief [AI] Advances the presenter's state and media stream, if any, by tickling (i.e., updating) components.
	 * @details [AI] Handles chunk progression and invokes the correct tickle state based on stream state.
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief [AI] Gets the class name string for handler dispatch and RTTI emulation.
	 * @return [AI] Static string "MxMediaPresenter"
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f074c
		return "MxMediaPresenter";
	}

	/**
	 * @brief [AI] Returns the class name for this presenter (see HandlerClassName()).
	 * @return [AI] Class name string for RTTI/dispatch.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Returns TRUE if the provided class name matches this class or any of its parents.
	 * @param p_name [AI] Class name to check for identity or inheritance
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxMediaPresenter::ClassName()) || MxPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Per-frame update when streaming the media stream.
	 * @details [AI] Consumes and processes the next available chunk in the stream as data arrives.
	 */
	void StreamingTickle() override; // vtable+0x20

	/**
	 * @brief [AI] Per-frame update while looping/repeating over known chunks.
	 * @details [AI] Recirculates through buffered chunks if the action is set to loop mode.
	 */
	void RepeatingTickle() override; // vtable+0x24

	/**
	 * @brief [AI] Per-frame update for the "done" state; transitions this presenter to idle and ends the action.
	 */
	void DoneTickle() override;      // vtable+0x2c

	/**
	 * @brief [AI] Begins a new media playback action, wiring up the stream and chunk lists as needed.
	 * @param p_controller [AI] Controller providing the stream data source
	 * @param p_action [AI] Data structure describing the action parameters for playback
	 */
	MxResult StartAction(MxStreamController*, MxDSAction*) override; // vtable+0x3c

	/**
	 * @brief [AI] Ends the media playback action, releasing all resources, notifying listeners if necessary.
	 */
	void EndAction() override;                                       // vtable+0x40

	/**
	 * @brief [AI] Enables or disables media stream playback and transitions state as needed.
	 * @param p_enable [AI] TRUE to enable playback, FALSE to disable and reset.
	 */
	void Enable(MxBool p_enable) override;                           // vtable+0x54

	/**
	 * @brief [AI] Adds a chunk to the looping chunk list, making it available for repeated playback.
	 * @param p_chunk [AI] Chunk to duplicate and append to loopingChunk list.
	 */
	virtual void LoopChunk(MxStreamChunk* p_chunk);                  // vtable+0x58

	/**
	 * @brief [AI] Returns a pointer to the current data chunk at the head of the stream, without consuming it.
	 * @return [AI] May be NULL if no chunk is available.
	 */
	MxStreamChunk* CurrentChunk();

	/**
	 * @brief [AI] Returns the next data chunk in the stream, removing it from the stream queue.
	 * @return [AI] May be NULL if the stream is exhausted.
	 */
	MxStreamChunk* NextChunk();

	// SYNTHETIC: LEGO1 0x1000c680
	// MxMediaPresenter::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Subscriber that provides the stream data (e.g., audio/video chunks) for this presenter.
	 */
	MxDSSubscriber* m_subscriber;                  // 0x40

	/**
	 * @brief [AI] Linked list of all chunks available for looping/repeating playback.
	 */
	MxStreamChunkList* m_loopingChunks;            // 0x44

	/**
	 * @brief [AI] Cursor used to iterate through the loopingChunk list during repeat mode.
	 */
	MxStreamChunkListCursor* m_loopingChunkCursor; // 0x48

	/**
	 * @brief [AI] Currently active data chunk for playback or processing.
	 */
	MxStreamChunk* m_currentChunk;                 // 0x4c

	/**
	 * @brief [AI] Initializes all member variables to a known default state (NULL pointers, etc).
	 */
	void Init();

	/**
	 * @brief [AI] Frees all managed resources, owned memory and pointers, optionally preventing destruction of the base class.
	 * @param p_fromDestructor [AI] TRUE if called from the destructor, FALSE if called directly.
	 */
	void Destroy(MxBool p_fromDestructor);
};

// SYNTHETIC: LEGO1 0x100b46e0
// MxStreamChunkListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x100b4750
// MxListCursor<MxStreamChunk *>::~MxListCursor<MxStreamChunk *>

// SYNTHETIC: LEGO1 0x100b47a0
// MxListCursor<MxStreamChunk *>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x100b4810
// MxStreamChunkListCursor::~MxStreamChunkListCursor

#endif // MXMEDIAPRESENTER_H