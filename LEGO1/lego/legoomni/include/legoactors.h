#ifndef LEGOACTORS_H
#define LEGOACTORS_H

#include "decomp.h"
#include "mxtypes.h"

class LegoExtraActor;
class LegoROI;

/// @brief [AI] Contains information about a single LEGO actor/character, including its name, head/part types, color/texture indices, and runtime pointers to objects. [AI]
/// @details [AI] This structure encodes both the static data (e.g. actor name and part type names) as well as pointers to the runtime ROI (graphical model) and actor logic object (LegoExtraActor). It also has sound, move, and mood fields (all S32 or U8), as well as a fixed array of 10 'parts', which describe the variations and color info for the key components (body/head/arms/etc). [AI]
/// @see LegoROI, LegoExtraActor, LegoActorLOD [AI]
struct LegoActorInfo { // SIZE 0x108 [AI]
	/// @brief [AI] Describes a part/slot of a LEGO actor (e.g. head, arm, etc.), including valid variations and associated resource pointers/names. [AI]
	/// @details [AI] Contains pointers to U8 arrays for variant options, name arrays, and a byte holding the default/selected index, as well as additional arrays for color/texture handling and palette. Used for managing selectable variations for each actor part in the game. [AI]
	struct Part { // SIZE 0x18 [AI]
		MxU8* m_unk0x00;        ///< [AI] Pointer to list of variant indices for this part (options for which sub-parts may be picked by this actor part). [AI_SUGGESTED_NAME: m_variants]
		const char** m_unk0x04; ///< [AI] Pointer to array of strings representing the names/resources corresponding to the part's variants. [AI_SUGGESTED_NAME: m_variantNames]
		MxU8 m_unk0x08;         ///< [AI] Default part variant index (or count/selection index). [AI_SUGGESTED_NAME: m_defaultVariant]
		MxU8* m_unk0x0c;        ///< [AI] Pointer to a list of values (indices/colors), purpose is to map this part to a color/texture set. [AI_SUGGESTED_NAME: m_colorMap]
		const char** m_unk0x10; ///< [AI] Pointer to palette or color array, typically strings with color names or filenames for textures. [AI_SUGGESTED_NAME: m_paletteNames]
		MxU8 m_unk0x14;         ///< [AI] Default color/texture or palette index for the part. [AI_SUGGESTED_NAME: m_defaultPalette]
	};

	const char* m_name;      ///< [AI] Unique name string for this actor type (used for lookup in runtime logic, e.g. "pepper", "mama"). [AI]
	LegoROI* m_roi;          ///< [AI] Pointer to the runtime ROI (graphical representation/model) of the actor, assigned at runtime. [AI]
	LegoExtraActor* m_actor; ///< [AI] Pointer to the runtime logic/controller object for the actor (LegoExtraActor), assigned at runtime. [AI]
	MxS32 m_sound;           ///< [AI] Sound profile or current sound effect associated (index/id). [AI]
	MxS32 m_move;            ///< [AI] Movement profile, move type, or current move id. [AI]
	MxU8 m_mood;             ///< [AI] Mood parameter for the actor (expressions/mouth shape/animation set). [AI]
	Part m_parts[10];        ///< [AI] Table of body parts, each with their own variant/color selection and mappings (see Part struct). [AI]
};

/// @brief [AI] Describes a single Level-of-Detail (LOD) variant for an actor part, including bounds and orientation info. [AI]
/// @details [AI] Records the name/flags, parent linkage, bounding sphere and box, as well as the part's spatial orientation/offset (used when positioning the part in hierarchical model composition). [AI]
/// @see LegoActorLODs, LegoActorLODs enum [AI]
struct LegoActorLOD { // SIZE 0x58 [AI]
	/// @brief [AI] Flags for the LOD part, which affect how it is processed/built (custom LOD/connection logic). [AI]
	enum {
		c_flag1 = 0x01, ///< [AI] Used to denote special processing/class of LOD part (see usage in creation routines). [AI]
		c_flag2 = 0x02  ///< [AI] Used to denote a secondary special flag (usage determined by implementation). [AI]
	};

	const char* m_name;        ///< [AI] Name string for the LOD (e.g. "body", "head", "leg-lft", etc.). [AI]
	const char* m_parentName;  ///< [AI] Name of parent part/Lod, forming hierarchy for placing in the model. [AI]
	MxU32 m_flags;             ///< [AI] LOD flags; see enum above for special handling during actor building and LOD selection. [AI]
	float m_boundingSphere[4]; ///< [AI] Defines center (x, y, z) and radius for the part's bounding sphere (collision and culling). [AI_SUGGESTED_NAME: m_boundingSphereCenterRadius]
	float m_boundingBox[6];    ///< [AI] Defines axis-aligned bounding box: minX, minY, minZ, maxX, maxY, maxZ. Used for spatial culling. [AI_SUGGESTED_NAME: m_boundingBox]
	float m_position[3];       ///< [AI] Default position offset (relative to parent LOD/part), in model/local space. [AI]
	float m_direction[3];      ///< [AI] Default facing/pointing direction vector. [AI]
	float m_up[3];             ///< [AI] Default up vector, used for orientation of the part/model. [AI]
};

/// @brief [AI] Indices of the various actor LODs for lookup or iteration purposes. [AI]
/// @details [AI] Used as indices into the g_actorLODs array, as well as other routines dealing with actor LODs. [AI]
enum LegoActorLODs {
	c_topLOD,       ///< [AI] Top/root of the actor LOD hierarchy (usually main body root). [AI]
	c_bodyLOD,      ///< [AI] Body LOD node (core component of models). [AI]
	c_infohatLOD,   ///< [AI] Information hat or top-accessory. [AI]
	c_infogronLOD,  ///< [AI] Another torso region/LOD, details contextual. [AI]
	c_headLOD,
	c_armlftLOD,
	c_armrtLOD,
	c_clawlftLOD,
	c_clawrtLOD,
	c_leglftLOD,
	c_legrtLOD
};

/// @brief [AI] Indices of main LEGO actor parts (used for parts table lookup and assignment in LegoActorInfo). [AI]
/// @details [AI] Used as slot indices for the m_parts array. [AI]
enum LegoActorParts {
	c_bodyPart,      ///< [AI] Index for the main body slot in m_parts. [AI]
	c_infohatPart,   ///< [AI] Info hat or top accessory slot. [AI]
	c_infogronPart,  ///< [AI] Info/torso accent part. [AI]
	c_headPart,      ///< [AI] Head slot. [AI]
	c_armlftPart,    ///< [AI] Left arm. [AI]
	c_armrtPart,     ///< [AI] Right arm. [AI]
	c_clawlftPart,   ///< [AI] Left hand or claw accessory. [AI]
	c_clawrtPart,    ///< [AI] Right hand or claw accessory. [AI]
	c_leglftPart,    ///< [AI] Left leg. [AI]
	c_legrtPart      ///< [AI] Right leg. [AI]
};

/// @brief [AI] Global initialization table for the 66 actor types in the game, each entry describing all key aspects of that actor. [AI]
extern LegoActorInfo g_actorInfoInit[66];

/// @brief [AI] Array of 11 LOD definitions which describe the conventions for actor part hierarchy and bounding data. [AI]
extern LegoActorLOD g_actorLODs[11];

#endif // LEGOACTORS_H
