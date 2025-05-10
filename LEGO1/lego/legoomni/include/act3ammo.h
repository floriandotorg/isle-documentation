#ifndef ACT3AMMO_H
#define ACT3AMMO_H

#include "legopathactor.h"
#include "mxgeometry/mxgeometry3d.h"

class Act3;

// VTABLE: LEGO1 0x100d8460
// SIZE 0x1a0
/**
 * @brief Represents an ammo object (pizza or donut) used in Act 3 gameplay sequence. Handles its state, trajectory, animation, and removal logic. [AI]
 * @details Act3Ammo manages special ammo (pizzas and donuts) fired by the player or AI in the Act 3 scenario. It can represent pizza or donut projectiles with different properties and behaviors. The class handles creation, animation (including trajectory calculations using quadratic Bezier curves), state changes (valid, bit flags, shark food status), and logic for interacting with the scene and other actors, including collision, removal, and sound effects. [AI]
 */
class Act3Ammo : public LegoPathActor {
public:
	/// @brief [AI] Internal ammo flags identifying type and various states. [AI]
	enum {
		c_pizza = 0x01,     ///< @brief [AI] The ammo is a pizza projectile. [AI]
		c_donut = 0x02,     ///< @brief [AI] The ammo is a donut projectile. [AI]
		c_valid = 0x04,     ///< @brief [AI] The ammo is in a valid/active state and available for interaction. [AI]
		c_bit4 = 0x08,      ///< @brief [AI] Internal usage (e.g. special event or collision, see SetBit4). [AI]
		c_sharkFood = 0x10  ///< @brief [AI] Marks this ammo as "shark food" (special event/consumed). [AI]
	};

	/**
	 * @brief Constructs a new Act3Ammo object. [AI]
	 */
	Act3Ammo();

	/**
	 * @brief Destructor. Cleans up and calls Destroy. [AI]
	 */
	~Act3Ammo() override;

	/**
	 * @brief Completely removes this ammo object from all managers. [AI]
	 * @param p_fromDestructor If called from destructor (must be TRUE or asserts). [AI]
	 */
	void Destroy(MxBool p_fromDestructor) override; // vtable+0x1c

	/**
	 * @brief Updates position, animation, and handles collision or end-of-trajectory logic for this ammo. [AI]
	 * @param p_time Current timer value, used for interpolation and timing events. [AI]
	 */
	void Animate(float p_time) override;            // vtable+0x70

	/**
	 * @brief Returns true if the ammo is valid (active in game/world). [AI]
	 */
	MxU32 IsValid() { return m_ammoFlag & c_valid; }

	/**
	 * @brief Returns the pointer to the second control point of the quadratic trajectory equation. [AI]
	 * @return Mx3DPointFloat* Pointer to m_eq (control points for motion curve). [AI]
	 */
	Mx3DPointFloat* GetUnknown0x160() { return m_eq; }

	/**
	 * @brief Returns pointer to an internal parameter used in trajectory and animation calculations. [AI]
	 * @return MxFloat* Pointer to m_unk0x19c. [AI]
	 */
	MxFloat* GetUnknown0x19c() { return &m_unk0x19c; }

	/**
	 * @brief Set or clear the valid flag for the object, making it active or inactive in the world. [AI]
	 * @param p_valid TRUE to set as valid/active, FALSE for inactive. [AI]
	 */
	void SetValid(MxBool p_valid)
	{
		if (p_valid) {
			m_ammoFlag |= c_valid;
		}
		else {
			m_ammoFlag &= ~c_valid;
		}
	}

	/**
	 * @brief Returns true if the ammo is a pizza projectile. [AI]
	 */
	MxU32 IsPizza() { return m_ammoFlag & c_pizza; }

	/**
	 * @brief Returns true if the ammo is a donut projectile. [AI]
	 */
	MxU32 IsDonut() { return m_ammoFlag & c_donut; }

	/**
	 * @brief Set or clear the bit4 flag, used internally for special state/behavior (e.g. was fired into shark food event). [AI]
	 * @param p_bit4 TRUE to set, FALSE to clear. [AI]
	 */
	void SetBit4(MxBool p_bit4)
	{
		if (p_bit4) {
			m_ammoFlag |= c_bit4;
		}
		else {
			m_ammoFlag &= ~c_bit4;
		}
	}

	/**
	 * @brief Returns true if the internal bit4 flag is set (special usage, e.g. collision). [AI]
	 */
	MxU32 IsBit4() { return m_ammoFlag & c_bit4; }

	/**
	 * @brief Sets the "shark food" flag if this ammo should become food for a shark. [AI]
	 * @param p_sharkFood TRUE to enable, FALSE to disable. [AI]
	 */
	void SetSharkFood(MxBool p_sharkFood)
	{
		if (p_sharkFood) {
			m_ammoFlag |= c_sharkFood;
		}
		else {
			m_ammoFlag &= ~c_sharkFood;
		}
	}

