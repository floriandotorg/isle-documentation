#ifndef ORIENTABLEROI_H
#define ORIENTABLEROI_H

#include "decomp.h"
#include "mxgeometry/mxmatrix.h"
#include "roi.h"

#include <windows.h>

// VTABLE: LEGO1 0x100dbc08
// SIZE 0xdc

/**
 * @brief [AI] Represents an ROI (Real-time Object Instance) that can be oriented in world space, supporting local-to-world transformations and hierarchical parenting of orientation. Abstract base for objects that require orientation in the LEGO Island engine 3D world.
 * 
 * Inherits from ROI, and adds transformation, orientation, velocity, and bounding volume management.
 * 
 * Main responsibility: Provides transformation (matrix), velocity, and bounding volume handling for objects with orientation (position/rotation), allowing parent-child relationship for local/world calculations.
 * 
 * Notable responsibilities:
 *   - Maintains hierarchy via parent ROI pointer
 *   - Holds a local-to-world matrix for accurate orientation
 *   - Updates bounding box and bounding sphere in world space
 *   - Provides utility operations for transformation propagation and bounding calculations
 * 
 * Abstract: cannot be instantiated; requires children to implement UpdateWorldBoundingVolumes.
 * [AI]
 */
class OrientableROI : public ROI {
public:
	enum {
		/** @brief [AI] Bit mask for internal status flag 1 (see usage in ToggleUnknown0xd8). Meaning unknown. [AI] */
		c_bit1 = 0x01,
		/** @brief [AI] Bit mask for internal status flag 2 (see usage in ToggleUnknown0xd8). Meaning unknown. [AI] */
		c_bit2 = 0x02
	};

	/**
	 * @brief Default constructor. Initializes bounding volumes, velocity, transformation matrix, and parent. [AI]
	 */
	OrientableROI();

	/**
	 * @brief Returns a pointer to the object's velocity vector in world space. [AI]
	 * @return Pointer to float array for velocity. [AI]
	 */
	const float* GetWorldVelocity() const override;

	/**
	 * @brief Returns the object's bounding box in world coordinates. [AI]
	 * @return Reference to world-aligned bounding box. [AI]
	 */
	const BoundingBox& GetWorldBoundingBox() const override;

	/**
	 * @brief Returns the object's bounding sphere in world coordinates. [AI]
	 * @return Reference to world-aligned bounding sphere. [AI]
	 */
	const BoundingSphere& GetWorldBoundingSphere() const override;

	/**
	 * @brief [AI] Calls VTable0x1c(). Default implementation delegates to VTable0x1c. May be overridden by children. [AI]
	 */
	virtual void VTable0x14() { VTable0x1c(); }

	/**
	 * @brief Recalculates all world bounding volumes from the current local-to-world transform. Must be implemented by subclasses. [AI]
	 * 
	 * Typically, this means recalculating m_world_bounding_box and m_world_bounding_sphere after m_local2world changes. [AI]
	 */
	virtual void UpdateWorldBoundingVolumes() = 0;

	/**
	 * @brief [AI] Concrete subclass implementation should implement this to perform post-bounding-volume-change logic. Default calls UpdateWorldBoundingVolumes and UpdateWorldVelocity. [AI]
	 */
	virtual void VTable0x1c();

	/**
	 * @brief Sets the local-to-world transformation matrix directly. [AI]
	 * 
	 * Updates m_local2world and recalculates bounding volumes and velocity. [AI]
	 * @param p_transform New transformation matrix (local-to-world). [AI]
	 */
	virtual void SetLocalTransform(const Matrix4& p_transform);

	/**
	 * @brief Post-multiplies the current local-to-world matrix by p_transform. [AI]
	 * 
	 * This allows relative rotation/translation to be combined. [AI]
	 * @param p_transform Matrix to post-multiply. [AI]
	 */
	virtual void VTable0x24(const Matrix4& p_transform);

	/**
	 * @brief Applies p_transform in (presumably) parent coordinates and updates world data for self and children. [AI]
	 * 
	 * Typical usage: propagate transformation hierarchy. [AI]
	 * @param p_transform Transform to apply in world or parent space. [AI]
	 */
	virtual void UpdateWorldData(const Matrix4& p_transform);

	/**
	 * @brief Updates the world velocity (must be implemented by subclasses if custom velocity logic is needed). [AI]
	 * 
	 * For many objects, may be left empty if not moving. [AI]
	 */
	virtual void UpdateWorldVelocity();

	/**
	 * @brief Wraps SetLocalTransform, for possible override or interface uniformity. [AI]
	 * @param p_transform Matrix to set as local-to-world. [AI]
	 */
	void WrappedSetLocalTransform(const Matrix4& p_transform);

