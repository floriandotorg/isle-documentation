#ifndef LEGOGAMESTATE_H
#define LEGOGAMESTATE_H

#include "actionsfwd.h"
#include "decomp.h"
#include "mxtypes.h"
#include "mxvariable.h"

#include <string.h>

class LegoFile;
class LegoState;
class LegoStorage;
class MxVariableTable;
class MxString;

extern const char* g_actorNames[7]; ///< Array of actor names indexed by actor ID. [AI] @brief [AI]

/// @struct ColorStringStruct
/// @brief Key-value pair tying a ROI color key name to a LEGO color string. [AI]
/// Used to save and restore per-ROI color settings in save games. [AI]
struct ColorStringStruct {
	const char* m_targetName; ///< The internal ROI color key (e.g. "c_rcsidey0"). [AI] @brief [AI]
	const char* m_colorName;  ///< The LEGO color name for that part (e.g. "lego red"). [AI] @brief [AI]
};

/// @class LegoBackgroundColor
/// @brief Variable controlling the sky background color (HSV) and related light color in the game. [AI]
/// Used for both persistent and temporary background color handling. [AI]
class LegoBackgroundColor : public MxVariable {
public:
	LegoBackgroundColor();
	LegoBackgroundColor(const char* p_key, const char* p_value);

	/// @brief Sets the value of the background color using a command string.
	/// Accepts strings like "set 56 54 68" to update HSV and set sky color. [AI]
	/// @param p_colorString Color command string to parse. [AI]
	void SetValue(const char* p_colorString) override;

	/// @brief Sets the global scene light color based on RGB values. [AI]
	/// @param p_r Red value in range 0..1 [AI]
	/// @param p_g Green value in range 0..1 [AI]
	/// @param p_b Blue value in range 0..1 [AI]
	void SetLightColor(float p_r, float p_g, float p_b);

	/// @brief Sets the light color according to the current HSV parameters. [AI]
	void SetLightColor();

	/// @brief Adjusts the saturation (day/night) and updates sky color and light accordingly. [AI]
	/// @param p_sun TRUE to increase (day), FALSE to decrease (night) [AI]
	void ToggleDayNight(MxBool p_sun);

	/// @brief Rotates hue to cycle sky color (e.g. progressing through the day), updating all visuals. [AI]
	void ToggleSkyColor();

private:
	float m_h; ///< Hue value in [0,1]; user-set via variable string. [AI]
	float m_s; ///< Saturation value in [0,1]; user-set via variable string. [AI]
	float m_v; ///< Value (brightness) in [0,1]; user-set via variable string. [AI]
};

/// @class LegoFullScreenMovie
/// @brief Variable controlling full screen movie playback in the video manager. [AI]
/// Recognizes "enable"/"disable" string values. [AI]
class LegoFullScreenMovie : public MxVariable {
public:
	/// @brief Construct with variable name and value ("fsmovie", "disable"/"enable"). [AI]
	LegoFullScreenMovie(const char* p_key, const char* p_value);

	/// @brief Sets the option to enable or disable fullscreen movies. [AI]
	/// @param p_option Should be "enable" or "disable" [AI]
	void SetValue(const char* p_option) override;
};

/// @class LegoGameState
/// @brief Comprehensive persistent game state manager: handles save/load, player selection, area switching, and score history. [AI]
/// Manages most variables for current player session, stored data, background color, player info and area/act state. [AI]
class LegoGameState {
public:
	/// @enum Act
	/// @brief Indicates which main storyline section (Act 1/2/3) is currently active. [AI]
	enum Act {
		e_actNotFound = -1, ///< No act currently loaded (does not correspond to valid play). [AI]
		e_act1,             ///< Act 1: the first main segment of the game. [AI]
		e_act2,             ///< Act 2: main story segment two. [AI]
		e_act3              ///< Act 3: final main story segment. [AI]
	};

