#ifndef LEGOTRANINFOLIST_H
#define LEGOTRANINFOLIST_H

#include "legotraninfo.h"
#include "mxlist.h"
#include "mxtypes.h"

// VTABLE: LEGO1 0x100d8ca8
// class MxCollection<LegoTranInfo *>

// VTABLE: LEGO1 0x100d8cc0
// class MxList<LegoTranInfo *>

// VTABLE: LEGO1 0x100d8cd8
// class MxPtrList<LegoTranInfo>

// VTABLE: LEGO1 0x100d8c90
// SIZE 0x18
/**
 * @brief [AI] List container holding pointers to LegoTranInfo objects for use in transfer/pathfinding/ROIs. Inherits from MxPtrList for pointer list management.
 * @details [AI] LegoTranInfoList manages an ordered collection of LegoTranInfo pointers. It is used wherever lists of LegoTranInfo (which often represent transfer points, animation states, or transform infos in the 3D world) are needed in the game engine, such as navigation and path management systems. Inherits pointer-list semantics, automatic ownership/cleanup, and iteration functionality from the base class.
 */
class LegoTranInfoList : public MxPtrList<LegoTranInfo> {
public:
	/**
	 * @brief [AI] Constructs an empty list of LegoTranInfo pointers; disables ownership deletion semantics in the base class by passing FALSE.
	 */
	LegoTranInfoList() : MxPtrList<LegoTranInfo>(FALSE) {}
};

// VTABLE: LEGO1 0x100d8cf0
// class MxListCursor<LegoTranInfo *>

// VTABLE: LEGO1 0x100d8d08
// class MxPtrListCursor<LegoTranInfo>

// VTABLE: LEGO1 0x100d8d20
// SIZE 0x10
/**
 * @brief [AI] Cursor/iterator for traversing a LegoTranInfoList.
 * @details [AI] LegoTranInfoListCursor allows controlled sequential traversal of a LegoTranInfoList, supporting navigation and access to each element in the list without exposing internal structures. Specialized for LegoTranInfo pointers and retains all pointer safety semantics of MxPtrListCursor/LegoTranInfo.
 */
class LegoTranInfoListCursor : public MxPtrListCursor<LegoTranInfo> {
public:
	/**
	 * @brief [AI] Construct a cursor targeting the given LegoTranInfoList.
	 * @param p_list The LegoTranInfoList to be iterated by this cursor. [AI]
	 */
	LegoTranInfoListCursor(LegoTranInfoList* p_list) : MxPtrListCursor<LegoTranInfo>(p_list) {}
};

// TEMPLATE: LEGO1 0x1005fdf0
// MxCollection<LegoTranInfo *>::Compare

// TEMPLATE: LEGO1 0x1005fe00
// MxCollection<LegoTranInfo *>::~MxCollection<LegoTranInfo *>

// TEMPLATE: LEGO1 0x1005fe50
// MxCollection<LegoTranInfo *>::Destroy

// TEMPLATE: LEGO1 0x1005fe60
// MxList<LegoTranInfo *>::~MxList<LegoTranInfo *>

// SYNTHETIC: LEGO1 0x1005fef0
// LegoTranInfoList::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1005ff60
// MxPtrList<LegoTranInfo>::~MxPtrList<LegoTranInfo>

// SYNTHETIC: LEGO1 0x1005ffb0
// MxCollection<LegoTranInfo *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10060020
// MxList<LegoTranInfo *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100600d0
// MxPtrList<LegoTranInfo>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100612f0
// LegoTranInfoListCursor::`scalar deleting destructor'

// FUNCTION: LEGO1 0x10061360
// MxPtrListCursor<LegoTranInfo>::~MxPtrListCursor<LegoTranInfo>

// SYNTHETIC: LEGO1 0x100613b0
// MxListCursor<LegoTranInfo *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10061420
// MxPtrListCursor<LegoTranInfo>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x10061490
// MxListCursor<LegoTranInfo *>::~MxListCursor<LegoTranInfo *>

// FUNCTION: LEGO1 0x100614e0
// LegoTranInfoListCursor::~LegoTranInfoListCursor

#endif // LEGOTRANINFOLIST_H
