#ifndef __LEGOWEGEDGE_H
#define __LEGOWEGEDGE_H

/// [AI] Represents a path segment with an associated trigger in LEGO Island pathing logic.
/// This structure contains a pointer to a path structure, a data field, and a trigger distance (or related float value). [AI]
/// Must be defined before the inclusion of Mx4DPointFloat for correct order. [AI]
/// SIZE 0x0c [AI]
struct PathWithTrigger {
	/// [AI] Constructs a PathWithTrigger and initializes its members to default values.
	/// @brief [AI]
	PathWithTrigger()
	{
		m_pathStruct = NULL;
		m_data = 0;
		m_unk0x08 = 0.0f;
	}

	LegoPathStruct* m_pathStruct; ///< [AI] Pointer to a path structure associated with this trigger. [AI]
	unsigned int m_data;          ///< [AI] Miscellaneous data value, use determined by path logic. [AI]
	float m_unk0x08;              ///< [AI] Distance along the path or trigger threshold (exact semantics unclear). [AI]
};

#include "mxgeometry/mxgeometry3d.h"
#include "mxgeometry/mxgeometry4d.h"

/// [AI] Represents a "geometry edge" in the LEGO Island world polygon/path system.
/// Extends LegoWEEdge. It contains extra geometry information such as edge normals, flags, triggers, and other geometry metrics. [AI]
/// The class is used in path/boundary computations, LOD edge logic, physics, and geometry-based triggering. [AI]
/// SIZE: 0x54 [AI]
/// VTABLE: LEGO1 0x100db7f8 [AI]
class LegoWEGEdge : public LegoWEEdge {
public:
	/// [AI] Flags controlling various edge behaviors and states. [AI]
	enum {
		c_bit1 = 0x01,  ///< [AI] Edge-specific flag (purpose determined by logic in edge processing)
		c_bit2 = 0x02,  ///< [AI]
		c_bit3 = 0x04,  ///< [AI]
		c_bit5 = 0x10   ///< [AI] Disabled flag mask (see GetFlag0x10/SetFlag0x10) [AI]
	};

	/// [AI] Constructs a LegoWEGEdge and initializes its member variables. [AI]
	/// @brief [AI]
	LegoWEGEdge();

	/// [AI] Destroys this edge instance and properly deallocates memory for associated dynamic members. [AI]
	/// @brief [AI]
	~LegoWEGEdge() override;

	/// [AI] Performs geometry calculations for the edge, sets up normals, center point, and trigger vectors.
	/// Returns 0 for success, negative values for various errors. See implementation for details on error codes. [AI]
	/// @return Result code (0 = OK, negatives = error). [AI]
	LegoS32 VTable0x04() override; // vtable+0x04

	/// Returns TRUE if the 'disabled' flag is not set, otherwise FALSE.
	/// Used as a quick status/activation check for edge-flags. [AI]
	/// @return TRUE if enabled, FALSE if disabled (bit5 cleared). [AI]
	LegoU32 GetFlag0x10()
	{
		if (m_flags & c_bit5) {
			return FALSE;
		}
		else {
			return TRUE;
		}
	}

	/// [AI] Returns a pointer to the cached 4D normal or reference plane for the edge.
	/// This vector is central for many operations like side detection, collision, and physics. [AI]
	/// @return Pointer to m_unk0x14. [AI]
	Mx4DPointFloat* GetUnknown0x14() { return &m_unk0x14; }

	/// [AI] Returns a pointer to the 4D edge normal at the given sub-edge index. Used for plane intersection/testing. [AI]
	/// @param index Index of the edge normal in the edge's polygonal set [AI]
	/// @return Pointer to the normal at the requested index. [AI]
	Mx4DPointFloat* GetEdgeNormal(int index) { return &m_edgeNormals[index]; }

	/// [AI] Returns the name string of this edge, typically used for debugging and lookup. [AI]
	/// @return Pointer to a null-terminated string holding the edge name. [AI]
	const LegoChar* GetName() { return m_name; }

	/// [AI] Sets the enabled/disabled flag for this edge.
	/// If p_disable is TRUE (nonzero), disables the edge (clears bit5). If FALSE, enables it (sets bit5).
	/// Used by path logic to dynamically disable/enable edges at runtime. [AI]
	/// @param p_disable Whether to disable (TRUE) or enable (FALSE) this edge. [AI]
	void SetFlag0x10(LegoU32 p_disable)
	{
		if (p_disable) {
			m_flags &= ~c_bit5;
		}
		else {
			m_flags |= c_bit5;
		}
	}

	/// [AI] Returns a two-bit mask of the first two edge state flags (bit1, bit2).
	/// Useful for quickly getting the basic state/type of this edge (e.g., path eligibility/state flags). [AI]
	/// @return Bitwise OR of c_bit1 and c_bit2 flags. [AI]
	LegoU8 GetMask0x03() { return m_flags & (c_bit1 | c_bit2); }

	/// [AI] Declares LegoPathController as a friend, allowing it to access internal members for path placement and control. [AI]
	friend class LegoPathController;

protected:
	/// [AI] Internal routine called by VTable0x04 for validity checking of polygon vertices and normal consistency.
	/// Returns 0 for OK, negative for degenerate or nonplanar geometry. [AI]
	/// @return Result code (0 OK, negative if error on geometry consistency) [AI]
	LegoS32 FUN_1009aea0();

	LegoU8 m_flags;                 ///< [AI] Flags indicating edge state, enabled/disabled, and type bits. [AI]
	LegoU8 m_unk0x0d;               ///< [AI] Unknown, used for internal status/tracking. [AI]
	LegoChar* m_name;               ///< [AI] Edge's name string, dynamically allocated for debug/lookup. [AI]
	Mx4DPointFloat m_unk0x14;       ///< [AI] 4D plane equation or normal used for polygon/edge side tests. [AI]
	Mx4DPointFloat* m_edgeNormals;  ///< [AI] Per-edge normals for each polygon segment, allocated dynamically. [AI]
	Mx3DPointFloat m_unk0x30;       ///< [AI] Cached center for the edge polygon, used in geometric calculations. [AI]
	float m_unk0x44;                ///< [AI] Maximum squared distance from center—polygon bounding radius or similar. [AI]
	LegoU8 m_numTriggers;           ///< [AI] Number of trigger (path/segment) structures attached to this edge. [AI]
	PathWithTrigger* m_pathTrigger; ///< [AI] Array of triggers influencing entity motion or event logic on this edge. [AI]
	Mx3DPointFloat* m_unk0x50;      ///< [AI] Transition direction/unit vector—used for edge trigger geometry. [AI]
};

#endif // __LEGOWEGEDGE_H
