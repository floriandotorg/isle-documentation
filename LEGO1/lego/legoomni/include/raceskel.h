#ifndef RACESKEL_H
#define RACESKEL_H

#include "legoanimactor.h"

// VTABLE: LEGO1 0x100d93f8 LegoPathActor
// VTABLE: LEGO1 0x100d94c8 LegoAnimActor
// VTABLE: BETA10 0x101bf9d0 LegoPathActor
// VTABLE: BETA10 0x101bfac0 LegoAnimActor
// SIZE 0x178

/**
 * @brief [AI] Specialized skeleton animation actor for LEGO Island car racing sequences.
 * 
 * Inherits from LegoAnimActor and manages the animated skeleton used in
 * car races, synchronizing animation state and position for the race system.
 * During ParseAction, it registers itself as the CarRace skeleton and applies a significant
 * scale-up to its ROI bounding sphere.
 * 
 * @details [AI] This class is a specific animation actor for handling the racing skeleton (driver/figure)
 * used in LEGO Island's Car Race mini-game. It connects its animation progress to the race logic
 * and ensures proper world-space placement of the skeleton model.
 */
class RaceSkel : public LegoAnimActor {
public:
	/**
	 * @brief [AI] Constructs a RaceSkel instance with animation state reset.
	 */
	RaceSkel();

	/**
	 * @brief [AI] Destructor for RaceSkel, cleans up resources.
	 */
	~RaceSkel() override;

	/**
	 * @brief [AI] Parses a string command to setup the skeleton for the car race, and modifies ROI bounding sphere.
	 * 
	 * Sets itself as the active skeleton for the CarRace world, then rescales the bounding
	 * sphere of its ROI for in-game collision or culling.
	 * 
	 * @param p_extra [AI] String containing action parameters or extra commands for initialization.
	 */
	void ParseAction(char* p_extra) override; // vtable+0x20

	/**
	 * @brief [AI] Apply race-specific position/orientation adjustment and updates animation position.
	 * 
	 * Sets the world-transform translation to a specific location (hardcoded), then updates
	 * internal m_animPosition to match p_und (likely animation progress/time), and calls the
	 * base implementation (which may advance the actual animation data).
	 * 
	 * @param p_und [AI] New animation position (progress/timestamp).
	 * @param p_transform [AI] Transform matrix to be overwritten with new skeleton position.
	 * @return [AI] Result from the base implementation, typically successful or error status.
	 */
	MxResult FUN_1001c360(float p_und, Matrix4& p_transform) override;

	/**
	 * @brief [AI] Assigns the skeleton's position in 3D space for the car race sequence.
	 *
	 * Sets the provided vector to the fixed race skeleton coordinates; used to position the skeleton.
	 * 
	 * @param p_vec [AI] Output vector set to the skeleton's world position.
	 */
	virtual void FUN_10071c80(Vector3& p_vec);

	/**
	 * @brief [AI] Retrieves the current animation position and its duration.
	 * 
	 * @details [AI] Outputs the current animation state: the exact position in the animation and its total duration.
	 * 
	 * @param p_outCurAnimPosition [AI] (out) Current animation position (progress/time/frame).
	 * @param p_outCurAnimDuration [AI] (out) Duration of the current animation being played.
	 */
	void GetCurrentAnimData(float* p_outCurAnimPosition, float* p_outCurAnimDuration);

	// SYNTHETIC: LEGO1 0x10071cf0
	// RaceSkel::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Current playback position in the skeleton's animation, used to synchronize with race events.
	 */
	float m_animPosition; // 0x1c
};

// GLOBAL: LEGO1 0x100d93f0
// RaceSkel::`vbtable'

#endif // RACESKEL_H
