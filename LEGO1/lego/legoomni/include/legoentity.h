#ifndef LEGOENTITY_H
#define LEGOENTITY_H

#include "decomp.h"
#include "extra.h"
#include "mxentity.h"

class LegoROI;
class MxDSAction;
class Vector3;

/// @brief [AI] Represents an entity that can be placed and managed in the LEGO Island world.
/// This class handles 3D transformation, linkage to a 3D object instance (ROI), script/action parsing,
/// audio/animation switching behaviors, and other entity-driven event responses. Derived from MxEntity.
/// [AI]
class LegoEntity : public MxEntity {
public:
	/// @brief [AI] Types of LegoEntity (Actor, Plant, Building, Auto ROI, etc.) [AI]
	enum Type {
		e_actor = 0,     ///< [AI] Standard character entity controlled by scripts or user [AI]
		e_unk1,          ///< [AI_SUGGESTED_NAME: e_unknown1] Reserved or unused, purpose unclear [AI]
		e_plant,         ///< [AI] Plant objects in the game (e.g., trees or bushes) [AI]
		e_building,      ///< [AI] Building entities, usually interactable or decorations [AI]
		e_autoROI        ///< [AI] Catchall for ROI-adapted/unknown entities [AI]
	};

	/// @brief [AI] Bit flag constants for entity state management [AI]
	enum {
		c_bit1 = 0x01,          ///< [AI] Used internally for ROI/entity ownership tracking [AI]
		c_managerOwned = 0x02   ///< [AI] Indicates this entity is managed/owned by an entity manager [AI]
	};

	/// @brief [AI] Secondary bit flag constants [AI]
	enum {
		c_altBit1 = 0x01        ///< [AI] Used to prevent repeat sound/animation actions while one is in progress [AI]
	};

	/// @brief [AI] Default constructor. Initializes the LegoEntity with default values. [AI]
	LegoEntity() { Init(); }

	/// @brief [AI] Destructor. Cleans up resources and ensures ROI and script state are released. [AI]
	// FUNCTION: LEGO1 0x1000c290
	~LegoEntity() override { Destroy(TRUE); }

