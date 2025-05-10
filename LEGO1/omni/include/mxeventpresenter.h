#ifndef MXEVENTPRESENTER_H
#define MXEVENTPRESENTER_H

#include "decomp.h"
#include "mxmediapresenter.h"

// VTABLE: LEGO1 0x100dca88
// SIZE 0x54

/**
 * @brief [AI] Presenter for handling "Event" stream data, typically parsed from event actions in SI files. 
 * 
 * MxEventPresenter is a derived class of MxMediaPresenter and responsible for processing and dispatching events encoded in streamed chunks, often to trigger in-game changes (such as variable table updates) in response to script commands. Handles memory for the parsed event data and interacts with the variable table if the event chunk represents a variable change. Registered with the event manager for processing and cleanup. [AI]
 */
class MxEventPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs an event presenter and initializes internal state.
	 */
	MxEventPresenter();

	/**
	 * @brief [AI] Destructor, unregisters from event manager and releases memory.
	 */
	~MxEventPresenter() override;

	/**
	 * @brief [AI] Returns the static class identifier for this presenter ("MxEventPresenter"). Used for dynamic type checks and dispatch.
	 * @return Pointer to null-terminated class name string. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x10101dcc
		return "MxEventPresenter";
	}

	/**
	 * @brief [AI] Returns the class identifier of this presenter instance. Overrides MxMediaPresenter::ClassName.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Checks if this object matches, or derives from, a class of the given name. 
	 * Returns true if p_name equals "MxEventPresenter" or if the parent class (MxMediaPresenter) matches.
	 * @param p_name Null-terminated class name to query against. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxEventPresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Processes event data in the ready state; copies the next chunk's data and prepares for parsing extra event commands. [AI]
	 */
	void ReadyTickle() override;                   // vtable+0x18

	/**
	 * @brief [AI] Processes "starting" state, transitioning to streaming if elapsed time has passed the chunk time. [AI]
	 */
	void StartingTickle() override;                // vtable+0x1c

	/**
	 * @brief [AI] Registers this presenter with the event manager for tickling and notification. [AI]
	 * @details Returns SUCCESS and registers with the event manager, or FAILURE if event manager is not present. [AI]
	 */
	MxResult AddToManager() override;              // vtable+0x34

	/**
	 * @brief [AI] Unregisters this presenter from the event manager and frees owned resources, including event data buffer. [AI]
	 */
	void Destroy() override;                       // vtable+0x38

	/**
	 * @brief [AI] If the event is a variable table command (event type == 2), parses and updates the variable table. Releases chunk memory if required and clears current chunk pointer. Always returns SUCCESS. [AI]
	 */
	MxResult PutData() override;                   // vtable+0x4c

	/**
	 * @brief [AI] Copies raw chunk data from a stream chunk (e.g., from a SI file), for use by the event presenter during parsing/execution. Allocates a buffer and duplicates the chunk's contents. [AI]
	 * @param p_chunk Pointer to the input MxStreamChunk holding original event data. [AI]
	 */
	virtual void CopyData(MxStreamChunk* p_chunk); // vtable+0x5c

	// SYNTHETIC: LEGO1 0x100c2d20
	// MxEventPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes the presenter's internal state, clearing data buffers and preparing for use. [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Raw event data copied from stream chunk for processing by this presenter.
	 * Allocated and released according to stream state; may encode commands to update in-game variables. [AI]
	 */
	MxU8* m_data; // 0x50
};

#endif // MXEVENTPRESENTER_H