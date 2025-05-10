#ifndef MXOMNICREATEPARAM_H
#define MXOMNICREATEPARAM_H

#include "mxomnicreateflags.h"
#include "mxparam.h"
#include "mxstring.h"
#include "mxvideoparam.h"

#include <windows.h>

// VTABLE: LEGO1 0x100dc218
// VTABLE: BETA10 0x101c1ca8
/**
 * @brief [AI] Encapsulates parameters required to initialize the core Omni engine.
 * @details [AI] MxOmniCreateParam gathers all required data for initializing the game engine including
 * the media path, main window handle, video/graphics settings, and a set of engine behavior flags.
 * It subclasses MxParam for easy passing in generic initialization APIs.
 */
class MxOmniCreateParam : public MxParam {
public:
	/**
	 * @brief [AI] Constructs a parameter set for initializing the Omni engine.
	 * @param p_mediaPath [AI] Path to the media/resources directory.
	 * @param p_windowHandle [AI] Handle to the parent window for rendering output. Expected to be a valid HWND.
	 * @param p_vparam [AI] Reference to a video parameter structure describing video mode and display options.
	 * @param p_flags [AI] Engine creation flags (see MxOmniCreateFlags) determining specific options for engine startup.
	 * @details [AI] This constructor sets all required information for creating and initializing the game engine.
	 */
	MxOmniCreateParam(
		const char* p_mediaPath,
		struct HWND__* p_windowHandle,
		MxVideoParam& p_vparam,
		MxOmniCreateFlags p_flags
	);

	/**
	 * @brief [AI] Access/modify the creation flags.
	 * @return [AI] Reference to internal creation flags for enabling/disabling engine features.
	 */
	MxOmniCreateFlags& CreateFlags() { return this->m_createFlags; }

	/**
	 * @brief [AI] Gets the media/resource directory path.
	 * @return [AI] Immutable reference to the string holding the absolute or relative resource path.
	 */
	const MxString& GetMediaPath() const { return m_mediaPath; }

	/**
	 * @brief [AI] Returns the handle to the rendering window.
	 * @return [AI] Handle (HWND) to the window that the engine will use for output.
	 */
	const HWND GetWindowHandle() const { return m_windowHandle; }

	/**
	 * @brief [AI] Access the detailed video parameter structure (for modification).
	 * @return [AI] Reference to the engine's video parameter configuration (see MxVideoParam).
	 */
	MxVideoParam& GetVideoParam() { return m_videoParam; }

	/**
	 * @brief [AI] Fetch immutable video parameter struct.
	 * @return [AI] Const reference to the engine's video parameter configuration (see MxVideoParam).
	 */
	const MxVideoParam& GetVideoParam() const { return m_videoParam; }

	// SYNTHETIC: LEGO1 0x100b0a70
	// SYNTHETIC: BETA10 0x10132740
	// MxOmniCreateParam::`scalar deleting destructor'

private:
	MxString m_mediaPath;            ///< @brief [AI] Path to resource/media directory used by the engine.
	HWND m_windowHandle;             ///< @brief [AI] Window handle for engine rendering surface (Windows API specific).
	MxVideoParam m_videoParam;       ///< @brief [AI] Parameters governing video configuration, such as resolution and color depth.
	MxOmniCreateFlags m_createFlags; ///< @brief [AI] Engine startup flags enabling/disabling certain initialization options.
};

// SYNTHETIC: ISLE 0x4014b0
// SYNTHETIC: BETA10 0x10132780
// MxOmniCreateParam::~MxOmniCreateParam

#endif // MXOMNICREATEPARAM_H