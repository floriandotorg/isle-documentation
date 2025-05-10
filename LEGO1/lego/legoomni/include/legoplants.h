#ifndef LEGOPLANTS_H
#define LEGOPLANTS_H

#include "decomp.h"
#include "mxtypes.h"

class LegoEntity;
class LegoPathBoundary;

/// @struct LegoPlantInfo
/// @brief [AI] Struct representing a single plant's static configuration on LEGO Island, including placement, type, physical attributes, and references to world geometry.
/// @details [AI]
/// This structure is a database entry describing a plant or vegetation object as placed on LEGO Island. It allows identification of the plant's type, the worlds/scenes it belongs to, spatial coordinates and orientation, links to boundaries for collision/delineation, and denormalized state for animation/sound/color, among other settings.
/// - "World" (as bit flags) determines which virtual area(s) the plant belongs to.
/// - Variants classify the geometry/model of the plant (e.g., flower/tree/bush/palm).
/// - Color denotes its primary appearance color.
/// Several fields are used by the game logic to manage instantiations and behaviors during gameplay.
struct LegoPlantInfo {
	/// @enum World
	/// @brief [AI] Bit flags indicating which game world(s) the plant appears in.
	/// @details [AI]
	/// Used to determine in which scene(s) the plant instance should be present. Each value corresponds to a different major scene or context.
	enum World {
		c_act1 = 1 << 0,   ///< [AI] Action scene 1 [AI]
		c_imain = 1 << 1,  ///< [AI] Main island/intro [AI]
		c_ielev = 1 << 4,  ///< [AI] Elevator interior scene [AI]
		c_iisle = 1 << 5,  ///< [AI] Small isle/secret (see SI files) [AI]
		c_act2 = 1 << 15,  ///< [AI] Action scene 2 [AI]
		c_act3 = 1 << 16   ///< [AI] Action scene 3 [AI]
	};

	/// @enum Variant
	/// @brief [AI] Plant geometry/model variant. [AI]
	enum Variant {
		e_flower = 0, ///< [AI] Standard flower
		e_tree,       ///< [AI] Tree
		e_bush,       ///< [AI] Bush/shrub
		e_palm        ///< [AI] Palm tree
	};

	/// @enum Color
	/// @brief [AI] Standard colors used for LEGO plants. [AI]
	enum Color {
		e_white = 0, ///< [AI] White
		e_black,     ///< [AI] Black
		e_yellow,    ///< [AI] Yellow
		e_red,       ///< [AI] Red
		e_green      ///< [AI] Green
	};

	LegoEntity* m_entity;         ///< [AI] Pointer to the associated entity instance (initialized later at runtime) [AI]
	MxU32 m_worlds;               ///< [AI] Bitfield of World enum - specifies which scenes/worlds this plant is present in [AI]
	MxU8 m_variant;               ///< [AI] Variant enum value specifying geometry/model [AI]
	MxU32 m_sound;                ///< [AI] Sound ID or sound group associated with this plant (e.g. upon interaction or environment event) [AI]
	MxU32 m_move;                 ///< [AI] Movement/action type (for animation, swaying, interactive move, etc.) [AI]
	MxU8 m_mood;                  ///< [AI] Mood state; used for animation, facial expression, etc. [AI]
	MxU8 m_color;                 ///< [AI] Color enum value, determines plant's rendering color [AI]
	MxS8 m_unk0x16;               ///< [AI] Unknown; appears to be a state variable, possibly animation frame or LOD index [AI]
	MxS8 m_initialUnk0x16;        ///< [AI] Initial value to be loaded into m_unk0x16 (reset/restore behavior) [AI]
	const char* m_name;           ///< [AI] Name identifier; often maps to geometry, SI file object, or level editor label [AI]
	undefined4 m_unk0x1c;         ///< [AI] Unknown purpose, four bytes, possibly used for runtime flags or temporary storage [AI]
	float m_x;                    ///< [AI] World X position (center or reference) [AI]
	float m_y;                    ///< [AI] World Y position (vertical/elevation) [AI]
	float m_z;                    ///< [AI] World Z position (depth/axis in world) [AI]
	LegoPathBoundary* m_boundary; ///< [AI] Pointer to a collision or path boundary for this plant, if any [AI]
	float m_position[3];          ///< [AI] Alternate position array (likely for display, reference, or bounding computations) [AI]
	float m_direction[3];         ///< [AI] Orientation direction vector, typically for forward orientation of plant (for animation/transforms) [AI]
	float m_up[3];                ///< [AI] Up direction vector, typically (0,1,0) but can be used for skew or special display [AI]
};

/// @var g_plantInfoInit
/// @brief [AI] Static global array of all initial plant data for the island (81 entries).
/// @details [AI] This table is filled at compile/link time, and used by the core game systems to instantiate vegetation for each island scene.
/// The actual plant instances are referenced run-time via m_entity; all other information remains constant/prototyped.
extern LegoPlantInfo g_plantInfoInit[81];

#endif // LEGOPLANTS_H
