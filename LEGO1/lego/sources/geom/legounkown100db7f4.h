#ifndef __LEGOUNKNOWN100DB7F4_H
#define __LEGOUNKNOWN100DB7F4_H

#include "legoedge.h"
#include "legowegedge.h"
#include "mxgeometry/mxgeometry3d.h"

#include <assert.h>

// VTABLE: LEGO1 0x100db7f4
// SIZE 0x40

/**
 * @brief [AI] Represents an advanced edge in the LEGO Island geometry system, with direction, flags, and geometric query utilities.
 * @details [AI] This is an extension of LegoEdge, featuring enhanced geometric capabilities. This structure associates an edge with additional information such as directionality (normal vector), flags indicating properties per-face, and several helper functions for geometry intersection and metric queries. Seen in the path- and world-edge system of LEGO Island.
 */
struct LegoUnknown100db7f4 : public LegoEdge {
public:
	/// @brief [AI] Flag values for edge-face properties.
	enum {
		c_bit1 = 0x01, ///< [AI] Bit flag 1 for face B connection/properties
		c_bit2 = 0x02, ///< [AI] Bit flag 2 for face A connection/properties
		c_bit3 = 0x04, ///< [AI] Bit flag 3 (purpose unknown)
		c_bit4 = 0x08  ///< [AI] Bit flag 4 (purpose unknown)
	};

	/**
	 * @brief [AI] Constructs a new edge object with zero-initialized per-face flags and direction/normal vector.
	 */
	LegoUnknown100db7f4();

	/**
	 * @brief [AI] Calculates the edge normal for use from the given face, negating it if called from faceA.
	 * @details [AI] Provides outward-facing edge normal as a vector for the specified edge; reversed for one side, used for collision, lighting, or traversal logic.
	 * @param p_f [AI] The face from which the query is made.
	 * @param p_point [AI] Output vector for the face's normal.
	 * @return Returns SUCCESS on completion. [AI]
	 */
	LegoResult FUN_1002ddc0(LegoWEEdge& p_f, Vector3& p_point) const;

	/**
	 * @brief [AI] Tests whether a WEG-edge meets complex mask and flag criteria for this edge, depending on mask and which face is referenced.
	 * @param p_face [AI] The WEG-edge being queried.
	 * @param p_mask [AI] Bitmask to match against the face's mask.
	 * @return TRUE if edge matches mask and flags conditions; otherwise FALSE. [AI]
	 */
	LegoU32 BETA_1004a830(LegoWEGEdge& p_face, LegoU8 p_mask);

	/**
	 * @brief [AI] Checks if a WEG-edge is connected to this edge with proper flagging for its side.
	 * @details [AI] Used to quickly determine face-edge-side relations.
	 * @param p_face [AI] The WEG-edge to check.
	 * @return TRUE if present according to correct flag (c_bit1/c_bit2), otherwise FALSE. [AI]
	 */
	LegoU32 BETA_100b53b0(LegoWEGEdge& p_face);

	/**
	 * @brief [AI] Returns the opposite face pointer to the one passed in.
	 * @details [AI] Call with a face pointer: gets the "other" face at the edge for traversal/type queries.
	 * @param p_other [AI] Known face.
	 * @return Returns pointer to the other (not passed-in) face. [AI]
	 */
	LegoWEEdge* OtherFace(LegoWEEdge* p_other);

	/**
	 * @brief [AI] Calculates linear distance from a vector position to the 3D midpoint of the edge.
	 * @details [AI] Used for proximity/metric queries.
	 * @param p_vec [AI] Position to compare against midpoint.
	 * @return Euclidean distance from input point to the midpoint of this edge. [AI]
	 */
	LegoFloat DistanceToMidpoint(const Vector3& p_vec);

