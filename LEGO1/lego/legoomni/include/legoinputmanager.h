#ifndef LEGOINPUTMANAGER_H
#define LEGOINPUTMANAGER_H

#include "decomp.h"
#include "legoeventnotificationparam.h"
#include "mxlist.h"
#include "mxpresenter.h"
#include "mxqueue.h"

#include <dinput.h>

class LegoCameraController;
class LegoControlManager;
class LegoWorld;

extern MxS32 g_unk0x100f31b0; ///< [AI] Global variable used for tracking drag state, -1 if inactive. [AI]
extern const char* g_unk0x100f31b4; ///< [AI] Global pointer for additional drag state/context (purpose unclear). [AI]

//! [AI] Event queue for processing Lego input (mouse/keyboard/joystick) events.
//! Used to enqueue and process input events in FIFO order.
class LegoEventQueue : public MxQueue<LegoEventNotificationParam> {}; ///< [AI] Queue of input events. [AI]

//! [AI] A list of notification targets (MxCore*) interested in input events (primarily keyboard).
class LegoNotifyList : public MxPtrList<MxCore> {
protected:
	//! [AI] Compare two notification MxCore* elements for list ordering (by pointer value).
	//! @param p_element1 First core pointer to compare [AI]
	//! @param p_element2 Second core pointer to compare [AI]
	//! @return 0 if equal, -1 if p_element1 < p_element2, 1 otherwise [AI]
	MxS8 Compare(MxCore* p_element1, MxCore* p_element2) override
	{
		return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1;
	} // vtable+0x14

public:
	//! [AI] Construct with ownership flag determining if contained pointers should be deleted on destruction. [AI]
	LegoNotifyList(MxBool p_ownership = FALSE) : MxPtrList<MxCore>(p_ownership) {}
};

//! [AI] Cursor (iterator) for traversing a LegoNotifyList.  Used to find or detach notification targets. [AI]
class LegoNotifyListCursor : public MxPtrListCursor<MxCore> {
public:
	//! [AI] Construct given a LegoNotifyList.
	//! @param p_list The notification list to iterate [AI]
	LegoNotifyListCursor(LegoNotifyList* p_list) : MxPtrListCursor<MxCore>(p_list) {}
};


//! [AI] Handles keyboard, mouse, and joystick input for the game.
//!
//! Central input system that tracks platform input devices and manages event notification and processing.
//! Responsible for processing DirectInput keyboard events, Windows joystick input, and mouse events.
//!
//! Registers and notifies listeners of key/button/mouse actions, manages drag/timing logic, and interacts with
//! camera and world objects to impart navigation and click/drag operations. Controls input availability/focus
//! and their event flows. [AI]
class LegoInputManager : public MxPresenter {
public:

	//! [AI] Key flags for common navigation keys and bitwise combinations used for state queries.
	enum Keys {
		c_left = 0x01,        ///< [AI] Left arrow key or equivalent key [AI]
		c_right = 0x02,       ///< [AI] Right arrow key or equivalent key [AI]
		c_up = 0x04,          ///< [AI] Up arrow key or equivalent key [AI]
		c_down = 0x08,        ///< [AI] Down arrow key or equivalent key [AI]
		c_ctrl = 0x10,        ///< [AI] Control key [AI]
		c_leftOrRight = c_left | c_right, ///< [AI] Combo: left or right arrow [AI]
		c_upOrDown   = c_up | c_down      ///< [AI] Combo: up or down arrow [AI]
	};

	//! [AI] Initialize default state: input device handles, notification lists, and member flags. [AI]
	LegoInputManager();

	//! [AI] Clean up and release all acquired input devices, notification lists, control managers, and event queues. [AI]
	~LegoInputManager() override;

	//! [AI] Add an input event (for mouse, keyboard, or joystick) to the processing queue, or process immediately based on flags/state.
	//! @param p_id         Notification type (e.g., key press, mouse click) [AI]
	//! @param p_modifier   Modifier flags (e.g., mouse button state, key modifiers) [AI]
	//! @param p_x          X screen coordinate [AI]
	//! @param p_y          Y screen coordinate [AI]
	//! @param p_key        Key code (virtual key, DIK_*, etc.) [AI]
	void QueueEvent(NotificationId p_id, MxU8 p_modifier, MxLong p_x, MxLong p_y, MxU8 p_key);

	//! [AI] Register a core object as a recipient for keyboard events; safe for concurrent multi-threading.
	//! @param p_notify     MxCore* to add to keyboard notification list [AI]
	void Register(MxCore*);

	//! [AI] Unregister a previously registered recipient so it will no longer receive input notifications.
	//! @param p_notify     MxCore* to remove [AI]
	void UnRegister(MxCore*);

