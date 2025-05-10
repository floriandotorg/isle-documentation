#ifndef LEGOCACHSOUND_H
#define LEGOCACHSOUND_H

#include "decomp.h"
#include "lego3dsound.h"
#include "mxcore.h"
#include "mxstring.h"

// VTABLE: LEGO1 0x100d4718
// VTABLE: BETA10 0x101bb6f0
// SIZE 0x88

/**
 * @brief Sound cache object managing DirectSound buffers and 3D positioning for preloaded sound data. [AI]
 * @details Used to pre-load sound data into a DirectSound buffer, allowing efficient playback with 3D spatialization via Lego3DSound. Handles both sound data management (copy, free) and buffer control (volume, positional updates, muting, looping, stop/play). [AI]
 */
class LegoCacheSound : public MxCore {
public:
	/**
	 * @brief Constructs a new LegoCacheSound and initializes its members to default/empty state. [AI]
	 */
	LegoCacheSound();
	/**
	 * @brief Destructor; releases owned sound resources and buffer, unmutes if needed. [AI]
	 */
	~LegoCacheSound() override; // vtable+0x00

	/**
	 * @brief Returns class name (for run-time type checks); always "LegoCacheSound". [AI]
	 * @return The string "LegoCacheSound". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// not in BETA10
		// STRING: LEGO1 0x100f01c4
		return "LegoCacheSound";
	}

	/**
	 * @brief Checks if this object has a class name equal to p_name, traversing parents. [AI]
	 * @param p_name Name to check against this class or its base classes. [AI]
	 * @return TRUE if p_name matches or parent returns TRUE [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoCacheSound::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief Creates the sound object with given audio format, source path, volume, and initializes DirectSound buffer with provided PCM data. [AI]
	 * @param p_pwfx Pointer to PCM audio format. [AI]
	 * @param p_mediaSrcPath Source path, used for identifying/basename only. [AI]
	 * @param p_volume Initial playback volume (0..100 range expected). [AI]
	 * @param p_data PCM audio data (copied internally, may be nullptr). [AI]
	 * @param p_dataSize Size of audio data buffer (must match buffer allocation if p_data provided). [AI]
	 * @return SUCCESS if buffer creation and setup succeeded, FAILURE otherwise. [AI]
	 */
	virtual MxResult Create(
		LPPCMWAVEFORMAT p_pwfx,
		MxString p_mediaSrcPath,
		MxS32 p_volume,
		MxU8* p_data,
		MxU32 p_dataSize
	);                                                 // vtable+0x14

	/**
	 * @brief Releases allocated DirectSound buffer and internal data, resetting all fields. [AI]
	 */
	virtual void Destroy();                            // vtable+0x18
	/**
	 * @brief Unknown legacy/function stub. Does nothing. [AI]
	 * @param param1 Unknown (possibly reserved/legacy). [AI]
	 * @param param2 Unknown (possibly reserved/legacy). [AI]
	 */
	virtual void FUN_10006cd0(undefined4 param1, undefined4 param2); // vtable+0x1c

	/**
	 * @brief Getter for an unknown string field, likely the sound's base filename. [AI]
	 * @return Base filename or unique identifier for this sound, derived from mediaSrcPath. [AI]
	 */
	const MxString& GetUnknown0x48() const { return m_unk0x48; }

	/**
	 * @brief Returns whether this sound is currently playing or is flagged as 'active'. [AI]
	 * @return TRUE if sound is playing, should be updated, or is otherwise 'active'. [AI]
	 */
	const MxBool GetUnknown0x58() const { return m_unk0x58; }

	/**
	 * @brief Creates an identical copy of this LegoCacheSound, including memory buffers, properties, and audio state. [AI]
	 * @details Used when multiple independent instances of the same preloaded audio asset are desired, e.g. in overlapping sound effect playback. [AI]
	 * @return Pointer to the new clone or nullptr if copy fails. [AI]
	 */
	LegoCacheSound* Clone();

