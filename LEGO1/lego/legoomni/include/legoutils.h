#ifndef LEGOUTILS_H
#define LEGOUTILS_H

#include "actionsfwd.h"
#include "decomp.h"
#include "extra.h"
#include "mxtypes.h"

#include <windows.h>

#define WM_ISLE_SETCURSOR 0x5400 ///< @brief [AI] Custom Windows message for setting the cursor in LEGO Island. Used with PostMessage. [AI]

/**
 * @brief [AI] Special stream ID indicating that the current stream is not valid. Used to check against invalid stream references. [AI]
 */
#define DS_NOT_A_STREAM -1

/**
 * @enum Cursor
 * @brief [AI] Enum representing cursor icons usable within the LEGO Island engine for custom cursor management. [AI]
 */
enum Cursor {
	e_cursorArrow = 0,   ///< @brief [AI] Standard arrow cursor. [AI]
	e_cursorBusy,        ///< @brief [AI] Busy or loading cursor (e.g., hourglass). [AI]
	e_cursorNo,          ///< @brief [AI] 'Not allowed' cursor. [AI]
	e_cursorUnused3,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused4,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused5,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused6,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused7,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused8,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused9,     ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorUnused10,    ///< @brief [AI] Reserved slot. Not used. [AI]
	e_cursorNone         ///< @brief [AI] No cursor (invisible or hidden). [AI]
};

class BoundingSphere; ///< @brief [AI] Represents a 3D sphere used for intersection and bounding calculations. [AI]
class MxAtomId; ///< @brief [AI] Unique identifier for resource or object instances, using case transformation and string lookup. [AI]
class LegoEntity; ///< @brief [AI] Represents an entity in the LEGO Island 3D world, potentially interactable. [AI]
class LegoAnimPresenter; ///< @brief [AI] Presenter for LEGO animation, used for camera and animation node manipulation. [AI]
class LegoNamedTexture; ///< @brief [AI] Texture with a name identifier for use in the LEGO rendering system. [AI]
class LegoPathActor; ///< @brief [AI] Actor in LEGO Island which can follow a path, often used for camera and NPCs. [AI]
class LegoROI; ///< @brief [AI] Renderable object instance, commonly used for picking and placement in the 3D world. [AI]
class LegoStorage; ///< @brief [AI] Abstracts file and memory storage for serialization and deserialization of LEGO data. [AI]
class LegoTreeNode; ///< @brief [AI] Node used in hierarchical scene graphs and animation trees. [AI]

extern MxAtomId* g_isleScript; ///< @brief [AI] Global script identifier for the main Isle game script resource. [AI]

/**
 * @brief [AI] Picks the LEGO entity root at the given screen coordinates. [AI]
 * @param p_x X screen coordinate. [AI]
 * @param p_y Y screen coordinate. [AI]
 * @return Pointer to LegoEntity at the location (or nullptr if none). [AI]
 */
LegoEntity* PickEntity(MxLong p_x, MxLong p_y);

/**
 * @brief [AI] Picks the ROI (Renderable Object Instance) at screen coordinates. [AI]
 * @param p_x X screen coordinate. [AI]
 * @param p_y Y screen coordinate. [AI]
 * @return Pointer to LegoROI at the location (or nullptr if none). [AI]
 */
LegoROI* PickROI(MxLong p_x, MxLong p_y);

/**
 * @brief [AI] Picks the root ROI at the given screen coordinates by traversing up the ROI parent tree. [AI]
 * @param p_x X screen coordinate. [AI]
 * @param p_y Y screen coordinate. [AI]
 * @return Pointer to the root LegoROI (or nullptr if none). [AI]
 */
LegoROI* PickRootROI(MxLong p_x, MxLong p_y);

/**
 * @brief [AI] Rotates the given ROI around the Y axis in world space. [AI]
 * @param p_roi ROI to rotate. [AI]
 * @param p_angle Angle in radians. [AI]
 */
void RotateY(LegoROI* p_roi, MxFloat p_angle);

/**
 * @brief [AI] Tests if two bounding spheres in the 3D world intersect. [AI]
 * @param p_sphere1 First bounding sphere for intersection. [AI]
 * @param p_sphere2 Second bounding sphere for intersection. [AI]
 */
MxBool SpheresIntersect(const BoundingSphere& p_sphere1, const BoundingSphere& p_sphere2);

