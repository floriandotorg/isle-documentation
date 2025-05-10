#ifndef __LEGOANIM_H
#define __LEGOANIM_H

#include "decomp.h"
#include "misc/legostorage.h"
#include "misc/legotree.h"

class Matrix4;

/// @brief [AI] Represents a single generic animation keyframe, containing timing and per-keyframe flags.
/// @details [AI] LegoAnimKey is the base class for all key types (translation, rotation, scale, morph, unknown), encapsulating time and flags for interpolation and animation processing.
class LegoAnimKey {
public:
	/// @brief [AI] Bitmask flag definitions for animation keys.
	enum Flags {
		c_bit1 = 0x01, ///< [AI] Indicates if the key affects the output (meaning depends on derived type).
		c_bit2 = 0x02, ///< [AI] Secondary bit, meaning varies by context.
		c_bit3 = 0x04  ///< [AI] Third bit, used for certain special processing during animation.
	};

	LegoAnimKey(); ///< @brief [AI] Constructs an animation key with zero time and cleared flags.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes the animation key from storage. @param p_storage Storage object to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the animation key to storage. @param p_storage Storage object to write to. [AI]
	LegoFloat GetTime() { return m_time; } ///< @brief [AI] Retrieves the time (frame/tick) of this key.

	/// @brief [AI] Sets the key's time (from an integer value, used during deserialization or legacy data).
	void SetTime(MxS32 p_time) { m_time = p_time; }

	LegoU32 TestBit1() { return m_flags & c_bit1; } ///< @brief [AI] Tests if flag bit1 is set.
	LegoU32 TestBit2() { return m_flags & c_bit2; } ///< @brief [AI] Tests if flag bit2 is set.
	LegoU32 TestBit3() { return m_flags & c_bit3; } ///< @brief [AI] Tests if flag bit3 is set.

	/// @brief [AI] Sets or clears bit1 depending on the parameter.
	void FUN_100739a0(MxS32 p_param)
	{
		if (p_param) {
			m_flags |= c_bit1;
		}
		else {
			m_flags &= ~c_bit1;
		}
	}

protected:
	LegoU8 m_flags;   ///< [AI] Flags controlling key behavior or interpolation (see Flags enum).
	LegoFloat m_time; ///< [AI] Time/sample/frame when this key occurs.
};

/// @brief [AI] Animation key class for translations (vector 3D positions).
/// @details [AI] Each key contains X, Y, and Z values, as well as inherited time and flags.
class LegoTranslationKey : public LegoAnimKey {
public:
	LegoTranslationKey(); ///< @brief [AI] Constructs a translation key with all translation components set to zero.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes this translation key from storage. @param p_storage Storage object to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes this translation key to storage. @param p_storage Storage object to write to. [AI]
	LegoFloat GetX() { return m_x; } ///< @brief [AI] Gets the translation X component.
	void SetX(LegoFloat p_x) { m_x = p_x; } ///< @brief [AI] Sets the translation X component.
	LegoFloat GetY() { return m_y; } ///< @brief [AI] Gets the translation Y component.
	void SetY(LegoFloat p_y) { m_y = p_y; } ///< @brief [AI] Sets the translation Y component.
	LegoFloat GetZ() { return m_z; } ///< @brief [AI] Gets the translation Z component.
	void SetZ(LegoFloat p_z) { m_z = p_z; } ///< @brief [AI] Sets the translation Z component.

protected:
	LegoFloat m_x; ///< [AI] Translation along X-axis.
	LegoFloat m_y; ///< [AI] Translation along Y-axis.
	LegoFloat m_z; ///< [AI] Translation along Z-axis.
};

/// @brief [AI] Animation key class for rotations (axis-angle format).
/// @details [AI] Contains axis (X, Y, Z) and angle (radians or normalized value), defining a rotation to be interpolated.
class LegoRotationKey : public LegoAnimKey {
public:
	LegoRotationKey(); ///< @brief [AI] Constructs a rotation key with default (identity) rotation.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes the rotation key from storage. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the rotation key to storage. @param p_storage Storage to write to. [AI]

