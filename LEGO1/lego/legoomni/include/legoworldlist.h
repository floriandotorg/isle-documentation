#ifndef LEGOWORLDLIST_H
#define LEGOWORLDLIST_H

#include "mxlist.h"
#include "mxtypes.h"

class LegoWorld;

/// \class LegoWorldList
/// \brief A specialized list for managing pointers to LegoWorld instances. [AI]
/// \details [AI] Inherits from MxPtrList<LegoWorld>, providing ordering, iteration, ownership control, and pointer management for LegoWorld objects in the engine. [AI]
/// @note [AI] Implements custom comparison logic for LegoWorld pointers. [AI]
class LegoWorldList : public MxPtrList<LegoWorld> {
public:
	/// \brief Constructor which may optionally enable ownership of the LegoWorld pointers. [AI]
	/// \param p_ownership If TRUE, the list will own (and delete) the objects it contains. [AI]
	LegoWorldList(MxBool p_ownership = FALSE) : MxPtrList<LegoWorld>(p_ownership) {}

	/// \brief Compares two LegoWorld pointers for ordering. [AI]
	/// \details [AI] Returns 0 if the pointers are equal, -1 if p_a < p_b, and 1 if p_a > p_b. Used for ordered list operations. [AI]
	/// \param p_a First LegoWorld pointer to compare. [AI]
	/// \param p_b Second LegoWorld pointer to compare. [AI]
	/// \return 0 if equal, -1 if p_a < p_b, 1 otherwise. [AI]
	MxS8 Compare(LegoWorld* p_a, LegoWorld* p_b) override { return p_a == p_b ? 0 : p_a < p_b ? -1 : 1; } // vtable+0x14

	// SYNTHETIC: LEGO1 0x10059a00
	// LegoWorldList::`scalar deleting destructor'
};

/// \class LegoWorldListCursor
/// \brief Provides iteration access to a LegoWorldList. [AI]
/// \details [AI] Inherits from MxPtrListCursor<LegoWorld>. Used to traverse the elements of a LegoWorldList safely, supporting robust iteration patterns over the contained LegoWorld pointers. [AI]
class LegoWorldListCursor : public MxPtrListCursor<LegoWorld> {
public:
	/// \brief Construct a cursor for a given LegoWorldList. [AI]
	/// \param p_list Pointer to the LegoWorldList to iterate over. [AI]
	LegoWorldListCursor(LegoWorldList* p_list) : MxPtrListCursor<LegoWorld>(p_list) {}
};

// SYNTHETIC: LEGO1 0x1003e870
// LegoWorldListCursor::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1003e8e0
// MxPtrListCursor<LegoWorld>::~MxPtrListCursor<LegoWorld>

// SYNTHETIC: LEGO1 0x1003e930
// MxListCursor<LegoWorld *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1003e9a0
// MxPtrListCursor<LegoWorld>::`scalar deleting destructor'

// FUNCTION: LEGO1 0x1003ea10
// MxListCursor<LegoWorld *>::~MxListCursor<LegoWorld *>

// FUNCTION: LEGO1 0x1003ea60
// LegoWorldListCursor::~LegoWorldListCursor

// TEMPLATE: LEGO1 0x100598f0
// MxCollection<LegoWorld *>::Compare

// TEMPLATE: LEGO1 0x10059900
// MxCollection<LegoWorld *>::~MxCollection<LegoWorld *>

// TEMPLATE: LEGO1 0x10059950
// MxCollection<LegoWorld *>::Destroy

// TEMPLATE: LEGO1 0x10059960
// MxList<LegoWorld *>::~MxList<LegoWorld *>

// TEMPLATE: LEGO1 0x100599f0
// MxPtrList<LegoWorld>::Destroy

// TEMPLATE: LEGO1 0x10059a70
// MxPtrList<LegoWorld>::~MxPtrList<LegoWorld>

// SYNTHETIC: LEGO1 0x10059ac0
// MxCollection<LegoWorld *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10059b30
// MxList<LegoWorld *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10059be0
// MxPtrList<LegoWorld>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1005b740
// MxList<LegoWorld *>::DeleteEntry

#endif // LEGOWORLDLIST_H
