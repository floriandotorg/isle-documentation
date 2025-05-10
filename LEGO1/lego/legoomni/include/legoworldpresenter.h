#ifndef LEGOWORLDPRESENTER_H
#define LEGOWORLDPRESENTER_H

#include "legoentitypresenter.h"

#include <stdio.h>

/**
 * @class LegoWorldPresenter
 * @brief [AI] Presenter for the entire LEGO world, responsible for loading, parsing, and managing world entities, geometry, and environmental data for a world. Drives the entity setup and presentation pipeline for a world/scene.
 * @details [AI] LegoWorldPresenter mediates between the world data files (especially world.wdb), loads and instantiates geometry/parts/models, creates texture and part presenters, and coordinates with other system managers (Building, Plant, Animation, etc.) on loading and configuration. It is capable of running in different presentation qualities, as set by configureLegoWorldPresenter.
 * Inherits from LegoEntityPresenter.
 */
class LegoWorld;
struct ModelDbPart;
struct ModelDbModel;

// VTABLE: LEGO1 0x100d8ee0
// SIZE 0x54
class LegoWorldPresenter : public LegoEntityPresenter {
public:
	/**
	 * @brief [AI] Constructs a LegoWorldPresenter with initial objectId for presented models.
	 */
	LegoWorldPresenter();

	/**
	 * @brief [AI] Destructor; unregisters, cleans up associated world, reverts system managers to previous state, and notifies system of its removal.
	 */
	~LegoWorldPresenter() override; // vtable+0x00

	/**
	 * @brief [AI] Configure the global 'quality' level for presenting the LEGO world. This affects which LOD (level-of-detail) geometry is loaded for the world, e.g. "isle_lo", "isle", or "isle_hi" models.
	 * @param p_legoWorldPresenterQuality Presentation quality (0=low, 1=default, 2=high). [AI]
	 */
	static void configureLegoWorldPresenter(MxS32 p_legoWorldPresenterQuality);

	/**
	 * @brief [AI] Returns handler class name for use by presenter/class factories.
	 * @return Pointer to static string "LegoWorldPresenter". [AI]
	 */
	static const char* HandlerClassName();

	/**
	 * @brief [AI] Returns handler class name for this presenter instance. Used for run-time type checking and reflection.
	 * @return "LegoWorldPresenter" [AI]
	 */
	const char* ClassName() const override; // vtable+0x0c

	/**
	 * @brief [AI] Checks whether this object is of a given class (or base class) by string name.
	 * @param p_name Class name to check against. [AI]
	 * @return True if the queried name is "LegoWorldPresenter" or any base class's implemented name. [AI]
	 */
	MxBool IsA(const char* p_name) const override; // vtable+0x10

	/**
	 * @brief [AI] Tickle when in "ready" state: creates the LegoWorld entity, places it into the system, and advances to "starting" tickle state. Responsible for initial instantiation.
	 */
	void ReadyTickle() override;                                                           // vtable+0x18

	/**
	 * @brief [AI] Tickle when in "starting" state: signals child presenters to move to "ready" if idle, then progresses to "streaming" state. Used to synchronize sub-presenters with world setup.
	 */
	void StartingTickle() override;                                                        // vtable+0x1c

	/**
	 * @brief [AI] Parses extra data attached to the current action, such as selecting which world to load from the world's extra SI file string (e.g., "WORLD:ISLE"). Loads the correct world and sets up its worldId.
	 */
	void ParseExtra() override;                                                            // vtable+0x30

	/**
	 * @brief [AI] Starts the world presentation process: creates child presenters for every sub-action (often parts/models)
	 * and registers itself with the VideoManager for streaming/rendering lifecycle. Used in SI file-driven media action trees.
	 * @param p_controller Stream controller for loading SI file data. [AI]
	 * @param p_action The world load action (should be a MultiAction/ParallelAction referring to world children). [AI]
	 * @return SUCCESS if all sub-presenters and models could be created, FAILURE otherwise. [AI]
	 */
	MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) override; // vtable+0x3c

	/**
	 * @brief [AI] Handles completion and composition of a presenter's child (typically model/entity), calling Add() for LegoWorld on presenters that aren't animations or composites, and forwarding their ownership to the world.
	 * @param p_presenter Presenter that finished its action. [AI]
	 */
	void VTable0x60(MxPresenter* p_presenter) override;                                    // vtable+0x60

	/**
	 * @brief [AI] Loads all data for a named world from the world database (WDB) file, creates all parts and models, and puts them into the world entity.
	 * @param p_worldName The name/key of the world to load, such as "ISLE". [AI]
	 * @param p_world The world entity instance that will receive all parts/models. [AI]
	 * @return SUCCESS on fully loaded, FAILURE on any error. [AI]
	 */
	MxResult LoadWorld(char* p_worldName, LegoWorld* p_world);

	// SYNTHETIC: LEGO1 0x10066750
	// LegoWorldPresenter::`scalar deleting destructor'

private:
	/**
	 * @brief [AI] Loads a single part from the world database file, reads and caches its chunk, and hands it to the LegoPartPresenter. Called for each ModelDbPart in the loaded world.
	 * @param p_part Model database part to load. [AI]
	 * @param p_wdbFile Opened file pointer to world.wdb. [AI]
	 * @return SUCCESS if part chunk stored successfully, FAILURE otherwise. [AI]
	 */
	MxResult LoadWorldPart(ModelDbPart& p_part, FILE* p_wdbFile);

	/**
	 * @brief [AI] Loads a single model (geometry instance) from the world database, creates a corresponding presenter, entity, and attaches it to the world. Handles actor/entity/model types based on their presenter type.
	 * @param p_model The model database model to load (location, direction, presenter, etc). [AI]
	 * @param p_wdbFile Opened file pointer to world.wdb. [AI]
	 * @param p_world The LegoWorld object the model gets attached to. [AI]
	 * @return SUCCESS if model loaded and presenter/entity created, FAILURE otherwise. [AI]
	 */
	MxResult LoadWorldModel(ModelDbModel& p_model, FILE* p_wdbFile, LegoWorld* p_world);

	/**
	 * @brief [AI] Next generated object ID for models/parts created by this presenter. Used to assign unique World Entity/Object IDs at runtime. Initialized to 50000.
	 */
	MxU32 m_nextObjectId;
};

#endif // LEGOWORLDPRESENTER_H