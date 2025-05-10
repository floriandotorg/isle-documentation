#ifndef LEGO3DSOUND_H
#define LEGO3DSOUND_H

#include "decomp.h"
#include "mxtypes.h"

#include <dsound.h>

class LegoActor;
class LegoROI;

/// @brief [AI] Implements 3D positional sound logic for LEGO Island using DirectSound 3D buffers. 
/// Responsible for associating 3D sound buffer positions with game object positions (mainly LegoROI / LegoActor), 
/// managing sound properties (volume, frequency), and ensuring realtime in-world relevant audio updates.
/// [AI]
/// @details [AI] Each instance can be associated with a named object in the world. It keeps track of whether that object is an actor
/// (for special frequency handling) or a generic ROI, updates positional audio in the scene, and handles the lifecycle
/// of associated DirectSound resources and the linkage to game objects.
class Lego3DSound {
public:
	/// @brief [AI] Constructs a new Lego3DSound instance and initializes all members to safe default values. [AI]
	Lego3DSound();
	/// @brief [AI] Destroys the Lego3DSound object and releases associated DirectSound buffers and object references. [AI]
	virtual ~Lego3DSound();

	/// @brief [AI] Initializes internal fields to their defaults. Used by constructor and destroy logic. [AI]
	void Init();

	/// @brief [AI] Initializes 3D sound for a given DirectSound buffer and associates it with a named game object. Sets up position linkage and sound parameters. [AI]
	/// @param p_directSoundBuffer [AI] Pointer to the DirectSoundBuffer (2D) to initialize as a 3D buffer if available.
	/// @param p_name [AI] Name of the target in-world object (typically a character or other interactive object).
	/// @param p_volume [AI] Initial base volume to use for this sound.
	/// @return [AI] Returns SUCCESS on complete setup, FAILURE if the 3D buffer could not be acquired.
	MxResult Create(LPDIRECTSOUNDBUFFER p_directSoundBuffer, const char* p_name, MxS32 p_volume);

	/// @brief [AI] Cleans up and releases all resources (DirectSound 3D buffer, associated object references).
	void Destroy(); // [AI]

	/// @brief [AI] Recalculates and updates the sound position on the underlying DirectSound 3D buffer or the volume on a fallback 2D buffer based on the associated object's (ROI's) current world position.
	/// @param p_directSoundBuffer [AI] Pointer to the 2D buffer for fallback positional volume attenuation.
	/// @return [AI] TRUE if any positional or frequency update was applied, FALSE otherwise.
	MxU32 UpdatePosition(LPDIRECTSOUNDBUFFER p_directSoundBuffer);

	/// @brief [AI] Associates a new in-world object to this sound, updating its 3D position tracking and (if applicable) enabling 3D positional mode, or disables 3D mode if p_name is NULL.
	/// @param p_directSoundBuffer [AI] The buffer managed by this sound instance.
	/// @param p_name [AI] Name of the new object to track, or NULL to disable 3D mode for this buffer.
	void FUN_10011a60(LPDIRECTSOUNDBUFFER p_directSoundBuffer, const char* p_name); // [AI_SUGGESTED_NAME: SetTargetObject]

	/// @brief [AI] Releases any in-world/actor/ROI associations and resets member pointers. 
	void Reset(); // [AI]

	/// @brief [AI] Sets the minimum and maximum 3D sound effective distances if 3D sound is enabled.
	/// @param p_min [AI] Minimum 3D attenuation distance.
	/// @param p_max [AI] Maximum 3D attenuation distance.
	/// @return [AI] 0 on success, -1 if buffer is not available, 1 if not using 3D sound.
	MxS32 SetDistance(MxS32 p_min, MxS32 p_max);

	// SYNTHETIC: LEGO1 0x10011650
	// Lego3DSound::`scalar deleting destructor'

private:
	LPDIRECTSOUND3DBUFFER m_ds3dBuffer; ///< [AI] Pointer to associated DirectSound 3D buffer interface, or NULL if not using 3D sound.
	LegoROI* m_roi;                     ///< [AI] The tracked in-world object (ROI), typically a character or a specific scene element.
	LegoROI* m_positionROI;             ///< [AI] The tracked ROI for positional updates, which may be a special "head" ROI for actors.
	MxBool m_enabled;                   ///< [AI] TRUE if this instance is tracking a valid in-world object and is active.
	MxBool m_isActor;                   ///< [AI] TRUE if the associated ROI is a LegoActor (for special frequency updates).
	LegoActor* m_actor;                 ///< [AI] Cached pointer to actor (if m_isActor is true), otherwise NULL.
	double m_frequencyFactor;           ///< [AI] Current frequency multiplication factor for actor-based frequency modulation.
	DWORD m_dwFrequency;                ///< [AI] Base frequency of the DirectSound buffer as reported by DirectSound.
	MxS32 m_volume;                     ///< [AI] User-set base volume for the sound instance, used in non-3D/fallback attenuation mode.
};

// GLOBAL: LEGO1 0x100db6c0
// IID_IDirectSound3DBuffer

#endif // LEGO3DSOUND_H