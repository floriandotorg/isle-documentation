#ifndef MXDSOBJECT_H
#define MXDSOBJECT_H

#include "decomp.h"
#include "mxatom.h"
#include "mxcore.h"
#include "mxutilitylist.h"

class MxDSFile;
class MxDSObject;
class MxPresenter;

/// \class MxDSObjectList
/// \brief [AI] Utility list for managing dynamic sequence (DS) objects, provides search and removal by pointer and state.
/// \details [AI] This is a utility list specifically containing pointers to MxDSObject instances. Used to look up and optionally erase matching DS action objects by their object and state identifiers. [AI]
/// \see MxDSObject
// SIZE 0x0c
class MxDSObjectList : public MxUtilityList<MxDSObject*> {
public:
	/// \brief [AI] Finds the matching object and removes it from the list.
	/// \param p_action Pointer to the DS object to find and erase. [AI]
	/// \return Pointer to the found and erased object (if any), otherwise NULL. [AI]
	MxDSObject* FindAndErase(MxDSObject* p_action) { return FindInternal(p_action, TRUE); }

	/// \brief [AI] Finds a matching object in the list without removing it.
	/// \param p_action Pointer to the DS object to search for. [AI]
	/// \return Pointer to the found object (if any), otherwise NULL. [AI]
	MxDSObject* Find(MxDSObject* p_action) { return FindInternal(p_action, FALSE); }

private:
	/// \brief [AI] Internal search routine for finding by object id and status, optionally erasing the item.
	/// \param p_action Pointer to prototype action (object id/status must match). [AI]
	/// \param p_delete If true, found object is erased from the list. [AI]
	/// \return Pointer to matching object or NULL. [AI]
	MxDSObject* FindInternal(MxDSObject* p_action, MxBool p_delete);
};

/// \class MxDSObject
/// \brief [AI] Base class for any object deserialized from an SI (script/data) file in the LEGO Island engine.
/// \details [AI] Represents a deserialized data object with identifiers, type, and names, used for collection, dispatch, and presenter instantiation. The class includes serialization information, atom ids (for identifying unique objects/resources), and ties to the presenter system. [AI_SUGGESTED_NAME: DataSequenceObject]
// VTABLE: LEGO1 0x100dc868
// VTABLE: BETA10 0x101c23f0
// SIZE 0x2c
class MxDSObject : public MxCore {
public:
	/// \enum Type
	/// \brief [AI] Enumerated type value for each kind of DS object. [AI]
	enum Type {
		e_object = 0,        ///< [AI] Base object, most basic type. [AI]
		e_action,            ///< [AI] Simple action or command invocation. [AI]
		e_mediaAction,       ///< [AI] Media-related action (usually for videos, audio, etc). [AI]
		e_anim,              ///< [AI] Animation sequence or reference. [AI]
		e_sound,             ///< [AI] Sound resource reference or cue. [AI]
		e_multiAction,       ///< [AI] Composite/multi-action list. [AI]
		e_serialAction,      ///< [AI] Series of actions to play in order. [AI]
		e_parallelAction,    ///< [AI] Parallel (simultaneous) action list. [AI]
		e_event,             ///< [AI] Scripted event type. [AI]
		e_selectAction,      ///< [AI] Selects an action from several (with rules/random). [AI]
		e_still,             ///< [AI] Still image resource. [AI]
		e_objectAction,      ///< [AI] Placeholder for generic object operations. [AI]
	};

	/// \brief [AI] Default constructor. Initializes to e_object and clears names and pointers.
	MxDSObject();

	/// \brief [AI] Destructor. Frees allocated objectName/sourceName memory.
	~MxDSObject() override;

	/// \brief [AI] Copy data from another MxDSObject, performing deep string copy for names.
	/// \param p_dsObject Source MxDSObject to copy from. [AI]
	void CopyFrom(MxDSObject& p_dsObject);

	/// \brief [AI] Copy constructor. [AI]
	/// \param p_dsObject Source MxDSObject. [AI]
	MxDSObject(MxDSObject& p_dsObject);

	/// \brief [AI] Assignment operator. Deep-copies fields. [AI]
	/// \param p_dsObject Source to assign from. [AI]
	/// \return Reference to this object. [AI]
	MxDSObject& operator=(MxDSObject& p_dsObject);

	/// \brief [AI] Sets object (internal) unique name; deep copies the string.
	/// \param p_objectName C-string to set as objectName. [AI]
	void SetObjectName(const char* p_objectName);

	/// \brief [AI] Sets the source name (usually source SI file); deep copies the string.
	/// \param p_sourceName C-string to set as sourceName. [AI]
	void SetSourceName(const char* p_sourceName);

	/// \brief [AI] Returns the class identifier string for run-time type ID.
	/// \return Pointer to literal class name string. [AI]
	const char* ClassName() const override { return "MxDSObject"; } // vtable+0x0c

	/// \brief [AI] Runtime type check; supports derived/parent class lookup by name.
	/// \param p_name Type name to compare. [AI]
	/// \return True if type matches this or any base type. [AI]
	MxBool IsA(const char* p_name) const override
	{
		return !strcmp(p_name, MxDSObject::ClassName()) || MxCore::IsA(p_name);
	} // vtable+0x10

