#ifndef LEGOPATHSTRUCT_H
#define LEGOPATHSTRUCT_H

#include "decomp.h"
#include "mxatom.h"
#include "mxnotificationparam.h"
#include "mxtypes.h"

class LegoPathActor;
class LegoWorld;

/// \class LegoPathStructNotificationParam
/// \brief [AI] Specialized notification parameter used for path structure related events in LEGO Island.
/// \details [AI] Encapsulates an additional data field (`m_data`) and a trigger indicator (`m_trigger`), defining the context of the notification within path struct-triggered events. Used to notify actors and worlds of crossing or entering path triggers.
/// \remark [AI] Used in path transition logic (see LegoPathStruct).
// VTABLE: LEGO1 0x100d6230
// SIZE 0x10
class LegoPathStructNotificationParam : public MxNotificationParam {
public:
	/// \brief [AI] Constructor for LegoPathStructNotificationParam.
	/// \param p_type [AI] The notification type identifier.
	/// \param p_sender [AI] The object (typically a path actor) that sends the notification.
	/// \param p_trigger [AI] A trigger value identifying the kind of trigger (e.g. 'D', 'S', etc.) the notification relates to.
	/// \param p_data [AI] Supplemental data relevant to the trigger (typically a numeric value such as an object or animation ID).
	LegoPathStructNotificationParam(NotificationId p_type, MxCore* p_sender, MxU8 p_trigger, MxS16 p_data)
		: MxNotificationParam()
	{
		m_type = p_type;
		m_sender = p_sender;
		m_data = p_data;
		m_trigger = p_trigger;
	}

	/// \brief [AI] Creates a deep copy of this notification parameter.
	/// \details [AI] Used by the notification system to safely propagate notification parameters.
	/// \return [AI] New instance, cloned from current contents.
	// FUNCTION: LEGO1 0x1001bac0
	MxNotificationParam* Clone() const override
	{
		return new LegoPathStructNotificationParam(m_type, m_sender, m_trigger, m_data);
	} // vtable+0x04

	/// \brief [AI] Returns the trigger type associated with this notification.
	/// \return [AI] The trigger byte (e.g. 'D', 'S').
	// FUNCTION: BETA10 0x10024270
	MxU8 GetTrigger() { return m_trigger; }

	/// \brief [AI] Retrieves the supplemental data associated with the notification.
	/// \return [AI] Notification context data (meaning depends on trigger type).
	// FUNCTION: BETA10 0x100242a0
	MxS16 GetData() { return m_data; }

protected:
	MxS16 m_data;   ///< [AI] Context-dependent data relevant to the trigger event (e.g. object id, animation id).
	MxU8 m_trigger; ///< [AI] Trigger type character - specifies which trigger caused the event (e.g. 'D' for door/passage, 'S' for state).
};

/// \struct LegoPathStructBase
/// \brief [AI] Abstract base describing named, flag-based elements of the LEGO world path system.
/// \details [AI] Used as the base class for path triggers and control points; stores the path struct's name and bitfield flags, including mask bits for various signal and direction properties.
// VTABLE: LEGO1 0x100d7d9c
// SIZE 0x0c
struct LegoPathStructBase {
public:
	/// \brief [AI] Bitmask constants for path struct matching and triggering logic.
	enum {
		c_bit1 = 0x01 << 24, ///< [AI] Bitmask for camera flag/actor trigger logic.
		c_bit2 = 0x02 << 24, ///< [AI] Bitmask for actor direction/state.
		c_bit3 = 0x04 << 24, ///< [AI] Bitmask for direction filter/type.
		c_bit4 = 0x08 << 24, ///< [AI] Bitmask for extra control/state.
		c_bit5 = 0x10 << 24, ///< [AI] Bitmask for direction or branch 'true' (see HandleTrigger) [AI].
		c_bit6 = 0x20 << 24, ///< [AI] Bitmask for direction or branch 'false' (see HandleTrigger) [AI].
		c_bit7 = 0x40 << 24  ///< [AI] Extra bit, typically used for advanced logic/filtering [AI].
	};

	/// \brief [AI] Default constructor. Initializes name pointer to NULL and flags to 0.
	LegoPathStructBase() : m_name(NULL), m_flags(0) {}

	/// \brief [AI] Virtual destructor. Frees the name buffer if allocated.
	// FUNCTION: LEGO1 0x10047420
	virtual ~LegoPathStructBase()
	{
		if (m_name != NULL) {
			delete[] m_name;
		}
	}

	char* m_name;  ///< [AI] Dynamically allocated name for this path struct instance (e.g., a label or trigger identifier).
	MxU32 m_flags; ///< [AI] Bitfield of state and trigger flags for fast matching in trigger logic.
};

