#ifndef LEGOROI_H
#define LEGOROI_H

#include "misc/legotypes.h"
#include "viewmanager/viewroi.h"

/**
 * @typedef ColorOverride
 * @brief [AI] Function pointer type for overriding color. Used to map a logical color name to an RGBA or palette format string.
 * @param const char* [AI] The original color name.
 * @param char* [AI] The output buffer for the overridden color name.
 * @param unsigned int [AI] Size of the buffer.
 * @return unsigned char [AI] Indicates whether an override occurred. [1 - overridden, 0 - not]
 */
typedef unsigned char (*ColorOverride)(const char*, char*, unsigned int);

/**
 * @typedef TextureHandler
 * @brief [AI] Function pointer type for custom palette lookup or texture palette fetching.
 * @param const char* [AI] Texture name.
 * @param unsigned char* [AI] Pointer to output palette entries.
 * @param unsigned int [AI] Number of entries expected/requested.
 * @return unsigned char [AI] Indicates success (nonzero) or failure (zero).
 */
typedef unsigned char (*TextureHandler)(const char*, unsigned char*, unsigned int);

class LegoEntity;
class LegoTextureContainer;
class LegoTextureInfo;
class LegoStorage;
class LegoAnim;
class LegoAnimNodeData;
class LegoTreeNode;
struct LegoAnimActorEntry;

/**
 * @class LegoROI
 * @brief [AI] Represents a Real-time Object Instance enriched with LEGO-specific functionality. Handles instance data for a 3D LEGO model, including hierarchy, bounding volumes, color/texturing, animation, and child ROIs.
 * @details [AI] This class extends ViewROI by providing LEGO-specific parsing from files, color alias lookups, palette management, naming, hierarchical composition, and interfaces for per-frame and per-animation state updating. Typical usage is to load and represent a LEGO object in a game world scene, supporting animation/skin selection, per-instance palette colorization, and child object composition.
 * @size 0x108 [AI]
 * @vtable LEGO1 0x100dbe38 [AI]
 */
class LegoROI : public ViewROI {
public:
	/**
	 * @brief [AI] Constructs a new LegoROI for a given renderer. Initializes basic ROI members without attaching to a LOD list yet.
	 * @param p_renderer [AI] The 3D renderer/context used for geometry.
	 */
	LegoROI(Tgl::Renderer* p_renderer);

	/**
	 * @brief [AI] Constructs a LegoROI with a specified LOD list to manage its geometry representations.
	 * @param p_renderer [AI] Renderer to use for geometry.
	 * @param p_lodList [AI] The view-level LOD list handle.
	 */
	LegoROI(Tgl::Renderer* p_renderer, ViewLODList* p_lodList);

	/**
	 * @brief [AI] Destroys the LegoROI, cleaning up children and name resources.
	 */
	~LegoROI() override;

	/**
	 * @brief [AI] Reads and initializes this ROI from a LEGO project resource stream, populating geometry, color/texture, and children recursively.
	 * @details [AI] Reads names, bounding box/sphere, textures/colors, LODs, and recursively loads all sub-ROIs from resource storage.
	 * @param p_unk0xd4 [AI] The parent ROI (can be null for the root).
	 * @param p_renderer [AI] Renderer used to create LOD geometry.
	 * @param p_viewLODListManager [AI] LOD manager for lookup/creation.
	 * @param p_textureContainer [AI] Source for texture information.
	 * @param p_storage [AI] Opened resource file stream to read from.
	 * @return [AI] SUCCESS or FAILURE, depending on if parsing succeeded.
	 */
	LegoResult Read(
		OrientableROI* p_unk0xd4,
		Tgl::Renderer* p_renderer,
		ViewLODListManager* p_viewLODListManager,
		LegoTextureContainer* p_textureContainer,
		LegoStorage* p_storage
	);

	/**
	 * @brief [AI] Recursively searches for a child ROI by name, starting at the given ROI.
	 * @details [AI] Performs a depth-first search to find a child whose name matches p_name (case-insensitive).
	 * @param p_name [AI] Name to search for (case-insensitive).
	 * @param p_roi [AI] ROI node to search from; if null, no search.
	 * @return [AI] The first matching child ROI found, or NULL if none.
	 */
	LegoROI* FindChildROI(const LegoChar* p_name, LegoROI* p_roi);

