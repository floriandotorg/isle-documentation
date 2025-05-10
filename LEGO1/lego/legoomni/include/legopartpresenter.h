#ifndef LEGOPARTPRESENTER_H
#define LEGOPARTPRESENTER_H

#include "legonamedpartlist.h"
#include "mxmediapresenter.h"

// VTABLE: LEGO1 0x100d4df0
// SIZE 0x54
/**
 * @brief [AI] Presents and loads Lego part definitions from SI chunks and manages their installation in ViewLODListManager.
 * @details [AI] LegoPartPresenter is a derived presenter that reads Lego part data (geometry, textures, names, LODs) from MxDSChunk binary data supplied by MxDSSubscriber. After parsing and instantiating all LegoNamedParts with their LODs, it stores these into the ViewLODListManager for later use by the renderer. It also manages the resources' proper destruction and deallocation. The loading of textures supports a configurable hardware/software order, based on global config.
 */
class LegoPartPresenter : public MxMediaPresenter {
public:
	/**
	 * @brief [AI] Constructs and resets the LegoPartPresenter state.
	 */
	LegoPartPresenter() { Reset(); }

	/**
	 * @brief [AI] Destructor calls Destroy to release resources.
	 * @details [AI] Ensures all loaded parts and references are deallocated when this presenter is destroyed.
	 */
	~LegoPartPresenter() override { Destroy(TRUE); }

	/**
	 * @brief [AI] Virtual destroy method called by framework. Calls Destroy(FALSE).
	 */
	void Destroy() override { Destroy(FALSE); } // vtable+0x38

	/**
	 * @brief [AI] Get static name of this handler's class.
	 * @return [AI] Static string literal "LegoPartPresenter".
	 */
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f05d8
		return "LegoPartPresenter";
	}

	/**
	 * @brief [AI] Returns the name of the concrete class.
	 * @return [AI] The handler class name.
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		return HandlerClassName();
	}

	/**
	 * @brief [AI] Type checking: returns true if p_name is this class or a parent class name.
	 * @param p_name [AI] Name to compare.
	 * @return [AI] True if the name matches this class or a base class.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, LegoPartPresenter::ClassName()) || MxMediaPresenter::IsA(p_name);
	}

	/**
	 * @brief [AI] Called when entering the Ready tickle state: loads and installs parts from the subscriber stream if available.
	 * @details [AI] Reads chunk data, parses all contained Lego parts and textures, and stores the results via Store(). Ends the action.
	 */
	void ReadyTickle() override;      // vtable+0x18

	/**
	 * @brief [AI] Registers this presenter with the VideoManager.
	 * @details [AI] Called when the presenter is added to the presenter's manager; makes the part presenter available for use.
	 * @return [AI] Success status.
	 */
	MxResult AddToManager() override; // vtable+0x34

	/**
	 * @brief [AI] Configure global settings for texture loading order and maximum number of LODs.
	 * @param p_partPresenterConfig1 [AI] If true, load hardware textures first; otherwise, load software textures first.
	 * @param p_partPresenterConfig2 [AI] Maximum allowed LODs per part to load (surplus are ignored).
	 */
	static void configureLegoPartPresenter(MxS32 p_partPresenterConfig1, MxS32 p_partPresenterConfig2);

	// SYNTHETIC: LEGO1 0x1000d060
	// LegoPartPresenter::`scalar deleting destructor'

	/**
	 * @brief [AI] Resets the LegoPartPresenter by clearing any loaded LegoNamedPartList.
	 * @details [AI] Sets the m_parts pointer to NULL and does not deallocate previous objects—it is intended to be used on a freshly constructed object.
	 */
	void Reset() { m_parts = NULL; }

	/**
	 * @brief [AI] Reads Lego part and texture data from a MxDSChunk and builds internal part list.
	 * @details [AI] Parses both texture and geometry definitions for all named parts, creating all necessary objects in memory.
	 * @param p_chunk [AI] SI chunk to be deserialized.
	 * @return [AI] Success if all data is parsed and objects are instantiated; failure if any errors occur.
	 */
	MxResult Read(MxDSChunk& p_chunk);

	/**
	 * @brief [AI] Transfers all loaded named Lego parts and LODs to the ViewLODListManager.
	 * @details [AI] After calling, the loaded part data is pushed to the centralized LOD manager and this presenter’s local storage is reset.
	 */
	void Store();

private:
	/**
	 * @brief [AI] Releases all resources associated with this presenter.
	 * @param p_fromDestructor [AI] True if called from destructor, false if called explicitly via Destroy().
	 * @details [AI] Handles unregistration from VideoManager, deletes all owned parts, and invokes base class destruction if needed.
	 */
	void Destroy(MxBool p_fromDestructor);

	/**
	 * @brief [AI] List of parsed LegoNamedParts loaded from the stream, pending installation.
	 */
	LegoNamedPartList* m_parts; // 0x50
};

#endif // LEGOPARTPRESENTER_H