/// \class LegoPathStruct
/// \brief [AI] Represents a trigger/control element in the LEGO world's path system, linked logically to the world and supporting complex event logic via triggers.
/// \details [AI] Each path struct can respond to triggers via HandleTrigger, linking actors, the world, notifications, and actions such as animations or music.
/// \remark [AI] Used extensively to define world transitions, script triggers, and area-based world changes.
// VTABLE: LEGO1 0x100d7da0
// SIZE 0x14
class LegoPathStruct : public LegoPathStructBase {
public:
	/// \brief [AI] Enumerated list of recognized path trigger types.
	/// [AI] These map to characters in 'm_name[2]' representing script/trigger actions handled in HandleTrigger().
	enum Trigger {
		c_camAnim = 'C', ///< [AI] Camera animation trigger.
		c_d = 'D',       ///< [AI] Door or passage transition trigger.
		c_e = 'E',       ///< [AI] Event trigger.
		c_g = 'G',       ///< [AI] Generic placeholder trigger.
		c_h = 'H',       ///< [AI] Hide animation trigger.
		c_music = 'M',   ///< [AI] Music control trigger.
		c_s = 'S',       ///< [AI] State change trigger.
		c_w = 'W'        ///< [AI] World notification trigger.
	};

	/// \brief [AI] Default constructor; sets world pointer to NULL.
	// FUNCTION: LEGO1 0x100473a0
	LegoPathStruct() : m_world(NULL) {}

	/// \brief [AI] Destructor.
	// FUNCTION: LEGO1 0x10047470
	~LegoPathStruct() override {}

	/// \brief [AI] Main trigger handler; evaluates flags and name-based script to decide what action to take when an actor enters the struct.
	/// \details [AI] Attempts handling in the default direction (`p_bool` = FALSE), but if no match and re-evaluation flag is set, will call again with opposite branch (`p_bool` = TRUE).
	/// \param p_actor [AI] The actor entering or interacting with the path struct.
	/// \param p_direction [AI] Direction flag relevant to the event context.
	/// \param p_data [AI] Supplemental data from the event (context-dependent: animation id, script id, etc).
	virtual void HandleTrigger(LegoPathActor* p_actor, MxBool p_direction, MxU32 p_data); // vtable+0x04

	/// \brief [AI] Binds a world instance to this path struct for context-specific handling.
	/// \param p_world [AI] Pointer to the LegoWorld using this struct.
	void SetWorld(LegoWorld* p_world) { m_world = p_world; }

	/// \brief [AI] Sets this struct's AtomId for data/action lookup and dispatch.
	/// \param p_atomId [AI] AtomId of the associated SI/script/asset.
	void SetAtomId(const MxAtomId& p_atomId) { m_atomId = p_atomId; }

private:
	/// \brief [AI] Internal trigger handler. Performs the actual match and action logic based on actor/world state and flags.
	/// \param p_actor [AI] The actor invoking the trigger.
	/// \param p_direction [AI] True if forward; false if backward.
	/// \param p_data [AI] Data value from the event (e.g., animation id).
	/// \param p_bool [AI] Secondary evaluation/path (used to differentiate direction/branch).
	/// \return [AI] True if trigger action was successfully processed.
	MxBool HandleTrigger(LegoPathActor* p_actor, MxBool p_direction, MxU32 p_data, MxBool p_bool);

	/// \brief [AI] Helper to either play or stop a corresponding action/animation on a name/data basis.
	/// \param p_name [AI] Action/animation name or identifier.
	/// \param p_data [AI] Numeric supplemental value (e.g. object id).
	/// \param p_bool [AI] If true, play; else (false), stop animation.
	void FUN_1001bc40(const char* p_name, MxU32 p_data, MxBool p_bool);

	/// \brief [AI] Initiates or switches current music according to direction and trigger, using internal mapping logic.
	/// \param p_direction [AI] Contextual direction (area entry/exit).
	/// \param p_data [AI] Music script or track id.
	void PlayMusic(MxBool p_direction, MxU32 p_data);

	LegoWorld* m_world; ///< [AI] The world this path struct is associated with; used for context, event, and lookup.
	MxAtomId m_atomId;  ///< [AI] SI/script identifier for this path struct (used in actions, e.g. PlayCamAnim, etc.).
};

// SYNTHETIC: LEGO1 0x1001bb80
// LegoPathStructNotificationParam::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x1001bbf0
// LegoPathStructNotificationParam::~LegoPathStructNotificationParam

// SYNTHETIC: LEGO1 0x10047440
// LegoPathStructBase::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x10047890
// LegoPathStruct::`vector deleting destructor'

#endif // LEGOPATHSTRUCT_H
