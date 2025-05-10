#ifndef INFOCENTER_H
#define INFOCENTER_H

#include "actionsfwd.h"
#include "legogamestate.h"
#include "legostate.h"
#include "legoworld.h"
#include "misc.h"
#include "mxgeometry.h"
#include "radio.h"

class MxNotificationParam;
class MxStillPresenter;
class LegoControlManagerNotificationParam;

// VTABLE: LEGO1 0x100d93a8
// VTABLE: BETA10 0x101b9b88
// SIZE 0x94
/**
 * @brief [AI] Represents the state of the Infocenter area, storing scripts, dialogue playlists and UI letter presenters.
 * @details [AI] This state class manages Infocenter-specific state, including tracked dialogue scripts for various acts, Brickster/exit dialogues, and a 7-letter list (used for player's name display/register). It also tracks an internal flag (m_unk0x74) representing a state machine, as well as presenters for UI.
 */
class InfocenterState : public LegoState {
public:
	/**
	 * @brief [AI] Constructs the InfocenterState, initializing all dialogue playlists and clearing letter pointers.
	 */
	InfocenterState();

	/**
	 * @brief [AI] Destroys the InfocenterState, cleaning up letter presenters and their associated actions.
	 */
	~InfocenterState() override;

	/**
	 * @brief [AI] Indicates the state is not serializable—InfocenterState is not saved to disk.
	 * @return Always returns FALSE [AI]
	 */
	MxBool IsSerializable() override { return FALSE; } // vtable+0x14

	/**
	 * @brief [AI] Returns the runtime class name.
	 * @return "InfocenterState" [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "InfocenterState";
	}

	/**
	 * @brief [AI] Type check for InfocenterState and base classes by name.
	 * @param p_name Name to test. [AI]
	 * @return True if @p_name is this or a parent class name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, InfocenterState::ClassName()) || LegoState::IsA(p_name);
	}

	/**
	 * @brief [AI] Returns the maximum number of letters in the UI registration name (always 7).
	 * @return Maximum length of name (7). [AI]
	 */
	MxS16 GetMaxNameLength() { return sizeOfArray(m_letters); }

	/**
	 * @brief [AI] Returns the pointer to the UI presenter for a specific letter in the name field.
	 * @param p_index Index of the letter (0-6). [AI]
	 */
	MxStillPresenter* GetNameLetter(MxS32 p_index) { return m_letters[p_index]; }

	/**
	 * @brief [AI] Sets the UI presenter for a specific name letter slot.
	 * @param p_index Index in the letters array [AI]
	 * @param p_letter Presenter to assign [AI]
	 */
	void SetNameLetter(MxS32 p_index, MxStillPresenter* p_letter) { m_letters[p_index] = p_letter; }

	/**
	 * @brief [AI] True if any letter slot is filled (indicating the player has registered).
	 * @return True if the first letter slot is not NULL. [AI]
	 */
	MxBool HasRegistered() { return m_letters[0] != NULL; }

	/**
	 * @brief [AI] Gets the next "leave" dialogue script for the current act, looping within the act's playlist.
	 * @return The next InfomainScript script for leave dialogue in current act. [AI]
	 */
	InfomainScript::Script GetNextLeaveDialogue()
	{
		return (InfomainScript::Script) m_leaveDialogue[GameState()->GetCurrentAct()].Next();
	}

	/**
	 * @brief [AI] Gets the next "return" dialogue script for the current act, looping within the act's playlist.
	 * @return The next InfomainScript script for return dialogue in current act. [AI]
	 */
	InfomainScript::Script GetNextReturnDialogue()
	{
		return (InfomainScript::Script) m_returnDialogue[GameState()->GetCurrentAct()].Next();
	}

	/**
	 * @brief [AI] Returns the exit dialogue playlist for act 1. [AI]
	 */
	Playlist& GetExitDialogueAct1() { return m_exitDialogueAct1; }

	/**
	 * @brief [AI] Returns the exit dialogue playlist for act 2 and 3. [AI]
	 */
	Playlist& GetExitDialogueAct23() { return m_exitDialogueAct23; }

	/**
	 * @brief [AI] Returns the Brickster random interjection dialogue playlist. [AI]
	 */
	Playlist& GetBricksterDialogue() { return m_bricksterDialogue; }

	// SYNTHETIC: LEGO1 0x10071900
	// InfocenterState::`scalar deleting destructor'

