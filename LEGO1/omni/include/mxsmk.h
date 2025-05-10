#ifndef MXSMK_H
#define MXSMK_H

#include "decomp.h"
#include "mxgeometry.h"
#include "mxtypes.h"

#include <smack.h>

struct MxBITMAPINFO;

// These functions are not part of the public interface,
// but present in SMACK.LIB and used directly by Mindscape.
/**
 * @brief [AI] External functions from SMACK.LIB used for decoding Smacker video data.
 * @details [AI] These functions provide access to the internal Huffman table and frame decoding
 * routines of the Smacker codec. They are used to decompress and decode video streams in LEGO Island.
 */
extern "C"
{
	/**
	 * @brief [AI] Returns the required size for Huffman tables used in Smacker video decoding.
	 * @return [AI] Size in bytes needed for the tables.
	 */
	u32 SmackGetSizeTables();

	/**
	 * @brief [AI] Generates Huffman tables required for decoding a Smacker frame.
	 * @param p_huffmanTrees [AI] Pointer to the Huffman trees (input).
	 * @param p_huffmanTables [AI] Buffer to receive generated Huffman tables (output).
	 * @param p_codeSize [AI] Size of the code table.
	 * @param p_abSize [AI] Size of the AB table.
	 * @param p_detailSize [AI] Size of the detail table.
	 * @param p_typeSize [AI] Size of the type table.
	 * @details [AI] This function prepares the internal coding tables based on Huffman tree input, enabling Smacker frame decompression.
	 */
	void SmackDoTables(
		u8* p_huffmanTrees,
		u8* p_huffmanTables,
		u32 p_codeSize,
		u32 p_abSize,
		u32 p_detailSize,
		u32 p_typeSize
	);

	/**
	 * @brief [AI] Decompress a single Smacker video frame into a provided buffer.
	 * @param p_source [AI] Source chunk/frame data to decode.
	 * @param p_huffmanTables [AI] Prepared Huffman tables for decompression.
	 * @param p_unk0x6b4 [AI] Buffer/context for decompression (decoded frame output or working state).
	 * @details [AI] Called for each frame displayed; decompresses frame from compressed data into output bitmap.
	 */
	void SmackDoFrameToBuffer(u8* p_source, u8* p_huffmanTables, u8* p_unk0x6b4);

	/**
	 * @brief [AI] Returns the size required for frame delta data given width and height.
	 * @param p_width [AI] Width of the frame.
	 * @param p_height [AI] Height of the frame.
	 */
	u32 SmackGetSizeDeltas(u32 p_width, u32 p_height);

	/**
	 * @brief [AI] Reads a rectangle from the frame update information.
	 * @param p_unk0x6b4 [AI] Frame decoder state/context.
	 * @param p_rect [AI] Output array for rectangle dimensions (left,top,width,height).
	 * @return [AI] Returns the rectangle descriptor (usually success state).
	 */
	u8 SmackGetRect(u8* p_unk0x6b4, u32* p_rect);
}

// SIZE 0x6b8
/**
 * @brief [AI] The MxSmk struct encapsulates all data required to decode and display a Smacker (SMK) video stream.
 * @details [AI] This struct holds both metadata, decompression tables and buffer pointers for one video stream,
 * as well as working memory for decompression of frames during playback. Used exclusively as part of video playback in LEGO Island.
 */
struct MxSmk {
	SmackTag m_smackTag;       ///< @brief [AI] Metadata block from the Smacker file header.
	undefined m_unk0x390[784]; ///< @brief [AI] Reserved/unused; aligns struct to file format ([AI_SUGGESTED_NAME: paddingOrWorkingBuffer])
	MxU32* m_frameSizes;       ///< @brief [AI] Array of frame sizes (in bytes), one entry per video frame (plus ring frame if present).
	MxU8* m_frameTypes;        ///< @brief [AI] Array of frame types, one entry per frame.
	MxU8* m_huffmanTrees;      ///< @brief [AI] Huffman trees used for decompressing video frames.
	MxU8* m_huffmanTables;     ///< @brief [AI] Generated decoding tables for use in SmackDoFrameToBuffer.
	MxU32 m_maxFrameSize;      ///< @brief [AI] Maximum size of any frame, used for allocation.
	MxU8* m_unk0x6b4;          ///< @brief [AI] Buffer/context for decoding frame delta data; referenced throughout decompression ([AI_SUGGESTED_NAME: frameDecompressionContext]).

	/**
	 * @brief [AI] Loads the SMK header and initializes decoding structures for a Smacker video.
	 * @param p_data [AI] Pointer to the raw .SMK header data.
	 * @param p_mxSmk [AI] The MxSmk struct to initialize.
	 * @return [AI] SUCCESS if header is loaded correctly, FAILURE otherwise.
	 * @details [AI] Fills out metadata, Huffman tables and allocates all required buffers for playback.
	 */
	static MxResult LoadHeader(MxU8* p_data, MxSmk* p_mxSmk);

	/**
	 * @brief [AI] Cleans up and deallocates all resources associated with this MxSmk.
	 * @param p_mxSmk [AI] The MxSmk instance to destroy.
	 * @details [AI] Releases all dynamic buffers/tables to avoid memory leaks.
	 */
	static void Destroy(MxSmk* p_mxSmk);

	/**
	 * @brief [AI] Decompresses and loads a single Smacker frame into a bitmap buffer, updating palette if needed.
	 * @param p_bitmapInfo [AI] Pointer to bitmap metadata (color format, dimensions, palette).
	 * @param p_bitmapData [AI] Pointer to target buffer for decompressed pixel data.
	 * @param p_mxSmk [AI] Decoding context for current video stream.
	 * @param p_chunkData [AI] Raw frame and palette chunk source data.
	 * @param p_paletteChanged [AI] Indicates if the color palette chunk is included/has changed.
	 * @param p_list [AI] List to be filled with rectangles (dirty regions) updated by this frame.
	 * @return [AI] SUCCESS if frame is loaded properly, FAILURE otherwise.
	 * @details [AI] Performs palette animation, decompresses frame, fills list of screen areas that changed.
	 */
	static MxResult LoadFrame(
		MxBITMAPINFO* p_bitmapInfo,
		MxU8* p_bitmapData,
		MxSmk* p_mxSmk,
		MxU8* p_chunkData,
		MxBool p_paletteChanged,
		MxRect32List* p_list
	);

	/**
	 * @brief [AI] Retrieves and merges rectangles describing updated regions of the current frame.
	 * @param p_unk0x6b4 [AI] Current decoding context for frame.
	 * @param p_und [AI] Input/output parameter controlling initial/continuation state.
	 * @param p_smackRect [AI] Input/output buffer for SMK rectangle coordinates.
	 * @param p_rect [AI] Output: receives merged rectangle for frame update.
	 * @return [AI] TRUE if rectangle was found, FALSE if done with regions.
	 * @details [AI] Called after each frame to help identify dirty regions (for partial redraw/optimizations).
	 */
	static MxBool GetRect(MxU8* p_unk0x6b4, MxU16* p_und, u32* p_smackRect, MxRect32* p_rect);
};

#endif // MXSMK_H
