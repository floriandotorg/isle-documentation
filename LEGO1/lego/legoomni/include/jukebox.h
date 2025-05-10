#ifndef JUKEBOX_H
#define JUKEBOX_H

#include "decomp.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;

/// @brief [AI] Represents the music selection state for the Jukebox in the game. Inherits from LegoState to support state saving/restoration architecture. Holds information about which song is currently selected and whether the Jukebox is active. [AI]
/// @details [AI] JukeBoxState manages which song is currently playing in the Jukebox area of the game. The state is not serializable as it is only relevant during gameplay. The Music enum identifies which track is selected. [AI]
/// @see LegoState [AI]
class JukeBoxState : public LegoState {
public:
	/// @brief [AI] Enumeration for Jukebox music tracks. Used to identify the currently selected music piece. [AI]
	enum Music {
		e_pasquell = 0, ///< [AI] "Pasquell" music track (default selection). [AI]
		e_right,        ///< [AI] "Right" music track. [AI]
		e_decal,        ///< [AI] "Decal" music track. [AI]
		e_wallis,       ///< [AI] "Wallis" music track. [AI]
		e_nelson,       ///< [AI] "Nelson" music track. [AI]
		e_torpedos      ///< [AI] "Torpedos" music track. [AI]
	};

	/// @brief [AI] Creates a new JukeBoxState with default music e_pasquell and inactive. [AI]
	JukeBoxState() : m_music(e_pasquell), m_active(FALSE) {}

	/// @brief [AI] JukeBoxState is never serialized—used only during gameplay session. [AI]
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14

	/// @brief [AI] Returns the class name "JukeBoxState" for run-time type identification. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f02bc
		return "JukeBoxState";
	}

	/// @brief [AI] Checks if the object is or derives from the class specified by p_name. [AI]
	/// @param p_name Name of class for comparison. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, JukeBoxState::ClassName()) || LegoState::IsA(p_name);
	}

	Music m_music;  ///< [AI] Currently selected music track in the Jukebox. [AI]
	MxU32 m_active; ///< [AI] Flag indicating whether the Jukebox is currently active (1=active, 0=inactive). [AI]
};

/// @brief [AI] Represents the Jukebox world environment in the game—handles display, state, notifications, player interaction, and control logic for the Jukebox area [AI]
/// @details [AI] JukeBox extends LegoWorld and implements the interactive world where the player can select different music tracks, respond to control objects, and follow transitions in and out of the Jukebox area. Maintains a pointer to the associated JukeBoxState object for music persistence within the gameplay session. [AI]
/// @see LegoWorld [AI]
class JukeBox : public LegoWorld {
public:
	/// @brief [AI] Constructs the JukeBox world instance and registers it with the notification manager for event handling. [AI]
	JukeBox();

	/// @brief [AI] Destructor. Unregisters world from all managers and releases input/camera focus if currently set. [AI]
	~JukeBox() override;

	/// @brief [AI] Handles incoming notifications (such as control input and transition events) for the Jukebox world and delegates to the appropriate handler if necessary. [AI]
	/// @param p_param Notification parameter object, must be properly cast depending on notification type. [AI]
	MxLong Notify(MxParam& p_param) override;

	/// @brief [AI] Called by the tickle manager on update/tick events; manages per-frame logic such as input disabling after transition effects. [AI]
	MxResult Tickle() override;

	/// @brief [AI] Returns TRUE indicating some special behavior (used by core engine input handling logic). [AI]
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// @brief [AI] Class identification string, used for run-time type checks. Returns "JukeBox". [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f02cc
		return "JukeBox";
	}

	/// @brief [AI] Returns true if this object is, or derives from, the class specified by p_name. [AI]
	/// @param p_name Class name to check. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, JukeBox::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// @brief [AI] Sets up world state, registers input and control handlers, and initializes camera upon entry. [AI]
	/// @param p_dsAction Action object containing parameters for world instantiation (typically from SI script system). [AI]
	/// @details [AI] Also initializes the JukeBoxState if not already persistent, and registers with TickleManager for update notifications. [AI]
	MxResult Create(MxDSAction& p_dsAction) override;

	/// @brief [AI] Finalizes world setup, including enabling presenters for the currently selected music bitmap and handling visual state. [AI]
	void ReadyWorld() override;

	/// @brief [AI] Handles request to exit the Jukebox world—sets destination for transition (will switch area on next transition event). [AI]
	/// @return [AI] Always returns TRUE to indicate escape was handled. [AI]
	MxBool Escape() override;

	/// @brief [AI] Enables or disables input/control focus for the world (and sets input manager state accordingly). [AI]
	/// @param p_enable TRUE to enable input for JukeBox, FALSE to disable. [AI]
	void Enable(MxBool p_enable) override;

private:
	/// @brief [AI] Handles specific input/control object notifications and updates music selection/presenter state accordingly. [AI]
	/// @param p_param Notification parameter carrying details about which control was activated. [AI]
	/// @return [AI] TRUE if the control was handled, FALSE otherwise. [AI]
	MxBool HandleControl(LegoControlManagerNotificationParam& p_param);

	LegoGameState::Area m_destLocation; ///< [AI] Area to transition to upon exiting the world; updated by escape or control events. [AI]
	JukeBoxState* m_state;              ///< [AI] Pointer to persistent state for the Jukebox; holds music selection and activity flags. [AI]
	undefined2 m_unk0x100;              ///< [AI] Internal state flag for post-initialization logic (used in tickle and setup). [AI]
};

#endif // JUKEBOX_H
