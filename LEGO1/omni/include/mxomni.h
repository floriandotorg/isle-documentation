#ifndef MXOMNI_H
#define MXOMNI_H

#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxstring.h"

class MxAtomSet;
class MxDSAction;
class MxEntity;
class MxEventManager;
class MxMusicManager;
class MxNotificationManager;
class MxNotificationParam;
class MxObjectFactory;
class MxOmniCreateParam;
class MxPresenter;
class MxSoundManager;
class MxStreamer;
class MxStreamController;
class MxTickleManager;
class MxTimer;
class MxVariableTable;
class MxVideoManager;

// VTABLE: LEGO1 0x100dc168
// SIZE 0x68
/**
 * @brief [AI] Central subsystem coordinator and singleton of the LEGO Island engine. Instantiated once in the process, this class manages all major subsystems such as resource streaming, variable tables, notification dispatch, media managers (sound/video/music), and event/timer systems. Also used for creation of subsystem objects and engine handling. Provides utility access to hardware paths and configuration (CD, HD, 3D sound).
 * @details [AI] Inherits from MxCore and is responsible for all high-level coordinated initialization, startup sequencing of media/actions, and teardown/cleanup of the game application. Patterned as an engine-wide singleton.
 */
class MxOmni : public MxCore {
public:
	/**
	 * @brief [AI] Destroys the singleton MxOmni instance and performs memory cleanup. Should be called before application exit.
	 */
	static void DestroyInstance();

	/**
	 * @brief [AI] Retrieves the configured CD-ROM media path string used for resource location.
	 * @return Pointer to a string containing the path to CD media. [AI]
	 */
	static const char* GetCD();

	/**
	 * @brief [AI] Retrieves the configured hard disk media path string used for resource location.
	 * @return Pointer to a string containing the path to the HD media. [AI]
	 */
	static const char* GetHD();

	/**
	 * @brief [AI] Returns the singleton instance of the MxOmni subsystem coordinator.
	 * @return Pointer to the global engine singleton. [AI]
	 */
	static MxOmni* GetInstance();

	/**
	 * @brief [AI] Returns current state of 3D sound configuration.
	 * @return TRUE if 3D sound output should be used; FALSE otherwise. [AI]
	 */
	static MxBool IsSound3D();

	/**
	 * @brief [AI] Sets the global CD media path used for source file lookup.
	 * @param p_cd The new CD path to use for resource access. [AI]
	 */
	static void SetCD(const char* p_cd);

	/**
	 * @brief [AI] Sets the global hard disk media path used for resource lookup.
	 * @param p_hd The new HD path to use for resource access. [AI]
	 */
	static void SetHD(const char* p_hd);

	/**
	 * @brief [AI] Enables or disables use of 3D sound processing.
	 * @param p_use3dSound Set TRUE to enable 3D sound, FALSE otherwise. [AI]
	 */
	static void SetSound3D(MxBool p_use3dSound);

	/**
	 * @brief [AI] Initializes default state. Does not create or allocate any subsystems. [AI]
	 */
	MxOmni();

	/**
	 * @brief [AI] Destroys all subsystems and releases memory/resources. [AI]
	 */
	~MxOmni() override;

	/**
	 * @brief [AI] Handles global notifications. Handles c_notificationEndAction and delegates to HandleEndAction.
	 * @param p_param Incoming notification/parameter. [AI]
	 * @return 1 if handled (end action), else 0. [AI]
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief [AI] Resets all internal pointers to defaults. Subsystem pointers are set to NULL. Window handle and paused state reset.
	 */
	virtual void Init();

	/**
	 * @brief [AI] Allocates and configures engine subsystems, depending on the provided flags in MxOmniCreateParam. Handles creation of atom set, object factory, variable table, media managers, notification/event/timer/tickle/streamer subsystems as requested.
	 * @param p_param Configuration describing which subsystems to create. [AI]
	 * @return SUCCESS if all requested subsystems are created and initialized, otherwise FAILURE. [AI]
	 */
	virtual MxResult Create(MxOmniCreateParam& p_param);

	/**
	 * @brief [AI] Tears down all engine subsystems, deletes and frees all managed memory. Also performs world object destruction. [AI]
	 */
	virtual void Destroy();

	/**
	 * @brief [AI] Requests the start of a top-level scripted action (from SI). Triggers sequence execution for streaming/media/subsystems as required by the action, via streamer.
	 * @param p_dsAction The action object (parsed from SI) to be started. [AI]
	 * @return SUCCESS if streaming was successfully initiated, FAILURE if requirements not met or error occurred. [AI]
	 */
	virtual MxResult Start(MxDSAction* p_dsAction);