	/**
	 * @brief [AI] Returns the Euclidean distance between the midpoints of this edge and another edge.
	 * @details [AI] Both midpoints are computed and then their distance measured, for geometry LOD or region grouping.
	 * @param p_other [AI] The other edge.
	 * @return Distance between midpoints. [AI]
	 */
	LegoFloat DistanceBetweenMidpoints(const LegoUnknown100db7f4& p_other);

	/**
	 * @brief [AI] Returns a mask of flags relevant to the two faces (bits 0 and 1: c_bit1, c_bit2).
	 * @return The flag mask for face assignment. [AI]
	 */
	LegoU32 GetMask0x03();

	/**
	 * @brief [AI] Directly sets the internal flags value.
	 * @param p_flags [AI] Value to assign to m_flags.
	 */
	void SetFlags(LegoU16 p_flags);

	/**
	 * @brief [AI] Tests if a position is on this edge based on its direction and points, within a precision threshold.
	 * @details [AI] Tests for geometric containment: whether the given position is on/along this edge segment (using direction/normal and tolerance).
	 * @param p_position [AI] The position to test.
	 * @return TRUE if the point lies on the edge (within a tolerance), else FALSE. [AI]
	 */
	inline LegoU32 FUN_10048c40(const Vector3& p_position);

	// SYNTHETIC: LEGO1 0x1009a6c0
	// LegoUnknown100db7f4::`scalar deleting destructor'

	/**
	 * @var m_flags
	 * @brief [AI] Internal flags controlling per-face properties and connection status.
	 */
	LegoU16 m_flags;          // 0x24

	/**
	 * @var m_unk0x28
	 * @brief [AI] Represents the edge's direction/normal vector or outward face normal.
	 * @details [AI] Used repeatedly for face-based normal queries and edge positioning.
	 */
	Mx3DPointFloat m_unk0x28; // 0x28

	/**
	 * @var m_unk0x3c
	 * @brief [AI] Unknown float; likely represents additional metric (possibly precomputed distance/weight).
	 */
	float m_unk0x3c;          // 0x3c
};

// FUNCTION: LEGO1 0x10048c40
// FUNCTION: BETA10 0x1001cc90
inline LegoU32 LegoUnknown100db7f4::FUN_10048c40(const Vector3& p_position)
{
	LegoFloat localc, local10;
	LegoU32 result = FALSE;

	if (m_unk0x28[0] > 0.001 || m_unk0x28[0] < -0.001) {
		localc = (p_position[0] - (*m_pointA)[0]) / m_unk0x28[0];

		if (localc < 0 || localc > 1) {
			return FALSE;
		}

		result = TRUE;
	}
	else {
		if (p_position[0] > (*m_pointA)[0] + 0.001 || p_position[0] < (*m_pointA)[0] - 0.001) {
			return FALSE;
		}
	}

	if (m_unk0x28[1] > 0.001 || m_unk0x28[1] < -0.001) {
		local10 = (p_position[1] - (*m_pointA)[1]) / m_unk0x28[1];

		if (result) {
			if (localc > local10 + 0.001 || localc < local10 - 0.001) {
				return FALSE;
			}
		}
		else {
			result = TRUE;
			localc = local10;
		}
	}
	else {
		if (p_position[1] > (*m_pointA)[1] + 0.001 || p_position[1] < (*m_pointA)[1] - 0.001) {
			return FALSE;
		}
	}

	if (m_unk0x28[2] > 0.001 || m_unk0x28[2] < -0.001) {
		local10 = (p_position[2] - (*m_pointA)[2]) / m_unk0x28[2];

		if (result) {
			if (localc > local10 + 0.001 || localc < local10 - 0.001) {
				return FALSE;
			}
		}
		else {
			return TRUE;
		}
	}
	else {
		if (p_position[2] > (*m_pointA)[2] + 0.001 || p_position[2] < (*m_pointA)[2] - 0.001) {
			return FALSE;
		}
	}

	return TRUE;
}

#endif // __LEGOUNKNOWN100DB7F4_H