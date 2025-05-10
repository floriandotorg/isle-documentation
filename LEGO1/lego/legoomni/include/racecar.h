#ifndef RACECAR_H
#define RACECAR_H

#include "decomp.h"
#include "islepathactor.h"

// VTABLE: LEGO1 0x100d6918
// VTABLE: BETA10 0x101bf878
// SIZE 0x164

/**
 * @brief [AI] Represents the drivable race car entity in the LEGO Island world.
 * 
 * Inherits from IslePathActor, providing specialized logic for interaction and
 * behavior as a race car, such as unique handling in race areas and transition
 * management when clicked.
 * 
 * @details [AI] RaceCar extends IslePathActor, representing the user/drivable car used
 * in the racing mini-game of LEGO Island. It registers itself in the control manager,
 * adds itself to the world upon creation, and handles input to trigger transitions
 * into the car race area. The class leverages IslePathActor's path-following and 
 * entity logic, but introduces custom parameters such as increased maximum speed.
 */
class RaceCar : public IslePathActor {
public:
	/**
	 * @brief [AI] Constructs a RaceCar and initializes its properties, such as velocity.
	 */
	RaceCar();

	/**
	 * @brief [AI] Destructor which unregisters the RaceCar from the control manager and performs cleanup.
	 */
	~RaceCar() override; // vtable+0x00

	/**
	 * @brief [AI] Returns the class name, "RaceCar".
	 * @return [AI] Pointer to the static string "RaceCar".
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f03e0
		return "RaceCar";
	}

	/**
	 * @brief [AI] Checks if the object is of or derives from the class name provided.
	 * @param p_name The queried class name. [AI]
	 * @retval TRUE if class name matches or is a parent class. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, RaceCar::ClassName()) || IslePathActor::IsA(p_name);
	}

	/**
	 * @brief [AI] Initializes the RaceCar from an MxDSAction.
	 * 
	 * Registers itself with the current world and the global control manager.
	 * 
	 * @param p_dsAction The action describing initialization/deserialization state. [AI]
	 * @retval MxResult Status of creation.
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief [AI] Handles click interaction with the RaceCar.
	 * 
	 * Triggers the game transition into the car race mini-game area
	 * if the world is in the proper state.
	 * 
	 * @retval 1 Always returns 1 on handled event. [AI]
	 */
	MxLong HandleClick() override;                    // vtable+0xcc

	// SYNTHETIC: LEGO1 0x10028400
	// RaceCar::`scalar deleting destructor'

private:
	// TODO: RaceCar fields
	/**
	 * @brief [AI] Unknown data member (4 bytes), possibly reserved for tracking state or flags for the RaceCar.
	 */
	undefined m_unk0x160[4]; ///< [AI] Unknown purpose, padding or future use.
};

#endif // RACECAR_H