	LegoFloat GetAngle() { return m_angle; } ///< @brief [AI] Gets the rotation angle (around the axis).
	void SetAngle(LegoFloat p_angle) { m_angle = p_angle; } ///< @brief [AI] Sets the rotation angle.
	LegoFloat GetX() { return m_x; } ///< @brief [AI] Gets the X-axis of the rotation.
	void SetX(LegoFloat p_x) { m_x = p_x; } ///< @brief [AI] Sets the X-axis of the rotation.
	LegoFloat GetY() { return m_y; } ///< @brief [AI] Gets the Y-axis of the rotation.
	void SetY(LegoFloat p_y) { m_y = p_y; } ///< @brief [AI] Sets the Y-axis of the rotation.
	LegoFloat GetZ() { return m_z; } ///< @brief [AI] Gets the Z-axis of the rotation.
	void SetZ(LegoFloat p_z) { m_z = p_z; } ///< @brief [AI] Sets the Z-axis of the rotation.

protected:
	LegoFloat m_angle; ///< [AI] Axis-angle rotation: the angle value.
	LegoFloat m_x;     ///< [AI] Axis-angle rotation: X component.
	LegoFloat m_y;     ///< [AI] Axis-angle rotation: Y component.
	LegoFloat m_z;     ///< [AI] Axis-angle rotation: Z component.
};

/// @brief [AI] Animation key class for scaling transformations.
/// @details [AI] Contains scaling factors for X, Y, and Z axes.
class LegoScaleKey : public LegoAnimKey {
public:
	LegoScaleKey(); ///< @brief [AI] Constructs a scale key (default: scale factor 1,1,1).
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes the scale key from storage. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the scale key to storage. @param p_storage Storage to write to. [AI]
	LegoFloat GetX() { return m_x; } ///< @brief [AI] Gets the scaling X factor.
	void SetX(LegoFloat p_x) { m_x = p_x; } ///< @brief [AI] Sets the scaling X factor.
	LegoFloat GetY() { return m_y; } ///< @brief [AI] Gets the scaling Y factor.
	void SetY(LegoFloat p_y) { m_y = p_y; } ///< @brief [AI] Sets the scaling Y factor.
	LegoFloat GetZ() { return m_z; } ///< @brief [AI] Gets the scaling Z factor.
	void SetZ(LegoFloat p_z) { m_z = p_z; } ///< @brief [AI] Sets the scaling Z factor.

protected:
	LegoFloat m_x; ///< [AI] Scale along the X-axis.
	LegoFloat m_y; ///< [AI] Scale along the Y-axis.
	LegoFloat m_z; ///< [AI] Scale along the Z-axis.
};

/// @brief [AI] Animation key for morphing states or mesh morphing.
/// @details [AI] Encodes a Boolean morph state (purpose unknown but is interpolated in animations).
class LegoMorphKey : public LegoAnimKey {
public:
	LegoMorphKey(); ///< @brief [AI] Constructs a morph key with an unset ("off") state.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes the morph key from storage. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the morph key to storage. @param p_storage Storage to write to. [AI]
	LegoBool GetUnknown0x08() { return m_unk0x08; } ///< @brief [AI] Gets the morph Boolean value (meaning unknown).
	void SetUnknown0x08(LegoBool p_unk0x08) { m_unk0x08 = p_unk0x08; } ///< @brief [AI] Sets the morph Boolean value (meaning unknown).

protected:
	LegoBool m_unk0x08; ///< [AI][AI_SUGGESTED_NAME: m_morphState] Morphing state or flag at this key (meaning unknown).
};

/// @brief [AI] Animation key of unknown type, used internally by camera/track animation.
/// @details [AI] Only contains a single float; used for Z axis as angle in LegoAnimScene.
class LegoUnknownKey : public LegoAnimKey {
public:
	LegoUnknownKey(); ///< @brief [AI] Constructs the unknown key, initializing value to zero.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Deserializes the unknown key from storage. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the unknown key to storage. @param p_storage Storage to write to. [AI]

	LegoFloat GetZ() { return m_z; } ///< @brief [AI] Gets the Z/angle value (usage specific to context).

protected:
	LegoFloat m_z; ///< [AI][AI_SUGGESTED_NAME: m_angleOrZ] Tracks either a Z translation or angle for camera movement.
};

