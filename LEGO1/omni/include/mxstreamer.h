#ifndef MXSTREAMER_H
#define MXSTREAMER_H

#include "decomp.h"
#include "mxcore.h"
#include "mxmemorypool.h"
#include "mxnotificationparam.h"
#include "mxstl/stlcompat.h"
#include "mxstreamcontroller.h"
#include "mxtypes.h"

#include <assert.h>

class MxDSObject;

/// Memory pool for 64-byte blocks, 22 blocks total. [AI]
typedef MxMemoryPool<64, 22> MxMemoryPool64; // [AI]
/// Memory pool for 128-byte blocks, 2 blocks total. [AI]
typedef MxMemoryPool<128, 2> MxMemoryPool128; // [AI]

/**
 * @brief Streamer notification param for streaming events in MxStreamer [AI]
 * @details Extends MxNotificationParam by providing a reference to the affected MxStreamController
 * for notification message passing when streaming operations change. [AI]
 * @see MxNotificationParam [AI]
 */
class MxStreamerNotification : public MxNotificationParam {
public:
	/**
	 * @brief [AI] Create a streamer notification with a controller reference.
	 * @param p_type Type of notification [AI]
	 * @param p_sender Sender object [AI]
	 * @param p_ctrlr Affected stream controller pointer [AI]
	 */
	MxStreamerNotification(NotificationId p_type, MxCore* p_sender, MxStreamController* p_ctrlr)
		: MxNotificationParam(p_type, p_sender)
	{
		m_controller = p_ctrlr;
	}

	/**
	 * @brief [AI] Clone this notification param. Used for notification delivery/copying.
	 * @return Pointer to a new clone of the notification parameter [AI]
	 */
	MxNotificationParam* Clone() const override;

	/**
	 * @brief [AI] Retrieve the stream controller associated with this notification.
	 * @return The stream controller affected by the notification [AI]
	 */
	MxStreamController* GetController() { return m_controller; }

private:
	MxStreamController* m_controller; ///< Stream controller relevant to this notification [AI]
};

/**
 * @brief Streams and manages media data, handles memory pools for RAM/disk streaming [AI]
 * @details The main subsystem for handling streaming of SI file (script or media) data to various controller objects.
 * Implements a registry of open stream controllers, supports RAM/disk streams, manages notification events
 * for streaming changes, and provides block-based memory pooling for efficiency in allocations. [AI]
 *
 * @see MxStreamController, MxRAMStreamController, MxDiskStreamController, MxNotificationManager [AI]
 */
class MxStreamer : public MxCore {
public:
	/**
	 * @brief Available streaming resource loading modes. [AI]
	 */
	enum OpenMode {
		e_diskStream = 0, ///< Load streaming resource from disk [AI]
		e_RAMStream        ///< Load streaming resource fully to RAM [AI]
	};

	/**
	 * @brief Construct a streamer and register it for notifications. [AI]
	 */
	MxStreamer();
	/**
	 * @brief Destructor—Stops all stream controllers and unregisters from notification manager. [AI]
	 */
	~MxStreamer() override;

	/**
	 * @brief Open a stream, returning a controller for further access [AI]
	 * @details Depending on the open mode, allocates a new Disk or RAM controller and opens the stream. [AI]
	 * @param p_name Name/identifier of the resource [AI]
	 * @param p_openMode 0 = disk, 1 = RAM [AI]
	 * @return Pointer to a stream controller if successful, otherwise NULL [AI]
	 */
	MxStreamController* Open(const char* p_name, MxU16 p_openMode);

	/**
	 * @brief Close a named stream and remove its controller from the open list [AI]
	 * @details Calls proper resource disposal on the controller if it is stopped.
	 * If not stopped, issues a notification instead. [AI]
	 * @param p_name Name/key for the stream to close [AI]
	 * @return SUCCESS (0) or FAILURE (nonzero) [AI]
	 */
	MxLong Close(const char* p_name);

	/**
	 * @brief Handle notifications, including deferred controller deletion [AI]
	 * @details Responds to MxStreamerNotification notifications. [AI]
	 * @param p_param Notification parameter (should be MxStreamerNotification) [AI]
	 * @return Always 0 [AI]
	 */
	MxLong Notify(MxParam& p_param) override;

