#ifndef __LEGOVERTEX_H
#define __LEGOVERTEX_H

#include "misc/legotypes.h"

class LegoStorage;

/// @brief [AI] Represents a 3D vertex with floating point coordinates. Used to store 3D position information in the LEGO Island engine.
/// @details [AI] This class encapsulates a 3D point or vector with three coordinates (x, y, z), 
/// and provides accessor, mutator, and serialization methods. It can be used to represent geometry positions or transform points.
class LegoVertex {
public:
	/// @brief [AI] Constructs a LegoVertex at the origin (0, 0, 0).
	LegoVertex();

	/// @brief [AI] Gets the value of one of the xyz coordinates by index (0=x, 1=y, 2=z).
	/// @param p_i Index of the coordinate (0, 1, or 2). [AI]
	/// @return The coordinate value at the given index. [AI]
	LegoFloat GetCoordinate(LegoU32 p_i) { return m_coordinates[p_i]; }

	/// @brief [AI] Sets the value of one of the xyz coordinates by index (0=x, 1=y, 2=z).
	/// @param p_i Index of the coordinate (0, 1, or 2). [AI]
	/// @param p_coordinate The new value for the coordinate. [AI]
	void SetCoordinate(LegoU32 p_i, LegoFloat p_coordinate) { m_coordinates[p_i] = p_coordinate; }

	/// @brief [AI] Gets the X coordinate.
	LegoFloat GetX() { return m_coordinates[0]; }

	/// @brief [AI] Sets the X coordinate.
	/// @param p_x The X value. [AI]
	void SetX(LegoFloat p_x) { m_coordinates[0] = p_x; }

	/// @brief [AI] Gets the Y coordinate.
	LegoFloat GetY() { return m_coordinates[1]; }

	/// @brief [AI] Sets the Y coordinate.
	/// @param p_y The Y value. [AI]
	void SetY(LegoFloat p_y) { m_coordinates[1] = p_y; }

	/// @brief [AI] Gets the Z coordinate.
	LegoFloat GetZ() { return m_coordinates[2]; }

	/// @brief [AI] Sets the Z coordinate.
	/// @param p_z The Z value. [AI]
	void SetZ(LegoFloat p_z) { m_coordinates[2] = p_z; }

	/// @brief [AI] Checks whether the vertex is located at the origin (0,0,0).
	/// @details [AI] Returns true if all coordinates are zero. Used to verify default or reset state.
	/// @return True if the vertex is the origin; otherwise false. [AI]
	LegoBool IsOrigin() { return m_coordinates[0] == 0.0 && m_coordinates[1] == 0.0 && m_coordinates[2] == 0.0; }

	/// @brief [AI] Reads the coordinates from a storage object (usually a file/buffer).
	/// @param p_storage Pointer to a LegoStorage for reading the coordinates. [AI]
	/// @details [AI] Reads 3 floats in order (X, Y, Z) from the storage stream.
	/// @return Indicates whether reading was successful or an error occurred. [AI]
	LegoResult Read(LegoStorage* p_storage);

	/// @brief [AI] Provides direct access to a coordinate by index (read/write).
	/// @param i Index of the coordinate (0 for X, 1 for Y, 2 for Z). [AI]
	/// @return Reference to the requested coordinate. [AI]
	LegoFloat& operator[](int i) { return m_coordinates[i]; }

	/// @brief [AI] Provides direct access to a coordinate by index (read-only).
	/// @param i Index of the coordinate (0 for X, 1 for Y, 2 for Z). [AI]
	/// @return Value of the requested coordinate. [AI]
	LegoFloat operator[](int i) const { return m_coordinates[i]; }

protected:
	/// @brief [AI] The x, y, and z coordinates of the vertex. [AI]
	LegoFloat m_coordinates[3]; // 0x00 [AI]
};

#endif // __LEGOVERTEX_H
