#ifndef LEGOROILIST_H
#define LEGOROILIST_H

#include "mxlist.h"
#include "mxtypes.h"
#include "roi/legoroi.h"

// VTABLE: LEGO1 0x100d8c30
// class MxCollection<LegoROI *>

// VTABLE: LEGO1 0x100d8c48
// class MxList<LegoROI *>

// VTABLE: LEGO1 0x100d8c60
// class MxPtrList<LegoROI>

// VTABLE: LEGO1 0x100d8c78
// SIZE 0x18

/**
 * @brief [AI] A specialized pointer list for managing LegoROI instances.
 * @details [AI] LegoROIList is a strongly-typed container derived from MxPtrList<LegoROI>, representing a collection
 * of real-time object instances (ROI) as used in the LEGO Island game engine. It provides type safety and specialized comparison logic for LegoROI pointers, typically used to maintain and organize sets of rendered 3D objects or their references within the game engine. Ownership semantics can be toggled via the constructor parameter.
 */
class LegoROIList : public MxPtrList<LegoROI> {
public:
	/**
	 * @brief [AI] Construct a new LegoROIList with optional ownership of contained pointers.
	 * @param p_ownership If TRUE, the list is responsible for deleting its contained LegoROI objects. [AI]
	 * @details [AI] By default, the list does not assume ownership of its elements. Ownership affects clean-up behavior on destruction.
	 */
	LegoROIList(MxBool p_ownership = FALSE) : MxPtrList<LegoROI>(p_ownership) {}

	/**
	 * @brief [AI] Comparison function for LegoROI pointers.
	 * @param p_a First LegoROI pointer. [AI]
	 * @param p_b Second LegoROI pointer. [AI]
	 * @return 0 if pointers are equal, -1 if p_a < p_b, 1 if p_a > p_b (pointer comparison). [AI]
	 * @details [AI] This function performs a direct pointer value comparison between two LegoROI instances, necessary for ordered or uniqueness operations in the underlying list implementation.
	 * @remark [AI] Overrides the virtual comparison required by MxPtrList. [AI]
	 */
	MxS8 Compare(LegoROI* p_a, LegoROI* p_b) override { return p_a == p_b ? 0 : p_a < p_b ? -1 : 1; } // vtable+0x14

	// SYNTHETIC: LEGO1 0x1005f480
	// LegoROIList::`scalar deleting destructor'
};


/**
 * @brief [AI] A typed list cursor for iterating over a LegoROIList.
 * @details [AI] Used to traverse elements within a LegoROIList in a type-safe manner. Inherits iteration mechanics from MxPtrListCursor.
 */
class LegoROIListCursor : public MxPtrListCursor<LegoROI> {
public:
	/**
	 * @brief [AI] Construct a cursor for a given LegoROIList.
	 * @param p_list The LegoROIList to traverse. [AI]
	 * @details [AI] The cursor provides sequential access to the ROIs in the list and maintains the iteration state internally.
	 */
	LegoROIListCursor(LegoROIList* p_list) : MxPtrListCursor<LegoROI>(p_list) {}
};

// TEMPLATE: LEGO1 0x1005f380
// MxCollection<LegoROI *>::Compare

// TEMPLATE: LEGO1 0x1005f390
// MxCollection<LegoROI *>::~MxCollection<LegoROI *>

// TEMPLATE: LEGO1 0x1005f3e0
// MxCollection<LegoROI *>::Destroy

// TEMPLATE: LEGO1 0x1005f3f0
// MxList<LegoROI *>::~MxList<LegoROI *>

// TEMPLATE: LEGO1 0x1005f4f0
// MxPtrList<LegoROI>::~MxPtrList<LegoROI>

// SYNTHETIC: LEGO1 0x1005f540
// MxCollection<LegoROI *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1005f5b0
// MxList<LegoROI *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1005f660
// MxPtrList<LegoROI>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10063540
// LegoROIListCursor::`scalar deleting destructor'

// FUNCTION: LEGO1 0x100635b0
// MxPtrListCursor<LegoROI>::~MxPtrListCursor<LegoROI>

// SYNTHETIC: LEGO1 0x10063600
// MxListCursor<LegoROI *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10063670
// MxPtrListCursor<LegoROI>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x100636e0
// MxListCursor<LegoROI *>::~MxListCursor<LegoROI *>

// FUNCTION: LEGO1 0x10063730
// LegoROIListCursor::~LegoROIListCursor

// TEMPLATE: LEGO1 0x1006ea00
// MxListEntry<LegoROI *>::MxListEntry<LegoROI *>

#endif // LEGOROILIST_H
