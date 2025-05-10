#ifndef LEGOPATHEDGECONTAINER_H
#define LEGOPATHEDGECONTAINER_H

#include "mxgeometry/mxgeometry3d.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"

class LegoPathBoundary;
struct LegoPathCtrlEdge;

/// @brief [AI] Represents an edge within a path boundary, used for path following and geometric computations. 
/// Consists of a pointer to a control edge and the boundary this edge is associated with. [AI]
/// @details [AI] Used for quick edge+boundary association when evaluating path connectivity, graph search, or boundary transitions. 
/// The edge and boundary are never owned (no lifetime management). [AI]
/// @note [AI] 0x08 bytes in size
struct LegoBoundaryEdge {
	LegoBoundaryEdge() {}

	/// @brief [AI] Construct a LegoBoundaryEdge with given edge and boundary.
	/// @param p_edge [AI] Pointer to the path control edge. 
	/// @param p_boundary [AI] Associated path boundary. 
	LegoBoundaryEdge(LegoPathCtrlEdge* p_edge, LegoPathBoundary* p_boundary)
	{
		m_edge = p_edge;
		m_boundary = p_boundary;
	}

	LegoPathCtrlEdge* m_edge;     ///< [AI] Pointer to the path control edge. [AI]
	LegoPathBoundary* m_boundary; ///< [AI] Pointer to the owning or containing path boundary. [AI]

	/// @brief [AI] Comparison operator, currently a stub (always returns false). [AI]
	int operator==(LegoBoundaryEdge) const { return 0; }

	/// @brief [AI] Less-than operator, currently a stub (always returns false). [AI]
	int operator<(LegoBoundaryEdge) const { return 0; }
};

/// @brief [AI] Represents a path edge with extra float data and potential linkage (single-linked). [AI]
/// @details [AI] Used to construct linked lists of boundary edges annotated with a floating-point value 
/// (possibly cost, parametric position, or priority for edge sets). [AI]
/// @note [AI] 0x10 bytes in size.
struct LegoBEWithFloat {
	LegoBEWithFloat()
	{
		m_edge = NULL;
		m_boundary = NULL;
		m_next = NULL;
		m_unk0x0c = 0.0f;
	}

	/// @brief [AI] Construct with edge, boundary, and a float value. [AI]
	/// @param p_edge [AI] Associated control edge. [AI]
	/// @param p_boundary [AI] Associated path boundary. [AI]
	/// @param p_unk0x0c [AI] Annotation value for the edge. Semantics depend on use case. [AI]
	LegoBEWithFloat(LegoPathCtrlEdge* p_edge, LegoPathBoundary* p_boundary, MxFloat p_unk0x0c)
	{
		m_edge = p_edge;
		m_boundary = p_boundary;
		m_next = NULL;
		m_unk0x0c = p_unk0x0c;
	}

	/// @brief [AI] Construct with edge, boundary, pointer to next, and float value.
	/// @param p_edge [AI] Associated control edge. [AI]
	/// @param p_boundary [AI] Associated path boundary. [AI]
	/// @param p_next [AI] Pointer to next node in the chain. [AI]
	/// @param p_unk0x0c [AI] Annotation value for the edge. [AI]
	LegoBEWithFloat(LegoPathCtrlEdge* p_edge, LegoPathBoundary* p_boundary, LegoBEWithFloat* p_next, MxFloat p_unk0x0c)
	{
		m_edge = p_edge;
		m_boundary = p_boundary;
		m_next = p_next;
		m_unk0x0c = p_unk0x0c;
	}

	LegoPathCtrlEdge* m_edge;     ///< [AI] Pointer to the relevant path control edge. [AI]
	LegoPathBoundary* m_boundary; ///< [AI] Path boundary this edge belongs to. [AI]
	LegoBEWithFloat* m_next;      ///< [AI] Next node in the edge chain, for linked structures (may be null). [AI]
	MxFloat m_unk0x0c;            ///< [AI] Annotation float; likely an edge priority, weight, parametric value, etc. [AI]

	/// @brief [AI] Comparison operator, stub (always returns false). [AI]
	int operator==(LegoBEWithFloat) const { return 0; }

	/// @brief [AI] Less-than operator, stub (always returns false). [AI]
	int operator<(LegoBEWithFloat) const { return 0; }
};

/// @brief [AI] Function object for comparing LegoBEWithFloat pointers by their floating-point annotation. [AI]
/// @details [AI] Used so that multiset or other sorted containers can order the elements by edge priority/value. [AI]
struct LegoBEWithFloatComparator {
	/// @brief [AI] Return true if a's annotation is strictly less than b's.
	/// @param p_a [AI] First edge. [AI]
	/// @param p_b [AI] Second edge. [AI]
	/// @return [AI] True if p_a's float value is less than p_b's. [AI]
	bool operator()(LegoBEWithFloat* const& p_a, LegoBEWithFloat* const& p_b) const
	{
		return p_a->m_unk0x0c < p_b->m_unk0x0c;
	}
};

/// @brief [AI] Multiset of LegoBEWithFloat pointers, ordered by their annotation float value. [AI]
typedef multiset<LegoBEWithFloat*, LegoBEWithFloatComparator> LegoBEWithFloatSet;

/// @brief [AI] Container for path boundary edges, also stores position, direction, and flags. [AI]
/// @details [AI] Stores a collection of boundary edges and records a spatial reference (position, direction), 
/// boundary association, and one or more flag bits. Used for geometric and logical grouping of path boundary edges 
/// in spatial networks. [AI]
/// @note [AI] Inherits from list<LegoBoundaryEdge>; size is 0x3c bytes. 
struct LegoPathEdgeContainer : public list<LegoBoundaryEdge> {
	enum {
		c_bit1 = 0x01 ///< [AI] Flag value for the container; purpose depends on subsystems using this structure. [AI]
	};

	/// @brief [AI] Default constructor. Initializes position and direction to default, clears boundary and flags. [AI]
	LegoPathEdgeContainer()
	{
		m_boundary = NULL;
		m_flags = 0;
	}

	/// @brief [AI] Set or clear the c_bit1 flag in m_flags.
	/// @param p_set [AI] Non-zero to set the flag, zero to clear it. [AI]
	void SetBit1(MxU32 p_set)
	{
		if (p_set) {
			m_flags |= c_bit1;
		}
		else {
			m_flags &= ~c_bit1;
		}
	}

	/// @brief [AI] Query if the c_bit1 flag is set. Returns zero if not set. [AI]
	/// @return [AI] Non-zero if flag is set, zero if not. [AI]
	MxU32 GetBit1() { return m_flags & c_bit1; }

	Mx3DPointFloat m_position;    ///< [AI] 3D position reference for the edge group, e.g., start or mean location. [AI]
	Mx3DPointFloat m_direction;   ///< [AI] 3D direction vector reference, e.g., average or intended facing. [AI]
	LegoPathBoundary* m_boundary; ///< [AI] Associated boundary for all contained edges; may be null if container is generic. [AI]
	MxU8 m_flags;                 ///< [AI] Flag bits for special edge container properties (e.g. active, reachable, etc.). [AI]
};

#endif // LEGOPATHEDGECONTAINER_H
