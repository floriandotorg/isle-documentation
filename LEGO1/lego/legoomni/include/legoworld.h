#ifndef LEGOWORLD_H
#define LEGOWORLD_H

// clang-format off
#include "mxpresenterlist.h"
#include "legoentitylist.h"
#include "legocachesoundlist.h"
// clang-format on

#include "legoentity.h"
#include "legomain.h"
#include "legopathcontrollerlist.h"
#include "roi/legoroi.h"

class LegoCameraController;
class LegoPathBoundary;
class LegoHideAnimPresenter;

#if defined(_M_IX86) || defined(__i386__)
#define COMPARE_POINTER_TYPE MxS32
#else
#define COMPARE_POINTER_TYPE MxS32*
#endif

/**
 * @brief Comparison functor for MxCore* pointers used by MxCoreSet to ensure a consistent ordering. [AI]
 * 
 * Uses casting to COMPARE_POINTER_TYPE for cross-platform compatibility, emulating pointer comparison as integers for some compilers. [AI]
 */
struct CoreSetCompare {
	MxS32 operator()(MxCore* const& p_a, MxCore* const& p_b) const
	{
		return (COMPARE_POINTER_TYPE) p_a < (COMPARE_POINTER_TYPE) p_b;
	}
};

/**
 * @brief Set of MxCore* pointers with custom comparison for pointer stability and uniqueness. [AI]
 */
typedef set<MxCore*, CoreSetCompare> MxCoreSet;

/**
 * @brief Represents the active 3D world, holding all entity, animation, sound, path, and ROI objects. [AI]
 * 
 * Derived from LegoEntity, LegoWorld manages the current game world, coordinating path controllers, animations, entity lists, ROIs, and sound cache for a specific "scene". [AI]
 * 
 * It is responsible for adding/removing actors and presenters, handling transitions and events, activating/pausing the world, and managing world startup sequences. [AI]
 */
class LegoWorld : public LegoEntity {
public:
	/**
	 * @brief Ticks for world startup sequencing. [AI]
	 */
	enum StartupTicks {
		e_start = 0, ///< Start tick, world is ready to be started. [AI]
		e_one,       ///< Countdown tick 1. [AI]
		e_two,       ///< Countdown tick 2. [AI]
		e_three,     ///< Countdown tick 3. [AI]
		e_four       ///< Countdown tick 4, initial state. [AI]
	};

	/**
	 * @brief Constructs a LegoWorld, initializing lists and notifying the notification manager. [AI]
	 */
	LegoWorld();

	/**
	 * @brief Cleans up the world, destroying all held entities, presenters, and controllers. [AI]
	 */
	~LegoWorld() override; // vtable+0x00

	/**
	 * @brief Notification callback responding to registered events such as EndAction and NewPresenter. [AI]
	 * @param p_param The notification parameter, interpreted depending on event. [AI]
	 * @return Nonzero if the notification was processed, zero otherwise. [AI]
	 */
	MxLong Notify(MxParam& p_param) override;         // vtable+0x04

	/**
	 * @brief Main world tick/update, especially manages startup countdown. [AI]
	 * @details Counts down the world startup ticks, prepares the world for activation and handles initial presenter readiness. [AI]
	 * @return TRUE on success. [AI]
	 */
	MxResult Tickle() override;                       // vtable+0x08

	/**
	 * @brief Initializes the world using an action, creating entity and sound lists, and camera controller. [AI]
	 * @param p_dsAction The action describing world's initialization parameters. [AI]
	 * @return SUCCESS on correct initialization, FAILURE otherwise. [AI]
	 */
	MxResult Create(MxDSAction& p_dsAction) override; // vtable+0x18

	/**
	 * @brief Destroys the world and its contents, optionally called from the destructor. [AI]
	 * @param p_fromDestructor If TRUE, destruction occurs as part of destructor; otherwise, cleans up as needed. [AI]
	 */
	void Destroy(MxBool p_fromDestructor) override;   // vtable+0x1c

	/**
	 * @brief Called when the world is ready to be used—typically for custom scene setup after startup. [AI]
	 */
	virtual void ReadyWorld();                        // vtable+0x50

	/**
	 * @brief Initializes and returns the camera controller for the world; may create it on-demand. [AI]
	 * @return The initialized camera controller, or NULL on failure. [AI]
	 */
	virtual LegoCameraController* VTable0x54();       // vtable+0x54