	/// @enum Area
	/// @brief Enumeration of all major in-game locations ("areas") for area/scene management and serialization. [AI]
	/// Used for switching large "world" states in engine. Some are unused/unknown. [AI]
	enum Area {
		e_undefined = 0,              ///< Undefined or unset area. [AI]
		e_previousArea = 0,           ///< Alias: go to previous area. [AI]
		e_isle,                       ///< Open world (LEGO Island main map). [AI]
		e_infomain,                   ///< Information Center, main screen. [AI]
		e_infodoor,                   ///< Info Center door/title view. [AI]
		e_unk4,                       ///< Unknown / possibly reserved. [AI]
		e_elevbott,                   ///< Elevator bottom. [AI]
		e_elevride,                   ///< Elevator ride/cab up (animated). [AI]
		e_elevride2,                  ///< Elevator ride/cab down (animated). [AI]
		e_elevopen,                   ///< Elevator doors open. [AI]
		e_seaview,                    ///< Ocean-side view at observatory. [AI]
		e_observe,                    ///< Observatory interior. [AI]
		e_elevdown,                   ///< Elevator moving down (animated). [AI]
		e_regbook,                    ///< Registration book "new game" area. [AI]
		e_infoscor,                   ///< Info Center hi-score area. [AI]
		e_jetrace,                    ///< Jetski race area, "interior"/main. [AI]
		e_jetrace2,                   ///< Jetski race (exterior). [AI]
		e_jetraceExterior,            ///< Jetski race transition? [AI]
		e_unk17,                      ///< Unknown. [AI]
		e_carrace,                    ///< Car race (track, main). [AI]
		e_carraceExterior,            ///< Car race exterior/transition. [AI]
		e_unk20,                      ///< Unknown [AI]
		e_unk21,                      ///< Unknown [AI]
		e_pizzeriaExterior,           ///< Pizzeria, seen from outside. [AI]
		e_unk23,                      ///< Unknown [AI]
		e_unk24,                      ///< Unknown [AI]
		e_garageExterior,             ///< Garage (vehicle construction) exterior. [AI]
		e_garage,                     ///< Garage (build vehicle) interior. [AI]
		e_garadoor,                   ///< Garage door or doorway. [AI]
		e_unk28,                      ///< Used for certain spawn locations. [AI]
		e_hospitalExterior,           ///< Hospital, seen from outside. [AI]
		e_hospital,                   ///< Hospital interior. [AI]
		e_unk31,                      ///< Unknown [AI]
		e_policeExterior,             ///< Police Station, from outside. [AI]
		e_unk33,                      ///< Used for certain player spawns. [AI]
		e_police,                     ///< Police Station interior. [AI]
		e_polidoor,                   ///< Police Station door. [AI]
		e_copterbuild,                ///< Vehicle construction: helicopter. [AI]
		e_dunecarbuild,               ///< Vehicle construction: dune buggy. [AI]
		e_jetskibuild,                ///< Vehicle construction: jetski. [AI]
		e_racecarbuild,               ///< Vehicle construction: racecar. [AI]
		e_unk40,                      ///< Unknown [AI]
		e_unk41,                      ///< Unknown [AI]
		e_unk42,                      ///< Unknown [AI]
		e_unk43,                      ///< Unknown [AI]
		e_unk44,                      ///< Unknown [AI]
		e_unk45,                      ///< Unknown [AI]
		e_act2main,                   ///< Act 2 world main screen. [AI]
		e_act3script,                 ///< Act 3 world/script main. [AI]
		e_unk48,                      ///< Unknown [AI]
		e_unk49,                      ///< Unknown [AI]
		e_unk50,                      ///< Unknown [AI]
		e_unk51,                      ///< Unknown [AI]
		e_unk52,                      ///< Unknown [AI]
		e_jukeboxw,                   ///< Western Jukebox (special minigame). [AI]
		e_jukeboxExterior,            ///< Jukebox, seen from outside. [AI]
		e_unk55,                      ///< Unknown [AI]
		e_histbook,                   ///< History book (scoreboard). [AI]
		e_bike,                       ///< Bike minigame (spawns). [AI]
		e_dunecar,                    ///< Dune buggy (vehicle, for spawn). [AI]
		e_motocycle,                  ///< Motorcycle (vehicle, spawn). [AI]
		e_copter,                     ///< Helicopter (vehicle, spawn). [AI]
		e_skateboard,                 ///< Skateboard (vehicle, spawn). [AI]
		e_ambulance,                  ///< Ambulance (vehicle, spawn). [AI]
		e_towtrack,                   ///< Towtruck (vehicle, spawn). [AI]
		e_jetski,                     ///< Jetski (vehicle, spawn). [AI]
		e_unk66 = 66                  ///< Used for some spawn locations. [AI]
	};

