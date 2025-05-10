#ifndef MXMUSICMANAGER_H
#define MXMUSICMANAGER_H

#include "decomp.h"
#include "mxaudiomanager.h"

#include <windows.h>

// VTABLE: LEGO1 0x100dc930
// SIZE 0x58

/**
 * @brief Manages MIDI music playback with Win32 MIDI streaming for the LEGO Island engine. [AI]
 * @details MxMusicManager inherits from MxAudioManager and extends it with MIDI handling, including streaming, looping, MIDI hardware initialization, and volume/multiplier mixing controls. Designed for music playback, including looping, dynamic volume control, and integration with audio tickling threads for timing. [AI]
 */
class MxMusicManager : public MxAudioManager {
public:
	/**
	 * @brief Constructs an instance and initializes member data. [AI]
	 */
	MxMusicManager();

	/**
	 * @brief Destructor, ensures proper cleanup of resources and MIDI deinitialization. [AI]
	 */
	~MxMusicManager() override;

	/**
	 * @brief Releases all resources and stops streaming. [AI]
	 * @details Disables music playback and unregisters the tickle client. Called automatically from the destructor with p_fromDestructor=TRUE, or manually with p_fromDestructor=FALSE. [AI]
	 * @param p_fromDestructor TRUE if called from destructor (does not call base class Destroy if true). [AI]
	 */
	void Destroy() override; // vtable+18

	/**
	 * @brief Sets the music playback volume, taking into account multiplier for overall gain adjustment. [AI]
	 * @param p_volume Percentage of the total volume (0-100). [AI]
	 */
	void SetVolume(MxS32 p_volume) override; // vtable+2c

	/**
	 * @brief Initializes and starts MIDI playback. [AI]
	 * @details Optionally creates a tickle thread for timing, or registers this as a tickle client with the given tick interval (in ms). [AI]
	 * @param p_frequencyMS Interval in ms between tickle updates. [AI]
	 * @param p_createThread If TRUE, creates a separate MxTickleThread for streaming. If FALSE, uses global TickleManager. [AI]
	 * @return SUCCESS on initialization, FAILURE otherwise. [AI]
	 */
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread); // vtable+30

	/**
	 * @brief Checks if the MIDI system is currently initialized and ready. [AI]
	 * @return TRUE if initialized, FALSE otherwise. [AI]
	 */
	MxBool GetMIDIInitialized() { return m_midiInitialized; }

	/**
	 * @brief Retrieves the current hardware MIDI out volume. [AI]
	 * @details If unable to get volume, sets to calculated value corresponding to 100%. [AI]
	 * @param p_volume Variable to receive current MIDI volume (hardware format, two-channel 0x0000HHHH | 0x0000LLLL). [AI]
	 */
	void GetMIDIVolume(DWORD& p_volume)
	{
		if (midiOutGetVolume((HMIDIOUT) m_midiStreamH, &p_volume)) {
			p_volume = CalculateVolume(100);
		}
	}

	/**
	 * @brief Schedules and streams the next chunk of MIDI data; handles buffer looping and completion. [AI]
	 * @details Returns FAILURE on buffer underrun/error, or if looping/completion disables playback. [AI]
	 */
	MxResult ResetStream();

	/**
	 * @brief Resets the MIDI buffer to the starting offset and sets the buffer size to the full stream. [AI]
	 */
	void ResetBuffer();

	/**
	 * @brief Initializes streaming for a MIDI data buffer and begins playback. [AI]
	 * @param p_data Pointer to MIDI data buffer, expected to be prepared for streaming. [AI]
	 * @param p_loopCount Number of times to loop playback, or -1 for infinite. [AI]
	 * @return SUCCESS if initialization succeeds and playback starts, FAILURE otherwise. [AI]
	 */
	MxResult InitializeMIDI(MxU8* p_data, MxS32 p_loopCount);

	/**
	 * @brief Stops playback and releases all MIDI streaming resources. [AI]
	 * @details Restores hardware volume to original, stops stream, unprepares header, and deletes buffer data. [AI]
	 */
	void DeinitializeMIDI();

	/**
	 * @brief Sets the volume multiplier for scaling volume output. [AI]
	 * @details Used for fade in/out or global gain controls on top of per-track volume. [AI]
	 * @param p_multiplier Multiplier value (percentage, where 100 = normal, 0 = muted). [AI]
	 */
	void SetMultiplier(MxS32 p_multiplier);

private:
	/**
	 * @brief Cleans up all streaming, buffer and MIDI resources; optionally as part of destructor. [AI]
	 * @param p_fromDestructor Set TRUE if called from destructor to prevent base class destruction loop. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief Computes the MIDI hardware volume value (both channels) from percentage input. [AI]
	 * @param p_volume Volume value in range 0-100. [AI]
	 * @return MIDI hardware volume DWORD, both channels set to calculated 16-bit value. [AI]
	 */
	MxS32 CalculateVolume(MxS32 p_volume);

	/**
	 * @brief Sets the current music volume on the MIDI output device, combining track volume and multiplier. [AI]
	 */
	void SetMIDIVolume();

	/**
	 * @brief WinMM MIDI streaming callback; triggers on completion of buffer, schedules next chunk. [AI]
	 * @details Used as a function pointer for the Win32 MIDI streaming API. [AI]
	 * @param p_hdrvr Driver handle (unused). [AI]
	 * @param p_uMsg Callback message (expect MOM_DONE for buffer completion). [AI]
	 * @param p_dwUser User data (this pointer). [AI]
	 * @param p_dw1 Reserved/wave header. [AI]
	 * @param p_dw2 Reserved. [AI]
	 */
	static void CALLBACK MidiCallbackProc(HDRVR p_hdrvr, UINT p_uMsg, DWORD p_dwUser, DWORD p_dw1, DWORD p_dw2);

	HMIDISTRM m_midiStreamH;     ///< Handle to Win32 MIDI stream. [AI]
	MxBool m_midiInitialized;    ///< TRUE if streaming is set up/active. [AI]
	MxU32 m_bufferSize;          ///< Number of MIDI data blocks in buffer. [AI]
	MxU32 m_bufferCurrentSize;   ///< Number of data blocks remaining in buffer. [AI]
	MxU8* m_bufferOffset;        ///< Pointer to start of MIDI data buffer. [AI]
	MxU8* m_bufferCurrentOffset; ///< Current offset for streaming/reading within buffer. [AI]
	MxU32 m_loopCount;           ///< Playback loops remaining (-1 = infinite). [AI]
	MIDIHDR* m_midiHdrP;         ///< Pointer to Windows MIDI streaming header struct. [AI]
	MxS32 m_multiplier;          ///< Additional scaling for the audio volume. [AI]
	DWORD m_midiVolume;          ///< Hardware MIDI output device volume to restore on stop. [AI]

protected:
	/**
	 * @brief Initializes multipliers and buffer with default values; called from constructor/Destroy. [AI]
	 */
	void Init();

	/**
	 * @brief Initializes and zeros all associated MIDI-related member data. [AI]
	 * @details Used to reinitialize this object after deallocation or streaming end. [AI]
	 */
	void InitData();
};

#endif // MXMUSICMANAGER_H