/**
 * @brief [AI] Calculates a ray starting at a screen location and outputs its world origin and direction. [AI]
 * @param p_param1 Screen coordinates (x, y). [AI]
 * @param p_param2 Output world-space ray direction (length 3). [AI]
 * @param p_param3 Output world-space ray origin (length 3). [AI]
 * @return TRUE always. [AI]
 */
MxBool FUN_1003ded0(MxFloat p_param1[2], MxFloat p_param2[3], MxFloat p_param3[3]);

/**
 * @brief [AI] Projects a world-space point into normalized screen coordinates. [AI]
 * @param p_world Input world coordinates (length 3). [AI]
 * @param p_screen Output screen coordinates (length 4 for homogeneous coordinates). [AI]
 * @return TRUE always. [AI]
 */
MxBool TransformWorldToScreen(const MxFloat p_world[3], MxFloat p_screen[4]);

/**
 * @brief [AI] Recursively counts the number of nodes (including the root) in a tree hierarchy rooted at the specified LegoTreeNode. [AI]
 * @param p_node Root node to start counting from. [AI]
 * @return Number of tree nodes including root. [AI]
 */
MxS16 CountTotalTreeNodes(LegoTreeNode* p_node);

/**
 * @brief [AI] Retrieves the nth node in tree traversal order (preorder) from a LegoTreeNode root. [AI]
 * @param p_node Root node to start searching from. [AI]
 * @param p_index The 0-based index into the tree traversal. [AI]
 * @return The LegoTreeNode pointer if found, otherwise NULL. [AI]
 */
LegoTreeNode* GetTreeNode(LegoTreeNode* p_node, MxU32 p_index);

/**
 * @brief [AI] Repositions the camera and updates the view matrix using a LegoAnimPresenter's animation nodes named "CAM" and "TARGET". [AI]
 * @param p_presenter Animation presenter used to locate camera and target. [AI]
 */
void FUN_1003e050(LegoAnimPresenter* p_presenter);

/**
 * @brief [AI] Parses an action string to determine the corresponding action type. [AI]
 * @param Str Null-terminated string to evaluate. [AI]
 * @return Matching action type. [AI]
 */
Extra::ActionType MatchActionString(const char*);

/**
 * @brief [AI] Dispatches and triggers a game action on the given script or object. [AI]
 * @param p_actionId Type of action to invoke. [AI]
 * @param p_pAtom ID of the target script/entity. [AI]
 * @param p_streamId Associated stream ID for the action (if applicable). [AI]
 * @param p_sender Optional pointer to the sender entity (can be NULL). [AI]
 */
void InvokeAction(Extra::ActionType p_actionId, const MxAtomId& p_pAtom, MxS32 p_streamId, LegoEntity* p_sender);

/**
 * @brief [AI] Updates the current camera controller to the main ISLE camera specified in the global script. [AI]
 */
void SetCameraControllerFromIsle();

/**
 * @brief [AI] Converts HSV color (hue/saturation/value) to RGB (red/green/blue). [AI]
 * @param p_h Hue, float in [0,1]. [AI]
 * @param p_s Saturation, float in [0,1]. [AI]
 * @param p_v Value, float in [0,1]. [AI]
 * @param p_rOut Output pointer for red result. [AI]
 * @param p_bOut Output pointer for blue result. [AI]
 * @param p_gOut Output pointer for green result. [AI]
 */
void ConvertHSVToRGB(float p_h, float p_s, float p_v, float* p_rOut, float* p_bOut, float* p_gOut);

/**
 * @brief [AI] Initiates a camera animation for a specific path actor, or falls back to default animation triggers. [AI]
 * @param p_actor Path actor to play camera animation for. [AI]
 * @param p_unused Not used in logic (placeholder for extended parameters). [AI]
 * @param p_location Camera location index/ID. [AI]
 * @param p_bool Boolean flag, often controlling secondary behavior. [AI]
 */
void PlayCamAnim(LegoPathActor* p_actor, MxBool p_unused, MxU32 p_location, MxBool p_bool);

/**
 * @brief [AI] Updates sound listener position to follow the view ROI's transform. [AI]
 */
void FUN_1003eda0();

/**
 * @brief [AI] Removes an entity or presenter with specified AtomId and ID from the current world; triggers EndAction or deletes it. [AI]
 * @param p_atomId AtomId of the object to remove. [AI]
 * @param p_id Object identifier within the world. [AI]
 * @return TRUE if object was found and removed, FALSE otherwise. [AI]
 */
MxBool RemoveFromCurrentWorld(const MxAtomId& p_atomId, MxS32 p_id);

