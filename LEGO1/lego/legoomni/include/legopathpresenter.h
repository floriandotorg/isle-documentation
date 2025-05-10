#ifndef LEGOPATHPRESENTER_H
#define LEGOPATHPRESENTER_H

#include "mxatom.h"
#include "mxmediapresenter.h"

// VTABLE: LEGO1 0x100d7c10
// SIZE 0x54

/**
 * @brief [AI] Presenter class for loading and managing path data from scripts/actions, used for actor pathing in the LEGO Island engine. Handles allocation, destruction, and registration of path controllers with the video (presentation) manager, as well as tickle logic for presenting and parsing associated trigger atom identifiers. [AI]
 *
 * LegoPathPresenter sits atop MxMediaPresenter and is responsible for interpreting and instantiating path data used by entities/actors to follow world paths. On ReadyTickle, it creates LegoPathController objects based on streamed chunk data and registers these with the active world. [AI]
 */
class LegoPathPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs a LegoPathPresenter, initializing its members and state. [AI]
	 */
	LegoPathPresenter();

	/**
	 * @brief [AI] Destroys this presenter, unregistering from the video manager, deleting resources, and restoring critical section safety. [AI]
	 */
	~LegoPathPresenter() override;

	/**
	 * @brief [AI] Returns the static handler class name for this presenter, used for identification and class dispatching. [AI]
	 * @return The fully-qualified handler class name ("LegoPathPresenter"). [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Returns the class name for this presenter instance, for dynamic type identification. [AI]
	 * @return The handler class name for this presenter. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks if this instance matches a specified class name in the inheritance hierarchy. [AI]
	 * @param p_name The class name to check against. [AI]
	 * @return True if p_name matches this class or an ancestor; false otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Handles the transition to the ready state ("ReadyTickle") by consuming streamed path data, creating a LegoPathController, and inserting it into the current world. If data is not yet available, operation is deferred. [AI]
	 */
	void ReadyTickle() override;      // vtable+0x18

	/**
	 * @brief [AI] Processes data stream chunks during the streaming tickle phase. Consumes and frees chunks, and triggers repetition state if end-of-stream is reached. [AI]
	 */
	void StreamingTickle() override;  // vtable+0x20

	/**
	 * @brief [AI] Handles the repeating tickle logic, ending the action if the associated duration is not indefinite. [AI]
	 */
	void RepeatingTickle() override;  // vtable+0x24

	/**
	 * @brief [AI] Parses the extra (optional) field from the related media action, searching for a trigger string and assigning it to m_trigger. [AI]
	 */
	void ParseExtra() override;       // vtable+0x30

	/**
	 * @brief [AI] Registers this presenter instance with the global or world's video manager (LegoVideoManager). Used to ensure update/tickle callbacks are performed. [AI]
	 * @return SUCCESS if registered, FAILURE otherwise. [AI]
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Unregisters the presenter from the video manager, deallocates managed resources, and resets internal state. [AI]
	 */
	void Destroy() override;          // vtable+0x38

	// SYNTHETIC: LEGO1 0x10044a90
	// LegoPathPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initializes all members and internal state. Called by the constructor and during destruction to reset the presenter's state for reuse or clean-up. [AI]
	 */
	void Init();

protected:
	/**
	 * @brief [AI] Internal destroy logic with destructor context flag. Handles resource deallocation, unregisters from video manager, resets state, and calls parent destroy if needed. [AI]
	 * @param p_fromDestructor True if called from destructor context; false otherwise. Prevents redundant deletion. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Atom identifier representing a trigger parsed from the extra string in the associated media action. This may be matched to in-world triggers or events by controllers, and is assigned during ParseExtra(). [AI]
	 */
	MxAtomId m_trigger; // 0x50
};

#endif // LEGOPATHPRESENTER_H