	/// @brief [AI] Handles event notification for the entity, most notably user clicks, using polymorphic dispatch.
	/// @details [AI] If an actionable event is received, invokes script-driven or context-specific action.
	/// @param p_param Parameter dispatch object, expected to reference LegoEventNotificationParam. [AI]
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// @brief [AI] Returns the class name string. Used in entity runtime type identification. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0064
		return "LegoEntity";
	}

	/// @brief [AI] Polymorphic type check for this entity given a string. [AI]
	/// @param p_name Name of class to check. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoEntity::ClassName()) || MxEntity::IsA(p_name);
	}

	/// @brief [AI] Initializes the entity from a DSAction object, typically from a script or file load. [AI]
	/// @param p_dsAction The source action to initialize from. [AI]
	virtual MxResult Create(MxDSAction& p_dsAction);                     // vtable+0x18

	/// @brief [AI] Cleans up the entity, detaching ROI and releasing references. [AI]
	/// @param p_fromDestructor True if called from destructor. [AI]
	virtual void Destroy(MxBool p_fromDestructor);                       // vtable+0x1c

	/// @brief [AI] Parses an action description string (usually from script "extra" data) and sets up this entity's action state.
	/// @param p_extra String with the action command to parse. Example: "ACTION:<action>; <filename>; <entity-id>". [AI]
	virtual void ParseAction(char* p_extra);                             // vtable+0x20

	/// @brief [AI] Assigns a 3D ROI (3D object instance) to this entity, controlling how it appears/acts in the world.
	/// @param p_roi ROI pointer to assign. [AI]
	/// @param p_bool1 Whether to clear or set a specific flag after setting the ROI. [AI]
	/// @param p_bool2 If true, updates the ROI transformation to match current world state. [AI]
	virtual void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2); // vtable+0x24

	/// @brief [AI] Explicitly sets the world transformation (location, direction, up vector) for this entity.
	/// @param p_location New world location. [AI]
	/// @param p_direction New world direction vector. [AI]
	/// @param p_up New world up vector. [AI]
	virtual void SetWorldTransform(
		const Vector3& p_location,
		const Vector3& p_direction,
		const Vector3& p_up
	);                                                     // vtable+0x28

	/// @brief [AI] Resets the transformation for this entity (e.g., used with camera transitions).
	/// @param p_cameraFlag Whether this entity should act as the camera controller target. [AI]
	virtual void ResetWorldTransform(MxBool p_cameraFlag); // vtable+0x2c

	/// @brief [AI] Sets the current world speed value for this entity (used to control motion/animation rate). [AI]
	/// @param p_worldSpeed New world speed value. [AI]
	virtual void SetWorldSpeed(MxFloat p_worldSpeed) { m_worldSpeed = p_worldSpeed; } // vtable+0x30

	/// @brief [AI] Plays a click sound, typically in response to user/AI actions, according to entity type.
	/// @param p_und Determines variant/alternate sound or behavior. [AI]
	virtual void ClickSound(MxBool p_und);    // vtable+0x34

	/// @brief [AI] Plays a context-sensitive click animation, driven by current entity type and state. [AI]
	virtual void ClickAnimation();            // vtable+0x38

	/// @brief [AI] Switches variants for this entity (e.g., different animation, mesh, or texture variant), based on type. [AI]
	virtual void SwitchVariant();             // vtable+0x3c

	/// @brief [AI] Triggers a context-dependent audio/sound variant switch for this entity. [AI]
	virtual void SwitchSound();               // vtable+0x40

	/// @brief [AI] Switches movement/animation variant for this entity, if applicable (e.g., walking/running state). [AI]
	virtual void SwitchMove();                // vtable+0x44

	/// @brief [AI] Switches the color or texture variant for this entity (or target ROI). [AI]
	/// @param p_roi Optional: target LegoROI for color/texture switching. [AI]
	virtual void SwitchColor(LegoROI* p_roi); // vtable+0x48

	/// @brief [AI] Triggers a mood/state switch for this entity (if supported), often for characters. [AI]
	virtual void SwitchMood();                // vtable+0x4c

	/// @brief [AI] Updates the camera transformation when this entity is the camera target. Used after movement or position updates. [AI]
	void FUN_10010c30();

	/// @brief [AI] Sets the entity's type (actor/plant/building/etc.) [AI]
	/// @param p_type Type enumeration value to set. [AI]
	void SetType(MxU8 p_type);

	/// @brief [AI] Sets the world-space location, direction, and up, applying normalization and transformation. [AI]
	/// @param p_location Target location. [AI]
	/// @param p_direction Forward vector (normalized internally). [AI]
	/// @param p_up Up vector (normalized internally). [AI]
	/// @param p_und If true, updates camera transform as well. [AI]
	void SetLocation(const Vector3& p_location, const Vector3& p_direction, const Vector3& p_up, MxBool p_und);

	/// @brief [AI] Gets the normalized world-space direction vector, optionally updating from ROI. [AI]
	Mx3DPointFloat GetWorldDirection();

	/// @brief [AI] Gets the normalized world-space up vector, optionally updating from ROI. [AI]
	Mx3DPointFloat GetWorldUp();

	/// @brief [AI] Gets the world-space position vector, optionally updating from ROI. [AI]
	Mx3DPointFloat GetWorldPosition();

	/// @brief [AI] Checks if a bit flag in m_unk0x10 is set (purpose: state/animation suppression lock). [AI]
	/// @param p_flag Flag value to test. [AI]
	MxBool GetUnknown0x10IsSet(MxU8 p_flag) { return m_unk0x10 & p_flag; }

	/// @brief [AI] Checks if a flag is set in the primary flags byte (m_flags). [AI]
	/// @param p_flag Flag value to test. [AI]
	MxBool GetFlagsIsSet(MxU8 p_flag) { return m_flags & p_flag; }

	/// @brief [AI] Returns the value of the flag byte. [AI]
	MxU8 GetFlags() { return m_flags; }

	/// @brief [AI] Gets the entity's current world speed state. [AI]
	MxFloat GetWorldSpeed() { return m_worldSpeed; }

	/// @brief [AI] Gets the ROI (Realtime Object Instance) associated with this entity. [AI]
	LegoROI* GetROI() { return m_roi; }

	/// @brief [AI] Gets the type of this entity (one of the enum Type values). [AI]
	MxU8 GetType() { return m_type; }

	/// @brief [AI] Returns whether this entity is flagged as camera (affects world/camera synchronization). [AI]
	MxBool GetCameraFlag() { return m_cameraFlag; }

	/// @brief [AI] Sets all entity flags at once (replaces previous). [AI]
	/// @param p_flags Bitfield value to set. [AI]
	void SetFlags(MxU8 p_flags) { m_flags = p_flags; }

	/// @brief [AI] Sets the given flag in the flags byte. [AI]
	/// @param p_flag Bit to set. [AI]
	void SetFlag(MxU8 p_flag) { m_flags |= p_flag; }

	/// @brief [AI] Clears the given flag in the flags byte. [AI]
	/// @param p_flag Bit to clear. [AI]
	void ClearFlag(MxU8 p_flag) { m_flags &= ~p_flag; }

	/// @brief [AI] Sets the given bit in the unknown (usually internal action suppression) flag byte. [AI]
	/// @param p_flag Bit to set. [AI]
	void SetUnknown0x10Flag(MxU8 p_flag) { m_unk0x10 |= p_flag; }

	/// @brief [AI] Clears the given bit in the unknown flag byte. [AI]
	/// @param p_flag Bit to clear. [AI]
	void ClearUnknown0x10Flag(MxU8 p_flag) { m_unk0x10 &= ~p_flag; }

