#ifndef LEGOPALETTEPRESENTER_H
#define LEGOPALETTEPRESENTER_H

#include "decomp.h"
#include "mxvideopresenter.h"

class MxPalette;

/**
 * @brief Class responsible for presenting and handling palettes for video sequences that require palette management [AI]
 * @details [AI] LegoPalettePresenter manages MxPalette resources, parses palette data from incoming MxStreamChunk objects (as found in SI file resources), and coordinates with the video subsystem to realize/activate the palette when necessary. It is triggered during "Ready" tickle state of a presentation, and is used for video or animation formats that require explicit palette updates (such as FLC or certain indexed video). [AI]
 * @see MxVideoPresenter, MxPalette, MxStreamChunk [AI] 
 */
class LegoPalettePresenter : public MxVideoPresenter {
public:
	/**
	 * @brief Constructs the LegoPalettePresenter and initializes its internal state. [AI]
	 */
	LegoPalettePresenter();

	/**
	 * @brief Cleans up and releases owned resources, including any loaded palette. [AI]
	 */
	~LegoPalettePresenter() override; // vtable+0x00

	/**
	 * @brief Provides the unique class handler name required for presenter dispatching. [AI]
	 * @return The string literal "LegoPalettePresenter". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f061c
		return "LegoPalettePresenter";
	}

	/**
	 * @brief Gets the presenter class name as used for RTTI (run-time type identification) and class dispatch. [AI]
	 * @return Class handler name string ("LegoPalettePresenter") [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief Implements run-time type identification matching for this presenter. [AI]
	 * @param p_name Name to check for class match, compared case-sensitively. [AI]
	 * @return True if p_name matches this class or any parent class; otherwise false. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	/**
	 * @brief Called by the tickle manager when presenter is in Ready state; handles next palette chunk if available. [AI]
	 * @details [AI] This method checks if there is palette data available from the associated subscriber, parses the palette, and if successful, sends it to the VideoManager to be realized (applied for rendering). [AI]
	 */
	void ReadyTickle() override; // vtable+0x18

	/**
	 * @brief Handles destruction and cleanup of palette presenter resources (public destroy invocation). [AI]
	 */
	void Destroy() override;     // vtable+0x38

	/**
	 * @brief Parses a palette from a chunk in the streaming media resource. [AI]
	 * @details [AI] Expects the chunk data to match the LEGO Island .SI palette chunk format: leading 40 bytes (usually image/palette header) followed by 256 RGBQUAD entries; creates an MxPalette from the color table. [AI]
	 * @param p_chunk Pointer to the streaming data chunk containing palette resource. [AI]
	 * @return SUCCESS if palette was parsed and created, FAILURE otherwise. [AI]
	 */
	MxResult ParsePalette(MxStreamChunk* p_chunk);

	// SYNTHETIC: LEGO1 0x1007a050
	// LegoPalettePresenter::`scalar deleting destructor'

private:
	/**
	 * @brief Initializes internal state; sets palette pointer to null and base class initialization as needed. [AI]
	 */
	void Init();

	/**
	 * @brief Called internally to release palette and optionally delegate up the hierarchy. [AI]
	 * @param p_fromDestructor Whether called from destructor or as part of manual cleanup. [AI]
	 * @details [AI] Frees MxPalette if present, resets internal state, then optionally calls parent Destroy() depending on p_fromDestructor. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	MxPalette* m_palette; ///< Currently loaded palette to be realized by the video manager, or nullptr if none loaded. [AI]
};

#endif // LEGOPALETTEPRESENTER_H
