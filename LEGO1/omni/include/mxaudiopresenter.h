#ifndef MXAUDIOPRESENTER_H
#define MXAUDIOPRESENTER_H

#include "decomp.h"
#include "mxmediapresenter.h"

// VTABLE: LEGO1 0x100d4c70
// SIZE 0x54

/**
 * @brief [AI] Presents (plays/streams) audio (WAV, MID, etc.) as part of the Omni engine's media handler system.
 *        Handles runtime volume control for the currently presented audio. Used as a concrete implementation of
 *        media presentation for sound playback.
 * @details [AI] If an SI file references a media format corresponding to audio, this class is used as the handler.
 *          Volume setting is stored as an integer (0-100). Subclass of MxMediaPresenter, and supports all presenter
 *          lifecycle/tick management (ready, streaming, looping, etc.). Used both for background music and sound effects.
 */
class MxAudioPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs an audio presenter with default volume at 100%.
	 */
	MxAudioPresenter() { m_volume = 100; }

	/**
	 * @brief [AI] Returns the current runtime audio volume for this presenter (0-100).
	 * @return The current volume. [AI]
	 */
	virtual MxS32 GetVolume() { return m_volume; } // vtable+0x5c

	/**
	 * @brief [AI] Sets the presentation volume for playback (0-100).
	 * @param p_volume The desired audio volume (usually clamped between 0-100). [AI]
	 */
	virtual void SetVolume(MxS32 p_volume) { m_volume = p_volume; } // vtable+0x60

	/**
	 * @brief [AI] Returns the class handler name used for presenter type registration and lookup.
	 * @details [AI] Used by PresenterNameDispatch and other systems to dynamically select the correct presenter subclass.
	 *          Audio is identified via this handler name for association with audio media formats (WAV, MIDI, etc.).
	 * @return The class string identifier for runtime dispatch. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f078c
		return "MxAudioPresenter";
	}

	/**
	 * @brief [AI] Returns the run-time class name string. Used for IsA and class introspection.
	 * @return Pointer to string literal with the class name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if this object is or derives from the given class name.
	 * @param p_name Name of the class to compare against. [AI]
	 * @return True if the class name matches this class or a base class. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxAudioPresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

protected:
	/**
	 * @brief [AI] Current playback volume, range 0-100 (percent).
	 */
	MxS32 m_volume; // 0x50
};

// SYNTHETIC: LEGO1 0x1000d370
// MxAudioPresenter::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1000d3e0
// MxAudioPresenter::~MxAudioPresenter

#endif // MXAUDIOPRESENTER_H