	/**
	 * @brief Calculates and updates the world transform relative to this object's parent, then calls UpdateWorldData. [AI]
	 * @details Used when an object's transform is to be re-parented or altered in the context of another parent. [AI]
	 * @param p_transform Transform relative to parent to be adopted. [AI]
	 */
	void UpdateTransformationRelativeToParent(const Matrix4& p_transform);

	/**
	 * @brief Wraps VTable0x24, possibly for decoupling or uniform invocation. [AI]
	 * @param p_transform Transform to post-multiply. [AI]
	 */
	void WrappedVTable0x24(const Matrix4& p_transform);

	/**
	 * @brief Retrieves the local-to-world transformation, or if there is a parent, computes the transform relative to it. [AI]
	 * 
	 * If the object has a parent, returns the transform needed to reach this object from its parent. [AI]
	 * @param p_transform Matrix to fill with the transform. [AI]
	 */
	void GetLocalTransform(Matrix4& p_transform);

	/**
	 * @brief Assigns the given matrix as the local-to-world transformation and enables some internal flags. [AI]
	 * @param p_transform New local-to-world transformation. [AI]
	 */
	void FUN_100a58f0(const Matrix4& p_transform);

	/**
	 * @brief Sets the world velocity to the provided vector. [AI]
	 * @param p_world_velocity New velocity in world space. [AI]
	 */
	void FUN_100a5a30(const Vector3& p_world_velocity);

	/**
	 * @brief Accessor for the current local-to-world transformation matrix. [AI]
	 * @return Reference to the local-to-world matrix. [AI]
	 */
	const Matrix4& GetLocal2World() const { return m_local2world; }

	/**
	 * @brief Returns a pointer to the world position from the transformation matrix (translation row). [AI]
	 * @return Pointer to the translation component of m_local2world. [AI]
	 */
	const float* GetWorldPosition() const { return m_local2world[3]; }

	/**
	 * @brief Returns a pointer to the world direction vector (forward axis) from the transformation matrix. [AI]
	 * @return Pointer to the direction component of m_local2world. [AI]
	 */
	const float* GetWorldDirection() const { return m_local2world[2]; }

	/**
	 * @brief Returns a pointer to the world up vector from the transformation matrix. [AI]
	 * @return Pointer to the up component of m_local2world. [AI]
	 */
	const float* GetWorldUp() const { return m_local2world[1]; }

	/**
	 * @brief Accessor for the parent ROI in the transformation hierarchy. [AI]
	 * @return OrientableROI pointer for the parent (may be nullptr). [AI]
	 */
	OrientableROI* GetParentROI() const { return m_parentROI; }

	/**
	 * @brief Sets the parent ROI used for transformation hierarchy. [AI]
	 * @param p_parentROI Parent OrientableROI pointer. [AI]
	 */
	void SetParentROI(OrientableROI* p_parentROI) { m_parentROI = p_parentROI; }

	/**
	 * @brief Enables or disables some bitfields in the internal unknown status variable m_unk0xd8. [AI]
	 * 
	 * If enabled, sets both c_bit1 and c_bit2; otherwise only clears c_bit1.
	 * The exact meaning is unknown. [AI]
	 * 
	 * @param p_enable TRUE to enable, FALSE to clear c_bit1. [AI]
	 */
	void ToggleUnknown0xd8(BOOL p_enable)
	{
		if (p_enable) {
			m_unk0xd8 |= c_bit1 | c_bit2;
		}
		else {
			m_unk0xd8 &= ~c_bit1;
		}
	}

protected:
	/**
	 * @brief The transform from local to world space; 4x4 transformation matrix. [AI]
	 */
	MxMatrix m_local2world;                 // 0x10

	/**
	 * @brief The object's axis-aligned bounding box in world space, recalculated as needed. [AI]
	 */
	BoundingBox m_world_bounding_box;       // 0x58

	/**
	 * @brief An unknown bounding box; usage unclear, could be related to extended collision or volume testing. [AI]
	 */
	BoundingBox m_unk0x80;                  // 0x80

	/**
	 * @brief The object's bounding sphere in world space, recalculated from m_local2world. [AI]
	 */
	BoundingSphere m_world_bounding_sphere; // 0xa8

	/**
	 * @brief The object's velocity vector in world coordinates. [AI]
	 */
	Mx3DPointFloat m_world_velocity;        // 0xc0

	/**
	 * @brief If non-null, points to the parent OrientableROI for local/world transformation hierarchy. [AI]
	 */
	OrientableROI* m_parentROI;             // 0xd4

	/**
	 * @brief Unknown status or flag field; bits manipulated via ToggleUnknown0xd8, possibly related to dirty state or internal update need. [AI]
	 */
	undefined4 m_unk0xd8;                   // 0xd8
};

// SYNTHETIC: LEGO1 0x100a4630
// OrientableROI::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100aa2f0
// OrientableROI::~OrientableROI

#endif // ORIENTABLEROI_H
