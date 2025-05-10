#ifndef MXMISC_H
#define MXMISC_H

#include "mxtypes.h"

/**
 * @class MxAtomSet
 * @brief [AI] Forward declaration for the global set storing all registered atom (string/value) pairs.
 */
class MxAtomSet; // [AI]

/**
 * @class MxDSAction
 * @brief [AI] Forward declaration for a data structure representing a queued or running script-based action.
 */
class MxDSAction; // [AI]

/**
 * @class MxEventManager
 * @brief [AI] Forward declaration for the global event manager responsible for in-game event queueing and dispatch.
 */
class MxEventManager; // [AI]

/**
 * @class MxMusicManager
 * @brief [AI] Forward declaration for the music manager controlling soundtrack playback and music resources.
 */
class MxMusicManager; // [AI]

/**
 * @class MxNotificationManager
 * @brief [AI] Forward declaration for a manager used to send or process notifications throughout the engine.
 */
class MxNotificationManager; // [AI]

/**
 * @class MxObjectFactory
 * @brief [AI] Forward declaration for the factory responsible for constructing core objects from atom or type ids.
 */
class MxObjectFactory; // [AI]

/**
 * @class MxSoundManager
 * @brief [AI] Forward declaration for the global DirectSound or software-mixer manager for sound FX and voice.
 */
class MxSoundManager; // [AI]

/**
 * @class MxStreamer
 * @brief [AI] Forward declaration for the global stream manager used for all file/media streaming operations.
 */
class MxStreamer; // [AI]

/**
 * @class MxTickleManager
 * @brief [AI] Forward declaration for the tickle manager, which schedules periodic updates on registered clients.
 */
class MxTickleManager; // [AI]

/**
 * @class MxTimer
 * @brief [AI] Forward declaration for the central timer used for measuring and providing simulation time.
 */
class MxTimer; // [AI]

/**
 * @class MxVariableTable
 * @brief [AI] Forward declaration for the global variable table (string/string), often used in scripting logic.
 */
class MxVariableTable; // [AI]

/**
 * @class MxVideoManager
 * @brief [AI] Forward declaration for the global video manager responsible for media presenter creation/setup.
 */
class MxVideoManager; // [AI]

/**
 * @brief [AI] Provides access to the global tickle manager.
 * @return Pointer to the singleton tickle manager. [AI]
 */
MxTickleManager* TickleManager(); // [AI]

/**
 * @brief [AI] Returns the global simulation timer.
 * @return Pointer to the global timer singleton. [AI]
 */
MxTimer* Timer(); // [AI]

/**
 * @brief [AI] Returns the global streamer used for all chunked media streaming (SI file, audio, etc).
 * @return Pointer to the global MxStreamer singleton. [AI]
 */
MxStreamer* Streamer(); // [AI]

/**
 * @brief [AI] Returns the global sound manager responsible for sound FX/voice playback.
 * @return Pointer to the sound manager singleton. [AI]
 */
MxSoundManager* MSoundManager(); // [AI]

/**
 * @brief [AI] Returns the variable table used for script variables and global key/value state.
 * @return Pointer to the global variable table singleton. [AI]
 */
MxVariableTable* VariableTable(); // [AI]

/**
 * @brief [AI] Returns the music manager, controlling playback of background music tracks.
 * @return Pointer to the global music manager singleton. [AI]
 */
MxMusicManager* MusicManager(); // [AI]

/**
 * @brief [AI] Returns the event manager responsible for handling event messages in the game.
 * @return Pointer to the event manager singleton. [AI]
 */
MxEventManager* EventManager(); // [AI]

/**
 * @brief [AI] Schedules and initiates execution of a script action.
 * @param p_dsAction The action object to start. [AI]
 * @return Failure/success of starting the script action. [AI]
 */
MxResult Start(MxDSAction* p_dsAction); // [AI]

/**
 * @brief [AI] Returns the notification manager for system-wide state/update notifications.
 * @return Pointer to the notification manager singleton. [AI]
 */
MxNotificationManager* NotificationManager(); // [AI]

/**
 * @brief [AI] Returns the video manager used for video/cutscene presenter management.
 * @return Pointer to the video manager singleton. [AI]
 */
MxVideoManager* MVideoManager(); // [AI]

/**
 * @brief [AI] Returns the single atom set for global registered atom/value pairs.
 * @return Pointer to the atom set singleton. [AI]
 */
MxAtomSet* AtomSet(); // [AI]

/**
 * @brief [AI] Returns the factory for creating core engine objects from atom/type ids.
 * @return Pointer to the object factory singleton. [AI]
 */
MxObjectFactory* ObjectFactory(); // [AI]

/**
 * @brief [AI] Deletes the specified action object, removing it from the global action list.
 * @param p_dsAction Reference to the action to delete. [AI]
 */
void DeleteObject(MxDSAction& p_dsAction); // [AI]

#endif // MXMISC_H
