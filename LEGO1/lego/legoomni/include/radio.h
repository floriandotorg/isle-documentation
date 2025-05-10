#ifndef RADIO_H
#define RADIO_H

#include "legostate.h"
#include "mxcore.h"

class LegoControlManagerNotificationParam;
class MxAtomId;
class MxEndActionNotificationParam;

/// \class RadioState
/// \brief [AI] Handles and stores state for the in-game radio, including track playlists, cycling, and active status.
/// \details [AI] Three playlists are used: one for sound effects, one for dialogue, and one for radio music. The state also tracks the currently playing playlist and handles serializability and RTTI.
/// \ingroup GameState [AI]
// VTABLE: LEGO1 0x100d6d28
// VTABLE: BETA10 0x101bfb08
// SIZE 0x30
class RadioState : public LegoState {
public:
	/// \brief [AI] Constructs a new RadioState, randomizing playlist indices and initial state.
	RadioState(); // [AI]

	/// \brief [AI] Radio state is not serializable, i.e., not written to save files.
	/// \return Always FALSE [AI]
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14 [AI]

	/// \brief [AI] Returns the runtime class name for RadioState.
	const char* ClassName() const override // vtable+0x0c [AI]
	{
		// STRING: LEGO1 0x100f04f8
		return "RadioState";
	}

	/// \brief [AI] Checks if the given type name matches this class or any parent class.
	/// \param p_name Class name to check against [AI]
	/// \details [AI] Compares against RadioState's name or falls back on LegoState::IsA
	MxBool IsA(const char* p_name) const override // vtable+0x10 [AI]
	{
		return !strcmp(p_name, RadioState::ClassName()) || LegoState::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1002d020
	// RadioState::`scalar deleting destructor'

	/// \brief [AI] Indicates whether the radio is currently playing.
	MxBool IsActive() { return m_active; } // [AI]

	/// \brief [AI] Sets active status of the radio.
	/// \param p_active New active state (TRUE = playing) [AI]
	void SetActive(MxBool p_active) { m_active = p_active; } // [AI]

	/// \brief [AI] Cycles to the next playlist and returns the next object ID to play.
	/// \return MxU32 representing the next audio object to play [AI]
	undefined4 FUN_1002d090(); // [AI_SUGGESTED_NAME: GetNextPlaylistObjectId]

	/// \brief [AI] Checks if the given atom/object ID matches one of the radio's playlists.
	/// \param p_atom Atom ID (script/audio identifier) [AI]
	/// \param p_objectId Audio object ID to check [AI]
	/// \return TRUE if the object ID is in any playlist, FALSE otherwise [AI]
	MxBool FUN_1002d0c0(const MxAtomId& p_atom, MxU32 p_objectId); // [AI_SUGGESTED_NAME: ContainsObjectId]

	/// \brief [AI] Radio playlists. Each is a collection of track IDs used by the radio (effects, dialogue, music).
	Playlist m_unk0x08[3]; // 0x08 [AI_SUGGESTED_NAME: m_playlists]
	/// \brief [AI] Index for cycling among the three playlists (0-2).
	MxS16 m_unk0x2c;       // 0x2c [AI_SUGGESTED_NAME: m_currentPlaylistIndex]
	/// \brief [AI] If TRUE, the radio is playing; FALSE otherwise.
	MxBool m_active;       // 0x2e [AI]
};

/// \class Radio
/// \brief [AI] High-level manager for the in-game radio, handling notifications, playing/stopping, and state synchronization.
/// \details [AI] Listens for player interaction and game events. Orchestrates radio playback and persists state through RadioState.
/// \ingroup GameSystem [AI]
// VTABLE: LEGO1 0x100d6d10
// VTABLE: BETA10 0x101bfaf0
// SIZE 0x10
class Radio : public MxCore {
public:
	/// \brief [AI] Constructs a new Radio, registering for notifications and control events.
	Radio(); // [AI]
	/// \brief [AI] Destructor; shuts down radio playback and unregisters events.
	~Radio() override; // [AI]

	/// \brief [AI] Handles system notifications (end actions, control events) relevant to the radio.
	/// \param p_param Notification parameters [AI]
	/// \details [AI] Dispatches to control or end-action handlers as required by notification type.
	MxLong Notify(MxParam& p_param) override; // vtable+0x04 [AI]

	/// \brief [AI] Returns the runtime class name for Radio objects.
	const char* ClassName() const override // vtable+0x0c [AI]
	{
		// STRING: LEGO1 0x100f328c
		return "Radio";
	}

	/// \brief [AI] Type check for the Radio class and its ancestors.
	/// \param p_name Class to test for. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10 [AI]
	{
		return !strcmp(p_name, Radio::ClassName()) || MxCore::IsA(p_name);
	}

	/// \brief [AI] Sets radio system as enabled/disabled and resets state if changed.
	/// \param p_und If TRUE, enables; if FALSE, disables and refreshes. [AI]
	void Initialize(MxBool p_und); // [AI]

	/// \brief [AI] Creates or retrieves a RadioState object in the game state manager.
	void CreateState(); // [AI]

	/// \brief [AI] Starts playing radio music if it is not already active.
	void Play(); // [AI]

	/// \brief [AI] Stops radio playback if currently active and updates audio state.
	void Stop(); // [AI]

	/// \brief [AI] Returns the current RadioState for this radio.
	/// \return Pointer to the managed RadioState. [AI]
	RadioState* GetState() { return m_state; } // [AI]

	// SYNTHETIC: LEGO1 0x1002c970
	// Radio::`scalar deleting destructor'

private:
	/// \brief [AI] Internal: currently managed RadioState object.
	RadioState* m_state;   // 0x08 [AI]
	/// \brief [AI] Internal: If TRUE, radio system events are processed.
	MxBool m_unk0x0c;      // 0x0c [AI_SUGGESTED_NAME: m_enabled]
	/// \brief [AI] Stores previous audio enable state to restore after stopping playback.
	MxBool m_audioEnabled; // 0x0d [AI]

	/// \brief [AI] Handles notification: audio action has ended. Restarts radio if appropriate.
	/// \param p_param End-action notification parameters. [AI]
	/// \return 1 if handled/continued playback, 0 otherwise. [AI]
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param); // [AI]

	/// \brief [AI] Handles player interaction with radio controls.
	/// \param p_param Control notification parameters. [AI]
	/// \return 1 if toggled radio state, 0 otherwise. [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param); // [AI]
};

#endif // RADIO_H
