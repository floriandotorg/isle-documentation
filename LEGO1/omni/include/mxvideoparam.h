#ifndef MXVIDEOPARAM_H
#define MXVIDEOPARAM_H

#include "compat.h"
#include "mxgeometry.h"
#include "mxtypes.h"
#include "mxvideoparamflags.h"

#include <ddraw.h>

class MxPalette;

/// @brief [AI] Video parameter configuration for display and rendering, encapsulates resolution, palette, backbuffers, display flags, and device identifier.
class MxVideoParam {
public:
	/// @brief [AI] Construct MxVideoParam with default screen rectangle (640x480), no palette, zero backbuffers, default flags, and null device name.
	MxVideoParam();

	/// @brief [AI] Construct MxVideoParam specifying display rectangle, color palette, number of back buffers, and display flags.
	/// @param p_rect Rectangle dimensions for the video output. [AI]
	/// @param p_palette Palette to use for video output. [AI]
	/// @param p_backBuffers Number of requested back buffers for double/triple buffering. [AI]
	/// @param p_flags Control flags such as windowed/fullscreen mode, hardware/software rendering etc. [AI]
	__declspec(dllexport)
		MxVideoParam(MxRect32& p_rect, MxPalette* p_palette, MxULong p_backBuffers, MxVideoParamFlags& p_flags);

	/// @brief [AI] Copy constructor, performs a deep copy of all fields including a duplicate of the device name string.
	/// @param p_videoParam Source video parameter object to copy. [AI]
	MxVideoParam(MxVideoParam& p_videoParam);

	/// @brief [AI] Destructor, frees device name memory if used. [AI]
	~MxVideoParam();

	/// @brief [AI] Set the device name/id for this video parameter (e.g., a specific display adapter), making a deep copy of the input string.
	/// @param p_deviceId Null-terminated string with device identifier; if NULL device will be unset. [AI]
	void SetDeviceName(char* p_deviceId);

	/// @brief [AI] Assignment operator, performs deep copy (including device name string) of another instance.
	/// @param p_videoParam Source object to copy from. [AI]
	/// @return Reference to this object after assignment. [AI]
	MxVideoParam& operator=(const MxVideoParam& p_videoParam);

	/// @brief [AI] Access the video parameter flags (windowed/fullscreen, rendering mode, etc).
	/// @return Modifiable reference to the flags object. [AI]
	MxVideoParamFlags& Flags() { return m_flags; }

	/// @brief [AI] Get the rectangle specifying the display dimensions and screen area.
	/// @return Modifiable reference to the rectangle. [AI]
	MxRect32& GetRect() { return m_rect; }

	/// @brief [AI] Get the palette used for rendering (may be NULL if not set).
	/// @return Pointer to the palette used currently. [AI]
	MxPalette* GetPalette() { return m_palette; }

	/// @brief [AI] Assign the palette pointer (color indexing) for the video mode.
	/// @param p_palette Palette instance to assign. [AI]
	void SetPalette(MxPalette* p_palette) { m_palette = p_palette; }

	/// @brief [AI] Get a pointer to the internal device name string (may be NULL).
	/// @return Pointer to the null-terminated device id string, e.g. a DirectDraw device. [AI]
	char* GetDeviceName() { return m_deviceId; }

	/// @brief [AI] Get the number of backbuffers requested for this display mode.
	MxU32 GetBackBuffers() { return m_backBuffers; }

	/// @brief [AI] Set the desired number of backbuffers (triple/double buffering).
	/// @param p_backBuffers Desired backbuffer count. [AI]
	void SetBackBuffers(MxU32 p_backBuffers) { m_backBuffers = p_backBuffers; }

private:
	MxRect32 m_rect;           ///< @brief [AI] Screen area and dimensions for the video device [AI]
	MxPalette* m_palette;      ///< @brief [AI] Pointer to the palette object (for indexed color modes) [AI]
	MxU32 m_backBuffers;       ///< @brief [AI] Number of backbuffers for page flipping / synchronization [AI]
	MxVideoParamFlags m_flags; ///< @brief [AI] Flags governing rendering mode, screen layout, etc. [AI]
	int m_unk0x1c;             ///< @brief [AI] Unknown; always initialized to zero. [AI]
	char* m_deviceId;          ///< @brief [AI] Null-terminated string identifying the target rendering device. [AI]
};

#endif // MXVIDEOPARAM_H
