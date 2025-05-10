#ifndef LEGOCACHESOUNDLIST_H
#define LEGOCACHESOUNDLIST_H

#include "legocachsound.h"
#include "mxlist.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d63b0
// class MxCollection<LegoCacheSound *>

// VTABLE: LEGO1 0x100d63c8
// class MxList<LegoCacheSound *>

// VTABLE: LEGO1 0x100d63e0
// class MxPtrList<LegoCacheSound>

// VTABLE: LEGO1 0x100d63f8
// SIZE 0x18
/**
 * @brief [AI] Specialized pointer list for managing a collection of LegoCacheSound objects, providing comparison and list management.
 * @details [AI] LegoCacheSoundList serves as a strongly typed container for LegoCacheSound pointers, managing ownership and order using MxPtrList as its base. Typical usage is to cache sound assets for reuse within the game, allowing efficient search and lifecycle management. The Compare function provides a way to order or uniquely identify sounds based on pointer value, which is important for pointer-based collections and deduplication of sound entries. Ownership semantics can be controlled on construction.
 */
class LegoCacheSoundList : public MxPtrList<LegoCacheSound> {
public:
	/**
	 * @brief [AI] Construct a LegoCacheSoundList with optional ownership setting.
	 * @param p_ownership Indicates whether the list owns the pointed LegoCacheSound objects and is responsible for deleting them. [AI]
	 * @details [AI] If ownership is true, the list will delete LegoCacheSound objects when removing them from the container or when the list is destroyed. If false, the caller manages the object lifetime.
	 */
	LegoCacheSoundList(MxBool p_ownership = FALSE) : MxPtrList<LegoCacheSound>(p_ownership) {}

	/**
	 * @brief [AI] Compare two LegoCacheSound pointer values for list ordering.
	 * @param p_a First LegoCacheSound pointer to compare. [AI]
	 * @param p_b Second LegoCacheSound pointer to compare. [AI]
	 * @return 0 if the pointers are equal, -1 if p_a is less than p_b, 1 otherwise. [AI]
	 * @details [AI] Used by the list to sort or identify uniqueness. This comparison is strictly on pointer value, not underlying sound data content; useful for managing objects within pointer-based collections. Implements and overrides the virtual method from the parent MxPtrList. [AI]
	 */
	MxS8 Compare(LegoCacheSound* p_a, LegoCacheSound* p_b) override
	{
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14
};

// VTABLE: LEGO1 0x100d64a0
// class MxListCursor<LegoCacheSound *>

// VTABLE: LEGO1 0x100d6500
// class MxPtrListCursor<LegoCacheSound>

// VTABLE: LEGO1 0x100d6518
// SIZE 0x10
/**
 * @brief [AI] Cursor/iterator class for traversing a LegoCacheSoundList.
 * @details [AI] A strongly-typed cursor for efficient and type-safe iteration across a LegoCacheSoundList. Inherits from generic MxPtrListCursor but ensures that only LegoCacheSoundList can be used, preventing mistakes in usage.
 */
class LegoCacheSoundListCursor : public MxPtrListCursor<LegoCacheSound> {
public:
	/**
	 * @brief [AI] Construct a cursor for a given LegoCacheSoundList.
	 * @param p_list The target LegoCacheSoundList to iterate over. [AI]
	 * @details [AI] After construction, the cursor can be used for advancing, inspecting, or modifying elements within the list in a controlled manner. [AI]
	 */
	LegoCacheSoundListCursor(LegoCacheSoundList* p_list) : MxPtrListCursor<LegoCacheSound>(p_list) {}
};

// TEMPLATE: LEGO1 0x1001e670
// MxCollection<LegoCacheSound *>::Compare

// TEMPLATE: LEGO1 0x1001e680
// MxCollection<LegoCacheSound *>::~MxCollection<LegoCacheSound *>

// TEMPLATE: LEGO1 0x1001e6d0
// MxCollection<LegoCacheSound *>::Destroy

// TEMPLATE: LEGO1 0x1001e6e0
// MxList<LegoCacheSound *>::~MxList<LegoCacheSound *>

// TEMPLATE: LEGO1 0x1001e770
// MxPtrList<LegoCacheSound>::Destroy

// SYNTHETIC: LEGO1 0x1001e780
// LegoCacheSoundList::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001e7f0
// MxPtrList<LegoCacheSound>::~MxPtrList<LegoCacheSound>

// SYNTHETIC: LEGO1 0x1001e840
// MxCollection<LegoCacheSound *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001e8b0
// MxList<LegoCacheSound *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001e960
// MxPtrList<LegoCacheSound>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f350
// LegoCacheSoundListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f3c0
// MxPtrListCursor<LegoCacheSound>::~MxPtrListCursor<LegoCacheSound>

// SYNTHETIC: LEGO1 0x1001f410
// MxListCursor<LegoCacheSound *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f480
// MxPtrListCursor<LegoCacheSound>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f4f0
// MxListCursor<LegoCacheSound *>::~MxListCursor<LegoCacheSound *>

// FUNCTION: LEGO1 0x1001f540
// LegoCacheSoundListCursor::~LegoCacheSoundListCursor

// TEMPLATE: LEGO1 0x10020840
// MxListCursor<LegoCacheSound *>::MxListCursor<LegoCacheSound *>

// TEMPLATE: LEGO1 0x100224e0
// MxList<LegoCacheSound *>::InsertEntry

// TEMPLATE: LEGO1 0x10022590
// MxListCursor<LegoCacheSound *>::Find

// TEMPLATE: LEGO1 0x10022680
// MxList<LegoCacheSound *>::DeleteEntry

#endif // LEGOCACHESOUNDLIST_H
