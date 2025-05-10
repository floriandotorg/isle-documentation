#ifndef MXWAVEPRESENTER_H
#define MXWAVEPRESENTER_H

#include "decomp.h"
#include "mxsoundpresenter.h"

#include <dsound.h>

// VTABLE: LEGO1 0x100d49a8
// SIZE 0x6c
/**
 * @brief [AI] Presenter for streaming and managing PCM waveform audio via DirectSound buffer.
 * @details [AI] This class handles reading, streaming, playing, and managing PCM audio data ("wave" format)
 * using DirectSound buffers, facilitating sound playback features such as 3D sound, chunked streaming, pause/resume,
 * volume management, and direct buffer operations. Used for WAV files in the LEGO Island engine.
 */
class MxWavePresenter : public MxSoundPresenter {
public:
	/**
	 * @brief [AI] Constructs MxWavePresenter and initializes all members.
	 */
	MxWavePresenter() { Init(); }

	/**
	 * @brief [AI] Destroys the wave presenter and releases all associated resources, including sound buffers and memory.
	 */
	~MxWavePresenter() override { Destroy(TRUE); } // vtable+0x00

	/**
	 * @brief [AI] Explicit resource release. Optionally skips base class destruction depending on flag.
	 * @param p_fromDestructor Indicates if called from destructor or not. [AI]
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief [AI] Pauses audio playback, halting sound buffer while keeping position for resume.
	 * [AI]
	 */
	virtual void Pause();  // vtable+0x64

	/**
	 * @brief [AI] Resumes audio playback after a pause, restarting sound from the current buffer position.
	 * [AI]
	 */
	virtual void Resume(); // vtable+0x68

	/**
	 * @brief [AI] Returns pause state of the current audio playback.
	 * @return TRUE if audio is currently paused. [AI]
	 */
	virtual MxBool IsPaused() { return m_paused; } // vtable+0x6c

	/**
	 * @brief [AI] Returns the name identifying this presenter class.
	 * @return Static string representing handler class name. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f07b4
		return "MxWavePresenter";
	}

	/**
	 * @brief [AI] Returns the class name string at runtime.
	 * @details [AI] Used for type identification and RTTI-like checks.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if this instance is of the given class or a parent class.
	 * @param p_name Class name to check against. [AI]
	 * @return TRUE if matches class or parent. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxWavePresenter::ClassName()) || MxSoundPresenter::IsA(p_name);
	}

	void ReadyTickle() override;                     // vtable+0x18
	void StartingTickle() override;                  // vtable+0x1c
	void StreamingTickle() override;                 // vtable+0x20
	void DoneTickle() override;                      // vtable+0x2c
	void ParseExtra() override;                      // vtable+0x30
	MxResult AddToManager() override;                // vtable+0x34
	void EndAction() override;                       // vtable+0x40
	MxResult PutData() override;                     // vtable+0x4c
	void Enable(MxBool p_enable) override;           // vtable+0x54
	void LoopChunk(MxStreamChunk* p_chunk) override; // vtable+0x58
	void SetVolume(MxS32 p_volume) override;         // vtable+0x60

	/**
	 * @brief [AI] Holds WAVE PCM format info for DirectSound buffer creation and streaming.
	 * @details [AI] Contains data describing PCM wave format, the audio data size, and custom flags.
	 * Used to describe format and allocation for DirectSound interaction.
	 */
	struct WaveFormat {
		PCMWAVEFORMAT m_pcmWaveFormat; ///< [AI] PCM format struct containing standard Windows WAVE format fields.
		MxU32 m_dataSize;              ///< [AI] Size of data buffer for the wave data.
		MxU32 m_flags;                 ///< [AI] Custom format-related flags.
	};

	// SYNTHETIC: LEGO1 0x1000d810
	// MxWavePresenter::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Initializes all member variables to safe/empty values.
	 */
	void Init();

	/**
	 * @brief [AI] Fully tears down/cleans up presenter state and releases resources.
	 * @param p_fromDestructor TRUE if called from destructor; used to decide whether to also destroy base class. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Returns the index of the currently played chunk in the sound buffer.
	 * @return Index of current chunk, or -1 if unknown/error. [AI]
	 */
	MxS8 GetPlayedChunks();

	/**
	 * @brief [AI] Checks if more chunks can or should be streamed into buffer.
	 * @return TRUE if buffer has room for or needs new chunk(s). [AI]
	 */
	MxBool FUN_100b1ba0();

	/**
	 * @brief [AI] Writes a block of audio data to the DirectSound buffer at the correct chunk offset.
	 * @param p_audioPtr Pointer to audio data to write. [AI]
	 * @param p_length Number of bytes to write. [AI]
	 */
	void WriteToSoundBuffer(void* p_audioPtr, MxU32 p_length);

	WaveFormat* m_waveFormat;       ///< [AI] Pointer to the wave format struct for buffer description/allocation.
	LPDIRECTSOUNDBUFFER m_dsBuffer; ///< [AI] DirectSound buffer handling PCM sample playback.
	MxU32 m_chunkLength;            ///< [AI] Size in bytes for one audio streaming chunk.
	MxU32 m_lockSize;               ///< [AI] Size in bytes for current buffer lock/write operation.
	MxU8 m_writtenChunks;           ///< [AI] Number of chunks written into the DirectSound buffer.
	MxBool m_started;               ///< [AI] TRUE if audio playback has started on the buffer.
	MxBool m_is3d;                  ///< [AI] TRUE if buffer/audio is 3D spatialized.
	MxS8 m_silenceData;             ///< [AI] Value written as silence into buffer when needed (format-dependent, e.g., 0 or 0x7F).
	MxBool m_paused;                ///< [AI] TRUE if playback is currently paused.
};

#endif // MXWAVEPRESENTER_H