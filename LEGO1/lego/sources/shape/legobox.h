#ifndef __LEGOBOX_H
#define __LEGOBOX_H

#include "legovertex.h"

// SIZE 0x18
/**
 * @brief [AI] Represents an axis-aligned 3D bounding box, defined by minimum and maximum corners. [AI]
 * @details [AI] The LegoBox class encapsulates an axis-aligned bounding box (AABB) in 3D space. It stores the minimum and maximum vertices, and provides operations for retrieving dimensions, checking for emptiness, and reading its data from storage. [AI]
 */
class LegoBox {
public:
	/**
	 * @brief [AI] Returns a reference to the minimum vertex of the box. [AI]
	 * @return [AI] Reference to the minimum corner vertex. [AI]
	 */
	LegoVertex& GetMin() { return m_min; }

	/**
	 * @brief [AI] Sets the minimum vertex of the box. [AI]
	 * @param p_min The LegoVertex to use as the minimum (corner) of the box. [AI]
	 */
	void SetMin(LegoVertex& p_min) { m_min = p_min; }

	/**
	 * @brief [AI] Returns a reference to the maximum vertex of the box. [AI]
	 * @return [AI] Reference to the maximum corner vertex. [AI]
	 */
	LegoVertex& GetMax() { return m_max; }

	/**
	 * @brief [AI] Sets the maximum vertex of the box. [AI]
	 * @param p_max The LegoVertex to use as the maximum (corner) of the box. [AI]
	 */
	void SetMax(LegoVertex& p_max) { m_max = p_max; }

	// LegoVertex GetCenter()
	// {
	// 	return LegoVertex(
	// 		(m_min.GetX() + m_max.GetX()) / 2,
	// 		(m_min.GetY() + m_max.GetY()) / 2,
	// 		(m_min.GetZ() + m_max.GetZ()) / 2
	// 	);
	// }

	/**
	 * @brief [AI] Calculates the length of the box along the X axis. [AI]
	 * @return [AI] The extent along X (max.x - min.x). [AI]
	 */
	LegoFloat GetDX() { return m_max.GetX() - m_min.GetX(); }

	/**
	 * @brief [AI] Calculates the length of the box along the Y axis. [AI]
	 * @return [AI] The extent along Y (max.y - min.y). [AI]
	 */
	LegoFloat GetDY() { return m_max.GetY() - m_min.GetY(); }

	/**
	 * @brief [AI] Calculates the length of the box along the Z axis. [AI]
	 * @return [AI] The extent along Z (max.z - min.z). [AI]
	 */
	LegoFloat GetDZ() { return m_max.GetZ() - m_min.GetZ(); }

	/**
	 * @brief [AI] Checks if both min and max vertices are set to the origin. [AI]
	 * @return [AI] True if both min and max are at the origin (box is "empty"). [AI]
	 * @details [AI] A box is considered empty if both of its defining vertices are (0,0,0). [AI]
	 */
	LegoBool IsEmpty() { return m_min.IsOrigin() && m_max.IsOrigin(); }

	/**
	 * @brief [AI] Reads the bounding box data from a LegoStorage stream. [AI]
	 * @param p_storage Pointer to the LegoStorage instance to read from. [AI]
	 * @return [AI] Result code indicating success or an error in reading either vertex. [AI]
	 * @details [AI] Calls the Read methods of the min and max vertices in sequence. [AI]
	 */
	LegoResult Read(LegoStorage* p_storage);

protected:
	/**
	 * @brief [AI] Minimum corner of the bounding box. [AI]
	 */
	LegoVertex m_min; // 0x00

	/**
	 * @brief [AI] Maximum corner of the bounding box. [AI]
	 */
	LegoVertex m_max; // 0x0c
};

#endif // __LEGOBOX_H
