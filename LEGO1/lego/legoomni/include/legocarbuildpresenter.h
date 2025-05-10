#ifndef LEGOCARBUILDPRESENTER_H
#define LEGOCARBUILDPRESENTER_H

#include "anim/legoanim.h"
#include "legoanimpresenter.h"

// VTABLE: LEGO1 0x100d99e0
// VTABLE: BETA10 0x101bb988
// SIZE 0x150

/**
 * @brief [AI] Handles the logic and animation presentation for the LEGO Island car-building activity,
 * providing the main interface for coordinating the step-wise assembly of cars using animated 3D parts. 
 * Manages the state of placed parts, handles morph and rotation keys, updates visibility, and syncs the 
 * camera based on the animation and 3D world.
 * @details [AI]
 * Inherits from LegoAnimPresenter and implements custom logic for car-building animations, including managing 
 * a sequence of parts, their placement state, morphological transformations, and animated assembly. It bridges
 * the game logic (placed part count, object ids, step timing) and the interactive 3D world/camera for the activity.
 * 
 * Responsibilities:
 *  - Tracks the main "platform", parts, and their sequence
 *  - Blinks the next part to place, morphs mesh nodes on placement
 *  - Swaps data/nodes in response to player action during assembly
 *  - Adjusts camera based on scene nodes ("CAM..." etc)
 *  - Serializes/deserializes assembly state for save/load
 * 
 * Known main uses are in the "car build" game room sequence.
 */
class LegoCarBuildAnimPresenter : public LegoAnimPresenter {
public:
	enum {
		c_bit1 = 0x01 ///< [AI] Internal bitmask used for blinking animation state and timers.
	};

	/**
	 * @brief [AI] Represents a single entry in the car assembly sequence ("part list"), 
	 * providing mapping between display name, internal "wired" 3D representation, and 
	 * an object id used to identify the animated node in the 3D scene.
	 * @details [AI]
	 * m_name is typically the logical (player-facing) name of the part.
	 * m_wiredName is the name as used in 3D scene graph ("wired" mesh representation).
	 */
	struct UnknownListEntry {
		/**
		 * @brief [AI] Initializes the entry with default/null values.
		 */
		UnknownListEntry()
		{
			m_name = NULL;
			m_wiredName = NULL;
			m_objectId = 0;
		}

		LegoChar* m_name;      ///< [AI] Player-facing name or identifier for the part. 
		LegoChar* m_wiredName; ///< [AI] Internal/scene-graph name for the 3D mesh node.
		MxS16 m_objectId;      ///< [AI] Internal object id (likely 3D node id or mapping for placement).
	};

	/**
	 * @brief [AI] Constructs and initializes the presenter, sets up default assembly state, part list, and other fields.
	 */
	LegoCarBuildAnimPresenter();

	/**
	 * @brief [AI] Destroys the presenter, deletes all allocated part information, strings, and detaches nodes from the 3D scene.
	 * @details [AI] Implements deep cleanup of m_parts and associated dynamically allocated strings, 
	 * and also cleans up auxiliary animation objects.
	 */
	~LegoCarBuildAnimPresenter() override; // vtable+0x00

	/**
	 * @brief [AI] Returns the string class name used by the presenter dispatch mechanism.
	 * @details [AI] Used for runtime class recognition and deserialization.
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] No-op for car build (repeats do not trigger anything).
	 */
	void RepeatingTickle() override {} // vtable+0x24

	/**
	 * @brief [AI] Gets the runtime class name; used for dynamic type checks.
	 * @return [AI] Static string "LegoCarBuildAnimPresenter".
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Returns TRUE if this object is of, or inherits from, the supplied type name.
	 * @param p_name String name of type to check. [AI]
	 * @details [AI] Supports run-time type identification for presenter scripting/subsystem.
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] "Ready" tickle for car-building: initializes main entity pointer, updates placed part count, 
	 * swaps to composite presentation if found. Fallbacks for non-car-present rooms.
	 * @details [AI] Also sets up internal state to progress to next assembly phase.
	 */
	void ReadyTickle() override;     // vtable+0x18

	/**
	 * @brief [AI] Handles streaming phase:
	 *   - Sets up m_mainSourceId based on current action/scene.
	 *   - Prepares morph/visibility for each car part node and synchronizes camera according to the nodes found ("CAM...").
	 *   - Blinks new parts, sets up camera transform, and triggers 3D viewpoint change.
	 * @details [AI] Called once before continuous animation ticks to set up the scene and presenter state.
	 */
	void StreamingTickle() override; // vtable+0x20

	/**
	 * @brief [AI] Ends the current build action safely, stops blinking and unlocks critical section.
	 */
	void EndAction() override;       // vtable+0x40

