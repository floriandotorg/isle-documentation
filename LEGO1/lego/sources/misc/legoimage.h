#ifndef __LEGOIMAGE_H
#define __LEGOIMAGE_H

#include "legotypes.h"

class LegoStorage;

/// @class LegoPaletteEntry
/// @brief [AI] Represents a single entry in an 8-bit RGB palette with red, green, and blue components.
/// @details [AI] Used for the palette of indexed images in the LEGO Island engine; each entry stores the intensity for a single color channel.
/// The palette is typically used for mapping image indices to RGB color values.
class LegoPaletteEntry {
public:
	/// @brief [AI] Constructs an empty palette entry with all components initialized to 0. [Existing comment: Default constructor]
	LegoPaletteEntry();

	/*
	/// @brief [AI] Constructs a palette entry with red, green, and blue intensities set. (Commented out in code)
	/// @param p_red [AI] Red color intensity.
	/// @param p_green [AI] Green color intensity.
	/// @param p_blue [AI] Blue color intensity.
	LegoPaletteEntry(LegoU8 p_red, LegoU8 p_green, LegoU8 p_blue);
	*/

	/// @brief [AI] Returns the red color intensity of this palette entry.
	LegoU8 GetRed() { return m_red; }

	/// @brief [AI] Sets the red color intensity.
	/// @param p_red [AI] Value to assign to the red component.
	void SetRed(LegoU8 p_red) { m_red = p_red; }

	/// @brief [AI] Returns the green color intensity of this palette entry.
	LegoU8 GetGreen() { return m_green; }

	/// @brief [AI] Sets the green color intensity.
	/// @param p_green [AI] Value to assign to the green component.
	void SetGreen(LegoU8 p_green) { m_green = p_green; }

	/// @brief [AI] Returns the blue color intensity of this palette entry.
	LegoU8 GetBlue() { return m_blue; }

	/// @brief [AI] Sets the blue color intensity.
	/// @param p_blue [AI] Value to assign to the blue component.
	void SetBlue(LegoU8 p_blue) { m_blue = p_blue; }

	/// @brief [AI] Reads the palette entry data from a storage object. Order: red, green, blue.
	/// @param p_storage [AI] Storage interface from which the palette entry data is read (usually a file or memory stream).
	/// @details [AI] Returns a LegoResult code. If a read fails midway, the error code is reported and object may be partially filled.
	LegoResult Read(LegoStorage* p_storage);

	/// @brief [AI] Writes the palette entry data to a storage object. Order: red, green, blue.
	/// @param p_storage [AI] Storage interface to which the palette entry data is written (usually a file or memory stream).
	/// @details [AI] Returns a LegoResult code. If a write fails midway, the error code is reported.
	LegoResult Write(LegoStorage* p_storage);

protected:
	LegoU8 m_red;   ///< @brief [AI] Red channel (0-255). Offset 0x00.
	LegoU8 m_green; ///< @brief [AI] Green channel (0-255). Offset 0x01.
	LegoU8 m_blue;  ///< @brief [AI] Blue channel (0-255). Offset 0x02.
};

/// @class LegoImage
/// @brief [AI] Class representing an 8-bit palettized image with up to 256 palette entries and indexed pixel data.
/// @details [AI] Each image consists of a width, height, a count of palette colors (typically 256 or less), a palette array, and a bitmap of indices referencing the palette.
/// Pixel data is 8-bit indices into the palette. Provides serialization/deserialization and functions to manipulate palette and raw image bits.
/// If square padding is requested upon read, non-square images are padded to squares by duplicating scanlines or columns as needed.
/// Used for textures, UI elements, or sprite data in LEGO Island.
class LegoImage {
public:
	/// @brief [AI] Constructs an empty image object. Palette is not initialized; bits is nullptr.
	LegoImage();

	/// @brief [AI] Constructs an image object with a given width and height. Allocates the bits buffer accordingly.
	/// @param p_width [AI] Width in pixels.
	/// @param p_height [AI] Height in pixels.
	LegoImage(LegoU32 p_width, LegoU32 p_height);