	/**
	 * @brief [AI] Playlist of exit dialogue scripts for Act 1. [AI]
	 */
	Playlist m_exitDialogueAct1;    // 0x08

	/**
	 * @brief [AI] Playlist of exit dialogue scripts for Act 2/3. [AI]
	 */
	Playlist m_exitDialogueAct23;   // 0x14

	/**
	 * @brief [AI] Playlists for return dialogue, one per act (indices: 0=act1, 1=act2, 2=act3). [AI]
	 */
	Playlist m_returnDialogue[3];   // 0x20

	/**
	 * @brief [AI] Playlists for leave dialogue, one per act (indices: 0=act1, 1=act2, 2=act3). [AI]
	 */
	Playlist m_leaveDialogue[3];    // 0x44

	/**
	 * @brief [AI] Playlist for Brickster special dialogue events ("heckling"). [AI]
	 */
	Playlist m_bricksterDialogue;   // 0x68

	/**
	 * @brief [AI] State machine variable tracking the Infocenter flow (e.g., 0=intro, 3=NA, 4=goto book, etc).
	 */
	MxU32 m_unk0x74;                // 0x74

	/**
	 * @brief [AI] UI presenters for each slot in the 7-letter name entry field (could be player's registered name).
	 */
	MxStillPresenter* m_letters[7]; // 0x78
};

/**
 * @brief [AI] Maps a UI region in the Infocenter to a destination presenter for glow effects.
 * @details [AI] Each map entry associates a rectangular area with a UI presenter and an integer used for internal routing/state. Used for "glow" feedback when mouse hovers or interacts with screen zones.
 *
 * SIZE 0x18
 */
struct InfocenterMapEntry {
	/**
	 * @brief [AI] Default constructor, does not initialize members. [AI]
	 */
	InfocenterMapEntry();

	/**
	 * @brief [AI] The bitmap/still presenter to enable/disable when the region is active. [AI]
	 */
	MxStillPresenter* m_destCtl; // 0x00

	/**
	 * @brief [AI] Action/group/area identifier; used for routing (e.g., 3=main, 10=boat, ...).
	 */
	undefined4 m_unk0x04;        // 0x04

	/**
	 * @brief [AI] The rectangular screen area for this map entry.
	 */
	MxRect<MxS32> m_area;        // 0x08
};

// VTABLE: LEGO1 0x100d9338
// VTABLE: BETA10 0x101b9b10
// SIZE 0x1d8
/**
 * @brief [AI] Manages Infocenter world logic, UI, cutscenes, dialogue, and area transitions.
 * @details [AI] This class represents the LEGO Island Infocenter gameplay area. It implements scene setup, manages Infocenter-specific state, handles mouse and keyboard input, dialogue scripting, character selection, registration, cutscene (movie) playback, and manages unique Infocenter UI like the name registration and "glow" highlighting of interactive areas.
 */
class Infocenter : public LegoWorld {
public:
	/**
	 * @brief [AI] Enum for cutscene (movie) types played within Infocenter.
	 * @details [AI] Used for both intro and ending movies, as well as unused types.
	 */
	enum Cutscene {
		e_noIntro = -1,         ///< [AI] Sentinel for no movie/cutscene running.
		e_legoMovie,            ///< [AI] The LEGO logo intro movie.
		e_mindscapeMovie,       ///< [AI] The Mindscape logo intro movie.
		e_introMovie,           ///< [AI] Main introduction movie.
		e_outroMovie,           ///< [AI] Generic outro (may reference any ending).
		e_badEndMovie,          ///< [AI] Bad ending cutscene.
		e_goodEndMovie          ///< [AI] Good ending cutscene.
	};

	/**
	 * @brief [AI] Enum for characters selectable in the Infocenter (i.e., for player/avatar registration).
	 */
	enum Character {
		e_noCharacter = 0,      ///< [AI] No selection.
		e_pepper,               ///< [AI] Pepper Roni.
		e_mama,                 ///< [AI] Mama Brickolini.
		e_papa,                 ///< [AI] Papa Brickolini.
		e_nick,                 ///< [AI] Nick Brick.
		e_laura                 ///< [AI] Laura Brick.
	};

	/**
	 * @brief [AI] Constructs Infocenter world, initializes state and registers for notifications.
	 */
	Infocenter();

