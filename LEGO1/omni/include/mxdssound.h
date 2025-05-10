#ifndef MXDSSOUND_H
#define MXDSSOUND_H

#include "mxdsmediaaction.h"

// VTABLE: LEGO1 0x100dcdd0
// VTABLE: BETA10 0x101c2b68
// SIZE 0xc0

/**
 * @brief [AI] Represents a sound action extracted from an SI script and used in the data-driven action system. 
 * @details [AI] MxDSSound inherits from MxDSMediaAction and specifically encapsulates data for a sound, including volume and serialization utilities. Used in the context of triggered events for playing sounds within the game engine.
 */
class MxDSSound : public MxDSMediaAction {
public:
	/**
	 * @brief [AI] Constructs a MxDSSound object with default values (type set to e_sound, default volume).
	 */
	MxDSSound();

	/**
	 * @brief [AI] Copy constructor for duplicating sound action data from another MxDSSound.
	 * @param p_dsSound The source MxDSSound to copy from. [AI]
	 */
	MxDSSound(MxDSSound& p_dsSound);

	/**
	 * @brief [AI] Destructor for cleanup (none specifically required, present for consistency).
	 */
	~MxDSSound() override;

	/**
	 * @brief [AI] Copies properties from another MxDSSound (volume and type).
	 * @param p_dsSound The source MxDSSound to copy from. [AI]
	 */
	void CopyFrom(MxDSSound& p_dsSound);

	/**
	 * @brief [AI] Assignment operator. Duplicates sound action data from another MxDSSound instance.
	 * @param p_dsSound The source MxDSSound to assign from. [AI]
	 * @return Reference to this. [AI]
	 */
	MxDSSound& operator=(MxDSSound& p_dsSound);

	/**
	 * @brief [AI] Returns the class type name "MxDSSound" as a string literal.
	 * @return Class name string. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x101025e4
		return "MxDSSound";
	}

	/**
	 * @brief [AI] Tests for type identity against this class or ancestors.
	 * @param p_name Requested class name. [AI]
	 * @return True if p_name matches this class or any ancestor's class name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSSound::ClassName()) || MxDSMediaAction::IsA(p_name);
	}

	/**
	 * @brief [AI] Returns the total size the action will occupy on disk, including media action and volume.
	 */
	MxU32 GetSizeOnDisk() override;                              // vtable+0x18

	/**
	 * @brief [AI] Deserializes this object from binary SI file data, extracting volume after base class fields.
	 * @param p_source Reference to pointer of serialized data buffer (is incremented appropriately). [AI]
	 * @param p_unk0x24 Action type/flags; passed to base class. [AI]
	 */
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override; // vtable+0x1c

	/**
	 * @brief [AI] Creates a duplicate of this MxDSSound instance.
	 * @details [AI] Used in scripting contexts that require a deep copy of the sound action.
	 * @return New cloned instance (heap-allocated). [AI]
	 */
	MxDSAction* Clone() override;                                // vtable+0x2c

	/**
	 * @brief [AI] Returns the stored volume field for the sound.
	 * @details [AI] This value defines how loud the sound should be when played.
	 */
	MxS32 GetVolume() const { return m_volume; }

	// SYNTHETIC: LEGO1 0x100c9450
	// SYNTHETIC: BETA10 0x1015d9d0
	// MxDSSound::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] The number of bytes written for this object when serialized to disk (does not include base class).
	 */
	MxU32 m_sizeOnDisk; // 0xb8

	/**
	 * @brief [AI] Playback volume for this sound action. Range is typically 0 (muted) to 0x7F (full).
	 */
	MxS32 m_volume;     // 0xbc
};

#endif // MXDSSOUND_H
