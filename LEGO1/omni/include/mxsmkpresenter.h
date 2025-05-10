#ifndef MXSMKPRESENTER_H
#define MXSMKPRESENTER_H

#include "decomp.h"
#include "mxsmk.h"
#include "mxvideopresenter.h"

// VTABLE: LEGO1 0x100dc348
// SIZE 0x720
/**
 * @brief [AI] Presenter for rendering .SMK (Smacker) video media within the game engine.
 * 
 * MxSmkPresenter handles decoding, frame management, palette realization, and invalidation of display regions for Smacker video streams.
 * It inherits from MxVideoPresenter and implements the specific details of Smacker video playback and update integration.
 * 
 * The class manages the current frame, manages the Smacker data structures, and maintains the bitmap for rendered video frames.
 * [AI]
 */
class MxSmkPresenter : public MxVideoPresenter {
public:
	/**
	 * @brief [AI] Constructs an MxSmkPresenter and initializes member variables.
	 * [AI]
	 */
	MxSmkPresenter();

	/**
	 * @brief [AI] Destructor. Cleans up allocated Smacker video resources and resets state.
	 * [AI]
	 */
	~MxSmkPresenter() override;

	/**
	 * @brief [AI] Returns the human-readable handler class name for this presenter type.
	 * @details [AI] Used for presenter name dispatching in the media system.
	 * @return "MxSmkPresenter" as the name of this class. [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x10101e38
		return "MxSmkPresenter";
	}

	/**
	 * @brief [AI] Returns the class name for this object.
	 * @details [AI] Used for RTTI and IsA() checks.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Run-time type check.
	 * @details [AI] Checks if the given class name matches this or any parent class.
	 * @param p_name Name to check for. [AI]
	 * @return TRUE if the class matches, otherwise calls inherited method. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxSmkPresenter::ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Registers this presenter instance with the video presentation manager.
	 * @details [AI] This handles adding the video presenter into the system for playback control and resource management.
	 */
	MxResult AddToManager() override;

	/**
	 * @brief [AI] Cleans up and destroys the resources used by this presenter.
	 * @details [AI] Calls internal destructor variant for proper cleanup sequencing depending on context.
	 */
	void Destroy() override;

	/**
	 * @brief [AI] Loads the Smacker header information from a stream chunk.
	 * @details [AI] Decodes video size, frame count, frame types, and prepares internal state for frame decoding.
	 * @param p_chunk MxStreamChunk containing header data. [AI]
	 */
	void LoadHeader(MxStreamChunk* p_chunk) override;

	/**
	 * @brief [AI] Allocates and prepares the bitmap for a Smacker video frame.
	 * @details [AI] Adjusts size to match the decoded Smacker dimensions.
	 */
	void CreateBitmap() override;

	/**
	 * @brief [AI] Loads and renders a Smacker video frame from a stream chunk.
	 * @details [AI] Handles palette changes, decompresses video data, calculates changed rect regions, and invalidates display as needed.
	 * @param p_chunk MxStreamChunk containing frame data. [AI]
	 */
	void LoadFrame(MxStreamChunk* p_chunk) override;

	/**
	 * @brief [AI] Realizes (uploads) the color palette for the current frame bitmap.
	 * @details [AI] Integrates with the global palette and video management system.
	 */
	void RealizePalette() override;

	/**
	 * @brief [AI] Virtual function for custom frame or looping logic for Smacker video playback.
	 * @details [AI] Handles internal looping or reset logic according to Smacker type and frame count. May be used for frame wrap-around, cycle, or loop support.
	 */
	virtual void VTable0x88();                        // vtable+0x88

	// SYNTHETIC: LEGO1 0x100b3850
	// MxSmkPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Initialization of member variables and Smacker-specific state.
	 * [AI]
	 */
	void Init();

	/**
	 * @brief [AI] Internal destroy method, allowing control whether it's called from destructor or externally.
	 * @details [AI] Resets and frees Smacker data, resets state, and optionally calls base class destroy.
	 * @param p_fromDestructor Indicates context: TRUE if from dtor, FALSE if external call. [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

protected:
	/// @brief [AI] Smacker file decoding context holding header, palette, frame types, and decode buffers.
	MxSmk m_mxSmk;        // 0x64

	/// @brief [AI] Current frame index within the Smacker stream.
	MxU32 m_currentFrame; // 0x71c
};

#endif // MXSMKPRESENTER_H
