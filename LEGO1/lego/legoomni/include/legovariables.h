#ifndef LEGOVARIABLES_H
#define LEGOVARIABLES_H

#include "mxvariable.h"

/// @brief [AI] Global variable key for the jet vehicle's speed. Used for scripting and state management.
/// @details [AI] This key can be used to look up or mutate the current value representing the speed of the jet vehicle in the variable table.
extern const char* g_varJETSPEED;

/// @brief [AI] Global variable key for the jet vehicle's fuel amount. Used for scripting and state management.
/// @details [AI] This key represents the current fuel quantity for the jet vehicle.
extern const char* g_varJETFUEL;

/// @brief [AI] Global variable key for the dune vehicle's speed.
/// @details [AI] Used in variable table or scripts to look up or set the current speed for dune vehicles.
extern const char* g_varDUNESPEED;

/// @brief [AI] Global variable key for the dune vehicle's fuel.
/// @details [AI] This is used to control or query the dune vehicle's fuel within variable-driven game logic.
extern const char* g_varDUNEFUEL;

/// @brief [AI] Global variable key for the motorcycle's speed.
/// @details [AI] Used in scripting or variable tables.
extern const char* g_varMOTOSPEED;

/// @brief [AI] Global variable key for the motorcycle's fuel value.
/// @details [AI] Used for motorcycle energetics scripting/state.
extern const char* g_varMOTOFUEL;

/// @brief [AI] Global variable key for ambulance speed.
/// @details [AI] Used to control or inquire about the current speed for the ambulance vehicle.
extern const char* g_varAMBULSPEED;

/// @brief [AI] Global variable key for ambulance fuel.
/// @details [AI] Represents the fuel level for the ambulance.
extern const char* g_varAMBULFUEL;

/// @brief [AI] Global variable key for tow truck speed.
/// @details [AI] Used to store/retrieve the tow truck's current speed.
extern const char* g_varTOWSPEED;

/// @brief [AI] Global variable key for tow truck fuel.
/// @details [AI] Represents the tow truck's fuel variable key.
extern const char* g_varTOWFUEL;

/// @brief [AI] Global variable key for controlling 3D object (ROI) visibility.
/// @details [AI] Used to signal visibility operations for in-game objects. The value can be "SHOW <ROI_NAME>" or "HIDE <ROI_NAME>".
extern const char* g_varVISIBILITY;

/// @brief [AI] Global variable key for the camera location.
/// @details [AI] Used to drive or obtain the camera's position or orientation in the scene.
extern const char* g_varCAMERALOCATION;

/// @brief [AI] Global variable key for the cursor state.
/// @details [AI] Used to manipulate or query the cursor display and state during gameplay.
extern const char* g_varCURSOR;

/// @brief [AI] Global variable key representing the player character identity ("who am I").
/// @details [AI] Used to signal or query which in-game character is currently the active player.
extern const char* g_varWHOAMI;

/// @class VisibilityVariable
/// @brief [AI] Variable to trigger show/hide operations on in-game 3D objects (ROIs) by parsing visibility commands.
/// @details [AI] This variable parses commands in the format "SHOW <ROI_NAME>" or "HIDE <ROI_NAME>", finds the corresponding ROI, and sets its visibility.
/// Inherits from MxVariable. The variable key is automatically set to g_varVISIBILITY.
class VisibilityVariable : public MxVariable {
public:
	/// @brief [AI] Initializes the VisibilityVariable and sets its key to g_varVISIBILITY. [AI]
	VisibilityVariable() { m_key = g_varVISIBILITY; }

	/// @brief [AI] Sets the value of this variable and, if the value encodes a valid visibility instruction,
	/// parses and applies the show/hide operation to the target ROI. [AI]
	/// @param p_value The new value, in the format "SHOW <ROI_NAME>" or "HIDE <ROI_NAME>". [AI]
	void SetValue(const char* p_value) override; // vtable+0x04
};

/// @class CameraLocationVariable
/// @brief [AI] Variable for updating camera location and POV (field of view/frustum settings) for navigation and scene rendering.
/// @details [AI] Parses the value as a comma-separated string updating the camera's logical location and, optionally, the field-of-view (perspective).
/// Inherits from MxVariable. The variable key is set to g_varCAMERALOCATION.
class CameraLocationVariable : public MxVariable {
public:
	/// @brief [AI] Initializes the CameraLocationVariable and sets its key to g_varCAMERALOCATION. [AI]
	CameraLocationVariable() { m_key = g_varCAMERALOCATION; }

	/// @brief [AI] Sets the value of this variable, updating the navigation controller and 3D manager with camera coordinates/POV. [AI]
	/// @param p_value The new value as a comma-delimited string (location[,field_of_view]). [AI]
	void SetValue(const char* p_value) override; // vtable+0x04
};

/// @class CursorVariable
/// @brief [AI] Variable to represent game cursor (pointer) state. [AI]
/// @details [AI] Used for scripting or game logic changes to the onscreen cursor.
/// The variable key is set to g_varCURSOR.
/// Actual processing and usage are stub or to be implemented.
class CursorVariable : public MxVariable {
public:
	/// @brief [AI] Initializes the CursorVariable and sets its key to g_varCURSOR. [AI]
	CursorVariable() { m_key = g_varCURSOR; }

	/// @brief [AI] Sets the value of this variable—actual implementation is a stub. [AI]
	/// @param p_value The new value. [AI]
	void SetValue(const char* p_value) override; // vtable+0x04
};

/// @class WhoAmIVariable
/// @brief [AI] Variable representing the current player's character, allowing the game to switch the active actor accordingly. [AI]
/// @details [AI] Accepts the value as a character name ("Papa", "Mama", "Pepper", "Nick", or "Laura") and sets the current player actor in game state.
/// The key is set to g_varWHOAMI.
class WhoAmIVariable : public MxVariable {
public:
	/// @brief [AI] Initializes the WhoAmIVariable and sets its key to g_varWHOAMI. [AI]
	WhoAmIVariable() { m_key = g_varWHOAMI; }

	/// @brief [AI] Sets the current player actor in the game state based on the specified character. [AI]
	/// @param p_value The new value; must match a valid character ("Papa", "Mama", "Pepper", "Nick", or "Laura"). [AI]
	void SetValue(const char* p_value) override; // vtable+0x04
};

#endif // LEGOVARIABLES_H
