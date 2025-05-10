#ifndef LEGOPHONEME_H
#define LEGOPHONEME_H

#include "decomp.h"
#include "mxstring.h"

class LegoTextureInfo;

// VTABLE: LEGO1 0x100d7c88
// SIZE 0x20

/**
 * @brief [AI] Represents a single phoneme (mouth shape) used for character lip-sync and speech animation. 
 *             Contains a name and up to two possible texture associations. 
 *             Typically, this class is used to manage the mapping between phoneme names and their visual representations/textures.
 * @details [AI] The class encapsulates the phoneme's string identifier, configuration (unknown property 0x14), and links to
 *              two LegoTextureInfo instances that describe the phoneme's in-game visual representation.
 */
class LegoPhoneme {
public:
	/**
	 * @brief [AI] Constructs a LegoPhoneme object using the provided name and an unknown parameter.
	 * @param p_name [AI] String identifier for the phoneme (e.g., "EH", "OO", etc). Will be uppercased for consistency.
	 * @param p_unk0x14 [AI] Unknown property/configuration value affecting the phoneme (purpose unknown).
	 */
	LegoPhoneme(const char* p_name, undefined4 p_unk0x14)
	{
		m_name = p_name;
		m_name.ToUpperCase();
		Init();
		m_unk0x14 = p_unk0x14;
	}

	/**
	 * @brief [AI] Destroys the LegoPhoneme object. Releases any owned resources.
	 */
	~LegoPhoneme();

	/**
	 * @brief [AI] Retrieves the value of the unknown property at offset 0x14.
	 * @return [AI] Value of m_unk0x14.
	 */
	virtual undefined4 VTable0x00();                     // vtable+0x00

	/**
	 * @brief [AI] Sets the value of the unknown property at offset 0x14.
	 * @param p_unk0x14 [AI] The new value for m_unk0x14.
	 */
	virtual void VTable0x04(undefined4 p_unk0x14);       // vtable+0x04

	/**
	 * @brief [AI] Retrieves the primary texture info associated with this phoneme.
	 * @return [AI] Pointer to LegoTextureInfo used for the standard mouth shape.
	 */
	virtual LegoTextureInfo* VTable0x08();               // vtable+0x08

	/**
	 * @brief [AI] Sets the primary texture info for this phoneme.
	 * @param p_unk0x18 [AI] Pointer to the texture information representing this phoneme's default face/mouth.
	 */
	virtual void VTable0x0c(LegoTextureInfo* p_unk0x18); // vtable+0x0c

	/**
	 * @brief [AI] Retrieves an alternate texture info for this phoneme.
	 * @return [AI] Pointer to LegoTextureInfo for an alternate mouth/face shape (if any).
	 */
	virtual LegoTextureInfo* VTable0x10();               // vtable+0x10

	/**
	 * @brief [AI] Sets the alternate texture info for this phoneme.
	 * @param p_unk0x1c [AI] Pointer to the alternate texture information (if used).
	 */
	virtual void VTable0x14(LegoTextureInfo* p_unk0x1c); // vtable+0x14

	/**
	 * @brief [AI] Optional virtual hook—purpose unclear, likely overridden in derived classes or for cleanup/reset.
	 */
	virtual void VTable0x18();                           // vtable+0x18

	/**
	 * @brief [AI] Initializes internal phoneme state (resets properties/textures).
	 */
	virtual void Init();                                 // vtable+0x1c

	/**
	 * @brief [AI] Unclear purpose; accepts an unknown argument. No implementation provided in the base class.
	 * @param [unnamed] [AI] Unknown/unused.
	 */
	virtual void VTable0x20(undefined4);                 // vtable+0x20

	/**
	 * @brief [AI] Returns (mutable) reference to the phoneme's name.
	 * @return [AI] Reference to the name string of this phoneme.
	 */
	MxString& GetName() { return m_name; }

private:
	MxString m_name;            ///< @brief [AI] Name (identifier) of the phoneme (uppercased). 
	undefined4 m_unk0x14;       ///< @brief [AI] Unknown configuration value (possibly a property or index for the phoneme).
	LegoTextureInfo* m_unk0x18; ///< @brief [AI] Pointer to primary texture information for this phoneme.
	LegoTextureInfo* m_unk0x1c; ///< @brief [AI] Pointer to alternative texture information for this phoneme.
};

#endif // LEGOPHONEME_H