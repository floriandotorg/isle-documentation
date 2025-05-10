#ifndef MXCOLLECTION_H
#define MXCOLLECTION_H

#include "mxcore.h"

/// @brief [AI] Template class for a generic collection, providing fundamental storage and comparison facilities, in addition to customized destruction policies.
/// @details [AI] MxCollection is a template base class for non-owning or lightweight-owning containers within the LEGO Island engine architecture. It manages element count, supports a custom destruction strategy for elements, and provides a virtual interface for type-specific comparisons. Designed to be subclassed for concrete storage behaviors.
/// @tparam T [AI] Type of element stored in the collection.
template <class T>
class MxCollection : public MxCore {
public:
	/// @brief [AI] Constructs an empty collection, initializing count and default element destructor.
	MxCollection()
	{
		m_count = 0;
		SetDestroy(Destroy);
	}

	/// @brief [AI] Compares two elements of the collection (default implementation returns zero; override in subclasses for meaningful comparison).
	/// @param a [AI] First element to compare.
	/// @param b [AI] Second element to compare.
	/// @return [AI] See subclass documentation; default is no ordering.
	virtual MxS8 Compare(T a, T b) { return 0; } // vtable+0x14

	/// @brief [AI] Virtual destructor for proper polymorphic destruction.
	~MxCollection() override {}

	/// @brief [AI] Static no-op destroy function; suitable for types that do not need destruction.
	/// @param obj [AI] Collection element (unused in default implementation).
	static void Destroy(T obj) {}

	/// @brief [AI] Assigns a custom destructor function to be used for elements of this collection.
	/// @param p_customDestructor [AI] Pointer to a function responsible for cleaning up individual collection elements.
	void SetDestroy(void (*p_customDestructor)(T)) { this->m_customDestructor = p_customDestructor; }

protected:
	MxU32 m_count;                 ///< @brief [AI] Number of elements currently stored in the collection.
	void (*m_customDestructor)(T); ///< @brief [AI] Function pointer to the custom element destructor used for cleanup of elements.
};

#endif // MXCOLLECTION_H
