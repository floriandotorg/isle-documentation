#ifndef MXOBJECTFACTORY_H
#define MXOBJECTFACTORY_H

#include "mxatom.h"
#include "mxcore.h"

/// @def FOR_MXOBJECTFACTORY_OBJECTS(X)
/// @brief [AI] Macro listing the presenter class types handled by the object factory. Used to generate code for each presenter type.
/// @details [AI] Expands to a sequence of invocations of X for each supported presenter type, enabling easy addition/removal across factory creation code. [AI]
#define FOR_MXOBJECTFACTORY_OBJECTS(X)                                                                                 \
	X(MxPresenter)                                                                                                     \
	X(MxCompositePresenter)                                                                                            \
	X(MxVideoPresenter)                                                                                                \
	X(MxFlcPresenter)                                                                                                  \
	X(MxSmkPresenter)                                                                                                  \
	X(MxStillPresenter)                                                                                                \
	X(MxWavePresenter)                                                                                                 \
	X(MxMIDIPresenter)                                                                                                 \
	X(MxEventPresenter)                                                                                                \
	X(MxLoopingFlcPresenter)                                                                                           \
	X(MxLoopingSmkPresenter)                                                                                           \
	X(MxLoopingMIDIPresenter)

/// @class MxObjectFactory
/// @brief [AI] Factory class for dynamic creation and destruction of presenter and core objects using their string names. [AI]
/// @details [AI] 
/// This class is responsible for instantiating objects of several presenter types, 
/// identified by string names. It provides a polymorphic interface for creating and destroying objects 
/// derived from MxCore, enabling data-driven object management, notably from script or resource file loading. 
/// String IDs (as MxAtomId) corresponding to each supported object type are retained for fast lookup. [AI]
/// 
/// The factory manages a set of presenter and media handler objects used throughout the LEGO Island game engine. 
///
class MxObjectFactory : public MxCore {
public:
	/// @brief [AI] Constructs a new MxObjectFactory and initializes atom IDs for all supported presenter classes. [AI]
	/// @details [AI] Upon initialization, string/class name mappings are built as MxAtomId members for fast lookup in Create. [AI]
	MxObjectFactory();

	/// @brief [AI] Returns the class name. [AI]
	/// @return [AI] Static class name string: "MxObjectFactory".
	const char* ClassName() const override // vtable+0x0c
	{
		return "MxObjectFactory";
	}

	/// @brief [AI] Determines whether this class is or inherits from the named class. [AI]
	/// @param p_name Name of class to check against (case sensitive). [AI]
	/// @details [AI] Checks if p_name matches "MxObjectFactory" or its ancestor MxCore's name. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxObjectFactory::ClassName()) || MxCore::IsA(p_name);
	}

	/// @brief [AI] Creates a new instance of the class matching the provided string name. [AI]
	/// @param p_name Null-terminated name of the class to instantiate. Must match one of the supported presenter types. [AI]
	/// @details [AI] Returns a pointer to the newly created object derived from MxCore, or NULL if the class is unknown. [AI]
	virtual MxCore* Create(const char* p_name); // vtable+0x14

	/// @brief [AI] Destroys (deletes) a dynamic object created by this factory. [AI]
	/// @param p_object Pointer to the object (MxCore-derived) to destroy. [AI]
	/// @details [AI] Assumes the pointer was obtained from Create and is safe to delete (uses delete operator). [AI]
	virtual void Destroy(MxCore* p_object);     // vtable+0x18

	// SYNTHETIC: LEGO1 0x100b1160
	// MxObjectFactory::`scalar deleting destructor'
	// @brief [AI] Scalar deleting destructor used internally. [AI]

	// SYNTHETIC: LEGO1 0x10009020
	// MxObjectFactory::~MxObjectFactory
	// @brief [AI] Destructor for MxObjectFactory. [AI]

private:
#define X(V) \
	/// @brief [AI] AtomId for the supported class type #V. Used for fast string-to-class lookup in Create(). [AI] \
	MxAtomId m_id##V;
	FOR_MXOBJECTFACTORY_OBJECTS(X)
#undef X
};

#endif // MXOBJECTFACTORY_H