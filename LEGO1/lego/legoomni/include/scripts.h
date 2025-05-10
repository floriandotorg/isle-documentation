#ifndef SCRIPTS_H
#define SCRIPTS_H

/**
 * @file scripts.h
 * @brief [AI] Contains global script AtomId pointers and utility functions for managing script AtomIds in LEGO Island.
 * @details [AI] This header defines a set of global pointers to MxAtomId objects, each representing the unique identifier (AtomId) for a specific in-game script or SI file path. These IDs are used to refer to key game scripts, such as vehicle behavior, world locations, and special actions. Utility functions are provided to create and destroy these AtomId objects, and to access special script source names for cases like NoCD handling.
 */

class MxAtomId;

/// \name Script AtomIds
/// @{
/// @brief [AI] Global pointers to AtomIds for core script SI files used throughout the game logic.
/// @details [AI] Each variable points to an MxAtomId uniquely representing a gameplay script or SI resource file, allowing code to reference scripts efficiently using identifier objects rather than raw strings.
/// @see CreateScripts(), DestroyScripts()
extern MxAtomId* g_copterScript;       ///< [AI] Script AtomId for the helicopter ("copter") build or activity.
extern MxAtomId* g_dunecarScript;      ///< [AI] Script AtomId for the dune car building or mission script.
extern MxAtomId* g_jetskiScript;       ///< [AI] Script AtomId for the jet ski-related script.
extern MxAtomId* g_racecarScript;      ///< [AI] Script AtomId for the build/race car SI file.
extern MxAtomId* g_carraceScript;      ///< [AI] Script AtomId for the car racing event script.
extern MxAtomId* g_carracerScript;     ///< [AI] Script AtomId for the car racer entity or race logic.
extern MxAtomId* g_jetraceScript;      ///< [AI] Script AtomId for jet racing-related scripts.
extern MxAtomId* g_jetracerScript;     ///< [AI] Script AtomId for a jet racer entity or event.
extern MxAtomId* g_isleScript;         ///< [AI] Script AtomId for the main island world logic script.
extern MxAtomId* g_elevbottScript;     ///< [AI] Script AtomId for the elevator bottom script in Info Center.
extern MxAtomId* g_infodoorScript;     ///< [AI] Script AtomId for the Info Center door logic script.
extern MxAtomId* g_infomainScript;     ///< [AI] Script AtomId for the main Info Center world/event script.
extern MxAtomId* g_infoscorScript;     ///< [AI] Script AtomId for the Info Center scoring/stat script.
extern MxAtomId* g_regbookScript;      ///< [AI] Script AtomId for the registration book script (name entry).
extern MxAtomId* g_histbookScript;     ///< [AI] Script AtomId for the history book script (view records).
extern MxAtomId* g_hospitalScript;     ///< [AI] Script AtomId for the hospital SI logic.
extern MxAtomId* g_policeScript;       ///< [AI] Script AtomId for the police station script logic.
extern MxAtomId* g_garageScript;       ///< [AI] Script AtomId for the vehicle garage/world logic.
extern MxAtomId* g_act2mainScript;     ///< [AI] Script AtomId for main script of Act 2 (island event progression).
extern MxAtomId* g_act3Script;         ///< [AI] Script AtomId for Act 3 (endgame/helicopter chase) scripting.
extern MxAtomId* g_jukeboxScript;      ///< [AI] Script AtomId for the Jukebox entity/event script.
extern MxAtomId* g_pz5Script;          ///< [AI] Script AtomId for the "PZ5" activity or demo.
extern MxAtomId* g_introScript;        ///< [AI] Script AtomId for the game introduction script.
extern MxAtomId* g_testScript;         ///< [AI] Script AtomId for test SI data (used in debug/development).
extern MxAtomId* g_jukeboxwScript;     ///< [AI] Script AtomId for the JukeboxW (alternate or special jukebox) script.
extern MxAtomId* g_sndAnimScript;      ///< [AI] Script AtomId for sound animation or related cutscenes.
extern MxAtomId* g_creditsScript;      ///< [AI] Script AtomId for the credits roll logic.
extern MxAtomId* g_nocdSourceName;     ///< [AI] AtomId for the NoCD patch/script identifier used for copy protection checks.
/// @}

/**
 * @brief [AI] Allocates and initializes all global script MxAtomIds.
 * @details [AI] This function is called at startup or world reset to set up all script AtomId pointers for use in the engine. It must be called before referencing any of the global script AtomIds.
 */
void CreateScripts();

/**
 * @brief [AI] Frees and nullifies all global script AtomIds.
 * @details [AI] Cleans up the AtomId pointers created by CreateScripts(), to prevent memory leaks or dangling pointers. Should be called at shutdown/clean-up.
 */
void DestroyScripts();

/**
 * @brief [AI] Retrieves the internal string for the NoCD script source AtomId.
 * @return [AI] Pointer to the internal C-string/char* representing the SI path used for NoCD patching logic.
 * @details [AI] Use this to access the path or identifier required by NoCD logic. Returns a string managed by the AtomId object, do not free.
 */
const char* GetNoCD_SourceName();

#endif // SCRIPTS_H