	/**
	 * @brief [AI] Called once per displayed animation frame. 
	 * Handles car assembly step advancements and blinking of the next part to be placed; updates the 3D mesh state if needed.
	 * @details [AI] Main place where car-building animation is stepped forward each tick.
	 */
	void PutFrame() override;        // vtable+0x6c

	/**
	 * @brief [AI] Serializes or deserializes the assembly state of the car build.
	 * @param p_storage Storage object (file or memory). [AI]
	 * @return [AI] Returns SUCCESS if (de)serialization completes.
	 * @details [AI] Handles reading/writing which part is placed, object IDs, and animation step state.
	 */
	virtual MxResult Serialize(LegoStorage* p_storage);

	/**
	 * @brief [AI] Swaps the nodes representing the part at the given index, then hides the 3D node for main (wired) part.
	 * @param p_index Index in m_parts array. [AI]
	 */
	void FUN_10079050(MxS16 p_index);

	/**
	 * @brief [AI] Swaps two animation nodes in the scene tree, exchanging their display names and internal indices.
	 * @param p_param1 First node/part name (wired name). [AI]
	 * @param p_param2 Second node/part name (placed part name). [AI]
	 */
	void SwapNodesByName(LegoChar* p_param1, LegoChar* p_param2);

	/**
	 * @brief [AI] (Re-)initializes internal state from animation root, prepares morph keys for "platform" node and other key data.
	 * @details [AI] Sets up m_parts, m_unk0xc4 and prepares the morph key state machine for assembly.
	 */
	void FUN_10079160();

	/**
	 * @brief [AI] Hides the referenced animation node by setting its morph key to invisible.
	 * @param p_param Wireframe/scenenode part name. [AI]
	 */
	void FUN_100795d0(LegoChar* p_param);

	/**
	 * @brief [AI] Resets the node's morph key count to zero, restoring/showing the node.
	 * @param p_param Wireframe/scenenode part name. [AI]
	 */
	void FUN_10079680(LegoChar* p_param);

	/**
	 * @brief [AI] Recursively searches for a node with the given name and returns its node data.
	 * @param p_treeNode The tree node to begin search from. [AI]
	 * @param p_name Node name to search for. [AI]
	 * @return [AI] The node data if found, or NULL.
	 */
	LegoAnimNodeData* FindNodeDataByName(LegoTreeNode* p_treeNode, const LegoChar* p_name);

	/**
	 * @brief [AI] Recursively searches for a node with the given name and returns the node itself.
	 * @param p_treeNode The tree node to search. [AI]
	 * @param p_name Node name to search for. [AI]
	 * @return [AI] Pointer to matching LegoTreeNode, or NULL.
	 */
	LegoTreeNode* FindNodeByName(LegoTreeNode* p_treeNode, const LegoChar* p_name);

	/**
	 * @brief [AI] Advances current placed part, handles swaps, and updates morph/visibility.
	 * @param p_name Name of the newly placed part. [AI]
	 */
	void FUN_10079790(const LegoChar* p_name);

	/**
	 * @brief [AI] Rotates the assembly platform (root part) around the Y axis by the given angle (quaternion math).
	 * @param p_angle Angle to rotate by (in radians/degrees TBD). [AI]
	 */
	void RotateAroundYAxis(MxFloat p_angle);

	/**
	 * @brief [AI] Returns true if the part with the given name is not yet placed, but is the current to-be-placed in the sequence.
	 * @param p_name Name of the part to check. [AI]
	 * @return [AI] TRUE if this is the next part and not yet placed.
	 */
	MxBool FUN_10079c30(const LegoChar* p_name);

	/**
	 * @brief [AI] Returns whether a part (by name) has already been placed in the sequence.
	 * @param p_name Name of the part. [AI]
	 */
	MxBool PartIsPlaced(const LegoChar* p_name);

	/**
	 * @brief [AI] Advances the internal state for the assembly animation (step advancement).
	 * @details [AI] Controls how quickly the build process animates through its intermediate morph targets.
	 */
	void FUN_10079a90();

	/**
	 * @brief [AI] Checks if the supplied string matches "PLATFORM" (case-insensitive).
	 * @param p_string String to check. [AI]
	 */
	MxBool StringEqualsPlatform(const LegoChar* p_string);

	/**
	 * @brief [AI] Checks if the supplied string matches "SHELF" prefix (case-insensitive).
	 * @param p_string String to check. [AI]
	 */
	MxBool StringEqualsShelf(const LegoChar* p_string);

	/**
	 * @brief [AI] Checks if the supplied string ends with "Y" or "y" in the second-to-last character.
	 * @param p_string String to check. [AI]
	 */
	MxBool StringEndsOnY(const LegoChar* p_string);

	/**
	 * @brief [AI] Checks if string does not end on the character '0'.
	 * @param p_string String to check. [AI]
	 */
	MxBool StringDoesNotEndOnZero(const LegoChar* p_string);

