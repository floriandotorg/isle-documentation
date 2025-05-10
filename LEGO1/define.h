#ifndef DEFINE_H
#define DEFINE_H

#include "mxtypes.h"

/**
 * @brief [AI] Delimiter tokens for parsing extra parameters in scripts or command strings. 
 * @details [AI] Used to split key-value pairs or other command fragments for object and action parsing in the game.
 */
extern const char* g_parseExtraTokens;

/**
 * @brief [AI] Symbolic name used to reference a "WORLD" entity or property in scripts and object definitions.
 */
extern const char* g_strWORLD;

/**
 * @brief [AI] Symbolic string used to reference sound effects or sound object properties in the scripting system.
 */
extern const char* g_strSOUND;

/**
 * @brief [AI] Used when referencing or distinguishing object instances in script actions or variable assignments.
 */
extern const char* g_strOBJECT;

/**
 * @brief [AI] Keyword used for tagging animation properties, types, or script commands.
 */
extern const char* g_strANIMATION;

/**
 * @brief [AI] Used as the key for defining an action or command block in game scripts.
 */
extern const char* g_strACTION;

/**
 * @brief [AI] Used when specifying visibility toggles or changes for objects/entities in scripting.
 */
extern const char* g_strVISIBILITY;

/**
 * @brief [AI] Used to read or set speed values for entities/animations via scripts or data files.
 */
extern const char* g_strSPEED;

/**
 * @brief [AI] Command for attaching or associating the camera with an entity via script instructions.
 */
extern const char* g_strATTACH_CAMERA;

/**
 * @brief [AI] Keyword for muting sound or disabling audio for an entity or context.
 */
extern const char* g_strMUTE;

/**
 * @brief [AI] Used to reference the animation manager identifier during entity or animation handling.
 */
extern const char* g_strANIMMAN_ID;

/**
 * @brief [AI] String indicating the data for fetching properties or configuration from a parent object.
 */
extern const char* g_strFROM_PARENT;

/**
 * @brief [AI] Script keyword to hide an object upon completion or stoppage of an event or animation.
 */
extern const char* g_strHIDE_ON_STOP;

/**
 * @brief [AI] Indicates that a command, script, or resource must complete successfully for script flow.
 */
extern const char* g_strMUST_SUCCEED;

/**
 * @brief [AI] Used to specify substitutions of names or resources in script or object instantiation.
 */
extern const char* g_strSUBST;

/**
 * @brief [AI] Name used to reference identifiers for possible event triggers or references to triggers sources.
 */
extern const char* g_strTRIGGERS_SOURCE;

/**
 * @brief [AI] Used to denote a script operation/keyword relating to the PTATCAM feature or module. 
 * @details [AI] The specific game system or camera feature named by PTATCAM is not further documented here.
 */
extern const char* g_strPTATCAM;

/**
 * @brief [AI] Used to toggle boolean states for properties or actions in scripting/config files.
 */
extern const char* g_strTOGGLE;

/**
 * @brief [AI] Script or configuration keyword for defining or referencing a map entity.
 */
extern const char* g_strMAP;

/**
 * @brief [AI] Used for identifying or interacting with grid-based maps or layouts.
 */
extern const char* g_strGRID;

/**
 * @brief [AI] String to specify styles, possibly for GUI, animation, or entity appearance.
 */
extern const char* g_strSTYLE;

/**
 * @brief [AI] Used to denote the type or class of an object/action in scripts or data files.
 */
extern const char* g_strTYPE;

/**
 * @brief [AI] Used when referencing objects laid out or animated from left to right.
 */
extern const char* g_strLEFT_TO_RIGHT;

/**
 * @brief [AI] Used when referencing objects laid out or animated from right to left.
 */
extern const char* g_strRIGHT_TO_LEFT;

/**
 * @brief [AI] Used when referencing objects laid out or animated from bottom to top.
 */
extern const char* g_strBOTTOM_TO_TOP;

/**
 * @brief [AI] Used when referencing objects laid out or animated from top to bottom.
 */
extern const char* g_strTOP_TO_BOTTOM;

/**
 * @brief [AI] Identifier string for special "filler" entity or material indices in definition files.
 */
extern const char* g_strFILLER_INDEX;

/**
 * @brief [AI] Used for referencing variable assignment or lookup in script commands or tables.
 */
extern const char* g_strVARIABLE;

/**
 * @brief [AI] Used to identify comparison operations, likely for variable or trigger checks in scripts.
 */
extern const char* g_strCOMP;

/**
 * @brief [AI] Denotes a BMP resource that acts as a map; used for interpreting image assets as collision/level maps.
 */
extern const char* g_strBMP_ISMAP;

/**
 * @brief [AI] Used to signal that an object or feature should be automatically created/initialized on load.
 */
extern const char* g_strAUTO_CREATE;

/**
 * @brief [AI] Used to indicate an entry should be created for a resource in a data block (DB) at load time.
 */
extern const char* g_strDB_CREATE;

/**
 * @brief [AI] Script key for allowing or restricting player/entity navigation in a context.
 */
extern const char* g_strPERMIT_NAVIGATE;

/**
 * @brief [AI] Name of a path for moving actors, objects or camera in the world scripting system.
 */
extern const char* g_strPATH;

/**
 * @brief [AI] Denotes the collision box; used to specify bounding volume for collision in the world/entities.
 */
extern const char* g_strCOLLIDEBOX;

/**
 * @brief [AI] Key for specifying or triggering sounds to play when an actor is hit.
 */
extern const char* g_strHIT_ACTOR_SOUND;

#endif // DEFINE_H