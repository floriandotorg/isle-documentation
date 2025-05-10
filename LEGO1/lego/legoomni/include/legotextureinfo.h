#ifndef LEGOTEXTUREINFO_H
#define LEGOTEXTUREINFO_H

#include "misc/legotypes.h"
#include "tgl/tgl.h"

#include <d3drmobj.h>
#include <ddraw.h>

class LegoTexture;

/**
 * @brief [AI] Contains DirectDraw and Direct3DRM handles and metadata for a texture used in the LEGO Island rendering system.
 *
 * @details [AI] This structure manages a DirectDrawSurface, a DirectDrawPalette, and a Direct3DRMTexture2 representing a loaded texture, 
 * as well as the C string name corresponding to the LEGO logical texture name. It also provides utility methods for creating, applying, and retrieving 
 * textures on Tgl/Microsoft Direct3D meshes.
 */
class LegoTextureInfo {
public:
	/**
	 * @brief [AI] Constructor. Initializes all pointer fields to null.
	 */
	LegoTextureInfo();

	/**
	 * @brief [AI] Destructor. Releases all associated DirectDraw and Direct3DRM resources, and frees the name string.
	 */
	~LegoTextureInfo();

	/**
	 * @brief [AI] Creates a new LegoTextureInfo for a given logical name and loaded LegoTexture.
	 * @param p_name [AI] Name of the texture (usually the LEGO logical name, e.g., "BROWN_ROOF").
	 * @param p_texture [AI] Pointer to a LegoTexture holding image/bitmap and palette data. 
	 * @return Pointer to a new LegoTextureInfo if successful, or NULL on failure. Returns NULL if either parameter is NULL or if resource allocation fails. [AI]
	 * @details [AI] Allocates a new LegoTextureInfo, creates DirectDrawSurface/Palette from the image, assigns the name, and stores the resulting D3DRM Texture. 
	 * The returned object owns its resources. Appends textureInfo into D3DRMAppData.
	 */
	static LegoTextureInfo* Create(const char* p_name, LegoTexture* p_texture);

	/**
	 * @brief [AI] Assigns a Direct3DRM texture group from a LegoTextureInfo to a mesh group via the Tgl/Microsoft retained mode API.
	 * @param pMesh [AI] Tgl::Mesh pointer representing the mesh group.
	 * @param p_textureInfo [AI] Texture info instance providing the D3DRMTexture to set.
	 * @return TRUE on success. [AI]
	 * @details [AI] Associates the Direct3DRMTexture2 in p_textureInfo with the specified mesh group using the Tgl layer, so it will be rendered textured.
	 */
	static BOOL SetGroupTexture(Tgl::Mesh* pMesh, LegoTextureInfo* p_textureInfo);

	/**
	 * @brief [AI] Retrieves the LegoTextureInfo currently attached to the supplied mesh group.
	 * @param pMesh [AI] Mesh to query for texture information.
	 * @param p_textureInfo [AI] Reference to pointer; on success, points to the associated LegoTextureInfo or NULL.
	 * @return TRUE if a texture is found and pointer is set, FALSE otherwise. [AI]
	 * @details [AI] Uses Direct3DRM APIs to query for an attached group texture and extract the LegoTextureInfo from its application data.
	 */
	static BOOL GetGroupTexture(Tgl::Mesh* pMesh, LegoTextureInfo*& p_textureInfo);

	/**
	 * @brief [AI] Updates the pixel bits for the current surface/texture with the provided bitmap data. 
	 * @param p_bits [AI] Pointer to the updated 8-bit indexed image pixel data to load into the DirectDrawSurface (same format as originally loaded).
	 * @return SUCCESS if the update succeeded and the texture is marked as changed, FAILURE otherwise. [AI]
	 * @details [AI] This is used for dynamic texture updates—locks the surface, copies over p_bits for the correct pitch/stride,
	 * and triggers the Direct3DRMTexture2 refresh.
	 */
	LegoResult FUN_10066010(const LegoU8* p_bits);

	// private:

	/**
	 * @brief [AI] Pointer to the logical name string for this texture (allocated; e.g., "BROWN_ROOF").
	 */
	char* m_name;                   // 0x00

	/**
	 * @brief [AI] DirectDraw surface holding the 8-bit indexed image for the texture.
	 */
	LPDIRECTDRAWSURFACE m_surface;  // 0x04

	/**
	 * @brief [AI] DirectDraw palette object (8-bit) assigned to the m_surface.
	 */
	LPDIRECTDRAWPALETTE m_palette;  // 0x08

	/**
	 * @brief [AI] Direct3DRM texture object used by retained-mode rendering. Receives updates from m_surface.
	 */
	LPDIRECT3DRMTEXTURE2 m_texture; // 0x0c
};

// GLOBAL: LEGO1 0x100db6f0
// IID_IDirect3DRMTexture2

#endif // LEGOTEXTUREINFO_H