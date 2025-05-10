#ifndef MXGEOMETRY3D_H
#define MXGEOMETRY3D_H

#include "decomp.h"
#include "realtime/vector3d.inl.h"

// VTABLE: LEGO1 0x100d4488
// VTABLE: BETA10 0x101b84d0
// SIZE 0x14
/**
 * @brief [AI] Represents a 3D point with floating-point precision, inheriting from Vector3. Used throughout the LEGO Island engine to denote world positions, directions and vectors in 3D space. [AI]
 * @details [AI] This class is often used as an interchangeable type with Vector3, but is promoted to a full class to allow explicit semantic usage for points versus general 3D vectors. [AI]
 */
class Mx3DPointFloat : public Vector3 {
public:
	/**
	 * @brief [AI] Constructs a zero-initialized 3D point at the origin (0, 0, 0). [AI]
	 */
	Mx3DPointFloat() : Vector3(m_elements) {}

	/**
	 * @brief [AI] Constructs a 3D point with supplied X, Y, and Z coordinates. [AI]
	 * @param p_x The X component of the point. [AI]
	 * @param p_y The Y component of the point. [AI]
	 * @param p_z The Z component of the point. [AI]
	 */
	Mx3DPointFloat(float p_x, float p_y, float p_z) : Vector3(m_elements)
	{
		m_elements[0] = p_x;
		m_elements[1] = p_y;
		m_elements[2] = p_z;
	}

	/**
	 * @brief [AI] Copy constructor from another Mx3DPointFloat. [AI]
	 * @param p_other The source Mx3DPointFloat to copy from. [AI]
	 */
	Mx3DPointFloat(const Mx3DPointFloat& p_other) : Vector3(m_elements) { EqualsImpl(p_other.m_data); }

	/**
	 * @brief [AI] Constructs from a generic Vector3, treating it as a 3D point. [AI]
	 * @param p_other The Vector3 whose values will be copied. [AI]
	 */
	Mx3DPointFloat(const Vector3& p_other) : Vector3(m_elements) { EqualsImpl(p_other.m_data); }

	/**
	 * @brief [AI] Assignment operator copies the content of a Vector3 into this point. [AI]
	 * @param p_impl The Vector3 to copy values from. [AI]
	 */
	virtual void operator=(const Vector3& p_impl) { EqualsImpl(p_impl.m_data); } // vtable+0x88

	/**
	 * @brief [AI] Accesses a component (X/Y/Z) of the point for modification. [AI]
	 * @param idx The index (0: X, 1: Y, 2: Z) [AI]
	 * @return Reference to the component's value. [AI]
	 */
	float& operator[](int idx) { return m_data[idx]; }

	/**
	 * @brief [AI] Accesses a component (X/Y/Z) of the point as a constant value. [AI]
	 * @param idx The index (0: X, 1: Y, 2: Z) [AI]
	 * @return Const reference to the component's value. [AI]
	 */
	const float& operator[](int idx) const { return m_data[idx]; }

	// SYNTHETIC: LEGO1 0x10010c00
	// SYNTHETIC: BETA10 0x10015240
	// ??4Mx3DPointFloat@@QAEAAV0@ABV0@@Z

private:
	/**
	 * @brief [AI] Internal storage for the three floating-point components of the point (X, Y, Z). Used by the base class and this class for vector math and position representation. [AI]
	 */
	float m_elements[3]; // 0x08
};

#endif // MXGEOMETRY3D_H
