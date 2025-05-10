#ifndef VIEWLOD_H
#define VIEWLOD_H

#include "decomp.h"
#include "realtime/roi.h"
#include "tgl/tgl.h"

//////////////////////////////////////////////////////////////////////////////
// ViewLOD
//

// VTABLE: LEGO1 0x100dbd70
// SIZE 0x0c
/**
 * @brief [AI] Represents a Level of Detail (LOD) object for rendering, implemented with a mesh builder and supporting bitwise flag operations.
 * @details [AI] ViewLOD handles a group of polygons (LODObject) at a specific detail level, utilizing a Tgl::MeshBuilder for 3D mesh construction. 
 *              It provides methods for average polygon area estimation and custom flag manipulation, intended for optimizing rendering performance 
 *              based on distance or importance. The flags in m_unk0x08 are manipulated to affect the object's LOD state.
 */
class ViewLOD : public LODObject {
public:
	enum {
		c_bit4 = 0x10 /**< @brief [AI] Flag value for bit 4 mask operation. [AI] */
	};

	/**
	 * @brief [AI] Constructs a ViewLOD using the provided Tgl Renderer. The mesh builder is initialized to NULL and internal flag to 3.
	 * @param pRenderer Tgl Renderer associated with the mesh construction. [AI]
	 */
	ViewLOD(Tgl::Renderer* pRenderer) : m_meshBuilder(NULL), m_unk0x08(3) {}

	/**
	 * @brief [AI] Destructor, deletes the owned mesh builder if present.
	 */
	~ViewLOD() override;

	/**
	 * @brief [AI] Approximates the average area of polygons within this LOD.
	 * @details [AI] Returns an average polygon area based on 2π*10 divided by the number of polygons. Used for LOD management heuristics. [AI]
	 * @return The average polygon area estimate. [AI]
	 */
	double AveragePolyArea() const override { return 2 * 3.14159 * 10.0 / NumPolys(); } // vtable+0x04

	/**
	 * @brief [AI] Returns the estimated number of vertices in this LOD.
	 * @details [AI] Calculates the vertex count as double the number of polygons. [AI]
	 * @return Number of vertices. [AI]
	 */
	int NVerts() const override { return NumPolys() * 2; } // vtable+0x08

	/**
	 * @brief [AI] Returns a pointer to the mesh builder associated with this LOD.
	 * @return Mesh builder object pointer. [AI]
	 */
	Tgl::MeshBuilder* GetMeshBuilder() { return m_meshBuilder; }

	/**
	 * @brief [AI] Returns a const pointer to the mesh builder for this LOD.
	 * @return Const mesh builder pointer. [AI]
	 */
	const Tgl::MeshBuilder* GetMeshBuilder() const { return m_meshBuilder; }

	/**
	 * @brief [AI] Returns the internal flag value m_unk0x08.
	 * @return Internal flag state. [AI]
	 */
	undefined4 GetUnknown0x08() { return m_unk0x08; }

	/**
	 * @brief [AI] Performs a bitwise AND (mask) with value 0xffffff04 on the internal flag, returning result as an unsigned char.
	 * @details [AI] Typically used to test or extract specific flags or bits from m_unk0x08. [AI]
	 * @return Result of flag AND operation. [AI]
	 */
	unsigned char GetUnknown0x08Test4() { return m_unk0x08 & 0xffffff04; }

	/**
	 * @brief [AI] Performs a bitwise AND (mask) with value 0xffffff08 on the internal flag, returning result as an unsigned char.
	 * @details [AI] Used for testing or extracting certain flag bits. [AI]
	 * @return Result of flag AND operation. [AI]
	 */
	unsigned char GetUnknown0x08Test8() { return m_unk0x08 & 0xffffff08; }

	/**
	 * @brief [AI] Sets a given flag in the internal flags (m_unk0x08) using bitwise OR.
	 * @param p_flag Flag bits to set. [AI]
	 */
	void SetFlag(unsigned char p_flag) { m_unk0x08 |= p_flag; }

	/**
	 * @brief [AI] Clears a given flag in the internal flags (m_unk0x08) using bitwise AND with negated p_flag.
	 * @param p_flag Flag bits to clear. [AI]
	 */
	void ClearFlag(unsigned char p_flag) { m_unk0x08 &= ~p_flag; }

	// SYNTHETIC: LEGO1 0x100a6f60
	// ViewLOD::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Points to a mesh builder instance for constructing or managing polygonal mesh data for this LOD.
	 */
	Tgl::MeshBuilder* m_meshBuilder; // 0x04 [AI]

	/**
	 * @brief [AI] Internal bitfield for flag/status storage controlling LOD state and behavior. Usage is determined by bit masking via accessor methods.
	 */
	undefined4 m_unk0x08;            // 0x08 [AI]
};

#endif // VIEWLOD_H
