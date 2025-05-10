#ifndef MXDISPLAYSURFACE_H
#define MXDISPLAYSURFACE_H

#include "decomp.h"
#include "mxcore.h"
#include "mxvideoparam.h"

#include <ddraw.h>

class MxBitmap;
class MxPalette;

/// \class MxDisplaySurface
/// \brief Provides a DirectDraw-based drawing surface for blitting bitmaps, managing palette, and screen updates. [AI]
/// \details [AI] This class manages the primary and secondary DirectDraw surfaces for the purpose of rendering game frames, copying bitmaps, handling palette changes, managing double buffering, and supporting transparent RLE bitmap blits. It works alongside MxVideoParam for resolution, flipping, palette, and fullscreen/window handling. [AI]
/// \ingroup Graphics [AI]
// VTABLE: LEGO1 0x100dc768
// SIZE 0xac
class MxDisplaySurface : public MxCore {
public:
	/// \brief [AI] Constructs the display surface and initializes all members.
	MxDisplaySurface(); // [AI]

	/// \brief [AI] Destroys the display surface and releases DirectDraw objects and resources.
	~MxDisplaySurface() override; // [AI]

	/// \brief [AI] Initializes the surface object with given video parameters, DirectDraw surfaces, and a clipper.
	/// \param p_videoParam Video parameters describing resolution, bitdepth, and flags. [AI]
	/// \param p_ddSurface1 Primary DirectDraw surface, typically the front buffer. [AI]
	/// \param p_ddSurface2 Secondary DirectDraw surface, typically the back buffer. [AI]
	/// \param p_ddClipper Window clipper for drawing in windowed mode. [AI]
	/// \returns SUCCESS on success, FAILURE otherwise. [AI]
	virtual MxResult Init(
		MxVideoParam& p_videoParam,
		LPDIRECTDRAWSURFACE p_ddSurface1,
		LPDIRECTDRAWSURFACE p_ddSurface2,
		LPDIRECTDRAWCLIPPER p_ddClipper
	); // vtable+0x14

	/// \brief [AI] Creates DirectDraw surfaces and initializes based on the desired video mode. [AI]
	/// \param p_videoParam Video parameters describing target video mode and properties. [AI]
	/// \returns SUCCESS on success, FAILURE otherwise. [AI]
	virtual MxResult Create(MxVideoParam& p_videoParam); // vtable+0x18

	/// \brief [AI] Releases all DirectDraw surfaces and resources held by this object.
	virtual void Destroy(); // vtable+0x1c

	/// \brief [AI] Sets the palette used for the primary and secondary DirectDraw surfaces. 
	/// \param p_palette Palette object containing hardware palette entries. [AI]
	/// \details [AI] This also handles internally converting the palette for 16-bit display modes. [AI]
	virtual void SetPalette(MxPalette* p_palette); // vtable+0x20

	/// \brief [AI] Draws a bitmap onto a surface described by p_desc, scaling to the specified rectangle. [AI]
	/// \param p_desc Surface description (mostly used for fast access to the raw buffer). [AI]
	/// \param p_bitmap The bitmap to draw. [AI]
	/// \param p_left/p_top/p_right/p_bottom Rectangle in surface coordinates to draw into. [AI]
	/// \param p_width/p_height The area width/height to draw. [AI]
	virtual void VTable0x24(
		LPDDSURFACEDESC p_desc,
		MxBitmap* p_bitmap,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	); // vtable+0x24

	/// \brief [AI] Draws a bitmap onto the back surface, specified by coordinates and output size. [AI]
	/// \param p_bitmap The bitmap to be drawn. [AI]
	/// \param p_left/p_top/p_right/p_bottom Surface destination rectangle. [AI]
	/// \param p_width/p_height The width and height to draw. [AI]
	virtual void VTable0x28(
		MxBitmap* p_bitmap,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height
	); // vtable+0x28

