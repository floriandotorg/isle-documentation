#ifndef MXPRESENTERLIST_H
#define MXPRESENTERLIST_H

#include "mxlist.h"
#include "mxpresenter.h"

// VTABLE: LEGO1 0x100d62f0
// class MxPtrList<MxPresenter>

// VTABLE: LEGO1 0x100d6308
// SIZE 0x18
/**
 * @brief [AI] List to hold pointers to MxPresenter objects with optional ownership semantics.
 * @details [AI] MxPresenterList extends MxPtrList<MxPresenter> to provide a specialized container for handling a list of pointers to MxPresenter instances.
 * It supports basic list operations, pointer comparison, and optional memory management based on ownership.
 * Typically used to manage presentational state/progression, sequencing multiple presenters in the LEGO Island engine.
 */
class MxPresenterList : public MxPtrList<MxPresenter> {
public:
	/**
	 * @brief [AI] Constructs an MxPresenterList with optional pointer ownership flag.
	 * @param p_ownership If TRUE, the list assumes ownership and will delete MxPresenter objects upon destruction or removal. [AI]
	 */
	MxPresenterList(MxBool p_ownership = FALSE) : MxPtrList<MxPresenter>(p_ownership) {}

	/**
	 * @brief [AI] Compares two MxPresenter pointers for equality and ordering.
	 * @details [AI] Returns 0 if the pointers are equal, -1 if the first is less than the second, and 1 otherwise.
	 * Used internally to support ordered list operations or uniqueness checks.
	 * @param p_a The first MxPresenter pointer to compare. [AI]
	 * @param p_b The second MxPresenter pointer to compare. [AI]
	 * @return 0 if equal, -1 if p_a < p_b, 1 if p_a > p_b. [AI]
	 */
	MxS8 Compare(MxPresenter* p_a, MxPresenter* p_b) override
	{
		return p_a == p_b ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14

	// SYNTHETIC: LEGO1 0x1001ceb0
	// MxPresenterList::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100d6488
// class MxListCursor<MxPresenter *>

// VTABLE: LEGO1 0x100d6530
// class MxPtrListCursor<MxPresenter>

// VTABLE: LEGO1 0x100d6470
// SIZE 0x10
/**
 * @brief [AI] Cursor/iterator for traversing an MxPresenterList.
 * @details [AI] Provides facilities to iterate through the list of presenters efficiently and safely.
 * Inherits from MxPtrListCursor<MxPresenter> which allows access and navigation over the list data structure.
 */
class MxPresenterListCursor : public MxPtrListCursor<MxPresenter> {
public:
	/**
	 * @brief [AI] Constructs a cursor for an MxPresenterList.
	 * @param p_list The MxPresenterList to iterate over. [AI]
	 */
	MxPresenterListCursor(MxPresenterList* p_list) : MxPtrListCursor<MxPresenter>(p_list) {}
};

// VTABLE: LEGO1 0x100d6350
// class MxCollection<MxPresenter *>

// VTABLE: LEGO1 0x100d6368
// class MxList<MxPresenter *>

// TEMPLATE: LEGO1 0x1001cd20
// MxCollection<MxPresenter *>::Compare

// TEMPLATE: LEGO1 0x1001cd30
// MxCollection<MxPresenter *>::Destroy

// TEMPLATE: LEGO1 0x1001cd40
// MxList<MxPresenter *>::MxList<MxPresenter *>

// TEMPLATE: LEGO1 0x1001cdd0
// MxCollection<MxPresenter *>::~MxCollection<MxPresenter *>

// TEMPLATE: LEGO1 0x1001ce20
// MxList<MxPresenter *>::~MxList<MxPresenter *>

// TEMPLATE: LEGO1 0x1001cf20
// MxPtrList<MxPresenter>::~MxPtrList<MxPresenter>

// SYNTHETIC: LEGO1 0x1001cf70
// MxCollection<MxPresenter *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001cfe0
// MxList<MxPresenter *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001d090
// MxPtrList<MxPresenter>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001d100
// MxPresenterList::~MxPresenterList

// SYNTHETIC: LEGO1 0x1001eed0
// MxPresenterListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001ef40
// MxPtrListCursor<MxPresenter>::~MxPtrListCursor<MxPresenter>

// SYNTHETIC: LEGO1 0x1001ef90
// MxListCursor<MxPresenter *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001f000
// MxPtrListCursor<MxPresenter>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1001f070
// MxListCursor<MxPresenter *>::~MxListCursor<MxPresenter *>

// FUNCTION: LEGO1 0x1001f0c0
// MxPresenterListCursor::~MxPresenterListCursor

// TEMPLATE: LEGO1 0x10020760
// MxListCursor<MxPresenter *>::MxListCursor<MxPresenter *>

// TEMPLATE: LEGO1 0x10022380
// MxList<MxPresenter *>::InsertEntry

// TEMPLATE: LEGO1 0x100225e0
// MxList<MxPresenter *>::DeleteEntry

// TEMPLATE: BETA10 0x1007d1d0
// MxPtrListCursor<MxPresenter>::MxPtrListCursor<MxPresenter>

// TEMPLATE: BETA10 0x1007d270
// MxListCursor<MxPresenter *>::MxListCursor<MxPresenter *>

// TEMPLATE: BETA10 0x100d9420
// MxListCursor<MxPresenter *>::Prev

#endif // MXPRESENTERLIST_H
