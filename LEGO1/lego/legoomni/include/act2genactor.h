#ifndef ACT2GENACTOR_H
#define ACT2GENACTOR_H

#include "legopathactor.h"

// VTABLE: LEGO1 0x100d4ed8
// SIZE 0x154

/**
 * @brief [AI] An actor that extends LegoPathActor with special collision logic for "Act2Gen" scene logic. Plays a sound when colliding with the actor named "pepper", but not more than once per second.
 * @details [AI] This class overrides the collision logic of the path actor to provide specific reactions (such as playing sounds) when colliding with a unique actor ("pepper"). It maintains a static timer to prevent repeated sound playback within a one-second interval.
 */
class Act2GenActor : public LegoPathActor {
	/**
	 * @brief [AI] Handles collision events with other path actors in the scene.
	 * @details [AI] If the other actor's ROI name is "pepper", plays a sound via the cache sound manager, but only if more than one second elapsed since the last such event (to throttle sound effects). Updates the static timer to track last collision. Returns SUCCESS in any case.
	 * @param p_actor The other LegoPathActor that is colliding with this actor [AI]
	 * @param [AI] Unknown boolean parameter, not used in this logic.
	 * @return [AI] Always returns SUCCESS.
	 */
	MxResult HitActor(LegoPathActor* p_actor, MxBool) override; // vtable+0x94

	// SYNTHETIC: LEGO1 0x1000f5a0
	// Act2GenActor::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Timestamp of the last time the "pepper" actor collision occurred to rate-limit reactions. Static for global tracking across all instances.
	 */
	static MxLong g_lastHitActorTime;
};

#endif // ACT2GENACTOR_H