#ifndef LEGOENTITYPRESENTER_H
#define LEGOENTITYPRESENTER_H

#include "mxcompositepresenter.h"

class LegoEntity;
class Vector3;

// VTABLE: LEGO1 0x100d8398
// SIZE 0x50
/**
 * @brief [AI] Presenter responsible for managing the lifecycle, location, and logic for a LegoEntity instance as part of a presenter-based media action, typically managing the appearance and animation of an in-game actor.
 * @details [AI] LegoEntityPresenter creates, updates, and manages a LegoEntity based on the associated MxDSAction and its extra data, integrates with the video manager for presentation logic, and supports setting its internal entity and its location. It extends MxCompositePresenter for composite sequencing and event-handling.
 */
class LegoEntityPresenter : public MxCompositePresenter {
public:
	/**
	 * @brief [AI] Constructs a new LegoEntityPresenter, initializing internal data.
	 */
	LegoEntityPresenter();

	/**
	 * @brief [AI] Destructor. Cleans up resources and unregisters itself from managers, if necessary.
	 */
	~LegoEntityPresenter() override; // vtable+0x00

	/**
	 * @brief [AI] Returns the class handler name string for this presenter type.
	 * @return [AI] The string "LegoEntityPresenter".
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Returns the class name for dynamic type checks.
	 * @return [AI] "LegoEntityPresenter".
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Tests this object or its parents for a class name match.
	 * @param p_name Name to be checked. [AI]
	 * @return [AI] True if @p p_name matches this class or any parent class.
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Called when the presenter is in the Ready state, typically responsible for instantiating and initializing the LegoEntity based on the current action.
	 * @details [AI] Creates a new internal entity, sets its location, and parses extra configuration.
	 */
	void ReadyTickle() override;                                                           // vtable+0x18

	/**
	 * @brief [AI] Called periodically in the Repeating state to check for completion and manage progression.
	 * @details [AI] Will end the action if there are no child presenters left.
	 */
	void RepeatingTickle() override;                                                       // vtable+0x24

	/**
	 * @brief [AI] Parses extra data (typically serialized commands/string) from the action and applies it to the managed entity.
	 * @details [AI] Usually invokes entity-specific configuration from the MxDSAction's extra data buffer.
	 */
	void ParseExtra() override;                                                            // vtable+0x30

	/**
	 * @brief [AI] Cleans up this presenter, unregisters itself from the VideoManager, and resets its entity.
	 * @details [AI] May be called both by destructor and for explicit destruction.
	 */
	void Destroy() override;                                                               // vtable+0x38

	/**
	 * @brief [AI] Starts a new LegoEntity action using the provided stream controller and definition.
	 * @param p_controller Stream controller managing the data source. [AI]
	 * @param p_action The data structure defining the action and parameters. [AI]
	 * @return [AI] Result code indicating start success/failure.
	 */
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) override; // vtable+0x3c

	/**
	 * @brief [AI] Initializes internal state for (re-)use, called from constructor and internal resets.
	 */
	virtual void Init();                                                                   // vtable+0x68

	/**
	 * @brief [AI] Sets the managed LegoEntity for this presenter.
	 * @param p_entity Entity to manage. [AI]
	 * @return [AI] Unknown return type, always returns 0. (possibly status/future compatibility).
	 */
	virtual undefined4 SetEntity(LegoEntity* p_entity);                                    // vtable+0x6c

	/**
	 * @brief [AI] Sets the entity's world transformation using location, direction, and up vectors.
	 * @param p_location New world position. [AI]
	 * @param p_direction New world direction. [AI]
	 * @param p_up New up vector. [AI]
	 */
	void SetEntityLocation(const Vector3& p_location, const Vector3& p_direction, const Vector3& p_up);

	/**
	 * @brief [AI] Returns the currently managed internal LegoEntity.
	 * @return [AI] Pointer to the LegoEntity managed by this presenter.
	 */
	LegoEntity* GetInternalEntity() { return m_entity; }

	/**
	 * @brief [AI] Directly sets the internal LegoEntity pointer without instantiating or taking ownership.
	 * @param p_entity The LegoEntity pointer to set. [AI]
	 */
	void SetInternalEntity(LegoEntity* p_entity) { m_entity = p_entity; }

	// SYNTHETIC: LEGO1 0x100535a0
	// LegoEntityPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Performs destruction and resource cleanup, optionally invoked from destructor context.
	 * @param p_fromDestructor True if called from the destructor. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

protected:
	/**
	 * @brief [AI] The entity instance managed by this presenter, typically created based on the current action.
	 */
	LegoEntity* m_entity; // 0x4c
};

#endif // LEGOENTITYPRESENTER_H
