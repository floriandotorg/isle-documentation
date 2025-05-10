#ifndef __LEGOEDGE_H
#define __LEGOEDGE_H

#include "misc/legotypes.h"

class LegoWEEdge;
class Vector3;

// VTABLE: LEGO1 0x100db7b8
// SIZE 0x24

/**
 * @brief [AI] Represents an edge in the LEGO world geometry graph. Connects two points and can belong to two faces. Provides clockwise/counterclockwise edge navigation and vertex lookup for algorithms requiring half-edge traversal. [AI]
 * @details [AI] A LegoEdge represents a connection between two points (Vector3*) and can be shared between two polygonal faces (LegoWEEdge*). It also stores links to adjacent edges around each face, which allows for efficient traversal (e.g., for walking along polygons' borders). [AI]
 */
struct LegoEdge {
	/**
	 * @brief [AI] Constructs a LegoEdge with all members initialized to nullptr. [AI]
	 */
	LegoEdge();
	
	/**
	 * @brief [AI] Destructor. No special cleanup is performed (pointers are not owned). [AI]
	 */
	virtual ~LegoEdge(); // vtable+0x00

	/**
	 * @brief [AI] Returns the clockwise adjacent edge relative to the given face. [AI]
	 * @param p_face The face (LegoWEEdge) for which to find the clockwise edge. [AI]
	 * @return The next adjacent edge in clockwise direction if found; otherwise nullptr. [AI]
	 */
	LegoEdge* GetClockwiseEdge(LegoWEEdge& p_face);

	/**
	 * @brief [AI] Returns the counterclockwise adjacent edge relative to the given face. [AI]
	 * @param p_face The face (LegoWEEdge) for which to find the counterclockwise edge. [AI]
	 * @return The next adjacent edge in counterclockwise direction if found; otherwise nullptr. [AI]
	 */
	LegoEdge* GetCounterclockwiseEdge(LegoWEEdge& p_face);

	/**
	 * @brief [AI] Returns the "clockwise" endpoint of this edge with respect to a given face. [AI]
	 * @details [AI] Returns the vertex that is at the endpoint of the edge in alignment with moving clockwise along the face p_face. Ownership is not transferred. [AI]
	 * @param p_face The face to determine the orientation. [AI]
	 * @return Pointer to the Vector3 representing the clockwise vertex. [AI]
	 */
	Vector3* CWVertex(LegoWEEdge& p_face);

	/**
	 * @brief [AI] Returns the "counterclockwise" endpoint of this edge with respect to a given face. [AI]
	 * @details [AI] Returns the vertex that is at the endpoint of the edge in alignment with moving counterclockwise along the face p_face. Ownership is not transferred. [AI]
	 * @param p_face The face to determine the orientation. [AI]
	 * @return Pointer to the Vector3 representing the counterclockwise vertex. [AI]
	 */
	Vector3* CCWVertex(LegoWEEdge& p_face);

	/**
	 * @brief [AI] Performs an, as yet, unknown operation using the given face and point. [AI_SUGGESTED_NAME: IntersectOrProjectOrClassify]
	 * @details [AI] The operation likely checks or projects the provided point relative to this edge and face. Exact semantics unresolved. [AI]
	 * @param p_face The face context for the operation. [AI]
	 * @param p_point The point involved in the operation. [AI]
	 * @return Result code indicating the outcome of the operation. [AI]
	 */
	LegoResult FUN_1002ddc0(LegoWEEdge& p_face, Vector3& p_point);

	/**
	 * @brief [AI] Gets the first face (A) using this edge. [AI]
	 * @return Pointer to the face (LegoWEEdge*) on side A. [AI]
	 */
	LegoWEEdge* GetFaceA() { return m_faceA; }

	/**
	 * @brief [AI] Gets the second face (B) using this edge. [AI]
	 * @return Pointer to the face (LegoWEEdge*) on side B. [AI]
	 */
	LegoWEEdge* GetFaceB() { return m_faceB; }

	/**
	 * @brief [AI] Gets the first endpoint (A) of the edge. [AI]
	 * @return Pointer to Vector3 representing endpoint A. [AI]
	 */
	Vector3* GetPointA() { return m_pointA; }

	/**
	 * @brief [AI] Gets the second endpoint (B) of the edge. [AI]
	 * @return Pointer to Vector3 representing endpoint B. [AI]
	 */
	Vector3* GetPointB() { return m_pointB; }

	// SYNTHETIC: LEGO1 0x1009a4a0
	// LegoEdge::`scalar deleting destructor'

	/**
	 * @brief [AI] Pointer to the first face sharing this edge. [AI]
	 * @details [AI] May be null if the edge is not referenced by a face. [AI]
	 */
	LegoWEEdge* m_faceA; // 0x04

	/**
	 * @brief [AI] Pointer to the second face sharing this edge. [AI]
	 * @details [AI] May be null if not referenced by a second face. [AI]
	 */
	LegoWEEdge* m_faceB; // 0x08

	/**
	 * @brief [AI] Next edge (counterclockwise) around face A. [AI]
	 */
	LegoEdge* m_ccwA;    // 0x0c

	/**
	 * @brief [AI] Next edge (clockwise) around face A. [AI]
	 */
	LegoEdge* m_cwA;     // 0x10

	/**
	 * @brief [AI] Next edge (counterclockwise) around face B. [AI]
	 */
	LegoEdge* m_ccwB;    // 0x14

	/**
	 * @brief [AI] Next edge (clockwise) around face B. [AI]
	 */
	LegoEdge* m_cwB;     // 0x18

	/**
	 * @brief [AI] The first endpoint of the edge. [AI]
	 */
	Vector3* m_pointA;   // 0x1c

	/**
	 * @brief [AI] The second endpoint of the edge. [AI]
	 */
	Vector3* m_pointB;   // 0x20
};

#endif // __LEGOEDGE_H
