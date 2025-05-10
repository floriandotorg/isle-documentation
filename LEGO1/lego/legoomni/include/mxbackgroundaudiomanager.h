#ifndef MXBACKGROUNDAUDIOMANAGER_H
#define MXBACKGROUNDAUDIOMANAGER_H

#include "mxcore.h"
#include "mxdsaction.h"
#include "mxpresenter.h"
#include "mxtypes.h"

class MxAudioPresenter;

/// @brief [AI] Background music manager that handles playback, volume, state transitions, and notifications for background audio tracks in the game.
///        Registers itself to the NotificationManager and TickleManager for event and periodic updates.
/// @details [AI] Responsible for handling the life cycle of background music tracks (open, play, fade, stop, destroy),
///        performing volume fades (in/out) and transitioning between background tracks as needed. Operates through
///        MxAudioPresenter objects related to current and pending audio actions.
/// @see MxAudioPresenter, MxDSAction [AI]
class MxBackgroundAudioManager : public MxCore {
public:
	/// @brief [AI] Constructs and registers the background audio manager, initializing internal state.
	MxBackgroundAudioManager();

	/// @brief [AI] Destructor unregisters from notification and tickle managers and stops any playing music.
	~MxBackgroundAudioManager() override;

	/// @brief [AI] Handles notification events such as start/stop actions relating to audio.
	/// @param p_param Notification parameter; expected to be a MxNotificationParam [AI]
	/// @returns 1 if notification was handled, 0 otherwise [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// @brief [AI] Called periodically by the tickle manager. Updates audio manager state based on current tickle state (e.g., fade in/out, streaming/repeating logic).
	/// @returns Always returns SUCCESS [AI]
	MxResult Tickle() override;               // vtable+0x08

	/// @brief [AI] Returns the class name string literal.
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f7ac4
		return "MxBackgroundAudioManager";
	}

	/// @brief [AI] Type-checks if the instance is, or inherits from, MxBackgroundAudioManager.
	/// @param p_name Name of class to check [AI]
	/// @returns True if p_name matches or is a base class [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxBackgroundAudioManager::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Returns whether background audio management is currently enabled.
	/// @returns True if manager is enabled; otherwise False [AI]
	MxBool GetEnabled() { return m_enabled; }

	/// @brief [AI] Handles incoming start action notification, sets up pending audio presenter and prepares (but does not play) a new track for fading in.
	/// @param p_param Notification parameter (MxNotificationParam expected) [AI]
	void StartAction(MxParam& p_param);

	/// @brief [AI] Handles incoming end action notification, resets state and clears finished presenters/actions; notifies game logic via Lego()->HandleEndAction().
	/// @param p_param Notification parameter [AI]
	void StopAction(MxParam& p_param);

	/// @brief [AI] Initiates playback of a new background music action with specified speed and target tickle state if possible (e.g., old music not in process).
	/// @param p_action New DS action (music track) to play [AI]
	/// @param p_speed Volume fade-in/fade-out speed [AI]
	/// @param p_tickleState Target tickle state after transition (e.g., e_streaming, e_repeating) [AI]
	/// @retval SUCCESS If the music is started [AI]
	/// @retval FAILURE Otherwise [AI]
	MxResult PlayMusic(MxDSAction& p_action, undefined4 p_speed, MxPresenter::TickleState p_tickleState);

	/// @brief [AI] Implements state update for e_streaming tickle state. Handles music track transition (fade out previous, apply new track to active slot).
	void FUN_1007ee70();

	/// @brief [AI] Handles music volume raising/lowering and track transitions in the e_repeating tickle state, implementing fade out for current and fade in for next track.
	void FUN_1007ef40();

	/// @brief [AI] Performs volume fade in/fade out logic, adjusting music volume towards target; sets tickle state to idle when target volume is reached.
	void FadeInOrFadeOut();

	/// @brief [AI] Enables or disables the background audio manager. Stops music when disabling.
	/// @param p_enable True to enable, False to disable [AI]
	void Enable(MxBool p_enable);

	/// @brief [AI] Opens the music script (SI file) for streaming and registers this background audio manager as a tickle client; used during game/scene transitions.
	/// @param p_script AtomId representing the music script to load [AI]
	/// @param p_frequencyMS Update tickle interval in milliseconds (used for registration) [AI]
	/// @returns SUCCESS if successfully opened/created, FAILURE otherwise [AI]
	virtual MxResult Create(MxAtomId& p_script, MxU32 p_frequencyMS);

	/// @brief [AI] Reinitializes manager's active presenter and tickle state; typically called at the start of a scene or audio context.
	void Init();

	/// @brief [AI] Immediately stops all background music, clears all actions and presenters, and resets tickle state.
	void Stop();

	/// @brief [AI] Requests a reduction in current background music volume, queuing for fade out (increments suppression counter). Initiates fade if not already started.
	void LowerVolume();

	/// @brief [AI] Requests that the background music volume is raised (decrements suppression counter); triggers fade-in if suppression goes to zero.
	void RaiseVolume();

	/// @brief [AI] Helper for queued volume changing: Sets up a coming presenter/action for activation with given speed and tickle state.
	/// @param p_unk0x138 Presenter pending activation [AI_SUGGESTED_NAME: p_audioPresenter]
	/// @param p_speed Speed for fade in/out [AI]
	/// @param p_tickleState Tickle state for the transition [AI]
	/// @returns Unused, always 0 [AI]
	undefined4 FUN_1007f610(MxPresenter* p_unk0x138, MxS32 p_speed, MxPresenter::TickleState p_tickleState);

	// SYNTHETIC: LEGO1 0x1007ec00
	// MxBackgroundAudioManager::`scalar deleting destructor'