	/// @struct Username
	/// @brief Player "username", stored as 7 short integers (character codes). [AI]
	struct Username {
		Username();
		/// @brief Set this username by copying another. [AI]
		/// @param p_other Username to copy from. [AI]
		void Set(Username& p_other) { memcpy(m_letters, p_other.m_letters, sizeof(m_letters)); }

		/// @brief Reads or writes username as S16 array to/from the given storage. [AI]
		/// @param p_storage File storage manager for serialization. [AI]
		MxResult Serialize(LegoStorage* p_storage);
		/// @brief Assignment, deep-copy of letter buffer [AI]
		Username& operator=(const Username& p_other);

		MxS16 m_letters[7]; ///< Array of 7 wide characters: player name (filled by registration). [AI]
	};

	/// @struct ScoreItem
	/// @brief Single score record for a player, including high score grids for all major games. [AI]
	struct ScoreItem {
		/// @brief Reads/writes the ScoreItem to/from storage. [AI]
		/// @param p_storage Storage to read from/write to. [AI]
		MxResult Serialize(LegoStorage* p_storage);

		MxS16 m_totalScore;  ///< The total score calculated from all minigames. [AI]
		MxU8 m_scores[5][5]; ///< Scores by (minigame,row,column): custom packed format for all 5 game types. [AI]
		Username m_name;     ///< Username this score belongs to. [AI]
		MxS16 m_unk0x2a;     ///< (Purpose: Each play/attempt index?) [AI]
	};

	/// @struct History
	/// @brief Collection of best scores for all recent plays/players (high score table). [AI]
	struct History {
		History();
		/// @brief Rebuilds the high score table from current state objects, sorts it descending. [AI]
		void WriteScoreHistory();
		/// @brief Serializes whole history, including all score item slots, to the provided storage/backend. [AI]
		MxResult Serialize(LegoStorage* p_storage);
		/// @brief Looks up a score entry for player and attempt index, or returns NULL if not found. [AI]
		/// @param p_player The username to search for. [AI]
		/// @param p_unk0x24 The index (attempt/run counter). [AI]
		/// @param p_unk0x2c Receives found index or slot. [AI]
		/// @return ScoreItem for found match. [AI]
		ScoreItem* FUN_1003cc90(Username* p_player, MxS16 p_unk0x24, MxS32& p_unk0x2c);

		/// @brief Current number of score entries in the history. [AI]
		MxS16 GetCount() { return m_count; }

		/// @brief Gets pointer to score entry at index, or NULL if out of range. [AI]
		/// @param p_index Index (0-based) in the history array to get. [AI]
		ScoreItem* GetScore(MxS32 p_index) { return p_index >= m_count ? NULL : &m_scores[p_index]; }

		MxS16 m_count;          ///< Count of active/used score history entries. [AI]
		ScoreItem m_scores[20]; ///< Score history; sorted by total score descending. [AI]
		MxS16 m_unk0x372;       ///< Serial/sequence field incremented for each player. [AI]
	};

	LegoGameState();
	~LegoGameState();

	/// @brief Change the player character in the world to the given actor ID. [AI]
	/// Instantiates correct IslePathActor/setups up ROI for selected character. [AI]
	/// @param p_actorId Actor ID to set as user-controlled. [AI]
	void SetActor(MxU8 p_actorId);

	/// @brief Removes (and deletes) the current user actor from the world. [AI]
	/// Also clears actorId to 0. [AI]
	void RemoveActor();

	/// @brief Re-applies the current actor's ROI to the 3D world (remove/add for update). [AI]
	void ResetROI();

	/// @brief Saves persistent game state (world variables, actor, etc.) to a file slot. [AI]
	/// @param p_slot Save slot index. [AI]
	MxResult Save(MxULong p_slot);

	/// @brief Destroys and removes all current state objects, freeing memory and unregistering. [AI]
	MxResult DeleteState();

	/// @brief Loads persistent game state from specified save slot. [AI]
	/// @param p_slot Save slot index to load. [AI]
	MxResult Load(MxULong p_slot);

