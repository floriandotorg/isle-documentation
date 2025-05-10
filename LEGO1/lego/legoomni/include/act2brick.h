#ifndef ACT2BRICK_H
#define ACT2BRICK_H

#include "legopathactor.h"

/// \class Act2Brick
/// \brief [AI] Represents a special 'brick' object in the LEGO Island "Act 2" sequence, derived from LegoPathActor.
/// [AI] Act2Brick provides methods to create, remove, and manage a special moving LEGO brick actor within scripted sequences.
/// [AI] Handles animation, sound playback, and interactions (such as being hit by Pepper), as well as state management using the tickle system integrated with the TickleManager.
/// [AI] It features behaviors such as moving along a spline when triggered, custom bounding initialization based on the brick type, whistle sound management, and custom notification for click events.
/// \details [AI] Usage of the class includes invoking Create with an index to instantiate and register it in the world, Remove to extract it, and specific helper methods for motion (FUN_1007a670), whistle sound handling, and muting.
class Act2Brick : public LegoPathActor {
public:
	/// \brief [AI] Constructs an Act2Brick. Initializes internal state, including whistle sound and tracking state flags.
	Act2Brick();

	/// \brief [AI] Destructor. Unregisters from the tickle manager and clears up resources.
	~Act2Brick() override; // vtable+0x00

	/// \brief [AI] Handles notifications. Reacts to click events by hiding the object, stopping the whistle sound, and sending a notification back to the world.
	/// \param p_param [AI] Notification parameter containing information about the event.
	/// \return [AI] Returns 1 when handled, asserts (crashes) otherwise. Used to communicate to the notification manager.
	MxLong Notify(MxParam& p_param) override; // vtable+0x04

	/// \brief [AI] Called periodically when registered with the TickleManager to animate the movement and state change of the brick actor.
	/// \return [AI] Returns SUCCESS after updating position or finalizing motion.
	MxResult Tickle() override;               // vtable+0x08

	/// \brief [AI] Returns the class name of this object ("Act2Brick").
	/// \return [AI] Literal string representing the class type.
	const char* ClassName() const override // vtable+0x0c
	{
		return "Act2Brick";
	}

	/// \brief [AI] Checks if the current object is of type Act2Brick or any of its parent classes.
	/// \param p_name [AI] String to compare against the class name.
	/// \return [AI] True if p_name matches this class or any parent up to LegoEntity.
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, Act2Brick::ClassName()) || LegoEntity::IsA(p_name);
	}

	/// \brief [AI] Called when another actor (typically Pepper) intersects or "hits" this brick. Plays a hit sound only if hit by Pepper and a delay condition is met.
	/// \param p_actor [AI] The actor that has collided or interacted.
	/// \param [AI] Unused/Misc bool parameter.
	/// \return [AI] Returns SUCCESS after sound logic is handled.
	MxResult HitActor(LegoPathActor* p_actor, MxBool) override; // vtable+0x94

	// SYNTHETIC: LEGO1 0x1007a450
	// Act2Brick::`scalar deleting destructor'

	/// \brief [AI] Instantiates and initializes the brick actor in the world with a specified index/type, selecting the proper LOD and initializing bounding sphere/ROI.
	/// \param p_index [AI] Index specifying which brick variation/type to use (corresponds to g_lodNames).
	/// \return [AI] SUCCESS on successful creation and registration; FAILURE if an ROI already exists for this actor.
	MxResult Create(MxS32 p_index);

	/// \brief [AI] Removes this brick from the world, releases associated resources, and notifies the character manager.
	void Remove();

	/// \brief [AI] Starts the brick motion and animation parameters, registers the object for tickling and places the actor in the world and boundary.
	/// \param p_param1 [AI] Matrix of the starting transform (source matrix).
	/// \param p_param2 [AI] Matrix of the destination transform (target matrix).
	/// \param p_boundary [AI] The path boundary which will manage this actor's motion and interactions.
	void FUN_1007a670(MxMatrix& p_param1, MxMatrix& p_param2, LegoPathBoundary* p_boundary);

	/// \brief [AI] Begins playback of the looping whistle sound associated with this brick, if not already playing.
	void PlayWhistleSound();

	/// \brief [AI] Stops the playback of the whistle sound if it is currently playing.
	void StopWhistleSound();

	/// \brief [AI] Mutes or unmutes the whistle sound according to the argument given.
	/// \param p_muted [AI] True to mute, false to unmute.
	void Mute(MxBool p_muted);

private:
	/// \brief [AI] List of LOD (Level of Detail) names used to instantiate variations of the brick actor.
	static const LegoChar* g_lodNames[];

	/// \brief [AI] Last absolute (Timer-based) timestamp a hit sound was played (for cooldown logic).
	static MxLong g_lastHitActorTime;

	/// \brief [AI] Handle/pointer to the currently active whistle sound, if any.
	LegoCacheSound* m_whistleSound; // 0x154

	/// \brief [AI] Unknown/reserved memory. Could be used for alignment, padding, or reserved state.
	undefined m_unk0x158[0x0c];     // 0x158

	/// \brief [AI] State variable. Used to manage internal transitions: (0 = inactive, 1 = spawned, 2 = animating, 3 = finished moving). [AI_SUGGESTED_NAME: m_brickState]
	undefined4 m_unk0x164;          // 0x164

	/// \brief [AI] Stores the vector position at the end of the motion/animation sequence. Used as motion target.
	Mx3DPointFloat m_unk0x168;      // 0x168

	/// \brief [AI] Stores the initial/world translation before animation/motion is started.
	Mx3DPointFloat m_unk0x17c;      // 0x17c

	/// \brief [AI] Tickle step/frame counter used for movement/interpolation sequence (incremented by Tickle).
	MxS32 m_unk0x190;               // 0x190
};

#endif // ACT2BRICK_H