	/**
	 * @brief [AI] [Unknown function.] Used during animation update to update the transformation of the ROI hierarchy given animation nodes.
	 * @param p_node [AI] Animation tree node data.
	 * @param p_matrix [AI] The parent local-to-world transformation; input for children.
	 * @param p_time [AI] The animation time/frame to evaluate.
	 * @param p_roi [AI] Current ROI context in the hierarchy.
	 * @return [AI] Always returns SUCCESS.
	 */
	LegoResult FUN_100a8da0(LegoTreeNode* p_node, const Matrix4& p_matrix, LegoTime p_time, LegoROI* p_roi);

	/**
	 * @brief [AI] [Static] Recursively evaluates animation nodes, updating the transformation matrices and visibility for ROI instances using a mapping table.
	 * @param p_node [AI] Current animation node.
	 * @param p_matrix [AI] Parent (accumulated) transformation matrix.
	 * @param p_time [AI] Animation time/frame.
	 * @param p_roiMap [AI] Lookup table of animation node index to LegoROI*.
	 */
	static void FUN_100a8e80(LegoTreeNode* p_node, Matrix4& p_matrix, LegoTime p_time, LegoROI** p_roiMap);

	/**
	 * @brief [AI] [Static] Similar to FUN_100a8e80, but only updates transformation matrices, not visibility or invocation.
	 * @param p_node [AI] Animation tree node.
	 * @param p_matrix [AI] Parent transformation.
	 * @param p_time [AI] Animation time/frame.
	 * @param p_roiMap [AI] ROI pointer map, index by animation node.
	 */
	static void FUN_100a8fd0(LegoTreeNode* p_node, Matrix4& p_matrix, LegoTime p_time, LegoROI** p_roiMap);

	/**
	 * @brief [AI] Sets the current animation frame for this ROI based on a parsed animation structure.
	 * @param p_anim [AI] Animation to use for data.
	 * @param p_time [AI] Time/frame to set.
	 * @return [AI] SUCCESS if operation completed, FAILURE otherwise.
	 */
	LegoResult SetFrame(LegoAnim* p_anim, LegoTime p_time);

	/**
	 * @brief [AI] Sets the RGBA color for all LODs and recursively for all children.
	 * @details [AI] Each LOD and each sub-ROI receives the color setting; if any LOD or child fails, returns FAILURE.
	 * @param p_red [AI] Red component [0...1].
	 * @param p_green [AI] Green component [0...1].
	 * @param p_blue [AI] Blue component [0...1].
	 * @param p_alpha [AI] Alpha component [0...1].
	 * @return [AI] SUCCESS if all set, FAILURE otherwise.
	 */
	LegoResult SetLodColor(LegoFloat p_red, LegoFloat p_green, LegoFloat p_blue, LegoFloat p_alpha);

	/**
	 * @brief [AI] Associates every LOD in this ROI (and sub-ROIs) with a given texture (palette/material information).
	 * @param p_textureInfo [AI] The texture info to apply.
	 * @return [AI] SUCCESS if all set, FAILURE otherwise.
	 */
	LegoResult SetTextureInfo(LegoTextureInfo* p_textureInfo);

	/**
	 * @brief [AI] Attempts to retrieve a texture info pointer used by any LOD in this ROI or its children.
	 * @param p_textureInfo [AI] Reference to receive found texture info pointer.
	 * @return [AI] SUCCESS if found, FAILURE if not present in hierarchy.
	 */
	LegoResult GetTextureInfo(LegoTextureInfo*& p_textureInfo);

	/**
	 * @brief [AI] Alias to SetLodColor; applies color to all LODs and children.
	 * @param p_red [AI] Red component [0...1].
	 * @param p_green [AI] Green component [0...1].
	 * @param p_blue [AI] Blue component [0...1].
	 * @param p_alpha [AI] Alpha component [0...1].
	 * @return [AI] Result of SetLodColor.
	 */
	LegoResult FUN_100a9330(LegoFloat p_red, LegoFloat p_green, LegoFloat p_blue, LegoFloat p_alpha);

	/**
	 * @brief [AI] Sets all LOD and child colors based on a named logical color alias.
	 * @details [AI] Looks up the color via defined alias, then assigns by SetLodColor.
	 * @param p_name [AI] Canonical LEGO color alias.
	 * @return [AI] Result from internal SetLodColor call.
	 */
	LegoResult SetLodColor(const LegoChar* p_name);

	/**
	 * @brief [AI] Like SetLodColor, but uses a different implementation or legacy style. [AI_SUGGESTED_NAME: SetLodColorLegacy]
	 * @param p_name [AI] Color alias.
	 * @return [AI] Result from FUN_100a9330.
	 */
	LegoResult FUN_100a93b0(const LegoChar* p_name);

