#ifndef BUILDINGS_H
#define BUILDINGS_H

#include "buildingentity.h"

class LegoEventNotificationParam;

/// @brief [AI] Entity for the Information Center building in LEGO Island.
/// @details [AI] The InfoCenterEntity class represents the interactive entity for the Information Center building on LEGO Island.
/// It provides specific interaction logic for the Info Center context by overriding the HandleClick method.
/// Serves as a specialization of BuildingEntity, adding Info Center-specific behaviors for player input.
class InfoCenterEntity : public BuildingEntity {
public:
	/// @brief [AI] Returns the class name ("InfoCenterEntity") for runtime type identification.
	/// @details [AI] Used for checking type at runtime or for serialization/inspection logic.
	const char* ClassName() const override // vtable+0x0c
	{
		return "InfoCenterEntity";
	}

	/// @brief [AI] Checks whether this object is of a certain class type or derives from it.
	/// @details [AI] Compares the provided name with this class and all its parent classes for "is-a" relationships.
	/// @param p_name Class name string to compare. [AI]
	/// @return TRUE if the entity is of type p_name or one of its ancestors. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, InfoCenterEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Information Center building.
	/// @details [AI] Triggers context-dependent actions and cutscenes when the Info Center is clicked,
	/// depending on the current game state/act. Transitions the player to the information main area.
	/// @param p_param Event notification parameter, includes information about the click event and context. [AI]
	/// @return Always returns 1 to indicate the click was handled. [AI]
	MxLong HandleClick(LegoEventNotificationParam& p_param) override; // vtable+0x50

	// SYNTHETIC: LEGO1 0x1000f7b0
	// InfoCenterEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Gas Station building in LEGO Island.
/// @details [AI] Represents the interactive gas station building, with custom click handling that can trigger the transition
/// to the garage area and related animation/state changes.
class GasStationEntity : public BuildingEntity {
public:
	/// @brief [AI] Returns the class name ("GasStationEntity") for runtime type identification.
	const char* ClassName() const override // vtable+0x0c
	{
		return "GasStationEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "GasStationEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, GasStationEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Gas Station building.
	/// @details [AI] When clicked, moves the player to the garage if certain state constraints are met.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// SYNTHETIC: LEGO1 0x1000f890
	// GasStationEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Hospital building in LEGO Island.
/// @details [AI] Handles custom player interaction logic for the hospital area.
class HospitalEntity : public BuildingEntity {
public:
	/// @brief [AI] Returns the class name ("HospitalEntity") for runtime type identification.
	const char* ClassName() const override // vtable+0x0c
	{
		return "HospitalEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "HospitalEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, HospitalEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Hospital building.
	/// @details [AI] When clicked, transitions player to hospital or triggers related actions.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override; // vtable+0x50

	// SYNTHETIC: LEGO1 0x1000f820
	// HospitalEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Police building in LEGO Island.
/// @details [AI] Handles click logic/events for the police station in the island game world.
class PoliceEntity : public BuildingEntity {
public:
	/// @brief [AI] Returns the class name ("PoliceEntity") for runtime type identification.
	const char* ClassName() const override // vtable+0x0c
	{
		return "PoliceEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "PoliceEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, PoliceEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Police building.
	/// @details [AI] Triggers transitions and scripting relevant to the police station.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override; // vtable+0x50

	// SYNTHETIC: LEGO1 0x1000f900
	// PoliceEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Beach House building in LEGO Island.
/// @details [AI] Implements unique click/interaction logic for the beach house location/building.
class BeachHouseEntity : public BuildingEntity {
public:
	/// @brief [AI] Returns the class name ("BeachHouseEntity") for runtime type identification.
	const char* ClassName() const override // vtable+0x0c
	{
		return "BeachHouseEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "BeachHouseEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, BeachHouseEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Beach House building.
	/// @details [AI] Initiates a transition to the jet-ski building area on click.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// SYNTHETIC: LEGO1 0x1000f970
	// BeachHouseEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Race Stands (grandstands) building in LEGO Island.
/// @details [AI] Handles interaction logic for moving to the racecar build area or triggering race stand events.
class RaceStandsEntity : public BuildingEntity {
	/// @brief [AI] Returns the class name ("RaceStandsEntity") for runtime type identification.
	const char* ClassName() const override // vtable+0x0c
	{
		return "RaceStandsEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "RaceStandsEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, RaceStandsEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events for the Race Stands building.
	/// @details [AI] Drives transitions toward the racecar build area.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// SYNTHETIC: LEGO1 0x1000f9e0
	// RaceStandsEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Jail building in LEGO Island.
/// @details [AI] Handles click event logic for the jail, often triggering animation or cutscene camera changes.
class JailEntity : public BuildingEntity {
	/// @brief [AI] Returns the class name ("RaceStandsEntity") for runtime type identification.
	/// @details [AI_SUGGESTED_CORRECTED_NAME: Should be "JailEntity"; current return value is likely a copy-paste error.]
	const char* ClassName() const override // vtable+0x0c
	{
		return "RaceStandsEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "JailEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, JailEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events specific to the Jail building.
	/// @details [AI] Triggers a special camera animation relevant to the jail when clicked.
	/// @param p_param [AI] Event notification parameter containing click context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// SYNTHETIC: LEGO1 0x1000fac0
	// JailEntity::`scalar deleting destructor'
};

/// @brief [AI] Entity for the Cave building in LEGO Island.
/// @details [AI] Handles complex interaction logic involving chest and cave door sub-objects.
/// Can trigger multiple-scripted actions/cutscenes for these special cave features.
class CaveEntity : public BuildingEntity {
	/// @brief [AI] Returns the class name ("RaceStandsEntity") for runtime type identification.
	/// @details [AI_SUGGESTED_CORRECTED_NAME: Should be "CaveEntity"; current return value is likely a copy-paste error.]
	const char* ClassName() const override // vtable+0x0c
	{
		return "RaceStandsEntity";
	}

	/// @brief [AI] Checks whether this object is (or inherits from) "CaveEntity".
	/// @param p_name Class name string to compare. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, CaveEntity::ClassName()) || BuildingEntity::IsA(p_name);
	}

	/// @brief [AI] Handles click events and scripting logic for cave-interactive objects (like the chest and cave door).
	/// @details [AI] Differentiates between clicking on the special chest or cave door, triggering corresponding scripts/animations,
	/// and manages the cycle of script actions used by these objects.
	/// @param p_param [AI] Event notification parameter containing click and ROI context.
	/// @return [AI] Always returns 1.
	MxLong HandleClick(LegoEventNotificationParam& p_param) override;

	// SYNTHETIC: LEGO1 0x1000fa50
	// CaveEntity::`scalar deleting destructor'
};

#endif // BUILDINGS_H
