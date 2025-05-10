#ifndef MXPRESENTER_H
#define MXPRESENTER_H

#include "decomp.h"
#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxgeometry.h"

class MxCompositePresenter;
class MxDSAction;
class MxOmni;
class MxStreamController;
class MxEntity;

/// @brief [AI] Abstract base class for all presenter types in the LEGO Island engine, responsible for managing the lifecycle of the presentation of actions and their corresponding tickle (update) state. The presenter tracks and transitions its tickle state and serves as an interface for derived classes which implement rendering, sound, and other forms of presentation logic.
/// @details [AI] Presenters are tickled by the engine and handle different stages of playback (idle, ready, starting, streaming, repeating, freezing, done). Each presenter holds an associated action (MxDSAction), its location, display depth order (Z), and optionally links to a composite presenter for hierarchical composition of presentational logic. Most derived classes correspond to specific media types or action groupings.
/// @see [AI] MxMediaPresenter, MxCompositePresenter, MxFlcPresenter, MxSmkPresenter, etc.
// VTABLE: LEGO1 0x100d4d38
// SIZE 0x40
class MxPresenter : public MxCore {
public:
	/// @brief [AI] Represents the state of the presenter's tickle (update) lifecycle.
	enum TickleState {
		e_idle = 0,     ///< [AI] Not processing an action.
		e_ready,        ///< [AI] Prepared to start processing an action.
		e_starting,     ///< [AI] In the process of starting playback/presentation.
		e_streaming,    ///< [AI] Streaming or rendering actively.
		e_repeating,    ///< [AI] Presentation is repeating (e.g., looping media).
		e_freezing,     ///< [AI] Temporarily suspending updates or playback.
		e_done,         ///< [AI] Completed processing the current action.
	};

	/// @brief [AI] Constructor. Initializes internal tickle state and other members.
	MxPresenter() { Init(); }

	/// @brief [AI] Main tickle handler, called periodically to progress presenter's internal state.
	/// @details [AI] Depending on the current tickle state, will delegate to the appropriate stage tickle method.
	/// @return [AI] Result code from tickling, always SUCCESS in the base class.
	MxResult Tickle() override; // vtable+0x08

	/// @brief [AI] Reserved for future or specialized use in derived classes.
	virtual void VTable0x14() {} // vtable+0x14 [AI_SUGGESTED_NAME: OnCustomTickle]

	/// @brief [AI] Handles the transition and setup for the Ready state. Parses extra action data and advances state.
	virtual void ReadyTickle()
	{
		ParseExtra();
		ProgressTickleState(e_starting);
	} // vtable+0x18

	/// @brief [AI] Handles actions required when first starting presentation. Advances to streaming state.
	virtual void StartingTickle() { ProgressTickleState(e_streaming); } // vtable+0x1c

	/// @brief [AI] Handles periodic updates during the streaming/presentation stage. Advances to repeating state.
	virtual void StreamingTickle() { ProgressTickleState(e_repeating); } // vtable+0x20

	/// @brief [AI] Handles updates when in a repeating (looping) stage. Advances to freezing state.
	virtual void RepeatingTickle() { ProgressTickleState(e_freezing); } // vtable+0x24

	/// @brief [AI] Handles updates during the freezing/suspended state. Advances to done state.
	virtual void FreezingTickle() { ProgressTickleState(e_done); } // vtable+0x28

protected:
	/// @brief [AI] Handles any post-completion logic, resetting to idle state.
	virtual void DoneTickle() { ProgressTickleState(e_idle); } // vtable+0x2c

	/// @brief [AI] Parses additional data from the associated action for configuration or world interaction.
	virtual void ParseExtra(); // vtable+0x30

	/// @brief [AI] Helper for advancing the presenter's tickle state and updating transition history.
	/// @param p_tickleState [AI] New tickle state to transition to.
	void ProgressTickleState(TickleState p_tickleState)
	{
		m_previousTickleStates |= 1 << (MxU8) m_currentTickleState;
		m_currentTickleState = p_tickleState;
	}

public:
	/// @brief [AI] Destructor, cleans up resources (base class: does nothing beyond Init).
	~MxPresenter() override {} // vtable+0x00

	/// @brief [AI] Optional registration with a manager (such as TickleManager); by default does nothing.
	/// @return [AI] Always returns SUCCESS in base class.
	virtual MxResult AddToManager() { return SUCCESS; } // vtable+0x34

	/// @brief [AI] Resets presenter state or cleans up resources after completion/removal.
	virtual void Destroy() { Init(); } // vtable+0x38

	/// @brief [AI] Initiates presenter for a new action, setting up context and state.
	/// @param p_controller [AI] Stream controller supplying data for the action (can be NULL for some presenters).
	/// @param p_action [AI] Action to be presented.
	/// @return [AI] SUCCESS if successfully started.
	virtual MxResult StartAction(MxStreamController*, MxDSAction*); // vtable+0x3c

	/// @brief [AI] Terminates the current action, notifies listeners and resets state.
	virtual void EndAction();                                       // vtable+0x40

	/// @brief [AI] Forces the tickle state, advancing to the requested lifecycle stage.
	/// @param p_tickleState [AI] The tickle state to transition into.
	virtual void SetTickleState(TickleState p_tickleState) { ProgressTickleState(p_tickleState); } // vtable+0x44

