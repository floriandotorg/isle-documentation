#ifndef MXCORE_H
#define MXCORE_H

#include "compat.h"
#include "mxtypes.h"

#include <string.h>

class MxParam;

/// \class MxCore
/// \brief [AI] Base virtual class for all Mindscape engine (Mx) objects. Implements the identity and tickle mechanism for core objects.
/// \details [AI] This is the root of the Mx object hierarchy. It defines a set of core virtual methods, provides an identity (unique id per-instance), and virtual mechanisms for tickle/updating and runtime class information. All objects in the Mindscape system ultimately inherit from this class.
/// \size 0x08 [AI]
class MxCore {
public:
	/// \brief [AI] Constructs a new MxCore object and assigns it a unique id.
	MxCore();

	/// \brief [AI] Virtual destructor. Required for correct polymorphic cleanup in derived classes.
	virtual ~MxCore();                       // vtable+00

	/// \brief [AI] Virtual callback notification mechanism.
	/// \details [AI] Designed to be overridden in derived classes to handle notifications/events. The base implementation asserts and does nothing.
	/// \param p_param [AI] Notification-specific parameter object (see child implementations for semantics).
	virtual MxLong Notify(MxParam& p_param); // vtable+04

	/// \brief [AI] Called by tickle managers to allow the object to update itself.
	/// \details [AI] Override in derived classes for time-sliced processing ("tickling"). Used extensively by game logic and resource management systems.
	/// \return [AI] Returns SUCCESS in the base class.
	virtual MxResult Tickle() { return SUCCESS; } // vtable+08

	/// \brief [AI] Returns the runtime class name of this object.
	/// \details [AI] Used for RTTI and dynamic class checking instead of C++ RTTI.
	/// \return [AI] "MxCore" string literal.
	virtual const char* ClassName() const // vtable+0c
	{
		// STRING: LEGO1 0x100f007c
		return "MxCore";
	}

	/// \brief [AI] Checks whether this object's class type or parents match the given name.
	/// \details [AI] Used for dynamic class checking. The default implementation returns true if the name matches the class name exactly. Derived classes override and chain for true IsA hierarchy.
	/// \param p_name [AI] Class name to check against.
	/// \return [AI] True if p_name equals this object's class name.
	virtual MxBool IsA(const char* p_name) const // vtable+10
	{
		return !strcmp(p_name, MxCore::ClassName());
	}

	/// \brief [AI] Gets the unique (per-process) id assigned to this object instance.
	MxU32 GetId() { return m_id; }

	// SYNTHETIC: LEGO1 0x100ae1c0
	// SYNTHETIC: BETA10 0x1012c0d0
	// MxCore::`scalar deleting destructor'

private:
	/// \brief [AI] Static atomic counter used for generating unique core ids.
	/// \details [AI] Each new MxCore assigns itself g_nextCoreId, then increments it. Used to uniquely identify MxCore-derived objects during their lifetime (may wrap on overflow).
	static MxU32 g_nextCoreId;

	/// \brief [AI] Unique instance id for this MxCore (set at construction from g_nextCoreId).
	MxU32 m_id; // 0x04
};

// SYNTHETIC: BETA10 0x10096940
// MxCore::operator=

#endif // MXCORE_H
