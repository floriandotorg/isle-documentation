#ifndef MXQUEUE_H
#define MXQUEUE_H

#include "mxlist.h"

/// @class MxQueue
/// @brief Template class implementing a queue, derived from MxList. [AI]
/// @details Provides typical queue operations (enqueue and dequeue) using the list infrastructure for storage. [AI]
/// @tparam T Type of object to be stored in the queue. [AI]
template <class T>
class MxQueue : public MxList<T> {
public:
	/// @brief Adds an object to the end of the queue. [AI]
	/// @param p_obj Reference to the object to be enqueued. [AI]
	void Enqueue(T& p_obj)
	{
		// TODO
	}

	/// @brief Removes the object from the front of the queue and copies it to p_obj. [AI]
	/// @param p_obj Reference to object where the dequeued value will be copied. [AI]
	/// @return TRUE if an object was dequeued, FALSE if the queue was empty. [AI]
	MxBool Dequeue(T& p_obj)
	{
		MxBool hasNext = (this->m_first != NULL);
		if (this->m_first) {
			p_obj = this->m_first->GetValue();
			this->DeleteEntry(this->m_first);
		}

		return hasNext;
	}
};

#endif // MXQUEUE_H
