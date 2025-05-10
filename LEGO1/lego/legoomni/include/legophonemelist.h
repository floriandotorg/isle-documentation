#ifndef LEGOPHONEMELIST_H
#define LEGOPHONEMELIST_H

#include "decomp.h"
#include "legophoneme.h"
#include "mxlist.h"

// VTABLE: LEGO1 0x100d9cd0
// class MxCollection<LegoPhoneme *>

// VTABLE: LEGO1 0x100d9ce8
// class MxList<LegoPhoneme *>

// VTABLE: LEGO1 0x100d9d00
// VTABLE: BETA10 0x101bef58
// SIZE 0x18
/**
 * @brief Specialized list class for managing LegoPhoneme objects. [AI]
 * 
 * @details Inherits from MxList<LegoPhoneme*> and provides functionality for comparison
 *          and destruction tailored to LegoPhoneme objects. Used to maintain the ordered
 *          set of phoneme definitions used in speech or lip-sync features. [AI] 
 */
class LegoPhonemeList : public MxList<LegoPhoneme*> {
public:
	/**
	 * @brief Constructor - sets custom destroy function for phoneme objects. [AI]
	 * @details Installs LegoPhonemeList::Destroy so the list is responsible for deleting
	 *          its LegoPhoneme objects when clearing or being destructed. [AI]
	 */
	LegoPhonemeList() { SetDestroy(Destroy); }

	/**
	 * @brief Compares two LegoPhoneme objects for equality, or orders them by address. [AI]
	 * @param p_a First LegoPhoneme pointer [AI]
	 * @param p_b Second LegoPhoneme pointer [AI]
	 * @details Performs the following logic:
	 *           - Compares the phoneme names using MxString::Equal().
	 *           - Returns 0 if their names are equal.
	 *           - Otherwise, orders pointers by their address: returns -1 if p_a < p_b, else 1.
	 *          This function is used to maintain internal ordering and avoid duplicates. [AI]
	 */
	MxS8 Compare(LegoPhoneme* p_a, LegoPhoneme* p_b) override
	{
		MxString a(p_a->GetName());
		MxString b(p_b->GetName());
		return a.Equal(b) ? 0 : p_a < p_b ? -1 : 1;
	} // vtable+0x14

	/**
	 * @brief Static destruction helper for MxList. [AI]
	 * @param p_element Pointer to the LegoPhoneme to delete [AI]
	 * @details Called by MxList when removing elements or clearing the list, ensuring
	 *          heap-allocated LegoPhoneme objects are properly freed. [AI]
	 */
	static void Destroy(LegoPhoneme* p_element) { delete p_element; }
};

// VTABLE: LEGO1 0x100d80c8
// class MxListCursor<LegoPhoneme *>

// VTABLE: LEGO1 0x100d80e0
// SIZE 0x10
/**
 * @brief Cursor class for iterating over LegoPhonemeList. [AI]
 * 
 * @details Provides sequential access to the elements of a LegoPhonemeList, using the
 *          generic cursor pattern from MxListCursor, but specialized for LegoPhoneme pointers.
 *          Intended for usage in lip sync parsing, animation, or scripting subsystems.
 *          Construction attaches it to a specific LegoPhonemeList instance. [AI]
 */
class LegoPhonemeListCursor : public MxListCursor<LegoPhoneme*> {
public:
	/**
	 * @brief Creates a cursor for a given LegoPhonemeList. [AI]
	 * @param p_list The LegoPhonemeList to iterate over [AI]
	 * @details Delegates construction to the base MxListCursor. [AI]
	 */
	LegoPhonemeListCursor(LegoPhonemeList* p_list) : MxListCursor<LegoPhoneme*>(p_list) {}
};

// TEMPLATE: LEGO1 0x1004e680
// LegoPhonemeListCursor::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1004e6f0
// MxListCursor<LegoPhoneme *>::~MxListCursor<LegoPhoneme *>

// TEMPLATE: LEGO1 0x1004e740
// MxListCursor<LegoPhoneme *>::`scalar deleting destructor'

// TEMPLATE: LEGO1 0x1004e7b0
// LegoPhonemeListCursor::~LegoPhonemeListCursor

// TEMPLATE: LEGO1 0x1007b300
// MxCollection<LegoPhoneme *>::Compare

// TEMPLATE: LEGO1 0x1007b310
// MxCollection<LegoPhoneme *>::~MxCollection<LegoPhoneme *>

// TEMPLATE: LEGO1 0x1007b360
// MxCollection<LegoPhoneme *>::Destroy

// TEMPLATE: LEGO1 0x1007b370
// MxList<LegoPhoneme *>::~MxList<LegoPhoneme *>

// SYNTHETIC: LEGO1 0x1007b400
// LegoPhonemeList::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1007b470
// MxCollection<LegoPhoneme *>::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1007b4e0
// MxList<LegoPhoneme *>::`scalar deleting destructor'

#endif // LEGOPHONEMELIST_H
