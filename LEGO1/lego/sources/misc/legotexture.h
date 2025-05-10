#ifndef __LEGOTEXTURE_H
#define __LEGOTEXTURE_H

#include "legotypes.h"

class LegoImage;
class LegoStorage;

/// @brief [AI] Represents a texture which wraps a LegoImage and provides loading/saving functionality.
/// @details [AI] LegoTexture owns a pointer to a LegoImage and is responsible for managing its lifetime.
///             It provides methods to read texture data from and write it to a LegoStorage (file/memory),
///             delegating the actual I/O work to the underlying LegoImage.
///             Used throughout the LEGO Island engine for texture management. [AI]
/// @see LegoImage [AI]
class LegoTexture {
public:
	/// @brief [AI] Constructs a LegoTexture object and allocates a new LegoImage.
	LegoTexture();

	/// @brief [AI] Destructor. Frees the owned LegoImage.
	~LegoTexture();

	/// @brief [AI] Returns the associated image used by this texture.
	/// @return [AI] Pointer to the underlying LegoImage for this texture.
	LegoImage* GetImage() { return m_image; }

	/// @brief [AI] Sets the associated image for this texture.
	/// @param p_image [AI] The new LegoImage instance to associate with this texture. Ownership is NOT transferred. The previous image is not deleted. [AI]
	void SetImage(LegoImage* p_image) { m_image = p_image; }

	/// @brief [AI] Reads texture data from a LegoStorage.
	/// @param p_storage [AI] Storage object to read from (can be file or memory).
	/// @param p_square [AI] The mipmap or level-of-detail index to read (purpose dependent on image format).
	/// @details [AI] Delegates the actual reading process to the internal LegoImage object.
	/// @return [AI] Returns a LegoResult indicating success or failure.
	LegoResult Read(LegoStorage* p_storage, LegoU32 p_square);

	/// @brief [AI] Writes texture data to a LegoStorage.
	/// @param p_storage [AI] Storage object to write to (can be file or memory).
	/// @details [AI] Delegates the actual writing process to the internal LegoImage object.
	/// @return [AI] Returns a LegoResult indicating success or failure.
	LegoResult Write(LegoStorage* p_storage);

protected:
	LegoImage* m_image; ///< @brief [AI] Pointer to the image data associated with this texture. Owned by the LegoTexture instance.
};

#endif // __LEGOTEXTURE_H