	//! [AI] Updates input and processes the event queue. Called by the tickle system each frame or input 'tick'.
	//! @return Always returns SUCCESS [AI]
	MxResult Tickle() override;

	//! [AI] No-op, always returns SUCCESS. Place-holder for presenter put-data protocol.
	MxResult PutData() override { return SUCCESS; } // vtable+0x4c

	//! [AI] Set up DirectInput and joystick state, instantiate controller and notification list.
	//! @param p_hwnd       Window handle whose instance/input context should be used. [AI]
	//! @return SUCCESS (0) if OK, FAILURE otherwise [AI]
	MxResult Create(HWND p_hwnd);

	//! [AI] Release all allocated DirectInput devices, notification lists, event queues, and control manager. [AI]
	void Destroy() override;

	//! [AI] Create keyboard input device and acquire focus for the given window handle.
	//! @param p_hwnd       Window handle to acquire for keyboard input [AI]
	void CreateAndAcquireKeyboard(HWND p_hwnd);

	//! [AI] Unacquire and release all DirectInput device interfaces (keyboard). [AI]
	void ReleaseDX();

	//! [AI] Scan for valid joystick ID based on preferred index or check all available joysticks. Sets up internal JOYCAPS.
	//! @return SUCCESS if joystick found and configured, FAILURE otherwise [AI]
	MxResult GetJoystickId();

	//! [AI] Retrieve state of the currently assigned joystick device and normalized position/button state.
	//! @param p_joystickX      Normalized X axis (0-100) [AI]
	//! @param p_joystickY      Normalized Y axis (0-100) [AI]
	//! @param p_buttonsState   Joystick button bitmask [AI]
	//! @param p_povPosition    POV (hat) position (degrees/100 or -1 if centered) [AI]
	//! @return SUCCESS if state successfully retrieved, FAILURE if not [AI]
	MxResult GetJoystickState(MxU32* p_joystickX, MxU32* p_joystickY, DWORD* p_buttonsState, MxU32* p_povPosition);

	//! [AI] Start the Windows timer used for distinguishing auto drag events during mouse interaction. [AI]
	void StartAutoDragTimer();

	//! [AI] Stop the running auto drag timer if any. [AI]
	void StopAutoDragTimer();

	//! [AI] Enable event queue and input event processing. Resets relevant state. [AI]
	void EnableInputProcessing();

	//! [AI] Assigns a new camera controller for mouse/look operations.
	//! @param p_camera Camera controller to use (may be NULL to disable camera actions) [AI]
	void SetCamera(LegoCameraController* p_camera);

	//! [AI] Remove any assigned camera controller, disabling camera navigation responses. [AI]
	void ClearCamera();

	//! [AI] Assigns the current world to receive mouse/click/pick notifications.
	//! @param p_world World for click/drag event targeting [AI]
	void SetWorld(LegoWorld* p_world);

	//! [AI] Remove any world assignment (used to clear targeting/scene changes). [AI]
	void ClearWorld();

	//! [AI] Set general-purpose input block flag (purpose: temporary input disable during drag or transitions).
	//! @param p_unk0x88 TRUE to block input, FALSE to allow [AI]
	void SetUnknown88(MxBool p_unk0x88) { m_unk0x88 = p_unk0x88; }

	//! [AI] Typically used to allow button-down event processing during partial-blocked states.
	//! @param p_unk0x335 New value for flag [AI]
	void SetUnknown335(MxBool p_unk0x335) { m_unk0x335 = p_unk0x335; }

	//! [AI] Enables accepting input only for space-bar events (used in special UI states).
	//! @param p_unk0x336 New value for flag [AI]
	void SetUnknown336(MxBool p_unk0x336) { m_unk0x336 = p_unk0x336; }

	//! [AI] Enable or disable joystick support in input processing.
	//! @param p_useJoystick TRUE to use joystick, FALSE to ignore joystick [AI]
	void SetUseJoystick(MxBool p_useJoystick) { m_useJoystick = p_useJoystick; }

	//! [AI] Set user-preferred joystick device index (overrides auto-detection).
	//! @param p_joystickIndex Preferred joystick index to use [AI]
	void SetJoystickIndex(MxS32 p_joystickIndex) { m_joystickIndex = p_joystickIndex; }

	//! [AI] Block most input processing, allowing only button-down and space events (UI modal input blocking).
	void DisableInputProcessing()
	{
		m_unk0x88 = TRUE;
		m_unk0x336 = FALSE;
	}

	//! [AI] Retrieve the active control manager, responsible for UI and main action mapping.
	//! @return Control manager object [AI]
	LegoControlManager* GetControlManager() { return m_controlManager; }

