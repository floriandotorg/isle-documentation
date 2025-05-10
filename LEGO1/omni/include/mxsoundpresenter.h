#ifndef MXSOUNDPRESENTER_H
#define MXSOUNDPRESENTER_H

#include "mxaudiopresenter.h"

// VTABLE: LEGO1 0x100d4b08
// SIZE 0x54

/**
 * @brief [AI] Concrete presenter for sound playback and control within the LEGO Island engine.
 * @details [AI] MxSoundPresenter manages the lifecycle and registration of sound resources and presentations, 
 * providing integration between an audio stream (via MxAudioPresenter base) and the MxSoundManager. 
 * It ensures that sound presenters are properly registered/unregistered and initialized/destroyed, reflecting
 * correct resource handling for sound as a form of media presentation.
 */
class MxSoundPresenter : public MxAudioPresenter {
public:
	/**
	 * @brief [AI] Destructor, ensures resource release and deregisters the presenter from MxSoundManager.
	 * @details [AI] Calls Destroy(TRUE) to trigger resource cleanup, including custom teardown logic.
	 */
	~MxSoundPresenter() override { Destroy(TRUE); }

	/**
	 * @brief [AI] Public destroy method called by the engine to clean up the presenter.
	 * @details [AI] Delegates to the protected Destroy(FALSE), ensuring proper resource management
	 * when called explicitly rather than by destructor. Informs the sound manager of its removal.
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief [AI] Returns the class name of the presenter as a static string.
	 * @details [AI] Used for dynamic runtime type identification and factory pattern dispatch in the engine.
	 * @return const char* Name of the handler class type. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f07a0
		return "MxSoundPresenter";
	}

	/**
	 * @brief [AI] Returns the class name of this instance.
	 * @details [AI] Supports runtime type identification, consistent with MxMediaPresenter framework.
	 * @return const char* Name of the class ("MxSoundPresenter"). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Tests if this instance is a MxSoundPresenter or derived type.
	 * @details [AI] Performs a type check, supporting the polymorphic "IsA" idiom for object hierarchies. 
	 * Delegates up to MxAudioPresenter if no match.
	 * @param p_name Name of the class to test. [AI]
	 * @return MxBool True if this matches the requested type or any parent type. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxSoundPresenter::ClassName()) || MxAudioPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Registers this presenter with the global MxSoundManager.
	 * @details [AI] Called when the object needs to participate in system sound management.
	 * Returns SUCCESS if registration was performed, FAILURE otherwise (e.g., no sound manager).
	 * @return MxResult Operation result code (SUCCESS/FAILURE). [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	// SYNTHETIC: LEGO1 0x1000d5c0
	// MxSoundPresenter::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Handles actual teardown logic for the presenter, including deregistration from manager.
	 * @details [AI] If called from the destructor, ensures that the presenter is removed from the sound manager,
	 * and re-initializes the base presenter state. If not called from the destructor, 
	 * explicitly invokes media base class destroy, which clears/frees all associated resources.
	 * @param p_fromDestructor Flag indicating destroy reason (TRUE if called from destructor). [AI]
	 */
	void Destroy(MxBool p_fromDestructor);
};

#endif // MXSOUNDPRESENTER_H