	/// @brief [AI] Checks if the specified tickle state has ever been passed since last reset.
	/// @param p_tickleState [AI] The tickle state to check for.
	/// @return [AI] TRUE if the specified state is in the state history bitmask.
	virtual MxBool HasTickleStatePassed(TickleState p_tickleState)
	{
		return m_previousTickleStates & (1 << (MxU8) p_tickleState);
	} // vtable+0x48

	/// @brief [AI] Allows the presenter to submit pending results or output to the engine.
	/// @details [AI] Placeholder implementation, always returns SUCCESS.
	virtual MxResult PutData() { return SUCCESS; } // vtable+0x4c

	/// @brief [AI] Returns TRUE if the given (x, y) falls within hit-test bounds for the presenter (e.g. clickable geometry).
	/// @param p_x [AI] X position to test.
	/// @param p_y [AI] Y position to test.
	/// @return [AI] FALSE in base class, override for hit-detection in derived types.
	virtual MxBool IsHit(MxS32 p_x, MxS32 p_y) { return FALSE; } // vtable+0x50

	/// @brief [AI] Enables or disables this presenter (controls action flags accordingly).
	/// @param p_enable [AI] TRUE to enable, FALSE to disable.
	virtual void Enable(MxBool p_enable); // vtable+0x54

	/// @brief [AI] Returns the handler class name for identification and reflection purposes.
	/// @return [AI] Static string representing the handler class ("MxPresenter" by default).
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0740
		return "MxPresenter";
	}

	/// @brief [AI] Returns the run-time class name for this presenter.
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/// @brief [AI] Determines if this object is of (or inherits) the specified named class.
	/// @param p_name [AI] Name of the class to check for.
	/// @return [AI] TRUE if type is MxPresenter or ancestor.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxPresenter::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Creates an entity based on action 'extra' data, or uses the provided default name.
	/// @param p_defaultName [AI] Fallback name to use if no OBJECT: key found in action extra data.
	/// @return [AI] Pointer to the created entity, or NULL if creation failed.
	MxEntity* CreateEntity(const char* p_defaultName);

	/// @brief [AI] Notifies a composite presenter (if one exists) that this presenter wishes to join a group.
	/// @param p_omni [AI] The central engine context; may be NULL to retrieve singleton instance.
	void SendToCompositePresenter(MxOmni* p_omni);

	/// @brief [AI] Returns whether this presenter is logically enabled (based on the associated action's flags).
	/// @return [AI] TRUE if action and c_enabled flag are both set.
	MxBool IsEnabled();

	/// @brief [AI] Returns the current tickle state.
	MxS32 GetCurrentTickleState() const { return this->m_currentTickleState; }

	/// @brief [AI] Returns the presenter's screen location (in pixels).
	MxPoint32 GetLocation() const { return this->m_location; }

	/// @brief [AI] Returns the X coordinate of screen location.
	MxS32 GetX() const { return this->m_location.GetX(); }

	/// @brief [AI] Returns the Y coordinate of screen location.
	MxS32 GetY() const { return this->m_location.GetY(); }

	/// @brief [AI] Returns the display Z (depth) order.
	MxS32 GetDisplayZ() const { return this->m_displayZ; }

	/// @brief [AI] Returns the current action being presented.
	MxDSAction* GetAction() const { return this->m_action; }

	/// @brief [AI] Sets the action associated with this presenter.
	/// @param p_action [AI] Action to associate with the presenter.
	void SetAction(MxDSAction* p_action) { m_action = p_action; }

	/// @brief [AI] Sets the composite presenter to notify/join on completion.
	/// @param p_compositePresenter [AI] Composite presenter instance to associate.
	void SetCompositePresenter(MxCompositePresenter* p_compositePresenter)
	{
		m_compositePresenter = p_compositePresenter;
	}

	/// @brief [AI] Sets the display Z (depth) order for the presenter.
	/// @param p_displayZ [AI] Z order value.
	void SetDisplayZ(MxS32 p_displayZ) { m_displayZ = p_displayZ; }

	// SYNTHETIC: LEGO1 0x1000c070
	// MxPresenter::`scalar deleting destructor'
protected:
	/// @brief [AI] Initializes object state to post-construction defaults.
	void Init();

	/// @brief [AI] Current state in the tickle lifecycle.
	TickleState m_currentTickleState;           // 0x08

	/// @brief [AI] Bitfield representing all tickle states that have already occurred during this lifetime.
	MxU32 m_previousTickleStates;               // 0x0c

	/// @brief [AI] 2D display location for the presenter.
	MxPoint32 m_location;                       // 0x10

	/// @brief [AI] Z-order value for display stacking.
	MxS32 m_displayZ;                           // 0x18

	/// @brief [AI] The associated action currently being presented by this presenter.
	MxDSAction* m_action;                       // 0x1c

	/// @brief [AI] Thread synchronization for presenter state and data.
	MxCriticalSection m_criticalSection;        // 0x20

	/// @brief [AI] Owner composite presenter, if any.
	MxCompositePresenter* m_compositePresenter; // 0x3c
};

/// @brief [AI] Provides a mapping from action object/type to the correct presenter handler class name based on action type and content.
/// @param p_action [AI] The action whose handler is to be determined.
/// @return [AI] Class name string representing the presenter implementation to be used for the given action.
const char* PresenterNameDispatch(const MxDSAction&);

#endif // MXPRESENTER_H