/**
 * @brief [AI] Enables or disables animation playback globally. Triggers resume and additional handler methods. [AI]
 * @param p_enable Enable/disable flag for animations. [AI]
 */
void EnableAnimations(MxBool p_enable);

/**
 * @brief [AI] Sets the in-game cursor to a specified type. [AI]
 * @param p_cursor Cursor enum value (e.g., arrow, busy, none). [AI]
 */
void SetAppCursor(Cursor p_cursor);

/**
 * @brief [AI] Determines if the current actor can exit their area, based on state/zone/vehicle. [AI]
 * @return TRUE if allowed to leave the area, FALSE otherwise. [AI]
 */
MxBool FUN_1003ef60();

/**
 * @brief [AI] Removes a game object referenced by atom/id from a specific world, handling presenters and EndActions. [AI]
 * @param p_entityAtom AtomId for the target object. [AI]
 * @param p_entityId ID for the target object. [AI]
 * @param p_worldAtom AtomId for the world containing the object. [AI]
 * @param p_worldEntityId ID for the world. [AI]
 * @return TRUE if removed, FALSE otherwise. [AI]
 */
MxBool RemoveFromWorld(MxAtomId& p_entityAtom, MxS32 p_entityId, MxAtomId& p_worldAtom, MxS32 p_worldEntityId);

/**
 * @brief [AI] Steps or resets the in-game light position; wraps and saves in global variables; updates lighting matrix. [AI]
 * @param p_increase Increments light position if positive; decrements otherwise. [AI]
 * @return Updated light position index. [AI]
 */
MxS32 UpdateLightPosition(MxS32 p_increase);

/**
 * @brief [AI] Sets the world space position and direction of the in-game directional light, based on a preset index. [AI]
 * @param p_index Lighting index (clamped to valid range). [AI]
 */
void SetLightPosition(MxS32 p_index);

/**
 * @brief [AI] Reads a named texture and its associated image data from storage. [AI]
 * @param p_storage Source storage for reading (disk or memory representation). [AI]
 * @return Pointer to allocated LegoNamedTexture, or NULL if failed. [AI]
 */
LegoNamedTexture* ReadNamedTexture(LegoStorage* p_storage);

/**
 * @brief [AI] Writes a default texture by name (and its image/palette) to storage for serialization. [AI]
 * @param p_storage Target storage for writing. [AI]
 * @param p_name Name of the texture/resource to write. [AI]
 */
void WriteDefaultTexture(LegoStorage* p_storage, const char* p_name);

/**
 * @brief [AI] Writes a LegoNamedTexture and its associated image to storage. [AI]
 * @param p_storage Target storage for writing. [AI]
 * @param p_namedTexture Pointer to the LegoNamedTexture to serialize. [AI]
 */
void WriteNamedTexture(LegoStorage* p_storage, LegoNamedTexture* p_namedTexture);

/**
 * @brief [AI] Applies the image bits of a named texture to its associated texture info container entry. [AI]
 * @param p_namedTexture Target named texture whose data will be uploaded. [AI]
 */
void FUN_1003f930(LegoNamedTexture* p_namedTexture);

/**
 * @brief [AI] Parses a string for entity existence and enables/disables it accordingly. [AI]
 * @param p_enable Enable or disable the entity. [AI]
 * @param p_filename Entity resource filename to search. [AI]
 * @param p_entityId Target entity identifier within the world. [AI]
 * @return TRUE if entity was found and enabled/disabled, otherwise FALSE. [AI]
 */
MxBool CheckIfEntityExists(MxBool p_enable, const char* p_filename, MxS32 p_entityId);

/**
 * @brief [AI] Sends a notification to the specified entity in all known worlds. [AI]
 * @param p_filename Entity resource filename. [AI]
 * @param p_entityId ID of the target entity. [AI]
 * @param p_sender Sender entity reference, may be NULL. [AI]
 */
void NotifyEntity(const char* p_filename, MxS32 p_entityId, LegoEntity* p_sender);

/**
 * @brief [AI] Helper to invoke a 'start' action for an Isle script object by its script ID. [AI]
 * @param p_objectId IsleScript script object identifier. [AI]
 */
inline void StartIsleAction(IsleScript::Script p_objectId)
{
	if (p_objectId != (IsleScript::Script) -1) {
		InvokeAction(Extra::e_start, *g_isleScript, p_objectId, NULL);
	}
}

// SYNTHETIC: LEGO1 0x10034b40
// LegoTexture::`scalar deleting destructor'

#endif // LEGOUTILS_H