	/**
	 * @brief Adds an object (entity, presenter, ROI, etc.) to the appropriate world-managed list or set. [AI]
	 * @param p_object The object to add. [AI]
	 */
	virtual void Add(MxCore* p_object);               // vtable+0x58

	/**
	 * @brief Potential "escape" action for world; returns FALSE by default, may be overridden in child worlds. [AI]
	 * @return FALSE by default. [AI]
	 */
	virtual MxBool VTable0x5c() { return FALSE; } // vtable+0x5c

	/**
	 * @brief Placeholder/extensible virtual—default does nothing. [AI]
	 */
	virtual void VTable0x60() {} // vtable+0x60

	/**
	 * @brief Handles user-initiated "escape" or exit action. Returns FALSE by default. [AI]
	 * @return FALSE by default. [AI]
	 */
	virtual MxBool Escape() { return FALSE; } // vtable+0x64

	/**
	 * @brief Enables or disables (pauses) the world and its main components. [AI]
	 * @param p_enable If TRUE, world is enabled; if FALSE, world is disabled and presenters/controllers are paused. [AI]
	 */
	virtual void Enable(MxBool p_enable); // vtable+0x68

	/**
	 * @brief Returns the class name for runtime type information and debugging. [AI]
	 * @return The string "LegoWorld". [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return "LegoWorld";
	}

	/**
	 * @brief Runtime type checking; checks class hierarchy. [AI]
	 * @param p_name Name to check against this or parent classes. [AI]
	 * @return TRUE if p_name matches this or any parent class; FALSE otherwise. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoWorld::ClassName()) || LegoEntity::IsA(p_name);
	}

	/**
	 * @brief Checks if there are any presenters pending to fully enter their tickle (animation) state. [AI]
	 * @return TRUE if any presenter is still preparing or starting, FALSE otherwise. [AI]
	 */
	MxBool PresentersPending();

	/**
	 * @brief Removes an object from all relevant world-managed lists or sets, and also detaches if needed. [AI]
	 * @param p_object The object to remove. [AI]
	 */
	void Remove(MxCore* p_object);