	/// \brief [AI] Draws a bitmap with optional transparency (RLE) onto the output surface. [AI]
	/// \param p_desc Surface description for output. [AI]
	/// \param p_bitmap Bitmap source. [AI]
	/// \param p_left/p_top/p_right/p_bottom Output rectangle in surface coordinates. [AI]
	/// \param p_width/p_height Area width/height to draw. [AI]
	/// \param p_RLE If TRUE, treat as RLE-style transparency. [AI]
	virtual void VTable0x2c(
		LPDDSURFACEDESC p_desc,
		MxBitmap* p_bitmap,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height,
		MxBool p_RLE
	); // vtable+0x2c

	/// \brief [AI] Draws a bitmap with optional transparency (RLE), outputting to active back surface. [AI]
	/// \param p_bitmap Bitmap to be drawn. [AI]
	/// \param p_left/p_top/p_right/p_bottom Output rectangle coordinates. [AI]
	/// \param p_width/p_height Drawing size. [AI]
	/// \param p_RLE If TRUE, apply RLE-based transparency algorithm. [AI]
	virtual void VTable0x30(
		MxBitmap* p_bitmap,
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_right,
		MxS32 p_bottom,
		MxS32 p_width,
		MxS32 p_height,
		MxBool p_RLE
	); // vtable+0x30

	/// \brief [AI] Directly writes an array of pixel data into the back surface at the given rectangle. [AI]
	/// \param p_pixels Source pixel data. [AI]
	/// \param p_bpp Bits per pixel of source. [AI]
	/// \param p_width/p_height Output rectangle in pixels. [AI]
	/// \param p_x/p_y Destination position (top-left). [AI]
	virtual void VTable0x34(
		MxU8* p_pixels,
		MxS32 p_bpp,
		MxS32 p_width,
		MxS32 p_height,
		MxS32 p_x,
		MxS32 p_y
	); // vtable+0x34

	/// \brief [AI] Presents the back buffer contents to the front buffer or window. [AI]
	/// \param p_left/p_top Source rectangle. [AI]
	/// \param p_left2/p_top2 Destination rectangle (windowed mode). [AI]
	/// \param p_width/p_height Size of area to copy or flip. [AI]
	virtual void Display(
		MxS32 p_left,
		MxS32 p_top,
		MxS32 p_left2,
		MxS32 p_top2,
		MxS32 p_width,
		MxS32 p_height
	); // vtable+0x38

	/// \brief [AI] Acquires a Win32 device context (DC) for the back buffer surface, for GDI drawing. [AI]
	/// \param p_hdc Output pointer for the device context handle. [AI]
	virtual void GetDC(HDC* p_hdc); // vtable+0x3c

	/// \brief [AI] Releases a device context (DC) previously acquired for the back surface. [AI]
	/// \param p_hdc The device context handle to release. [AI]
	virtual void ReleaseDC(HDC p_hdc); // vtable+0x40

	/// \brief [AI] Allocates a DirectDraw surface for a bitmap to allow hardware blitting/transparency. [AI_SUGGESTED_NAME: AllocateBitmapSurface]
	/// \param p_bitmap Bitmap source. [AI]
	/// \param p_ret Used as allocation flag; returned as a pointer to updated allocation status. [AI]
	/// \param p_doNotWriteToSurface If set, surface is not filled (unsupported). [AI]
	/// \param p_transparent Whether to use transparency/color key. [AI]
	/// \returns Newly created DirectDraw surface, or NULL on failure. [AI]
	virtual LPDIRECTDRAWSURFACE VTable0x44(
		MxBitmap* p_bitmap,
		undefined4* p_ret,
		undefined4 p_doNotWriteToSurface,
		undefined4 p_transparent
	); // vtable+0x44

	/// \brief [AI] Fills the current back buffer with black (clears the display area). [AI]
	void ClearScreen(); // [AI]
	
	/// \brief [AI] Creates and draws a 16x16 cursor DirectDraw surface. [AI]
	/// \returns Pointer to the new cursor surface, or NULL on error. [AI]
	static LPDIRECTDRAWSURFACE CreateCursorSurface(); // [AI]

