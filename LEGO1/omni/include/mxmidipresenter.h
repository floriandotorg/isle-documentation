#ifndef MXMIDIPRESENTER_H
#define MXMIDIPRESENTER_H

#include "mxmusicpresenter.h"

class MxStreamChunk;

// VTABLE: LEGO1 0x100dca20
// SIZE 0x58
/**
 * @brief MIDI presenter class responsible for handling playback of MIDI music streams. [AI]
 * @details [AI]
 * The MxMIDIPresenter class extends MxMusicPresenter and manages the streaming, initialization, 
 * and control of MIDI music playback, using the tickle architecture to advance playback states.
 * It interacts with a MxMusicManager to control MIDI hardware/software. It also manages
 * the lifecycle of the streamed MIDI chunks. [AI]
 */
class MxMIDIPresenter : public MxMusicPresenter {
public:
	/**
	 * @brief Constructs an MxMIDIPresenter object and initializes its data. [AI]
	 * @details [AI]
	 * Calls Init() to initialize internal pointers and state. [AI]
	 */
	MxMIDIPresenter();

	/**
	 * @brief Destructor, ensures proper resource cleanup for MIDI playback. [AI]
	 * @details [AI]
	 * Calls Destroy(TRUE) for full destruction, cleaning up stream chunks
	 * and deinitializing the MIDI system. [AI]
	 */
	~MxMIDIPresenter() override;

	/**
	 * @brief Returns the handler class name for this presenter. [AI]
	 * @return Pointer to static class name string "MxMIDIPresenter". [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief Returns the class name for run-time type identification. [AI]
	 * @return The handler class name string for run-time type checks. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief Checks if this instance matches a class type by name. [AI]
	 * @param p_name The class name string to compare. [AI]
	 * @return TRUE if p_name matches this class or a parent, FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief Tickle state for preparing the presenter before playback starts. [AI]
	 * @details [AI]
	 * Releases the next MIDI chunk if available and transitions to starting tickle. [AI]
	 */
	void ReadyTickle() override;             // vtable+0x18

	/**
	 * @brief Tickle state for initializing MIDI playback of the current chunk. [AI]
	 * @details [AI]
	 * Waits for the correct time and transitions to streaming tickle when ready. [AI]
	 */
	void StartingTickle() override;          // vtable+0x1c

	/**
	 * @brief Tickle state for streaming (playing) the MIDI chunk. [AI]
	 * @details [AI]
	 * Moves to done tickle state if chunk has finished, otherwise fetches next chunk. [AI]
	 */
	void StreamingTickle() override;         // vtable+0x20

	/**
	 * @brief Tickle state signaling that playback is done. [AI]
	 * @details [AI]
	 * Ends the current action if MIDI subsystem is no longer initialized. [AI]
	 */
	void DoneTickle() override;              // vtable+0x2c

	/**
	 * @brief Cleanup resources, free MIDI data, and deinitialize MIDI. [AI]
	 * @details [AI]
	 * Public interface for resource cleanup. [AI]
	 */
	void Destroy() override;                 // vtable+0x38

	/**
	 * @brief Called when playback/action is finished or needs to be ended. [AI]
	 * @details [AI]
	 * Cleans up MIDI and resets tickle state as needed. [AI]
	 */
	void EndAction() override;               // vtable+0x40

	/**
	 * @brief Actually provides MIDI stream data to the playback system. [AI]
	 * @details [AI]
	 * Initializes and starts playback of MIDI data if streaming and the chunk is ready. [AI]
	 * Ends the action if initialization fails. [AI]
	 */
	MxResult PutData() override;             // vtable+0x4c

	/**
	 * @brief Sets the playback volume for MIDI music. [AI]
	 * @param p_volume The new volume multiplier value. [AI]
	 * @details [AI]
	 * Updates both internal volume and notifies the music manager to use the correct multiplier. [AI]
	 */
	void SetVolume(MxS32 p_volume) override; // vtable+0x60

	// SYNTHETIC: LEGO1 0x100c27a0
	// MxMIDIPresenter::`scalar deleting destructor'
	// [AI] Standard compiler-generated destructor for proper memory cleanup

private:
	/**
	 * @brief Initializes internal members to their default values. [AI]
	 * @details [AI]
	 * Sets pointers such as m_chunk to NULL on construction or reset. [AI]
	 */
	void Init();

	/**
	 * @brief Helper for destruction logic, optionally full or partial based on flag. [AI]
	 * @param p_fromDestructor TRUE if called during destruction, FALSE if by explicit destroy. [AI]
	 * @details [AI]
	 * Frees the current chunk, releases critical section, and deinitializes MIDI.
	 * Only calls base class Destroy if not called from destructor. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

protected:
	/**
	 * @brief Current MIDI data chunk being streamed/played. [AI]
	 * @details [AI]
	 * Set when a new MIDI chunk is obtained and cleared on playback completion or destruction. [AI]
	 */
	MxStreamChunk* m_chunk; // 0x54 [AI]
};

#endif // MXMIDIPRESENTER_H