/// @brief [AI] Holds per-node animation data for a model's animation tree.
/// @details [AI] Contains keyframe arrays for translation, rotation, scale, and morph animations, plus per-node name and anonymous flags. Provides transformation generation for a given time.
/// Inherits from LegoTreeNodeData, fitting into a hierarchical animation structure.
class LegoAnimNodeData : public LegoTreeNodeData {
public:
	LegoAnimNodeData(); ///< @brief [AI] Default-initializes all animation key counts to zero and pointers to NULL. [AI]
	~LegoAnimNodeData() override; ///< @brief [AI] Cleans up all allocated animation key arrays and the node name. [AI]
	LegoResult Read(LegoStorage* p_storage) override;  ///< @brief [AI] Reads all node keyframe arrays, name, and meta from storage. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage) override; ///< @brief [AI] Writes all node keyframe arrays, name, and meta to storage. @param p_storage Storage to write to. [AI]

	/// @brief [AI] Sets the node's name (deep-copies string).
	void SetName(LegoChar* p_name);

	/// @brief [AI] Computes the interpolated local transformation matrix for this node at the given animation time.
	/// @param p_time Time to evaluate animation at [AI]
	/// @param p_matrix Resulting local transformation matrix [AI]
	LegoResult CreateLocalTransform(LegoFloat p_time, Matrix4& p_matrix);

	/// @brief [AI] Evaluates morph keys at the given animation time and returns result (typically affects mesh shape or blend shape state).
	/// @param p_time Time to evaluate morph at [AI]
	LegoBool FUN_100a0990(LegoFloat p_time);

	LegoChar* GetName() { return m_name; } ///< @brief [AI] Name of this animation node (used for lookup/mapping to scene graph).
	LegoU16 GetNumTranslationKeys() { return m_numTranslationKeys; } ///< @brief [AI] Number of translation keys for this node.
	LegoU16 GetNumRotationKeys() { return m_numRotationKeys; } ///< @brief [AI] Number of rotation keys for this node.
	void SetNumRotationKeys(LegoU16 p_numRotationKeys) { m_numRotationKeys = p_numRotationKeys; } ///< @brief [AI] Sets the number of rotation keys for this node.

	/// @brief [AI] Sets the node's rotation keys array, resets rotation index.
	void SetRotationKeys(LegoRotationKey* p_keys)
	{
		m_rotationKeys = p_keys;
		m_rotationIndex = 0;
	}

	LegoU32 GetTranslationIndex() { return m_translationIndex; } ///< @brief [AI] Gets last used/optimized translation index for interpolation.
	LegoU32 GetRotationIndex() { return m_rotationIndex; } ///< @brief [AI] Gets last used/optimized rotation index for interpolation.
	LegoU32 GetScaleIndex() { return m_scaleIndex; } ///< @brief [AI] Gets last used/optimized scale index for interpolation.
	LegoU32 GetMorphIndex() { return m_morphIndex; } ///< @brief [AI] Gets last used/optimized morph index for interpolation.

	LegoU16 GetUnknown0x20() { return m_unk0x20; } ///< @brief [AI] Unknown, used in scene/camera calculations (purpose unclear).
	LegoU16 GetUnknown0x22() { return m_unk0x22; } ///< @brief [AI] Unknown, used in scene/camera calculations (purpose unclear).

	/// @brief [AI] Access a pointer to the i-th rotation key.
	/// @param index Array index (0-based) [AI]
	LegoRotationKey* GetRotationKey(MxS32 index) { return &m_rotationKeys[index]; }

	void SetTranslationIndex(LegoU32 p_translationIndex) { m_translationIndex = p_translationIndex; } ///< @brief [AI] Sets last used translation index.
	void SetRotationIndex(LegoU32 p_rotationIndex) { m_rotationIndex = p_rotationIndex; } ///< @brief [AI] Sets last used rotation index.
	void SetScaleIndex(LegoU32 p_scaleIndex) { m_scaleIndex = p_scaleIndex; } ///< @brief [AI] Sets last used scale index.
	void SetMorphIndex(LegoU32 p_morphIndex) { m_morphIndex = p_morphIndex; } ///< @brief [AI] Sets last used morph index.

