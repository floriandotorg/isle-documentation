#ifndef MXBITMAP_H
#define MXBITMAP_H

#include "mxcore.h"
#include "mxtypes.h"

#include <ddraw.h>
#include <stdlib.h>

class MxPalette;

// The stock BITMAPINFO struct from wingdi.h only makes room for one color
// in the palette. It seems like the expectation (if you use the struct)
// is to malloc as much as you actually need, and then index into the array
// anyway even though its stated size is [1].
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo
// In our case, the size 0x428 is used frequently, which matches
// a 40-byte header plus 256 colors, so just use that as our template.

/**
 * @struct MxBITMAPINFO
 * @brief [AI] Represents a bitmap information header plus a 256-color palette, matching the layout for 8-bit DIBs used in the game engine.
 * @details [AI] This struct gives enough room for 256 color palette entries and is used as a template for 8-bit (palettized) .BMP images. 
 */
struct MxBITMAPINFO {
	BITMAPINFOHEADER m_bmiHeader;      /**< @brief [AI] Standard DIB bitmap header (size 0x28 bytes). */
	RGBQUAD m_bmiColors[256];          /**< @brief [AI] 256-entry color palette for 8bpp images. */

	/**
	 * @brief [AI] Returns the size of this structure in bytes (0x428 for 256 colors).
	 * @return [AI] Size in bytes of MxBITMAPINFO, always 0x428.
	 */
	static MxU32 Size() { return sizeof(MxBITMAPINFO); }
};

// Non-standard value for biCompression in the BITMAPINFOHEADER struct.
// By default, uncompressed bitmaps (BI_RGB) are stored in bottom-up order.
// You can specify that the bitmap has top-down order instead by providing
// a negative number for biHeight. It could be that Mindscape decided on a
// belt & suspenders approach here.
/**
 * @def BI_RGB_TOPDOWN
 * @brief [AI] Non-standard biCompression value indicating top-down row order for uncompressed bitmaps.
 * @details [AI] Used as a custom marker in .bmp headers for distinguishing top-down scanline storage. (Mindscape extension)
 */
#define BI_RGB_TOPDOWN 0x10

/**
 * @class MxBitmap
 * @brief [AI] Represents an 8bpp or high color device-independent bitmap (DIB) and provides operations for bitmap loading, manipulation, and palette management.
 * @details [AI] This class manages both the metadata (header and palette) and raw pixel data for a bitmap, supporting direct blitting, transparency, and palette operations for the LEGO Island engine.
 * 
 * The bitmap can be managed in either palettized or "high color" (truecolor) modes. It is primarily used for image resource management and 2D rendering, such as GUI assets or video frames.
 */
class MxBitmap : public MxCore {
public:
	/**
	 * @brief [AI] Constructs an empty MxBitmap instance, initializing all data pointers to NULL.
	 */
	MxBitmap();

	/**
	 * @brief [AI] Frees allocated memory for bitmap info, pixel data, and palette.
	 */
	~MxBitmap() override; // vtable+00

	/**
	 * @brief [AI] Imports the contents of another bitmap into this bitmap, allocating new storage and copying metadata and pixel data.
	 * @param p_bitmap [AI] Source bitmap to copy from.
	 * @return [AI] SUCCESS if the operation completed, FAILURE otherwise.
	 */
	virtual MxResult ImportBitmap(MxBitmap* p_bitmap); // vtable+0x14

	/**
	 * @brief [AI] Imports bitmap header/palette info (but not pixel data) from the given info block.
	 * @param p_info [AI] Source MxBITMAPINFO structure to import.
	 * @return [AI] SUCCESS if the operation completed, FAILURE otherwise.
	 */
	virtual MxResult ImportBitmapInfo(MxBITMAPINFO* p_info); // vtable+0x18

	/**
	 * @brief [AI] Allocates the bitmap to a specified width and height, attaches a palette, and configures bit depth.
	 * @param p_width [AI] Image width in pixels.
	 * @param p_height [AI] Image height in pixels.
	 * @param p_palette [AI] Palette to assign to this bitmap, or NULL for a default.
	 * @param [AI] p_isHighColor Whether to use high color/truecolor (TRUE) or palettized (FALSE) format.
	 * @return [AI] SUCCESS if allocated and initialized correctly, FAILURE otherwise.
	 */
	virtual MxResult SetSize(MxS32 p_width, MxS32 p_height, MxPalette* p_palette, MxBool); // vtable+0x1c

	/**
	 * @brief [AI] Loads a bitmap from a file handle, populating header, palette data and pixel data.
	 * @param p_handle [AI] File handle (must be positioned at the start of a valid BMP file).
	 * @return [AI] SUCCESS if bitmap loaded, FAILURE otherwise.
	 */
	virtual MxResult LoadFile(HANDLE p_handle); // vtable+0x20

	/**
	 * @brief [AI] Loads a bitmap from a file given its filename.
	 * @param p_filename [AI] Path to the bitmap file.
	 * @return [AI] 0 on failure or if not found, nonzero on success.
	 */
	virtual MxLong Read(const char* p_filename); // vtable+0x24

