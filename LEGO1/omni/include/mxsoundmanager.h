#ifndef MXSOUNDMANAGER_H
#define MXSOUNDMANAGER_H

#include "decomp.h"
#include "mxatom.h"
#include "mxaudiomanager.h"

#include <dsound.h>

// VTABLE: LEGO1 0x100dc128
// VTABLE: BETA10 0x101c1ce8
// SIZE 0x3c

/**
 * @brief [AI] Manages DirectSound-based sound playback, implementing volume, resource, and device management.
 * @details [AI] MxSoundManager provides sound output by controlling DirectSound device and primary buffer. It creates, manages, and destroys relevant resources, integrating with the main tickle/timer system for updating sound playback, volume, and pausing/resuming playback, including compatibility with both standard and 3D audio. It is thread-safe for sound playback through critical section management.
 */
class MxSoundManager : public MxAudioManager {
public:
	/**
	 * @brief [AI] Constructs a new MxSoundManager instance.
	 * @details [AI] Initializes all DirectSound pointers and internal state to a safe default.
	 */
	MxSoundManager();

	/**
	 * @brief [AI] Destructor for MxSoundManager.
	 * @details [AI] Releases all DirectSound resources and unregisters from tickle managers if necessary.
	 */
	~MxSoundManager() override; // vtable+0x00

	/**
	 * @brief [AI] Releases sound resources and unregisters from tickle system.
	 * @details [AI] Used to safely clean up all managed resources, either explicitly or from destruction.
	 */
	void Destroy() override; // vtable+0x18

	/**
	 * @brief [AI] Sets the global audio output volume for all managed sound presenters.
	 * @param p_volume Volume level as an integer percentage (0-100). [AI]
	 * @details [AI] Iterates through all managed sound presenters and sets their individual volumes to match the manager's global volume.
	 */
	void SetVolume(MxS32 p_volume) override; // vtable+0x2c

	/**
	 * @brief [AI] Initializes and sets up the DirectSound environment.
	 * @param p_frequencyMS Tickle/update frequency in milliseconds for updating sound playback. [AI]
	 * @param p_createThread If true, runs the tickle loop in a dedicated thread, otherwise uses the tickle manager. [AI]
	 * @return SUCCESS if initialization succeeded, otherwise FAILURE.
	 * @details [AI] Creates the DirectSound interface, sets the cooperative level, and configures the primary buffer (for 3D or regular sound according to the application's setting). Registers for tickle updates either via a thread or the global tickle manager.
	 */
	virtual MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread); // vtable+0x30

	/**
	 * @brief [AI] Pauses all currently playing wave presenters.
	 * @details [AI] Iterates through all managed presenters and pauses those that are MxWavePresenter. Used for suspending sound playback (e.g., when the game is minimized).
	 */
	virtual void Pause(); // vtable+0x34

	/**
	 * @brief [AI] Resumes all previously paused wave presenters.
	 * @details [AI] Iterates through all managed presenters and resumes those that are MxWavePresenter. Used for continuing sound playback after a pause.
	 */
	virtual void Resume(); // vtable+0x38

	/**
	 * @brief [AI] Gets pointer to internal DirectSound interface.
	 * @return LPDIRECTSOUND interface pointer for use with low-level DirectSound APIs. [AI]
	 */
	LPDIRECTSOUND GetDirectSound() { return m_directSound; }

	/**
	 * @brief [AI] Maps a percentage volume (1-100) to a DirectSound-specific attenuation value.
	 * @param p_volume The desired volume as a percentage, 1 (min, not zero) to 100 (max). [AI]
	 * @return The corresponding DirectSound attenuation value, ranging from -10000 (silent) to 0 (loudest).
	 * @details [AI] Returns a lookup from a static table for DirectSound volume attenuation.
	 */
	MxS32 GetAttenuation(MxU32 p_volume);

	/**
	 * @brief [AI] Finds a presenter matching a specific atom ID and object ID.
	 * @param p_atomId The atom ID corresponding to a resource (audio object identifier). [AI]
	 * @param p_objectId Unique object instance identifier used to distinguish between multiple sounds of the same type. [AI]
	 * @return A pointer to the matching MxPresenter, or NULL if no match is found.
	 * @details [AI] Used to locate a currently-active sound presenter for a given asset/object pair.
	 */
	MxPresenter* FUN_100aebd0(const MxAtomId& p_atomId, MxU32 p_objectId);

protected:
	/**
	 * @brief [AI] Internal initialization routine for member variables and DirectSound pointers.
	 * @details [AI] Sets all internal pointers to NULL, called during construction and resource resets.
	 */
	void Init();

	/**
	 * @brief [AI] Internal destroy logic for use both in destructor and standard resource reset.
	 * @param p_fromDestructor Set true if called from destructor to avoid recursive destruction of base classes. [AI]
	 * @details [AI] Releases DirectSound resources, primary buffer, and manages tickle registration/threads as appropriate. Optionally cascades to parent class destroy.
	 */
	void Destroy(MxBool p_fromDestructor);

	LPDIRECTSOUND m_directSound;    ///< @brief [AI] Pointer to main DirectSound interface. Needed for all DirectSound operations.
	LPDIRECTSOUNDBUFFER m_dsBuffer; ///< @brief [AI] Primary DirectSound buffer interface for setting output format/volume.
	undefined m_unk0x38[4];         ///< @brief [AI] Unknown, reserved/unused memory or opaque data per binary compatibility. [AI_SUGGESTED_NAME: reserved] [AI]
};

// SYNTHETIC: LEGO1 0x100ae7b0
// MxSoundManager::`scalar deleting destructor'

#endif // MXSOUNDMANAGER_H