	/**
	 * @brief [AI] Tests for collision along or within sphere/box, and computes intersection point as needed.
	 * @details [AI] Checks either the ROI's box or sphere. Supports ray or vector intersection tests, updating p_v3 with intersection details if relevant.
	 * @param p_v1 [AI] Start location for intersection test.
	 * @param p_v2 [AI] Direction/step vector.
	 * @param p_f1 [AI] Magnitude/scalar for limiting the intersection check.
	 * @param p_f2 [AI] [Unknown. Used in calculations but intention unclear.]
	 * @param p_v3 [AI] Point to receive intersection coordinate if any.
	 * @param p_collideBox [AI] If true, collide against box; otherwise, collide against sphere.
	 * @return [AI] 1 if collision/intersection detected; else 0.
	 */
	LegoU32 FUN_100a9410(Vector3& p_v1, Vector3& p_v2, float p_f1, float p_f2, Vector3& p_v3, LegoBool p_collideBox);

	/**
	 * @brief [AI] Sets this ROI's name, replacing the previous (converted to lower-case).
	 * @param p_name [AI] New name to assign, or NULL to clear.
	 */
	void SetName(const LegoChar* p_name);

	/**
	 * @brief [AI] Returns the importance rating for LOD/visibility management (fixed value).
	 * @return [AI] Always 0.5, representing default intrinsic importance.
	 */
	float IntrinsicImportance() const override; // vtable+0x04

	/**
	 * @brief [AI] Updates this ROI's world-space bounding volumes based on its local-to-world transform.
	 * @details [AI] Updates both bounding box and sphere, propagating to parent where needed.
	 */
	void UpdateWorldBoundingVolumes() override; // vtable+0x18

	/**
	 * @brief [AI] Resets mesh offset for all LODs in this ROI.
	 */
	void ClearMeshOffset();

	/**
	 * @brief [AI] Sets whether to display or hide the bounding box. (Not implemented)
	 * @param p_displayBB [AI] Display/hide flag.
	 */
	void SetDisplayBB(int p_displayBB);

	/**
	 * @brief [AI] [Static] Sets the transform matrix for a given animation node at a specific time.
	 * @param p_data [AI] Animation node data.
	 * @param p_time [AI] Animation time/frame to set.
	 * @param p_matrix [AI] Matrix to be updated with local transform.
	 * @return [AI] Always returns SUCCESS.
	 */
	static LegoResult FUN_100a8cb0(LegoAnimNodeData* p_data, LegoTime p_time, Matrix4& p_matrix);

	/**
	 * @brief [AI] [Static] Prints or logs an error message about missing ROI for animation (no-op in release).
	 * @param p_error [AI] Error string format.
	 * @param p_name [AI] ROI name or additional details.
	 */
	static void FUN_100a81b0(const LegoChar* p_error, const LegoChar* p_name);

	/**
	 * @brief [AI] [Static] Configures the global ROI loading limit, controlling max LODs at load time.
	 * @param p_roi [AI] New LOD limit value.
	 */
	static void configureLegoROI(int p_roi);

	/**
	 * @brief [AI] [Static] Sets the global color override callback function to allow palette remapping or customization.
	 * @param p_colorOverride [AI] Function pointer to override.
	 */
	static void SetColorOverride(ColorOverride p_colorOverride);

	/**
	 * @brief [AI] [Static] Resolves a logical color alias into RGBA floats. Can also pass through color aliases via override.
	 * @param p_name [AI] Logical name or palette string.
	 * @param p_red [AI] Out: red value.
	 * @param p_green [AI] Out: green value.
	 * @param p_blue [AI] Out: blue value.
	 * @param p_alpha [AI] Out: alpha value.
	 * @return [AI] TRUE if alias found and color resolved, FALSE otherwise.
	 */
	static LegoBool GetRGBAColor(const LegoChar* p_name, float& p_red, float& p_green, float& p_blue, float& p_alpha);

	/**
	 * @brief [AI] [Static] Looks up a color alias in the static alias table and sets p_red/p_green/p_blue/p_alpha with normalized [0..1] floats.
	 * @param p_param [AI] Color alias to search.
	 * @param p_red [AI] Out: red component.
	 * @param p_green [AI] Out: green component.
	 * @param p_blue [AI] Out: blue component.
	 * @param p_alpha [AI] Out: alpha component.
	 * @return [AI] TRUE if a match was found; otherwise FALSE.
	 */
	static LegoBool ColorAliasLookup(
		const LegoChar* p_param,
		float& p_red,
		float& p_green,
		float& p_blue,
		float& p_alpha
	);