	/// @brief [AI] Destructor; releases any allocated pixel buffer memory.
	~LegoImage();

	/// @brief [AI] Returns the current image width in pixels.
	LegoU32 GetWidth() { return m_width; }

	/// @brief [AI] Sets the image width in pixels. [AI_SUGGESTED_CORRECTED_NAME: SetImageWidth]
	/// @param p_width [AI] New width value to store.
	void SetWidth(LegoU32 p_width) { m_width = p_width; }

	/// @brief [AI] Returns the current image height in pixels.
	LegoU32 GetHeight() { return m_height; }

	/// @brief [AI] Sets the image height in pixels. [AI_SUGGESTED_CORRECTED_NAME: SetImageHeight]
	/// @param p_height [AI] New height value to store.
	void SetHeight(LegoU32 p_height) { m_height = p_height; }

	/// @brief [AI] Returns the number of palette entries in use for this image.
	LegoU32 GetCount() { return m_count; }

	/// @brief [AI] Sets the palette color count (number of valid entries in m_palette).
	/// @param p_count [AI] Number of palette colors used (<= 256).
	void SetCount(LegoU32 p_count) { m_count = p_count; }

	/// @brief [AI] Returns the pointer to the start of the palette array (256 entries).
	LegoPaletteEntry* GetPalette() { return m_palette; }

	/// @brief [AI] Returns a reference to the palette entry at index p_i. No bounds checking.
	/// @param p_i [AI] Index (palette entry number, 0-255).
	LegoPaletteEntry& GetPaletteEntry(LegoU32 p_i) { return m_palette[p_i]; }

	/// @brief [AI] Sets the palette entry at index p_i to the given value. No bounds checking.
	/// @param p_i [AI] Index (palette entry number, 0-255).
	/// @param p_paletteEntry [AI] Palette object containing the desired RGB value for this entry.
	void SetPaletteEntry(LegoU32 p_i, LegoPaletteEntry& p_paletteEntry) { m_palette[p_i] = p_paletteEntry; }

	/// @brief [AI] Returns pointer to the buffer containing indexed pixel data. [AI_SUGGESTED_CORRECTED_NAME: GetPixelIndices]
	/// @details [AI] Each byte is a palette index for the corresponding pixel, row-major order. Buffer size is width*height bytes.
	LegoU8* GetBits() { return m_bits; }

	/// @brief [AI] Sets the pixel data buffer pointer. Does NOT take ownership of the memory.
	/// @param p_bits [AI] Pointer to new bits data. Must be width * height bytes.
	void SetBits(LegoU8* p_bits) { m_bits = p_bits; }

	/// @brief [AI] Reads the full image from the storage source, including width, height, count, palette, and pixel indices.
	/// @param p_storage [AI] Storage interface to read from (file/memory/etc).
	/// @param p_square [AI] If nonzero, enforces padding of the image to square dimensions by duplicating scanlines or columns.
	/// @details [AI] Allocates m_bits with new[] (deletes the previous on success). Applies square-padding if requested and width != height.
	LegoResult Read(LegoStorage* p_storage, LegoU32 p_square);

	/// @brief [AI] Writes the full image to the given storage: width, height, count, palette, pixel indices.
	/// @param p_storage [AI] Storage output to receive the formatted palette data and image bits.
	LegoResult Write(LegoStorage* p_storage);

protected:
	LegoU32 m_width;                 ///< @brief [AI] Image width, in pixels.
	LegoU32 m_height;                ///< @brief [AI] Image height, in pixels.
	LegoU32 m_count;                 ///< @brief [AI] Number of palette entries in use (<= 256).
	LegoPaletteEntry m_palette[256]; ///< @brief [AI] Full palette array (256 possible 8-bit RGB entries).
	LegoU8* m_bits;                  ///< @brief [AI] Pointer to the image bits. Each byte is a palette index; size = width*height.
};

#endif // __LEGOIMAGE_H