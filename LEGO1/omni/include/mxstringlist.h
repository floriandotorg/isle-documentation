#ifndef MXSTRINGLIST_H
#define MXSTRINGLIST_H

#include "mxlist.h"
#include "mxstring.h"

// VTABLE: LEGO1 0x100dd040
// VTABLE: BETA10 0x101c2a18
// SIZE 0x18
/**
 * @brief [AI] Specialized list class for storing MxString objects.
 * @details [AI] Inherits from MxList<MxString> and provides a collection of strings.
 *   Often used where a set or sequence of strings (potentially with ordering or duplicates) is required,
 *   such as scripting, configuration, or resource management.
 */
class MxStringList : public MxList<MxString> {}; // [AI]

/**
 * @brief [AI] Cursor class for traversing an MxStringList.
 * @details [AI] Allows iteration over each MxString in an MxStringList using the typical cursor-style interface,
 *   providing access and navigation for list traversal.
 */
class MxStringListCursor : public MxListCursor<MxString> {
public:
	/**
	 * @brief [AI] Constructs a cursor attached to the given MxStringList.
	 * @param p_list The string list to iterate over. [AI]
	 * @details [AI] Initializes the cursor at the start of the provided list, ready for iteration.
	 */
	MxStringListCursor(MxStringList* p_list) : MxListCursor<MxString>(p_list) {} // [AI]
};

#endif // MXSTRINGLIST_H