	/**
	 * @brief [AI] Destroys Infocenter world, unregisters and cleans up all state and UI/presenters.
	 */
	~Infocenter() override;

	/**
	 * @brief [AI] Handles all notifications/events for Infocenter, routing them to specialized handlers.
	 * @param p_param The notification's parameter object. [AI]
	 * @return Event result code; may return 0, 1, or result of an inner handler. [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Advances the Infocenter tick/update logic (timers, dialogue triggers, animation triggers, etc).
	 * @return Always returns SUCCESS. [AI]
	 */
	MxResult Tickle() override;               // vtable+0x08

	/**
	 * @brief [AI] Returns the runtime class name ("Infocenter"). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "Infocenter";
	}

	/**
	 * @brief [AI] Checks whether this object or any base is of type @p_name.
	 * @param p_name Name to check [AI]
	 * @return True if the class or a parent matches the name [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Infocenter::ClassName()) || LegoWorld::IsA(p_name);
	}

	/**
	 * @brief [AI] Creates the Infocenter world and performs all Infocenter-specific setup logic.
	 * @param p_dsAction Associated DSAction. [AI]
	 * @return SUCCESS/FAILURE [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Loads initial Infocenter state and presents the background, name registration, and first dialogue/cutscene as appropriate.
	 */
	void ReadyWorld() override;                       // vtable+0x50

	/**
	 * @brief [AI] Returns TRUE unconditionally. Used for world logic consistency checks. [AI]
	 */
	MxBool VTable0x5c() override;                     // vtable+0x5c

	/**
	 * @brief [AI] Handles Escape key (or similar) logic—exits cutscenes, cancels credits, or advances dialog state.
	 * @return FALSE [AI]
	 */
	MxBool Escape() override;                         // vtable+0x64

	/**
	 * @brief [AI] Enables or disables the Infocenter world, managing input and activity appropriately.
	 * @param p_enable TRUE to enable, FALSE to disable. [AI]
	 */
	void Enable(MxBool p_enable) override;            // vtable+0x68

	// SYNTHETIC: LEGO1 0x1006ec60
	// Infocenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes all Infocenter UI bitmaps and glow information. [AI]
	 */
	void InitializeBitmaps();

	/**
	 * @brief [AI] Handles keyboard events for Infocenter (mostly registration/shortcut/skip/cutscene control).
	 * @param p_key Key code. [AI]
	 * @return Result code. [AI]
	 */
	MxLong HandleKeyPress(MxS8 p_key);

	/**
	 * @brief [AI] Handles mouse movement for dragging presenters and "glow" region highlighting.
	 * @param p_x Mouse x position. [AI]
	 * @param p_y Mouse y position. [AI]
	 * @return TRUE if handled a drag, FALSE otherwise. [AI]
	 */
	MxU8 HandleMouseMove(MxS32 p_x, MxS32 p_y);

	/**
	 * @brief [AI] Handles mouse button up (release) event; processes character drop and region activation.
	 * @param p_x Mouse x position. [AI]
	 * @param p_y Mouse y position. [AI]
	 * @return FALSE. [AI]
	 */
	MxU8 HandleButtonUp(MxS32 p_x, MxS32 p_y);

	/**
	 * @brief [AI] Handles control manager notifications (e.g. button/control press events, book click, etc).
	 * @param p_param Control notification param. [AI]
	 * @return Always 1. [AI]
	 */
	MxU8 HandleControl(LegoControlManagerNotificationParam& p_param);

	/**
	 * @brief [AI] Handles end-of-action events for Infocenter dialogs, cutscenes or mini-animations, and manages transition between Infocenter substates.
	 * @param p_param End action notification param. [AI]
	 * @return 1, or inner results depending on cutscene logic. [AI]
	 */
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/**
	 * @brief [AI] Handles generic notification type 0 (various sender-driven events, like entity activates region).
	 * @param p_param Notification parameter. [AI]
	 * @return 1. [AI]
	 */
	MxLong HandleNotification0(MxNotificationParam& p_param);

	/**
	 * @brief [AI] Updates frame/UI to highlight current actor when p_display is true. [AI]
	 * @param p_display Show or hide the highlight frame. [AI]
	 */
	void UpdateFrameHot(MxBool p_display);

	/**
	 * @brief [AI] Fully resets all Infocenter state (and other game objects) to defaults.
	 */
	void Reset();