	/// @brief Serializes all player info (usernames, player count) to the appropriate storage. [AI]
	/// @param p_flags File mode flags (read/write) for the storage. [AI]
	void SerializePlayersInfo(MxS16 p_flags);

	/// @brief Adds a new player (username), moves others down, manages slot files. [AI]
	/// Truncates to 9, maintaining latest player in top slot. [AI]
	/// @param p_player Username to add. [AI]
	MxResult AddPlayer(Username& p_player);

	/// @brief Make the specified player (by ID/index) the current player. [AI]
	/// Updates slots/files, reloads, and initializes if load fails. [AI]
	/// @param p_playerId Index to switch to (0-8). [AI]
	void SwitchPlayer(MxS16 p_playerId);

	/// @brief Finds the player index for a username; returns -1 if not found. [AI]
	/// @param p_player Username to check. [AI]
	/// @return Index in m_players array, or -1. [AI]
	MxS16 FindPlayer(Username& p_player);

	/// @brief Serializes the score history table to score file. [AI]
	/// @param p_flags File mode flags (read/write) for the score file. [AI]
	void SerializeScoreHistory(MxS16 p_flags);

	/// @brief Sets the path for current save slot directory; creates a copy of input string. [AI]
	/// @param p_savePath New path for save files. [AI]
	void SetSavePath(char* p_savePath);

	/// @brief Find an existing state (LegoState-derived) object by its registered script/class name. [AI]
	/// @param p_stateName String identifying the state class. [AI]
	LegoState* GetState(const char* p_stateName);

	/// @brief Creates an instance of given state, registers it, and returns pointer. [AI]
	/// @param p_stateName Name to instantiate. [AI]
	LegoState* CreateState(const char* p_stateName);

	/// @brief Writes the full save path for the given slot to the output string object. [AI]
	/// @param p_outPath MxString to write resulting file path to. [AI]
	/// @param p_slotn Slot index (0-9). [AI]
	void GetFileSavePath(MxString* p_outPath, MxS16 p_slotn);

	/// @brief Calls cleanup logic for the specified area (removes actors, VMs, closes handles, etc.). [AI]
	/// Used when leaving an area/world. [AI]
	/// @param p_area Area to stop (see Area enum). [AI]
	void StopArea(Area p_area);

	/// @brief Switches the whole game state into a new area/world; manages transitions/scene loads. [AI]
	/// Sets camera, disables input, loads if needed. [AI]
	/// @param p_area Area to switch to. [AI]
	void SwitchArea(Area p_area);

	/// @brief Re-initializes all world/variable state to the current act's defaults. [AI]
	void Init();

	/// @brief Returns the current selected actor ID. [AI]
	MxU8 GetActorId() { return m_actorId; }

	/// @brief Returns the actor name, based on the current actor ID. [AI]
	const char* GetActorName() { return g_actorNames[GetActorId()]; }

	/// @brief Returns the active act that is currently in play. [AI]
	Act GetCurrentAct() { return m_currentAct; }

	/// @brief Returns the act that is currently loaded in memory. [AI]
	Act GetLoadedAct() { return m_loadedAct; }
	/// @brief Gets the last area before the current one. [AI]
	Area GetPreviousArea() { return m_previousArea; }
	/// @brief Gets the value of m_unk0x42c (used for act area save/load mechanics). [AI]
	Area GetUnknown0x42c() { return m_unk0x42c; }

	/// @brief Sets whether there are unsaved changes to the state. [AI]
	/// @param p_isDirty TRUE to mark save required. [AI]
	void SetDirty(MxBool p_isDirty) { m_isDirty = p_isDirty; }

	/// @brief Sets the previous area for reload/stop logic. [AI]
	/// @param p_previousArea Area to set as last. [AI]
	void SetPreviousArea(Area p_previousArea) { m_previousArea = p_previousArea; }

	/// @brief Directly sets the current actor ID (preferred: use SetActor). [AI]
	/// @param p_actorId ID to set. [AI]
	void SetActorId(MxU8 p_actorId) { m_actorId = p_actorId; }

	/// @brief Gets a pointer to a player username in the array by index. [AI]
	/// @param p_index Index into m_players. [AI]
	Username* GetPlayersIndex(MxS32 p_index) { return &m_players[p_index]; }

