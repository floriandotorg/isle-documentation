#ifndef MXDSACTION_H
#define MXDSACTION_H

#include "mxdsobject.h"
#include "mxgeometry/mxgeometry3d.h"
#include "mxtypes.h"

class MxOmni;

// VTABLE: LEGO1 0x100dc098
// VTABLE: BETA10 0x101c1b68
// SIZE 0x94
/**
 * @brief [AI] Represents an action deserialized from SI chunks, holding key animation or script parameters such as location, duration, and extra action-specific data.
 * @details [AI] MxDSAction extends MxDSObject and contains information used to control actions in the world, including timing (start time, duration), looping, transformation (location, direction, up), and user-defined "extra" data for further parametrization. Used extensively for scripting animation/logic flows as loaded from SI files. Flags and several unknown fields hint at unimplemented or engine-specific behaviors.
 */
class MxDSAction : public MxDSObject {
public:
	/// @brief [AI] Action bitmask flag options controlling flow (loop, enable, world-space, etc)
	enum {
		c_looping = 0x01,   ///< [AI] Action or media should repeat in a loop [AI]
		c_bit3 = 0x04,      ///< [AI] Unknown - possibly reserved [AI]
		c_bit4 = 0x08,      ///< [AI] Unknown - possibly reserved [AI]
		c_bit5 = 0x10,      ///< [AI] Unknown - possibly reserved [AI]
		c_enabled = 0x20,   ///< [AI] Action is currently enabled [AI]
		c_bit7 = 0x40,      ///< [AI] Unknown - possibly reserved [AI]
		c_world = 0x80,     ///< [AI] Action is described in world-space coordinates [AI]
		c_bit9 = 0x100,     ///< [AI] Unknown - possibly reserved [AI]
		c_bit10 = 0x200,    ///< [AI] Unknown - possibly reserved [AI]
		c_bit11 = 0x400,    ///< [AI] Unknown - possibly reserved [AI]
	};

	/**
	 * @brief [AI] Default constructor. Initializes all fields with default, safe, or sentinel values.
	 * @details [AI] Ensures all primary data members are initialized for deserialization and live-action use.
	 */
	MxDSAction();

	/**
	 * @brief [AI] Destructor. Frees resources held by this action, especially extra data.
	 * @details [AI] Cleans up dynamic memory in m_extraData.
	 */
	~MxDSAction() override;