	/**
	 * @brief [AI] Starts a cutscene (movie) for the given cutscene type, setting UI, cursor and fullscreen appropriately.
	 * @param p_entityId Enum of cutscene to play. [AI]
	 * @param p_scale Whether to scale the video full screen. [AI]
	 */
	void PlayCutscene(Cutscene p_entityId, MxBool p_scale);

	/**
	 * @brief [AI] Stops any running cutscene and restores non-movie Infocenter state/UI.
	 */
	void StopCutscene();

	/**
	 * @brief [AI] [AI_SUGGESTED_NAME: HandleGlowRegionHover] Evaluates mouse (x,y) position vs. all m_glowInfo regions, updating glowing UI and tracking hovered region index.
	 * @param p_x Mouse X. [AI]
	 * @param p_y Mouse Y. [AI]
	 */
	void FUN_10070d10(MxS32 p_x, MxS32 p_y);

	/**
	 * @brief [AI] Starts/stops the Infocenter credits sequence and associated presenters/music.
	 */
	void StartCredits();
	void StopCredits();

	/**
	 * @brief [AI] Starts a new action/dialogue using the InfomainScript scripting system.
	 * @param p_script Which InfomainScript action to run. [AI]
	 */
	void PlayAction(InfomainScript::Script p_script);

	/**
	 * @brief [AI] Stops/hides the current action/dialogue or running script associated with Infocenter.
	 */
	void StopCurrentAction();

	/**
	 * @brief [AI] Plays the animated "wiggle book" registration animation. [AI]
	 */
	void PlayBookAnimation();

	/**
	 * @brief [AI] Stops the book animation by ending/killing its running DSAction.
	 */
	void StopBookAnimation();

	/**
	 * @brief [AI] The currently playing InfomainScript in the Infocenter (used to know which dialogue is active). [AI]
	 */
	InfomainScript::Script m_currentInfomainScript; // 0xf8

	/**
	 * @brief [AI] Currently selected character (e.g. on the selection board, or for registration). [AI]
	 */
	MxS16 m_selectedCharacter;                      // 0xfc

	/**
	 * @brief [AI] Pointer to the InfocenterState object holding dialogue scripts and registration state. [AI]
	 */
	InfocenterState* m_infocenterState;             // 0x100

	/**
	 * @brief [AI] When set, destination area for world transition after Infocenter actions/registration, or e_undefined.
	 */
	LegoGameState::Area m_destLocation;             // 0x104

	/**
	 * @brief [AI] Which cutscene is currently playing (-1 if none). [AI]
	 */
	Cutscene m_currentCutscene;                     // 0x108

	/**
	 * @brief [AI] The radio jukebox/presenter UI/state (music/audio dialog interaction). [AI]
	 */
	Radio m_radio;                                  // 0x10c

	/**
	 * @brief [AI] The presenter currently being "dragged" (typically a character or registration tile), or NULL if no drag in progress. [AI]
	 */
	MxStillPresenter* m_dragPresenter;              // 0x11c

	/**
	 * @brief [AI] Interactive glow zone mapping; each entry corresponds to an interactive screen region whose bitmap is highlighted when hovered or clicked. Size 7. [AI]
	 */
	InfocenterMapEntry m_glowInfo[7];               // 0x120

	/**
	 * @brief [AI] Index of last-glowed region in m_glowInfo, or -1 if none. [AI]
	 */
	MxS16 m_unk0x1c8;                               // 0x1c8

	/**
	 * @brief [AI] Presenter for the "frame highlight" UI, which is moved to indicate selection. [AI]
	 */
	MxStillPresenter* m_frame;                      // 0x1cc

	/**
	 * @brief [AI] Timer for triggering Infoman ("info man") dialogue after a period of inactivity. [AI]
	 */
	MxS16 m_infoManDialogueTimer;                   // 0x1d0

	/**
	 * @brief [AI] Timer for triggering book animation after a period of inactivity. [AI]
	 */
	MxS16 m_bookAnimationTimer;                     // 0x1d2

	/**
	 * @brief [AI] Number of consecutive character movies to play (used when watching profile movies in sequence). [AI]
	 */
	MxU16 m_unk0x1d4;                               // 0x1d4

	/**
	 * @brief [AI] Frame timer for special glow/animation effects, e.g. animating the frame highlight for attention.
	 */
	MxS16 m_unk0x1d6;                               // 0x1d6
};

#endif // INFOCENTER_H