	/**
	 * @brief Return the class name string at runtime. [AI]
	 */
	const char* ClassName() const override
	{
		return "MxStreamer";
	}

	/**
	 * @brief Query for run-time type information by class name. [AI]
	 * @param p_name The class name to check [AI]
	 * @return TRUE if the class is MxStreamer or a base; otherwise FALSE [AI]
	 */
	MxBool IsA(const char* p_name) const override
	{
		return !strcmp(p_name, MxStreamer::ClassName()) || MxCore::IsA(p_name);
	}

	/**
	 * @brief Allocate memory pools needed for streaming operation. [AI]
	 * @details Initializes the block allocators for 64 and 128 byte memory blocks. [AI]
	 * @return SUCCESS if allocation passed, FAILURE if not [AI]
	 */
	virtual MxResult Create();

	/**
	 * @brief Check stream state for a dsObject's Atom ID. [AI]
	 * @param p_dsObject The SI object to check against open streams [AI]
	 * @return TRUE if the stream is stopped or does not exist, else controller's stopped state [AI]
	 */
	MxBool FUN_100b9b30(MxDSObject& p_dsObject);

	/**
	 * @brief Search for and return an open stream controller with a matching name. [AI]
	 * @param p_name Name/Atom of the stream to find [AI]
	 * @return Pointer to stream controller if found, else NULL [AI]
	 */
	MxStreamController* GetOpenStream(const char* p_name);

	/**
	 * @brief Internal: Delegate stream operation on MxDSAction to a DiskStreamController if present. [AI]
	 * @param p_action Data Action referencing the target resource [AI]
	 */
	void FUN_100b98f0(MxDSAction* p_action);

	/**
	 * @brief Add a controller to the open list, asserting if already present. [AI]
	 * @details Performs an O(n) search to ensure no duplicates before insertion. [AI]
	 * @param p_stream Controller to add [AI]
	 * @return SUCCESS if added, else FAILURE [AI]
	 */
	MxResult AddStreamControllerToOpenList(MxStreamController* p_stream);

	/**
	 * @brief Internal: Calls stream controller's specific command for action execution. [AI]
	 * @param p_action Action to process [AI]
	 * @return FAILURE if action or controller invalid, controller result otherwise [AI]
	 */
	MxResult FUN_100b99b0(MxDSAction* p_action);

	/**
	 * @brief Ask all controllers to remove a DS Action's object. [AI]
	 * @param p_dsAction Data action whose object to remove [AI]
	 * @return FAILURE if not found/none matched, else controller operation result [AI]
	 */
	MxResult DeleteObject(MxDSAction* p_dsAction);

	/**
	 * @brief Allocate a temporary memory block from the streamer pool. [AI]
	 * @details Allocates 64- or 128-byte blocks from specialized fixed-size pools to improve locality and reduce 
	 * fragmentation. [AI]
	 * @param p_blockSize Required block size [AI]
	 * @return Pointer to the memory block, or NULL if not valid size [AI]
	 */
	MxU8* GetMemoryBlock(MxU32 p_blockSize)
	{
		switch (p_blockSize) {
		case 0x40:
			return m_pool64.Get();

		case 0x80:
			return m_pool128.Get();

		default:
			assert("Invalid block size for memory pool" == NULL);
			break;
		}

		return NULL;
	}

	/**
	 * @brief Return a previously-acquired memory block to the pool. [AI]
	 * @param p_block Memory block pointer [AI]
	 * @param p_blockSize Size of block (must match exact pool size) [AI]
	 */
	void ReleaseMemoryBlock(MxU8* p_block, MxU32 p_blockSize)
	{
		switch (p_blockSize) {
		case 0x40:
			m_pool64.Release(p_block);
			break;

		case 0x80:
			m_pool128.Release(p_block);
			break;

		default:
			assert("Invalid block size for memory pool" == NULL);
			break;
		}
	}

private:
	list<MxStreamController*> m_controllers; ///< Open stream controllers (RAM and disk streams) [AI]
	MxMemoryPool64 m_pool64;                 ///< Fixed-size 64-byte block allocator [AI]
	MxMemoryPool128 m_pool128;               ///< Fixed-size 128-byte block allocator [AI]
};

#endif // MXSTREAMER_H
