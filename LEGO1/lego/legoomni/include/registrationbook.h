#ifndef REGISTRATIONBOOK_H
#define REGISTRATIONBOOK_H

#include "legoworld.h"

class InfocenterState;
class MxControlPresenter;
class MxEndActionNotificationParam;
class MxStillPresenter;
class LegoControlManagerNotificationParam;
class LegoPathStructNotificationParam;

/// @brief Derived world for handling the user registration book/infocenter name entry interface. [AI]
/// @details [AI] The RegistrationBook manages the infocenter registration book, which allows users to enter and register their name. It provides the name letter widgets, checkmark controls, handles keyboard/keypad entry, manages transitions and stores player registration information. It coordinates all UI and logic state for the registration process. [AI]
class RegistrationBook : public LegoWorld {
public:
	/// @brief Constructs a RegistrationBook and initializes UI elements and registration state. [AI]
	RegistrationBook();

	/// @brief Destructor, cleans up UI elements, surfaces, and unregisters input/control/notification. [AI]
	~RegistrationBook() override; // vtable+0x00

	/// @brief Called for notification events including actions, keypresses, controls and transitions. [AI]
	/// @param p_param Notification parameter (MxNotificationParam hierarchy) [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// @brief Per-frame tick/update handler, manages dialogue timer and checkbox blink logic. [AI]
	MxResult Tickle() override;               // vtable+0x08

	/// @brief Returns the class name string of this world ("RegistrationBook"). [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f04c8
		return "RegistrationBook";
	}

	/// @brief Tests class identity for type checking/casting. [AI]
	/// @param p_name Class name to test against [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, RegistrationBook::ClassName()) || LegoWorld::IsA(p_name);
	}

	/// @brief Handles creation/initialization logic when launched, registering to input/control and setting up state. [AI]
	/// @param p_dsAction Launch script action [AI]
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/// @brief Called to fully initialize the infocenter registration UI and player names. [AI]
	void ReadyWorld() override;                       // vtable+0x50

	/// @brief Handles player pressing Escape, cancels animation and returns to main infocenter. [AI]
	MxBool Escape() override;                         // vtable+0x64

	/// @brief Enables/disables world; updates input and UI state accordingly. [AI]
	/// @param p_enable TRUE to enable, FALSE to disable [AI]
	void Enable(MxBool p_enable) override;            // vtable+0x68

	/// @brief Helper to play script action within the regbook. [AI]
	/// @param p_objectId Object id of action to play [AI]
	inline static void PlayAction(MxU32 p_objectId);

private:
	MxS32 m_registerDialogueTimer;    ///< [AI] Last time registration dialogue was active, or sentinel value if inactive.
	undefined m_unk0xfc;              ///< [AI] Unknown, set to 1 in constructor; possibly a UI/control flag.
	undefined m_unk0xfd[3];           ///< [AI] Unknown alignment/padding or minor control state.
	MxStillPresenter* m_alphabet[26]; ///< [AI] Array of letter presenters ('A'...'Z') for constructing names.
	MxStillPresenter* m_name[10][7];  ///< [AI] 2D array: [player][letter slot], UI presenters for player names (max 10 players, 7 letters).
	struct {
		MxS16 m_letters[7];                ///< [AI] Letter indices ('A'=0...'Z'=25 or -1 for empty) for currently-entered name.
		MxS16 m_cursorPos;                 ///< [AI] Current cursor position within the 7-letter name being entered.
	} m_unk0x280;                          ///< [AI] Current input state for active registration (name/cursor buffer).

	MxControlPresenter* m_checkmark[10];   ///< [AI] Array of checkmark presenters for confirming names (1 per player slot).
	undefined2 m_unk0x2b8;                 ///< [AI] Counter/flag for registration events (controls exit transition).
	InfocenterState* m_infocenterState;    ///< [AI] Pointer to the infocenter game state for registration updates.
	undefined m_unk0x2c0;                  ///< [AI] Unknown, gameplay/transition control flag.
	undefined m_unk0x2c1;                  ///< [AI] TRUE if registration just occurred (prevents double transitions).
	undefined m_unk0x2c2[0x02];            ///< [AI] Unknown, likely padding or additional UI state.
	LPDIRECTDRAWSURFACE m_checkboxHilite;  ///< [AI] Highlighted checkbox DirectDraw surface for blinking effect.
	LPDIRECTDRAWSURFACE m_checkboxSurface; ///< [AI] Checkmark surface currently being displayed (swapped for blink).
	LPDIRECTDRAWSURFACE m_checkboxNormal;  ///< [AI] Normal, non-highlighted checkbox surface clone.

	/// @brief Handles notification that an EndAction script/media piece has completed during registration. [AI]
	/// @param p_param EndAction notification context [AI]
	/// @return Result integer to continue or halt notification propagation [AI]
	MxLong HandleEndAction(MxEndActionNotificationParam& p_param);

	/// @brief Handles keyboard key input (A-Z, Backspace, etc) for registration text entry and registration logic. [AI]
	/// @param p_key Keycode pressed [AI]
	/// @return Always 1 (event handled) [AI]
	MxLong HandleKeyPress(MxU8 p_key);

	/// @brief Handles UI control events (button clicks, on-screen keypad) for registration interaction. [AI]
	/// @param p_param Control notification context [AI]
	/// @return Always 1 (event handled) [AI]
	MxLong HandleControl(LegoControlManagerNotificationParam& p_param);

	/// @brief Handles notification involving a path structure (vehicle actor registration transition). [AI]
	/// @param p_param PathStruct notification context [AI]
	/// @return Always 1 (event handled) [AI]
	MxLong HandlePathStruct(LegoPathStructNotificationParam& p_param);

	/// @brief Handles checkmark click—completes the registration process, switches/saves or creates/selects player. [AI]
	/// @param p_playerIndex Index of the player/registration entry selected [AI]
	void FUN_100775c0(MxS16 p_playerIndex);

	/// @brief Writes the currently entered/selected letters to the infocenter state for a given player slot. [AI]
	/// @param p_user Player/user index (0 = just registered, >0 = preexisting) [AI]
	void WriteInfocenterLetters(MxS16 p_user);

	/// @brief Handles post-registration vehicle media animation and disables input while actions run. [AI]
	void FUN_100778c0();

	/// @brief Attempts to create DirectDraw surfaces and obtain checkmark UI graphics for blinking. [AI]
	/// @return TRUE if surface creation was successful, FALSE otherwise [AI]
	MxBool CreateSurface();
};

#endif // REGISTRATIONBOOK_H
