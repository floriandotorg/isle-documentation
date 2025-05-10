#ifndef DOORS_H
#define DOORS_H

#include "legopathactor.h"

class LegoROI;

/// \class Doors
/// \brief [AI] Represents a special LegoPathActor controlling the animation and logic of a pair of doors, including opening and closing transitions.
/// \details [AI]
/// - Inherits movement/path logic from LegoPathActor.
/// - Holds explicit pointers to two LegoROI child instances (representing left and right doors), which are animated when an entity interacts (hits) with the doors.
/// - Animations are time-based and use interpolation for opening, holding, and closing states.
/// - The object transitions through several states (closed, activating/opening, animating, restoring).
/// - The underlying ROI is required to be a compound object named "rcdor", and its children named with prefixes for left ("dor-lt"/"dor-sl") and right ("dor-rt"/"dor-sr") doors.
/// - This class also acts as a finite state machine over its controlled door geometry. [AI]
class Doors : public LegoPathActor {
public:
	/// \brief [AI] Constructs a Doors object and initializes member variables, in particular, sets pointers to per-door LegoROI objects to null and state variables to zero.
	Doors() : m_unk0x154(0), m_ltDoor(NULL), m_rtDoor(NULL), m_unk0x1f4(0) {}

	/// \brief [AI] Returns the class name string literal ("Doors") used for RTTI and IsA checks.
	/// \return [AI] "Doors"
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03e8
		return "Doors";
	}

	/// \brief [AI] Checks whether this object derives from or matches the given class name.
	/// \details [AI] Will return true for both "Doors" and any parent type (LegoPathActor), enabling RTTI and scripting compatibility.
	/// \param p_name Name of the class to compare against. [AI]
	/// \return [AI] True if the class names match Doors or its base; otherwise false.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Doors::ClassName()) || LegoPathActor::IsA(p_name);
	}

	/// \brief [AI] Parses action directives for the Doors, as well as identifying and associating left and right door objects from the ROI.
	/// \details [AI] This method subclasses LegoPathActor's version and then identifies child ROIs named "dor-lt"/"dor-sl" (left door) and "dor-rt"/"dor-sr" (right door). 
	/// Sets m_ltDoor and m_rtDoor accordingly. Asserts that both doors are found and that the main ROI is a recognized compound. [AI]
	/// \param p_extra Additional action arguments, typically from an SI script or level data. [AI]
	void ParseAction(char* p_extra) override;                          // vtable+0x20

	/// \brief [AI] Animates the doors based on current time, moving them through different animation states (closed, opening, holding open, closing).
	/// \details [AI] Operations depend on the internal state indicated by m_unk0x154 and time parameters. Handles updating the transformation (rotation) of both door ROIs.
	/// Restores state and resets to closed once the animation completes. [AI]
	/// \param p_time The current absolute time used for interpolation and state transitions. [AI]
	void Animate(float p_time) override;                               // vtable+0x70

	/// \brief [AI] Handles the event where another path actor interacts (collides) with this Doors actor, initiating the door opening sequence.
	/// \details [AI] This sets the animation state to opening and records the opening start time, as well as the original transforms of both doors. 
	/// Returns SUCCESS or FAILURE depending on whether the doors are fully open. [AI]
	/// \param p_actor The incoming LegoPathActor that is "hitting" this Doors instance. [AI]
	/// \param p_bool Unused, possibly for type of hit (ignored in implementation). [AI]
	/// \return [AI] SUCCESS if doors open, FAILURE if animation is ongoing.
	MxResult HitActor(LegoPathActor* p_actor, MxBool p_bool) override; // vtable+0x94

	/// \brief [AI] Calculates the normalized open-close position of the doors for the given time, based on the time since opening was triggered.
	/// \details [AI] Returns a value dependent on how far along the open-close timer the animation is, used for smooth interpolation. [AI]
	/// \param p_time The current time for which to compute normalized open/animation phase. [AI]
	/// \return [AI] Amount in radians (0...Pi/2) for door rotation/animation.
	virtual MxFloat VTable0xcc(float p_time);                          // vtable+0xcc

	// SYNTHETIC: LEGO1 0x1000e580
	// Doors::`scalar deleting destructor'

private:
	undefined4 m_unk0x154;  ///< [AI] State variable/state machine for doors: 0=uninitialized, 1=ready/closed, 2=animating. [AI_SUGGESTED_NAME: m_state]
	MxFloat m_unk0x158;     ///< [AI] Stores the animation (opening) start time for doors to enable smooth interpolation. [AI_SUGGESTED_NAME: m_animationStartTime]
	LegoROI* m_ltDoor;      ///< [AI] Pointer to left-side door's LegoROI in compound object; must be identified by ParseAction. [AI]
	LegoROI* m_rtDoor;      ///< [AI] Pointer to right-side door's LegoROI in compound object; must be identified by ParseAction. [AI]
	MxMatrix m_ltDoorLocal; ///< [AI] Original local-to-world transform for left door, used as reference for animation/restoring orientation. [AI]
	MxMatrix m_rtDoorLocal; ///< [AI] Original local-to-world transform for right door, used as reference for animation/restoring orientation. [AI]
	MxFloat m_unk0x1f4;     ///< [AI] Stores most recent phase/progress/angle of animation (used for transition interpolation). [AI_SUGGESTED_NAME: m_animationPhase]
};

#endif // DOORS_H
