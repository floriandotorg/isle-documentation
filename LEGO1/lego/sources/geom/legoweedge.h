#ifndef __LEGOWEEDGE_H
#define __LEGOWEEDGE_H

#include "decomp.h"
#include "misc/legotypes.h"

struct LegoUnknown100db7f4;

/**
 * @brief [AI] Represents a face (polygon) composed of a list of edges in the LEGO Island world engine. 
 * [AI] This class manages an array of pointers to edge objects (LegoUnknown100db7f4), tracks their count, 
 * and handles establishing adjacency (linking edges to their neighbors and faces). Used as base for faces in world mesh structure.
 * @details [AI] Each LegoWEEdge instance corresponds to a face, and contains references to its constituent edges (m_edges), 
 * which are edge objects with information on face membership (A/B), adjacency, and points (vertices). The VTable0x04 method (with custom edge linkage logic) 
 * is important for setting up cyclic relations between edge objects and their corresponding faces, based on edge connectivity.
 */
class LegoWEEdge {
public:
	/**
	 * @brief [AI] Constructs a LegoWEEdge with no edges. Members are set to represent an empty face.
	 */
	LegoWEEdge();

	/**
	 * @brief [AI] Destroys the LegoWEEdge object, releasing memory used by its edge list.
	 * @details [AI] Frees the m_edges array if it was allocated, but does not delete the actual edge objects (LegoUnknown100db7f4), which are managed elsewhere.
	 */
	virtual ~LegoWEEdge(); // vtable+0x00

	/**
	 * @brief [AI] Connects and links the associated edge objects to set up adjacency across the face.
	 * @details [AI] Iterates over the edge pointers stored in m_edges, and, for each pair, examines point connectivity
	 * to assign face and neighbor links between the edge objects, ensuring proper winding and adjacency for the mesh structures.
	 * This is a core step in establishing geometric/topological consistency in the in-game world's mesh.
	 * @return [AI] Always returns 0 after processing. [AI_SUGGESTED_NAME: LinkEdgesAndFaces]
	 */
	virtual LegoS32 VTable0x04(); // vtable+0x04

	/**
	 * @brief [AI] Returns the number of edge elements assigned to this face.
	 * @return The number of edges.
	 */
	LegoU8 GetNumEdges() { return m_numEdges; }

	/**
	 * @brief [AI] Gets the array of pointers to the edge objects that form this face.
	 * @return Pointer to array of LegoUnknown100db7f4*.
	 */
	LegoUnknown100db7f4** GetEdges() { return m_edges; }

	/**
	 * @brief [AI] Checks if this face object is the same as another.
	 * @param p_other The other LegoWEEdge to compare with. [AI]
	 * @return Nonzero if the two pointers are identical; 0 otherwise.
	 */
	LegoU32 IsEqual(LegoWEEdge* p_other) { return this == p_other; }

	/**
	 * @brief [AI] Assigns the edge list and count for this face.
	 * @param p_edges Pointer to an array of LegoUnknown100db7f4* objects (edge pointers). [AI]
	 * @param p_numEdges Number of edge pointers in the array. [AI]
	 * @details [AI] Does not take ownership of the array memory (only pointer assignment); edge objects should persist for the face's lifetime.
	 */
	void SetEdges(LegoUnknown100db7f4** p_edges, LegoU8 p_numEdges)
	{
		m_edges = p_edges;
		m_numEdges = p_numEdges;
	}

	// SYNTHETIC: LEGO1 0x1009a570
	// LegoWEEdge::`scalar deleting destructor'

protected:
	LegoU8 m_numEdges;             ///< [AI] Number of edge elements in m_edges; number of sides of the polygon. [AI]
	LegoUnknown100db7f4** m_edges; ///< [AI] Array of pointers to edge objects (LegoUnknown100db7f4) comprising this face. [AI]
};

#endif // __LEGOWEEDGE_H
