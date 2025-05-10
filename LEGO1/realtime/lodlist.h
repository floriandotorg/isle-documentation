#ifndef LODLIST_H
#define LODLIST_H

#include "assert.h"

#include <stddef.h> // size_t

class LODObject;

// disable: identifier was truncated to '255' characters in the debug information
#pragma warning(disable : 4786)

//////////////////////////////////////////////////////////////////////////////
//
// LODListBase
//
// An LODListBase is an ordered list of LODObjects
// where each successive object in the list has a more complex
// geometric representation than the one preceeding it.
//

// VTABLE: LEGO1 0x100dbdc8
// VTABLE: BETA10 0x101c3500
// SIZE 0x10
/**
 * @brief [AI] Abstract base class for an ordered list of LODObject pointers, where each entry represents
 *        an increasing level of geometric detail. Provides functionality to store and access the LOD chain,
 *        manage its capacity, and order.
 * @details [AI] LODListBase is not copyable and is intended as a base for typed LOD collections. 
 */
class LODListBase {
protected:
	/**
	 * @brief [AI] Constructs a new LODListBase with specified storage capacity.
	 * @param capacity [AI] The maximum number of LODObject pointers the list can hold.
	 */
	LODListBase(size_t capacity);

	/**
	 * @brief [AI] Adds a new LODObject pointer at the end of the list.
	 * @param pLOD [AI] The pointer to the LODObject to append.
	 * @return [AI] Pointer to the added LODObject.
	 */
	const LODObject* PushBack(const LODObject*);
	/**
	 * @brief [AI] Removes and returns the last LODObject pointer from the list.
	 * @return [AI] Pointer to the removed LODObject or undefined if the list is empty (asserts).
	 */
	const LODObject* PopBack();

public:
	/**
	 * @brief [AI] Destructor. Deallocates internal storage. Asserts that the list is empty.
	 */
	virtual ~LODListBase();
	/**
	 * @brief [AI] Returns a pointer to the LODObject at the given index.
	 * @param i [AI] Index in the list (asserts if out of bounds).
	 * @return [AI] Pointer to the LODObject.
	 */
	const LODObject* operator[](int) const;

	/**
	 * @brief [AI] Returns the current number of LODObject pointers contained.
	 * @return [AI]
	 */
	size_t Size() const;

	/**
	 * @brief [AI] Returns the maximum number of LODObject pointers the list can hold.
	 * @return [AI]
	 */
	size_t Capacity() const;

	// SYNTHETIC: LEGO1 0x100a77b0
	// SYNTHETIC: BETA10 0x1017b410
	// LODListBase::`scalar deleting destructor'

#ifdef _DEBUG
	/**
	 * @brief [AI] For debug builds: print the contents and capacity statistics.
	 * @param pTracer [AI] Function pointer to a print handler accepting printf-style parameters.
	 */
	virtual void Dump(void (*pTracer)(const char*, ...)) const;
#endif

private:
	// not implemented
	LODListBase(const LODListBase&);
	LODListBase& operator=(const LODListBase&);

private:
	const LODObject** m_ppLODObject; //!< [AI] Array of pointers to LODObjects, implementing the backing storage.
	size_t m_capacity;               //!< [AI] Maximum number of LODObject* that may be stored.
	size_t m_size;                   //!< [AI] Current number of valid entries in m_ppLODObject.
};

//////////////////////////////////////////////////////////////////////////////
//
// LODList
//

/**
 * @brief [AI] Type-safe extension of LODListBase, templated for any LODObject-derived type.
 *        Provides typed access/casting for stored pointers.
 * @details [AI] Used to represent lists of a specific type of LOD object, such as ViewLOD.
 * @tparam T [AI] A type derived from LODObject.
 */
template <class T>
class LODList : public LODListBase {
public:
	/**
	 * @brief [AI] Constructs a type-safe LODList with given capacity.
	 * @param capacity [AI] Maximum number of pointers the list can hold.
	 */
	LODList(size_t capacity);

