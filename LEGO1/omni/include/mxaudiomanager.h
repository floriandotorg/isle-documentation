#ifndef MXAUDIOMANAGER_H
#define MXAUDIOMANAGER_H

#include "decomp.h"
#include "mxmediamanager.h"

// VTABLE: LEGO1 0x100dc6e0
// SIZE 0x30

/**
 * @brief [AI] Audio subsystem manager for the LEGO Island engine, responsible for managing audio playback and audio resources.
 * @details [AI] MxAudioManager is derived from MxMediaManager, providing specialized handling for audio initialization, shutdown, and runtime control (e.g., global volume adjustment). It maintains a static instance counter, and performs thread-safe operations via an internal critical section.
 */
class MxAudioManager : public MxMediaManager {
public:
	/**
	 * @brief [AI] Constructs the audio manager and initializes default volume.
	 */
	MxAudioManager();

	/**
	 * @brief [AI] Destructs the audio manager and handles cleanup of resources.
	 */
	~MxAudioManager() override;

	/**
	 * @brief [AI] Initializes audio subsystem resources and registers an instance for global audio management.
	 * @details [AI] Thread-safe; increments global audio manager instance count on success.
	 * @return MxResult indicating if the creation succeeded. [AI]
	 */
	MxResult Create() override; // vtable+14

	/**
	 * @brief [AI] Tears down the audio subsystem instance and unregisters it from global management.
	 * @details [AI] Thread-safe; decrements global audio manager instance count and releases resources.
	 */
	void Destroy() override;    // vtable+18

	/**
	 * @brief [AI] Gets the current global audio volume.
	 * @details [AI] Returns the current audio output volume (range and meaning engine-specific, default is 100).
	 * @return Current volume value. [AI]
	 */
	virtual MxS32 GetVolume() { return m_volume; } // vtable+28

	/**
	 * @brief [AI] Sets the current global audio volume.
	 * @details [AI] Thread-safe; updates audio output volume (does not scale individual sound channels).
	 * @param p_volume The desired volume to set. [AI]
	 */
	virtual void SetVolume(MxS32 p_volume); // vtable+2c

	// SYNTHETIC: LEGO1 0x100b8d70
	// MxAudioManager::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Internal destroy logic for audio manager with destructor context distinction.
	 * @details [AI] Performs thread-safe resource cleanup and calls base class destroy method if not invoked from destructor.
	 * @param p_fromDestructor TRUE if called from destructor, FALSE otherwise. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Counts the number of MxAudioManager instances active.
	 * @details [AI] Used for resource tracking and ensuring proper initialization/shutdown of shared audio subsystems.
	 */
	static MxS32 g_count;

protected:
	/**
	 * @brief [AI] Initializes audio manager state, setting default volume and other relevant fields.
	 * @details [AI] Called during construction and when resetting state on destroy.
	 */
	void Init();

	/**
	 * @brief [AI] Holds the current global audio volume for the game.
	 * @details [AI] Thread-safe access (via critical section). Default is 100. [AI_SUGGESTED_NAME: m_volume]
	 */
	MxS32 m_volume; // 0x2c
};

#endif // MXAUDIOMANAGER_H