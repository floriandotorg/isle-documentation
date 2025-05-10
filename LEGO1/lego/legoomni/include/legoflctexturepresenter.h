#ifndef LEGOFLCTEXTUREPRESENTER_H
#define LEGOFLCTEXTUREPRESENTER_H

#include "decomp.h"
#include "mxflcpresenter.h"

class LegoTextureInfo;

/// @brief [AI]
/// Presenter for rendering FLC animation frames as textures in the LEGO engine. This class is
/// responsible for handling the process of decoding FLC video frames and updating corresponding
/// textures used by the 3D rendering system. Acts as a bridge between the FLC (Autodesk Animator) 
/// bitmap sequence and the LEGO engine's texture system, enabling animated textures in the world.
/// [AI]
///
/// @details [AI]
/// This presenter decodes frames from FLC animation and uploads them to textures using `LegoTextureInfo`.
/// On each StartTickle sequence it loads (if required) a LEGO texture based on extra data from the action (usually a filename).
/// As frames are loaded via `LoadFrame`, the decoded frame data is stored in the presenter's bitmap.
/// When the next frame is ready for drawing, the texture is updated using that bitmap via `PutFrame`.
///
/// The rect count is parsed from the incoming stream chunk, indicating potentially updated dirty rectangles for optimization. [AI]
/// [AI]
///
/// @see MxFlcPresenter, LegoTextureInfo [AI]
class LegoFlcTexturePresenter : public MxFlcPresenter {
public:
	/// @brief [AI] Constructs a LegoFlcTexturePresenter and resets state for first run. [AI]
	LegoFlcTexturePresenter();

	/// @brief [AI] Returns the static handler class name for this presenter type ("LegoFlcTexturePresenter"). [AI]
	/// @return Pointer to static class name string. [AI]
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f0634
		return "LegoFlcTexturePresenter";
	}

	/// @brief [AI] Returns the class name of this instance. Used for runtime type information and serialization. [AI]
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/// @brief [AI] Called on transition to 'Starting' tickle state. Loads target LegoTextureInfo from action extra data if specified. [AI]
	///
	/// @details [AI]
	/// If the .SI action's extra data specifies a filename, appends ".gif" and queries the global TextureContainer for the associated texture.
	/// After setting up, calls the base implementation.
	/// [AI]
	void StartingTickle() override;

	/// @brief [AI] Decodes an FLC animation frame from a chunk, extracting both dirty rects and animation data. [AI]
	///
	/// @param p_chunk Stream chunk containing the FLC frame data. [AI]
	/// @details [AI]
	/// Reads the updated rectangle count, advances the data pointer past the rectangle headers,
	/// then decodes the FLC image into the internal bitmap using the base presenter's logic.
	/// [AI]
	void LoadFrame(MxStreamChunk* p_chunk) override;

	/// @brief [AI] Uploads the newly decoded FLC frame to the associated LegoTextureInfo, updating the active texture. [AI]
	/// @details [AI]
	/// If a target texture is loaded and there are dirty rectangles (rectCount != 0), uploads the new frame region(s) to the texture and resets state.
	/// [AI]
	void PutFrame() override;

	// SYNTHETIC: LEGO1 0x1005df00
	// LegoFlcTexturePresenter::`scalar deleting destructor'

private:
	/// @brief [AI] Internal helper to reset fields to initial state; called by constructor. [AI]
	void Init();

	MxS32 m_rectCount;          ///< @brief [AI] Number of FLC update rectangles in the current frame. Used to track dirty regions for texture updates. [AI]
	LegoTextureInfo* m_texture; ///< @brief [AI] Pointer to the LEGO texture object this FLC animation is driving. [AI]
};

#endif // LEGOFLCTEXTUREPRESENTER_H