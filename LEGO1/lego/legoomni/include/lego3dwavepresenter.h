#ifndef LEGO3DWAVEPRESENTER_H
#define LEGO3DWAVEPRESENTER_H

#include "decomp.h"
#include "lego3dsound.h"
#include "mxwavepresenter.h"

// VTABLE: LEGO1 0x100d52b0
// SIZE 0xa0

/**
 * @brief [AI] Handles the presentation of 3D positional audio using DirectSound buffers within the LEGO Island engine. 
 * Inherits from MxWavePresenter to add 3D sound support. Used to play in-world audio that must be positioned and updated each frame according to the game world's logic and the listener (camera) position.
 * @details [AI] This class encapsulates a Lego3DSound object which manages the actual 3D sound buffer, and integrates with the tickling/updating system to correctly stream and update the source position in 3D. It may also fetch additional initialization parameters from associated MxDSAction objects or from parent presenters (e.g., MxCompositePresenter).
 */
class Lego3DWavePresenter : public MxWavePresenter {
public:
	/**
	 * @brief [AI] Returns the class name for presenter dispatching.
	 * @return Pointer to a string literal with the handler class name. [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Returns the name used for IsA() type identification and dispatch.
	 * @return Pointer to class name string. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if another class matches this or a parent class type name.
	 * @param p_name Name to compare for type checking. [AI]
	 * @return True if this or a parent class matches the name. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Performs setup and initial buffer management prior to starting audio streaming.
	 * @details [AI] Handles initializing 3D sound mode and creating the 3D buffer from action data. Also processes "FROM_PARENT" extra data to inherit audio initialization from the parent presenter if needed.
	 */
	void StartingTickle() override;   // vtable+0x1c

	/**
	 * @brief [AI] Updates the 3D buffer position each tick, keeping audio in sync with moving objects in the world.
	 * @details [AI] Calls Lego3DSound::UpdatePosition() so that audio tracks the correct world location. [AI]
	 */
	void StreamingTickle() override;  // vtable+0x20

	/**
	 * @brief [AI] Registers the presenter with the tickle manager, initializes for 3D mode if relevant.
	 * @details [AI] Calls base implementation and further enables 3D sound if supported by the engine state. [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Cleans up internal 3D sound resources and DirectSound objects, and reinitializes base presenter.
	 * @details [AI] Called during destruction or detachment, ensures all associated memory is freed and presenter state is safely reset. [AI]
	 */
	void Destroy() override;          // vtable+0x38

	// SYNTHETIC: LEGO1 0x1000f4b0
	// Lego3DWavePresenter::`scalar deleting destructor'

private:
	undefined m_unk0x6c[4]; ///< @brief [AI][AI_SUGGESTED_NAME: m_reserved] Unknown purpose; padding or reserved space for future or internal usage. [AI]
	Lego3DSound m_sound; ///< @brief [AI] Manages 3D DirectSound buffer and updates, encapsulating all DirectSound3D logic for positional audio. [AI]
};

#endif // LEGO3DWAVEPRESENTER_H