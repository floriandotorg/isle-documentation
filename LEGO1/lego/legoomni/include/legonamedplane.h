#ifndef LEGONAMEDPLANE_H
#define LEGONAMEDPLANE_H

#include "misc/legostorage.h"
#include "mxgeometry/mxgeometry3d.h"
#include "mxstring.h"

// SIZE 0x4c

/**
 * @brief [AI] Represents a named 3D plane with orientation and position, used to describe places or camera targets in LEGO Island's world.
 * 
 * This structure encapsulates a plane in 3D space by providing a name, a position,
 * a direction vector (the facing/forward vector), and an up vector to fully specify
 * its orientation. It's serializable to and from LegoStorage, making it suitable for
 * game state save/load and scripting purposes.
 * [AI]
 */
struct LegoNamedPlane {
	/**
	 * @brief [AI] Default constructor that initializes an unnamed plane. [AI]
	 */
	LegoNamedPlane() {}

	// FUNCTION: LEGO1 0x10033a70
	// LegoNamedPlane::~LegoNamedPlane
	/**
	 * @brief [AI] Default destructor (implementation likely trivial). [AI]
	 */

	// Unclear whether getters/setters were used.
	// Act1State::Serialize seems to access `m_name` directly (only matches like that)
	// Act1State::PlaceActors though seems to require extensive use of getters to improve
	/**
	 * @brief [AI] Retrieve the name identifier for this plane. [AI]
	 * @return Pointer to the character array holding the name. [AI]
	 */
	const char* GetName() const { return m_name.GetData(); }

	/**
	 * @brief [AI] Get the 3D position of this plane in world coordinates. [AI]
	 * @return Reference to Mx3DPointFloat containing position. [AI]
	 */
	const Mx3DPointFloat& GetPosition() { return m_position; }

	/**
	 * @brief [AI] Get the normalized direction (forward) vector of the plane. [AI]
	 * @return Reference to Mx3DPointFloat containing the direction. [AI]
	 */
	const Mx3DPointFloat& GetDirection() { return m_direction; }

	/**
	 * @brief [AI] Get the normalized "up" vector of the plane, defining its orientation. [AI]
	 * @return Reference to Mx3DPointFloat containing the up vector. [AI]
	 */
	const Mx3DPointFloat& GetUp() { return m_up; }

	/**
	 * @brief [AI] Set the name identifier for this plane. [AI]
	 * @param p_name Null-terminated string for the new name. [AI]
	 */
	void SetName(const char* p_name) { m_name = p_name; }

	/**
	 * @brief [AI] Set the 3D position of the plane. [AI]
	 * @param p_position Reference to the new position value. [AI]
	 */
	void SetPosition(const Mx3DPointFloat& p_position) { m_position = p_position; }

	/**
	 * @brief [AI] Set the direction (forward) vector of the plane. [AI]
	 * @param p_direction Reference to the new direction vector. [AI]
	 */
	void SetDirection(const Mx3DPointFloat& p_direction) { m_direction = p_direction; }

	/**
	 * @brief [AI] Set the "up" vector of the plane. [AI]
	 * @param p_up Reference to the new up vector. [AI]
	 */
	void SetUp(const Mx3DPointFloat& p_up) { m_up = p_up; }

	/**
	 * @brief [AI] Determines whether the plane instance is valid (present) based on its name.
	 * 
	 * A plane is present if its name is not empty. [AI]
	 * 
	 * @return True if the plane has a non-empty name, false otherwise. [AI]
	 */
	MxBool IsPresent() { return strcmp(m_name.GetData(), "") != 0; }

	/**
	 * @brief [AI] Reset the plane to "not present" by clearing its name. [AI]
	 */
	void Reset() { m_name = ""; }

	/**
	 * @brief [AI] Serialize or deserialize the plane data to or from a LegoStorage object.
	 * 
	 * If the storage is in write mode, writes the members (name, position, direction, up).
	 * In read mode, reads in the same order. Used for saving/loading state and scripting.
	 * [AI]
	 * @param p_storage Pointer to the LegoStorage for serialization. [AI]
	 * @return SUCCESS on successful read/write. [AI]
	 */
	MxResult Serialize(LegoStorage* p_storage)
	{
		if (p_storage->IsWriteMode()) {
			p_storage->WriteMxString(m_name);
			p_storage->WriteVector(m_position);
			p_storage->WriteVector(m_direction);
			p_storage->WriteVector(m_up);
		}
		else if (p_storage->IsReadMode()) {
			p_storage->ReadMxString(m_name);
			p_storage->ReadVector(m_position);
			p_storage->ReadVector(m_direction);
			p_storage->ReadVector(m_up);
		}

		return SUCCESS;
	}

	/**
	 * @brief [AI] Name identifier for this plane (used for lookups and scripting). [AI]
	 */
	MxString m_name;            // 0x00

	/**
	 * @brief [AI] 3D position of the plane in world space. [AI]
	 */
	Mx3DPointFloat m_position;  // 0x10

	/**
	 * @brief [AI] Direction (forward/facing) vector for the plane orientation. [AI]
	 */
	Mx3DPointFloat m_direction; // 0x24

	/**
	 * @brief [AI] "Up" vector for the plane, defines its local up direction. [AI]
	 */
	Mx3DPointFloat m_up;        // 0x38
};

#endif // LEGONAMEDPLANE_H