	/// @brief Gets the number of player slots currently used. [AI]
	MxS16 GetPlayerCount() { return m_playerCount; }

	/// @brief Gets the main background color variable object. [AI]
	LegoBackgroundColor* GetBackgroundColor() { return m_backgroundColor; }

	/// @brief Sets the current game act.
	/// @param p_currentAct The new act to set as current. [AI]
	void SetCurrentAct(Act p_currentAct);

	/// @brief Analyses the loaded Lego worlds to determine which act is present. [AI]
	void FindLoadedAct();

	/// @brief Registers a state object, replacing by class if already present. [AI]
	/// @param p_state Pointer to a LegoState to register. [AI]
	void RegisterState(LegoState* p_state);

private:
	/// @brief Writes a single named variable's value from a variable table into save storage. [AI]
	/// @param p_storage The file/storage to write into. [AI]
	/// @param p_from Variable table to read value from. [AI]
	/// @param p_variableName Name of the variable key. [AI]
	MxResult WriteVariable(LegoStorage* p_storage, MxVariableTable* p_from, const char* p_variableName);

	/// @brief Writes a sentinel/terminator for variable block in save storage. [AI]
	/// @param p_storage File/storage to write into. [AI]
	MxResult WriteEndOfVariables(LegoStorage* p_storage);

	/// @brief Reads a variable-value pair from save storage into variable table. [AI]
	/// @param p_storage File/storage to read from. [AI]
	/// @param p_to Variable table to receive value. [AI]
	MxS32 ReadVariable(LegoStorage* p_storage, MxVariableTable* p_to);

	/// @brief Initializes variable table with the default colors for ROIs/parts. [AI]
	void SetColors();

	/// @brief Installs global color override hook for custom ROI coloring. [AI]
	void SetROIColorOverride();

	// === Main persistent game state variables ===

	char* m_savePath;                           ///< Path for where save/load files are stored for this session. [AI]
	MxS16 m_stateCount;                         ///< Number of active state objects in m_stateArray. [AI]
	LegoState** m_stateArray;                   ///< Array of dynamic state objects, registered with their class names. [AI]
	MxU8 m_actorId;                             ///< Currently selected playable actor, by g_actorNames index. [AI]
	Act m_currentAct;                           ///< "Current" act set (may differ from m_loadedAct!). [AI]
	Act m_loadedAct;                            ///< Act currently in memory ("true" story act of world). [AI]
	LegoBackgroundColor* m_backgroundColor;     ///< Persistent variable object holding background color. [AI]
	LegoBackgroundColor* m_tempBackgroundColor; ///< Temporary background color object; for visual transitions. [AI]
	LegoFullScreenMovie* m_fullScreenMovie;     ///< Controls movie playback variable ("enable"/"disable"). [AI]

	// === Exposed/game-managed slots for player and area data ===

public:
	MxS16 m_unk0x24;                      ///< Serial/generation marker used for score records. [AI]
	MxS16 m_playerCount;                  ///< Number of player usernames registered. [AI]
	Username m_players[9];                ///< Array of all known player usernames (max 9, ranked). [AI]
	History m_history;                    ///< High score table/history for current game. [AI]
	undefined2 m_unk0x41a;                ///< Unknown (padding or unused). [AI]
	JukeboxScript::Script m_jukeboxMusic; ///< Which jukebox music is currently set to play. [AI]
	MxBool m_isDirty;                     ///< TRUE if unsaved changes present. [AI]
	Area m_currentArea;                   ///< Area/world the player is presently in. [AI]
	Area m_previousArea;                  ///< Where player was before last area switch. [AI]
	Area m_unk0x42c;                      ///< Used for act area storage on save/load. [AI]
};

/// @brief Helper for ROI color override mechanism, mapping special part labels to variable table values. [AI]
/// If a special "INDIR-F/G" label is passed, looks up its mapped color in the variable table.
/// @param p_input ROI part name to resolve color for. [AI]
/// @param p_output (Output) Where the resolved color will be placed, if found. [AI]
/// @param p_copyLen Maximum number of characters to copy. [AI]
/// @return TRUE if override performed, else FALSE. [AI]
MxBool ROIColorOverride(const char* p_input, char* p_output, MxU32 p_copyLen);

#endif // LEGOGAMESTATE_H
