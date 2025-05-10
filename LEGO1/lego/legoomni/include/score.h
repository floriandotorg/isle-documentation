#ifndef SCORE_H
#define SCORE_H

#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"

class LegoControlManagerNotificationParam;
class MxEndActionNotificationParam;

/// \class ScoreState
/// \brief [AI] State object used to track the status of the Score/High Score area, particularly whether the educational "cube" tutorial should be shown to the player.
/// \details [AI] ScoreState is a game state associated with the InfoScore/High Score room/area. It currently holds only one property: whether the cube tutorial should be played. This flag is used to determine if the "bigcube.gif" tutorial audio should play when entering the score area. Inherits from LegoState to allow serialization and integration with the game's state system.
/// \sa LegoState [AI]
class ScoreState : public LegoState {
public:
	/// \brief [AI] Constructor initializes the tutorial flag to TRUE by default.
	ScoreState() : m_playCubeTutorial(TRUE) {}

	/// \brief [AI] Indicates whether this state can be serialized for savegames. Always returns FALSE.
	/// \return [AI] FALSE.
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14

	/// \brief [AI] Resets the ScoreState by re-enabling the tutorial.
	/// \return [AI] TRUE.
	MxBool Reset() override
	{
		m_playCubeTutorial = TRUE;
		return TRUE;
	} // vtable+0x18

	/// \brief [AI] Returns the class name as a string.
	/// \return [AI] "ScoreState"
	const char* ClassName() const override // vtable+0x0c
	{
		return "ScoreState";
	}

	/// \brief [AI] Checks if this object is the given class or any of its base classes.
	/// \param p_name [AI] The name of the class to check.
	/// \return [AI] TRUE if p_name matches ScoreState or any base class, FALSE otherwise.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ScoreState::ClassName()) || LegoState::IsA(p_name);
	}

	/// \brief [AI] Get whether the high score cube tutorial should be played.
	/// \return [AI] TRUE if the tutorial is pending playback; FALSE otherwise.
	MxBool GetTutorialFlag() { return m_playCubeTutorial; }

	/// \brief [AI] Set whether the high score cube tutorial should be played.
	/// \param p_playCubeTutorial [AI] Set TRUE to show tutorial, FALSE to skip.
	void SetTutorialFlag(MxBool p_playCubeTutorial) { m_playCubeTutorial = p_playCubeTutorial; }

	/// \brief [AI] Whether the cube tutorial should be played when entering the Score/High Score area.
	MxBool m_playCubeTutorial; // 0x08

	// SYNTHETIC: LEGO1 0x1000df00
	// ScoreState::`scalar deleting destructor'
};

/// \class Score
/// \brief [AI] Implements the InfoScore/High Score game world/area, including score table display and handling user actions to transition to other areas.
/// \details [AI] Score manages the logic behind the high score table (“bigcube.gif”) display, responds to notifications from input and actions, paints actual scores for players, and manages transitions to/from the InfoScore area. It interacts with InfoScore scripts to animate or play audio, and tracks the "destination" (where the player is going next via arrows/doors). Inherits from LegoWorld for in-game area functionality.
/// \sa LegoWorld [AI]
class Score : public LegoWorld {
public:
	/// \brief [AI] Constructor initializes destination location and registers Score for notifications.
	Score();

	/// \brief [AI] Destructor unregisters Score from managers and performs cleanup.
	~Score() override;

	/// \brief [AI] Handles incoming notifications, including control and action completion, and manages state transitions and events in the score area.
	/// \param p_param [AI] Reference to a notification parameter object.
	/// \return [AI] Notification handling result (varies by event type).
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Returns TRUE, indicating this world supports whatever subsystem the vtable+0x5c is checking for (possibly always visible/active).
	MxBool VTable0x5c() override { return TRUE; } // vtable+0x5c

	/// \brief [AI] Returns the class name.
	/// \return [AI] "Score"
	const char* ClassName() const override // vtable+0x0c
	{
		return "Score";
	}

	/// \brief [AI] Checks if this object is an instance of Score or its base type.
	/// \param p_name [AI] The class name to check.
	/// \return [AI] TRUE if p_name matches Score or any base class, FALSE otherwise.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Score::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// \brief [AI] Creates and initializes the Score world with the specified DS action.
	/// \param p_dsAction [AI] The data structure action controlling area logic.
	/// \return [AI] Result of world creation.
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// \brief [AI] Called when the world is ready to be started (usually upon area entry); triggers the correct animations and cube score updates, and plays the tutorial or music.
	void ReadyWorld() override;                       // vtable+0x50

	/// \brief [AI] Called when the player is attempting to “escape” (exit) the InfoScore area; deletes script actions and sets the next world.
	/// \return [AI] TRUE if successful.
	MxBool Escape() override;                         // vtable+0x64

	/// \brief [AI] Called to enable or disable this world, hooking up input as needed.
	/// \param p_enable [AI] TRUE to enable (focus/gain control), FALSE to disable.
	void Enable(MxBool p_enable) override;            // vtable+0x68
	
	/// \brief [AI] Paints the current score cube with the high scores for each activity and actor.
	void Paint();

	/// \brief [AI] Handles notification of a completed action (like an InfoScore script finishing).
	/// \param p_param [AI] Notification structure with completed action information.
	/// \return [AI] Always 1.
	MxLong FUN_10001510(MxEndActionNotificationParam& p_param);

	/// \brief [AI] Handles user input/control interaction (button/cube click) in the InfoScore area, including navigation arrows, books, or score boxes.
	/// \param p_param [AI] Notification parameter structure for control input.
	/// \return [AI] Always 1.
	MxLong FUN_100016d0(LegoControlManagerNotificationParam& p_param);

	/// \brief [AI] Helper for painting – fills the correct high score colored area for an activity/actor pair on the score table graphic.
	/// \param i_activity [AI] Activity index (0 = car race, 1 = jetski, 2 = pizza, 3 = tow truck, 4 = ambulance).
	/// \param i_actor [AI] Slot for which actor/player (0..4).
	/// \param score [AI] Score index (0 = lowest to 3 = best/perfect).
	void FillArea(MxS32 i_activity, MxS32 i_actor, MxS16 score);

protected:
	/// \brief [AI] Cancels the tutorial script playback if still running and disables further tutorials for this session.
	void DeleteScript();

	/// \brief [AI] Area/room to switch to after leaving Score (set when the user clicks navigation arrows/books/etc).
	LegoGameState::Area m_destLocation; // 0xf8

	/// \brief [AI] Pointer to the current ScoreState for this world's area/session.
	ScoreState* m_state;                // 0xfc

	/// \brief [AI] Raw surface data pointer for direct pixel manipulation (locked during Paint(); NULL otherwise). Used for writing scores onto the cube texture.
	MxU8* m_surface;                    // 0x100

	// SYNTHETIC: LEGO1 0x100011e0
	// Score::`scalar deleting destructor'
};

#endif // SCORE_H