	/**
	 * @brief [AI] [Static] Fetches palette entries for a named texture using current texture handler.
	 * @param p_name [AI] Name of texture/palette.
	 * @param paletteEntries [AI] Pointer to buffer where entries will be written.
	 * @param p_numEntries [AI] Number of entries to be written.
	 * @return [AI] TRUE if palette data is available, otherwise FALSE.
	 */
	static LegoBool GetPaletteEntries(const LegoChar* p_name, unsigned char* paletteEntries, LegoU32 p_numEntries);

	/**
	 * @brief [AI] Gets this ROI's name.
	 * @return [AI] Pointer to the ROI name string.
	 */
	const LegoChar* GetName() const { return m_name; }

	/**
	 * @brief [AI] Gets the entity associated with this ROI (or NULL).
	 * @return [AI] Pointer to the current LegoEntity.
	 */
	LegoEntity* GetEntity() { return m_entity; }

	/**
	 * @brief [AI] Accesses the local bounding sphere object.
	 * @return [AI] Reference to this ROI's bounding sphere.
	 */
	BoundingSphere& GetBoundingSphere() { return m_sphere; }

	/**
	 * @brief [AI] Associates a LegoEntity with this ROI (typically called by parent entity/logic).
	 * @param p_entity [AI] Entity to attach.
	 */
	void SetEntity(LegoEntity* p_entity) { m_entity = p_entity; }

	/**
	 * @brief [AI] Attaches a new CompoundObject pointer (container for child ROIs).
	 * @param p_comp [AI] Compound object pointer to set.
	 */
	void SetComp(CompoundObject* p_comp) { comp = p_comp; }

	/**
	 * @brief [AI] Sets the local and world bounding spheres.
	 * @param p_sphere [AI] Bounding sphere to assign.
	 */
	void SetBoundingSphere(const BoundingSphere& p_sphere) { m_sphere = m_world_bounding_sphere = p_sphere; }

	/**
	 * @brief [AI] Sets the local bounding box from read data.
	 * @param p_unk0x80 [AI] Local bounding box.
	 */
	void SetUnknown0x80(const BoundingBox& p_unk0x80) { m_unk0x80 = p_unk0x80; }

	// SYNTHETIC: LEGO1 0x100a82b0
	// LegoROI::`scalar deleting destructor' [AI] Standard C++ scalar-deleting destructor

private:
	LegoChar* m_name;        ///< @brief [AI] Lowercase string name for this ROI (null-terminated, allocated). [0xe4]
	BoundingSphere m_sphere; ///< @brief [AI] Local bounding sphere. [0xe8]
	undefined m_unk0x100;    ///< @brief [AI] Flag or format identifier (purpose ambiguous). [0x100]
	LegoEntity* m_entity;    ///< @brief [AI] Attached entity if this ROI is controlled by/linked to an entity. [0x104]
};

/**
 * @class TimeROI
 * @brief [AI] An extension of LegoROI that adds support for keeping and applying a base time reference (used for time-based animation/control).
 * @details [AI] Stores a start/reference time, used in movement or animation interpolation.
 * @size 0x10c [AI]
 * @vtable LEGO1 0x100dbea8 [AI]
 */
class TimeROI : public LegoROI {
public:
	/**
	 * @brief [AI] Creates a TimeROI with reference time and LOD geometry.
	 * @param p_renderer [AI] The renderer/context.
	 * @param p_lodList [AI] The view LOD list.
	 * @param p_time [AI] Start or reference time for animation.
	 */
	TimeROI(Tgl::Renderer* p_renderer, ViewLODList* p_lodList, LegoTime p_time);

	// SYNTHETIC: LEGO1 0x100a9ad0
	// TimeROI::`scalar deleting destructor' [AI] Standard C++ scalar-deleting destructor

	/**
	 * @brief [AI] Updates animated position/offset by integrating movement since last update (applying time delta).
	 * @param p_matrix [AI] New matrix to compare/reference.
	 * @param p_time [AI] Current time.
	 */
	void FUN_100a9b40(Matrix4& p_matrix, LegoTime p_time);

private:
	LegoTime m_time; // 0x108
};

#endif // LEGOROI_H