	/**
	 * @brief [AI] Deletes a world or subsystem object corresponding to an action. Notifies streamer to unregister and clean up streaming resources associated with the action.
	 * @param p_dsAction The action whose resources/object should be deleted. [AI]
	 */
	virtual void DeleteObject(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Checks whether an entity (gameplay object) exists by querying the streamer and notification manager.
	 * @param p_dsAction The action referencing the entity (usually by ID or AtomID). [AI]
	 * @return TRUE if entity exists and no queued notifications for deletion remain, FALSE otherwise. [AI]
	 */
	virtual MxBool DoesEntityExist(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Instantiates and starts a Presenter (e.g., video, sound, animation) to handle the specified action on the given stream controller. Name-dispatches to correct presenter type based on action format.
	 * @param p_controller Stream controller managing the resource/media. [AI]
	 * @param p_action Action specifying presenter type and parameters. [AI]
	 * @return SUCCESS if presenter was created, manager notification dispatched, and start succeeded. FAILURE otherwise. [AI]
	 */
	virtual MxResult CreatePresenter(MxStreamController* p_controller, MxDSAction& p_action);

	/**
	 * @brief [AI] [VIRTUAL BASE] Placeholder virtual for derived engines to instantiate an entity and add to the 3D world. Not implemented in base class.
	 * @param [unused] [description unavailable] [AI]
	 * @param [unused] [description unavailable] [AI]
	 * @param [unused] [description unavailable] [AI]
	 * @return NULL by default. [AI]
	 */
	virtual MxEntity* AddToWorld(const char*, MxS32, MxPresenter*);

	/**
	 * @brief [AI] [VIRTUAL BASE] Placeholder for derived implementations—sends a notification to the currently active entity. Not implemented in base. [AI]
	 * @param p_param Notification parameters to send. [AI]
	 */
	virtual void NotifyCurrentEntity(const MxNotificationParam& p_param);

	/**
	 * @brief [AI] Pauses subsystems that support pausing (timer, sound manager) and sets paused state.
	 */
	virtual void Pause();

	/**
	 * @brief [AI] Resumes paused subsystems (timer, sound manager) and clears paused state.
	 */
	virtual void Resume();

	/**
	 * @brief [AI] Returns paused state of the engine. [AI]
	 * @return True if the engine is currently paused, false otherwise. [AI]
	 */
	virtual MxBool IsPaused() { return m_paused; }

	/**
	 * @brief [AI] Manually set the static instance of the global engine object.
	 * @param p_instance The new instance pointer. [AI]
	 */
	static void SetInstance(MxOmni* p_instance);

	/**
	 * @brief [AI] Recursive walk to check if the given action, or any child multi-action, was sourced from the provided name.
	 * @param p_action The top-level or nested action to check (may be multi-action). [AI]
	 * @param p_name The name/string to compare as action source. [AI]
	 * @return TRUE if found, FALSE otherwise. [AI]
	 */
	static MxBool ActionSourceEquals(MxDSAction* p_action, const char* p_name);

	/**
	 * @brief [AI] Gets the window handle (HWND) associated with the engine (ownership not transferred).
	 * @return Window handle. [AI]
	 */
	HWND GetWindowHandle() const { return this->m_windowHandle; }

	/**
	 * @brief [AI] Retrieves the currently used object factory for presenter/entity instantiation (ownership not transferred).
	 * @return Pointer to global object factory. [AI]
	 */
	MxObjectFactory* GetObjectFactory() const { return this->m_objectFactory; }

	/**
	 * @brief [AI] Returns the notification manager responsible for enqueuing and dispatching notifications/events.
	 * @return Notification manager. [AI]
	 */
	MxNotificationManager* GetNotificationManager() const { return this->m_notificationManager; }

	/**
	 * @brief [AI] Returns the tickle manager which manages the tickle update loop for registered clients.
	 * @return Pointer to tickle manager. [AI]
	 */
	MxTickleManager* GetTickleManager() const { return this->m_tickleManager; }

	/**
	 * @brief [AI] Gets the main frame-timer object (if any).
	 * @return Pointer to engine timer. [AI]
	 */
	MxTimer* GetTimer() const { return this->m_timer; }

	/**
	 * @brief [AI] Returns the engine's global streamer object for media/data access.
	 * @return Pointer to streamer subsystem. [AI]
	 */
	MxStreamer* GetStreamer() const { return this->m_streamer; }

	/**
	 * @brief [AI] Gets the engine's sound manager used for playing/controlling sounds.
	 * @return Sound manager object. [AI]
	 */
	MxSoundManager* GetSoundManager() const { return this->m_soundManager; }

	/**
	 * @brief [AI] Returns the video media manager (for handling FLC/SMK/etc.), if present.
	 * @return Video manager instance. [AI]
	 */
	MxVideoManager* GetVideoManager() const { return this->m_videoManager; }

	/**
	 * @brief [AI] Gets the global variable table for scripting/logic purposes.
	 * @return The variable table used for storing game variables/values. [AI]
	 */
	MxVariableTable* GetVariableTable() const { return this->m_variableTable; }

	/**
	 * @brief [AI] Returns the current music manager, responsible for background/interactive music.
	 * @return Pointer to music manager. [AI]
	 */
	MxMusicManager* GetMusicManager() const { return this->m_musicManager; }

	/**
	 * @brief [AI] Get the event manager responsible for handling event queueing/dispatching.
	 * @return Pointer to event manager. [AI]
	 */
	MxEventManager* GetEventManager() const { return this->m_eventManager; }

	/**
	 * @brief [AI] Gets the atom set used for mapping strings/IDs to atom objects.
	 * @return Pointer to the atom set. [AI]
	 */
	MxAtomSet* GetAtomSet() const { return this->m_atomSet; }

	/**
	 * @brief [AI] Handles the engine's response to action end notifications (c_notificationEndAction), deletes action objects as necessary and manages streamer state.
	 * @param p_param End action notification parameter. [AI]
	 * @return Always 1 to acknowledge handling. [AI]
	 */
	MxLong HandleEndAction(MxParam& p_param);

	// SYNTHETIC: LEGO1 0x100aefd0
	// MxOmni::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] The singleton instance pointer of the MxOmni engine. [AI]
	 */
	static MxOmni* g_instance;

	/**
	 * @brief [AI] Path to media assets (SI files, resources) used for loading content. [AI]
	 */
	MxString m_mediaPath;                         // 0x08

	/**
	 * @brief [AI] Associated window handle for DirectX/Win32 operations. [AI]
	 */
	HWND m_windowHandle;                          // 0x18

	/**
	 * @brief [AI] Factory object used to instantiate engine objects (presenters, entities) by class name. [AI]
	 */
	MxObjectFactory* m_objectFactory;             // 0x1c

	/**
	 * @brief [AI] Variable table for scripting/in-engine variable storage. [AI]
	 */
	MxVariableTable* m_variableTable;             // 0x20

	/**
	 * @brief [AI] Manages list of objects requiring tickle updates each frame/step. [AI]
	 */
	MxTickleManager* m_tickleManager;             // 0x24

	/**
	 * @brief [AI] Manages notifications and their distribution to interested clients. [AI]
	 */
	MxNotificationManager* m_notificationManager; // 0x28

	/**
	 * @brief [AI] Manager for decoding and rendering video resources (FLC, etc.). [AI]
	 */
	MxVideoManager* m_videoManager;               // 0x2c

	/**
	 * @brief [AI] Manages sound (WAV, MIDI) output and channels. [AI]
	 */
	MxSoundManager* m_soundManager;               // 0x30

	/**
	 * @brief [AI] Manages background and event-triggered music. [AI]
	 */
	MxMusicManager* m_musicManager;               // 0x34

	/**
	 * @brief [AI] Centralized event manager for engine events (scripted/game logic). [AI]
	 */
	MxEventManager* m_eventManager;               // 0x38

	/**
	 * @brief [AI] Master timer for time-keeping and scheduling. [AI]
	 */
	MxTimer* m_timer;                             // 0x3c

	/**
	 * @brief [AI] Main streamer for handling open files and distributed streaming. [AI]
	 */
	MxStreamer* m_streamer;                       // 0x40

	/**
	 * @brief [AI] Global set of strings mapped to atom objects (for fast lookup/id assignment). [AI]
	 */
	MxAtomSet* m_atomSet;                         // 0x44

	/**
	 * @brief [AI] Critical section used for thread-safe engine operations. [AI]
	 */
	MxCriticalSection m_criticalSection;          // 0x48

	/**
	 * @brief [AI] Indicates if the engine/systems are currently paused. [AI]
	 */
	MxBool m_paused;                              // 0x64
};

#endif // MXOMNI_H