	/**
	 * @brief Places an actor along a path, from source to destination, using named references and scaling. [AI]
	 * @param p_actor The actor to place. [AI]
	 * @param p_name Name of the path/segment. [AI]
	 * @param p_src Source point/index. [AI]
	 * @param p_srcScale Scaling value at the source. [AI]
	 * @param p_dest Destination point/index. [AI]
	 * @param p_destScale Scaling value at the destination. [AI]
	 * @return SUCCESS on placement, FAILURE otherwise. [AI]
	 */
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		const char* p_name,
		MxS32 p_src,
		float p_srcScale,
		MxS32 p_dest,
		float p_destScale
	);

	/**
	 * @brief Places an actor using only its reference, using controller logic. [AI]
	 * @param p_actor The actor to place. [AI]
	 * @return SUCCESS on placement, FAILURE otherwise. [AI]
	 */
	MxResult PlaceActor(LegoPathActor* p_actor);

	/**
	 * @brief Places an actor using detailed presenter, position and direction. [AI]
	 * @param p_actor The actor to place. [AI]
	 * @param p_presenter Presenter (animation, locomotion, etc.) to associate. [AI]
	 * @param p_position Target position vector. [AI]
	 * @param p_direction Target direction vector. [AI]
	 * @return SUCCESS on placement, FAILURE otherwise. [AI]
	 */
	MxResult PlaceActor(
		LegoPathActor* p_actor,
		LegoAnimPresenter* p_presenter,
		Vector3& p_position,
		Vector3& p_direction
	);

	/**
	 * @brief Removes an actor from all known path controllers. [AI]
	 * @param p_actor The actor to remove. [AI]
	 */
	void RemoveActor(LegoPathActor* p_actor);

	/**
	 * @brief Determines if an actor already exists in any controller in this world. [AI]
	 * @param p_actor The actor to search for. [AI]
	 * @return TRUE if found, FALSE otherwise. [AI]
	 */
	MxBool ActorExists(LegoPathActor* p_actor);

	/**
	 * @brief Forwards a presenter to all path controllers to perform a custom action (possibly hide, etc.). [AI]
	 * @param p_presenter The presenter for the custom action. [AI]
	 */
	void FUN_1001fda0(LegoAnimPresenter* p_presenter); // [AI_SUGGESTED_NAME: ForwardHideAnimationToControllers]

	/**
	 * @brief Forwards a presenter to all path controllers for another custom or state change action. [AI]
	 * @param p_presenter The presenter for the custom action. [AI]
	 */
	void FUN_1001fe90(LegoAnimPresenter* p_presenter); // [AI_SUGGESTED_NAME: ForwardShowAnimationToControllers]

	/**
	 * @brief Finds a path boundary in all path controllers by name. [AI]
	 * @param p_name The name of the path boundary to find. [AI]
	 * @return The pointer to the found boundary, or NULL. [AI]
	 */
	LegoPathBoundary* FindPathBoundary(const char* p_name);

	/**
	 * @brief Adds a path controller to the world and calls its initialization with this. [AI]
	 * @param p_controller The path controller to add. [AI]
	 */
	void AddPath(LegoPathController* p_controller);

	/**
	 * @brief Gets information about the currently active path and boundaries. [AI]
	 * @param p_boundaries Array to hold boundaries (output). [AI]
	 * @param p_numL Number of boundaries (output). [AI]
	 * @return SUCCESS or FAILURE. [AI]
	 */
	MxResult GetCurrPathInfo(LegoPathBoundary** p_boundaries, MxS32& p_numL);

	/**
	 * @brief Finds an object of a given class and name in the world. [AI]
	 * @param p_class The class name to search for ("MxEntity", "MxControlPresenter", etc.). [AI]
	 * @param p_name The object name to match. [AI]
	 * @return Object pointer if found, otherwise NULL. [AI]
	 */
	MxCore* Find(const char* p_class, const char* p_name);

	/**
	 * @brief Finds an object in the world by its atom id and entity id. [AI]
	 * @param p_atom The atom id to match. [AI]
	 * @param p_entityId The entity id to match. [AI]
	 * @return Object pointer if found, otherwise NULL. [AI]
	 */
	MxCore* Find(const MxAtomId& p_atom, MxS32 p_entityId);

	/**
	 * @brief Returns the current camera controller for the world. [AI]
	 * @return Pointer to the camera controller. [AI]
	 */
	LegoCameraController* GetCameraController() { return m_cameraController; }

	/**
	 * @brief Returns the current list of entities. [AI]
	 * @return Pointer to the entity list. [AI]
	 */
	LegoEntityList* GetEntityList() { return m_entityList; }

	/**
	 * @brief Gets the world id associated with this world. [AI]
	 * @return The world id enum value. [AI]
	 */
	LegoOmni::World GetWorldId() { return m_worldId; }

	/**
	 * @brief Checks if the 'set0xd0' set is empty. [AI]
	 * @return TRUE if empty, FALSE otherwise. [AI]
	 */
	MxBool GetUnknown0xd0Empty() { return m_set0xd0.empty(); } // [AI_SUGGESTED_NAME: IsPausedSetEmpty]

	/**
	 * @brief Gets the list of all ROIs (Real-time Object Instances) in the world. [AI]
	 * @return Reference to the ROI list. [AI]
	 */
	list<LegoROI*>& GetROIList() { return m_roiList; }

	/**
	 * @brief Gets the animation presenter responsible for hide animations in this world. [AI]
	 * @return Pointer to the hide animation presenter, or NULL. [AI]
	 */
	LegoHideAnimPresenter* GetHideAnimPresenter() { return m_hideAnim; }

	/**
	 * @brief Sets the world id for this world instance. [AI]
	 * @param p_worldId The world id to set. [AI]
	 */
	void SetWorldId(LegoOmni::World p_worldId) { m_worldId = p_worldId; }

	// SYNTHETIC: LEGO1 0x1001dee0
	// LegoWorld::`scalar deleting destructor'

