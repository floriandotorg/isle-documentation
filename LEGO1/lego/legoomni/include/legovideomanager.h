#ifndef LEGOVIDEOMANAGER_H
#define LEGOVIDEOMANAGER_H

#include "decomp.h"
#include "legophonemelist.h"
#include "mxvideomanager.h"

#include <d3drm.h>
#include <ddraw.h>

class Lego3DManager;
class LegoROI;
class MxDirect3D;
class MxStopWatch;
struct ViewportAppData;

namespace Tgl
{
class Renderer;
}

/**
 * @class LegoVideoManager
 * @brief [AI] Extends the functionality of MxVideoManager to provide LEGO Island–specific video and 3D graphics management, including interface with DirectDraw/Direct3D, 3D scene composition, custom resource and palette/sky color handling, and in-engine FPS/cursor overlays. [AI]
 * @details [AI] This manager is responsible for handling both 2D (video overlays, cursor, movies) and 3D rendering using Direct3D Retained Mode, palette manipulations, and integrating multiple engine components including Lego3DManager, phoneme reference lists for speech, and presenter-layer management. It also manages DirectDraw surfaces for custom overlays like the cursor and FPS meter, handles switching between fullscreen movies and gameplay, and exposes logic for enabling/disabling the 3D device state. [AI]
 */
// VTABLE: LEGO1 0x100d9c88
// SIZE 0x590
class LegoVideoManager : public MxVideoManager {
public:
	/**
	 * @brief [AI] Constructs a new LegoVideoManager, initializing all graphics, rendering, and state members to default. [AI]
	 */
	LegoVideoManager();

	/**
	 * @brief [AI] Releases all allocated resources and restores graphics state. [AI]
	 */
	~LegoVideoManager() override;

	/**
	 * @brief [AI] Enables the Direct3D Retained Mode (RM) rendering device, and re-creates the device/viewport if currently paused (e.g. after a fullscreen movie). [AI]
	 * @return [AI] Returns 0 on success, -1 if not paused or on error.
	 */
	int EnableRMDevice();

	/**
	 * @brief [AI] Disables the Direct3D Retained Mode (RM) rendering device and saves/restores 3D state as needed. [AI]
	 * @return [AI] Returns 0 on success, -1 if already paused or on error.
	 */
	int DisableRMDevice();

	/**
	 * @brief [AI] Convenience method to enable or disable fullscreen movie playback with default scaling. [AI]
	 * @param p_enable True to enable fullscreen movie, false to disable. [AI]
	 */
	void EnableFullScreenMovie(MxBool p_enable);

	/**
	 * @brief [AI] Enables or disables fullscreen movie playback, with option to scale video content. [AI]
	 * @param p_enable True to enable, false to disable. [AI]
	 * @param p_scale  True to scale movie to window/screen size; false to maintain original size. [AI]
	 */
	void EnableFullScreenMovie(MxBool p_enable, MxBool p_scale);

	/**
	 * @brief [AI] Updates the position of the custom software cursor overlay, and ensures it renders on the next frame. Caps position within window bounds. [AI]
	 * @param p_cursorX X pixel coordinate. [AI]
	 * @param p_cursorY Y pixel coordinate. [AI]
	 */
	void MoveCursor(MxS32 p_cursorX, MxS32 p_cursorY);

	/**
	 * @brief [AI] Toggles display of the on-screen frames-per-second (FPS) overlay. [AI]
	 * @param p_visible Show FPS overlay if true, hide if false. [AI]
	 */
	void ToggleFPS(MxBool p_visible);

	/**
	 * @brief [AI] Performs per-frame update for all video, 3D, and interface layers. Includes tickling all presenters, handling overlays, and performing buffer swaps. [AI]
	 * @return [AI] Always returns SUCCESS. [AI]
	 */
	MxResult Tickle() override;

	/**
	 * @brief [AI] Cleans up graphics resources, disables overlays, removes from 3D scene and releases presenters/lists. [AI]
	 */
	void Destroy() override;

