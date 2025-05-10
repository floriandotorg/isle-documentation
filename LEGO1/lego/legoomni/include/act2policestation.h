#ifndef ACT2POLICESTATION_H
#define ACT2POLICESTATION_H

#include "legoentity.h"

// VTABLE: LEGO1 0x100d53a8
// VTABLE: BETA10 0x101bd570
// SIZE 0x68

/**
 * @brief [AI] Represents the Act 2 Police Station entity in LEGO Island.
 * 
 * This class extends LegoEntity and implements notification handling specific to the police station in Act 2.
 * On receiving a click notification, triggers a secondary notification to the current world,
 * signaling a special event (c_notificationType23).
 * 
 * The class supports class type identification and notification interfaces.
 * @details [AI] The core functionality minimally overrides notification logic and RTTI interface.
 */
class Act2PoliceStation : public LegoEntity {
public:
	/**
	 * @brief [AI] Handles notifications directed at the police station entity.
	 * 
	 * Intercepts click notifications and, when one occurs, dispatches a special notification
	 * (c_notificationType23) to the current LegoWorld via the notification manager.
	 * 
	 * @param p_param The notification parameter object carrying notification type and metadata. [AI]
	 * @return Returns 1 if the notification was handled (e.g., on click). [AI]
	 * @details [AI] Primary extension point for event-driven world interactions such as clicks.
	 */
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/**
	 * @brief [AI] Gets the class name identifier for RTTI type checking.
	 * 
	 * @return Pointer to static string "Act2PoliceStation". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03fc
		return "Act2PoliceStation";
	}

	/**
	 * @brief [AI] Checks whether the class is or derives from a specified named type.
	 * 
	 * Returns true if the provided name matches "Act2PoliceStation" or any parent class's type.
	 *
	 * @param p_name Name of the class to match for RTTI/is-a checks. [AI]
	 * @return True if the entity is of or derived from the named class. [AI]
	 * @details [AI] Used for runtime type-checking and reflection; compatible with parent class hierarchy.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Act2PoliceStation::ClassName()) || LegoEntity::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x1000f610
	// Act2PoliceStation::`scalar deleting destructor'
};

#endif // ACT2POLICESTATION_H
