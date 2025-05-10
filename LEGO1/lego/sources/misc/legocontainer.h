#ifndef LEGOCONTAINER_H
#define LEGOCONTAINER_H

#include "compat.h"
#include "decomp.h"
#include "legotexture.h"
#include "legotypes.h"
#include "mxstl/stlcompat.h"

// Note: dependency on LegoOmni
#include "lego/legoomni/include/legotextureinfo.h"

#pragma warning(disable : 4237)

/**
 * @brief Comparator used to order keys in LegoContainerInfo maps; compares C-strings lexicographically. [AI]
 * @details [AI] Used as a functor for sorting map keys in a descending string order, making use of std::strcmp. [AI]
 */
struct LegoContainerInfoComparator {
	LegoBool operator()(const char* const& p_key0, const char* const& p_key1) const
	{
		return strcmp(p_key0, p_key1) > 0;
	}
};

/**
 * @brief Template alias for a map from C-string keys to object pointers, using LegoContainerInfoComparator for ordering. [AI]
 * @tparam T Element type, must be pointer. [AI]
 * @details [AI] Used as the internal storage for LegoContainer. Manages pointers and does not own the memory by default. [AI]
 */
template <class T>
class LegoContainerInfo : public map<const char*, T*, LegoContainerInfoComparator> {}; // [AI]

/**
 * @brief Template container associating string names with object pointers, optional lifetime management. [AI]
 * @tparam T Object type, used as pointer. [AI]
 * @details [AI] Manages a mapping from names (C-strings) to pointers to objects of type T. Supports adding, retrieving, and clearing objects, and can optionally manage the deletion of both key strings and mapped objects depending on m_ownership. Used for centrally managing game resources by name. [AI]
 */
template <class T>
class LegoContainer {
public:
	/**
	 * @brief Default constructor, sets this container to own its elements. [AI]
	 * @details [AI] By default, the container will delete objects and name strings when destroyed. [AI]
	 */
	LegoContainer() { m_ownership = TRUE; }

	/**
	 * @brief Destructor. Cleans up all key strings and objects depending on ownership flag. [AI]
	 * @details [AI] Iterates map and deletes both key string and object pointer. [AI]
	 */
	virtual ~LegoContainer()
	{
#ifdef COMPAT_MODE
		typename LegoContainerInfo<T>::iterator it;
#else
		LegoContainerInfo<T>::iterator it;
#endif
		for (it = m_map.begin(); it != m_map.end(); it++) {
			// DECOMP: Use of const_cast here matches ~ViewLODListManager from 96 source.
			const char* const& key = (*it).first;
			delete[] const_cast<char*>(key);

			if (m_ownership) {
				delete (*it).second;
			}
		}
	}

	/**
	 * @brief Remove and delete all mapped objects; preserves key strings. [AI]
	 * @details [AI] Iterates through the map, deleting objects (but not C-string keys) from memory. [AI]
	 */
	void Clear()
	{
#ifdef COMPAT_MODE
		for (typename LegoContainerInfo<T>::iterator it = m_map.begin(); it != m_map.end(); it++)
#else
		for (LegoContainerInfo<T>::iterator it = m_map.begin(); it != m_map.end(); it++)
#endif
		{
			delete (*it).second;
		}
	}

	/**
	 * @brief Retrieve the element mapped to the given name, or nullptr if missing. [AI]
	 * @param p_name Name of the element (C-string). [AI]
	 * @return Pointer to the element if found, otherwise nullptr. [AI]
	 * @details [AI] Looks up the map for the name (using comparator). [AI]
	 */
	T* Get(const char* p_name)
	{
		T* value = NULL;

#ifdef COMPAT_MODE
		typename LegoContainerInfo<T>::iterator it = m_map.find(p_name);
#else
		LegoContainerInfo<T>::iterator it = m_map.find(p_name);
#endif

		if (it != m_map.end()) {
			value = (*it).second;
		}

		return value;
	}