	/**
	 * @brief [AI] Initializes LegoVideoManager with video parameters, creates all Direct3D, 3DManager, and renderer resources, and sets up camera/view state. [AI]
	 * @param p_videoParam Video settings (resolution, palette, etc.) [AI]
	 * @param p_frequencyMS Tick/update frequency for rendering. [AI]
	 * @param p_createThread If true, creates a separate rendering thread. [AI]
	 * @return [AI] SUCCESS if all initialization succeeded; otherwise FAILURE. [AI]
	 */
	MxResult Create(MxVideoParam& p_videoParam, MxU32 p_frequencyMS, MxBool p_createThread) override;

	/**
	 * @brief [AI] Sets the realized palette to use for rendering and updates the display surface. [AI]
	 * @param p_palette Input palette to realize and install. [AI]
	 * @return [AI] Returns SUCCESS if palette set. [AI]
	 */
	MxResult RealizePalette(MxPalette*) override;

	/**
	 * @brief [AI] Notifies the manager of changes in view rectangle, updating the 3D device's viewport as needed. [AI]
	 * @param p_x Left pixel. [AI] @param p_y Top pixel. [AI] @param p_width New width; 0 for unchanged. [AI] @param p_height New height; 0 for unchanged. [AI]
	 */
	void UpdateView(MxU32 p_x, MxU32 p_y, MxU32 p_width, MxU32 p_height) override;

	/**
	 * @brief [AI] Finds a presenter at the specific screen coordinates (for hit testing). [AI]
	 * @param p_x Screen X coordinate. [AI]
	 * @param p_y Screen Y coordinate. [AI]
	 * @return [AI] The presenter if found (typically for interactive overlays, e.g. buttons), or NULL otherwise. [AI]
	 */
	virtual MxPresenter* GetPresenterAt(MxS32 p_x, MxS32 p_y);

	/**
	 * @brief [AI] Returns the currently installed phoneme list for in-game speech synchronization. [AI]
	 * @return [AI] The LegoPhonemeList reference pointer. [AI]
	 */
	virtual LegoPhonemeList* GetPhonemeList() { return m_phonemeRefList; }

	/**
	 * @brief [AI] Sets the RGB color for the sky/background in the 3D view and updates the palette accordingly. [AI]
	 * @param p_red Red component (0-1). [AI]
	 * @param p_green Green component (0-1). [AI]
	 * @param p_blue Blue component (0-1). [AI]
	 */
	void SetSkyColor(float p_red, float p_green, float p_blue);

	/**
	 * @brief [AI] Requests that the palette override the sky color entry, for movie transitions or when re-enabling 3D rendering. [AI]
	 * @param p_shouldOverride True to force sky color override; false to allow normal palette. [AI]
	 */
	void OverrideSkyColor(MxBool p_shouldOverride);

	/**
	 * @brief [AI] Resets palette entries and re-installs base palette, restoring sky color if requested. [AI]
	 * @param p_ignoreSkyColor True to keep current sky color, false to reload from default. [AI]
	 * @return [AI] Returns SUCCESS if palette reset. [AI]
	 */
	MxResult ResetPalette(MxBool p_ignoreSkyColor);

	/**
	 * @brief [AI] Searches all active presenters for one associated with the given action object name. [AI]
	 * @param p_char Object/action name of interest. [AI]
	 * @return [AI] Pointer to presenter if found, NULL otherwise. [AI]
	 */
	MxPresenter* GetPresenterByActionObjectName(const char* p_char);

	/**
	 * @brief [AI] Sets rendering state to allow PutData for all overlay presenters, disables 3D main rendering. [AI]
	 */
	void FUN_1007c520();

	/**
	 * @brief [AI] Returns the underlying renderer for this manager; normally a Direct3D Retained Mode wrapper. [AI]
	 * @return [AI] The Tgl::Renderer pointer. [AI]
	 */
	Tgl::Renderer* GetRenderer() { return m_renderer; }

	/**
	 * @brief [AI] Returns the Lego3DManager for this manager, which owns all 3D scene representations and view control. [AI]
	 */
	Lego3DManager* Get3DManager() { return m_3dManager; }