	/**
	 * @brief Starts playback of the cached sound in this buffer. Sets loop mode, resets buffer, writes audio and starts play. [AI]
	 * @param p_name Optional: Tag/name representing playback event or context. [AI]
	 * @param p_looping If TRUE, playback will loop; if FALSE, plays once. [AI]
	 * @return SUCCESS if playback starts, FAILURE for missing/invalid buffer/data. [AI]
	 */
	MxResult Play(const char* p_name, MxBool p_looping);

	/**
	 * @brief Immediately stops playback and resets buffer, clearing event tag and position cues. [AI]
	 */
	void Stop();

	/**
	 * @brief Handles sound updates per tick; manages stopping, buffer state, and 3D-position refreshes if sound is looping/non-looping. [AI]
	 * @details Called every tick to check playback status for looping sound, update position for 3D audio, mute, or stop when finished. [AI]
	 */
	void FUN_10006be0();

	/**
	 * @brief Sets minimum and maximum audible distances for 3D sound attenuation. [AI]
	 * @param p_min Minimum distance for unattenuated playback. [AI]
	 * @param p_max Maximum distance at which sound will be silent. [AI]
	 */
	void SetDistance(MxS32 p_min, MxS32 p_max);

	/**
	 * @brief Mutes/unmutes by scaling volume to minimum (muted) or restoring original volume. [AI]
	 * @param p_muted If TRUE, mute by reducing volume; if FALSE, restore volume. [AI]
	 */
	void MuteSilence(MxBool p_muted);

	/**
	 * @brief Mutes/unmutes by stopping (mute) or resuming playback. [AI]
	 * @param p_mute If TRUE, mute by stopping playback; if FALSE, resume. [AI]
	 */
	void MuteStop(MxBool p_mute);

	// SYNTHETIC: LEGO1 0x10006610
	// SYNTHETIC: BETA10 0x100675b0
	// LegoCacheSound::`scalar deleting destructor'

private:
	/**
	 * @brief Initializes all data members to default/zero; helper for constructor and reset. [AI]
	 */
	void Init();

	/**
	 * @brief Copies PCM audio data into internal buffer, replacing previous data and updating length. [AI]
	 * @param p_data Source PCM data (must be non-null, p_dataSize > 0). [AI]
	 * @param p_dataSize Number of bytes of PCM to copy. [AI]
	 */
	void CopyData(MxU8* p_data, MxU32 p_dataSize);

	/**
	 * @brief Extracts the base filename (w/o extension or path) from a full source path. [AI]
	 * @details For example, "C:\\Sounds\\MySound.wav" → "MySound" [AI]
	 * @param p_path String containing full file path. [AI]
	 * @return Base filename as string. [AI]
	 */
	MxString GetBaseFilename(MxString& p_path);

	LPDIRECTSOUNDBUFFER m_dsBuffer; ///< DirectSound buffer for sample storage and playback [AI]
	undefined m_unk0x0c[4];         ///< Unknown/reserved, likely padding or legacy pointer [AI]
	Lego3DSound m_sound;            ///< 3D sound controller; manages 3D position, attenuation, updates [AI]
	MxU8* m_data;                   ///< PCM audio data buffer (copied from Create). [AI]
	MxU32 m_dataSize;               ///< Size of PCM buffer. [AI]
	MxString m_unk0x48;             ///< Stores base filename or audio resource identifier (from Create/GetBaseFilename). [AI]
	MxBool m_unk0x58;               ///< Active/playback flag: TRUE when sound is playing and should tick. [AI]
	PCMWAVEFORMAT m_wfx;            ///< Audio format descriptor for this sound sample. [AI]
	MxBool m_looping;               ///< Loop playback mode flag [AI]
	MxBool m_unk0x6a;               ///< 3D engine streaming/silence-resume flag, used to manage play/stop when unavailable. [AI]
	MxS32 m_volume;                 ///< Current (normalized) playback volume for buffer [AI]
	MxBool m_unk0x70;               ///< Playing or potentially playing flag, used in tickling logic. [AI]
	MxString m_unk0x74;             ///< Playback event/tag name, to distinguish instances. [AI]
	MxBool m_muted;                 ///< TRUE if sound is muted through MuteSilence or MuteStop. [AI]
};

#endif // LEGOCACHSOUND_H
