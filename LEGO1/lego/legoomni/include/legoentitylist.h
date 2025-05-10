#ifndef LEGOENTITYLIST_H
#define LEGOENTITYLIST_H

#include "legoentity.h"
#include "mxlist.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d6410
// class MxCollection<LegoEntity *>

// VTABLE: LEGO1 0x100d6428
// class MxList<LegoEntity *>

// VTABLE: LEGO1 0x100d6440
// class MxPtrList<LegoEntity>

// VTABLE: LEGO1 0x100d6458
// SIZE 0x18
/**
 * @brief [AI] A strongly typed list for holding LegoEntity pointers. 
 * @details [AI] Inherits from MxPtrList<LegoEntity> and provides ownership semantics and entity-comparison specifically for LegoEntity objects. Used to maintain a collection of world or non-world entities, and provides a custom comparison based on pointer equality.
 */
class LegoEntityList : public MxPtrList<LegoEntity> {
public:
	/**
	 * @brief [AI] Constructs a LegoEntityList.
	 * @details [AI] Calls MxPtrList's constructor, optionally taking ownership of the pointed entities according to p_ownership.
	 * @param p_ownership Whether this list owns the pointers it contains ([AI] if TRUE, destructor deletes objects). Default is FALSE. [AI]
	 */
	LegoEntityList(MxBool p_ownership = FALSE) : MxPtrList<LegoEntity>(p_ownership) {}

	/**
	 * @brief [AI] Compare two LegoEntity pointers.
	 * @details [AI] Returns 0 if pointers are equal, -1 if p_a is less than p_b, 1 otherwise. Used to provide pointer-based ordering for list operations.
	 * @param p_a First LegoEntity pointer. [AI]
	 * @param p_b Second LegoEntity pointer. [AI]
	 * @return 0 if equal, -1 if p_a < p_b, 1 if p_a > p_b [AI]
	 */
	MxS8 Compare(LegoEntity* p_a, LegoEntity* p_b) override
	{
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14 [AI] (Compare pointer values of entities)
};

// VTABLE: LEGO1 0x100d64e8
// class MxListCursor<LegoEntity *>

// VTABLE: LEGO1 0x100d64b8
// class MxPtrListCursor<LegoEntity>

// VTABLE: LEGO1 0x100d64d0
// SIZE 0x10
/**
 * @brief [AI] Cursor class for iterating through a LegoEntityList.
 * @details [AI] Provides an interface for sequential access to LegoEntityList contents (entities), enabling safe, position-based iteration. 
 */
class LegoEntityListCursor : public MxPtrListCursor<LegoEntity> {
public:
	/**
	 * @brief [AI] Constructs a cursor attached to a LegoEntityList.
	 * @param p_list List to iterate over [AI] (must remain valid for lifetime of cursor).
	 */
	LegoEntityListCursor(LegoEntityList* p_list) : MxPtrListCursor<LegoEntity>(p_list) {}
};

// TEMPLATE: LEGO1 0x1001e2f0
// MxCollection<LegoEntity *>::Compare

// TEMPLATE: LEGO1 0x1001e300
// MxCollection<LegoEntity *>::~MxCollection<LegoEntity *>

// TEMPLATE: LEGO1 0x1001e350
// MxCollection<LegoEntity *>::Destroy

// TEMPLATE: LEGO1 0x1001e360
// MxList<LegoEntity *>::~MxList<LegoEntity *>

// TEMPLATE: LEGO1 0x1001e3f0
// MxPtrList<LegoEntity>::Destroy

// SYNTHETIC: LEGO1 0x1001e400
// LegoEntityList::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001e470
// MxPtrList<LegoEntity>::~MxPtrList<LegoEntity>

// SYNTHETIC: LEGO1 0x1001e4c0
// MxCollection<LegoEntity *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001e530
// MxList<LegoEntity *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001e5e0
// MxPtrList<LegoEntity>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f110
// LegoEntityListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f180
// MxPtrListCursor<LegoEntity>::~MxPtrListCursor<LegoEntity>

// SYNTHETIC: LEGO1 0x1001f1d0
// MxListCursor<LegoEntity *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f240
// MxPtrListCursor<LegoEntity>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f2b0
// MxListCursor<LegoEntity *>::~MxListCursor<LegoEntity *>

// FUNCTION: LEGO1 0x1001f300
// LegoEntityListCursor::~LegoEntityListCursor

// TEMPLATE: LEGO1 0x100207d0
// MxListCursor<LegoEntity *>::MxListCursor<LegoEntity *>

// TEMPLATE: LEGO1 0x10022430
// MxList<LegoEntity *>::InsertEntry

// TEMPLATE: LEGO1 0x10022630
// MxList<LegoEntity *>::DeleteEntry

#endif // LEGOENTITYLIST_H
