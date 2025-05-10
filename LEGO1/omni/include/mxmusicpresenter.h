#ifndef MXMUSICPRESENTER_H
#define MXMUSICPRESENTER_H

#include "mxaudiopresenter.h"

// VTABLE: LEGO1 0x100dc9b8
// SIZE 0x54

/**
 * @brief [AI] Presenter class that handles playback and management of music (streamed or MIDI) in LEGO Island.
 * @details [AI] MxMusicPresenter extends MxAudioPresenter and is managed through MxMusicManager, which coordinates music-related events and playback across the game. Presenters are responsible for handling the lifecycle of a music event within the broader DirectShow-like sequence execution model. Music presenters may play background themes or other streamed music resources and must register/unregister themselves with the central music management system for correct sequencing and prioritization. Implements relevant interfaces for tickling and notification like all Presenters.
 */
class MxMusicPresenter : public MxAudioPresenter {
public:
	/**
	 * @brief [AI] Constructs and initializes the music presenter object.
	 * @details [AI] Calls Init() to establish internal state and register any required behavior.
	 */
	MxMusicPresenter();

	/**
	 * @brief [AI] Destroys the music presenter instance and unregisters from the music manager.
	 * @details [AI] Ensures proper cleanup via Destroy(TRUE).
	 */
	~MxMusicPresenter() override;

	/**
	 * @brief [AI] Returns the handler class name string for use in PresenterNameDispatch and dynamic class recognition.
	 * @details [AI] This static method enables dynamic dispatch and identification of this class's handler by name as part of the presenter instantiation system.
	 * @return Pointer to "MxMusicPresenter". [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Returns the runtime class name of the MxMusicPresenter.
	 * @details [AI] Used for dynamic identification and IsA-cascade checks.
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if this object's class matches or is derived from the specified name.
	 * @details [AI] Compares name against MxMusicPresenter and parents; enables flexible class hierarchy checks as required in some notification and sequence systems.
	 * @param p_name Name of class to check against. [AI]
	 * @return True if p_name is this class or one of its parents. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Registers this music presenter with the MxMusicManager.
	 * @details [AI] This is called by the presentation system when a music event needs to be managed (enqueued for playback etc.). Registers itself with the global music manager singleton. Called as part of stream setup.
	 * @return SUCCESS if registration is successful, FAILURE if not. [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Destroys this presenter, safely unregisters from music manager.
	 * @details [AI] Ensures that all internal data is properly destroyed and presenter is removed from relevant manager. Uses critical section for thread safety.
	 */
	void Destroy() override; // vtable+0x38

	// SYNTHETIC: LEGO1 0x100c24c0
	// MxMusicPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes all member variables and object state.
	 * @details [AI] Called from constructor and after destruction logic to reset state.
	 */
	void Init();

	/**
	 * @brief [AI] Releases all resources, unregisters from manager, and performs object cleanup.
	 * @details [AI] Depending on p_fromDestructor, may propagate destroy semantics to parent classes. Used to distinguish normal runtime destroy from destructor-level cleanup.
	 * @param p_fromDestructor True if invoked from destructor; false if directly called. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXMUSICPRESENTER_H