	LegoMorphKey* GetMorphKeys() { return m_morphKeys; } ///< @brief [AI] Returns pointer to morph keyframes array.
	void SetMorphKeys(LegoMorphKey* p_morphKeys)
	{
		m_morphKeys = p_morphKeys;
		m_morphIndex = 0;
	}

	void SetNumMorphKeys(LegoU16 p_numMorphKeys) { m_numMorphKeys = p_numMorphKeys; } ///< @brief [AI] Sets morph key count.
	void SetUnknown0x20(LegoU16 p_unk0x20) { m_unk0x20 = p_unk0x20; } ///< @brief [AI] Sets unknown parameter (possibly camera/scene state).
	void SetUnknown0x22(LegoU16 p_unk0x22) { m_unk0x22 = p_unk0x22; } ///< @brief [AI] Sets unknown parameter (possibly camera/scene state).

	/// @brief [AI] Convenience: overloaded CreateLocalTransform for time in integer time units.
	/// @param p_time Animation time (integer) [AI]
	/// @param p_matrix Result matrix [AI]
	LegoResult CreateLocalTransform(LegoTime p_time, Matrix4& p_matrix)
	{
		return CreateLocalTransform((LegoFloat) p_time, p_matrix);
	}

	/// @brief [AI] Convenience: evaluate morph state at integer time value.
	LegoBool FUN_100a0990(LegoTime p_time) { return FUN_100a0990((LegoFloat) p_time); }

	/// @brief [AI] Computes interpolated translation for a node at specified time, filling p_matrix.
	/// @param p_numTranslationKeys Count of translation keys in array [AI]
	/// @param p_translationKeys Translation keys array [AI]
	/// @param p_time Animation time [AI]
	/// @param p_matrix Matrix to be set [AI]
	/// @param p_old_index Key search starting index (pass in/out optimized for playback) [AI]
	inline static void GetTranslation(
		LegoU16 p_numTranslationKeys,
		LegoTranslationKey* p_translationKeys,
		LegoFloat p_time,
		Matrix4& p_matrix,
		LegoU32& p_old_index
	);

	/// @brief [AI] Computes interpolated rotation at a given time, filling p_matrix.
	/// @param p_numRotationKeys Count of rotation keys [AI]
	/// @param p_rotationKeys Rotation keys array [AI]
	/// @param p_time Animation time [AI]
	/// @param p_matrix Matrix to set [AI]
	/// @param p_old_index Key search starting index (pass in/out) [AI]
	static void GetRotation(
		LegoU16 p_numRotationKeys,
		LegoRotationKey* p_rotationKeys,
		LegoFloat p_time,
		Matrix4& p_matrix,
		LegoU32& p_old_index
	);

	/// @brief [AI] Computes interpolated scaling on a node at given time, updating p_matrix.
	/// @param p_numScaleKeys Number of scale keys [AI]
	/// @param p_scaleKeys Scale keys array [AI]
	/// @param p_time Animation time [AI]
	/// @param p_matrix Matrix to update [AI]
	/// @param p_old_index Key search starting index (pass in/out) [AI]
	inline static void GetScale(
		LegoU16 p_numScaleKeys,
		LegoScaleKey* p_scaleKeys,
		LegoFloat p_time,
		Matrix4& p_matrix,
		LegoU32& p_old_index
	);

	/// @brief [AI] Performs linear interpolation between two key values for the given time.
	/// @param p_time Current animation time [AI]
	/// @param p_key1 First keyframe [AI]
	/// @param p_value1 Value at first keyframe [AI]
	/// @param p_key2 Second keyframe [AI]
	/// @param p_value2 Value at second keyframe [AI]
	inline static LegoFloat Interpolate(
		LegoFloat p_time,
		LegoAnimKey& p_key1,
		LegoFloat p_value1,
		LegoAnimKey& p_key2,
		LegoFloat p_value2
	);

	/// @brief [AI] Retrieves a reference to the p_i-th LegoAnimKey of given size.
	/// @param p_i Array index [AI]
	/// @param p_keys Start of keyframe array [AI]
	/// @param p_size Stride/size of each keyframe [AI]
	inline static LegoAnimKey& GetKey(LegoU32 p_i, LegoAnimKey* p_keys, LegoU32 p_size);