	/**
	 * @brief [AI] Placeholder or unused virtual; always returns -1.
	 * @param [AI] Unknown / unused argument.
	 * @return [AI] -1 always.
	 */
	virtual MxS32 VTable0x28(MxS32) { return -1; } // vtable+0x28

	/**
	 * @brief [AI] Copies a rectangular area from a source bitmap into this bitmap (BitBlt).
	 * @param p_src [AI] Source bitmap.
	 * @param p_left [AI] Source left pixel X position.
	 * @param p_top [AI] Source top pixel Y position.
	 * @param p_right [AI] Destination left pixel X position.
	 * @param p_bottom [AI] Destination top pixel Y position.
	 * @param p_width [AI] Width of rectangle to copy.
	 * @param p_height [AI] Height of rectangle to copy.
	 * @details [AI] Performs a memory copy for each scanline, including proper stride handling and clipping.
	 */
	virtual void BitBlt(
		MxBitmap* p_src,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	); // vtable+0x2c

	/**
	 * @brief [AI] Copies a rectangular region from a source bitmap to this bitmap, but skips "transparent" (index 0) pixels.
	 * @param p_src [AI] Source bitmap.
	 * @param p_left [AI] Source left pixel X position.
	 * @param p_top [AI] Source top pixel Y position.
	 * @param p_right [AI] Destination left pixel X position.
	 * @param p_bottom [AI] Destination top pixel Y position.
	 * @param p_width [AI] Width of rectangle to copy.
	 * @param p_height [AI] Height of rectangle to copy.
	 * @details [AI] Used for drawing sprites/images with transparency by ignoring palette index 0.
	 */
	virtual void BitBltTransparent(
		MxBitmap* p_src,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	); // vtable+0x30

	/**
	 * @brief [AI] Allocates or clones the current palette for the bitmap.
	 * @return [AI] Newly allocated or cloned MxPalette instance (if success), NULL if allocation failed.
	 * @details [AI] Returns a palette copy depending on current color depth mode.
	 */
	virtual MxPalette* CreatePalette(); // vtable+0x34

	/**
	 * @brief [AI] Attaches or clones a palette for the bitmap and updates color data as needed.
	 * @param p_palette [AI] Palette to import (will clone if high color).
	 * @details [AI] Behavior depends on current color depth mode (palettized or high color).
	 */
	virtual void ImportPalette(MxPalette* p_palette); // vtable+0x38

	/**
	 * @brief [AI] Changes the bit depth mode for the bitmap (palettized or high color).
	 * @param [AI] TRUE for high color, FALSE for palette mode.
	 * @return [AI] SUCCESS if mode switched or same as before, FAILURE on allocation/conversion error.
	 * @details [AI] May allocate/reallocate a new palette if switching to high color. 
	 */
	virtual MxResult SetBitDepth(MxBool); // vtable+0x3c

	/**
	 * @brief [AI] Draws (blits) a scaled region of the bitmap to a Windows device context.
	 * @param p_hdc [AI] Target device context handle.
	 * @param p_xSrc [AI] Source X origin.
	 * @param p_ySrc [AI] Source Y origin.
	 * @param p_xDest [AI] Destination X origin.
	 * @param p_yDest [AI] Destination Y origin.
	 * @param p_destWidth [AI] Destination width (in pixels).
	 * @param p_destHeight [AI] Destination height (in pixels).
	 * @return [AI] The result code from Windows StretchDIBits.
	 * @details [AI] Handles flipping for bottom-up DIBs.
	 */
	virtual MxResult StretchBits(
		HDC p_hdc,
		MxS32 p_xSrc,
		MxS32 p_ySrc,
		MxS32 p_xDest,
		MxS32 p_yDest,
		MxS32 p_destWidth,
		MxS32 p_destHeight
	); // vtable+0x40

	/**
	 * @brief [AI] Aligns a value up to the nearest multiple of four (stride alignment for DIBs).
	 * @param p_value [AI] The input value to align (pixels/bytes).
	 * @return [AI] The aligned value (next multiple of 4, at minimum p_value).
	 * @details [AI] Used for scanline stride calculations in Win32 DIB format.
	 */
	MxLong AlignToFourByte(MxLong p_value) const { return (p_value + 3) & -4; }

	/**
	 * @brief [AI] Returns the absolute value of the input height (for DIBs).
	 * @param p_value [AI] The value (may be negative or positive).
	 * @return [AI] Always positive height.
	 * @details [AI] Used for supporting negative heights (top-down flag) in DIBs.
	 */
	static MxLong HeightAbs(MxLong p_value) { return p_value > 0 ? p_value : -p_value; }

	/**
	 * @brief [AI] Returns a pointer to the underlying BITMAPINFOHEADER.
	 * @return [AI] Pointer to BITMAPINFOHEADER struct.
	 */
	BITMAPINFOHEADER* GetBmiHeader() const { return m_bmiHeader; }

	/**
	 * @brief [AI] Fetches the width (in pixels) encoded in this bitmap's header.
	 * @return [AI] Bitmap width in pixels.
	 */
	MxLong GetBmiWidth() const { return m_bmiHeader->biWidth; }

