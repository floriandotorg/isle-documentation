#ifdef 0

// LIBRARY: LEGO1 0x100cd782
// LIBRARY: BETA10 0x1015fb82
/**
 * @brief [AI] Retrieves the size tables needed for SMK (Smacker) video decoding. The tables determine how data chunks are interpreted for decompression.
 * @details [AI] Used internally by the Smacker video codec to initialize or access decoding lookup tables for each frame or video stream.
 */
void _SmackGetSizeTables();

// LIBRARY: LEGO1 0x100cd7e8
// LIBRARY: BETA10 0x1015fbe8
/**
 * @brief [AI] Processes or applies the internal tables used during SMK (Smacker) video decoding.
 * @details [AI] Called by the video decompression logic when parsing and reconstructing frame data, using tables to transform compressed data into screen pixels.
 */
void _SmackDoTables();

// LIBRARY: LEGO1 0x100cda83
// LIBRARY: BETA10 0x1015fe83
/**
 * @brief [AI] Decodes a Smacker (SMK) frame into a general-purpose memory buffer.
 * @details [AI] Performs frame decompression for a single SMK video frame, writing the output image pixel data into a provided destination buffer, usually for further processing or blitting.
 */
void _SmackDoFrameToBuffer();

// LIBRARY: LEGO1 0x100cea58
// LIBRARY: BETA10 0x10160e58
/**
 * @brief [AI] Decodes and renders a Smacker (SMK) video frame directly to VESA video memory.
 * @details [AI] Used for fast video playback by decompressing the frame and writing pixels straight to the graphics framebuffer in VESA-compatible modes.
 */
void _SmackDoFrameToVESA();

// LIBRARY: LEGO1 0x100cfd90
/**
 * @brief [AI] Decodes and processes SMK (Smacker) PCM audio from a video stream.
 * @details [AI] Handles the decompression and possibly format conversion of audio data stored within a SMK file, outputting PCM samples for playback.
 */
void _SmackDoPCM();

// LIBRARY: LEGO1 0x100d052c
// LIBRARY: BETA10 0x1016292c
/**
 * @brief [AI] Retrieves delta size tables for SMK decoding.
 * @details [AI] Used in difference-frame decoding, this function provides the lookup (or calculation) of how pixel/region delta sizes are managed in differential frames within SMK videos.
 */
void _SmackGetSizeDeltas();

// LIBRARY: LEGO1 0x100d0543
// LIBRARY: BETA10 0x10162943
/**
 * @brief [AI] Calculates or provides the rectangular region (bounding box) for the current video frame operation.
 * @details [AI] Used to determine which portion of the screen or buffer is being read/written to, for optimized compositing or updating only a subregion of the video.
 */
void _SmackGetRect();

// LIBRARY: LEGO1 0x100d0654
/**
 * @brief [AI] Remaps internal SMK codec tables, possibly for palette or frame re-interpretation during video decoding.
 * @details [AI] May be used during effects that require reinterpretation of pixel data, or when the video format/palette changes during playback.
 */
void _SmackRemapTables();

#endif