protected:
	/**
	 * @brief List of all path controllers currently managing pathing in this world. [AI]
	 */
	LegoPathControllerList m_pathControllerList; // 0x68

	/**
	 * @brief List of active animation presenters (anims, hide/show, looping, etc.). [AI]
	 */
	MxPresenterList m_animPresenters;            // 0x80

	/**
	 * @brief Camera controller for world's main view. [AI]
	 */
	LegoCameraController* m_cameraController;    // 0x98

	/**
	 * @brief List of all main world entities, such as actors and objects. [AI]
	 */
	LegoEntityList* m_entityList;                // 0x9c

	/**
	 * @brief List of cached sounds for faster access during this world's lifetime. [AI]
	 */
	LegoCacheSoundList* m_cacheSoundList;        // 0xa0

	/**
	 * @brief Indicates if the world has been destroyed or is pending destruction. [AI]
	 */
	MxBool m_destroyed;                          // 0xa4

	/**
	 * @brief Set of 'auxiliary' objects, including presenters, that aren't core entity or animation, but still must be managed. [AI]
	 */
	MxCoreSet m_set0xa8;                         // 0xa8

	/**
	 * @brief List of control presenters (UI, input, cutscene control, etc.). [AI]
	 */
	MxPresenterList m_controlPresenters;         // 0xb8

	/**
	 * @brief Set of currently paused/disconnected objects when world is disabled. [AI]
	 * @details Holds any object that should be re-enabled on world resume, mainly presenters. [AI]
	 */
	MxCoreSet m_set0xd0;                         // 0xd0

	/**
	 * @brief List of all visible LegoROI objects in the world, used for rendering and selection. [AI]
	 */
	list<LegoROI*> m_roiList;                    // 0xe0

	/**
	 * @brief Currently assigned world id, corresponding to an enum in LegoOmni. [AI]
	 */
	LegoOmni::World m_worldId;                   // 0xec

	/**
	 * @brief Animation presenter for ROI hide (vanish, fade, etc.) sequences. [AI]
	 */
	LegoHideAnimPresenter* m_hideAnim; // 0xf0

	/**
	 * @brief Current world startup tick countdown—controls staged world startup logic. [AI]
	 */
	MxS16 m_startupTicks;  // 0xf4

	/**
	 * @brief Indicates if the world has successfully started and is considered active. [AI]
	 */
	MxBool m_worldStarted; // 0xf6

	/**
	 * @brief Unknown, probably flags or padding. [AI]
	 */
	undefined m_unk0xf7;   // 0xf7
};

// clang-format off
// TEMPLATE: LEGO1 0x1001d780
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::~_Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >

// TEMPLATE: LEGO1 0x1001d850
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::iterator::_Inc

// TEMPLATE: LEGO1 0x1001d890
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::erase

// TEMPLATE: LEGO1 0x1001dcf0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Erase

// TEMPLATE: LEGO1 0x1001dd30
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Init

// TEMPLATE: LEGO1 0x1001ddf0
// list<LegoROI *,allocator<LegoROI *> >::~list<LegoROI *,allocator<LegoROI *> >

// TEMPLATE: LEGO1 0x1001df50
// List<LegoROI *>::~List<LegoROI *>

// TEMPLATE: LEGO1 0x1001de60
// list<LegoROI *,allocator<LegoROI *> >::_Buynode

// TEMPLATE: LEGO1 0x1001de90
// set<MxCore *,CoreSetCompare,allocator<MxCore *> >::~set<MxCore *,CoreSetCompare,allocator<MxCore *> >

// TEMPLATE: LEGO1 0x1001df00
// Set<MxCore *,CoreSetCompare>::~Set<MxCore *,CoreSetCompare>

// TEMPLATE: LEGO1 0x1001f590
// list<LegoROI *,allocator<LegoROI *> >::erase

// TEMPLATE: LEGO1 0x100208b0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::insert

// TEMPLATE: LEGO1 0x10020b20
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::iterator::_Dec

// TEMPLATE: LEGO1 0x10020b70
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::lower_bound

// TEMPLATE: LEGO1 0x10020bb0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Buynode

// TEMPLATE: LEGO1 0x10020bd0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Insert

// TEMPLATE: LEGO1 0x10020e50
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Lrotate

// TEMPLATE: LEGO1 0x10020eb0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Rrotate

// TEMPLATE: LEGO1 0x10021340
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::find

// TEMPLATE: LEGO1 0x10022360
// ?_Construct@@YAXPAPAVMxCore@@ABQAV1@@Z

// GLOBAL: LEGO1 0x100f11a0
// _Tree<MxCore *,MxCore *,set<MxCore *,CoreSetCompare,allocator<MxCore *> >::_Kfn,CoreSetCompare,allocator<MxCore *> >::_Nil
// clang-format on

#endif // LEGOWORLD_H