	/// @brief [AI] Finds surrounding key(s) for interpolation at p_time.
	/// @param p_time Current animation time [AI]
	/// @param p_numKeys Number of keys in array [AI]
	/// @param p_keys Key array [AI]
	/// @param p_size Stride/size of keys [AI]
	/// @param p_new_index Resulting key index [AI]
	/// @param p_old_index Key search starting index (in/out) [AI]
	/// @return Number of keys found: 0 (none), 1 (exact), or 2 (between) [AI]
	static LegoU32 FindKeys(
		LegoFloat p_time,
		LegoU32 p_numKeys,
		LegoAnimKey* p_keys,
		LegoU32 p_size,
		LegoU32& p_new_index,
		LegoU32& p_old_index
	);

protected:
	LegoChar* m_name;                      ///< [AI] Animation node name.
	LegoU16 m_numTranslationKeys;          ///< [AI] Number of translation keyframes.
	LegoU16 m_numRotationKeys;             ///< [AI] Number of rotation keyframes.
	LegoU16 m_numScaleKeys;                ///< [AI] Number of scale keyframes.
	LegoU16 m_numMorphKeys;                ///< [AI] Number of morph keyframes.
	LegoTranslationKey* m_translationKeys; ///< [AI] Array of translation keyframes.
	LegoRotationKey* m_rotationKeys;       ///< [AI] Array of rotation keyframes.
	LegoScaleKey* m_scaleKeys;             ///< [AI] Array of scale keyframes.
	LegoMorphKey* m_morphKeys;             ///< [AI] Array of morph keyframes.
	LegoU16 m_unk0x20;                     ///< [AI] Unknown, used in camera/scene morph/rotation (purpose unclear).
	LegoU16 m_unk0x22;                     ///< [AI] Unknown, used in camera/scene morph/rotation (purpose unclear).
	LegoU32 m_translationIndex;            ///< [AI] Index cache for optimized translation lookup/interpolation.
	LegoU32 m_rotationIndex;               ///< [AI] Index cache for optimized rotation lookup/interpolation.
	LegoU32 m_scaleIndex;                  ///< [AI] Index cache for optimized scale lookup/interpolation.
	LegoU32 m_morphIndex;                  ///< [AI] Index cache for optimized morph lookup/interpolation.
};

/// @brief [AI] Describes a single actor or model referenced by an animation.
/// @details [AI] Holds the actor/model name and an unknown value (typically a per-actor property).
struct LegoAnimActorEntry {
	LegoChar* m_name;     ///< [AI] Name of the actor/model.
	undefined4 m_unk0x04; ///< [AI] Unknown. May refer to a flag, index, or property (purpose unclear). [AI_SUGGESTED_NAME: m_actorProperty]
};

/// @brief [AI] Represents an animation scene; possibly used for camera motion or global transforms.
/// @details [AI] Contains multiple keyframe streams and other data for animating scene-level properties, such as camera movement, or track movement for cutscenes.
/// See usage in LegoAnim for details.
class LegoAnimScene {
public:
	LegoAnimScene(); ///< @brief [AI] Default construction, zeroes all data pointers and counters.
	~LegoAnimScene(); ///< @brief [AI] Destroys the scene, frees all allocated key arrays.
	LegoResult Read(LegoStorage* p_storage); ///< @brief [AI] Reads the entire scene data from storage, including all translation/unknown key arrays. @param p_storage Storage to read from. [AI]
	LegoResult Write(LegoStorage* p_storage); ///< @brief [AI] Serializes the entire scene data to storage, including all translation/unknown key arrays. @param p_storage Storage to write to. [AI]

	/// @brief [AI] Evaluates this scene's animation at the given time, updating the passed matrix.
	/// @param p_time Time to evaluate at [AI]
	/// @param p_matrix Output matrix [AI]
	LegoResult FUN_1009f490(LegoFloat p_time, Matrix4& p_matrix);

	LegoU32 GetUnknown0x18() { return m_unk0x18; } ///< @brief [AI] Cached index for translation key interpolation (for first translation key array).
	LegoU32 GetUnknown0x1c() { return m_unk0x1c; } ///< @brief [AI] Cached index for translation key interpolation (for second translation key array).
	LegoU32 GetUnknown0x20() { return m_unk0x20; } ///< @brief [AI] Cached index for unknown key interpolation.