protected:
	/// @brief [AI] Initializes the entity's members to default/neutral values (utility for constructors and resets). [AI]
	void Init();

	/// @brief [AI] Registers/attaches this entity to the current world if not already; called on create or location change. [AI]
	void SetWorld();

	/// @brief [AI] Unknown state/flag, used mainly to guard against repeated actions or manage animation/sound state. [AI]
	MxU8 m_unk0x10;                  // 0x10

	/// @brief [AI] Primary entity flags (bitfield); tracks per-entity management status, internal update locks, etc. [AI]
	MxU8 m_flags;                    // 0x11

	/// @brief [AI] Entity location in world coordinates. [AI]
	Mx3DPointFloat m_worldLocation;  // 0x14

	/// @brief [AI] Entity direction vector in world space (normalized). [AI]
	Mx3DPointFloat m_worldDirection; // 0x28

	/// @brief [AI] Entity up vector in world space (normalized). [AI]
	Mx3DPointFloat m_worldUp;        // 0x3c

	/// @brief [AI] World-relative speed (can affect animation/movement logic). [AI]
	MxFloat m_worldSpeed;            // 0x50

	/// @brief [AI] Pointer to this entity's currently assigned ROI (3D instance in the world). [AI]
	LegoROI* m_roi;                  // 0x54

	/// @brief [AI] Set to TRUE if this entity is currently the camera target. [AI]
	MxBool m_cameraFlag;             // 0x58

	/// @brief [AI] The entity type (Type enum value). [AI]
	MxU8 m_type;                     // 0x59

	/// @brief [AI] Action type, parsed from script/extra string (e.g., openram/run/exit); guides Notify() and click logic. [AI]
	Extra::ActionType m_actionType; // 0x5c

	/// @brief [AI] When parsing ACTION command, this is the SI script/filename to execute (owned, heap-allocated). [AI]
	// variable name verified by BETA10 0x1007eddf
	char* m_siFile; // 0x60

	/// @brief [AI] When parsing ACTION command, this is the target entity ID for the action (or -1 for none). [AI]
	MxS32 m_targetEntityId; // 0x64
};

// SYNTHETIC: LEGO1 0x1000c3b0
// LegoEntity::`scalar deleting destructor'

#endif // LEGOENTITY_H
