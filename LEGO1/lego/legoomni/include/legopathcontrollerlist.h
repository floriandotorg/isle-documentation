#ifndef LEGOPATHCONTROLLERLIST_H
#define LEGOPATHCONTROLLERLIST_H

#include "legopathcontroller.h"
#include "mxlist.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d6380
// VTABLE: BETA10 0x101bf130
// class MxCollection<LegoPathController *>

// VTABLE: LEGO1 0x100d6398
// VTABLE: BETA10 0x101bf110
// class MxList<LegoPathController *>

// VTABLE: LEGO1 0x100d6320
// VTABLE: BETA10 0x101bf0f0
// class MxPtrList<LegoPathController>

// VTABLE: LEGO1 0x100d6338
// VTABLE: BETA10 0x101bf0d0
// SIZE 0x18
/**
 * @brief Class representing a list of pointers to LegoPathController objects, with optional ownership semantics. [AI]
 * @details [AI] Inherits from MxPtrList<LegoPathController>. This class is used to manage a collection of LegoPathController pointers, optionally owning (deleting) the objects when the list is destroyed, depending on the ownership flag. Provides pointer comparison to support sorting or unique enforcement. Used to track all active LegoPathControllers, which are responsible for moving actors along paths. [AI]
 */
class LegoPathControllerList : public MxPtrList<LegoPathController> {
public:
	/**
	 * @brief Constructor for LegoPathControllerList. [AI]
	 * @param p_ownership If TRUE, the list will delete objects when destroyed or removed; otherwise, objects are not deleted. Defaults to FALSE. [AI]
	 * @details [AI] Passes ownership parameter to the base MxPtrList constructor. [AI]
	 */
	LegoPathControllerList(MxBool p_ownership = FALSE) : MxPtrList<LegoPathController>(p_ownership) {}

	/**
	 * @brief Compares two LegoPathController pointers for equality or ordering. [AI]
	 * @param p_a Pointer to first LegoPathController. [AI]
	 * @param p_b Pointer to second LegoPathController. [AI]
	 * @return 0 if equal, -1 if p_a < p_b, 1 if p_a > p_b (using pointer value comparison). [AI]
	 * @details [AI] Used by list implementation for ordering or duplicate checks. Comparisons are based on pointer address, not on object content. [AI]
	 */
	MxS8 Compare(LegoPathController* p_a, LegoPathController* p_b) override
	{
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14
};

// VTABLE: LEGO1 0x100d6578
// VTABLE: BETA10 0x101bf200
// class MxListCursor<LegoPathController *>

// VTABLE: LEGO1 0x100d6548
// VTABLE: BETA10 0x101bf1e8
// class MxPtrListCursor<LegoPathController>

// VTABLE: LEGO1 0x100d6560
// VTABLE: BETA10 0x101bf1d0
// SIZE 0x10
/**
 * @brief Cursor/iterator for traversing a LegoPathControllerList. [AI]
 * @details [AI] Inherits from MxPtrListCursor<LegoPathController> and provides cursor semantics for iterating over the list of LegoPathController pointers. Useful for safe traversal and manipulation of the active controller list. [AI]
 */
class LegoPathControllerListCursor : public MxPtrListCursor<LegoPathController> {
public:
	/**
	 * @brief Constructs a cursor for the given LegoPathControllerList. [AI]
	 * @param p_list Pointer to a LegoPathControllerList to iterate. [AI]
	 * @details [AI] Creates a cursor associated with the given list for sequential access. [AI]
	 */
	LegoPathControllerListCursor(LegoPathControllerList* p_list) : MxPtrListCursor<LegoPathController>(p_list) {}
};

// TEMPLATE: LEGO1 0x1001d230
// TEMPLATE: BETA10 0x100dd1f0
// MxCollection<LegoPathController *>::Compare

// TEMPLATE: LEGO1 0x1001d240
// TEMPLATE: BETA10 0x100dd210
// MxList<LegoPathController *>::MxList<LegoPathController *>

// TEMPLATE: LEGO1 0x1001d2d0
// TEMPLATE: BETA10 0x100dd370
// MxCollection<LegoPathController *>::~MxCollection<LegoPathController *>

// TEMPLATE: LEGO1 0x1001d320
// TEMPLATE: BETA10 0x100dd430
// MxCollection<LegoPathController *>::Destroy

// TEMPLATE: LEGO1 0x1001d330
// TEMPLATE: BETA10 0x100dd450
// MxList<LegoPathController *>::~MxList<LegoPathController *>

// TEMPLATE: LEGO1 0x1001d3c0
// TEMPLATE: BETA10 0x100dd530
// MxPtrList<LegoPathController>::Destroy

// SYNTHETIC: LEGO1 0x1001d3d0
// SYNTHETIC: BETA10 0x100dd580
// LegoPathControllerList::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001d440
// TEMPLATE: BETA10 0x100dd5d0
// MxPtrList<LegoPathController>::~MxPtrList<LegoPathController>

// SYNTHETIC: LEGO1 0x1001d490
// SYNTHETIC: BETA10 0x100dd650
// MxCollection<LegoPathController *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001d500
// SYNTHETIC: BETA10 0x100dd6a0
// MxList<LegoPathController *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001d5b0
// SYNTHETIC: BETA10 0x100dd6f0
// MxPtrList<LegoPathController>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001d620
// SYNTHETIC: BETA10 0x100dd740
// LegoPathControllerList::~LegoPathControllerList

// SYNTHETIC: LEGO1 0x1001f830
// SYNTHETIC: BETA10 0x100dfef0
// LegoPathControllerListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f8a0
// TEMPLATE: BETA10 0x100dff40
// MxPtrListCursor<LegoPathController>::~MxPtrListCursor<LegoPathController>

// SYNTHETIC: LEGO1 0x1001f8f0
// SYNTHETIC: BETA10 0x100dffc0
// MxListCursor<LegoPathController *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f960
// SYNTHETIC: BETA10 0x100e0010
// MxPtrListCursor<LegoPathController>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f9d0
// TEMPLATE: BETA10 0x100e0060
// MxListCursor<LegoPathController *>::~MxListCursor<LegoPathController *>

// FUNCTION: LEGO1 0x1001fa20
// FUNCTION: BETA10 0x100e00e0
// LegoPathControllerListCursor::~LegoPathControllerListCursor

// TEMPLATE: BETA10 0x100dd150
// MxPtrList<LegoPathController>::MxPtrList<LegoPathController>

// TEMPLATE: BETA10 0x100dd2c0
// MxCollection<LegoPathController *>::MxCollection<LegoPathController *>

// TEMPLATE: BETA10 0x100dd400
// MxCollection<LegoPathController *>::SetDestroy

// TEMPLATE: BETA10 0x100dd4e0
// MxPtrList<LegoPathController>::SetOwnership

// TEMPLATE: BETA10 0x100dfda0
// MxPtrListCursor<LegoPathController>::MxPtrListCursor<LegoPathController>

// TEMPLATE: BETA10 0x100dfe40
// MxListCursor<LegoPathController *>::MxListCursor<LegoPathController *>

// TEMPLATE: BETA10 0x100e1cb0
// MxList<LegoPathController *>::DeleteAll

// TEMPLATE: BETA10 0x100e1d70
// MxListCursor<LegoPathController *>::Next

// TEMPLATE: BETA10 0x100e1ff0
// MxListEntry<LegoPathController *>::GetNext

// TEMPLATE: BETA10 0x100e2050
// MxListEntry<LegoPathController *>::GetValue

#endif // LEGOPATHCONTROLLERLIST_H
