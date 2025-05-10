#ifndef __LEGOMESH_H
#define __LEGOMESH_H

#include "decomp.h"
#include "legocolor.h"
#include "misc/legotypes.h"

class LegoStorage;

// SIZE 0x1c
/**
 * @brief [AI] Unknown mesh sub-component structure possibly used for materials or textures. 
 * The destructor deletes its owned dynamic members.
 * @details [AI] This struct acts as an opaque component container holding five pointer members that are deleted on destruction if not null, but their purpose is unknown. [AI]
 */
struct LegoMeshUnkComponent {
	~LegoMeshUnkComponent()
	{
		if (m_unk0x08) {
			delete m_unk0x08;
		}
		if (m_unk0x0c) {
			delete m_unk0x0c;
		}
		if (m_unk0x10) {
			delete m_unk0x10;
		}
		if (m_unk0x14) {
			delete m_unk0x14;
		}
		if (m_unk0x18) {
			delete m_unk0x18;
		}
	}

	undefined m_unk0x00[8]; ///< @brief [AI] Padding/unknown bytes, function unknown. [AI]
	undefined* m_unk0x08;   ///< @brief [AI] Unknown dynamically allocated pointer, deleted in destructor. [AI]
	undefined* m_unk0x0c;   ///< @brief [AI] Unknown dynamically allocated pointer, deleted in destructor. [AI]
	undefined* m_unk0x10;   ///< @brief [AI] Unknown dynamically allocated pointer, deleted in destructor. [AI]
	undefined* m_unk0x14;   ///< @brief [AI] Unknown dynamically allocated pointer, deleted in destructor. [AI]
	undefined* m_unk0x18;   ///< @brief [AI] Unknown dynamically allocated pointer, deleted in destructor. [AI]
};

// VTABLE: LEGO1 0x100dd228
// SIZE 0x24
/**
 * @brief [AI] Represents the rendering attributes and state of a LEGO mesh, including color, transparency, shading mode, texture, and material.
 * @details [AI] This class encapsulates information about a mesh's appearance — its color, alpha (transparency), shading mode (flat/gouraud/wireframe), and optionally a texture and material name.
 * It supports serialization/deserialization via the Read() method (reading all mesh color and material properties from a LegoStorage).
 */
class LegoMesh {
public:
	/**
	 * @brief [AI] Shading mode enumeration for mesh rendering.
	 * @details [AI] Used to select the shading method: flat, Gouraud interpolated, or wireframe rendering for the mesh.
	 */
	enum {
		e_flat,      ///< @brief [AI] Use flat shading (per-polygon color).
		e_gouraud,   ///< @brief [AI] Use gouraud shading (interpolated vertex colors).
		e_wireframe  ///< @brief [AI] Use wireframe rendering.
	};

	LegoMesh();
	virtual ~LegoMesh();

	/**
	 * @brief [AI] Returns the mesh's primary color.
	 */
	LegoColor GetColor() { return m_color; }

	/**
	 * @brief [AI] Sets the mesh's primary color.
	 * @param p_color New color value. [AI]
	 */
	void SetColor(LegoColor p_color) { m_color = p_color; }

	/**
	 * @brief [AI] Gets the mesh's transparency alpha value.
	 * @details [AI] 0.0 = fully transparent, 1.0 = fully opaque.
	 */
	LegoFloat GetAlpha() { return m_alpha; }

	/**
	 * @brief [AI] Gets the shading mode of the mesh.
	 * @details [AI] Value corresponds to the shading enum (e_flat, e_gouraud, e_wireframe).
	 */
	LegoU8 GetShading() { return m_shading; }

	/**
	 * @brief [AI] Sets the shading mode.
	 * @param p_shading New shading mode (should be one of the enum values). [AI]
	 */
	void SetShading(LegoU8 p_shading) { m_shading = p_shading; }

	/**
	 * @brief [AI] Returns the value of an unknown flag or property at offset 0x0d.
	 * @details [AI] Purpose of this property is currently unidentified. [AI]
	 */
	LegoU8 GetUnknown0x0d() { return m_unk0x0d; }

	/**
	 * @brief [AI] Returns the texture resource name associated with the mesh.
	 * @details [AI] Texture name is a null-terminated lowercase string, or nullptr if no texture. [AI]
	 */
	const LegoChar* GetTextureName() { return m_textureName; }

	/**
	 * @brief [AI] Returns the material resource name for the mesh.
	 * @details [AI] Material name is a null-terminated lowercase string, or nullptr if no material. [AI]
	 */
	const LegoChar* GetMaterialName() { return m_materialName; }

	/**
	 * @brief [AI] Returns the value of an unknown boolean at offset 0x21.
	 * @details [AI] This boolean is initialized to FALSE but its function is unknown. [AI]
	 */
	LegoBool GetUnknown0x21() { return m_unk0x21; }

	/**
	 * @brief [AI] Reads mesh properties (color, alpha, shading, flags, names) from the given storage stream.
	 * @details [AI] This method deserializes the mesh data, loading color, alpha, shading, unknown properties, texture and material names, from a LegoStorage. [AI]
	 * @param p_storage Storage source to read from. [AI]
	 */
	LegoResult Read(LegoStorage* p_storage);

	// SYNTHETIC: LEGO1 0x100d3840
	// LegoMesh::`scalar deleting destructor'

protected:
	LegoColor m_color;               ///< @brief [AI] The main (diffuse) color of the mesh.
	LegoFloat m_alpha;               ///< @brief [AI] Mesh transparency (0=transparent, 1=opaque).
	LegoU8 m_shading;                ///< @brief [AI] Shading mode (see enum above).
	LegoU8 m_unk0x0d;                ///< @brief [AI] Unknown property/flag at offset 0x0d.
	LegoMeshUnkComponent* m_unk0x10; ///< @brief [AI] Unknown pointer; owned; deleted in destructor. [AI]
	undefined4 m_unk0x14;            ///< @brief [AI] Unknown 4-byte field; unused. [AI]
	LegoChar* m_textureName;         ///< @brief [AI] Name of texture resource, null if none; string is lowercase.
	LegoChar* m_materialName;        ///< @brief [AI] Name of material resource, null if none; string is lowercase.
	undefined m_unk0x20;             ///< @brief [AI] Single unused/padding byte.
	LegoBool m_unk0x21;              ///< @brief [AI] Unknown boolean property; function unknown.
};

#endif // __LEGOMESH_H