	void SetUnknown0x18(LegoU32 p_unk0x18) { m_unk0x18 = p_unk0x18; } ///< @brief [AI] Sets cached translation index (first stream).
	void SetUnknown0x1c(LegoU32 p_unk0x1c) { m_unk0x1c = p_unk0x1c; } ///< @brief [AI] Sets cached translation index (second stream).
	void SetUnknown0x20(LegoU32 p_unk0x20) { m_unk0x20 = p_unk0x20; } ///< @brief [AI] Sets cached key interpolation index (unknown key type).

private:
	LegoU16 m_unk0x00;             ///< [AI] Number of elements in m_unk0x04. [AI_SUGGESTED_NAME: m_numTranslation0Keys]
	LegoTranslationKey* m_unk0x04; ///< [AI] First translation track/key array. [AI_SUGGESTED_NAME: m_translation0Keys]
	LegoU16 m_unk0x08;             ///< [AI] Number of elements in m_unk0x0c. [AI_SUGGESTED_NAME: m_numTranslation1Keys]
	LegoTranslationKey* m_unk0x0c; ///< [AI] Second translation track/key array. [AI_SUGGESTED_NAME: m_translation1Keys]
	LegoU16 m_unk0x10;             ///< [AI] Number of elements in m_unk0x14. [AI_SUGGESTED_NAME: m_numAngleKeys]
	LegoUnknownKey* m_unk0x14;     ///< [AI] Array of angle keys (used for Z angle/camera rotation).
	LegoU32 m_unk0x18;             ///< [AI] Index cache for optimized interpolation (first translation).
	LegoU32 m_unk0x1c;             ///< [AI] Index cache for optimized interpolation (second translation).
	LegoU32 m_unk0x20;             ///< [AI] Index cache for angle interpolation.
};

/// @brief [AI] Root class for all node-based animation blending/structure.
/// @details [AI] Contains top-level control over all node animation for a scene or model.
/// Includes list of animated model actors and (optionally) a camera or scene animation track.
class LegoAnim : public LegoTree {
public:
	LegoAnim(); ///< @brief [AI] Constructs an empty animation object, with no actors or tracks.
	~LegoAnim() override; ///< @brief [AI] Destructor, deallocates actors and camera animation.

	LegoTime GetDuration() { return m_duration; } ///< @brief [AI] Duration (in time units) of the animation.
	LegoU32 GetNumActors() { return m_numActors; } ///< @brief [AI] Number of animated actors/models in the animation.
	LegoResult Write(LegoStorage* p_storage) override; ///< @brief [AI] Serializes all model and animation data to storage.

	/// @brief [AI] Loads model and animation data from storage, optionally including scene/camera animation.
	/// @param p_storage Storage object to read from [AI]
	/// @param p_parseScene If nonzero, also loads and parses the camera/scene animation [AI]
	virtual LegoResult Read(LegoStorage* p_storage, LegoS32 p_parseScene);

	/// @brief [AI] Gets the name of the actor at a given index.
	/// @param p_index Actor index [AI]
	const LegoChar* GetActorName(LegoU32 p_index);

	/// @brief [AI] Gets the actor's "unk0x04" property at a given index. [AI_SUGGESTED_NAME: GetActorProperty]
	/// @param p_index Actor index [AI]
	undefined4 GetActorUnknown0x04(LegoU32 p_index);

	LegoAnimScene* GetCamAnim() { return m_camAnim; } ///< @brief [AI] Gets the optional camera/scene animation track.

protected:
	LegoTime m_duration;             ///< [AI] Animation duration in time units.
	LegoAnimActorEntry* m_modelList; ///< [AI] Array of actor/model entries animated by this object.
	LegoU32 m_numActors;             ///< [AI] Number of actors/models.
	LegoAnimScene* m_camAnim;        ///< [AI] Pointer to camera/scene animation (may be nullptr).

	/// @brief [AI] Creates a node data instance for the animation tree nodes (factory method).
	LegoTreeNodeData* CreateData() override { return new LegoAnimNodeData(); }
};

#endif // __LEGOANIM_H