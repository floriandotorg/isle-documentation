#ifndef LEGOLOADCACHESOUNDPRESENTER_H
#define LEGOLOADCACHESOUNDPRESENTER_H

#include "decomp.h"
#include "mxwavepresenter.h"

class LegoCacheSound;

// VTABLE: LEGO1 0x100d5fa8
// SIZE 0x90
/**
 * @brief Derived presenter class used for loading and creating cached sound objects from streamed audio data. Handles the management and staging of raw wave data before inserting it into the audio cache for later playback. [AI]
 * 
 * This presenter is utilized for processing streamed sound data into the game's sound cache, suitable for efficient playback without reloading from disk. [AI]
 */
class LegoLoadCacheSoundPresenter : public MxWavePresenter {
public:
	/**
	 * @brief Default constructor. Initializes all internal state and pointers. [AI]
	 */
	LegoLoadCacheSoundPresenter();

	/**
	 * @brief Destructor. Frees dynamically allocated sound data and manages proper destruction sequence. [AI]
	 */
	~LegoLoadCacheSoundPresenter() override;

	/**
	 * @brief Returns the static class handler name used for presenter type dispatching. [AI]
	 * @return Pointer to the static string literal "LegoLoadCacheSoundPresenter". [AI]
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f05a0
		return "LegoLoadCacheSoundPresenter";
	}

	/**
	 * @brief Returns the runtime class name for this presenter. Used for reflection/type identification. [AI]
	 * @return The same string as HandlerClassName(). [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief Called when the presenter enters the ReadyTickle state. Prepares chunked wave data and initializes cache sound object. [AI]
	 * @details Allocates memory for incoming wave data, extracts header information, and prepares the cache sound placeholder. [AI]
	 */
	void ReadyTickle() override;

	/**
	 * @brief Called during the StreamingTickle state. Receives and accumulates streamed wave data into the cache buffer. [AI]
	 * @details Handles copying of streamed chunks into buffer and, on end of stream, finalizes cache sound creation. [AI]
	 */
	void StreamingTickle() override;

	/**
	 * @brief Called when the presenter enters the DoneTickle state. Notifies end of the cache loading operation if needed. [AI]
	 * @details Ends the action if the post-processing flag has been set. [AI]
	 */
	void DoneTickle() override;

	/**
	 * @brief Called to commit prepared data to the cache manager. [AI]
	 * @details Will hand the temporary cache sound object to the sound manager's cache, marking it for subsequent playback. [AI]
	 */
	MxResult PutData() override;

private:
	/**
	 * @brief Initializes member variables to their default state. [AI]
	 */
	void Init();

	/**
	 * @brief Destroys the data buffer and optionally performs full destructor logic. [AI]
	 * @param p_fromDestructor Indicates if the call happens from the destructor (TRUE) or not (FALSE). [AI]
	 */
	void Destroy(MxBool p_fromDestructor);

	LegoCacheSound* m_cacheSound;  ///< Pointer to the managed cache sound object being created from the stream. [AI]
	MxU8* m_data;                  ///< Pointer to the start of the allocated buffer for incoming wave data. [AI]
	MxU8* m_pData;                 ///< Write cursor into the data buffer for streamed chunk accumulation. [AI]
	MxU32 m_dataSize;              ///< Number of bytes currently filled in the data buffer. [AI]
	MxBool m_unk0x7c;              ///< Internal flag used to signal end-of-action processing. [AI]
	PCMWAVEFORMAT m_pcmWaveFormat; ///< Wave format information extracted from the initial chunk header. [AI]
};

// SYNTHETIC: LEGO1 0x10018460
// LegoLoadCacheSoundPresenter::`scalar deleting destructor'

#endif // LEGOLOADCACHESOUNDPRESENTER_H