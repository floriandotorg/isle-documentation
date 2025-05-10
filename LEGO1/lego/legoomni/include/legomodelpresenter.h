#ifndef LEGOMODELPRESENTER_H
#define LEGOMODELPRESENTER_H

#include "mxvideopresenter.h"

class LegoROI;
class LegoWorld;
class LegoEntity;
class MxDSChunk;

/// \class LegoModelPresenter
/// \brief [AI] Presenter class for managing 3D model (ROI) presentation and their relationship with entities in the world. Inherits from MxVideoPresenter.
/// \details [AI] Handles the instantiation, configuration, and tickle logic of a 3D ROI (Render Object Instance) as used in LEGO Island. Supports parsing extra actions, streaming model data from resources, configuring textures, and linking ROIs to entities or placing them in the world. Can be configured for special texture handling via a static configuration. [AI]
///
/// SIZE 0x6c [AI]
/// VTABLE: LEGO1 0x100d4e50 [AI]
/// VTABLE: BETA10 0x101bcd88 [AI]
class LegoModelPresenter : public MxVideoPresenter {
public:
	/// \brief [AI] Default constructor, initializes member variables to default.
	LegoModelPresenter() { Reset(); }

	/// \brief [AI] Destructor. Cleans up allocated resources. Calls Destroy with TRUE.
	~LegoModelPresenter() override { Destroy(TRUE); }

	/// \brief [AI] Destroys all resources and resets state. Calls base class destroy if not from destructor.
	void Destroy() override { Destroy(FALSE); } // vtable+0x38 [AI]

	/// \brief [AI] Configures the LegoModelPresenter's handling of textures/model data. [AI]
	/// \param p_modelPresenterConfig Enable/disable special texture mode (see source handling of ^ prefix in texture names). [AI]
	static void configureLegoModelPresenter(MxS32 p_modelPresenterConfig);

	/// \brief [AI] Returns the handler class name string. Used for class identification/disambiguation. [AI]
	static const char* HandlerClassName()
	{
		// STRING: LEGO1 0x100f067c
		return "LegoModelPresenter";
	}

	/// \brief [AI] Returns the class name of this presenter. Used for run-time class checks. [AI]
	const char* ClassName() const override // vtable+0x0c [AI]
	{
		return HandlerClassName();
	}

	/// \brief [AI] Checks if this object matches a given class name (checks own and base class). [AI]
	/// \param p_name Class name to check against. [AI]
	/// \return True if the object matches the class name or is a subclass. [AI]
	MxBool IsA(const char* p_name) const override // vtable+0x10 [AI]
	{
		return !strcmp(p_name, ClassName()) || MxVideoPresenter::IsA(p_name);
	}

	/// \brief [AI] Handles the tickle state when moving into the Ready state. If necessary, creates or assigns an ROI, links it to an entity, and updates internal state. [AI]
	void ReadyTickle() override; // vtable+0x18 [AI]

	/// \brief [AI] Parses and applies extra data from the action, for example to auto-create or DB-create an ROI based on parsed strings. [AI]
	void ParseExtra() override;  // vtable+0x30 [AI]

	/// \brief [AI] Loads or associates an ROI for presentation from a chunk, linking it to a LegoEntity or LegoWorld as appropriate. Sets visibility, attaches to video manager and/or world. [AI]
	/// \param p_chunk [AI] Data chunk with ROI animation/model resource.
	/// \param p_entity [AI] Entity to associate the ROI with. May be NULL.
	/// \param p_roiVisible [AI] Initial visibility for the created ROI.
	/// \param p_world [AI] World to add ROI to if no entity provided.
	/// \return [AI] SUCCESS or FAILURE.
	MxResult FUN_1007ff70(MxDSChunk& p_chunk, LegoEntity* p_entity, MxBool p_roiVisible, LegoWorld* p_world);

	/// \brief [AI] Resets member variables to initial state. [AI]
	void Reset()
	{
		m_roi = NULL;
		m_addedToView = FALSE;
	}

	// SYNTHETIC: LEGO1 0x1000cdd0
	// LegoModelPresenter::`scalar deleting destructor'
	// [AI] This is a compiler-synthesized destructor, no need to document.

protected:
	/// \brief [AI] Resource destroy function, called by both regular and destructor destroy. Resets state and optionally calls base destroy logic. [AI]
	/// \param p_fromDestructor True if being destroyed via destructor (do not call base destroy). [AI]
	void Destroy(MxBool p_fromDestructor);

private:
	LegoROI* m_roi;       ///< [AI] Pointer to the currently managed ROI (3D model instance). [AI]
	MxBool m_addedToView; ///< [AI] True if the ROI was inserted into the 3D manager/view; false if managed externally (e.g., by character manager, DB create, etc.). [AI]

	/// \brief [AI] Helper to create and setup the ROI from a resource chunk, reading model and texture information, and setting up transformation according to action. [AI]
	/// \param p_chunk [AI] Data chunk containing ROI resource data.
	/// \return [AI] SUCCESS or FAILURE depending on model loading and setup.
	MxResult CreateROI(MxDSChunk* p_chunk);
};

#endif // LEGOMODELPRESENTER_H