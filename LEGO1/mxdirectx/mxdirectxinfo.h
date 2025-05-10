#ifndef MXDIRECTXINFO_H
#define MXDIRECTXINFO_H

#include "decomp.h"
#include "mxstl/stlcompat.h"

#include <d3d.h>

// SIZE 0x17c
/**
 * @struct DeviceModesInfo
 * @brief [AI] Contains detailed information about a Direct3D device's supported display modes and capabilities.
 * @details [AI] Manages information about a video device, including its GUID, a list of supported video modes (resolutions and color depths),
 * capabilities as reported by DirectDraw, and an unknown pointer possibly related to device state or additional features.
 */
struct DeviceModesInfo {
	/**
	 * @struct Mode
	 * @brief [AI] Represents a specific display mode supported by the device (width, height, bits per pixel).
	 * @details [AI] Used to store and compare supported video modes (resolutions and color depths) for enumeration and selection.
	 */
	struct Mode {
		/**
		 * @brief [AI] Compares two display modes for equality by width, height, and bits per pixel.
		 * @param p_mode The mode to compare against [AI].
		 * @return 1 if the modes are identical; otherwise 0. [AI]
		 */
		int operator==(const Mode& p_mode) const
		{
			return ((width == p_mode.width) && (height == p_mode.height) && (bitsPerPixel == p_mode.bitsPerPixel));
		}

		int width;        ///< [AI] Horizontal resolution in pixels
		int height;       ///< [AI] Vertical resolution in pixels
		int bitsPerPixel; ///< [AI] Color depth (bits per pixel)
	};

	/**
	 * @brief [AI] Constructs an empty DeviceModesInfo with zeroed members.
	 */
	DeviceModesInfo();

	/**
	 * @brief [AI] Destructor. Cleans up owned resources such as m_guid and m_modeArray.
	 */
	~DeviceModesInfo();

	GUID* m_guid;              ///< [AI] GUID of the video device (heap-allocated and owned by this struct).
	Mode* m_modeArray;         ///< [AI] Array of supported display modes; dynamically allocated and owned.
	int m_count;               ///< [AI] Number of display modes in m_modeArray.
	DDCAPS m_ddcaps;           ///< [AI] Capabilities of the DirectDraw device as filled by GetCaps.
	void* m_unk0x178;          ///< [AI] Unknown purpose, possibly additional device state or context. [AI_SUGGESTED_NAME: extraState]

	// SYNTHETIC: BETA10 0x1011c650
	// DeviceModesInfo::`scalar deleting destructor'
};

// SIZE 0xe4
/**
 * @class MxAssignedDevice
 * @brief [AI] Holds assignment and description details for a Direct3D rendering device in use.
 * @details [AI] Encapsulates metadata about a rendering device instance, including its GUID, flags (hardware mode, primary device),
 * device description, and associated DeviceModesInfo for enumerated capabilities.
 */
class MxAssignedDevice {
public:
	enum {
		c_hardwareMode = 0x01,  ///< [AI] Indicates that the device is a hardware rendering device.
		c_primaryDevice = 0x02   ///< [AI] Flags the device as the system's primary device.
	};

	/**
	 * @brief [AI] Initializes an empty MxAssignedDevice structure.
	 */
	MxAssignedDevice();
	/**
	 * @brief [AI] Destructor; deletes associated DeviceModesInfo.
	 */
	~MxAssignedDevice();

	/**
	 * @brief [AI] Returns all flags describing hardware mode/primary device status.
	 */
	unsigned int GetFlags() { return m_flags; }
	/**
	 * @brief [AI] Checks if the device is operating in hardware mode.
	 */
	BOOL GetHardwareMode() { return ((int) m_flags << 31) >> 31; }
	/**
	 * @brief [AI] Accessor for device's current description.
	 */
	D3DDEVICEDESC& GetDesc() { return m_desc; }

	friend class MxDirect3D;

	// SYNTHETIC: BETA10 0x1011c130
	// MxAssignedDevice::`scalar deleting destructor'

private:
	GUID m_guid;                   ///< [AI] GUID uniquely identifying the Direct3D device
	unsigned int m_flags;          ///< [AI] Flags: describes primary/hardware mode status
	D3DDEVICEDESC m_desc;          ///< [AI] Direct3D device description (capabilities)
	DeviceModesInfo* m_deviceInfo; ///< [AI] Pointer to associated device modes information
};

// SIZE 0x1a4
/**
 * @struct Direct3DDeviceInfo
 * @brief [AI] Encapsulates Direct3D device enumeration information and capability structures.
 * @details [AI] Used to describe an individual 3D device discovered during enumeration, including hardware/software details and display strings.
 */