	/**
	 * @brief [AI] Copy constructor from another MxDSAction
	 * @param p_dsAction Source action to copy from [AI]
	 */
	MxDSAction(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Copies all properties from another MxDSAction (deep copy, including extra data string)
	 * @param p_dsAction Source action to copy from [AI]
	 */
	void CopyFrom(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Assignment operator: deep-copy from a different MxDSAction, including base class data and extra fields.
	 * @param p_dsAction Source action to assign from [AI]
	 * @return Reference to the assigned MxDSAction. [AI]
	 */
	MxDSAction& operator=(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Returns the class name for RTTI or reflection purposes.
	 * @return Null-terminated string with the class name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101013f4
		return "MxDSAction";
	}

	/**
	 * @brief [AI] Run-time type check, compares provided name with this or any ancestor type.
	 * @param p_name Potential class type to match [AI]
	 * @retval TRUE If type or ancestor type matches [AI]
	 * @retval FALSE Otherwise [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSAction::ClassName()) || MxDSObject::IsA(p_name);
	}

	/**
	 * @brief [AI] Unknown virtual placeholder, possibly for additional interfaces. [AI_SUGGESTED_NAME: UnknownVirtual]
	 * @return Unknown 4-byte data from base implementation [AI]
	 */
	undefined4 VTable0x14() override;

	/**
	 * @brief [AI] Serializes the size on disk of this action (all fields + extra data length)
	 * @details [AI] Used for saving/exporting out the action. [AI]
	 */
	MxU32 GetSizeOnDisk() override;

	/**
	 * @brief [AI] Deserializes this action's data from a binary buffer.
	 * @param p_source Buffer (by reference, advances pointer) [AI]
	 * @param p_unk0x24 Flags or mode for deserialization [AI]
	 * @details [AI] Reads all fields, and also appends or loads extra data if present.
	 */
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override;

	/**
	 * @brief [AI] Gets the duration for which this action is intended to run.
	 * @details [AI] Duration is measured in game or media ticks.
	 */
	virtual MxLong GetDuration();

	/**
	 * @brief [AI] Sets the duration of this action in ticks or time units.
	 * @param p_duration The intended duration [AI]
	 */
	virtual void SetDuration(MxLong p_duration);

	/**
	 * @brief [AI] Clones (deep-copies) this action and returns a new pointer.
	 * @details [AI] Extra data and all fields are duplicated.
	 */
	virtual MxDSAction* Clone();

	/**
	 * @brief [AI] Copies/merges properties from another action. Respects special value sentinels to only merge set values.
	 * @param p_dsAction Source action to merge from [AI]
	 * @details [AI] Fields with INT_MIN/FLT_MAX are ignored. Handles extra data concatenation with separator.
	 */
	virtual void MergeFrom(MxDSAction& p_dsAction);

	/**
	 * @brief [AI] Checks if this action contains/was created for a specific SI object id.
	 * @param p_objectId Object id being checked [AI]
	 * @retval TRUE If id matches, FALSE otherwise [AI]
	 */
	virtual MxBool HasId(MxU32 p_objectId);

	/**
	 * @brief [AI] Set unknown value at offset 0x90, used as baseline in GetElapsedTime. [AI_SUGGESTED_NAME: SetStartTimestamp]
	 * @param p_unk0x90 Value to set at 0x90 [AI]
	 */
	virtual void SetUnknown90(MxLong p_unk0x90);

	/**
	 * @brief [AI] Gets the unknown value at offset 0x90, likely a start timestamp. [AI_SUGGESTED_NAME: GetStartTimestamp]
	 * @return Value stored at 0x90 [AI]
	 */
	virtual MxLong GetUnknown90();

	/**
	 * @brief [AI] Gets elapsed time for this action since the last time field 0x90 was set.
	 * @details [AI] Value is determined by current timer - m_unk0x90.
	 */
	virtual MxLong GetElapsedTime();

	/**
	 * @brief [AI] Concatenates or stores extra data associated with this action, robust for multi-part actions.
	 * @param p_extraLength Length of extra data [AI]
	 * @param p_extraData Extra data string or binary blob, not null-terminated [AI]
	 * @details [AI] Used for storing action-specific script or parameter data.
	 */
	void AppendExtra(MxU16 p_extraLength, const char* p_extraData);

	/**
	 * @brief [AI] Retrieves the extra data and its length for this action.
	 * @param[out] p_extraLength The length of extra [AI]
	 * @param[out] p_extraData The pointer to extra data [AI]
	 */
	void GetExtra(MxU16& p_extraLength, char*& p_extraData)
	{
		p_extraLength = m_extraLength;
		p_extraData = m_extraData;
	}

	/**
	 * @brief [AI] Returns the flag field for this action (bitmask).
	 */
	MxU32 GetFlags() { return m_flags; }

	/**
	 * @brief [AI] Sets the flag bitmask controlling action logic (enabled, looping, etc).
	 * @param p_flags Bitmask to set [AI]
	 */
	void SetFlags(MxU32 p_flags) { m_flags = p_flags; }

	/**
	 * @brief [AI] Accessor for extra data (not null-terminated).
	 */
	char* GetExtraData() { return m_extraData; }

	/**
	 * @brief [AI] Returns the length (in bytes) of extra data.
	 */
	MxU16 GetExtraLength() const { return m_extraLength; }

	/**
	 * @brief [AI] Gets the nominal start time for the action, as loaded or scheduled.
	 */
	MxLong GetStartTime() const { return m_startTime; }

	/**
	 * @brief [AI] Returns the loop count for this action. -1 means infinite or not specified.
	 */
	MxS32 GetLoopCount() { return m_loopCount; }

	/**
	 * @brief [AI] Sets the loop count for this action.
	 * @param p_loopCount Value to assign [AI]
	 */
	void SetLoopCount(MxS32 p_loopCount) { m_loopCount = p_loopCount; }

	/**
	 * @brief [AI] Gets the location vector for this action (world or local space).
	 * @details [AI] (x, y, z) in Mx3DPointFloat units.
	 */
	const Vector3& GetLocation() { return m_location; }

	/**
	 * @brief [AI] Gets the direction vector (typically forward vector) for this action.
	 */
	const Vector3& GetDirection() { return m_direction; }

	/**
	 * @brief [AI] Gets the up vector for this action (global or local).
	 */
	const Vector3& GetUp() { return m_up; }

	/**
	 * @brief [AI] Sets the location vector for this action.
	 * @param p_location Location vector [AI]
	 */
	void SetLocation(const Vector3& p_location) { m_location = p_location; }

	/**
	 * @brief [AI] Sets the direction vector for this action.
	 * @param p_direction Direction vector [AI]
	 */
	void SetDirection(const Vector3& p_direction) { m_direction = p_direction; }

	/**
	 * @brief [AI] Sets the up vector for this action.
	 * @param p_up Up vector [AI]
	 */
	void SetUp(const Vector3& p_up) { m_up = p_up; }

	/**
	 * @brief [AI] Returns a pointer to an associated or auxiliary core object. [AI_SUGGESTED_NAME: GetAuxObject]
	 */
	MxCore* GetUnknown84() { return m_unk0x84; }

	/**
	 * @brief [AI] Sets the auxiliary core pointer for this action. [AI_SUGGESTED_NAME: SetAuxObject]
	 * @param p_unk0x84 Object pointer to associate [AI]
	 */
	void SetUnknown84(MxCore* p_unk0x84) { m_unk0x84 = p_unk0x84; }

	/**
	 * @brief [AI] Returns a pointer to the "origin" core object, which may be used to localize the action. [AI_SUGGESTED_NAME: GetOriginCore]
	 */
	MxCore* GetOrigin() { return m_origin; }

	/**
	 * @brief [AI] Sets the origin core pointer for this action, if spatially transforming/localizing this action. [AI_SUGGESTED_NAME: SetOriginCore]
	 * @param p_origin Core object pointer [AI]
	 */
	void SetOrigin(MxCore* p_origin) { m_origin = p_origin; }

	/**
	 * @brief [AI] Whether this action is set to loop based on current flags.
	 */
	MxBool IsLooping() const { return m_flags & c_looping; }

	/**
	 * @brief [AI] Tests for the state of the (unknown purpose) bit 3 flag in m_flags.
	 */
	MxBool IsBit3() const { return m_flags & c_bit3; }

	// SYNTHETIC: LEGO1 0x100ada60
	// SYNTHETIC: BETA10 0x1012be40
	// MxDSAction::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] The size of this action's fields on disk, not counting ancestor size. Used for serialization. [AI]
	 */
	MxU32 m_sizeOnDisk;         // 0x2c

	/**
	 * @brief [AI] Bitfield for flags (enabled, looping, etc). [AI]
	 */
	MxU32 m_flags;              // 0x30

	/**
	 * @brief [AI] Time at which the action is meant to start, or INT_MIN for unset. [AI]
	 */
	MxLong m_startTime;         // 0x34

	/**
	 * @brief [AI] The duration to run the action, or INT_MIN for undefined. [AI]
	 */
	MxLong m_duration;          // 0x38

	/**
	 * @brief [AI] Number of times to repeat the action, or -1 for infinite/not-set. [AI]
	 */
	MxS32 m_loopCount;          // 0x3c

	/**
	 * @brief [AI] Location in 3D world or local space (x, y, z). [AI]
	 */
	Mx3DPointFloat m_location;  // 0x40

	/**
	 * @brief [AI] "Forward" direction vector for this action. [AI]
	 */
	Mx3DPointFloat m_direction; // 0x54

	/**
	 * @brief [AI] "Up" vector for this action. [AI]
	 */
	Mx3DPointFloat m_up;        // 0x68

	/**
	 * @brief [AI] Opaque extra data for custom or extended behavior. [AI]
	 */
	char* m_extraData;          // 0x7c

	/**
	 * @brief [AI] Length of extra data in bytes. [AI]
	 */
	MxU16 m_extraLength;        // 0x80

	/**
	 * @brief [AI] Pointer to an auxiliary MxCore object, purpose unknown. [AI]
	 */
	MxCore* m_unk0x84;          // 0x84

	/**
	 * @brief [AI] 4 bytes at 0x88; usage not known. [AI]
	 */
	undefined4 m_unk0x88;       // 0x88

	/**
	 * @brief [AI] Pointer to an "origin" MxCore object, for spatial/ownership reference. [AI]
	 */
	MxCore* m_origin;           // 0x8c

	/**
	 * @brief [AI] Unknown field, appears to store a timestamp for GetElapsedTime logics. [AI_SUGGESTED_NAME: m_startTimestamp]
	 */
	MxLong m_unk0x90;           // 0x90
};

#endif // MXDSACTION_H
