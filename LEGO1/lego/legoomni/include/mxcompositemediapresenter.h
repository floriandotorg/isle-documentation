#ifndef MXCOMPOSITEMEDIAPRESENTER_H
#define MXCOMPOSITEMEDIAPRESENTER_H

#include "mxcompositepresenter.h"

// VTABLE: LEGO1 0x100d96b0
// VTABLE: BETA10 0x101bf540
// SIZE 0x50

/**
 * @brief Composite presenter for handling multiple synchronized media actions. [AI]
 * 
 * This class manages a group of media presenters (audio, video, etc.), allowing
 * for coordinated playback of multiple media elements as a single multimedia composite. [AI]
 * It is typically used to present compound cutscenes or complex scenes
 * where several media streams must be controlled as a unit or in lockstep. [AI]
 * 
 * Registering and unregistering occurs with the video manager to allow centralized control. [AI]
 */
class MxCompositeMediaPresenter : public MxCompositePresenter {
public:
	/**
	 * @brief Constructs the composite media presenter and registers it with the video manager. [AI]
	 */
	MxCompositeMediaPresenter();

	/**
	 * @brief Destructor; unregisters this presenter from the video manager. [AI]
	 */
	~MxCompositeMediaPresenter() override;

	/**
	 * @brief Orchestrates the tickle (update) across all managed sub-presenters, depending on current tickle state. [AI]
	 * @details Progresses state machine as needed and delegates tickles to child presenters for ongoing management. [AI]
	 */
	MxResult Tickle() override; // vtable+0x08

	/**
	 * @brief Returns the class name for this presenter type. [AI]
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x100f02d4
		return "MxCompositeMediaPresenter";
	}

	/**
	 * @brief Checks if this presenter is, or derives from, the given class name. [AI]
	 * @param p_name Name to check against type hierarchy. [AI]
	 * @return True if this or a base class matches the provided type name. [AI]
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxCompositeMediaPresenter::ClassName()) || MxCompositePresenter::IsA(p_name);
	}

	/**
	 * @brief Handles transition logic when entering the starting state,
	 * orchestrating sub-presenters and managing scene construction logic. [AI]
	 * @details This drives the transition from pre-start to ready for streaming, handling 
	 * special conditions for action flags and time synchronization. [AI]
	 */
	void StartingTickle() override;                                           // vtable+0x1c

	/**
	 * @brief Begins the playback of composite actions—
	 * instantiates and configures individual sub-presenters for each action in a multi-action container. [AI]
	 * @param p_controller Source stream controller for media data. [AI]
	 * @param p_action Multi-action containing list of sub-actions; each is assigned to a proper presenter type. [AI]
	 * @details Instantiates presenters using action dispatch, configures loop or special flags as needed, 
	 * and adds them to internal management list. [AI]
	 */
	MxResult StartAction(MxStreamController*, MxDSAction* p_action) override; // vtable+0x3c

	/**
	 * @brief Propagates PutData events to all sub-presenters during streaming or completion states. [AI]
	 * @details Updates child presenters that may need to flush or process their own output, 
	 * but only applies while streaming, repeating, freezing, or done. [AI]
	 */
	MxResult PutData() override;                                              // vtable+0x4c

private:
	MxS16 m_unk0x4c;  ///< [AI] Counter used for tracking how many child presenters have completed/started—purpose: synchronization in state transitions. [AI_SUGGESTED_NAME: m_readyChildrenCount]
	MxBool m_unk0x4e; ///< [AI] Indicates whether all child presenters have processed initial tickle logic and are prepared for streaming together. [AI_SUGGESTED_NAME: m_allChildrenStarted]
};

// SYNTHETIC: LEGO1 0x10074000
// MxCompositeMediaPresenter::`scalar deleting destructor'

#endif // MXCOMPOSITEMEDIAPRESENTER_H