struct Direct3DDeviceInfo {
	/**
	 * @brief [AI] Constructs a zero-initialized Direct3DDeviceInfo instance.
	 */
	Direct3DDeviceInfo() {}
	/**
	 * @brief [AI] Destructor; frees owned resources such as GUID and strings.
	 */
	~Direct3DDeviceInfo();
	/**
	 * @brief [AI] Initializes and assigns all information for a Direct3D device.
	 * @param p_guid GUID pointer describing the device. [AI]
	 * @param p_deviceDesc Description string as reported by the API. [AI]
	 * @param p_deviceName Untranslated device name or identifier. [AI]
	 * @param p_HWDesc Capabilities in hardware mode. [AI]
	 * @param p_HELDesc Capabilities via Microsoft software emulation. [AI]
	 */
	Direct3DDeviceInfo(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);

	/**
	 * @brief [AI] Initializes instance with device GUID, description strings, and capability structures.
	 * @param p_guid GUID pointer describing the device. [AI]
	 * @param p_deviceDesc Description string as reported by the API. [AI]
	 * @param p_deviceName Untranslated device name. [AI]
	 * @param p_HWDesc Capabilities in hardware mode. [AI]
	 * @param p_HELDesc Capabilities via software (HEL). [AI]
	 */
	void Initialize(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);

	LPGUID m_guid;           ///< [AI] GUID uniquely identifying this 3D device. [AI]
	char* m_deviceDesc;      ///< [AI] API-provided textual description of device (owned string).
	char* m_deviceName;      ///< [AI] Unlocalized device name/identifier (owned string).
	D3DDEVICEDESC m_HWDesc;  ///< [AI] Hardware Direct3D device capability description.
	D3DDEVICEDESC m_HELDesc; ///< [AI] Software (HEL) emulation device capability description.

	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator==(Direct3DDeviceInfo) const { return 0; }
	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator<(Direct3DDeviceInfo) const { return 0; }
};

// SIZE 0x0c
/**
 * @struct MxDisplayMode
 * @brief [AI] Represents a display mode with specific resolution and color depth.
 * @details [AI] Used when enumerating available output modes for a graphics driver.
 */
struct MxDisplayMode {
	/**
	 * @brief [AI] Default constructor. Leaves values uninitialized.
	 */
	MxDisplayMode() {}
	/**
	 * @brief [AI] Initialize the display mode with width, height, and color depth.
	 * @param p_width Width in pixels. [AI]
	 * @param p_height Height in pixels. [AI]
	 * @param p_bitsPerPixel Bits per pixel (color depth). [AI]
	 */
	MxDisplayMode(DWORD p_width, DWORD p_height, DWORD p_bitsPerPixel)
	{
		m_width = p_width;
		m_height = p_height;
		m_bitsPerPixel = p_bitsPerPixel;
	}

	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator==(MxDisplayMode) const { return 0; }
	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator<(MxDisplayMode) const { return 0; }

	DWORD m_width;        ///< [AI] Width in pixels
	DWORD m_height;       ///< [AI] Height in pixels
	DWORD m_bitsPerPixel; ///< [AI] Color depth (bits per pixel)
};

// SIZE 0x190
/**
 * @struct MxDriver
 * @brief [AI] Holds data about a DirectDraw driver including devices and supported display modes.
 * @details [AI] Used during device enumeration to accumulate hardware and software information, capabilities, and available display modes.
 */
struct MxDriver {
	/**
	 * @brief [AI] Constructs an empty MxDriver structure.
	 */
	MxDriver() {}
	/**
	 * @brief [AI] Destructor; frees GUID and owned strings.
	 */
	~MxDriver();
	/**
	 * @brief [AI] Initializes the driver with only its GUID.
	 * @param p_guid GUID (may be null). [AI]
	 */
	MxDriver(LPGUID p_guid);
	/**
	 * @brief [AI] Initializes the driver with GUID, description, and name.
	 * @param p_guid GUID (may be null). [AI]
	 * @param p_driverDesc Driver description string (may be null). [AI]
	 * @param p_driverName Name string (may be null). [AI]
	 */
	MxDriver(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName);

	/**
	 * @brief [AI] Initializes or resets the driver's GUID and strings.
	 * @param p_guid GUID (may be null). [AI]
	 * @param p_driverDesc Driver description string. [AI]
	 * @param p_driverName Name string. [AI]
	 */
	void Init(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName);

	LPGUID m_guid;                      ///< [AI] GUID for this DirectDraw driver (heap-allocated and owned).
	char* m_driverDesc;                 ///< [AI] Driver description string (owned).
	char* m_driverName;                 ///< [AI] Driver name/identifier string (owned).
	DDCAPS m_ddCaps;                    ///< [AI] Capabilities structure as reported by the driver.
	list<Direct3DDeviceInfo> m_devices; ///< [AI] List of all Direct3D devices provided by this driver.
	list<MxDisplayMode> m_displayModes; ///< [AI] List of all display modes reported by the driver.

	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator==(MxDriver) const { return 0; }
	/**
	 * @brief [AI] Comparison operator placeholder: returns 0, not implemented.
	 */
	int operator<(MxDriver) const { return 0; }
};