	/// \brief [AI] Creates a deep copy of the provided surface (new DirectDraw surface with same content). [AI]
	/// \param p_src Source DirectDraw surface to copy. [AI]
	/// \returns New surface on success, or NULL. [AI]
	static LPDIRECTDRAWSURFACE CopySurface(LPDIRECTDRAWSURFACE p_src); // [AI]

	/// \brief [AI] Returns the primary DirectDraw surface (front buffer).
	LPDIRECTDRAWSURFACE GetDirectDrawSurface1() { return m_ddSurface1; } // [AI]

	/// \brief [AI] Returns the secondary DirectDraw surface (back buffer).
	LPDIRECTDRAWSURFACE GetDirectDrawSurface2() { return m_ddSurface2; } // [AI]

	/// \brief [AI] Gets the video parameter configuration (mode/resolution/etc) in use by this surface.
	MxVideoParam& GetVideoParam() { return m_videoParam; } // [AI]

	/// \brief [AI] Performs RLE-based transparent drawing from an RLE-compressed bitmap into the given surface. [AI]
	/// \param p_bitmapData Current position in the RLE-compressed bitmap data. [AI]
	/// \param p_surfaceData Target point in destination surface memory. [AI]
	/// \param p_bitmapSize Total size in bytes of the bitmap data. [AI]
	/// \param p_width/p_height Size of area to draw. [AI]
	/// \param p_pitch Surface pitch (bytes per row). [AI]
	/// \param p_bpp Bits per pixel for output surface. [AI]
	void DrawTransparentRLE(
		MxU8*& p_bitmapData,
		MxU8*& p_surfaceData,
		MxU32 p_bitmapSize,
		MxS32 p_width,
		MxS32 p_height,
		MxLong p_pitch,
		MxU8 p_bpp
	); // [AI]

	/// \brief [AI] Creates a 16-bit DirectDraw surface of specified size, either in video or system memory.
	/// \param width Surface width. [AI]
	/// \param height Surface height. [AI]
	/// \returns Created surface on success, or NULL. [AI]
	LPDIRECTDRAWSURFACE FUN_100bc8b0(MxS32 width, MxS32 height); // [AI_SUGGESTED_NAME: Create16BitSurface]

private:
	/// \brief [AI] Counts the total number of bits set to 1 in p_param. [AI]
	/// \param p_param Input bitmask. [AI]
	MxU8 CountTotalBitsSetTo1(MxU32 p_param); // [AI]

	/// \brief [AI] Counts number of trailing zero bits before the first 1 in p_param (contiguous bits set to 1). [AI]
	/// \param p_param Input bitmask. [AI]
	MxU8 CountContiguousBitsSetTo1(MxU32 p_param); // [AI]

	/// \brief [AI] Initializes all members to safe defaults or NULL. [AI]
	void Init(); // [AI]

	MxVideoParam m_videoParam;        ///< [AI] Video parameters describing resolution, bit depth, and rendering mode. [AI]
	LPDIRECTDRAWSURFACE m_ddSurface1; ///< [AI] Primary/front DirectDraw surface for display output. [AI]
	LPDIRECTDRAWSURFACE m_ddSurface2; ///< [AI] Secondary/back DirectDraw surface for double buffering. [AI]
	LPDIRECTDRAWCLIPPER m_ddClipper;  ///< [AI] Clipper used in windowed mode for restricting drawing area. [AI]
	MxBool m_initialized;             ///< [AI] TRUE if the surfaces have been successfully initialized and created. [AI]
	DDSURFACEDESC m_surfaceDesc;      ///< [AI] Description of the back surface (format, size, pitch, bit masks, etc). [AI]
	MxU16* m_16bitPal;                ///< [AI] Palette lookup table for fast 8-bit to 16-bit color conversion. [AI]
};

// SYNTHETIC: LEGO1 0x100ba580
// MxDisplaySurface::`scalar deleting destructor'

#endif // MXDISPLAYSURFACE_H