	/**
	 * @brief Returns true if the ammo became "shark food". [AI]
	 */
	MxU32 IsSharkFood() { return m_ammoFlag & c_sharkFood; }

	/**
	 * @brief Returns a time/duration parameter used in animation transitions. [AI]
	 */
	MxFloat GetUnknown0x158() { return m_unk0x158; }

	/**
	 * @brief Sets a time/duration parameter used for state transitions after collision. [AI]
	 * @param p_unk0x158 New value for unknown0x158. [AI]
	 */
	void SetUnknown0x158(MxFloat p_unk0x158) { m_unk0x158 = p_unk0x158; }

	/**
	 * @brief Removes this ammo instance from the world, cleans up path controller/boundary and notifies managers. [AI]
	 * @details Used when ammo is consumed, goes out of bounds, or is otherwise removed; disables, unlinks, and sets flag to invalid. [AI]
	 */
	MxResult Remove();

	/**
	 * @brief Creates an ammo (pizza or donut), initializes its ROI, bounding volumes, and enables it in the world. [AI]
	 * @param p_world Pointer to the owning Act3 game controller/world. [AI]
	 * @param p_isPizza TRUE for pizza, FALSE for donut. [AI]
	 * @param p_index Index for naming/id purposes. [AI]
	 * @return Success status of creation. [AI]
	 */
	MxResult Create(Act3* p_world, MxU32 p_isPizza, MxS32 p_index);

	/**
	 * @brief Sets up trajectory control points for the projectile, calculating a quadratic curve based on origin/direction/up. [AI]
	 * @param p_srcLoc Source location (initial position). [AI]
	 * @param p_srcDir Direction vector. [AI]
	 * @param p_srcUp Up vector. [AI]
	 * @return Success or failure of setup. [AI]
	 */
	MxResult FUN_10053b40(const Vector3& p_srcLoc, const Vector3& p_srcDir, const Vector3& p_srcUp);

	/**
	 * @brief Initializes the path controller/boundary and sets up animation and sound when ammo is fired. [AI]
	 * @param p_p Path controller (movement controller). [AI]
	 * @param p_boundary Path boundary for collision/ownership. [AI]
	 * @param p_unk0x19c Animation parameter for curve duration/scaling. [AI]
	 * @return Result of operation. [AI]
	 */
	MxResult FUN_10053cb0(LegoPathController* p_p, LegoPathBoundary* p_boundary, MxFloat p_unk0x19c);

	/**
	 * @brief Variant of firing logic (uses only controller and param, also sets bit4). [AI]
	 * @param p_p Path controller. [AI]
	 * @param p_unk0x19c Animation parameter. [AI]
	 * @return Result of operation. [AI]
	 */
	MxResult FUN_10053d30(LegoPathController* p_p, MxFloat p_unk0x19c);

	// SYNTHETIC: LEGO1 0x10053880
	// Act3Ammo::`scalar deleting destructor'

private:
	/**
	 * @brief Performs the core Bezier/curve transformation at a given parametric time, updating transformation matrix for ammo. [AI]
	 * @details Used internally by Animate() to interpolate position and orientation along the defined trajectory curve. [AI]
	 * @param p_param1 Parametric value (progress along trajectory, 0...1). [AI]
	 * @param p_param2 Output transformation matrix, updated to new position/orientation. [AI]
	 * @return SUCCESS or FAILURE if math error occurs. [AI]
	 */
	MxResult FUN_10053db0(float p_param1, const Matrix4& p_param2);

	/**
	 * @brief Global vertical offset vector used for animating ammo when it finishes its animation. [AI]
	 */
	static Mx3DPointFloat g_unk0x10104f08;

	/**
	 * @brief Bit flags tracking ammo type and state (pizza, donut, valid, sharkFood, bit4, etc.). [AI]
	 */
	MxU16 m_ammoFlag;       // 0x154

	/**
	 * @brief Time/duration parameter used for special animation state transitions (e.g., post-collision delay). [AI]
	 */
	MxFloat m_unk0x158;     // 0x158

	/**
	 * @brief Owning game context or world this ammo belongs to. [AI]
	 */
	Act3* m_world;          // 0x15c

	/**
	 * @brief Control points for ammo's quadratic trajectory (Bezier): [0]: curve coeffs, [1]: direction/up, [2]: initial pos. [AI]
	 */
	Mx3DPointFloat m_eq[3]; // 0x160

	/**
	 * @brief Curve timing parameter, used for animating progression along the ammo's flight path. [AI]
	 */
	MxFloat m_unk0x19c;     // 0x19c
};

#endif // ACT3AMMO_H
