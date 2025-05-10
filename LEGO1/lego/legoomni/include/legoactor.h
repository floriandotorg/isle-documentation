#ifndef LEGOACTOR_H
#define LEGOACTOR_H

#include "decomp.h"
#include "legoentity.h"
#include "mxgeometry/mxmatrix.h"

class LegoCacheSound;

/// \brief [AI] Represents an actor (character) entity in the LEGO Island 3D world, providing specific actor logic, such as sound, camera, and identity. Inherits from LegoEntity.
/// \details [AI] LegoActor encapsulates information about game actors, including type (character), actor-specific sound control, and actor identity (ID and name). It also implements logic for camera attachment, speed setting, and sound muting based on parsed actions. Typical actor types are Pepper, Mama, Papa, Nick, Laura, and Brickster.
class LegoActor : public LegoEntity {
public:
	/// \brief [AI] Enumeration of actor IDs for known characters.
	enum {
		c_none = 0,      ///< No actor ([AI])
		c_pepper,        ///< Pepper Roni ([AI])
		c_mama,          ///< Mama ([AI])
		c_papa,          ///< Papa ([AI])
		c_nick,          ///< Nick ([AI])
		c_laura,         ///< Laura ([AI])
		c_brickster      ///< The Brickster ([AI])
	};

	/// \brief [AI] Constructs new LegoActor, initializes members.
	LegoActor();

	/// \brief [AI] Cleans up LegoActor; stops sound if active.
	~LegoActor() override;

	/// \brief [AI] Gets the class name of this object.
	/// \details [AI] Used for run-time identification within the engine.
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f0124
		return "LegoActor";
	}

	/// \brief [AI] Determines if the class is or derives from the given name.
	/// \details [AI] Checks for "LegoActor" or any base class using IsA.
	/// \param p_name The name of the type to test. [AI]
	/// \return True if type matches this class or any ancestor. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoActor::ClassName()) || LegoEntity::IsA(p_name);
	}

	/// \brief [AI] Parses an action string and applies parsed behaviors to the actor.
	/// \details [AI] Supports key-value pairs for camera attachment, speed, sound, mute, and visibility. Used by game scripts for dynamic behavior.
	/// \param p_extra The key-value action string. [AI]
	void ParseAction(char* p_extra) override;

	/// \brief [AI] Sets the Region of Interest (ROI, i.e. visual representation) for the actor, updating actor ID/type if name matches known actor names.
	/// \param p_roi Pointer to LegoROI to assign. [AI]
	/// \param p_bool1 If true, perform extra logic (see base class). [AI]
	/// \param p_bool2 If true, perform extra logic (see base class). [AI]
	void SetROI(LegoROI* p_roi, MxBool p_bool1, MxBool p_bool2) override;

	/// \brief [AI] Returns the current frequency factor for the actor's sound.
	virtual MxFloat GetSoundFrequencyFactor() { return m_frequencyFactor; } // vtable+0x50

	/// \brief [AI] Sets the frequency factor for the actor's sound playback (e.g., to alter pitch).
	/// \param p_frequencyFactor The desired frequency factor. [AI]
	virtual void SetSoundFrequencyFactor(MxFloat p_frequencyFactor)
	{
		m_frequencyFactor = p_frequencyFactor;
	} // vtable+0x54

	/// \brief [AI] Sets a floating point property, unknown usage (possibly animation or audio parameter).
	/// \param p_unk0x70 Value to store in m_unk0x70. [AI] [AI_SUGGESTED_NAME: SetVoicePitchModifier]
	virtual void VTable0x58(MxFloat p_unk0x70) { m_unk0x70 = p_unk0x70; } // vtable+0x58

	/// \brief [AI] Gets the unknown floating point property set by VTable0x58. [AI] [AI_SUGGESTED_NAME: GetVoicePitchModifier]
	virtual MxFloat VTable0x5c() { return m_unk0x70; } // vtable+0x5c

	/// \brief [AI] Gets this actor's numeric ID, corresponding to a known enumeration/actor.
	virtual MxU8 GetActorId() { return m_actorId; } // vtable+0x60

	/// \brief [AI] Sets the actor's numeric ID.
	/// \param p_actorId The value to set as actor ID. [AI]
	virtual void SetActorId(MxU8 p_actorId) { m_actorId = p_actorId; } // vtable+0x64

	/// \brief [AI] Gets the static display name of an actor by ID.
	/// \details [AI] Used for actor name lookup by scripting and user interface.
	/// \param p_id Numeric actor ID as per the enum. [AI]
	/// \return Name of the actor, or "none" if not found. [AI]
	static const char* GetActorName(MxU8 p_id);

	/// \brief [AI] Mutes or unmutes the actor's current sound.
	/// \param p_muted True to mute/stop, false to enable (potentially resumes playback). [AI]
	void Mute(MxBool p_muted);

protected:
	MxFloat m_frequencyFactor; ///< [AI] The frequency/pitch scaling factor for the actor's sound (default 0 == normal).
	LegoCacheSound* m_sound;   ///< [AI] Pointer to a currently active sound instance played by the actor, if any.
	MxFloat m_unk0x70;         ///< [AI] Unknown float property, likely used for advanced audio/animation control. [AI_SUGGESTED_NAME: m_voicePitchModifier]
	MxU8 m_actorId;            ///< [AI] Unique identifier for this actor, corresponding to enum above.
};

#endif // LEGOACTOR_H