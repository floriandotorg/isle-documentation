#ifndef MXDSMEDIAACTION_H
#define MXDSMEDIAACTION_H

#include "decomp.h"
#include "mxdsaction.h"

// VTABLE: LEGO1 0x100dcd40
// VTABLE: BETA10 0x101c2ad8
// SIZE 0xb8

/**
 * @brief MxDSMediaAction extends MxDSAction to add media-specific playback properties and management. [AI]
 * 
 * This class is used as a base for DS objects that represent a media action in the LEGO Island engine, 
 * providing parameters such as media source path, frame rate, format, palette options, and sustain time.
 * [AI]
 */
class MxDSMediaAction : public MxDSAction {
public:
	/**
	 * @brief Constructs a new MxDSMediaAction and initializes all members. [AI]
	 */
	MxDSMediaAction();

	/**
	 * @brief Copy constructor; constructs a new MxDSMediaAction by copying the state of another. [AI]
	 * @param p_dsMediaAction Reference to the MxDSMediaAction to copy from. [AI]
	 */
	MxDSMediaAction(MxDSMediaAction& p_dsMediaAction);

	/**
	 * @brief Destructor. Cleans up allocated media source path memory. [AI]
	 */
	~MxDSMediaAction() override;

	/**
	 * @brief Copy the internal state and properties from another MxDSMediaAction. [AI]
	 * @param p_dsMediaAction The source object to copy from. [AI]
	 */
	void CopyFrom(MxDSMediaAction& p_dsMediaAction);

	/**
	 * @brief Assignment operator. Copies the state from another MxDSMediaAction, including deep copies where required. [AI]
	 * @param p_dsMediaAction Source of the data to assign. [AI]
	 * @return Reference to this object. [AI]
	 */
	MxDSMediaAction& operator=(MxDSMediaAction& p_dsMediaAction);

	/**
	 * @brief Returns the class name string for this object. [AI]
	 * @return "MxDSMediaAction" as the class name. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f7624
		return "MxDSMediaAction";
	}

	/**
	 * @brief Checks for class membership. Compares with this and parent class names. [AI]
	 * @param p_name Class name string to query. [AI]
	 * @return True if p_name matches this class or any parent class in hierarchy. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxDSMediaAction::ClassName()) || MxDSAction::IsA(p_name);
	}

	// SYNTHETIC: LEGO1 0x100c8cd0
	// SYNTHETIC: BETA10 0x1015d810
	// MxDSMediaAction::`scalar deleting destructor'

	/**
	 * @brief [AI] Implementation-specific vtable placeholder. Inherited from MxDSAction. Purpose unknown. [AI_SUGGESTED_NAME: ReservedVTable0x14]
	 */
	undefined4 VTable0x14() override;                            // vtable+0x14

	/**
	 * @brief Calculates size in bytes required to store this object on disk, including strings and additional fields. [AI]
	 * @return Total size in bytes needed for serialization. [AI]
	 */
	MxU32 GetSizeOnDisk() override;                              // vtable+0x18

	/**
	 * @brief Deserializes the object data from a binary buffer, restoring state including media source path and configuration. [AI]
	 * @param p_source Pointer reference to the current read position in the buffer. [AI]
	 * @param p_unk0x24 Deserialization flags, see MxDSAction. [AI]
	 */
	void Deserialize(MxU8*& p_source, MxS16 p_unk0x24) override; // vtable+0x1c

	/**
	 * @brief Creates a deep copy (clone) of this action and returns it. [AI]
	 * @return Pointer to a new MxDSAction clone. [AI]
	 */
	MxDSAction* Clone() override;                                // vtable+0x2c

	/**
	 * @brief Deep-copies a new string for the media source path; cleans up previous memory as needed. [AI]
	 * @param p_mediaSrcPath Source path string for the media. [AI]
	 */
	void CopyMediaSrcPath(const char* p_mediaSrcPath);

	/**
	 * @brief Provides access to the path string of the media resource used by this action. [AI]
	 * @return The media source path as a const char pointer. [AI]
	 */
	const char* GetMediaSrcPath() { return m_mediaSrcPath; }

	/**
	 * @brief Gets the frame rate to use for media playback. [AI]
	 * @return Frames per second as integer. [AI]
	 */
	MxS32 GetFramesPerSecond() const { return m_framesPerSecond; }

	/**
	 * @brief Returns the media format code (e.g., FLC, SMK, WAV) for playback and presenter dispatch. [AI]
	 * @return Media format as integer code. [AI]
	 */
	MxS32 GetMediaFormat() const { return m_mediaFormat; }

	/**
	 * @brief Gets the palette management mode for playback of this media. [AI]
	 * @return Palette management value. [AI]
	 */
	MxS32 GetPaletteManagement() const { return m_paletteManagement; }

	/**
	 * @brief Returns the sustain time for the media, i.e., time it should remain presented/active. [AI]
	 * @return Time in system-dependent units. [AI]
	 */
	MxLong GetSustainTime() const { return m_sustainTime; }

private:
	/**
	 * @brief [AI] Internal struct containing unknown 4-byte values, likely extra configuration for media action (e.g. timing, reserved flags). [AI_SUGGESTED_NAME: MediaExtraParams]
	 */
	struct Unk0x9cStruct {
		/**
		 * @brief Sets the value of the first (unknown) parameter. [AI]
		 * @param p_value New value for m_unk0x00. [AI]
		 */
		void SetUnk0x00(undefined4 p_value) { m_unk0x00 = p_value; }

		/**
		 * @brief Sets the value of the second (unknown) parameter. [AI]
		 * @param p_value New value for m_unk0x04. [AI]
		 */
		void SetUnk0x04(undefined4 p_value) { m_unk0x04 = p_value; }

		/**
		 * @brief First extra 4 bytes, purpose unknown; may be reserved for future parameters or flags. [AI]
		 */
		undefined4 m_unk0x00;

		/**
		 * @brief Second extra 4 bytes, purpose unknown. [AI]
		 */
		undefined4 m_unk0x04;
	};

	/**
	 * @brief Caches the calculated size of data this object will take on disk during serialization. [AI]
	 */
	MxU32 m_sizeOnDisk;        // 0x94

	/**
	 * @brief String representing the path to the media resource (audio/video) associated with this action. [AI]
	 */
	char* m_mediaSrcPath;      // 0x98

	/**
	 * @brief Internal unknown structure, see Unk0x9cStruct. May store media-specific configuration or reserved data. [AI]
	 */
	Unk0x9cStruct m_unk0x9c;   // 0x9c

	/**
	 * @brief Playback frame rate for this media. [AI]
	 */
	MxS32 m_framesPerSecond;   // 0xa4

	/**
	 * @brief Format code indicating type of media (e.g., FLC, SMK, MID, WAV). [AI]
	 */
	MxS32 m_mediaFormat;       // 0xa8

	/**
	 * @brief Palette management mode—configuration for how palette is handled during playback. [AI]
	 */
	MxS32 m_paletteManagement; // 0xac

	/**
	 * @brief The amount of time (duration in some time unit) that this media should be sustained after presentation. [AI]
	 */
	MxLong m_sustainTime;      // 0xb0

	/**
	 * @brief Unused or unknown 4 bytes seen in construction/set to -1. [AI]
	 */
	undefined4 m_unk0xb4;      // 0xb4
};

#endif // MXDSMEDIAACTION_H
