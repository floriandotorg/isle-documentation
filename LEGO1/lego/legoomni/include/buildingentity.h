#ifndef BUILDINGENTITY_H
#define BUILDINGENTITY_H

#include "legoentity.h"

class LegoEventNotificationParam;

/// \brief [AI] Represents an entity corresponding to a building within the LEGO Island game world.
/// [AI] This is an abstract base class extending LegoEntity, which adds notification handling appropriate for buildings, including click event responses.
/// [AI] BuildingEntity instances are automatically registered and unregistered with the notification system on construction/destruction.
/// [AI] Subclasses must implement HandleClick to define unique click interactions for their specific building type.
/// [AI] SIZE 0x68
class BuildingEntity : public LegoEntity {
public:
	/// \brief [AI] Constructs a BuildingEntity and registers it for notification events. [AI]
	BuildingEntity();

	/// \brief [AI] Destroys the BuildingEntity and unregisters it from notification events. [AI]
	~BuildingEntity() override; // vtable+0x00

	/// \brief [AI] Handles notification parameters sent to this entity. [AI]
	/// \details [AI] This override filters for click notifications and dispatches them to HandleClick, allowing building-specific interaction handling. Other notification types result in a no-op.
	/// \param p_param Parameter object describing the notification context. [AI]
	/// \returns [AI] The result of handle click if notification is a click, otherwise 0.
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Returns the class name of this entity type ("BuildingEntity"). [AI]
	/// \returns [AI] Static string "BuildingEntity".
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f07e8
		return "BuildingEntity";
	}

	/// \brief [AI] Checks if this object is of a given class or one of its superclasses. [AI]
	/// \details [AI] Allows type-safe checks using string comparison, compatible with the game's dynamic RTTI system.
	/// \param p_name Name or type to check. [AI]
	/// \returns [AI] True if the class name matches or any parent returns true; otherwise, false.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, BuildingEntity::ClassName()) || LegoEntity::IsA(p_name);
	}

	/// \brief [AI] Abstract method called when this building entity receives a click notification. [AI]
	/// \details [AI] Subclasses must implement this method to define what occurs when the building is clicked (e.g., open, close, interact, etc.).
	/// \param p_param Details about the click event and game context. [AI]
	/// \return [AI] Value indicating the outcome of the click event handling.
	virtual MxLong HandleClick(LegoEventNotificationParam& p_param) = 0;

	// SYNTHETIC: LEGO1 0x10015010
	// BuildingEntity::`scalar deleting destructor'
};

#endif // BUILDINGENTITY_H