// VTABLE: CONFIG 0x00406000
// VTABLE: LEGO1 0x100db814
// VTABLE: BETA10 0x101c1b0c
// SIZE 0x14
/**
 * @class MxDeviceEnumerate
 * @brief [AI] Enumerates DirectDraw/Direct3D drivers, devices, and display modes on the system.
 * @details [AI] Used to collect and expose lists of graphics drivers, 3D devices, and supported modes for device selection and initialization.
 */
class MxDeviceEnumerate {
public:
	/**
	 * @brief [AI] Constructs an MxDeviceEnumerate object, sets initialized flag to FALSE.
	 */
	MxDeviceEnumerate();

	/**
	 * @brief [AI] Destructor. No dynamic resource management.
	 */
	~MxDeviceEnumerate();

	/**
	 * @brief [AI] Begins enumeration of DirectDraw drivers, their devices, and available display modes.
	 * @details [AI] This will populate m_list with all available drivers/devices/modes and set m_initialized to TRUE if successful.
	 * @return 0 on success, -1 if already initialized or on error [AI].
	 */
	virtual int DoEnumerate(); // vtable+0x00

	/**
	 * @brief [AI] Callback for enumerating a single DirectDraw driver.
	 * @param p_guid GUID of driver. [AI]
	 * @param p_driverDesc Description string from DirectDraw. [AI]
	 * @param p_driverName Name string from DirectDraw. [AI]
	 * @return TRUE (continue), used during enumeration. [AI]
	 */
	BOOL EnumDirectDrawCallback(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName);

	/**
	 * @brief [AI] Callback for each display mode in a driver.
	 * @param p_ddsd Surface description structure for the display mode. [AI]
	 * @return DDENUMRET_OK. [AI]
	 */
	HRESULT EnumDisplayModesCallback(LPDDSURFACEDESC p_ddsd);

	/**
	 * @brief [AI] Callback for enumerating 3D devices on a driver.
	 * @param p_guid Device GUID. [AI]
	 * @param p_deviceDesc Description string from the API. [AI]
	 * @param p_deviceName Name string from the API. [AI]
	 * @param p_HWDesc Hardware capabilities. [AI]
	 * @param p_HELDesc HEL (software) capabilities. [AI]
	 * @return DDENUMRET_OK. [AI]
	 */
	HRESULT EnumDevicesCallback(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc
	);
	/**
	 * @brief [AI] Converts a DirectDraw/Direct3D HRESULT enumeration error to a human-readable string.
	 * @param p_error HRESULT error value returned during enumeration. [AI]
	 * @return Human-readable error description. [AI]
	 */
	const char* EnumerateErrorToString(HRESULT p_error);

	/**
	 * @brief [AI] Utility for formatting and outputting error/debug strings.
	 * @param ... printf-style format/varargs. [AI]
	 */
	static void BuildErrorString(const char*, ...);

	/**
	 * @brief [AI] Static thunk callback suitable for passing to DirectDrawEnumerate.
	 * @param p_guid GUID pointer to the driver. [AI]
	 * @param p_driverDesc Description string provided by DirectDraw. [AI]
	 * @param p_driverName Name string provided by DirectDraw. [AI]
	 * @param p_context pointer to this instance. [AI]
	 * @return TRUE; always continues enumeration. [AI]
	 */
	static BOOL CALLBACK
	DirectDrawEnumerateCallback(LPGUID p_guid, LPSTR p_driverDesc, LPSTR p_driverName, LPVOID p_context);

	/**
	 * @brief [AI] Static thunk callback for enumerating display modes during driver enumeration.
	 * @param p_ddsd Surface description for the display mode. [AI]
	 * @param p_context pointer to this instance. [AI]
	 * @return DDENUMRET_OK. [AI]
	 */
	static HRESULT CALLBACK DisplayModesEnumerateCallback(LPDDSURFACEDESC p_ddsd, LPVOID p_context);

	/**
	 * @brief [AI] Static thunk callback for enumerating 3D devices within a driver.
	 * @param p_guid Device GUID. [AI]
	 * @param p_deviceDesc Device description string. [AI]
	 * @param p_deviceName Device name string. [AI]
	 * @param p_HWDesc Hardware device capabilities. [AI]
	 * @param p_HELDesc Software (HEL) capabilities. [AI]
	 * @param p_context Pointer to this instance. [AI]
	 * @return DDENUMRET_OK. [AI]
	 */
	static HRESULT CALLBACK DevicesEnumerateCallback(
		LPGUID p_guid,
		LPSTR p_deviceDesc,
		LPSTR p_deviceName,
		LPD3DDEVICEDESC p_HWDesc,
		LPD3DDEVICEDESC p_HELDesc,
		LPVOID p_context
	);

