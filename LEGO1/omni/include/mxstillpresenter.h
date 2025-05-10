#ifndef MXSTILLPRESENTER_H
#define MXSTILLPRESENTER_H

#include "decomp.h"
#include "mxvideopresenter.h"

// VTABLE: LEGO1 0x100d7a38
// SIZE 0x6c

/**
 * @brief [AI] Presenter for single still image/bitmap media sources in the game. Handles loading, creating, and rendering bitmap images and their palettes, supporting positioning and visibility.
 * @details [AI] MxStillPresenter is responsible for displaying and managing still images within the Lego Island engine. It manages the memory and presentation pipeline for single frame image data, providing bitmap and palette management, rendering area invalidation, and configuration through action extra data.
 */
class MxStillPresenter : public MxVideoPresenter {
public:
	/**
	 * @brief [AI] Constructs an MxStillPresenter. Initializes m_bitmapInfo pointer to NULL.
	 */
	MxStillPresenter() { m_bitmapInfo = NULL; }

	/**
	 * @brief [AI] Destructor—ensures resource cleanup of bitmap information and other associated memory.
	 */
	~MxStillPresenter() override { Destroy(TRUE); } // vtable+0x00

	/**
	 * @brief [AI] Destroys the presenter's resources, optionally called by the destructor for complete cleanup.
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief [AI] Returns the handler class name string for this Presenter type ("MxStillPresenter").
	 * @return [AI] Static string literal with the handler name.
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0184
		return "MxStillPresenter";
	}

	/**
	 * @brief [AI] Returns the class name of this presenter type. Used for run-time type identification.
	 * @return [AI] Static string literal with the class name.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Run-time type check against the provided type name. Compares to MxStillPresenter, and if not matching, delegates to MxVideoPresenter.
	 * @param p_name [AI] Class name to check identity against.
	 * @return [AI] TRUE if the provided name matches this class or its parent.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxStillPresenter::ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Handles transition to the starting state of the presenter, processing palette realization if needed.
	 */
	void StartingTickle() override;                   // vtable+0x1c

	/**
	 * @brief [AI] Main frame advancing logic, loads the next frame if the elapsed time is appropriate.
	 */
	void StreamingTickle() override;                  // vtable+0x20

	/**
	 * @brief [AI] Repetition tickle logic—handles repeated action/time-based state changes.
	 */
	void RepeatingTickle() override;                  // vtable+0x24

	/**
	 * @brief [AI] Parses extra action data for bitmap configuration, such as visibility or image mapping, from the associated DSAction.
	 */
	void ParseExtra() override;                       // vtable+0x30

	/**
	 * @brief [AI] Sets the enabled/disabled state of the presenter, updating the video manager's rendering as needed.
	 * @param p_enable [AI] TRUE to enable, FALSE to disable the presenter (visibility).
	 */
	void Enable(MxBool p_enable) override;            // vtable+0x54

	/**
	 * @brief [AI] Loads header chunk data into the presenter's bitmap info buffer (BITMAPINFO structure).
	 * @param p_chunk [AI] Stream chunk containing header/bitmap metadata.
	 */
	void LoadHeader(MxStreamChunk* p_chunk) override; // vtable+0x5c

	/**
	 * @brief [AI] Allocates and constructs the bitmap from internal bitmap info, importing palette and image layout information.
	 */
	void CreateBitmap() override;                     // vtable+0x60

	/**
	 * @brief [AI] Loads the next single image frame from the stream and updates the presenter's display state.
	 */
	void NextFrame() override;                        // vtable+0x64

	/**
	 * @brief [AI] Copies frame image data from chunk to presenter's bitmap and prepares for rendering, including palette and alpha mask if necessary.
	 * @param p_chunk [AI] Stream chunk containing the image/frame pixel data.
	 */
	void LoadFrame(MxStreamChunk* p_chunk) override;  // vtable+0x68

	/**
	 * @brief [AI] Realizes/updates the palette in the current video environment using the frame bitmap and notifies the video manager.
	 */
	void RealizePalette() override;                   // vtable+0x70

	/**
	 * @brief [AI] Sets the pixel-based position of the presented image. Invalidate and update the required screen regions in the video manager when enabled.
	 * @param p_x [AI] The new X coordinate for the image region's top-left corner.
	 * @param p_y [AI] The new Y coordinate for the image region's top-left corner.
	 */
	virtual void SetPosition(MxS32 p_x, MxS32 p_y);   // vtable+0x88

	/**
	 * @brief [AI] Clones the presenter, attempting to fully duplicate internal state and associated memory resources.
	 * @return [AI] Pointer to a newly created clone, or NULL on failure.
	 */
	virtual MxStillPresenter* Clone();                // vtable+0x8c

private:
	/**
	 * @brief [AI] Internal destroy helper—performs resource cleanup related to the presenter's image data.
	 * @param p_fromDestructor [AI] TRUE if called from destructor, otherwise FALSE for direct destroy.
	 */
	void Destroy(MxBool p_fromDestructor);

	MxLong m_chunkTime;         /**< @brief [AI] Timestamp (in ms or appropriate time unit) of the current image chunk being displayed. */
	MxBITMAPINFO* m_bitmapInfo; /**< @brief [AI] Stores Windows BITMAPINFO structure for the loaded still image, including palette and resolution. */
};

// SYNTHETIC: LEGO1 0x100436e0
// MxStillPresenter::`scalar deleting destructor'

#endif // MXSTILLPRESENTER_H