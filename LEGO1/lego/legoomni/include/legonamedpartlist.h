#ifndef LEGONAMEDPARTLIST_H
#define LEGONAMEDPARTLIST_H

#include "legonamedpart.h"
#include "mxlist.h"

// VTABLE: LEGO1 0x100d9d90
// class MxCollection<LegoNamedPart *>

// VTABLE: LEGO1 0x100d9da8
// class MxList<LegoNamedPart *>

// VTABLE: LEGO1 0x100d9dc0
// class MxPtrList<LegoNamedPart>

// VTABLE: LEGO1 0x100d9dd8
// SIZE 0x18
/**
 * @brief [AI] A list container for storing pointers to LegoNamedPart objects. 
 *        Inherits from MxPtrList<LegoNamedPart>, providing management of ownership and list operations.
 * @details [AI] The list owns its contents (i.e., TRUE passed to base), so deleting the list will delete the contained LegoNamedPart objects.
 */
class LegoNamedPartList : public MxPtrList<LegoNamedPart> {
public:
	/**
	 * @brief [AI] Constructor. Initializes the list as an owning list of LegoNamedPart pointers.
	 * @details [AI] Passing TRUE to the base MxPtrList constructor ensures automatic deletion of contained elements.
	 */
	LegoNamedPartList() : MxPtrList<LegoNamedPart>(TRUE) {}

	// SYNTHETIC: LEGO1 0x1007dbf0
	// LegoNamedPartList::`scalar deleting destructor'
	/**
	 * @brief [AI] Destructor. Cleans up contents if owned.
	 */
};

// VTABLE: LEGO1 0x100d9e68
// class MxListCursor<LegoNamedPart *>

// VTABLE: LEGO1 0x100d9e38
// class MxPtrListCursor<LegoNamedPart>

// VTABLE: LEGO1 0x100d9e50
// SIZE 0x10
/**
 * @brief [AI] Cursor/iterator for traversing a LegoNamedPartList.
 * @details [AI] Provides navigation capabilities over LegoNamedPartList objects using the MxPtrListCursor base class.
 */
class LegoNamedPartListCursor : public MxPtrListCursor<LegoNamedPart> {
public:
	/**
	 * @brief [AI] Constructor. Creates a cursor for the supplied LegoNamedPartList.
	 * @param p_list [AI] Pointer to the LegoNamedPartList to iterate over.
	 */
	LegoNamedPartListCursor(LegoNamedPartList* p_list) : MxPtrListCursor<LegoNamedPart>(p_list) {}
};

// SYNTHETIC: LEGO1 0x1007e170
// LegoNamedPartListCursor::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1007e1e0
// MxPtrListCursor<LegoNamedPart>::~MxPtrListCursor<LegoNamedPart>

// SYNTHETIC: LEGO1 0x1007e230
// MxListCursor<LegoNamedPart *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1007e2a0
// MxPtrListCursor<LegoNamedPart>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1007e310
// MxListCursor<LegoNamedPart *>::~MxListCursor<LegoNamedPart *>

// FUNCTION: LEGO1 0x1007e360
// LegoNamedPartListCursor::~LegoNamedPartListCursor

// TEMPLATE: LEGO1 0x1007d760
// MxCollection<LegoNamedPart *>::Compare

// TEMPLATE: LEGO1 0x1007d770
// MxCollection<LegoNamedPart *>::~MxCollection<LegoNamedPart *>

// TEMPLATE: LEGO1 0x1007d7c0
// MxCollection<LegoNamedPart *>::Destroy

// TEMPLATE: LEGO1 0x1007d7d0
// MxList<LegoNamedPart *>::~MxList<LegoNamedPart *>

// TEMPLATE: LEGO1 0x1007d860
// MxPtrList<LegoNamedPart>::Destroy

// TEMPLATE: LEGO1 0x1007dc60
// MxPtrList<LegoNamedPart>::~MxPtrList<LegoNamedPart>

// SYNTHETIC: LEGO1 0x1007dcb0
// MxCollection<LegoNamedPart *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1007dd20
// MxList<LegoNamedPart *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1007ddd0
// MxPtrList<LegoNamedPart>::`scalar deleting destructor'

#endif // LEGONAMEDPARTLIST_H
