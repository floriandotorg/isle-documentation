#ifndef FLIC_H
#define FLIC_H

#include "decomp.h"

#include <windows.h>

/**
 * @enum FLI_CHUNK_TYPE
 * @brief [AI] Enumerates the chunk types used in the FLIC animation file format. These chunk types define the encoding, compression, and image/palette data present in a FLIC stream, as per the Autodesk FLIC file specification.
 * @details [AI] FLIC animation files (FLC/FLI) use different chunk types to store animation frames, palette data, and compress pixel data. Each chunk specifies how its contained data should be interpreted to reconstruct or update an animation frame.
 */
enum FLI_CHUNK_TYPE {
	FLI_CHUNK_COLOR256 = 4,  ///< 256-level color palette info. Updates the color lookup table with 256 entries. [AI]
	FLI_CHUNK_SS2 = 7,       ///< Word-oriented delta compression. Efficient for lines with word-aligned runs or minimal pixel changes. [AI]
	FLI_CHUNK_COLOR64 = 11,  ///< 64-level color palette info. Updates only 64 palette entries. [AI]
	FLI_CHUNK_LC = 12,       ///< Byte-oriented delta compression. Encodes lines with byte-level difference encoding. [AI]
	FLI_CHUNK_BLACK = 13,    ///< Entire frame is filled with color index 0 (black). [AI]
	FLI_CHUNK_BRUN = 15,     ///< Byte run-length compression. Lossless RLE for frame data. [AI]
	FLI_CHUNK_COPY = 16,     ///< No compression; raw pixel data for the frame. [AI]
	FLI_CHUNK_PSTAMP = 18,   ///< Postage stamp sized image for previews/thumbnails. [AI]
	FLI_CHUNK_FRAME = 0xf1fa ///< Marks the start of a FLIC animation frame. [AI]
};

#pragma pack(push, 1)
/**
 * @struct FLIC_CHUNK
 * @brief [AI] Represents a generic chunk header in a FLIC animation file. All FLIC chunks start with this header.
 * @details [AI] The "size" field specifies the length of the chunk, including both this header and any subchunks or data, in bytes. The "type" field contains the FLI_CHUNK_TYPE.
 */
typedef struct {
	DWORD size; ///< [AI] Total size of the chunk in bytes, including the header and payload/subchunks.
	WORD type;  ///< [AI] Chunk type identifier (see FLI_CHUNK_TYPE).
} FLIC_CHUNK;

/**
 * @struct FLIC_HEADER
 * @brief [AI] Structure for the main header of a FLIC animation file. Defines resolution, color depth, and timing information for the animation.
 * @details [AI] This header is found at the start of every .FLI/.FLC animation and describes global properties for rendering the animation.
 * Inherits from FLIC_CHUNK.
 */
typedef struct : FLIC_CHUNK {
	WORD frames;   ///< [AI] Number of animation frames in the first segment of the file (main animation). [AI]
	WORD width;    ///< [AI] Image width in pixels for the animation. [AI]
	WORD height;   ///< [AI] Image height in pixels for the animation. [AI]
	WORD depth;    ///< [AI] Color depth in bits per pixel (usually 8, i.e., indexed color). [AI]
	WORD flags;    ///< [AI] File format flags, usually zero or three. [AI]
	DWORD speed;   ///< [AI] Playback speed—time between frames in milliseconds. [AI]
} FLIC_HEADER;
#pragma pack(pop)

/**
 * @struct FLIC_FRAME
 * @brief [AI] Structure describing the header of a FLIC animation frame, used to organize frame subchunks and per-frame metadata.
 * @details [AI] Each animation frame is a chunk (type FLI_CHUNK_FRAME) starting with this structure, which may contain several subchunks (palette updates, image updates, etc).
 * Inherits from FLIC_CHUNK.
 */
typedef struct : FLIC_CHUNK {
	WORD chunks;    ///< [AI] Number of subchunks that compose this animation frame (palette/image/compression chunks). [AI]
	WORD delay;     ///< [AI] Delay before displaying this frame, in milliseconds. [AI]
	WORD reserved;  ///< [AI] Reserved, always zero; for alignment or future use. [AI]
	WORD width;     ///< [AI] Frame width override (if non-zero, overrides main animation width for this frame). [AI]
	WORD height;    ///< [AI] Frame height override (if non-zero, overrides main animation height for this frame). [AI]
} FLIC_FRAME;

/**
 * @brief [AI] Decodes a single FLIC (FLI/FLC) animation frame and updates the pixel data and palette.
 * @details [AI] Reads the frame, applies decompression and color/palette updates, and writes the updated result into the destination bitmap.
 * @param p_bitmapHeader [AI] Pointer to the Windows DIB BITMAPINFOHEADER structure describing the destination bitmap. Must match the dimensions of the FLIC data.
 * @param p_pixelData [AI] Pointer to the raw pixel data buffer where decoded image output will be written.
 * @param p_flcHeader [AI] Pointer to the global FLIC_HEADER for this animation.
 * @param p_flcFrame [AI] Pointer to the frame header (FLIC_FRAME) describing this animation frame.
 * @param p_decodedColorMap [AI] Output flag, set to TRUE if this frame updates the color palette, FALSE otherwise. Used to signal palette changes.
 */
void DecodeFLCFrame(
	LPBITMAPINFOHEADER p_bitmapHeader,
	BYTE* p_pixelData,
	FLIC_HEADER* p_flcHeader,
	FLIC_FRAME* p_flcFrame,
	BYTE* p_decodedColorMap
);

#endif // FLIC_H
