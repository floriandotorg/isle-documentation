#ifndef MXFLCPRESENTER_H
#define MXFLCPRESENTER_H

#include "decomp.h"
#include "mxvideopresenter.h"

#include <flic.h>

// VTABLE: LEGO1 0x100dc2c0
// VTABLE: BETA10 0x101c1eb0
// SIZE 0x68

/**
 * @brief Implements playback and presentation of Autodesk FLIC (FLC) video streams. [AI]
 * @details [AI] MxFlcPresenter is a video presenter subclass specialized for handling the animation format FLIC (FLC). 
 * It manages FLC header parsing, frame decoding, bitmap and palette creation, and screen drawing integration within
 * the LEGO Island engine's video / multimedia framework. [AI]
 */
class MxFlcPresenter : public MxVideoPresenter {
public:
	/**
	 * @brief Constructs a FLIC presenter and initializes state. [AI]
	 */
	MxFlcPresenter();

	/**
	 * @brief Cleans up FLIC presenter and associated resources (including FLIC header memory). [AI]
	 */
	~MxFlcPresenter() override;

	/**
	 * @brief [AI] Runtime type check; determines if this is a MxFlcPresenter or a base. [AI]
	 * @param p_name Name of type to check against (usually returned from ClassName()). [AI]
	 * @retval TRUE if match is found for this class or base classes. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxFlcPresenter::ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Provides the class handler string for presenter registration/dispatch. [AI]
	 * @return Static type string "MxFlcPresenter". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f43c8
		return "MxFlcPresenter";
	}

	/**
	 * @brief [AI] Returns the runtime class name string for this presenter. [AI]
	 * @return Value from HandlerClassName(). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Loads FLIC header data from a stream chunk into memory for subsequent decoding. [AI]
	 * @details [AI] Copies the chunk data into newly allocated memory interpreted as a FLIC_HEADER. [AI]
	 * @param p_chunk Chunk containing FLIC header data. [AI]
	 */
	void LoadHeader(MxStreamChunk* p_chunk) override; // vtable+0x5c

	/**
	 * @brief [AI] Creates a bitmap sized from FLIC header for decoded frame output. [AI]
	 * @details [AI] If a bitmap exists from a previous frame, it will be deleted and reallocated. [AI]
	 */
	void CreateBitmap() override;                     // vtable+0x60

	/**
	 * @brief [AI] Decodes a FLIC frame from the stream chunk, applies it to the bitmap, and triggers any
	 * palette/region updates. [AI]
	 * @param p_chunk Chunk containing FLIC frame data and region rectangles. [AI]
	 * @details [AI] Handles both frame image decoding and palette management (if required). Also
	 * notifies the video manager about which screen regions have changed for redrawing. [AI]
	 */
	void LoadFrame(MxStreamChunk* p_chunk) override;  // vtable+0x68

	/**
	 * @brief [AI] Realizes the palette for the current frame by creating a palette object (MxPalette)
	 * and updating the video manager's palette state. [AI]
	 * @details [AI] Palette is created from the frame bitmap and passed to the engine's palette manager. [AI]
	 */
	void RealizePalette() override;                   // vtable+0x70

	// SYNTHETIC: LEGO1 0x100b3400
	// MxFlcPresenter::`scalar deleting destructor'

protected:
	/**
	 * @brief [AI] Internal cached FLIC header for video decoding and playback. [AI]
	 * @details [AI] Allocated in LoadHeader(), freed in destructor. [AI]
	 */
	FLIC_HEADER* m_flcHeader; // 0x64
};

#endif // MXFLCPRESENTER_H