	/**
	 * @brief [AI] Returns the viewpoint ROI for the current view/camera. [AI]
	 */
	LegoROI* GetViewROI() { return m_viewROI; }

	/**
	 * @brief [AI] Returns the active Direct3D wrapper (engine/utility) object. [AI]
	 */
	MxDirect3D* GetDirect3D() { return m_direct3d; }

	/**
	 * @brief [AI] Indicates if 3D rendering is enabled and active (false if paused/fullscreen movie). [AI]
	 */
	MxBool GetRender3D() { return m_render3d; }

	/**
	 * @brief [AI] Returns the elapsed wall clock seconds since the last Tickle update (frame time). [AI]
	 */
	double GetElapsedSeconds() { return m_elapsedSeconds; }

	/**
	 * @brief [AI] Enables or disables main 3D rendering (e.g., used internally on video transitions). [AI]
	 * @param p_render3d True to enable, false to disable. [AI]
	 */
	void SetRender3D(MxBool p_render3d) { m_render3d = p_render3d; }

	/**
	 * @brief [AI] Used to control a non-interactive, non-main rendering update (PutData only). [AI]
	 * @param p_unk0x554 True to enter overlay (PutData-only) mode. [AI]
	 */
	void SetUnk0x554(MxBool p_unk0x554) { m_unk0x554 = p_unk0x554; }

private:
	/**
	 * @brief [AI] Creates the main Direct3D wrapper object and initializes the core 3D device interfaces. [AI]
	 * @return [AI] SUCCESS if successfully created, FAILURE otherwise. [AI]
	 */
	MxResult CreateDirect3D();

	/**
	 * @brief [AI] Applies/chooses Direct3DRM device quality, shading, and texture modes based on hardware caps. [AI]
	 * @return [AI] SUCCESS if successful, FAILURE if no D3DRM device is available. [AI]
	 */
	MxResult ConfigureD3DRM();

	/**
	 * @brief [AI] Draws the FPS overlay to a DirectDraw surface, updating every few seconds with a new measurement. [AI]
	 */
	void DrawFPS();

	/**
	 * @brief [AI] Draws the custom cursor overlay to the current DirectDraw backbuffer at the tracked position. [AI]
	 */
	inline void DrawCursor();

	/// @brief Renderer implementation (Direct3D Retained Mode). [AI]
	Tgl::Renderer* m_renderer;            // 0x64

	/// @brief Manages the world/scene and camera in 3D engine. [AI]
	Lego3DManager* m_3dManager;           // 0x68

	/// @brief Current view's region-of-interest, i.e., camera node in 3D space. [AI]
	LegoROI* m_viewROI;                   // 0x6c

	/// @brief Unknown. [AI]
	undefined4 m_unk0x70;                 // 0x70

	/// @brief Direct3D interface wrapper for device/buffer/palette/state logic. [AI]
	MxDirect3D* m_direct3d;               // 0x74

	/// @brief Unknown DirectDraw/3D/manager state buffer. [AI]
	undefined4 m_unk0x78[27];             // 0x78

	/// @brief True while 3D rendering is enabled (not paused/fullscreen movie). [AI]
	MxBool m_render3d;                    // 0xe4

	/// @brief Used to enable alternate presenter-only rendering loop. [AI]
	MxBool m_unk0xe5;                     // 0xe5

	/// @brief Used for mode switching in 3D/palette (fullscreen movie etc). [AI]
	MxBool m_unk0xe6;                     // 0xe6

	/// @brief Palette entries, up to 256 for 8bpp. [AI]
	PALETTEENTRY m_paletteEntries[256];   // 0xe7

	/// @brief Phoneme list for speech, loaded from resource/script. [AI]
	LegoPhonemeList* m_phonemeRefList;    // 0x4e8

	/// @brief True if a fullscreen movie is currently playing. [AI]
	MxBool m_isFullscreenMovie;           // 0x4ec

	/// @brief Backed up/restored palette used for fullscreen movie state. [AI]
	MxPalette* m_palette;                 // 0x4f0

	/// @brief Used for frame timing/calculation. [AI]
	MxStopWatch* m_stopWatch;             // 0x4f4