	//! [AI] Retrieve the currently assigned LegoWorld for scene and actor event notifications.
	//! @return The assigned world object [AI]
	LegoWorld* GetWorld() { return m_world; }

	//! [AI] Returns the current camera controller.
	//! @return Camera controller or NULL [AI]
	LegoCameraController* GetCamera() { return m_camera; }

	//! [AI] Dispatch processing of all queued input events until the queue is empty or processing requests exit.
	void ProcessEvents();

	//! [AI] Processes a single input event (key, mouse click, drag, etc.), sending it to appropriate targets.
	//! Applies drag/click logic, entity and UI focus resolution. Returns TRUE if the event caused an exclusive action.
	//! @param p_param Input event description [AI]
	//! @return TRUE if the event consumed and should stop further processing [AI]
	MxBool ProcessOneEvent(LegoEventNotificationParam& p_param);

	//! [AI] Complex drag/click/timer event filter. Determines if/when to convert mouse motion into clicks or drags.
	//! @param p_param Input event (may be updated to reflect drag state) [AI]
	//! @return TRUE if notification should continue, FALSE to block further handling [AI]
	MxBool FUN_1005cdf0(LegoEventNotificationParam& p_param);

	//! [AI] Polls DirectInput for current keyboard state. Updates m_keyboardState and success flag. [AI]
	void GetKeyboardState();

	//! [AI] Retrieves current navigation (arrow) key status from the keyboard, combining keypad and arrow keys into bitmask.
	//! @param p_keyFlags Output for combined key status (bitmask of enum Keys). [AI]
	//! @return SUCCESS if keyboard state fetched, FAILURE if device not ready [AI]
	MxResult GetNavigationKeyStates(MxU32& p_keyFlags);

private:
	MxCriticalSection m_criticalSection;     ///< [AI] For synchronizing access to notification/event lists (thread-safety). [AI]
	LegoNotifyList* m_keyboardNotifyList;    ///< [AI] List of MxCore* receiving keyboard notifications. [AI]
	LegoCameraController* m_camera;          ///< [AI] Currently assigned camera controller for mouse/camera input. [AI]
	LegoWorld* m_world;                      ///< [AI] Current active world to receive input/click notifications. [AI]
	LegoEventQueue* m_eventQueue;            ///< [AI] Event queue for all pending input events. [AI]
	MxS32 m_x;                               ///< [AI] Most recent mouse X coordinate relevant for drag/click [AI]
	MxS32 m_y;                               ///< [AI] Most recent mouse Y coordinate relevant for drag/click [AI]
	MxS32 m_unk0x74;                         ///< [AI] Mouse drag threshold squared (for initiation of drag) [AI]
	UINT m_autoDragTimerID;                  ///< [AI] ID of auto-drag timer (Windows timer object) [AI]
	UINT m_autoDragTime;                     ///< [AI] Milliseconds before auto-converting mouse down to drag [AI]
	MxBool m_unk0x80;                        ///< [AI] TRUE if a drag is currently active [AI]
	MxBool m_unk0x81;                        ///< [AI] TRUE if a mouse button is held down, but not yet dragging [AI]
	LegoControlManager* m_controlManager;    ///< [AI] Manager for input control remapping/UI actions [AI]
	MxBool m_unk0x88;                        ///< [AI] TRUE to block most input processing [AI]
	IDirectInput* m_directInput;             ///< [AI] DirectInput COM object for keyboard input [AI]
	IDirectInputDevice* m_directInputDevice; ///< [AI] DirectInput device for the keyboard [AI]
	MxBool m_kbStateSuccess;                 ///< [AI] TRUE if the last call to GetKeyboardState succeeded [AI]
	MxU8 m_keyboardState[256];               ///< [AI] DirectInput keyboard button state array [AI]
	MxBool m_unk0x195;                       ///< [AI] Drag input/toggle state (shift key logic) [AI]
	MxS32 m_joyid;                           ///< [AI] Current active joystick device ID [AI]
	MxS32 m_joystickIndex;                   ///< [AI] User-specified joystick index (or -1 for auto) [AI]
	JOYCAPS m_joyCaps;                       ///< [AI] Capabilities of the currently active joystick [AI]
	MxBool m_useJoystick;                    ///< [AI] Flag: TRUE to accept/process joystick input [AI]
	MxBool m_unk0x335;                       ///< [AI] Partial input block: button-down events only [AI]
	MxBool m_unk0x336;                       ///< [AI] Partial input: only allow SPACE key [AI]
};

#endif // LEGOINPUTMANAGER_H
