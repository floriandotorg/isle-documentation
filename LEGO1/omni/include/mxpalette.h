#ifndef MXPALETTE_H
#define MXPALETTE_H

#include "mxcore.h"
#include "mxtypes.h"

#include <ddraw.h>

// VTABLE: LEGO1 0x100dc848
// VTABLE: BETA10 0x101c2300
// SIZE 0x414
/**
 * @brief [AI] Encapsulates a DirectDraw 8-bit (256 color) palette for use with DirectX rendering. Handles palette entry management, overrides for special colors (e.g., sky), cloning, and platform/system palette integration. [AI]
 *
 * The palette provides facilities to set, retrieve, and modify palette entries, set the palette for rendering, and override specific entries for custom rendering effects such as sky gradients. Internal members allow for efficient updates and synchronization with DirectDraw API objects. [AI]
 */
class MxPalette : public MxCore {
public:
	/**
	 * @brief [AI] Compares two palettes for equality by checking all 256 color entries (RGB only, not flags). [AI]
	 * @param p_other The palette to compare with. [AI]
	 * @return TRUE if all RGB entries are equal; otherwise FALSE. [AI]
	 */
	MxBool operator==(MxPalette& p_other); // [AI]

	/**
	 * @brief [AI] Detaches the internal DirectDraw palette object, releasing ownership. Does not release the underlying DirectDraw resource. [AI]
	 */
	void Detach(); // [AI]

	/**
	 * @brief [AI] Constructs a new palette, initializing to the system or default palette entries. [AI]
	 */
	MxPalette(); // [AI]

	/**
	 * @brief [AI] Constructs a palette using an array of RGBQUADs for indices 10..245, with system entries at borders. [AI]
	 * @param p_colors Pointer to RGBQUAD array (minimum 256 entries recommended). [AI]
	 */
	MxPalette(const RGBQUAD*); // [AI]

	/**
	 * @brief [AI] Destructor. Releases any allocated DirectDraw palette. [AI]
	 */
	~MxPalette() override; // [AI]

	/**
	 * @brief [AI] Copies system palette entries (first and last 10) to the specified buffer. [AI]
	 * @param p_entries Pointer to a PALETTEENTRY array to receive system entries. [AI]
	 * @details Used to synchronize palette with system colors for correct display. [AI]
	 */
	void ApplySystemEntriesToPalette(LPPALETTEENTRY p_entries); // [AI]

	/**
	 * @brief [AI] Creates a duplicate of this palette object with the same palette data and override flag. [AI]
	 * @return A new MxPalette instance with copied entries and state. [AI]
	 */
	MxPalette* Clone(); // [AI]

	/**
	 * @brief [AI] Retrieves the default palette for the current system/graphics environment. [AI]
	 * @param p_entries Pointer to a PALETTEENTRY array to receive all default entries. [AI]
	 * @details Uses system palette if supported, otherwise uses static default. [AI]
	 */
	void GetDefaultPalette(LPPALETTEENTRY p_entries); // [AI]

	/**
	 * @brief [AI] Copies all palette entries to external buffer. [AI]
	 * @param p_entries Output buffer for 256 palette entries. [AI]
	 * @return SUCCESS always. [AI]
	 */
	MxResult GetEntries(LPPALETTEENTRY p_entries); // [AI]

	/**
	 * @brief [AI] Sets the palette's RGB entries from an external array and updates the DirectDraw palette if attached. [AI]
	 * @param p_palette Input buffer of 256 palette entries. [AI]
	 * @return SUCCESS if successful; FAILURE on DirectDraw error. [AI]
	 */
	MxResult SetEntries(LPPALETTEENTRY p_palette); // [AI]

	/**
	 * @brief [AI] Sets the "sky color" palette entry (typically index 141, reserved for sky background), and updates attached DirectDraw palette. [AI]
	 * @param p_skyColor Pointer to sky color entry (only one entry used). [AI]
	 * @return SUCCESS or FAILURE depending on update result. [AI]
	 * @details If override for sky color is enabled, this call has no effect. [AI]
	 */
	MxResult SetSkyColor(LPPALETTEENTRY p_skyColor); // [AI]

	/**
	 * @brief [AI] Resets palette entries to default system values, optionally preserving the current sky color, then uploads to DirectDraw. [AI]
	 * @param p_ignoreSkyColor If FALSE, the sky color entry will be forcibly set. [AI]
	 */
	void Reset(MxBool p_ignoreSkyColor); // [AI]

	/**
	 * @brief [AI] Creates the internal DirectDraw palette object and populates it with the current palette entries. [AI]
	 * @return LPDIRECTDRAWPALETTE to the created native palette object (can be NULL on failure). [AI]
	 * @details On first call, creates palette. No-op on subsequent calls. [AI]
	 */
	LPDIRECTDRAWPALETTE CreateNativePalette(); // [AI]

	/**
	 * @brief [AI] Sets the internal DirectDraw palette pointer, releasing any previously held instance. No copy is made. [AI]
	 * @param p_palette Pointer to DirectDraw palette instance. [AI]
	 */
	void SetPalette(LPDIRECTDRAWPALETTE p_palette); // [AI]

	/**
	 * @brief [AI] Sets whether the sky color is overridden, preventing calls to SetSkyColor from effecting palette entries. [AI]
	 * @param p_value TRUE to override, FALSE to use palette. [AI]
	 */
	void SetOverrideSkyColor(MxBool p_value) { m_overrideSkyColor = p_value; } // [AI]

	// SYNTHETIC: LEGO1 0x100beeb0
	// SYNTHETIC: BETA10 0x10144640
	// MxPalette::`scalar deleting destructor'

private:
	LPDIRECTDRAWPALETTE m_palette;    ///< [AI] DirectDraw palette interface pointer for this palette. [AI]
	PALETTEENTRY m_entries[256];      ///< [AI] Local copy of palette entries for manipulation and comparison. [AI]
	MxBool m_overrideSkyColor;        ///< [AI] If TRUE, disables modification of palette sky color entries for special rendering effects. [AI]
	PALETTEENTRY m_skyColor;          ///< [AI] Backup for sky color entry, used to restore or temporarily swap sky background. [AI]
};

#endif // MXPALETTE_H