	/// \brief [AI] Placeholder for early vtable slot (purpose unknown, may be used for RTTI). [AI]
	/// \return Always returns 10. [AI]
	virtual undefined4 VTable0x14();                            // vtable+0x14

	/// \brief [AI] Calculates serialized size of this object on disk (for buffer allocation).
	/// \return Size in bytes needed to serialize this object. [AI]
	virtual MxU32 GetSizeOnDisk();                              // vtable+0x18

	/// \brief [AI] Initializes this object from serialized (memory buffer) data.
	/// \param p_source Reference to pointer for in-place buffer decoding, pointer is advanced. [AI]
	/// \param p_unk0x24 Likely data version or additional context flag. [AI]
	/// [AI] Sets object/source names, object id, and type flag from the provided buffer.
	virtual void Deserialize(MxU8*& p_source, MxS16 p_unk0x24); // vtable+0x1c

	/// \brief [AI] Sets the atom id for this object instance, used for indexing or lookup.
	/// \param p_atomId Atom identifier for string/value pair. [AI]
	virtual void SetAtomId(MxAtomId p_atomId) { m_atomId = p_atomId; } // vtable+0x20

	/// \brief [AI] Returns the object's type enum as stored in m_type.
	Type GetType() const { return (Type) m_type; }

	/// \brief [AI] Returns the source name string (typically the originating SI file).
	const char* GetSourceName() const { return m_sourceName; }

	/// \brief [AI] Returns the object name string.
	const char* GetObjectName() const { return m_objectName; }

	/// \brief [AI] Returns the object id numeric value.
	MxU32 GetObjectId() { return m_objectId; }

	/// \brief [AI] Returns a const-reference to the object's atom identifier.
	const MxAtomId& GetAtomId() { return m_atomId; }

	/// \brief [AI] Returns the unknown 0x24 value (may be data version or usage state). [AI]
	MxS16 GetUnknown24() { return m_unk0x24; }

	/// \brief [AI] Returns the pointer stored at 0x28, likely a presenter or handler for this DS object.
	MxPresenter* GetUnknown28() { return m_unk0x28; }

	/// \brief [AI] Sets the DS object type.
	/// \param p_type Value to store as m_type. [AI]
	void SetType(Type p_type) { m_type = p_type; }

	/// \brief [AI] Sets the object id (for serialization or lookup).
	/// \param p_objectId Value to use as objectId. [AI]
	void SetObjectId(MxU32 p_objectId) { m_objectId = p_objectId; }

	/// \brief [AI] Sets the unknown field at 0x24 (possibly version/state).
	/// \param p_unk0x24 Value for 0x24. [AI]
	void SetUnknown24(MxS16 p_unk0x24) { m_unk0x24 = p_unk0x24; }

	/// \brief [AI] Sets the pointer at 0x28 (presenter or handler).
	/// \param p_unk0x28 Pointer, usually to a MxPresenter. [AI]
	void SetUnknown28(MxPresenter* p_unk0x28) { m_unk0x28 = p_unk0x28; }

	/// \brief [AI] Clears the atom id, releasing its association.
	void ClearAtom() { m_atomId.Clear(); }

	// SYNTHETIC: LEGO1 0x100bf7c0
	// SYNTHETIC: BETA10 0x10148770
	// MxDSObject::`scalar deleting destructor'

protected:
	MxU32 m_sizeOnDisk;     ///< [AI] Cached/calculated disk size of object data for serialization. [AI]
	MxU16 m_type;           ///< [AI] Object type enum (see Type) as read from data or set in code. [AI]
	char* m_sourceName;     ///< [AI] Heap copy: SI file or source identifier string. [AI]
	undefined4 m_unk0x14;   ///< [AI] Unknown usage, possibly flags or reserved SI-format field. [AI]
	char* m_objectName;     ///< [AI] Heap copy: Logical object name as referenced in script/data. [AI]
	MxU32 m_objectId;       ///< [AI] Numeric id (unique per file or context, often -1). [AI]
	MxAtomId m_atomId;      ///< [AI] String/value pair for engine lookup/reference. [AI]
	MxS16 m_unk0x24;        ///< [AI] Unknown usage, possibly used for context or flags during loading. [AI]
	MxPresenter* m_unk0x28; ///< [AI] Presenter or handler associated to this object (may be null). [AI]
};

/// \brief [AI] Reads and deserializes a DS object of the specific type from an SI buffer.
/// \param p_source Pointer to buffer pointer; pointer is advanced upon deserialization. [AI]
/// \param p_flags Optional flags used to influence deserialization (context-specific). [AI]
/// \return Pointer to the newly allocated MxDSObject (specific derived type), or NULL if type is unknown. [AI]
MxDSObject* DeserializeDSObjectDispatch(MxU8*&, MxS16);

/// \brief [AI] Creates and deserializes a stream object from a chunk inside a DS file.
/// \param p_file Pointer to DS file to load from. [AI]
/// \param p_ofs Offset into the DS file chunk. [AI]
/// \return Pointer to a newly created/deserialized DS object, or NULL on error. [AI]
MxDSObject* CreateStreamObject(MxDSFile*, MxS16);

// TEMPLATE: BETA10 0x10150950
// MxUtilityList<MxDSObject *>::PopFront

#endif // MXDSOBJECT_H
