#ifndef MXVIDEOMANAGER_H
#define MXVIDEOMANAGER_H

#include "mxmediamanager.h"
#include "mxvideoparam.h"

#include <d3d.h>

class MxDisplaySurface;
class MxRect32;
class MxRegion;

// VTABLE: LEGO1 0x100dc810
// SIZE 0x64
/**
 * @brief [AI] Video subsystem manager for DirectDraw/Direct3D video rendering and presenter control.
 * 
 * The MxVideoManager class manages the DirectDraw and Direct3D interfaces, handles display surface allocation,
 * region-based updates and invalidation, and sorts and calls tickle on registered video presenters. It can
 * operate either using a tickle thread or by registering with the tickle manager for manual frame updates.
 * Palette management, presenter sorting (by Z), and region-based redisplay are also handled here.
 * 
 * The video parameters, such as palette and display region, are managed using a MxVideoParam instance.
 * This class is essential for rendering of animated and FMV sequences in LEGO Island and for their
 * associated presenter ticks.
 * 
 * This manager may create its own DirectDraw/Direct3D interfaces, or be configured to use externally provided ones.
 * @details [AI]
 */
class MxVideoManager : public MxMediaManager {
public:
	/**
	 * @brief [AI] Constructs a new MxVideoManager and initializes resources.
	 */
	MxVideoManager();
	/**
	 * @brief [AI] Destructor; cleans up all allocated resources (DirectDraw, display surface, etc.).
	 */
	~MxVideoManager() override;

	/**
	 * @brief [AI] Runs the per-frame tick/update including presenter tickle, surface update, and region display.
	 * Also sorts presenters and performs double-buffered region redraw.
	 * @return MxResult indicating operation success or failure. [AI]
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief [AI] Releases all display/video resources, any DirectDraw/Direct3D handles, and associated objects.
	 * @details Called by the base destructor.
	 */
	void Destroy() override;    // vtable+0x18

	/**
	 * @brief [AI] Main DirectDraw/Direct3D allocator and presenter chain creation.
	 * 
	 * Creates or assigns all underlying graphics interfaces, regions, palettes, and display surface, then spawns a tickle thread if so configured.
	 * p_pDirectDraw/p_pDirect3D are optionally provided externally. Also responsible for double-buffer backbuffer targets, and registering tickle interval.
	 * @param p_videoParam Video parameters, including palette, display region, etc. [AI]
	 * @param p_pDirectDraw The DirectDraw interface, can be external or newly allocated. [AI]
	 * @param p_pDirect3D The Direct3D2 interface, can be external or newly allocated. [AI]
	 * @param p_ddSurface1 Primary DirectDraw surface for backbuffer. [AI]
	 * @param p_ddSurface2 Secondary DirectDraw surface for double-buffering. [AI]
	 * @param p_ddClipper The DirectDraw clipper for region management. [AI]
	 * @param p_frequencyMS Tickle frequency in milliseconds. [AI]
	 * @param p_createThread TRUE to create a dedicated tickle thread, FALSE to register with the main tickle manager. [AI]
	 * @returns MxResult indicating success/failure. [AI]
	 */
	virtual MxResult VTable0x28(
		MxVideoParam& p_videoParam,
		LPDIRECTDRAW p_pDirectDraw,
		LPDIRECT3D2 p_pDirect3D,
		LPDIRECTDRAWSURFACE p_ddSurface1,
		LPDIRECTDRAWSURFACE p_ddSurface2,
		LPDIRECTDRAWCLIPPER p_ddClipper,
		MxU32 p_frequencyMS,
		MxBool p_createThread
	);                                                                                               // vtable+0x28