	/**
	 * @brief [AI] Computes the stride (bytes per scanline, aligned to 4 bytes).
	 * @return [AI] Number of bytes per scanline with stride padding.
	 */
	MxLong GetBmiStride() const { return ((m_bmiHeader->biWidth + 3) & -4); }

	/**
	 * @brief [AI] Fetches the height (could be negative if top-down) of the bitmap.
	 * @return [AI] DIB height as encoded (could be negative for top-down).
	 */
	MxLong GetBmiHeight() const { return m_bmiHeader->biHeight; }

	/**
	 * @brief [AI] Returns the absolute value of the bitmap's height.
	 * @return [AI] Height in pixels (always positive).
	 */
	MxLong GetBmiHeightAbs() const { return HeightAbs(m_bmiHeader->biHeight); }

	/**
	 * @brief [AI] Retrieves the pointer to the image pixel data.
	 * @return [AI] Pointer to start of pixel array.
	 */
	MxU8* GetImage() const { return m_data; }

	/**
	 * @brief [AI] Retrieves the pointer to the underlying MxBITMAPINFO struct (header and palette).
	 * @return [AI] Pointer to bitmap info struct.
	 */
	MxBITMAPINFO* GetBitmapInfo() const { return m_info; }

	/**
	 * @brief [AI] Computes the total size in bytes for the bitmap's pixel data buffer.
	 * @return [AI] Data size (width aligned to four bytes * abs(height)).
	 */
	MxLong GetDataSize() const { return AlignToFourByte(m_bmiHeader->biWidth) * GetBmiHeightAbs(); }

	/**
	 * @brief [AI] Checks if the bitmap is stored in top-down scanline order.
	 * @return [AI] TRUE if top-down, FALSE otherwise.
	 * @details [AI] Uses the custom BI_RGB_TOPDOWN or negative height.
	 */
	MxBool IsTopDown() const
	{
		if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return TRUE;
		}
		else {
			return m_bmiHeader->biHeight < 0;
		}
	}

#define GetAdjustedStride(p_bitmap)                                                                                    \
	(p_bitmap->IsTopDown() ? p_bitmap->AlignToFourByte(p_bitmap->GetBmiWidth())                                        \
						   : -p_bitmap->AlignToFourByte(p_bitmap->GetBmiWidth()))

	/**
	 * @brief [AI] Returns a pointer to the starting address of the pixel data at the specified coordinates.
	 * @param p_left [AI] X coordinate (column).
	 * @param p_top [AI] Y coordinate (row).
	 * @return [AI] Pointer to start of requested pixel.
	 * @details [AI] Takes into account DIB storage format (top-down or bottom-up).
	 */
	MxU8* GetStart(MxS32 p_left, MxS32 p_top) const
	{
		if (m_bmiHeader->biCompression == BI_RGB) {
			return m_data + p_left +
				   AlignToFourByte(GetBmiWidth()) * (IsTopDown() ? p_top : (GetBmiHeightAbs() - 1) - p_top);
		}
		else if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return m_data;
		}
		else {
			return m_data + AlignToFourByte(GetBmiWidth()) * (IsTopDown() ? 0 : (GetBmiHeightAbs() - 1));
		}
	}

	// SYNTHETIC: LEGO1 0x100bc9f0
	// SYNTHETIC: BETA10 0x1013dcd0
	// MxBitmap::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Returns the size of the bitmap info struct (MxBITMAPINFO), always 0x428.
	 * @return [AI] Size in bytes of MxBITMAPINFO.
	 */
	MxLong MxBitmapInfoSize() const { return sizeof(MxBITMAPINFO); }

	/**
	 * @brief [AI] Internal check for bottom-up DIB storage.
	 * @return [AI] TRUE if bottom-up, FALSE otherwise.
	 */
	MxBool IsBottomUp()
	{
		if (m_bmiHeader->biCompression == BI_RGB_TOPDOWN) {
			return FALSE;
		}
		else {
			return m_bmiHeader->biHeight > 0;
		}
	}

	/**
	 * @brief [AI] Helper to import RGBQUAD palette colors from another MxPalette.
	 * @param p_rgbquad [AI] Target RGBQUAD array.
	 * @param p_palette [AI] Palette to import from.
	 * @return [AI] SUCCESS if imported, FAILURE otherwise.
	 */
	MxResult ImportColorsToPalette(RGBQUAD*, MxPalette*);

	MxBITMAPINFO* m_info;          /**< @brief [AI] Pointer to bitmap info header and color table. */
	BITMAPINFOHEADER* m_bmiHeader; /**< @brief [AI] Pointer to the BITMAPINFOHEADER (image metadata). */
	RGBQUAD* m_paletteData;        /**< @brief [AI] Pointer to the color table portion of the bitmap info. */
	MxU8* m_data;                  /**< @brief [AI] Pointer to the raw pixel array. */
	MxBool m_isHighColor;          /**< @brief [AI] TRUE if using high color/truecolor, FALSE if 8bpp palette. */
	MxPalette* m_palette;          /**< @brief [AI] Current palette (deep copy/clone when high color). */
};

#endif // MXBITMAP_H