	/// @brief Stores elapsed seconds (last frame update). [AI]
	double m_elapsedSeconds;              // 0x4f8

	/// @brief True if game is currently in full screen movie PutData mode. [AI]
	MxBool m_fullScreenMovie;             // 0x500

	/// @brief If true, the custom cursor overlay is drawn this frame. [AI]
	MxBool m_drawCursor;                  // 0x501

	/// @brief Last cursor X used for BltFast. [AI]
	MxS32 m_cursorXCopy;                  // 0x504

	/// @brief Last cursor Y used for BltFast. [AI]
	MxS32 m_cursorYCopy;                  // 0x508

	/// @brief X coordinate to move the custom cursor to within software overlay. [AI]
	MxS32 m_cursorX;                      // 0x50c

	/// @brief Y coordinate to move the custom cursor to within software overlay. [AI]
	MxS32 m_cursorY;                      // 0x510

	/// @brief DirectDraw surface used for the cursor overlay. [AI]
	LPDIRECTDRAWSURFACE m_cursorSurface;  // 0x514

	/// @brief Rectangle for cursor overlay on the surface. [AI]
	RECT m_cursorRect;                    // 0x518

	/// @brief Surface for rendering the FPS overlay. [AI]
	LPDIRECTDRAWSURFACE m_unk0x528;       // 0x528

	/// @brief If true, FPS overlay is drawn. [AI]
	MxBool m_drawFPS;                     // 0x52c

	/// @brief Rectangle area of the FPS overlay surface. [AI]
	RECT m_fpsRect;                       // 0x530

	/// @brief Font handle for FPS text drawing. [AI]
	HFONT m_arialFont;                    // 0x540

	/// @brief Text size of FPS overlay (pixel width/height). [AI]
	SIZE m_fpsSize;                       // 0x544

	/// @brief Used in FPS calculation (timestamp for last update). [AI]
	MxFloat m_unk0x54c;                   // 0x54c

	/// @brief Used in FPS calculation (frame count during interval). [AI]
	MxFloat m_unk0x550;                   // 0x550

	/// @brief If true, override main rendering for presenter/PutData only. [AI]
	MxBool m_unk0x554;                    // 0x554

	/// @brief If true, rendering is paused (e.g. movie, loss of device). [AI]
	MxBool m_paused;                      // 0x555

	/// @brief Camera clipping back plane distance. [AI]
	D3DVALUE m_back;                      // 0x558

	/// @brief Camera clipping front plane distance. [AI]
	D3DVALUE m_front;                     // 0x55c

	/// @brief Current camera width. [AI]
	float m_cameraWidth;                  // 0x560

	/// @brief Current camera height. [AI]
	float m_cameraHeight;                 // 0x564

	/// @brief Field of view for the camera. [AI]
	D3DVALUE m_fov;                       // 0x55c

	/// @brief Camera object in D3DRM. [AI]
	IDirect3DRMFrame* m_camera;           // 0x56c

	/// @brief Camera projection type (parallel, perspective, etc.). [AI]
	D3DRMPROJECTIONTYPE m_projection;     // 0x570

	/// @brief Application data for viewport handling (engine-internal). [AI]
	ViewportAppData* m_appdata;           // 0x574

	/// @brief D3DRM rendering quality selected for this manager. [AI]
	D3DRMRENDERQUALITY m_quality;         // 0x578

	/// @brief Number of shades for rendering (D3DRM). [AI]
	DWORD m_shades;                       // 0x57c

	/// @brief Texture mapping quality for D3DRM. [AI]
	D3DRMTEXTUREQUALITY m_textureQuality; // 0x580

	/// @brief D3DRM render mode for device. [AI]
	DWORD m_rendermode;                   // 0x584

	/// @brief If true, dithering is enabled in D3DRM. [AI]
	BOOL m_dither;                        // 0x588

	/// @brief Number of backbuffers for D3DRM rendering. [AI]
	DWORD m_bufferCount;                  // 0x58c
};

// SYNTHETIC: LEGO1 0x1007ab20
// LegoVideoManager::`scalar deleting destructor'

#endif // LEGOVIDEOMANAGER_H
