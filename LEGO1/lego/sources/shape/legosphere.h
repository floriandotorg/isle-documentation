#ifndef __LEGOSPHERE_H
#define __LEGOSPHERE_H

#include "legovertex.h"

// SIZE 0x10

/**
 * @brief [AI] Represents a sphere in 3D space, used for bounding volume calculations and spatial queries. 
 * @details [AI] The class contains a center vertex and a floating-point radius. This is commonly used in collision detection,
 * bounding volume hierarchies, view frustum culling, and other 3D spatial operations to efficiently represent and test spherical areas.
 */
class LegoSphere {
public:
	/**
	 * @brief [AI] Default constructor initializing the sphere with zero radius.
	 * @details [AI] The center vertex is implicitly constructed, and the radius is set to 0.0f.
	 */
	LegoSphere() { m_radius = 0.0F; }

	/**
	 * @brief [AI] Returns a reference to the center vertex of the sphere.
	 * @return [AI] Reference to the m_center member containing the 3D center coordinate.
	 */
	LegoVertex& GetCenter() { return m_center; }

	/**
	 * @brief [AI] Sets the center of the sphere to the specified vertex.
	 * @param p_center The new center position. [AI]
	 */
	void SetCenter(LegoVertex& p_center) { m_center = p_center; }

	/**
	 * @brief [AI] Retrieves the current radius of the sphere.
	 * @return [AI] The radius (float) of the sphere.
	 */
	LegoFloat GetRadius() { return m_radius; }

	/**
	 * @brief [AI] Sets the radius to the specified value.
	 * @param p_radius The new radius. [AI]
	 */
	void SetRadius(LegoFloat p_radius) { m_radius = p_radius; }

	/**
	 * @brief [AI] Reads the center and radius of the sphere from a binary storage source.
	 * @param p_storage The storage object to read from. [AI]
	 * @details [AI] This method first calls the center's Read method, then reads the raw binary value for radius.
	 * @return [AI] SUCCESS if all data was read correctly; a failure code otherwise.
	 */
	LegoResult Read(LegoStorage* p_storage);

protected:
	LegoVertex m_center; ///< Center position of the sphere in 3D space. [AI]
	LegoFloat m_radius;  ///< Radius of the sphere. [AI]
};

#endif // __LEGOSPHERE_H