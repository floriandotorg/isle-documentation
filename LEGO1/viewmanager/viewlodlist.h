#ifndef VIEWLODLIST_H
#define VIEWLODLIST_H

#include "assert.h"
#include "compat.h"
#include "mxstl/stlcompat.h"
#include "realtime/lodlist.h"

#include <string.h>

#pragma warning(disable : 4237)
#pragma warning(disable : 4786)

class ViewLOD;
class ViewLODListManager;

//////////////////////////////////////////////////////////////////////////////
// ViewLODList
//
// An ViewLODList is an LODList that is shared among instances of the "same ROI".
//
// ViewLODLists are managed (created and destroyed) by ViewLODListManager.
//

/**
 * @class ViewLODList
 * @brief [AI] Reference-counted list of Level-of-Detail (LOD) objects associated with a single ROI (Realtime Object Instance), shared by all instances of the same ROI.
 * @details [AI] Inherits from LODList<ViewLOD>. Each ViewLODList is managed exclusively by a ViewLODListManager, and contains the LODs for a particular ROI (object type). Lifetime is tied to reference counting to ensure proper sharing and cleanup between multiple ROI instances sharing geometry. 
 */
class ViewLODList : public LODList<ViewLOD> {
	friend ViewLODListManager;

protected:
	/**
	 * @brief [AI] Constructs a ViewLODList with a given capacity and owner manager.
	 * @param capacity [AI] Initial allocation for the number of LODs to hold.
	 * @param owner [AI] Pointer to the ViewLODListManager responsible for this list.
	 */
	ViewLODList(size_t capacity, ViewLODListManager* owner);

	/**
	 * @brief [AI] Destructor for ViewLODList; asserts that no references remain before destroying.
	 */
	~ViewLODList() override;

public:
	/**
	 * @brief [AI] Increments the reference count. Used to manage shared ownership across different ROI instances.
	 * @return [AI] The incremented reference count value.
	 */
	inline int AddRef();

	/**
	 * @brief [AI] Decrements the reference count. When the reference count reaches zero, deletes this ViewLODList via the owning manager.
	 * @return [AI] The decremented reference count, or 0 if deleted.
	 */
	inline int Release();

#ifdef _DEBUG
	/**
	 * @brief [AI] Outputs diagnostic information about the LOD list, its contents, and reference count using the given tracing function.
	 * @param pTracer [AI] Function pointer to a printf-style tracing routine.
	 */
	void Dump(void (*pTracer)(const char*, ...)) const;
#endif

private:
	int m_refCount;              ///< [AI] Reference count for shared ownership semantics among ROI instances.
	ViewLODListManager* m_owner; ///< [AI] Manager that owns and deletes this ViewLODList when no longer referenced.
};

//////////////////////////////////////////////////////////////////////////////
//

/**
 * @typedef ROIName
 * @brief [AI] String type used as a key to identify uniquely-named ROI (Realtime Object Instance) classes.
 */
typedef const char* ROIName;

/**
 * @struct ROINameComparator
 * @brief [AI] Comparator for ROIName (C-style strings) to be used as keys in maps, using strcmp for sorting.
 */
struct ROINameComparator {
	/**
	 * @brief [AI] Lexicographical comparison of two ROI names for map ordering.
	 * @param rName1 [AI] First ROIName to compare.
	 * @param rName2 [AI] Second ROIName to compare.
	 * @return [AI] TRUE if rName1 > rName2, FALSE otherwise.
	 */
	unsigned char operator()(const ROIName& rName1, const ROIName& rName2) const
	{
		return strcmp((const char*) rName1, (const char*) rName2) > 0;
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODListManager
//
// ViewLODListManager manages creation and sharing of ViewLODLists.
// It stores ViewLODLists under a name, the name of the ROI where
// the ViewLODList belongs.

/**
 * @class ViewLODListManager
 * @brief [AI] Manages the lifecycle, lookup, and sharing of ViewLODList instances for different ROI names.
 * @details [AI] Ensures that ViewLODList objects are created uniquely per ROI name and shared using reference counting. Responsible for deletion and lifetime management of all shared ViewLODLists.
 */
class ViewLODListManager {

	/**
	 * @brief [AI] Typedef for the map associating ROI names (C strings) to ViewLODList pointers, using a custom comparator.
	 */
	typedef map<ROIName, ViewLODList*, ROINameComparator> ViewLODListMap;

public:
	/**
	 * @brief [AI] Constructs a ViewLODListManager; initializes internal structures.
	 */
	ViewLODListManager();

	/**
	 * @brief [AI] Destroys the manager and all ViewLODLists it owns, ensuring proper cleanup of all managed instances.
	 */
	virtual ~ViewLODListManager();

	/**
	 * @brief [AI] Creates and registers a new ViewLODList for a named ROI, with space for the specified number of LODs.
	 * @param rROIName [AI] Name of the ROI to associate with the new LOD list. Must be unique.
	 * @param lodCount [AI] How many LODs to reserve space for.
	 * @return [AI] Pointer to the newly created ViewLODList (with reference count initialized to 1).
	 * @details [AI] Caller must call Release() when done with the returned list; if a list with the same name already exists, a new unique name is generated.
	 */
	ViewLODList* Create(const ROIName& rROIName, int lodCount);

	/**
	 * @brief [AI] Looks up an existing ViewLODList by ROI name, incrementing its reference count.
	 * @param[in] [AI] ROI name key.
	 * @return [AI] The found ViewLODList, or NULL if not found. Reference count is incremented.
	 * @details [AI] Caller is responsible for calling Release() on the returned ViewLODList.
	 */
	ViewLODList* Lookup(const ROIName&) const;

	/**
	 * @brief [AI] Destroys (removes and deletes) the given ViewLODList from the manager. Called automatically via ViewLODList reference counting.
	 * @param lodList [AI] The ViewLODList to remove and deallocate.
	 * @return [AI] TRUE if successfully deleted, FALSE otherwise.
	 */
	unsigned char Destroy(ViewLODList* lodList);

#ifdef _DEBUG
	/**
	 * @brief [AI] Outputs diagnostic information about all managed LOD lists using the provided tracer function.
	 * @param pTracer [AI] Function pointer to a printf-style tracing routine.
	 */
	void Dump(void (*pTracer)(const char*, ...)) const;
#endif

private:
	static int g_ROINameUID;        ///< [AI] Counter for generating unique ROI names if needed for collisions.

	ViewLODListMap m_map;           ///< [AI] Associates ROI names to managed ViewLODList pointers.
};

//////////////////////////////////////////////////////////////////////////////
//
// Implementation notes:
//
// - ViewLODList instances are reference counted and deleted when their count reaches zero.
// - Each list is associated with a string key (the ROI type's name) in ViewLODListManager.
// - New lists are created with unique names in case of collisions, using g_ROINameUID for disambiguation.
//
// [AI] The overall pattern supports resource sharing among many ROI instances of the same type while maintaining
// correct resource lifetime, suitable for geometry sharing in a 3D engine.
//

#endif // VIEWLODLIST_H