#ifndef LEGOCACHESOUNDMANAGER_H
#define LEGOCACHESOUNDMANAGER_H

#include "decomp.h"
#include "legocachsound.h"
#include "mxstl/stlcompat.h"
#include "mxtypes.h"

#pragma warning(disable : 4237)

//! @brief [AI] Represents a single entry in the cached sound system, linking a sound pointer with its identifying name.
//! 
//! Contains non-owning pointer to a LegoCacheSound and a string name. The destructor deletes the name string only if
//! the sound pointer is NULL and the name is not NULL (prevents accidental deletion when sound owns its name).
//! [AI] Size: 0x08 bytes.
struct LegoCacheSoundEntry {
	//! @brief [AI] Constructs an empty sound entry with null pointers. [AI]
	LegoCacheSoundEntry() : m_sound(NULL), m_name(NULL) {}

	//! @brief [AI] Constructs a sound entry with a given sound and name string pointer. [AI]
	//! @param p_sound Pointer to the LegoCacheSound instance. [AI]
	//! @param p_name Pointer to the name string (not copied, non-owning, unless m_sound is NULL). [AI]
	LegoCacheSoundEntry(LegoCacheSound* p_sound, const char* p_name) : m_sound(p_sound), m_name(p_name) {}

	//! @brief [AI] Constructs a sound entry referencing a given sound, using its internal name data. [AI]
	//! @details [AI] The entry copies the pointer to the name from p_sound->GetUnknown0x48().GetData(). [AI]
	//! @param p_sound Pointer to the LegoCacheSound. [AI]
	LegoCacheSoundEntry(LegoCacheSound* p_sound) : m_sound(p_sound), m_name(p_sound->GetUnknown0x48().GetData()) {}

	//! @brief [AI] Destructor for LegoCacheSoundEntry. Deletes the name only if entry does NOT own a sound (m_sound == NULL). [AI]
	~LegoCacheSoundEntry()
	{
		if (m_sound == NULL && m_name != NULL) {
			delete[] const_cast<char*>(m_name);
		}
	}

	//! @brief [AI] Dummy equality operator (always returns false). [AI]
	//! @param [unused] [AI]
	bool operator==(LegoCacheSoundEntry) const { return 0; }
	//! @brief [AI] Dummy less-than operator (always returns false). [AI]
	//! @param [unused] [AI]
	bool operator<(LegoCacheSoundEntry) const { return 0; }

	//! @brief [AI] Returns the pointer to the cached LegoCacheSound. [AI]
	LegoCacheSound* GetSound() const { return m_sound; }
	//! @brief [AI] Returns the name (string key) of this sound entry. [AI]
	const char* GetName() const { return m_name; }

	//! @brief [AI] Allows Set100d6b4cComparator access to private fields. [AI]
	friend struct Set100d6b4cComparator;

private:
	LegoCacheSound* m_sound; //!< @brief [AI] Pointer to the cached sound object. Ownership, if any, is managed outside. [AI]
	const char* m_name;      //!< @brief [AI] Name or key associated with the sound. If m_sound is NULL, this must be deleted by the destructor. [AI]
};

//! @brief [AI] Comparator used in the sound cache sound entry set (Set100d6b4c).
struct Set100d6b4cComparator {
	//! @brief [AI] Performs case-insensitive reverse-lexical comparison between sound names (for set order). [AI]
	//! @param p_a Left hand LegoCacheSoundEntry. [AI]
	//! @param p_b Right hand LegoCacheSoundEntry. [AI]
	//! @return True if p_a's name is greater than p_b's name (case-insensitive). [AI]
	bool operator()(const LegoCacheSoundEntry& p_a, const LegoCacheSoundEntry& p_b) const
	{
		return strcmpi(p_a.m_name, p_b.m_name) > 0;
	}
};

//! @brief [AI] Set of LegoCacheSoundEntry, sorted by case-insensitive name for fast lookup. [AI]
typedef set<LegoCacheSoundEntry, Set100d6b4cComparator> Set100d6b4c;

//! @brief [AI] List of LegoCacheSoundEntry, used for maintaining order of managed/playing sounds. [AI]
typedef list<LegoCacheSoundEntry> List100d6b4c;

//! @brief [AI] Manages caching, reuse, and playback of LegoCacheSound objects. Provides fast sound lookup by name/key,
//!            supports object reuse, sound playback, and sound destruction. [AI]
//! @details [AI] Holds two containers: a set for quick lookup (by name) and a list for managing sounds in use,
//! properly cleaning up both on destruction. [AI]
//! Size: 0x20 bytes.
class LegoCacheSoundManager {
public:
	//! @brief [AI] Default constructor. [AI]
	LegoCacheSoundManager() {}
	//! @brief [AI] Destructor. Cleans up all cached sound entries in set and list, stops sounds and deletes sound objects. [AI]
	~LegoCacheSoundManager();

	//! @brief [AI] Advances or cleans up all managed sounds. Invokes internal logic for cleanup and update of cached sounds. [AI]
	//! @return SUCCESS after tickle. [AI]
	virtual MxResult Tickle(); // vtable+0x00

	//! @brief [AI] Attempts to find and return a cached sound by its key (case-insensitive). If not present, returns NULL. [AI]
	//! @param p_key Name/key for the sound. [AI]
	//! @return Pointer to the matching LegoCacheSound or NULL. [AI]
	LegoCacheSound* FindSoundByKey(const char* p_key);

	//! @brief [AI] Manages a sound entry. Adds new one or returns existing one (by internal cache). [AI]
	//! @details [AI] If a sound with the same data already exists, the new one may be destroyed. [AI]
	//! @param p_sound The sound object to manage. [AI]
	//! @return A pointer to the managed sound (possibly input, possibly merged). [AI]
	LegoCacheSound* ManageSoundEntry(LegoCacheSound* p_sound);

	//! @brief [AI] Plays a sound identified by key, with the given playback name and looping flag.
	//! Will play a managed or cloned version. [AI]
	//! @param p_key Key identifying the sound to play. [AI]
	//! @param p_name Name to use for playback. [AI]
	//! @param p_looping Should the sound play looped. [AI]
	//! @return A pointer to the playing LegoCacheSound, or NULL if failed. [AI]
	LegoCacheSound* Play(const char* p_key, const char* p_name, MxBool p_looping);

	//! @brief [AI] Plays a given sound object, with named playback and looping option. Handles cloning if required. [AI]
	//! @param p_sound Sound object to play. [AI]
	//! @param p_name Playback label/name used in the sound engine. [AI]
	//! @param p_looping Should the sound play looped. [AI]
	//! @return Pointer to the sound object that plays, or NULL if failed. [AI]
	LegoCacheSound* Play(LegoCacheSound* p_sound, const char* p_name, MxBool p_looping);

	//! @brief [AI] Stops playback of the specified sound object. [AI]
	//! @param p_sound Reference to pointer of sound; only matches by pointer. [AI]
	void Stop(LegoCacheSound*& p_sound);

	//! @brief [AI] Destroys (deletes and removes) the specified sound object from all tracking. [AI]
	//! @param p_sound Reference to sound pointer to destroy. Removes, stops and deletes its memory. [AI]
	void Destroy(LegoCacheSound*& p_sound);

private:
	Set100d6b4c m_set;   //!< @brief [AI] Set of cached sound entries for fast key lookup by sound name. [AI]
	List100d6b4c m_list; //!< @brief [AI] List of additional managed sound entries in use or pending cleanup. [AI]
};

// clang-format off
// TEMPLATE: see source for template usages and STL-style implementation notes [AI]

// clang-format on

#endif // LEGOCACHESOUNDMANAGER_H
