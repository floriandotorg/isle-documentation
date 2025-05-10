#ifndef LEGODXINFO_H
#define LEGODXINFO_H

#include "mxdirectxinfo.h"

// VTABLE: CONFIG 0x4060e4
// VTABLE: LEGO1 0x100d9cc8
// VTABLE: BETA10 0x101befb4
// SIZE 0x14

/**
 * @brief [AI] Enumerates and manages Direct3D devices and drivers for the LEGO Island engine.
 * 
 * LegoDeviceEnumerate inherits from MxDeviceEnumerate, providing extended functionality to identify,
 * process, and verify Direct3D devices and drivers required for engine rendering. This includes hardware
 * capability checks (such as MMX and CPUID support), device string parsing/formatting, and display mode support checks.
 *
 * @details [AI]
 * This class holds a list of available Direct3D drivers (MxDriver) with their associated device information.
 * It provides functions to search, filter, and format driver or device descriptors, and supports pruning
 * the list according to hardware or mode requirements needed by the LEGO Island engine renderer.
 *
 */
class LegoDeviceEnumerate : public MxDeviceEnumerate {
public:
	/**
	 * @brief [AI] Parses a device string identifier and locates the matching device entry.
	 * @param p_deviceId Device identifier string in the format: "<driverIndex> 0x<X> 0x<Y> 0x<Z> 0x<W>" [AI]
	 * @return Device index if found, -1 on failure. [AI]
	 */
	int ParseDeviceName(const char* p_deviceId);

	/**
	 * @brief [AI] Returns the index of the device matching the given GUID and driver number.
	 * @param p_deviceNum Driver index; may be -1 to search all drivers. [AI]
	 * @param p_guid GUID of the device. [AI]
	 * @return Index of device within the device enumeration, or -1 if not found. [AI]
	 */
	int ProcessDeviceBytes(int p_deviceNum, GUID& p_guid);

	/**
	 * @brief [AI] Outputs pointers to the MxDriver and Direct3DDeviceInfo for the given device index.
	 * @param p_deviceNum Global device list index. [AI]
	 * @param p_driver Output: Pointer to the matched MxDriver. [AI]
	 * @param p_device Output: Pointer to the matched Direct3DDeviceInfo. [AI]
	 * @return 0 on success, -1 if not found. [AI]
	 */
	int GetDevice(int p_deviceNum, MxDriver*& p_driver, Direct3DDeviceInfo*& p_device);

	/**
	 * @brief [AI] Formats and serializes a device identification string for a given driver/device.
	 * @param p_buffer Output buffer for the formatted device string. [AI]
	 * @param p_ddInfo Pointer to the relevant MxDriver (DirectDraw info). [AI]
	 * @param p_d3dInfo Pointer to the relevant Direct3DDeviceInfo. [AI]
	 * @return 0 on success, -1 if the driver not found. [AI]
	 */
	int FormatDeviceName(char* p_buffer, const MxDriver* p_ddInfo, const Direct3DDeviceInfo* p_d3dInfo) const;

	/**
	 * @brief [AI] Formats device identification string for the device at a specific global index (Beta10-specific).
	 * @param p_idx Index of the device in the global list. [AI]
	 * @param p_buffer Output buffer for the formatted string. [AI]
	 * @return 0 on success, -1 if index is invalid. [AI]
	 */
	int BETA_1011cc65(int p_idx, char* p_buffer);

	/**
	 * @brief [AI] Finds and returns the preferred device index that supports required features. [AI]
	 * @return Device index for first device meeting requirements, or -1 if none is found. [AI]
	 */
	int FUN_1009d0d0();

	/**
	 * @brief [AI] Checks if the CPU supports MMX instructions.
	 * @details [AI] Uses platform-specific assembly instructions to detect MMX feature availability.
	 * @return 1 if MMX is supported, 0 otherwise. [AI]
	 */
	static int SupportsMMX();

	/**
	 * @brief [AI] Checks if the CPU supports CPUID instruction.
	 * @details [AI] Uses platform-specific assembly instructions to detect CPUID availability.
	 * @return 1 if CPUID is supported, 0 otherwise. [AI]
	 */
	static int SupportsCPUID();

	/**
	 * @brief [AI] Prunes the enumeration to only include devices/drivers that support the required display mode and features.
	 * @return 0 on success, -1 if no valid devices remain. [AI]
	 */
	int FUN_1009d210();

	/**
	 * @brief [AI] Checks if a driver supports a 640x480 display mode in 8bpp or 16bpp (needed by LEGO Island).
	 * @param p_driver The driver to check. [AI]
	 * @return TRUE if supported, FALSE otherwise. [AI]
	 */
	unsigned char DriverSupportsRequiredDisplayMode(MxDriver& p_driver);

	/**
	 * @brief [AI] Checks if a device supports required rendering features (Z-buffer, perspective, HW support, etc).
	 * @param p_device The device to validate. [AI]
	 * @return TRUE if device is adequate, FALSE otherwise. [AI]
	 */
	unsigned char FUN_1009d3d0(Direct3DDeviceInfo& p_device);

	// SYNTHETIC: BETA10 0x100d8d10
	// LegoDeviceEnumerate::LegoDeviceEnumerate

	// SYNTHETIC: LEGO1 0x1007b590
	// SYNTHETIC: BETA10 0x100d8da0
	// LegoDeviceEnumerate::~LegoDeviceEnumerate
};

#endif // LEGODXINFO_H
