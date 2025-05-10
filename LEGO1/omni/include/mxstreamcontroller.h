#ifndef MXSTREAMCONTROLLER_H
#define MXSTREAMCONTROLLER_H

#include "decomp.h"
#include "mxatom.h"
#include "mxcore.h"
#include "mxcriticalsection.h"
#include "mxdsobject.h"
#include "mxdssubscriber.h"
#include "mxnextactiondatastart.h"
#include "mxstl/stlcompat.h"

class MxDSAction;
class MxDSStreamingAction;
class MxStreamProvider;

/**
 * @brief [AI] List class specialized for storing MxNextActionDataStart pointers, managing streaming action start data.
 * @details [AI] This utility list provides searching and removal capabilities for action data starts, linking data offsets to logical actions in the streaming logic.
 */
class MxNextActionDataStartList : public MxUtilityList<MxNextActionDataStart*> {
public:
	/**
	 * @brief [AI] Searches for a MxNextActionDataStart element with the given object ID and unknown value.
	 * @param p_id [AI] Object ID to match against.
	 * @param p_value [AI] Value (often "unknown24") to match.
	 * @return [AI] Pointer to the matching MxNextActionDataStart or NULL if not found.
	 */
	MxNextActionDataStart* Find(MxU32 p_id, MxS16 p_value);

	/**
	 * @brief [AI] Searches for a MxNextActionDataStart with the given properties and erases it from the list if found.
	 * @param p_id [AI] Object ID to match against.
	 * @param p_value [AI] Value (often "unknown24") to match, or -2 to match any.
	 * @return [AI] Pointer to the found-and-erased MxNextActionDataStart, or NULL if none found.
	 */
	MxNextActionDataStart* FindAndErase(MxU32 p_id, MxS16 p_value);
};

/**
 * @brief [AI] Controller for streaming and managing multimedia resources and actions during gameplay.
 * @details [AI] MxStreamController manages dynamic streaming of data, handling subscribers, action objects, and the provider responsible for loading/reading resources. It works with MxDSAction and MxDSSubscriber, coordinating how scripted actions and multimedia objects are streamed and parsed frame-by-frame.
 * 
 * This is a central class in resource handling, linking file abstraction, direct stream control, and update notifications across the system.
 * In its lifetime, it tracks actions pending to be streamed, in-process or queued, and actions already streamed, to manage play and event timing for media.
 */
class MxStreamController : public MxCore {
public:
	/**
	 * @brief [AI] Constructor. Initializes member variables and sets up an empty streaming control context.
	 */
	MxStreamController();

	/**
	 * @brief [AI] Destructor. Cleans up provider, all current actions, subscribers, and action lists.
	 */
	~MxStreamController() override; // vtable+0x00

	/**
	 * @brief [AI] Returns the class name used for runtime type checks.
	 * @return [AI] "MxStreamController"
	 */
	const char* ClassName() const override // vtable+0x0c
	{
		// STRING: LEGO1 0x10102130
		return "MxStreamController";
	}

