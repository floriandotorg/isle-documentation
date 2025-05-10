#ifndef MXUTILITYLIST_H
#define MXUTILITYLIST_H

#include "mxstl/stlcompat.h"

// Probably should be defined somewhere else

/**
 * @brief [AI] A utility list extending the STL list<T>, providing simplified PushBack, Remove, and a PopFront operation.
 * @details [AI] MxUtilityList enhances std::list by adding convenience methods for pushing, popping, and removing elements,
 *   with the addition of a PopFront method that pops and copies the first item into a reference, as well as wrapping push_back and remove for simple access. [AI]
 */
template <class T>
class MxUtilityList : public list<T> {
public:
	/**
	 * @brief [AI] Removes and returns the first element of the list.
	 * @details [AI] If the list is not empty, copies the front value of the list to p_obj, pops the head, and returns TRUE. Otherwise, does nothing and returns FALSE. [AI]
	 * @param p_obj [AI] Reference to a variable of type T where the first object will be copied if the list is not empty.
	 * @return TRUE if an item was popped, FALSE if the list was empty. [AI]
	 */
	MxBool PopFront(T& p_obj)
	{
		if (this->empty()) {
			return FALSE;
		}

		p_obj = this->front();
		this->pop_front();
		return TRUE;
	}

	/**
	 * @brief [AI] Pushes a copy of the provided object to the back of the list. [AI]
	 * @details [AI] Calls std::list<T>::push_back(p_obj). [AI]
	 * @param p_obj [AI] Object to add to the back of the list.
	 */
	void PushBack(T p_obj) { this->push_back(p_obj); }

	/**
	 * @brief [AI] Removes all matching objects from the list. [AI]
	 * @details [AI] Calls std::list<T>::remove(p_obj), which removes all elements equal to p_obj. [AI]
	 * @param p_obj [AI] Object(s) to remove from the list.
	 */
	void Remove(T p_obj) { this->remove(p_obj); }
};

#endif // MXUTILITYLIST_H
