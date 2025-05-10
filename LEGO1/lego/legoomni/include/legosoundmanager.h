#ifndef LEGOSOUNDMANAGER_H
#define LEGOSOUNDMANAGER_H

#include "mxsoundmanager.h"

class LegoCacheSoundManager;

/// \class LegoSoundManager
/// \brief [AI] Manages 3D sound effects and music playback for LEGO Island, integrating with DirectSound and providing caching.
/// \details [AI] This class extends MxSoundManager to add LEGO-specific sound management, including 3D audio listener control and caching of sound resources through LegoCacheSoundManager.
/// It is responsible for initializing DirectSound interfaces, updating the listener's position/orientation for 3D sound, and coordinating sound resource caches.
/// Size: 0x44 bytes.
/// VTABLE: LEGO1 0x100d6b10 / BETA10 0x101bec30
class LegoSoundManager : public MxSoundManager {
public:
	/// \brief [AI] Constructs the LegoSoundManager and initializes its internal members.
	LegoSoundManager();

	/// \brief [AI] Destructor. Cleans up resources, optionally as part of destruction. 
	~LegoSoundManager() override;

	/// \brief [AI] Performs periodic processing, such as updating the cache sound manager. Called by the main tick loop.
	/// \returns [AI] Status of the tick operation (see underlying tickle logic).
	MxResult Tickle() override;                                           // vtable+0x08

	/// \brief [AI] Cleans up and releases all resources used by the sound manager and its cache.
	void Destroy() override;                                              // vtable+0x18

	/// \brief [AI] Initializes the sound manager with a desired tick frequency and threading option.
	/// \param p_frequencyMS [AI] Desired tick/update interval, in milliseconds.
	/// \param p_createThread [AI] If TRUE, creates a separate audio thread for updates.
	/// \returns [AI] Result of the create operation.
	MxResult Create(MxU32 p_frequencyMS, MxBool p_createThread) override; // vtable+0x30

	/// \brief [AI] Updates the 3D sound listener properties in DirectSound, reflecting player/world changes.
	/// \param p_position [AI] 3D position vector of the listener (array of 3 floats). Can be nullptr.
	/// \param p_direction [AI] Forward direction vector of the listener (array of 3 floats). Can be nullptr.
	/// \param p_up [AI] Up vector of the listener (array of 3 floats). Can be nullptr.
	/// \param p_velocity [AI] Velocity vector of the listener (array of 3 floats). Can be nullptr.
	/// \details [AI] If any vector is not nullptr, applies the change and updates the DirectSound listener object.
	void UpdateListener(const float* p_position, const float* p_direction, const float* p_up, const float* p_velocity);

	/// \brief [AI] Returns the cache sound manager used to cache and reuse sound effects.
	/// \returns [AI] Pointer to the LegoCacheSoundManager instance.
	LegoCacheSoundManager* GetCacheSoundManager() { return m_cacheSoundManager; }

private:
	/// \brief [AI] Initializes member variables to default (safe) values.
	void Init();

	/// \brief [AI] Destroys sound resources and internal members, with an option for destructor-specific logic.
	/// \param p_fromDestructor [AI] If TRUE, indicates this is being called by the class destructor itself.
	void Destroy(MxBool p_fromDestructor);

	LPDIRECTSOUND3DLISTENER m_listener;         ///< [AI] DirectSound 3D listener interface for spatial audio. Used to set position/orientation. Offset 0x3c.
	LegoCacheSoundManager* m_cacheSoundManager; ///< [AI] Pointer to the LEGO sound resource cache for reused samples. Offset 0x40.
};

// GLOBAL: LEGO1 0x100db6d0 [AI] IID_IDirectSound3DListener (COM Interface GUID for DirectSound 3D Listener)

#endif // LEGOSOUNDMANAGER_H