	/**
	 * @brief Add an element mapped to the given name, replacing existing item if present. [AI]
	 * @param p_name Name to map. Will be allocated/copied if new. [AI]
	 * @param p_value Pointer to object to store. [AI]
	 * @details [AI] If the key exists, the old object is deleted (if ownership is set). Key strings are managed by this container and freed in the destructor. [AI]
	 */
	void Add(const char* p_name, T* p_value)
	{
#ifdef COMPAT_MODE
		typename LegoContainerInfo<T>::iterator it = m_map.find(p_name);
#else
		LegoContainerInfo<T>::iterator it = m_map.find(p_name);
#endif

		char* name;
		if (it != m_map.end()) {
			name = const_cast<char*>((*it).first);

			if (m_ownership) {
				delete (*it).second;
			}
		}
		else {
			name = new char[strlen(p_name) + 1];
			strcpy(name, p_name);
		}

		m_map[name] = p_value;
	}

	/**
	 * @brief Set whether this container owns/deletes its objects (and name strings) on removal/destruction. [AI]
	 * @param p_ownership If TRUE, container owns the memory and is responsible for cleanup. [AI]
	 */
	void SetOwnership(LegoBool p_ownership) { m_ownership = p_ownership; }

protected:
	LegoBool m_ownership;       ///< If TRUE, container owns objects and keys; else no cleanup on destruction. [AI]
	LegoContainerInfo<T> m_map; ///< Underlying map from name strings to objects. [AI]
};

/**
 * @typedef LegoCachedTexture [AI]
 * @brief Pair associating a LegoTextureInfo pointer with a cache state (BOOL). [AI]
 * @details [AI] Used for tracking cached DirectDraw/Direct3D texture resources, where the BOOL indicates if the texture is actively in use (=TRUE). [AI]
 */
typedef pair<LegoTextureInfo*, BOOL> LegoCachedTexture;

/**
 * @typedef LegoCachedTextureList [AI]
 * @brief List of cached textures, each with a pointer and a cache state. [AI]
 * @details [AI] Used by the LegoTextureContainer to manage temporary/in-use DirectDraw/Direct3D textures. [AI]
 */
typedef list<LegoCachedTexture> LegoCachedTextureList;

/**
 * @brief Specialized LegoContainer handling LegoTextureInfo objects and their DirectDraw/Direct3D caching. [AI]
 * @details [AI] In addition to basic named texture management, supports tracking and sharing temporary DirectDraw/Direct3D textures, avoiding redundant texture loads and managing texture resources efficiently. [AI]
 * @inherits LegoContainer<LegoTextureInfo> [AI]
 */
class LegoTextureContainer : public LegoContainer<LegoTextureInfo> {
public:
	/**
	 * @brief Destructor. Cleans up all cached textures as well as the standard container cleanup. [AI]
	 * @details [AI] Ensures that texture resources in m_cached are released. [AI]
	 */
	~LegoTextureContainer() override;

	/**
	 * @brief Attempt to find and return a cached LegoTextureInfo with the same properties as p_textureInfo, or create and cache a new one if not found. [AI]
	 * @param p_textureInfo The reference texture to match or duplicate. [AI]
	 * @return Pointer to a cached (shared or newly-created) LegoTextureInfo, or nullptr if creation fails. [AI]
	 * @details [AI] Tries to match any existing cached texture of the same name and size; if none, duplicates the DirectDraw surface and texture for sharing. [AI]
	 */
	LegoTextureInfo* GetCached(LegoTextureInfo* p_textureInfo);

	/**
	 * @brief Mark a cached texture as unused and release its Direct3D/DirectDraw resources if its reference count reaches zero. [AI]
	 * @param p_textureInfo The texture to erase from the cache. [AI]
	 * @details [AI] Sets the cached/freed flag to FALSE and erases the texture from cache if its ref count is now 0, cleaning up its resources. [AI]
	 */
	void EraseCached(LegoTextureInfo* p_textureInfo);

protected:
	LegoCachedTextureList m_cached; ///< List of cached temporary texture objects, pairing texture info with a cache/in-use flag. [AI]
};

#endif // LEGOCONTAINER_H
