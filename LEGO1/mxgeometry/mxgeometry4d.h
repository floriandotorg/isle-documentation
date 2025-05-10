#ifndef MXGEOMETRY4D_H
#define MXGEOMETRY4D_H

#include "decomp.h"
#include "realtime/vector4d.inl.h"

// VTABLE: LEGO1 0x100d41e8
// VTABLE: BETA10 0x101bab78
// SIZE 0x18

/**
 * @brief [AI] 4D point class for floating point values.
 *
 * @details [AI] This class extends the Vector4 class, adding storage for 4D point coordinates using float precision. 
 * It provides various constructors and utility methods to manipulate 4D points, such as setting/getting each coordinate, assignment,
 * and array-style access. This is especially useful in graphics or spatial transformations where a homogeneous coordinate is needed.
 */
class Mx4DPointFloat : public Vector4 {
public:
	/**
     * @brief [AI] Default constructor. Initializes a 4D point with uninitialized elements. [AI]
     * @details [AI] Constructs the base Vector4 with m_elements as storage for coordinate values.
     */
	Mx4DPointFloat() : Vector4(m_elements) {}

	/**
     * @brief [AI] Constructor with explicit coordinates.
     * @param p_x X component. [AI]
     * @param p_y Y component. [AI]
     * @param p_z Z component. [AI]
     * @param p_a 'A' component (homogeneous or fourth dimension). [AI]
     * @details [AI] Initializes the four-dimensional point with given values. Used for direct coordinate control.
     */
	Mx4DPointFloat(float p_x, float p_y, float p_z, float p_a) : Vector4(m_elements)
	{
		m_elements[0] = p_x;
		m_elements[1] = p_y;
		m_elements[2] = p_z;
		m_elements[3] = p_a;
	}

	/**
     * @brief [AI] Copy constructor.
     * @param p_other Instance to copy from. [AI]
     * @details [AI] Initializes the new object by copying all 4 coordinate values from another Mx4DPointFloat.
     */
	Mx4DPointFloat(const Mx4DPointFloat& p_other) : Vector4(m_elements) { EqualsImpl(p_other.m_data); }

	/**
	 * @brief [AI] Assignment operator from a Vector4 object.
	 * @param p_impl The source Vector4 to copy values from. [AI]
	 * @details [AI] Overwrites the current 4D point's data array with another Vector4's components.
	 */
	virtual void operator=(const Vector4& p_impl) { EqualsImpl(p_impl.m_data); } // vtable+0x98

	/**
     * @brief [AI] Array subscript operator for modifiable access.
     * @param idx Index (0-3) for x/y/z/a components. [AI]
     * @return Reference to the requested coordinate component. [AI]
     * @details [AI] Allows for array-style reading and writing of component values, e.g. pt[2] = 4.5f;
     */
	float& operator[](int idx) { return m_data[idx]; }

	// According to the PDB, BETA10 will not link this one if it is never used
	// const float& operator[](int idx) const { return m_data[idx]; }

	/**
     * @brief [AI] Explicit indexed access wrapper (alias for operator[]). [AI]
     * @param idx Index into the four components. [AI]
     * @return Reference to the float component. [AI]
     * @details [AI] Used by several legacy routines, provides alternate access to the data array.
     */
	float& index_operator(int idx) { return m_data[idx]; }

	// SYNTHETIC: LEGO1 0x10064b20
	// SYNTHETIC: BETA10 0x10070420
	// ??4Mx4DPointFloat@@QAEAAV0@ABV0@@Z

private:
	/**
     * @brief [AI] Local storage for the four 32-bit float components (x, y, z, a). [AI]
     * @details [AI] This array provides backing storage for the inherited Vector4 base, used for all component manipulation.
     */
	float m_elements[4]; // 0x08
};

#endif // MXGEOMETRY4D_H
