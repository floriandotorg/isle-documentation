#ifndef LEGONAMEDTEXTURE_H
#define LEGONAMEDTEXTURE_H

#include "misc/legotexture.h"
#include "mxstring.h"

// SIZE 0x14

/**
 * @brief [AI] Associates a named string with a LegoTexture instance, allowing textures to be referenced symbolically (by name).
 * 
 * This class owns the texture pointer and automatically deletes it in its destructor. It is useful for managing named texture resources, for example for lookup and resource management.
 * @details [AI]
 */
class LegoNamedTexture {
public:
	/**
	 * @brief [AI] Constructor. Creates a LegoNamedTexture pairing a name with a texture.
	 * @param p_name The symbolic name to associate with the texture. [AI]
	 * @param p_texture Pointer to the LegoTexture to own and manage. [AI]
	 */
	LegoNamedTexture(const char* p_name, LegoTexture* p_texture)
	{
		m_name = p_name;
		m_texture = p_texture;
	}

	/**
	 * @brief [AI] Destructor. Deletes the associated LegoTexture automatically to manage memory.
	 * @details [AI]
	 */
	~LegoNamedTexture() { delete m_texture; }

	/**
	 * @brief [AI] Returns a pointer to the name string associated with this texture.
	 * @return Pointer to the internal MxString name. [AI]
	 */
	const MxString* GetName() const { return &m_name; }

	/**
	 * @brief [AI] Returns a pointer to the owned LegoTexture instance.
	 * @return Pointer to the LegoTexture. [AI]
	 */
	LegoTexture* GetTexture() { return m_texture; }

private:
	MxString m_name;        ///< @brief [AI] The symbolic name (identifier) for this texture. [AI]
	LegoTexture* m_texture; ///< @brief [AI] Pointer to the owned texture (will be deleted by this class). [AI]
};

#endif // LEGONAMEDTEXTURE_H
