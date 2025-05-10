#ifndef LEGOLOD_H
#define LEGOLOD_H

#include "misc/legotypes.h"
#include "viewmanager/viewlod.h"

class LegoTextureContainer;
class LegoTextureInfo;
class LegoStorage;

// VTABLE: LEGO1 0x100dbf10
// SIZE 0x20
/**
 * @brief [AI] Level-Of-Detail (LOD) object used for rendering and managing polygonal mesh data with LOD switching.
 * 
 * LegoLOD extends ViewLOD to provide support for handling multiple Tgl::Mesh objects,
 * each potentially representing a different material/texture within a single LOD, as used in LEGO Island's 3D engine.
 * Provides mesh management, LOD data loading, cloning, color and texture assignment.
 * Deserialization from storage populates mesh arrays and applies material/texture as needed.
 * 
 * Typical usage: constructed and filled by the resource system (LegoROI and friends) to store mesh geometry of an object at a specific LOD.
 * 
 * Meshes may be indexed/colorized or texturized depending on geometry/material; supports group color/texture assignment for variants.
 * 
 * @note [AI] Deletion of this object will clean up allocated meshes and mesh arrays.
 */
class LegoLOD : public ViewLOD {
public:
	// SIZE 0x08
	/**
	 * @brief [AI] Structure representing a sub-mesh and its texturization flag.
	 * 
	 * Holds a pointer to the low-level graphics mesh (Tgl::Mesh) and a boolean if it is currently texturized.
	 * Used for supporting objects with multiple mesh parts using different materials/textures.
	 */
	struct Mesh {
		Tgl::Mesh* m_tglMesh; ///< Pointer to the mesh object for rendering. [AI]
		BOOL m_unk0x04;       ///< Indicates if this mesh has a texture group assigned (TRUE = textured). [AI]
	};

	/**
	 * @brief [AI] Constructor. Initializes this LOD for a given Tgl::Renderer. Allocates no meshes.
	 * @param p_renderer Renderer to associate materials/meshes with. [AI]
	 */
	LegoLOD(Tgl::Renderer*);

	/**
	 * @brief [AI] Destructor. Frees all allocated meshes and mesh arrays. [AI]
	 */
	~LegoLOD() override;

	/**
	 * @brief [AI] Get number of polygons (faces) for this LOD.
	 */
	int NumPolys() const override { return m_numPolys; } // vtable+0x0c

	/**
	 * @brief [AI] Reserved LOD callback, returns zero.
	 */
	float VTable0x10() override { return 0.0; } // vtable+0x10

	/**
	 * @brief [AI] Load LOD geometry and material info from storage, building Tgl::Mesh group(s).
	 * 
	 * Reads geometry/mesh data, materials, textures, palette, and builds meshes as needed.
	 * Associates meshes with correct renderer/textures.
	 * 
	 * @param p_renderer Renderer to allocate resources for. [AI]
	 * @param p_textureContainer Container to look up (by name) textures/material groups. [AI]
	 * @param p_storage Stream/storage to read LOD binary data from. [AI]
	 * @return Result code indicating success/failure of load. [AI]
	 */
	LegoResult Read(Tgl::Renderer* p_renderer, LegoTextureContainer* p_textureContainer, LegoStorage* p_storage);

	/**
	 * @brief [AI] Create an exact copy of this LOD, including cloned meshes, for another (or the same) renderer.
	 * 
	 * All internal meshes are shallow cloned onto the new mesh builder for the target renderer.
	 * @param p_renderer Renderer to use for duplicated resources. [AI]
	 * @return New LegoLOD with duplicated (but non-deep) resources. [AI]
	 */
	LegoLOD* Clone(Tgl::Renderer* p_renderer);

	/**
	 * @brief [AI] Overrides the color of all non-textured mesh parts for this LOD.
	 * 
	 * All sub-meshes without a group texture/m_unk0x04==FALSE will have their color set as provided (RGBA floats).
	 * 
	 * @param p_red Red component (0.0 - 1.0). [AI]
	 * @param p_green Green component (0.0 - 1.0). [AI]
	 * @param p_blue Blue component (0.0 - 1.0). [AI]
	 * @param p_alpha Alpha component. [AI]
	 * @return Success or failure code. [AI]
	 */
	LegoResult SetColor(LegoFloat p_red, LegoFloat p_green, LegoFloat p_blue, LegoFloat p_alpha);

	/**
	 * @brief [AI] Assigns the same texture group to all textured meshes in this LOD.
	 * 
	 * All meshes with m_unk0x04==TRUE will have their group texture set to the provided texture info.
	 * Used when switching/animating texture variants. Also sets mesh color to (1,1,1,0) for those meshes.
	 * 
	 * @param p_textureInfo Pointer to desired texture info/group. [AI]
	 * @return Success/failure code. [AI]
	 */
	LegoResult SetTextureInfo(LegoTextureInfo* p_textureInfo);

	/**
	 * @brief [AI] Assigns the group texture to all textured meshes, but does NOT override mesh color.
	 * 
	 * Use when only switching texture, but not the per-mesh color.
	 * 
	 * @param p_textureInfo Texture group to assign. [AI]
	 * @return Success/failure code. [AI]
	 */
	LegoResult FUN_100aad70(LegoTextureInfo* p_textureInfo);

	/**
	 * @brief [AI] Reset mesh offset index to start at 0, affecting which meshes are updated by future color/texture calls.
	 */
	void ClearMeshOffset();

	/**
	 * @brief [AI] Retrieves the texture info/group of the first mesh with group texture in this LOD.
	 * 
	 * Used to get the current texture group in use, e.g., for variant logic or serialization.
	 * 
	 * @param[out] p_textureInfo Reference to pointer that receives the found texture info/group. [AI]
	 * @return Success if found and assigned, FAILURE if not present. [AI]
	 */
	LegoResult GetTextureInfo(LegoTextureInfo*& p_textureInfo);

	/**
	 * @brief [AI] Helper to check if a mesh/material name matches the "inh" group, which separates non-inheritable types.
	 * 
	 * Used internally to split mesh arrays/grouping between texture- and color-based segments.
	 * 
	 * @param p_name Name to check (usually a mesh or material name). [AI]
	 * @retval TRUE if the name matches "inh" group. [AI]
	 */
	static LegoBool FUN_100aae20(const LegoChar* p_name);

	// SYNTHETIC: LEGO1 0x100aa430
	// LegoLOD::`scalar deleting destructor'

protected:
	Mesh* m_melems;        ///< Array of mesh struct objects representing all mesh parts that make up this LOD. [AI]
	LegoU32 m_numMeshes;   ///< Number of sub-meshes held in m_melems. [AI]
	LegoU32 m_numVertices; ///< Total number of vertices across all mesh parts. Used for stats and validation. [AI]
	LegoU32 m_numPolys;    ///< Total number of polygons (faces) across all meshes (NumPolys implementation). [AI]
	LegoU32 m_meshOffset;  ///< Internal mesh starting index for iteration; used for color/texture selective assignment. [AI]
};

#endif // LEGOLOD_H