	friend class MxDirect3D;

	/**
	 * @brief [AI] Returns a const reference to the list of enumerated drivers/devices/modes.
	 * @return Const list reference. [AI]
	 */
	const list<MxDriver>& GetDriverList() const { return m_list; }

	/**
	 * @struct GUID4
	 * @brief [AI] Utility structure for GUID comparison.
	 * @details [AI] Used for abstract GUID operations not using the Windows GUID struct. Contains four int32 members.
	 */
	struct GUID4 {
		int m_data1; ///< [AI]
		int m_data2; ///< [AI]
		int m_data3; ///< [AI]
		int m_data4; ///< [AI]

		/**
		 * @brief [AI] Compares two GUID4s for complete equality.
		 * @param p_a First GUID4. [AI]
		 * @param p_b Second GUID4. [AI]
		 * @return TRUE if identical, FALSE otherwise. [AI]
		 */
		static unsigned char Compare(const GUID4& p_a, const GUID4& p_b)
		{
			return p_a.m_data1 == p_b.m_data1 && p_a.m_data2 == p_b.m_data2 && p_a.m_data3 == p_b.m_data3 &&
				   p_a.m_data4 == p_b.m_data4;
		}
	};

	/**
	 * @brief [AI] Checks if the enumeration has already been performed.
	 * @return TRUE if initialized/enumerated, FALSE if not. [AI]
	 */
	unsigned char IsInitialized() const { return m_initialized; }

protected:
	list<MxDriver> m_list;       ///< [AI] List of all discovered DirectDraw drivers and their device/mode info.
	unsigned char m_initialized; ///< [AI] Set TRUE after successful enumeration to prevent redundant operations.
};

// TEMPLATE: BETA10 0x1011c1b0
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::iterator::operator*

// TEMPLATE: BETA10 0x1011c200
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::iterator::operator++

// TEMPLATE: BETA10 0x1011c290
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::begin

// TEMPLATE: BETA10 0x1011c300
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::end

// TEMPLATE: BETA10 0x1011c4d0
// list<MxDriver,allocator<MxDriver> >::iterator::operator*

// TEMPLATE: BETA10 0x1011c520
// list<MxDriver,allocator<MxDriver> >::iterator::operator++

// TEMPLATE: BETA10 0x1011c560
// list<MxDriver,allocator<MxDriver> >::iterator::operator++

// TEMPLATE: BETA10 0x1011c590
// list<MxDriver,allocator<MxDriver> >::_Acc::_Next

// TEMPLATE: BETA10 0x1011c5b0
// list<MxDriver,allocator<MxDriver> >::begin

// TEMPLATE: BETA10 0x1011c5f0
// list<MxDriver,allocator<MxDriver> >::iterator::iterator

// TEMPLATE: BETA10 0x1011c620
// list<MxDriver,allocator<MxDriver> >::end

// TEMPLATE: BETA10 0x1011c690
// ??9@YAHABViterator@?$list@UMxDriver@@V?$allocator@UMxDriver@@@@@@0@Z

// TEMPLATE: BETA10 0x1011c770
// ??9@YAHABViterator@?$list@UDirect3DDeviceInfo@@V?$allocator@UDirect3DDeviceInfo@@@@@@0@Z

// TEMPLATE: BETA10 0x1011d3a0
// list<MxDriver,allocator<MxDriver> >::size

// TEMPLATE: BETA10 0x1011d3c0
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::size

// TEMPLATE: BETA10 0x1011d3e0
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::erase

// TEMPLATE: BETA10 0x1011d570
// list<MxDriver,allocator<MxDriver> >::erase

// TEMPLATE: BETA10 0x1011d6a0
// list<MxDriver,allocator<MxDriver> >::_Freenode

// TEMPLATE: BETA10 0x1011d700
// list<MxDriver,allocator<MxDriver> >::front

// TEMPLATE: BETA10 0x1011f750
// list<MxDriver,allocator<MxDriver> >::back

// TEMPLATE: BETA10 0x1011f780
// list<MxDriver,allocator<MxDriver> >::iterator::operator--

// TEMPLATE: BETA10 0x1011f7b0
// list<MxDriver,allocator<MxDriver> >::push_back

// TEMPLATE: BETA10 0x1011f830
// list<MxDriver,allocator<MxDriver> >::insert

// TEMPLATE: BETA10 0x1011f960
// list<MxDisplayMode,allocator<MxDisplayMode> >::push_back

// TEMPLATE: BETA10 0x1011fa90
// list<Direct3DDeviceInfo,allocator<Direct3DDeviceInfo> >::push_back

#endif // MXDIRECTXINFO_H
