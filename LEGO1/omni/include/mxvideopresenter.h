#ifndef MXVIDEOPRESENTER_H
#define MXVIDEOPRESENTER_H

#include "decomp.h"
#include "mxbitmap.h"
#include "mxgeometry.h"
#include "mxmediapresenter.h"

#include <ddraw.h>

// VTABLE: LEGO1 0x100d4be8
// SIZE 0x64

/**
 * @brief Derived video presenter responsible for displaying video frames using DirectDraw surfaces.
 * @details [AI] MxVideoPresenter manages video playback, bitmap frames, alpha masking for hit tests, palette management, and rendering output onto the display. It is used for both software and hardware-accelerated video display and ties into the video tickle/update system.
 */
class MxVideoPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief Constructs a new MxVideoPresenter and initializes internal state.
	 * @details [AI]
	 */
	MxVideoPresenter() { Init(); }

	/**
	 * @brief Loads and processes header information from a video stream chunk.
	 * @param p_chunk Pointer to the stream chunk containing header data. [AI]
	 * @details [AI] This is intended to be implemented in derived classes to parse format-specific header information.
	 */
	virtual void LoadHeader(MxStreamChunk* p_chunk) {} // vtable+0x5c

	/**
	 * @brief Allocates and sets up the display bitmap for video frame data.
	 * @details [AI] Typically called after header information is available so the bitmap can be sized appropriately for the video media.
	 */
	virtual void CreateBitmap() {} // vtable+0x60

	/**
	 * @brief Advances video playback to the next frame, handling decoding and playback progression.
	 * @details [AI] This method is responsible for decoding/loading the next frame and advancing state within the tickle loop.
	 */
	virtual void NextFrame(); // vtable+0x64

	/**
	 * @brief Loads and processes frame data from a video stream chunk.
	 * @param p_chunk Pointer to the stream chunk containing frame data. [AI]
	 * @details [AI] Frame loading typically performs format-specific decoding or copying of bitmap data into the display buffer.
	 */
	virtual void LoadFrame(MxStreamChunk* p_chunk) {} // vtable+0x68

	/**
	 * @brief Presents the current frame using the chosen output mechanism (e.g., blitting to screen).
	 * @details [AI] Handles both hardware-accelerated surfaces and software presentation, including correct color keying and region-drawing if necessary.
	 */
	virtual void PutFrame(); // vtable+0x6c

	/**
	 * @brief Loads or establishes the palette for display from the current video format or media.
	 * @details [AI] Often required for paletted video data (such as 8-bit surfaces).
	 */
	virtual void RealizePalette() {} // vtable+0x70

	/**
	 * @brief Unknown/potentially format-specific method (VTable0x74).
	 * @details [AI_SUGGESTED_NAME: FormatSpecificOperation] [AI] This placeholder method is likely for extending media-specific features or queries.
	 */
	virtual undefined VTable0x74(); // vtable+0x74

	/**
	 * @brief Destroys the MxVideoPresenter, releasing owned resources and unregistering from the manager.
	 * @details [AI] Calls Destroy(TRUE) to indicate destruction from the destructor context.
	 */
	~MxVideoPresenter() override { Destroy(TRUE); } // vtable+0x00

	/**
	 * @brief Destroys internal resources for the presenter.
	 * @details [AI] Calls Destroy(FALSE) to indicate manual destruction.
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief Retrieves the DirectDraw surface used for hardware-accelerated rendering.
	 * @return Pointer to the DirectDraw surface used by this presenter. [AI]
	 * @details [AI] Used to integrate with hardware-accelerated drawing pipelines.
	 */
	virtual LPDIRECTDRAWSURFACE VTable0x78() { return m_unk0x58; } // vtable+0x78

	/**
	 * @brief Checks if this presenter has either a video frame bitmap or alpha mask available.
	 * @return TRUE if either is valid, otherwise FALSE. [AI]
	 * @details [AI] Used to quickly test if video content is available for hit testing or drawing.
	 */
	virtual MxBool VTable0x7c() { return m_frameBitmap != NULL || m_alpha != NULL; } // vtable+0x7c

	/**
	 * @brief Returns the width of the current bitmap or alpha mask in pixels.
	 * @details [AI] Alpha mask width is prioritized if available, otherwise bitmap width is used.
	 */
	virtual MxS32 GetWidth() { return m_alpha ? m_alpha->GetWidth() : m_frameBitmap->GetBmiWidth(); } // vtable+0x80

	/**
	 * @brief Returns the height of the current bitmap or alpha mask in pixels.
	 * @details [AI] Alpha mask height is prioritized if available, otherwise bitmap height is used.
	 */
	virtual MxS32 GetHeight()
	{
		return m_alpha ? m_alpha->GetHeight() : m_frameBitmap->GetBmiHeightAbs();
	} // vtable+0x84

	/**
	 * @brief Returns the class name string for this presenter type.
	 * @details [AI] Used for run-time class identification and IsA checks.
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0760
		return "MxVideoPresenter";
	}

	/**
	 * @brief Returns the run-time class name of this presenter instance.
	 * @details [AI] Used for polymorphic identification and the IsA hierarchy check.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief Determines if this object is or derives from a class with the given name.
	 * @param p_name Name of the class to check. [AI]
	 * @return TRUE on a match or base-class match, FALSE otherwise. [AI]
	 * @details [AI] Recursively checks up the parent class chain.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxVideoPresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

	/**
	 * @brief Advance logic for the "ready" tickle state. Loads headers and transitions state.
	 * @details [AI] Loads the video header from the next stream chunk and sets tickle state.
	 */
	void ReadyTickle() override;                 // vtable+0x18

	/**
	 * @brief Advance logic for the "starting" tickle state (frame setup).
	 * @details [AI] Creates the bitmap buffer and prepares for streaming.
	 */
	void StartingTickle() override;              // vtable+0x1c

	/**
	 * @brief Advance logic for the "streaming" tickle state (typical video playback).
	 * @details [AI] Loads video frames/ticks as appropriate for elapsed media time.
	 */
	void StreamingTickle() override;             // vtable+0x20

	/**
	 * @brief Advance logic for the "repeating" tickle state (media looping).
	 * @details [AI] Handles looped playback, loads frames corresponding to looped time.
	 */
	void RepeatingTickle() override;             // vtable+0x24

	/**
	 * @brief Advance logic for the "freezing" tickle state (sustain after playback).
	 * @details [AI] Handles the delay after playback by counting sustain time.
	 */
	void FreezingTickle() override;              // vtable+0x28

	/**
	 * @brief Adds this presenter to the global video manager.
	 * @return SUCCESS if added, FAILURE if not. [AI]
	 * @details [AI] Presenter registration is required for global invalidation/redraw integration.
	 */
	MxResult AddToManager() override;            // vtable+0x34

	/**
	 * @brief Signals the end of the current playback action.
	 * @details [AI] Cleans up and invalidates regions after playback stops.
	 */
	void EndAction() override;                   // vtable+0x40

	/**
	 * @brief Writes the frame to the display device if appropriate.
	 * @details [AI] Called within the tickle loop to present active video content.
	 */
	MxResult PutData() override;                 // vtable+0x4c

	/**
	 * @brief Determines if a point is inside the non-transparent region of frame/alpha.
	 * @param p_x X pixel coordinate (absolute). [AI]
	 * @param p_y Y pixel coordinate (absolute). [AI]
	 * @return TRUE if hit, otherwise FALSE. [AI]
	 * @details [AI] Used for input/mouse hit testing.
	 */
	MxBool IsHit(MxS32 p_x, MxS32 p_y) override; // vtable+0x50

	// VTABLE: LEGO1 0x100dc2bc
	// SIZE 0x0c
	/**
	 * @brief Opaque mask used for efficient hit testing against video transparency.
	 * @details [AI] An alpha mask representing frame pixel visibility as a bitmask for hit testing. Constructed from or copied from a video frame. Used to determine clickable regions or pointer hits on non-rectangular/transparent video.
	 */
	class AlphaMask {
	public:
		/**
		 * @brief Creates an alpha mask from a bitmap, recording pixel presence in a bitmask.
		 * @param p_bitmap Source bitmap to generate mask from. [AI]
		 */
		AlphaMask(const MxBitmap&);

		/**
		 * @brief Copy constructor, clones the bitmask and size.
		 * @param p_alpha Source alpha mask. [AI]
		 */
		AlphaMask(const AlphaMask&);

		/**
		 * @brief Frees the bitmask memory.
		 * @details [AI]
		 */
		virtual ~AlphaMask();

		/**
		 * @brief Checks whether the specified local coordinate is visible in the mask.
		 * @param p_x X coordinate (0-based, mask-local). [AI]
		 * @param p_y Y coordinate (0-based, mask-local). [AI]
		 * @return 1 if hit (non-transparent), 0 otherwise. [AI]
		 * @details [AI]
		 */
		MxS32 IsHit(MxU32 p_x, MxU32 p_y);

		/**
		 * @brief [AI] Width of the alpha mask in pixels.
		 */
		MxS32 GetWidth() const { return m_width; }
		/**
		 * @brief [AI] Height of the alpha mask in pixels.
		 */
		MxS32 GetHeight() const { return m_height; }

	private:
		MxU8* m_bitmask; ///< Array of bits holding pixel mask [AI]
		MxU16 m_width;   ///< Width in pixels [AI]
		MxU16 m_height;  ///< Height in pixels [AI]
	};

	/**
	 * @brief Utility function to adjust source/dest rectangles to stay within allowed bounds.
	 * @param p_rectDest Destination rectangle (will be clipped). [AI]
	 * @param p_rectSrc Source rectangle (will be clipped). [AI]
	 * @return 1 if unchanged, 0 if src rect was adjusted to match dest, -1 if unclippable. [AI]
	 * @details [AI] Used in DirectDraw blitting to guarantee rendering does not exceed screen limits.
	 */
	inline MxS32 PrepareRects(RECT& p_rectDest, RECT& p_rectSrc);

	/**
	 * @brief Returns the frame bitmap currently used for this presenter.
	 * @details [AI] This bitmap contains the raw pixel data for the current frame.
	 */
	MxBitmap* GetBitmap() { return m_frameBitmap; }

	/**
	 * @brief Returns this presenter's alpha mask for hit testing.
	 * @details [AI] May be nullptr if no alpha mask is present.
	 */
	AlphaMask* GetAlphaMask() { return m_alpha; }

	/**
	 * @brief Provides a pointer to the start of frame bitmap data at a given coordinate.
	 * @param p_left X coordinate within the bitmap. [AI]
	 * @param p_top Y coordinate within the bitmap. [AI]
	 * @return Pointer to first byte of pixel data at the given location. [AI]
	 * @details [AI] Used for pixel-level access into the video frame.
	 */
	MxU8* GetBitmapStart(MxS32 p_left, MxS32 p_top) { return m_frameBitmap->GetStart(p_left, p_top); }

	/**
	 * @brief Sets internal miscellaneous state flags.
	 * @param p_e Value to set in bit N, for bits 0-4. [AI]
	 * @details [AI] These bits are used for logic state and presentation properties (uncertain specifics).
	 */
	void SetBit0(BOOL p_e) { m_flags.m_bit0 = p_e; }
	void SetBit1(BOOL p_e) { m_flags.m_bit1 = p_e; }
	void SetBit2(BOOL p_e) { m_flags.m_bit2 = p_e; }
	void SetBit3(BOOL p_e) { m_flags.m_bit3 = p_e; }
	void SetBit4(BOOL p_e) { m_flags.m_bit4 = p_e; }

	/**
	 * @brief Gets internal miscellaneous state flags (bits 0-4).
	 * @details [AI] Used for logic and presentation decision-making.
	 */
	BYTE GetBit0() { return m_flags.m_bit0; }
	BYTE GetBit1() { return m_flags.m_bit1; }
	BYTE GetBit2() { return m_flags.m_bit2; }
	BYTE GetBit3() { return m_flags.m_bit3; }
	BYTE GetBit4() { return m_flags.m_bit4; }

private:
	/**
	 * @brief Initializes video presenter state for construction or destruction.
	 * @details [AI] Sets initial values and queries video manager for integration.
	 */
	void Init();

protected:
	/**
	 * @brief Releases resources and unregisters presenter from the video manager.
	 * @param p_fromDestructor If TRUE, indicates called from destructor. [AI]
	 * @details [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	MxBitmap* m_frameBitmap;       ///< Bitmap for current video frame. [AI]
	AlphaMask* m_alpha;            ///< Alpha mask for hit testing. May be null. [AI]
	LPDIRECTDRAWSURFACE m_unk0x58; ///< DirectDraw surface for hardware video rendering. [AI]
	MxS16 m_unk0x5c;               ///< Loop/advance/frame decode counter. [AI]
	FlagBitfield m_flags;          ///< Miscellaneous flags for object and UI state. [AI]
	MxLong m_unk0x60;              ///< Last freeze time/start of sustain interval. [AI]
};

#endif // MXVIDEOPRESENTER_H
