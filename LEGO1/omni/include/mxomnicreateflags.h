#ifndef MXOMNICREATEFLAGS_H
#define MXOMNICREATEFLAGS_H

#include "mxtypes.h"

// SIZE 0x02
/**
 * @brief [AI] Stores creation flags for initializing core LEGO Island engine subsystems. Used during MxOmni startup to decide which sub-managers to instantiate.
 * @details [AI] Each flag corresponds to a different subsystem (object factory, tickle manager, video manager, sound manager, variable table, etc). These flags are internally used during engine startup to control which management classes are instantiated. FlagBitfield is a bitfield-based utility struct for efficient boolean flag management.
 */
class MxOmniCreateFlags {
public:
	/**
	 * @brief [AI] Initializes all subsystem creation flags to TRUE (i.e., default: all managers enabled). See source constructor for which bit is mapped to which subsystem.
	 */
	MxOmniCreateFlags();

	/**
	 * @brief [AI] Enables or disables the creation of the Object Factory subsystem at startup.
	 * @param p_enable TRUE to enable creation; FALSE to disable. [AI]
	 */
	void CreateObjectFactory(MxBool p_enable) { m_flags1.m_bit0 = p_enable; }

	/**
	 * @brief [AI] Enables or disables the creation of the Tickle Manager subsystem at startup.
	 * @param p_enable TRUE to enable creation; FALSE to disable. [AI]
	 */
	void CreateTickleManager(MxBool p_enable) { m_flags1.m_bit2 = p_enable; }

	/**
	 * @brief [AI] Enables or disables the creation of the Video Manager subsystem at startup.
	 * @param p_enable TRUE to enable creation; FALSE to disable. [AI]
	 */
	void CreateVideoManager(MxBool p_enable) { m_flags1.m_bit4 = p_enable; }

	/**
	 * @brief [AI] Enables or disables the creation of the Sound Manager subsystem at startup.
	 * @param p_enable TRUE to enable creation; FALSE to disable. [AI]
	 */
	void CreateSoundManager(MxBool p_enable) { m_flags1.m_bit5 = p_enable; }

	/**
	 * @brief [AI] Returns whether the Object Factory will be created.
	 */
	const MxBool CreateObjectFactory() const { return m_flags1.m_bit0; }

	/**
	 * @brief [AI] Returns whether the Variable Table will be created.
	 */
	const MxBool CreateVariableTable() const { return m_flags1.m_bit1; }

	/**
	 * @brief [AI] Returns whether the Tickle Manager will be created.
	 */
	const MxBool CreateTickleManager() const { return m_flags1.m_bit2; }

	/**
	 * @brief [AI] Returns whether the Notification Manager will be created.
	 */
	const MxBool CreateNotificationManager() const { return m_flags1.m_bit3; }

	/**
	 * @brief [AI] Returns whether the Video Manager will be created.
	 */
	const MxBool CreateVideoManager() const { return m_flags1.m_bit4; }

	/**
	 * @brief [AI] Returns whether the Sound Manager will be created.
	 */
	const MxBool CreateSoundManager() const { return m_flags1.m_bit5; }

	/**
	 * @brief [AI] Returns whether the Music Manager will be created.
	 */
	const MxBool CreateMusicManager() const { return m_flags1.m_bit6; }

	/**
	 * @brief [AI] Returns whether the Event Manager will be created.
	 */
	const MxBool CreateEventManager() const { return m_flags1.m_bit7; }

	/**
	 * @brief [AI] Returns whether the Timer subsystem will be created.
	 */
	const MxBool CreateTimer() const { return m_flags2.m_bit1; }

	/**
	 * @brief [AI] Returns whether the Streamer subsystem will be created.
	 */
	const MxBool CreateStreamer() const { return m_flags2.m_bit2; }

private:
	/**
	 * @brief [AI] Bitfield flags for core managers (bits 0-7 map to subsystems in the order shown in the constructor).
	 */
	FlagBitfield m_flags1; ///< [AI]
	/**
	 * @brief [AI] Additional bitfield flags, currently only bit 1 (Timer) and bit 2 (Streamer) used.
	 */
	FlagBitfield m_flags2; ///< [AI]
};

#endif // MXOMNICREATEFLAGS_H