	/**
	 * @brief [AI] Typed access to the LODObject at position i.
	 * @param i [AI] Index in the list.
	 * @return [AI] Pointer to the object of type T.
	 */
	const T* operator[](int) const;
	/**
	 * @brief [AI] Typed append. Adds a pointer to an object of type T at the end of the list.
	 * @param pLOD [AI] Pointer to the object to add.
	 * @return [AI] Pointer to added object.
	 */
	const T* PushBack(const T*);
	/**
	 * @brief [AI] Typed remove. Removes and returns the last element as T*.
	 * @return [AI] Pointer to removed object.
	 */
	const T* PopBack();
};

//////////////////////////////////////////////////////////////////////////////
//
// LODListBase implementation

// FUNCTION: BETA10 0x1017b390
inline LODListBase::LODListBase(size_t capacity)
	: m_capacity(capacity), m_size(0), m_ppLODObject(new const LODObject*[capacity])
{
#ifdef _DEBUG
	int i;

	for (i = 0; i < (int) m_capacity; i++) {
		m_ppLODObject[i] = 0;
	}
#endif
}

// FUNCTION: LEGO1 0x100a77e0
// FUNCTION: BETA10 0x1017b450
inline LODListBase::~LODListBase()
{
	// all LODObject* should have been popped by client
	assert(m_size == 0);

	delete[] m_ppLODObject;
}

// FUNCTION: BETA10 0x1005c480
inline size_t LODListBase::Size() const
{
	return m_size;
}

// FUNCTION: BETA10 0x10178b40
inline size_t LODListBase::Capacity() const
{
	return m_capacity;
}

// FUNCTION: BETA10 0x1007b6a0
inline const LODObject* LODListBase::operator[](int i) const
{
	assert((0 <= i) && (i < (int) m_size));

	return m_ppLODObject[i];
}

// FUNCTION: BETA10 0x1007bb40
inline const LODObject* LODListBase::PushBack(const LODObject* pLOD)
{
	assert(m_size < m_capacity);

	m_ppLODObject[m_size++] = pLOD;
	return pLOD;
}

// FUNCTION: BETA10 0x10178b60
inline const LODObject* LODListBase::PopBack()
{
	const LODObject* pLOD;

	assert(m_size > 0);

	pLOD = m_ppLODObject[--m_size];

#ifdef _DEBUG
	m_ppLODObject[m_size] = 0;
#endif

	return pLOD;
}

#ifdef _DEBUG
// FUNCTION: BETA10 0x1017b4c0
inline void LODListBase::Dump(void (*pTracer)(const char*, ...)) const
{
	int i;

	pTracer("LODListBase<0x%x>: Capacity=%d, Size=%d\n", (void*) this, m_capacity, m_size);

	for (i = 0; i < (int) m_size; i++) {
		pTracer("   [%d]: LOD<0x%x>\n", i, m_ppLODObject[i]);
	}

	for (i = (int) m_size; i < (int) m_capacity; i++) {
		assert(m_ppLODObject[i] == 0);
	}
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// LODList implementation

template <class T>
inline LODList<T>::LODList(size_t capacity) : LODListBase(capacity)
{
}

template <class T>
inline const T* LODList<T>::operator[](int i) const
{
	return static_cast<const T*>(LODListBase::operator[](i));
}

template <class T>
inline const T* LODList<T>::PushBack(const T* pLOD)
{
	return static_cast<const T*>(LODListBase::PushBack(pLOD));
}

template <class T>
inline const T* LODList<T>::PopBack()
{
	return static_cast<const T*>(LODListBase::PopBack());
}

// VTABLE: LEGO1 0x100dbdc0
// VTABLE: BETA10 0x101c34f8
// class LODList<ViewLOD>

// SYNTHETIC: LEGO1 0x100a7740
// SYNTHETIC: BETA10 0x1017b350
// LODList<ViewLOD>::`scalar deleting destructor'

// TEMPLATE: BETA10 0x10178b20
// LODList<ViewLOD>::PopBack

// TEMPLATE: BETA10 0x1017b2d0
// LODList<ViewLOD>::LODList<ViewLOD>

// TEMPLATE: LEGO1 0x100a8160
// TEMPLATE: BETA10 0x1017b5d0
// LODList<ViewLOD>::~LODList<ViewLOD>

// TEMPLATE: BETA10 0x1007bae0
// LODList<ViewLOD>::operator[]

// re-enable: identifier was truncated to '255' characters in the debug information
#pragma warning(default : 4786)

#endif // LODLIST_H
