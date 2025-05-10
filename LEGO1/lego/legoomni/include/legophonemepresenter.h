#ifndef LEGOPHONEMEPRESENTER_H
#define LEGOPHONEMEPRESENTER_H

#include "decomp.h"
#include "mxflcpresenter.h"
#include "mxstring.h"
#include "mxtypes.h"

class LegoTextureInfo;

// VTABLE: LEGO1 0x100d8040
// SIZE 0x88
/**
 * @brief Class responsible for presenting lip-synced ("phoneme") mouth animations on LEGO character head textures using FLC animations. [AI]
 *
 * @details Inherits from MxFlcPresenter and is specialized to update the mouth portion of a LEGO ROI by updating regions of a head texture in real-time using frame data,
 *          based on phoneme frames streamed from video/audio data. Handles creation and tracking of texture cache entries, maintains the proper texture state, and cleans up when the action is over. [AI]
 *          Phoneme entries and their associated textures are managed by LegoPhonemeList and cached via a global TextureContainer. [AI]
 */
class LegoPhonemePresenter : public MxFlcPresenter {
public:
	/**
	 * @brief Constructor. Initializes internal state for the phoneme presenter. [AI]
	 */
	LegoPhonemePresenter();

	/**
	 * @brief Destructor. Cleans up resources associated with the presenter. [AI]
	 */
	~LegoPhonemePresenter() override; // vtable+0x00

	/**
	 * @brief Returns the static handler class name string for presenter dispatch. Used for run-time type identification and factory construction. [AI]
	 *
	 * @return Pointer to static string literal "LegoPhonemePresenter". [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief Returns the class name string for this presenter instance. Used for run-time type identification. [AI]
	 *
	 * @return HandlerClassName() result. [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief Called on media/actor action start. Responsible for extracting relevant ROI and phoneme resource information, and preparing texture caching and ROI references for phoneme display. [AI]
	 *
	 * @details Extracts the ROI name from the attached action's extra data, locates the head ROI and prepares texture info and phoneme cache entries. Associates the ROI texture for later frame updates. [AI]
	 */
	void StartingTickle() override;                  // vtable+0x1c

	/**
	 * @brief Called when the associated action concludes. Cleans up cached phoneme entries and releases or resets associated textures and actors as appropriate. [AI]
	 *
	 * @details Ensures the reference count for phoneme textures/entries is properly decremented, detaches textures from the ROI, handles actor release and phoneme cache destruction. [AI]
	 */
	void EndAction() override;                       // vtable+0x40

	/**
	 * @brief Loads FLC frame data describing mouth region updates and decodes frame information for use in texture updates. [AI]
	 *
	 * @details Decodes rectangle count and FLIC pixel data into internal frame buffer(s), to later update the corresponding ROI head texture. [AI]
	 *
	 * @param p_chunk A chunk containing the next frame of FLIC animation/phoneme data. [AI]
	 */
	void LoadFrame(MxStreamChunk* p_chunk) override; // vtable+0x68

	/**
	 * @brief Applies the loaded frame data to the cached texture, updating the target ROI's mouth/phoneme region. [AI]
	 *
	 * @details If a texture is available and there are updated mouth regions, calls the texture update method and resets the rect count for the next frame. [AI]
	 */
	void PutFrame() override;                        // vtable+0x6c

	// SYNTHETIC: LEGO1 0x1004e320
	// LegoPhonemePresenter::`scalar deleting destructor'

private:
	/**
	 * @brief Initializes member variables to their default values. Called by the constructor. [AI]
	 */
	void Init();

	MxS32 m_rectCount;              ///< Number of rectangles to update in the mouth region for the current frame. [AI]
	LegoTextureInfo* m_textureInfo; ///< Pointer to the cached head-mouth texture info for the target ROI. [AI]
	MxBool m_unk0x70;               ///< Unknown; used as a flag when updating a cached/duplicate phoneme entry. [AI]
	MxString m_roiName;             ///< Name (string) of the ROI (character/entity) being lip-synced. [AI]
	MxBool m_unk0x84;               ///< Unknown; used as a flag for variant ROI selection (mainly for composite presenters). [AI]
};

// TEMPLATE: LEGO1 0x1004eb20
// MxListEntry<LegoPhoneme *>::MxListEntry<LegoPhoneme *>

#endif // LEGOPHONEMEPRESENTER_H