private:
	/// @brief [AI] Opens (loads/streams) the given music script by AtomId, destroying previous music instance if any. Updates internal script marker.
	/// @param p_script AtomId for script to load/open [AI]
	/// @returns SUCCESS if opened successfully, FAILURE otherwise [AI]
	MxResult OpenMusic(MxAtomId& p_script);

	/// @brief [AI] Closes and destroys any currently active music action/session and unregisters resources. Resets enabled state. No-op if no script loaded.
	void DestroyMusic();

	/// @brief [AI] True if background audio management and music playback is enabled. Controls PlayMusic and Stop behavior.
	MxBool m_enabled;             // 0x08

	/// @brief [AI] Information about the currently active (playing) DSAction (music track).
	MxDSAction m_action1;         // 0x0c

	/// @brief [AI] Currently active MxAudioPresenter, handling real-time audio playback for the active music. 
	MxAudioPresenter* m_unk0xa0;  // 0xa0 [AI_SUGGESTED_NAME: m_activePresenter]

	/// @brief [AI] Queued MxDSAction information for an upcoming (pending) background music track.
	MxDSAction m_action2;         // 0xa4

	/// @brief [AI] Presenter for the queued music track (pending activation).
	MxAudioPresenter* m_unk0x138; // 0x138 [AI_SUGGESTED_NAME: m_pendingPresenter]

	/// @brief [AI] Current tickle state, determines if music is fading in, streaming, repeating, or idle.
	MxPresenter::TickleState m_tickleState; // 0x13c

	/// @brief [AI] Current fade in/out speed for adjusting volume dynamically.
	MxS32 m_speed; // 0x140

	/// @brief [AI] Target volume for currently playing/pending background music. Used for fade logic.
	MxS32 m_targetVolume; // 0x144

	/// @brief [AI] Counter used to stack multiple requests for volume suppression (e.g., to allow multiple LowerVolume calls before restoring volume with RaiseVolume).
	MxS16 m_unk0x148;     // 0x148 [AI_SUGGESTED_NAME: m_volumeSuppressCount]

	/// @brief [AI] AtomId of the currently open music script (SI file). Used to manage the loaded audio resource.
	MxAtomId m_script;    // 0x14c
};

#endif // MXBACKGROUNDAUDIOMANAGER_H
