#ifndef LEGOLOCATIONS_H
#define LEGOLOCATIONS_H

#include "decomp.h"
#include "mxtypes.h"

// SIZE 0x60

/**
 * @brief Data structure representing a named spatial location and orientation in the LEGO Island world, 
 *        with associated boundaries for source/destination triggers and some custom flags. [AI]
 * @details [AI] LegoLocation encapsulates a spatial location by name, with position, orientation (direction, up), 
 *          and two possible boundary definitions for logical mapping such as scene transitions or camera events. 
 *          Used to define camera spots, spawn points, trigger areas, etc.
 */
struct LegoLocation {
	// SIZE 0x18

	/**
	 * @brief Defines a logical boundary associated with a location for things such as triggers, teleportation areas, or view control. [AI]
	 * @details [AI] Contains a name to identify the boundary, source/destination indices and scales for mapping between zones, and an unknown bool field. 
	 *          Likely used to define the edge between two areas or control zone transitions/logic. [AI]
	 */
	struct Boundary {
		const char* m_name; ///< Name of the boundary, typically referencing a map edge or connection. [AI]
		MxS32 m_src;        ///< Source zone or tile index for this boundary. [AI]
		float m_srcScale;   ///< Source scaling factor, modifies transition logic or geometric mapping. [AI]
		MxS32 m_dest;       ///< Destination zone or tile index for this boundary. [AI]
		float m_destScale;  ///< Destination scaling factor. [AI]
		MxBool m_unk0x10;   ///< Unknown flag. Presumed to control boundary activation/enabling or directionality. [AI]
	};

	MxU32 m_index;        ///< Index or ID of this location in the global locations array. [AI]
	const char* m_name;   ///< Name of the location (camera preset, landmark, or spawn zone). [AI]
	float m_position[3];  ///< Cartesian position of the location (x, y, z). [AI]
	float m_direction[3]; ///< Direction vector, describes primary view or travel direction. [AI]
	float m_up[3];        ///< Up vector, for orientation (used in look-at or camera frames). [AI]
	Boundary m_boundaryA; ///< First logical boundary associated with this location, for zone transitions or triggers. [AI]
	Boundary m_boundaryB; ///< Second logical boundary, enables junctions or asymmetric transitions. [AI]
	MxBool m_unk0x5c;     ///< Unknown flag, seems to mark special locations or enable/disable associated logic. [AI]
	MxU8 m_frequency;     ///< Frequency or priority, may control how often this location is used/appears in algorithms. [AI]
};

/**
 * @brief Global table of all defined LEGO Island scene/camera/world locations. [AI]
 * @details [AI] Each element represents a distinct point of interest (such as camera positions, spawn/transition points) 
 *          with named boundaries for zone connection logic.
 */
extern LegoLocation g_locations[70];

#endif // LEGOLOCATIONS_H