	/**
	 * @brief [AI] Retrieves the wireframe/scene-graph name associated with the player-facing part name.
	 * @param p_name Player-facing part name. [AI]
	 * @return [AI] The corresponding wired (scene-node) name, or NULL if not found.
	 */
	const LegoChar* GetWiredNameByPartName(const LegoChar* p_name);

	/**
	 * @brief [AI] Sets the object id for the given part name in the assembly state.
	 * @param p_name Name of the part to update. [AI]
	 * @param p_objectId Object id to set. [AI]
	 */
	void SetPartObjectIdByName(const LegoChar* p_name, MxS16 p_objectId);

	/**
	 * @brief [AI] Sets the internal unknown word at offset 0xbc.
	 * @param p_unk0xbc The new value. [AI]
	 */
	void SetUnknown0xbc(undefined2 p_unk0xbc) { m_unk0xbc = p_unk0xbc; }

	/**
	 * @brief [AI] Provides access to the internal Matrix4 representing current animation state, typically a transformation matrix.
	 * @return [AI] Reference to the current transformation matrix.
	 */
	Matrix4& GetUnknown0xe0() { return m_unk0xe0; }

	/**
	 * @brief [AI] Returns TRUE if the given part's name ends with 'W' or 'w' as the second-to-last character.
	 * @param p_param String to check. [AI]
	 */
	MxBool StringEndsOnW(LegoChar* p_param);

	/**
	 * @brief [AI] Returns TRUE if the given part's name ends with 'Y', 'y', 'N', or 'n' as the second-to-last character.
	 * @param p_string String to check. [AI]
	 */
	MxBool StringEndsOnYOrN(const LegoChar* p_string);

	/**
	 * @brief [AI] Returns the world bounding sphere of the next part to be placed.
	 * @return [AI] Reference to the bounding sphere.
	 */
	const BoundingSphere& FUN_10079e20();

	/**
	 * @brief [AI] Returns the wired part name for the last placed part.
	 * @return [AI] String name.
	 */
	const LegoChar* GetWiredNameOfLastPlacedPart() { return m_parts[m_placedPartCount].m_wiredName; }

	/**
	 * @brief [AI] Returns how many assembly parts exist in the current build.
	 */
	MxS16 GetNumberOfParts() { return m_numberOfParts; }

	/**
	 * @brief [AI] Returns the count of how many parts have been placed so far.
	 */
	MxS16 GetPlacedPartCount() { return m_placedPartCount; }

	/**
	 * @brief [AI] Returns TRUE if all parts have been placed (i.e., assembly is complete).
	 */
	MxBool AllPartsPlaced()
	{
		return m_placedPartCount == m_numberOfParts;
	}

private:
	/**
	 * @brief [AI] Internal helper for blinking/visibility cycling of the next part to place, based on timer and bitmask.
	 */
	void Beta10Inline0x100733d0();

	MxU16 m_unk0xbc; ///< [AI] Used as a simple state/state counter variable; controls animation mode progression.

	MxS16 m_numberOfParts; ///< [AI] Total number of assembly steps (car parts). Verified by beta symbol dump.
	MxS16 m_placedPartCount; ///< [AI] Number of parts placed in current state. Name/offset aligns with game save/load. 

	LegoAnimNodeData* m_unk0xc4; ///< [AI] Pointer to main platform node data (root of assembly). 
	LegoAnim m_unk0xc8; ///< [AI] Secondary animation struct, used for direct manipulation/render of platform etc.
	MxMatrix m_unk0xe0; ///< [AI] Stores a local-to-world transform, set during StreamingTickle (usually "VIEW" node).

	UnknownListEntry* m_parts; ///< [AI] Array of assembly steps; entry per part. Deeply managed (allocated and deleted).

	MxFloat m_unk0x12c; ///< [AI] Animation and placement state timer; used for morph key progression.
	MxFloat m_unk0x130; ///< [AI] Step-wise timing/location for animated car build component.
	MxFloat m_unk0x134; ///< [AI] Cached animation duration (for platform or main shelf part).
	MxFloat m_unk0x138; ///< [AI] Step duration for each part (m_unk0x134 divided by number of keys).

	MxULong m_unk0x13c; ///< [AI] Used as state for part visibility blinking; contains bit fields and timers.
	LegoEntity* m_unk0x140; ///< [AI] Pointer to the main build entity ("Dunebld" or other entity under assembly).
	MxS32 m_unk0x144; ///< [AI] Temporary fields for internal counters/state. Often set to -1.
	MxS32 m_unk0x148; ///< [AI] Temporary fields for internal counters/state. Often set to -1.

	LegoChar* m_mainSourceId; ///< [AI] Name/id string for the current animation's data source, used for re-sync and action lookup.
};

#endif // LEGOCARBUILDPRESENTER_H