	/**
	 * @brief [AI] Performs runtime type checking, matching the given name with this or any parent class.
	 * @param p_name [AI] Name to check against.
	 * @return [AI] TRUE if matches this class or a base, else FALSE.
	 */
	MxBool IsA(const char* p_name) const override // vtable+0x10
	{
		return !strcmp(p_name, MxStreamController::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief [AI] Opens a data stream with the specified resource filename.
	 * @param p_filename [AI] Name of the resource file to open (typically .SI).
	 * @return [AI] SUCCESS (0) if source name is set, otherwise other status.
	 * @details [AI] This sets the atom ID with the converted source name for unique logical identification and later lookups.
	 */
	virtual MxResult Open(const char* p_filename); // vtable+0x14

	/**
	 * @brief [AI] Unknown virtual function placeholder.
	 * @param [AI] Undefined arguments.
	 * @return [AI] Always FAILURE.
	 * @details [AI] [AI_SUGGESTED_NAME: Close] Most likely a placeholder for closing or releasing a stream.
	 */
	virtual MxResult VTable0x18(undefined4, undefined4) { return FAILURE; } // vtable+0x18

	/**
	 * @brief [AI] Unknown virtual function placeholder.
	 * @param [AI] Undefined arguments.
	 * @return [AI] Always FAILURE.
	 * @details [AI] [AI_SUGGESTED_NAME: Reset] Placeholder for possible reset/flush operation.
	 */
	virtual MxResult VTable0x1c(undefined4, undefined4) { return FAILURE; } // vtable+0x1c

	/**
	 * @brief [AI] Streams data for the provided action by determining data offset and reading required chunk.
	 * @param p_action [AI] The action requesting a data stream.
	 * @return [AI] Result of the read/streaming operation.
	 * @details [AI] This function performs lookup of the data offset, then executes the data read. Used as a key step in action handling.
	 */
	virtual MxResult VTable0x20(MxDSAction* p_action); // vtable+0x20

	/**
	 * @brief [AI] Matches and processes an action in the "unk0x54" (pending) list and triggers sending to subscribers.
	 * @param p_action [AI] The action to process.
	 * @return [AI] SUCCESS on match and dispatch, FAILURE otherwise.
	 * @details [AI] This removes the matching action from the pending list, updates fields, and initiates streaming.
	 */
	virtual MxResult VTable0x24(MxDSAction* p_action); // vtable+0x24

	/**
	 * @brief [AI] Returns a pointer to the current/active streaming action object.
	 * @return [AI] NULL or pointer to current/active MxDSStreamingAction.
	 * @details [AI] [AI_SUGGESTED_NAME: GetCurrentStreamingAction]
	 */
	virtual MxDSStreamingAction* VTable0x28() { return NULL; } // vtable+0x28

	/**
	 * @brief [AI] Handles allocation and setup of a new streaming action and associated chunk for the action, with prefetch based on buffer value.
	 * @param p_action [AI] Action to stream.
	 * @param p_bufferval [AI] Data offset or buffer location in the stream.
	 * @return [AI] SUCCESS if setup, otherwise FAILURE.
	 */
	virtual MxResult VTable0x2c(MxDSAction* p_action, MxU32 p_bufferval); // vtable+0x2c

	/**
	 * @brief [AI] Removes a completed action from in-progress ("unk0x3c") list and deletes its data block.
	 * @param p_action [AI] Action to remove and finalize.
	 * @return [AI] SUCCESS on removal, FAILURE otherwise.
	 * @details [AI] [AI_SUGGESTED_NAME: FinalizeAction]
	 */
	virtual MxResult VTable0x30(MxDSAction* p_action); // vtable+0x30

	/**
	 * @brief [AI] Adds a subscriber to the list who will receive streaming action data.
	 * @param p_subscriber [AI] Subscriber to add.
	 * @details [AI] Used to register clients/entities interested in data chunks from the stream.
	 */
	void AddSubscriber(MxDSSubscriber* p_subscriber);

	/**
	 * @brief [AI] Removes a previously registered subscriber from the stream notification list.
	 * @param p_subscriber [AI] Subscriber to remove.
	 * @details [AI] Prevents further notifications/callbacks for this subscriber.
	 */
	void RemoveSubscriber(MxDSSubscriber* p_subscriber);

	/**
	 * @brief [AI] Helper function to add a next action data start object for tracking offsets for streaming actions.
	 * @param p_action [AI] Action whose start should be tracked.
	 * @param p_val [AI] Offset value to track.
	 * @return [AI] SUCCESS on success, FAILURE if allocation failed.
	 * @details [AI] [AI_SUGGESTED_NAME: TrackNextActionDataStart]
	 */
	MxResult FUN_100c1800(MxDSAction* p_action, MxU32 p_val);

	/**
	 * @brief [AI] Allocates and inserts a streaming action chunk at a given buffer offset for the supplied action.
	 * @param p_action [AI] Action to stream.
	 * @param p_offset [AI] Buffer offset in the resource stream.
	 * @return [AI] SUCCESS on allocation and insertion, FAILURE otherwise.
	 * @details [AI] [AI_SUGGESTED_NAME: AllocateStreamingAction]
	 */
	MxResult FUN_100c1a00(MxDSAction* p_action, MxU32 p_offset);

	/**
	 * @brief [AI] Returns the presenter associated with a given in-progress streaming action.
	 * @param p_action [AI] Action whose presenter is to be retrieved.
	 * @return [AI] Pointer to MxPresenter if available.
	 * @details [AI] This retrieves a media presenter object linked to a currently executing action, allowing external control or progress check.
	 */
	MxPresenter* FUN_100c1e70(MxDSAction& p_action);

	/**
	 * @brief [AI] Sends a streaming chunk to all current subscribers for the specified action, handling recursive send for multi-actions.
	 * @param p_action [AI] Action to send data for.
	 * @return [AI] SUCCESS on sending to all, FAILURE if allocation fails or one send fails.
	 * @details [AI] Used to propagate action completion/data to all interested game entities or systems.
	 */
	MxResult FUN_100c1f00(MxDSAction* p_action);

	/**
	 * @brief [AI] Checks if the streaming operation for a given object/action has fully stopped and no longer has active subscribers.
	 * @param p_obj [AI] The data object or action to check.
	 * @return [AI] TRUE if fully stopped, otherwise FALSE.
	 * @details [AI] Used to determine when an action and all its branches are completely done processing.
	 */
	MxBool IsStoped(MxDSObject* p_obj);

	/**
	 * @brief [AI] Inserts a clone of the provided action into the pending ("unk0x54") list.
	 * @param p_action [AI] Action to be cloned and inserted.
	 * @return [AI] SUCCESS if insertion is completed, otherwise FAILURE if allocation fails.
	 */
	MxResult InsertActionToList54(MxDSAction* p_action);

	/**
	 * @brief [AI] Finds the corresponding next action data start (offset info) for a streaming action.
	 * @param p_action [AI] Streaming action to lookup data start for.
	 * @return [AI] Corresponding MxNextActionDataStart or NULL if not found.
	 */
	MxNextActionDataStart* FindNextActionDataStartFromStreamingAction(MxDSStreamingAction* p_action);

	/**
	 * @brief [AI] Retrieves the atom ID (unique logical identifier) for this stream controller.
	 * @return [AI] Reference to the atom ID for this stream instance.
	 * @details [AI] The atom ID is derived from source name, allowing stream lookup and management globally.
	 */
	MxAtomId& GetAtom() { return m_atom; }

	/**
	 * @brief [AI] Retrieves the current stream provider abstraction used to access file/memory resources.
	 * @return [AI] Pointer to stream provider.
	 * @details [AI] Allows direct access for custom reading or provider queries.
	 */
	MxStreamProvider* GetProvider() { return m_provider; }

	/**
	 * @brief [AI] Returns the list of actions currently being streamed ("in progress" list).
	 * @return [AI] Reference to in-progress actions list.
	 */
	MxDSObjectList& GetUnk0x3c() { return m_unk0x3c; }

	/**
	 * @brief [AI] Returns the list of actions pending to be streamed ("pending" list).
	 * @return [AI] Reference to list of pending actions.
	 */
	MxDSObjectList& GetUnk0x54() { return m_unk0x54; }

	/**
	 * @brief [AI] Returns the list of current stream subscribers.
	 * @return [AI] Reference to subscriber list.
	 */
	MxDSSubscriberList& GetSubscriberList() { return m_subscribers; }

protected:
	MxCriticalSection m_criticalSection;        ///< @brief [AI] Protects streaming controller state for thread-safety.
	MxAtomId m_atom;                            ///< @brief [AI] Unique identifier for this stream, derived from source/resource name.
	MxStreamProvider* m_provider;               ///< @brief [AI] Stream provider abstraction, handling resource IO (RAM/disk).
	undefined4* m_unk0x2c;                      ///< @brief [AI] Unknown data, likely used for streaming internals or as a metadata pointer.
	MxDSSubscriberList m_subscribers;           ///< @brief [AI] List of current subscribers (listening entities for streamed data).
	MxDSObjectList m_unk0x3c;                   ///< @brief [AI] List of actions currently being processed/streamed ("in progress" actions).
	MxNextActionDataStartList m_nextActionList; ///< @brief [AI] List mapping from streamed object/action to starting offset (used for internal tracking).
	MxDSObjectList m_unk0x54;                   ///< @brief [AI] List of actions queued and ready to be streamed ("pending" actions).
	MxDSAction* m_action0x60;                   ///< @brief [AI] Current action pointer used during processing, moved from pending to active as actions are processed.
};

#endif // MXSTREAMCONTROLLER_H