#ifndef HISTORYBOOK_H
#define HISTORYBOOK_H

#include "decomp.h"
#include "legogamestate.h"
#include "legoworld.h"

class MxStillPresenter;

// VTABLE: LEGO1 0x100da328
// VTABLE: BETA10 0x101b99b0
// SIZE 0x3e4
/**
 * @brief [AI] The HistoryBook class represents the "History Book" world/scene shown in LEGO Island, displaying name, letter and score history. It is responsible for visualizing previous play sessions, rendering the player's names as colored bitmap letters and displaying scores. Inherits common world behavior from LegoWorld.
 * @details [AI] Implements the transition from the history book screen to other areas (such as Information Center or Info Score screen), manages drawing letter bitmaps for player names and the score grids, and responds to user input events (buttons, escape, notifications).
 */
class HistoryBook : public LegoWorld {
public:
	/**
	 * @brief [AI] Constructor for HistoryBook. Initializes member arrays for alphabet bitmaps, per-entry name/score presenters, registers for notifications.
	 */
	HistoryBook();

	/**
	 * @brief [AI] Destructor for HistoryBook. Cleans up all allocated presenters and unregisters input/notification/control.
	 */
	~HistoryBook() override; // vtable+0x00

	/**
	 * @brief [AI] Notification handler processing game events for this world, such as button presses and transitions.
	 * @param p_param [AI] A reference to the parameter object describing the notification event, expected to be a MxNotificationParam.
	 * @return [AI]
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Get the class name string ("HistoryBook").
	 * @return [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f04bc
		return "HistoryBook";
	}

	/**
	 * @brief [AI] Type check for "HistoryBook" class or parent types.
	 * @param p_name [AI] The class name to check for.
	 * @return [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, HistoryBook::ClassName()) || LegoWorld::IsA(p_name);
	}

	/**
	 * @brief [AI] Sets up the world based on the provided action, registers for input/control, and enters the history book area in the game state.
	 * @param p_dsAction [AI] Description of the data source action initializing this world.
	 * @return [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Prepares the HistoryBook for display, populates bitmap presenters with alphabet letters, names and scores, and updates game state. Called before the world is shown.
	 */
	void ReadyWorld() override;                       // vtable+0x50

	/**
	 * @brief [AI] Handles Escape key/input, setting the world to transition to the Info Main area.
	 * @return [AI]
	 */
	MxBool Escape() override;                         // vtable+0x64

	// SYNTHETIC: LEGO1 0x100824b0
	// HistoryBook::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] The destination area/location to switch to when user triggers a world change (e.g., Info Score or Info Main).
	 */
	LegoGameState::Area m_destLocation; // 0xf8

	/**
	 * @brief [AI] Array of presenter pointers for the 26 alphabet bitmaps, used to draw colored letters for player names.
	 *
	 * Each entry corresponds to 'A'..'Z' (0 = 'A', 25 = 'Z').
	 */
	MxStillPresenter* m_alphabet[26];   // 0xfc

	/**
	 * @brief [AI] 2D array of bitmap presenters for each letter of up to 20 player names, with up to 7 letters per name.
	 *
	 * Each m_name[i][j] is the j-th letter bitmap in the i-th name slot for the history table.
	 *
	 * Variable name verified by BETA10 0x1002bd27.
	 */
	MxStillPresenter* m_name[20][7]; // 0x164

	/**
	 * @brief [AI] Array of presenter pointers for up to 20 score boxes (each representing a play session's score breakdown).
	 */
	MxStillPresenter* m_scores[20]; // 0x394
};

#endif // HISTORYBOOK_H