	/**
	 * @brief [AI] Similar to VTable0x28, this launches video with a new DirectDraw instance. Only used when the manager is responsible for all video resources.
	 * 
	 * Initializes video, region, palettes, and display surface, with optional thread or tickle interval.
	 * @param p_videoParam Configuration parameters and palette for the video.
	 * @param p_frequencyMS Tickle frequency in ms.
	 * @param p_createThread Whether to use internal tickle thread or not.
	 * @returns MxResult indicating status.
	 * @details [AI]
	 */
	virtual MxResult Create(MxVideoParam& p_videoParam, MxU32 p_frequencyMS, MxBool p_createThread); // vtable+0x2c

	/**
	 * @brief [AI] Applies (realizes) the palette to both MxVideoParam and hardware palette, and updates the display surface.
	 * @param p_palette Palette to use, can be NULL. [AI]
	 * @returns MxResult for operation.
	 */
	virtual MxResult RealizePalette(MxPalette* p_palette);                                           // vtable+0x30

	/**
	 * @brief [AI] Updates the visible video sub-rectangle inside the overall frame; typically for sub-region blits.
	 * @param p_x Offset X (left).
	 * @param p_y Offset Y (top).
	 * @param p_width Display rectangle width.
	 * @param p_height Display rectangle height.
	 * @details [AI]
	 */
	virtual void UpdateView(MxU32 p_x, MxU32 p_y, MxU32 p_width, MxU32 p_height);                    // vtable+0x34

	/**
	 * @brief [AI] Initializes video resources and zeros pointers for this manager.
	 * @returns MxResult indicating success/failure.
	 */
	MxResult Init();

	/**
	 * @brief [AI] Destroys all resources; called with destruction source information. Used for finer destructor control.
	 * @param p_fromDestructor TRUE if called from destructor, used for shutdown cleanup order. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] Invalidates a rectangular region in the display; marks it for redraw on next tick.
	 * @param p_rect Region of the display to be marked dirty and queued for redraw.
	 */
	void InvalidateRect(MxRect32& p_rect);

	/**
	 * @brief [AI] Sorts presenters in descending Z order for proper overdraw order during tickle (bubble-sort).
	 */
	void SortPresenterList();

	/**
	 * @brief [AI] Updates the portion of the display surface that is marked dirty based on m_region, performs the actual onscreen blit.
	 */
	void UpdateRegion();

	/**
	 * @brief [AI] Retrieves the current video parameter configuration used by this manager.
	 * @return Reference to the video parameter structure in use for this video manager.
	 */
	MxVideoParam& GetVideoParam() { return this->m_videoParam; }
	/**
	 * @brief [AI] Returns the current DirectDraw COM interface managed by this class (may be owned or external).
	 */
	LPDIRECTDRAW GetDirectDraw() { return this->m_pDirectDraw; }
	/**
	 * @brief [AI] Returns the display surface used for video output; for direct drawing and palette operations.
	 */
	MxDisplaySurface* GetDisplaySurface() { return this->m_displaySurface; }
	/**
	 * @brief [AI] Gets region-tracking structure managing currently invalidated rectangles.
	 */
	MxRegion* GetRegion() { return this->m_region; }

	// SYNTHETIC: LEGO1 0x100be280
	// MxVideoManager::`scalar deleting destructor'

protected:
	MxVideoParam m_videoParam;          ///< [AI] Video configuration, containing palette, source/dest rectangles, and other state. [Offset 0x2c]
	LPDIRECTDRAW m_pDirectDraw;         ///< [AI] DirectDraw interface pointer. May be allocated here, or passed in/injected. [0x50]
	LPDIRECT3D2 m_pDirect3D;            ///< [AI] Direct3D2 interface pointer, for 3D presentation and device context. [0x54]
	MxDisplaySurface* m_displaySurface; ///< [AI] Concrete blitting/output surface where final image is copied each frame. [0x58]
	MxRegion* m_region;                 ///< [AI] Tracks regions that have been invalidated and need to be updated/redrawn. [0x5c]
	MxBool m_unk0x60;                   ///< [AI] TRUE if manager owns the DirectDraw/Direct3D objects and should release them; FALSE if external. [0x60]
};

#endif // MXVIDEOMANAGER_H