#ifndef LEGOSTATE_H
#define LEGOSTATE_H

#include "decomp.h"
#include "misc/legostorage.h"
#include "mxcore.h"

// VTABLE: LEGO1 0x100d46c0
// VTABLE: BETA10 0x101b89d8
// SIZE 0x08
/**
 * @brief [AI] Base class for game state blocks which encapsulate serializable and/or resettable aspects of the game's state. [AI]
 *
 * LegoState is a polymorphic base for objects representing state relevant to LEGO Island's scripting/game logic.
 * It allows derived states to be serialized, reset, and identifies themselves via RTTI-style interface. [AI]
 */
class LegoState : public MxCore {
public:
	/**
	 * @brief [AI] Score coloring values for in-game display feedback or logic. [AI]
	 */
	enum ScoreColor {
		e_grey = 0,      ///< [AI] Default/neutral color (0) [AI]
		e_yellow,        ///< [AI] First colored highlight (1) [AI]
		e_blue,          ///< [AI] Second color, e.g. better score (2) [AI]
		e_red            ///< [AI] Warning/critical color (3) [AI]
	};

	/**
	 * @brief [AI] Playlist structure representing an indexed list of object IDs
	 * with next-item selection strategies (loop, once, random etc). [AI]
	 *
	 * This is used for e.g. playing sounds, animations or other events in sequence or randomly. [AI]
	 */
	// SIZE 0x0c
	struct Playlist {
		/**
		 * @brief [AI] Playback/select mode for playlist sequencing [AI]
		 */
		enum Mode {
			e_loop,           ///< [AI] Continue repeating all items in sequence [AI]
			e_once,           ///< [AI] Play all items just one time [AI]
			e_random,         ///< [AI] Pick a random item each time [AI]
			e_loopSkipFirst   ///< [AI] Repeats items in sequence, but skips first entry after the initial loop [AI]
		};

		/**
		 * @brief [AI] Initializes playlist with no object IDs and default mode (loop). [AI]
		 */
		// FUNCTION: LEGO1 0x10017c00
		// FUNCTION: BETA10 0x10031dc0
		Playlist()
		{
			m_objectIds = NULL;
			m_length = 0;
			m_mode = e_loop;
			m_nextIndex = 0;
		}

		/**
		 * @brief [AI] Initialize a Playlist using specific object IDs, length, and mode.
		 * @param p_objectIds Pointer to array of object IDs for playlist [AI]
		 * @param p_length Total number of object IDs [AI]
		 * @param p_mode Playlist's sequencing mode, as per Mode enum [AI]
		 */
		// FUNCTION: BETA10 0x10031e10
		Playlist(MxU32* p_objectIds, MxS16 p_length, MxS16 p_mode)
		{
			m_objectIds = p_objectIds;
			m_length = p_length;
			m_mode = p_mode;
			m_nextIndex = 0;
		}

		/**
		 * @brief [AI] Assignment operator to copy playlist state (pointers and counters only; does not deep-copy IDs array). [AI]
		 * @param p_playlist Source playlist to copy from [AI]
		 * @return Reference to this Playlist [AI]
		 * @details [AI] Copies the pointer to object ID array, length, next index, and mode. [AI]
		 */
		// FUNCTION: LEGO1 0x10071800
		// FUNCTION: BETA10 0x10031e70
		Playlist& operator=(const Playlist& p_playlist)
		{
			m_objectIds = p_playlist.m_objectIds;
			m_length = p_playlist.m_length;
			m_nextIndex = p_playlist.m_nextIndex;
			m_mode = p_playlist.m_mode;
			return *this;
		}

		/**
		 * @brief [AI] Retrieves the object ID at the current position, advances next index according to playlist mode. [AI]
		 * @return Next object ID selected by the playlist strategy [AI]
		 * @details [AI] e_loop: cycles round, e_once: stops incrementing, e_random: picks randomly, e_loopSkipFirst: starts from 1 after first loop. [AI]
		 */
		MxU32 Next();

		/**
		 * @brief [AI] Checks if playlist contains an object ID. [AI]
		 * @param p_objectId The object ID to look for [AI]
		 * @return TRUE if found, FALSE otherwise [AI]
		 * @details [AI] Linear search through current range. [AI]
		 */
		MxBool Contains(MxU32 p_objectId);

		MxU32* m_objectIds; ///< [AI] Pointer to array of object IDs. Not owned; just used for lookup. [AI]
		MxS16 m_length;     ///< [AI] Number of IDs in the playlist. [AI]
		MxS16 m_mode;       ///< [AI] Selection/iteration mode (as in Mode). [AI]
		MxS16 m_nextIndex;  ///< [AI] Current index for next selection (suitable for sequential/random access). [AI]
	};

	/**
	 * @brief [AI] Virtual destructor to allow subclass cleanup. [AI]
	 */
	// FUNCTION: LEGO1 0x10005f40
	~LegoState() override {}

	/**
	 * @brief [AI] Returns if this state can be serialized (for game saving/loading support). [AI]
	 * @return TRUE if serializable, overrides can return FALSE [AI]
	 */
	// FUNCTION: LEGO1 0x10005f90
	virtual MxBool IsSerializable() { return TRUE; } // vtable+0x14

	/**
	 * @brief [AI] Hook for returning object to default (empty) state; not implemented in this base. [AI]
	 * @return TRUE if state was reset, FALSE otherwise [AI]
	 */
	// FUNCTION: LEGO1 0x10005fa0
	virtual MxBool Reset() { return FALSE; } // vtable+0x18

	/**
	 * @brief [AI] Serialize state to a storage (for save/load). [AI]
	 * @param p_storage Stream/abstraction for state IO (see LegoStorage) [AI]
	 * @return Serialization result (SUCCESS or error code) [AI]
	 * @details [AI] In write mode, stores class name; designed for override in derived classes. [AI]
	 */
	// FUNCTION: LEGO1 0x10005fb0
	// FUNCTION: BETA10 0x10017af0
	virtual MxResult Serialize(LegoStorage* p_storage)
	{
		if (p_storage->IsWriteMode()) {
			p_storage->WriteMxString(ClassName());
		}
		return SUCCESS;
	} // vtable+0x1c

	/**
	 * @brief [AI] Gets this class's name for RTTI/IsA functionality. [AI]
	 * @return Always returns "LegoState" string [AI]
	 */
	// FUNCTION: LEGO1 0x100060d0
	// FUNCTION: BETA10 0x10017d20
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f01b8
		// STRING: BETA10 0x101dcdac
		return "LegoState";
	}

	/**
	 * @brief [AI] Tests if this object is of a given class name, directly or through inheritance. [AI]
	 * @param p_name Class name string to compare [AI]
	 * @return TRUE if matches this class or any ancestor [AI]
	 */
	// FUNCTION: LEGO1 0x100060e0
	// FUNCTION: BETA10 0x100a9000
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoState::ClassName()) || MxCore::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x10006160
	// LegoState::`scalar deleting destructor'
};

#endif // LEGOSTATE_H
