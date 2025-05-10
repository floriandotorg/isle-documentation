#ifndef JUKEBOXENTITY_H
#define JUKEBOXENTITY_H

#include "actionsfwd.h"
#include "legoentity.h"

// VTABLE: LEGO1 0x100da8a0
// VTABLE: BETA10 0x101ba728
// SIZE 0x6c

/**
 * @brief [AI] Represents the jukebox interactive entity in LEGO Island, handling click events, background music control, and script-driven animations for the jukebox object.
 * @details [AI] Inherits from LegoEntity; gets registered for notifications by the notification manager, reacts on "click" notifications by triggering a teleport to the jukebox location and starting a mosaic transition, manages music playback based on game jukebox state, and ensures background audio is restored to the previous enabled/disabled state after actions. [AI]
 */
class JukeBoxEntity : public LegoEntity {
public:
	/**
	 * @brief [AI] Constructs the JukeBoxEntity, registering itself for notifications.
	 */
	JukeBoxEntity();
	/**
	 * @brief [AI] Destructor unregisters from the notification manager.
	 */
	~JukeBoxEntity() override; // vtable+0x00

	/**
	 * @brief [AI] Handles notification events relevant to the jukebox, e.g., click events to activate jukebox behavior.
	 * @param p_param [AI] The parameter bundle for the notification, expected to contain notification type info (cast to MxNotificationParam internally).
	 * @return [AI] 1 if the notification was handled (e.g., on click), 0 otherwise.
	 * @details [AI] On click, checks if click should be processed; if so, may make the player exit the current actor, then teleports to the correct location and triggers a screen transition. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Returns the class name of the JukeBoxEntity.
	 * @return [AI] The string "JukeBoxEntity".
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f02f0
		return "JukeBoxEntity";
	}

	/**
	 * @brief [AI] Checks whether this entity matches the given class name, including parent class checks ("IsA" hierarchy check).
	 * @param p_name [AI] Class name to compare.
	 * @return [AI] True if the class name matches JukeBoxEntity or a parent entity type.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, JukeBoxEntity::ClassName()) || LegoEntity::IsA(p_name);
	}

	/**
	 * @brief [AI] Starts the jukebox action: plays the selected music track, sets proper animation, modifies the audio manager, and updates game state for the active jukebox music.
	 * @details [AI] Looks up the current jukebox state (which track is selected) and plays/animates the appropriate song and animation sequence. Enables background audio if needed for the duration. [AI]
	 */
	void StartAction();

	/**
	 * @brief [AI] Stops the given jukebox music and resets related animation/states.
	 * @param p_script [AI] The script/music identifier to stop (from JukeboxScript).
	 * @details [AI] Deactivates jukebox state and invokes the stop animation for the selected track. Restores background audio enable state to its previous value. [AI]
	 */
	void StopAction(JukeboxScript::Script p_script);

	/**
	 * @brief [AI] Returns whether background audio was enabled before the current jukebox action.
	 * @return [AI] True if background audio was enabled before StartAction was called, false otherwise.
	 */
	MxBool IsBackgroundAudioEnabled() { return m_audioEnabled; }

	// SYNTHETIC: LEGO1 0x10085db0
	// JukeBoxEntity::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Whether background audio was enabled before this entity started its action. Used to restore the previous background audio state after stopping.
	 */
	MxBool m_audioEnabled; // 0x68
};

#endif // JUKEBOXENTITY_H