#include "compat.h"
#include "decomp.h"
#include "tgl/tgl.h"

#include <d3drm.h>

#ifdef DIRECTX5_SDK
typedef DWORD LPD3DRM_APPDATA; ///< @brief [AI] Application data type varies by DirectX version [AI]
#else
typedef LPVOID LPD3DRM_APPDATA; ///< @brief [AI] Application data type varies by DirectX version [AI]
#endif

// Forward declare D3D types
struct IDirect3DRM2; ///< @brief [AI] Forward declaration for Direct3DRM2 interface [AI]
struct IDirect3DRMDevice2; ///< @brief [AI] Forward declaration for Direct3DRMDevice2 interface [AI]
struct IDirect3DRMViewport; ///< @brief [AI] Forward declaration for Direct3DRMViewport interface [AI]
struct IDirect3DRMFrame2; ///< @brief [AI] Forward declaration for Direct3DRMFrame2 interface [AI]
struct IDirect3DRMMesh; ///< @brief [AI] Forward declaration for Direct3DRMMesh interface [AI]
struct IDirect3DRMMeshBuilder; ///< @brief [AI] Forward declaration for Direct3DRMMeshBuilder interface [AI]
struct IDirect3DRMTexture; ///< @brief [AI] Forward declaration for Direct3DRMTexture interface [AI]

namespace TglImpl
{

using namespace Tgl;

// Utility function used by implementations
// FUNCTION: BETA10 0x10169cf0
/**
 * @brief Returns a Tgl Result value for HRESULT [AI]
 *
 * @param result HRESULT value [AI]
 * @return Returns Success if SUCCEEDED(result) is true, Error otherwise [AI]
 */
inline Result ResultVal(HRESULT result)
{
	return SUCCEEDED(result) ? Success : Error;
}

// Forward declare implementations
class RendererImpl; ///< @brief [AI] Implements Tgl::Renderer using Direct3D Retained Mode [AI]
class DeviceImpl; ///< @brief [AI] Implements Tgl::Device for Direct3DRMDevice2 [AI]
class ViewImpl; ///< @brief [AI] Implements Tgl::View with Direct3DRMViewport [AI]
class LightImpl; ///< @brief [AI] Implements Tgl::Light using Direct3DRMFrame2 [AI]
class CameraImpl; ///< @brief [AI] Implements Tgl::Camera using Direct3DRMFrame2 [AI]
class GroupImpl; ///< @brief [AI] Implements Tgl::Group using Direct3DRMFrame2 [AI]
class MeshImpl; ///< @brief [AI] Implements Tgl::Mesh; stores mesh/geometry data [AI]
class TextureImpl; ///< @brief [AI] Implements Tgl::Texture wrapping Direct3DRMTexture [AI]
class MeshBuilderImpl; ///< @brief [AI] Implements Tgl::MeshBuilder; facilitates mesh construction [AI]

/**
 * @class RendererImpl
 * @brief [AI] Implements the Tgl::Renderer interface with Direct3DRM2 as backend. Handles creation of rendering devices, cameras, lights, and scene graph objects. [AI]
 */
class RendererImpl : public Renderer {
public:
	// FUNCTION: BETA10 0x10169a20
	RendererImpl() : m_data(0) {} ///< @brief [AI] Initializes renderer data to null. [AI]

	// FUNCTION: BETA10 0x10169d20
	~RendererImpl() override { Destroy(); } ///< @brief [AI] Destructor ensures Direct3DRM2 resources are freed. [AI]

	/**
	 * @brief Returns implementation-specific data pointer (Direct3DRM2) [AI]
	 * @return void pointer to implementation data [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Creates a device from DirectDraw configuration [AI]
	 * @param data Device configuration for DirectDraw [AI]
	 * @return Newly created Device [AI]
	 */
	Device* CreateDevice(const DeviceDirectDrawCreateData&) override;

	/**
	 * @brief Creates a device from Direct3D configuration [AI]
	 * @param data Device configuration for Direct3D [AI]
	 * @return Newly created Device [AI]
	 */
	Device* CreateDevice(const DeviceDirect3DCreateData&) override;

	// vtable+0x10
	/**
	 * @brief Creates a view using provided device and camera [AI]
	 * @param Device Rendering device [AI]
	 * @param Camera Camera to view scene through [AI]
	 * @param x Viewport x position [AI]
	 * @param y Viewport y position [AI]
	 * @param width Viewport width [AI]
	 * @param height Viewport height [AI]
	 * @return Newly created View [AI]
	 */
	View* CreateView(
		const Device*,
		const Camera*,
		unsigned long x,
		unsigned long y,
		unsigned long width,
		unsigned long height
	) override;

	/**
	 * @brief Creates a camera object [AI]
	 * @return Newly created Camera [AI]
	 */
	Camera* CreateCamera() override;

	/**
	 * @brief Creates a light source with color and type [AI]
	 * @param type Light type (ambient, point, etc.) [AI]
	 * @param r Red component [AI]
	 * @param g Green component [AI]
	 * @param b Blue component [AI]
	 * @return Newly created Light [AI]
	 */
	Light* CreateLight(LightType, float r, float g, float b) override;

	/**
	 * @brief Creates a new group under parent group [AI]
	 * @param pParent Parent group [AI]
	 * @return Newly created Group [AI]
	 */
	Group* CreateGroup(const Group* pParent) override;

	// vtable+0x20
	/**
	 * @brief Creates a mesh builder for assembling geometry [AI]
	 * @return Newly created MeshBuilder [AI]
	 */
	MeshBuilder* CreateMeshBuilder() override;

	/**
	 * @brief Creates a texture from buffer data and palette [AI]
	 * @param width Texture width [AI]
	 * @param height Texture height [AI]
	 * @param bitsPerTexel Bits per texel [AI]
	 * @param pTexels Texel data pointer [AI]
	 * @param pTexelsArePersistent Flag for texel data persistence [AI]
	 * @param paletteEntryCount Number of palette entries [AI]
	 * @param pEntries Palette entries [AI]
	 * @return Newly created Texture [AI]
	 */
	Texture* CreateTexture(
		int width,
		int height,
		int bitsPerTexel,
		const void* pTexels,
		int pTexelsArePersistent,
		int paletteEntryCount,
		const PaletteEntry* pEntries
	) override;

	/**
	 * @brief Creates an empty texture [AI]
	 * @return Newly created Texture [AI]
	 */
	Texture* CreateTexture() override;

	/**
	 * @brief Sets the number of default texture shades used [AI]
	 * @param value Number of default shades [AI]
	 */
	Result SetTextureDefaultShadeCount(unsigned long) override;

	// vtable+0x30
	/**
	 * @brief Sets the number of default texture colors used [AI]
	 * @param value Number of default colors [AI]
	 */
	Result SetTextureDefaultColorCount(unsigned long) override;

	/**
	 * @brief Creates a Direct3DRM texture from a DirectDraw surface [AI]
	 * @param pSurface Pointer to DirectDraw surface [AI]
	 * @param pTexture2 Output pointer for created Direct3DRM texture [AI]
	 * @return HRESULT from Direct3DRM [AI]
	 */
	HRESULT CreateTextureFromSurface(LPDIRECTDRAWSURFACE pSurface, LPDIRECT3DRMTEXTURE2* pTexture2)
	{
		return m_data->CreateTextureFromSurface(pSurface, pTexture2);
	}

	typedef IDirect3DRM2* RendererDataType; ///< @brief [AI] Internal data type for renderer (Direct3DRM2*) [AI]

	/**
	 * @brief Retrieves the Direct3DRM2 pointer (const) [AI]
	 * @return Reference to Direct3DRM2 pointer [AI]
	 */
	const RendererDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x10174c10
	/**
	 * @brief Retrieves the Direct3DRM2 pointer (mutable) [AI]
	 * @return Reference to Direct3DRM2 pointer [AI]
	 */
	RendererDataType& ImplementationData() { return m_data; }

public:
	/**
	 * @brief Initializes Direct3DRM2 [AI]
	 */
	inline Result Create();
	/**
	 * @brief Frees Direct3DRM2 resources [AI]
	 */
	inline void Destroy();
	/**
	 * @brief Helper for light creation with explicit output parameter [AI]
	 * @param type LightType [AI]
	 * @param r Red [AI]
	 * @param g Green [AI]
	 * @param b Blue [AI]
	 * @param rLight Output LightImpl [AI]
	 */
	inline Result CreateLight(LightType type, float r, float g, float b, LightImpl& rLight);
	/**
	 * @brief Helper for view creation [AI]
	 * @param rDevice DeviceImpl [AI]
	 * @param rCamera CameraImpl [AI]
	 * @param x X position [AI]
	 * @param y Y position [AI]
	 * @param width Width [AI]
	 * @param height Height [AI]
	 * @param rView Output ViewImpl [AI]
	 */
	inline Result CreateView(
		const DeviceImpl& rDevice,
		const CameraImpl& rCamera,
		unsigned long x,
		unsigned long y,
		unsigned long width,
		unsigned long height,
		ViewImpl& rView
	);
	/**
	 * @brief Helper for mesh builder creation [AI]
	 * @param rMesh Output MeshBuilderImpl [AI]
	 */
	inline Result CreateMeshBuilder(MeshBuilderImpl& rMesh);
	/**
	 * @brief Helper for camera creation [AI]
	 * @param rCamera Output CameraImpl [AI]
	 */
	inline Result CreateCamera(CameraImpl& rCamera);
	/**
	 * @brief Helper for texture creation (empty) [AI]
	 * @param rTexture Output TextureImpl [AI]
	 */
	inline Result CreateTexture(TextureImpl& rTexture);
	/**
	 * @brief Helper for texture creation with buffer [AI]
	 * @param rTexture Output TextureImpl [AI]
	 * @param width Texture width [AI]
	 * @param height Texture height [AI]
	 * @param bitsPerTexel Bits per texel [AI]
	 * @param pTexels Buffer pointer [AI]
	 * @param texelsArePersistent Persistence flag [AI]
	 * @param paletteEntryCount Palette entries [AI]
	 * @param pEntries Palette data [AI]
	 */
	inline Result CreateTexture(
		TextureImpl& rTexture,
		int width,
		int height,
		int bitsPerTexel,
		const void* pTexels,
		int texelsArePersistent,
		int paletteEntryCount,
		const PaletteEntry* pEntries
	);
	/**
	 * @brief Helper for device creation (Direct3D) [AI]
	 * @param rCreateData Creation params [AI]
	 * @param rDevice Output DeviceImpl [AI]
	 */
	inline Result CreateDevice(const DeviceDirect3DCreateData& rCreateData, DeviceImpl& rDevice);
	/**
	 * @brief Helper for device creation (DirectDraw) [AI]
	 * @param rCreateData Creation params [AI]
	 * @param rDevice Output DeviceImpl [AI]
	 */
	inline Result CreateDevice(const DeviceDirectDrawCreateData& rCreateData, DeviceImpl& rDevice);

private:
	RendererDataType m_data; ///< @brief [AI] Holds Direct3DRM2 pointer [AI]
};

extern IDirect3DRM2* g_pD3DRM; ///< @brief [AI] Global pointer to Direct3DRM2, used to manage lifecycle [AI]

// FUNCTION: BETA10 0x1016dd20
/**
 * @brief Destroys a Direct3DRM2 renderer object, manages global pointer [AI]
 * @param pRenderer Pointer to renderer to destroy [AI]
 */
inline void RendererDestroy(IDirect3DRM2* pRenderer)
{
	int refCount = pRenderer->Release();
	if (refCount <= 0) {
		g_pD3DRM = NULL;
	}
}

// Inlined only
// FUNCTION: BETA10 0x1016dce0
/**
 * @brief Destroy and cleanup Direct3DRM2 resources for the renderer [AI]
 */
void RendererImpl::Destroy()
{
	if (m_data) {
		RendererDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class DeviceImpl
 * @brief [AI] Implements the Tgl::Device interface, encapsulates Direct3DRMDevice2 and provides rendering device operations. [AI]
 */
class DeviceImpl : public Device {
public:
	// FUNCTION: BETA10 0x1016b2e0
	DeviceImpl() : m_data(0) {} ///< @brief [AI] Initializes device data to null [AI]

	// FUNCTION: BETA10 0x1016dd80
	~DeviceImpl() override { Destroy(); } ///< @brief [AI] Destructor releases resources [AI]

	/**
	 * @brief Returns Direct3DRMDevice2 pointer as a generic implementation data pointer [AI]
	 * @return Implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Returns the current device width in pixels [AI]
	 */
	unsigned long GetWidth() override;

	/**
	 * @brief Returns the current device height in pixels [AI]
	 */
	unsigned long GetHeight() override;

	// vtable+0x10
	/**
	 * @brief Sets the color model used for rendering [AI]
	 * @param model Color model (RGB, etc.) [AI]
	 */
	Result SetColorModel(ColorModel) override;

	/**
	 * @brief Sets the shading model (flat, Gouraud, etc.) [AI]
	 * @param model Shading model [AI]
	 */
	Result SetShadingModel(ShadingModel) override;

	/**
	 * @brief Sets number of shades [AI]
	 * @param count Shade count [AI]
	 */
	Result SetShadeCount(unsigned long) override;

	/**
	 * @brief Enables or disables dithering [AI]
	 * @param value Dither enabled or not [AI]
	 */
	Result SetDither(int) override;

	// vtable+0x20
	/**
	 * @brief Submits any pending updates to the device [AI]
	 */
	Result Update() override;

	/**
	 * @brief Handles application/window activation event [AI]
	 * @param wParam Activation parameter (from WM_ACTIVATE) [AI]
	 */
	void HandleActivate(WORD) override;

	/**
	 * @brief Handles window paint event [AI]
	 * @param hdc Device context handle [AI]
	 */
	void HandlePaint(HDC) override;

	typedef IDirect3DRMDevice2* DeviceDataType; ///< @brief [AI] Internal data type for device (Direct3DRMDevice2*) [AI]

	// FUNCTION: BETA10 0x101708e0
	/**
	 * @brief Retrieves the device pointer (const) [AI]
	 * @return Reference to Direct3DRMDevice2 pointer [AI]
	 */
	const DeviceDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x100d9540
	/**
	 * @brief Retrieves the device pointer (mutable) [AI]
	 * @return Reference to Direct3DRMDevice2 pointer [AI]
	 */
	DeviceDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Replaces the implementation pointer [AI]
	 * @param device Direct3DRMDevice2* to assign [AI]
	 */
	void SetImplementationData(IDirect3DRMDevice2* device) { m_data = device; }

	/**
	 * @brief Frees device resources [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

private:
	DeviceDataType m_data; ///< @brief [AI] Holds Direct3DRMDevice2 pointer [AI]
};

// FUNCTION: BETA10 0x101708c0
/**
 * @brief Releases (decreases ref count of) a Direct3DRMDevice2 [AI]
 * @param pDevice Device to release [AI]
 */
inline void DeviceDestroy(IDirect3DRMDevice2* pDevice)
{
	pDevice->Release();
}

// FUNCTION: BETA10 0x10170880
/**
 * @brief Frees Direct3DRMDevice2 resources [AI]
 */
void DeviceImpl::Destroy()
{
	if (m_data) {
		DeviceDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class ViewImpl
 * @brief [AI] Implementation of Tgl::View backed by Direct3DRMViewport, handles scene rendering, picking, and camera control. [AI]
 */
class ViewImpl : public View {
public:
	// FUNCTION: BETA10 0x1016b360
	ViewImpl() : m_data(0) {} ///< @brief [AI] Initializes viewport pointer [AI]

	// FUNCTION: BETA10 0x1016e5d0
	~ViewImpl() override { Destroy(); } ///< @brief [AI] Cleans up viewport on destruction [AI]

	/**
	 * @brief Returns Direct3DRMViewport implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Adds a light to this view [AI]
	 * @param Light Pointer to Tgl::Light [AI]
	 */
	Result Add(const Light*) override;

	/**
	 * @brief Removes a light from this view [AI]
	 * @param Light Pointer to Tgl::Light [AI]
	 */
	Result Remove(const Light*) override;

	// vtable+0x10
	/**
	 * @brief Sets the active camera for this view [AI]
	 * @param Camera Pointer to Tgl::Camera [AI]
	 */
	Result SetCamera(const Camera*) override;

	/**
	 * @brief Sets the camera projection type (perspective/orthographic) [AI]
	 * @param type Projection type [AI]
	 */
	Result SetProjection(ProjectionType) override;

	/**
	 * @brief Sets the view frustum parameters [AI]
	 * @param frontClippingDistance Near clipping plane [AI]
	 * @param backClippingDistance Far clipping plane [AI]
	 * @param degrees Field of view or orthographic width [AI]
	 */
	Result SetFrustrum(float frontClippingDistance, float backClippingDistance, float degrees) override;

	/**
	 * @brief Sets background color [AI]
	 * @param r Red [AI]
	 * @param g Green [AI]
	 * @param b Blue [AI]
	 */
	Result SetBackgroundColor(float r, float g, float b) override;

	// vtable+0x20
	/**
	 * @brief Gets the background color [AI]
	 * @param r Red output [AI]
	 * @param g Green output [AI]
	 * @param b Blue output [AI]
	 */
	Result GetBackgroundColor(float* r, float* g, float* b) override;

	/**
	 * @brief Clears the view [AI]
	 */
	Result Clear() override;

	/**
	 * @brief Renders the provided scene/group [AI]
	 * @param Group Group (scene root) [AI]
	 */
	Result Render(const Group*) override;

	/**
	 * @brief Forces an update/redraw of specified rectangle [AI]
	 * @param x X position [AI]
	 * @param y Y position [AI]
	 * @param width Width [AI]
	 * @param height Height [AI]
	 */
	Result ForceUpdate(unsigned long x, unsigned long y, unsigned long width, unsigned long height) override;

	// vtable+0x30
	/**
	 * @brief Converts a world coordinate to screen space [AI]
	 * @param world Input world coordinates [AI]
	 * @param screen Output screen coordinates [AI]
	 */
	Result TransformWorldToScreen(const float world[3], float screen[4]) override;

	/**
	 * @brief Converts screen coordinates to world space [AI]
	 * @param screen Input screen coordinates [AI]
	 * @param world Output world coordinates [AI]
	 */
	Result TransformScreenToWorld(const float screen[4], float world[3]) override;

	/**
	 * @brief Picks objects in the view by screen coordinate [AI]
	 * @param x Screen X coord [AI]
	 * @param y Screen Y coord [AI]
	 * @param ppGroupsToPickFrom List of groups to pick from [AI]
	 * @param groupsToPickFromCount Count of groups to pick from [AI]
	 * @param rppPickedGroups Reference to list of picked groups [AI]
	 * @param rPickedGroupCount Reference to number of picked groups [AI]
	 */
	Result Pick(
		unsigned long x,
		unsigned long y,
		const Group** ppGroupsToPickFrom,
		int groupsToPickFromCount,
		const Group**& rppPickedGroups,
		int& rPickedGroupCount
	) override;

	typedef IDirect3DRMViewport* ViewDataType; ///< @brief [AI] Internal pointer to Direct3DRMViewport [AI]

	/**
	 * @brief Gets internal viewport pointer, const [AI]
	 */
	const ViewDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x101711c0
	/**
	 * @brief Gets internal viewport pointer, mutable [AI]
	 */
	ViewDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Sets internal viewport pointer [AI]
	 * @param viewport Viewport to set [AI]
	 */
	void SetImplementationData(IDirect3DRMViewport* viewport) { m_data = viewport; }

	/**
	 * @brief Associates user app data with a viewport/frame [AI]
	 * @param d3drm Direct3DRM2 pointer [AI]
	 * @param viewport Viewport pointer [AI]
	 * @param frame Associated frame [AI]
	 */
	static Result ViewportCreateAppData(IDirect3DRM2*, IDirect3DRMViewport*, IDirect3DRMFrame2*);

	/**
	 * @brief Frees viewport resources [AI]
	 */
	inline void Destroy();

	/**
	 * @brief Adds a light using impl object [AI]
	 * @param rLight LightImpl reference [AI]
	 */
	Result Add(const LightImpl& rLight);

	/**
	 * @brief Removes a light using impl object [AI]
	 * @param rLight LightImpl reference [AI]
	 */
	Result Remove(const LightImpl& rLight);

	/**
	 * @brief Sets active camera using impl [AI]
	 * @param rCamera CameraImpl reference [AI]
	 */
	Result SetCamera(const CameraImpl& rCamera);

	/**
	 * @brief Renders a group using impl [AI]
	 * @param rScene GroupImpl reference [AI]
	 */
	Result Render(const GroupImpl& rScene);

	/**
	 * @brief Picks group using impl objects [AI]
	 */
	Result Pick(
		unsigned long x,
		unsigned long y,
		const GroupImpl** ppGroupsToPickFrom,
		int groupsToPickFromCount,
		const Group**& rppPickedGroups,
		int& rPickedGroupCount
	);

	friend class RendererImpl;

private:
	ViewDataType m_data; ///< @brief [AI] Holds Direct3DRMViewport pointer [AI]
};

// FUNCTION: BETA10 0x101711a0
/**
 * @brief Releases a Direct3DRMViewport [AI]
 * @param pView Viewport to release [AI]
 */
inline void ViewDestroy(IDirect3DRMViewport* pView)
{
	pView->Release();
}

// FUNCTION: BETA10 0x10171160
/**
 * @brief Frees Direct3DRMViewport resources [AI]
 */
void ViewImpl::Destroy()
{
	if (m_data) {
		ViewDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class CameraImpl
 * @brief [AI] Implementation of Tgl::Camera, wraps a Direct3DRMFrame2 and provides transformation management [AI]
 */
class CameraImpl : public Camera {
public:
	// FUNCTION: BETA10 0x1016b3e0
	CameraImpl() : m_data(0) {} ///< @brief [AI] Initializes frame pointer [AI]

	// FUNCTION: BETA10 0x1016f200
	~CameraImpl() override { Destroy(); } ///< @brief [AI] Cleans up frame on destruction [AI]

	/**
	 * @brief Returns Direct3DRMFrame2 implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Sets the camera transformation matrix [AI]
	 * @param Transform 4x4 transformation matrix [AI]
	 */
	Result SetTransformation(FloatMatrix4&) override;

	typedef IDirect3DRMFrame2* CameraDataType; ///< @brief [AI] Internal pointer to Direct3DRMFrame2 [AI]

	// FUNCTION: BETA10 0x10170960
	/**
	 * @brief Retrieves camera pointer (const) [AI]
	 */
	const CameraDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x10170980
	/**
	 * @brief Retrieves camera pointer (mutable) [AI]
	 */
	CameraDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Frees the camera/frame resources [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

private:
	CameraDataType m_data; ///< @brief [AI] Holds Direct3DRMFrame2 pointer [AI]
};

// FUNCTION: BETA10 0x10170940
/**
 * @brief Releases (decreases ref count) for a Direct3DRMFrame2 [AI]
 * @param pFrame Frame pointer to be released [AI]
 */
inline void CameraDestroy(IDirect3DRMFrame2* pFrame)
{
	pFrame->Release();
}

// FUNCTION: BETA10 0x10170900
/**
 * @brief Frees the camera/frame resources if managed [AI]
 */
void CameraImpl::Destroy()
{
	if (m_data) {
		CameraDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class LightImpl
 * @brief [AI] Implementation of Tgl::Light, wraps a Direct3DRMFrame2 and color data [AI]
 */
class LightImpl : public Light {
public:
	// FUNCTION: BETA10 0x1016b460
	LightImpl() : m_data(0) {} ///< @brief [AI] Initializes light frame pointer [AI]

	// FUNCTION: BETA10 0x1016f5c0
	~LightImpl() override { Destroy(); } ///< @brief [AI] Frees resources on destruction [AI]

	/**
	 * @brief Returns Direct3DRMFrame2 implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Sets transformation matrix for the light [AI]
	 * @param Transform 4x4 transformation matrix [AI]
	 */
	Result SetTransformation(FloatMatrix4&) override;

	/**
	 * @brief Sets color for the light [AI]
	 * @param r Red [AI]
	 * @param g Green [AI]
	 * @param b Blue [AI]
	 */
	Result SetColor(float r, float g, float b) override;

	typedef IDirect3DRMFrame2* LightDataType; ///< @brief [AI] Internal pointer to Direct3DRMFrame2 [AI]

	// FUNCTION: BETA10 0x10171b90
	/**
	 * @brief Retrieves light pointer (const) [AI]
	 */
	const LightDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x10171240
	/**
	 * @brief Retrieves light pointer (mutable) [AI]
	 */
	LightDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Frees resources for the light [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

private:
	LightDataType m_data; ///< @brief [AI] Holds Direct3DRMFrame2 pointer [AI]
};

// FUNCTION: BETA10 0x10171220
/**
 * @brief Releases a Direct3DRMFrame2 used as light [AI]
 * @param pLight Light frame pointer [AI]
 */
inline void LightDestroy(IDirect3DRMFrame2* pLight)
{
	pLight->Release();
}

// FUNCTION: BETA10 0x101711e0
/**
 * @brief Frees resources for the light if managed [AI]
 */
void LightImpl::Destroy()
{
	if (m_data) {
		LightDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class MeshImpl
 * @brief [AI] Implementation of Tgl::Mesh, manages a mesh object and geometry data with group index [AI]
 */
class MeshImpl : public Mesh {
public:
	// FUNCTION: BETA10 0x1016f970
	MeshImpl() : m_data(0) {} ///< @brief [AI] Initializes mesh data pointer [AI]

	// FUNCTION: BETA10 0x10170460
	~MeshImpl() override { Destroy(); } ///< @brief [AI] Frees resources on destruction [AI]

	/**
	 * @brief Returns pointer to mesh implementation data [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Sets the color for this mesh [AI]
	 * @param r Red [AI]
	 * @param g Green [AI]
	 * @param b Blue [AI]
	 * @param a Alpha [AI]
	 */
	Result SetColor(float r, float g, float b, float a) override;

	/**
	 * @brief Assigns a texture to this mesh [AI]
	 * @param Texture Tgl::Texture pointer [AI]
	 */
	Result SetTexture(const Texture*) override;

	// vtable+0x10
	/**
	 * @brief Retrieves the texture currently assigned to this mesh [AI]
	 * @param[out] Reference to Texture pointer [AI]
	 */
	Result GetTexture(Texture*&) override;

	/**
	 * @brief Sets the mesh texturing mode (UV/cylindrical/etc.) [AI]
	 * @param mode Mapping mode [AI]
	 */
	Result SetTextureMappingMode(TextureMappingMode) override;

	/**
	 * @brief Sets mesh shading model (flat, Gouraud, etc.) [AI]
	 * @param model ShadingModel [AI]
	 */
	Result SetShadingModel(ShadingModel) override;

	/**
	 * @brief Creates a deep copy of this mesh using a mesh builder [AI]
	 * @param MeshBuilder MeshBuilder pointer [AI]
	 * @return New Mesh [AI]
	 */
	Mesh* DeepClone(MeshBuilder*) override;

	// vtable+0x20
	/**
	 * @brief Creates a shallow copy of this mesh using a mesh builder [AI]
	 * @param MeshBuilder MeshBuilder pointer [AI]
	 * @return New Mesh [AI]
	 */
	Mesh* ShallowClone(MeshBuilder*) override;

	/**
	 * @struct MeshData
	 * @brief [AI] Holds D3DRMMesh pointer and group index for referencing geometry [AI]
	 */
	struct MeshData {
		IDirect3DRMMesh* groupMesh; ///< @brief [AI] D3DRM mesh pointer [AI]
		D3DRMGROUPINDEX groupIndex; ///< @brief [AI] Index within mesh group [AI]
	};

	typedef MeshData* MeshDataType; ///< @brief [AI] Pointer to mesh data struct [AI]

	/**
	 * @brief Gets mesh implementation data (const) [AI]
	 */
	const MeshDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x10171b70
	/**
	 * @brief Gets mesh implementation data (mutable) [AI]
	 */
	MeshDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Frees mesh and associated data [AI]
	 */
	inline void Destroy();

	/**
	 * @brief Deep clones the mesh using an explicit MeshBuilderImpl [AI]
	 * @param rMesh MeshBuilderImpl reference [AI]
	 */
	inline Mesh* DeepClone(const MeshBuilderImpl& rMesh);

	friend class RendererImpl;

private:
	MeshDataType m_data; ///< @brief [AI] Holds pointers to mesh and group index [AI]
};

// FUNCTION: BETA10 0x10171b40
/**
 * @brief Destroys mesh data object [AI]
 * @param pMesh MeshData pointer to destroy [AI]
 */
inline void MeshDestroy(MeshImpl::MeshDataType pMesh)
{
	delete pMesh;
}

// FUNCTION: BETA10 0x10171b00
/**
 * @brief Frees mesh and disassociates group index [AI]
 */
void MeshImpl::Destroy()
{
	if (m_data) {
		MeshDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class GroupImpl
 * @brief [AI] Implementation of Tgl::Group, wraps a Direct3DRMFrame2 and provides scene graph and transformation features [AI]
 */
class GroupImpl : public Group {
public:
	// FUNCTION: BETA10 0x1016a240
	GroupImpl() : m_data(0) {} ///< @brief [AI] Initializes frame/group to null [AI]

	// FUNCTION: BETA10 0x1016a410
	~GroupImpl() override { Destroy(); } ///< @brief [AI] Cleanly releases resources on destruction [AI]

	/**
	 * @brief Returns group implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Sets transformation matrix for group [AI]
	 * @param transform 4x4 transform [AI]
	 */
	Result SetTransformation(FloatMatrix4&) override;

	/**
	 * @brief Sets color and alpha for the group [AI]
	 * @param r Red [AI]
	 * @param g Green [AI]
	 * @param b Blue [AI]
	 * @param a Alpha [AI]
	 */
	Result SetColor(float r, float g, float b, float a) override;

	// vtable+0x10
	/**
	 * @brief Sets texture for all group geometry [AI]
	 * @param Texture pointer [AI]
	 */
	Result SetTexture(const Texture*) override;

	/**
	 * @brief Gets texture from group [AI]
	 * @param[out] Reference to Texture pointer [AI]
	 */
	Result GetTexture(Texture*&) override;

	/**
	 * @brief Sets usage/staging of group as a material [AI]
	 * @param mode Material mode [AI]
	 */
	Result SetMaterialMode(MaterialMode) override;

	/**
	 * @brief Adds a child group [AI]
	 * @param Group pointer to add [AI]
	 */
	Result Add(const Group*) override;

	// vtable+0x20
	/**
	 * @brief Adds mesh builder to group [AI]
	 * @param MeshBuilder pointer to add [AI]
	 */
	Result Add(const MeshBuilder*) override;

	/**
	 * @brief Removes a child group [AI]
	 * @param Group pointer to remove [AI]
	 */
	Result Remove(const Group*) override;

	/**
	 * @brief Removes a mesh builder from group [AI]
	 * @param MeshBuilder pointer to remove [AI]
	 */
	Result Remove(const MeshBuilder*) override;

	/**
	 * @brief Removes all contained groups and meshes [AI]
	 */
	Result RemoveAll() override;

	// vtable+0x30
	/**
	 * @brief Returns bounding box in world space [AI]
	 * @param p_min Output min vector [AI]
	 * @param p_max Output max vector [AI]
	 */
	Result Bounds(D3DVECTOR* p_min, D3DVECTOR* p_max) override;

	typedef IDirect3DRMFrame2* GroupDataType; ///< @brief [AI] Internal pointer to Direct3DRMFrame2 [AI]

	// FUNCTION: BETA10 0x1016fc20
	/**
	 * @brief Gets internal group/frame pointer, const [AI]
	 */
	const GroupDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x1016fce0
	/**
	 * @brief Gets internal group/frame pointer, mutable [AI]
	 */
	GroupDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Frees resources for group, such as child groups and geometry [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

private:
	GroupDataType m_data; ///< @brief [AI] Holds Direct3DRMFrame2 pointer representing group [AI]
};

// FUNCTION: BETA10 0x1016c2b0
/**
 * @brief Releases group/frame resource from Direct3DRM [AI]
 * @param pGroup Frame pointer to release [AI]
 */
inline void GroupDestroy(IDirect3DRMFrame2* pGroup)
{
	pGroup->Release();
}

// FUNCTION: BETA10 0x1016c270
/**
 * @brief Frees group resources and nullifies pointer [AI]
 */
void GroupImpl::Destroy()
{
	if (m_data) {
		GroupDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class MeshBuilderImpl
 * @brief [AI] Implements Tgl::MeshBuilder, manages mesh construction and provides the interface for creating geometry buffers [AI]
 */
class MeshBuilderImpl : public MeshBuilder {
public:
	// FUNCTION: BETA10 0x1016b260
	MeshBuilderImpl() : m_data(0) {} ///< @brief [AI] Initializes mesh builder to null [AI]

	// FUNCTION: BETA10 0x1016c7e0
	~MeshBuilderImpl() override { Destroy(); } ///< @brief [AI] Frees mesh building resources on destruction [AI]

	/**
	 * @brief Returns mesh builder implementation pointer [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Creates a mesh from arrays of data (positions, normals, etc.) [AI]
	 * @param faceCount Number of faces [AI]
	 * @param vertexCount Number of vertices [AI]
	 * @param pPositions Array of vertex positions [AI]
	 * @param pNormals Array of normals [AI]
	 * @param pTextureCoordinates Array of texture coordinates [AI]
	 * @param pFaceIndices Face indices [AI]
	 * @param pTextureIndices Texture indices per face [AI]
	 * @param shadingModel Shading model to use [AI]
	 * @return New Mesh pointer [AI]
	 */
	Mesh* CreateMesh(
		unsigned long faceCount,
		unsigned long vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned long (*pFaceIndices)[3],
		unsigned long (*pTextureIndices)[3],
		ShadingModel shadingModel
	) override;

	/**
	 * @brief Gets the bounding box of the constructed mesh [AI]
	 * @param min Minimum extents output [AI]
	 * @param max Maximum extents output [AI]
	 */
	Result GetBoundingBox(float min[3], float max[3]) const override;

	// vtable+0x10
	/**
	 * @brief Clones the mesh builder [AI]
	 * @return MeshBuilder clone [AI]
	 */
	MeshBuilder* Clone() override;

	typedef IDirect3DRMMesh* MeshBuilderDataType; ///< @brief [AI] Internal pointer to Direct3DRMMesh [AI]

	// FUNCTION: BETA10 0x10170420
	/**
	 * @brief Gets mesh builder pointer (const) [AI]
	 */
	const MeshBuilderDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x10170440
	/**
	 * @brief Gets mesh builder pointer (mutable) [AI]
	 */
	MeshBuilderDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Frees mesh builder resources [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

private:
	/**
	 * @brief Creates a mesh in-place in the provided MeshImpl object [AI]
	 * @param pMeshImpl Output mesh implementation [AI]
	 * @param faceCount Number of faces [AI]
	 * @param vertexCount Number of vertices [AI]
	 * @param pPositions Vertex positions [AI]
	 * @param pNormals Normal vectors [AI]
	 * @param pTextureCoordinates Texture coordinates [AI]
	 * @param pFaceIndices Face indices [AI]
	 * @param pTextureIndices Texture indices [AI]
	 * @param shadingModel Shading model [AI]
	 */
	inline Result CreateMeshImpl(
		MeshImpl* pMeshImpl,
		unsigned long faceCount,
		unsigned long vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned long (*pFaceIndices)[3],
		unsigned long (*pTextureIndices)[3],
		ShadingModel shadingModel
	);

	MeshBuilderDataType m_data; ///< @brief [AI] Holds Direct3DRMMesh pointer [AI]
};

// FUNCTION: BETA10 0x10170390
/**
 * @brief Releases a Direct3DRMMesh [AI]
 * @param pMeshBuilder Mesh object to release [AI]
 */
inline void MeshBuilderDestroy(IDirect3DRMMesh* pMeshBuilder)
{
	pMeshBuilder->Release();
}

// FUNCTION: BETA10 0x10170350
/**
 * @brief Frees mesh builder object if owned [AI]
 */
void MeshBuilderImpl::Destroy()
{
	if (m_data) {
		MeshBuilderDestroy(m_data);
		m_data = NULL;
	}
}

/**
 * @class TglD3DRMIMAGE
 * @brief [AI] Simple wrapper for D3DRMIMAGE; manages pixel buffer and palette for Direct3DRM textures [AI]
 */
class TglD3DRMIMAGE {
public:
	/**
	 * @brief Constructs an image buffer for use with Direct3DRM textures [AI]
	 * @param width Image width [AI]
	 * @param height Image height [AI]
	 * @param depth Bits per pixel [AI]
	 * @param pBuffer Pixel buffer pointer [AI]
	 * @param useBuffer Whether to use provided buffer (1) or allocate [AI]
	 * @param paletteSize Palette entries [AI]
	 * @param pEntries Palette data [AI]
	 */
	TglD3DRMIMAGE(
		int width,
		int height,
		int depth,
		void* pBuffer,
		int useBuffer,
		int paletteSize,
		PaletteEntry* pEntries
	);
	~TglD3DRMIMAGE() { Destroy(); } ///< @brief [AI] Destroys and frees buffer/palette if needed [AI]

	/**
	 * @brief Creates or reallocates image buffer as necessary [AI]
	 * @param width Width [AI]
	 * @param height Height [AI]
	 * @param depth Depth [AI]
	 * @param pBuffer Buffer data [AI]
	 * @param useBuffer Client or local allocation [AI]
	 */
	Result CreateBuffer(int width, int height, int depth, void* pBuffer, int useBuffer);

	/**
	 * @brief Destroys any buffers/palette managed by the image [AI]
	 */
	void Destroy();

	/**
	 * @brief Writes pixel rows into texture [AI]
	 * @param y Row to start [AI]
	 * @param height Number of rows to fill [AI]
	 * @param content Pixel data [AI]
	 */
	Result FillRowsOfTexture(int y, int height, char* content);

	/**
	 * @brief Initializes palette for image [AI]
	 * @param paletteSize Number of entries [AI]
	 * @param pEntries Palette data [AI]
	 */
	Result InitializePalette(int paletteSize, PaletteEntry* pEntries);

	D3DRMIMAGE m_image; ///< @brief [AI] Underlying D3DRM image struct [AI]
	int m_texelsAllocatedByClient; ///< @brief [AI] Flag for texel memory ownership (by client) [AI]
};

/**
 * @class TextureImpl
 * @brief [AI] Implements Tgl::Texture using a Direct3DRMTexture; provides upload and palette control [AI]
 */
class TextureImpl : public Texture {
public:
	// FUNCTION: BETA10 0x1016b1e0
	TextureImpl() : m_data(0) {} ///< @brief [AI] Initializes texture pointer [AI]

	// FUNCTION: BETA10 0x1016c2d0
	~TextureImpl() override { Destroy(); } ///< @brief [AI] Releases on destruction [AI]

	/**
	 * @brief Returns implementation pointer for texture [AI]
	 */
	void* ImplementationDataPtr() override;

	// vtable+0x08
	/**
	 * @brief Sets texel data for the texture [AI]
	 * @param width Width [AI]
	 * @param height Height [AI]
	 * @param bitsPerTexel Bits per texel [AI]
	 * @param pTexels Buffer pointer [AI]
	 */
	Result SetTexels(int width, int height, int bitsPerTexel, void* pTexels) override;

	/**
	 * @brief Fills rows of the texture [AI]
	 * @param y Row [AI]
	 * @param height Number of rows [AI]
	 * @param pBuffer Buffer for texels [AI]
	 */
	void FillRowsOfTexture(int y, int height, void* pBuffer) override;

	// vtable+0x10
	/**
	 * @brief Notifies that texels or palette have changed [AI]
	 * @param texelsChanged Flag [AI]
	 * @param paletteChanged Flag [AI]
	 */
	Result Changed(int texelsChanged, int paletteChanged) override;
	/**
	 * @brief Returns current buffer and palette [AI]
	 * @param pWidth Width output [AI]
	 * @param pHeight Height output [AI]
	 * @param pDepth Bits per texel output [AI]
	 * @param ppBuffer Texel data pointer output [AI]
	 * @param ppPaletteSize Palette size output [AI]
	 * @param ppPalette Palette entries output [AI]
	 */
	Result GetBufferAndPalette(
		int* pWidth,
		int* pHeight,
		int* pDepth,
		void** ppBuffer,
		int* ppPaletteSize,
		PaletteEntry** ppPalette
	) override;

	/**
	 * @brief Sets the palette entries for the texture [AI]
	 * @param entryCount Palette entry count [AI]
	 * @param entries Palette data [AI]
	 */
	Result SetPalette(int entryCount, PaletteEntry* entries) override;

	typedef IDirect3DRMTexture* TextureDataType; ///< @brief [AI] Internal type for Direct3DRMTexture pointer [AI]

	// FUNCTION: BETA10 0x1016fd60
	/**
	 * @brief Gets Direct3DRMTexture pointer (const) [AI]
	 */
	const TextureDataType& ImplementationData() const { return m_data; }

	// FUNCTION: BETA10 0x1016fe20
	/**
	 * @brief Gets Direct3DRMTexture pointer (mutable) [AI]
	 */
	TextureDataType& ImplementationData() { return m_data; }

	/**
	 * @brief Replaces implementation pointer [AI]
	 * @param pData Texture pointer [AI]
	 */
	void SetImplementation(IDirect3DRMTexture* pData) { m_data = pData; }

	/**
	 * @brief Frees the texture [AI]
	 */
	inline void Destroy();

	friend class RendererImpl;

	/**
	 * @brief Copies palette/texel data from TglD3DRMIMAGE to Direct3DRMTexture [AI]
	 * @param pSelf Texture pointer [AI]
	 * @param pImage TglD3DRMIMAGE pointer [AI]
	 */
	static Result SetImage(IDirect3DRMTexture* pSelf, TglD3DRMIMAGE* pImage);

private:
	TextureDataType m_data; ///< @brief [AI] Holds Direct3DRMTexture pointer [AI]
};

// FUNCTION: BETA10 0x1016fd40
/**
 * @brief Releases texture and manages memory [AI]
 * @param pTexture Texture pointer to release [AI]
 */
inline void TextureDestroy(IDirect3DRMTexture* pTexture)
{
	pTexture->Release();
}

// FUNCTION: BETA10 0x1016fd00
/**
 * @brief Frees texture and any resources if loaded [AI]
 */
void TextureImpl::Destroy()
{
	if (m_data) {
		TextureDestroy(m_data);
		m_data = NULL;
	}
}

// Translation helpers
// FUNCTION: BETA10 0x1016fc40
/**
 * @brief Converts Tgl shading model enum to D3DRM enum [AI]
 * @param tglShadingModel Tgl shading model [AI]
 * @return Corresponding D3DRM shading enum [AI]
 */
inline D3DRMRENDERQUALITY Translate(ShadingModel tglShadingModel)
{
	D3DRMRENDERQUALITY renderQuality;

	switch (tglShadingModel) {
	case Wireframe:
		renderQuality = D3DRMRENDER_WIREFRAME;
		break;
	case UnlitFlat:
		renderQuality = D3DRMRENDER_UNLITFLAT;
		break;
	case Flat:
		renderQuality = D3DRMRENDER_FLAT;
		break;
	case Gouraud:
		renderQuality = D3DRMRENDER_GOURAUD;
		break;
	case Phong:
		renderQuality = D3DRMRENDER_PHONG;
		break;
	default:
		renderQuality = D3DRMRENDER_FLAT;
		break;
	}

	return renderQuality;
}

// FUNCTION: BETA10 0x101703b0
/**
 * @brief Converts Tgl projection type enum to D3DRM enum [AI]
 * @param tglProjectionType Tgl projection type [AI]
 * @return D3DRM projection type [AI]
 */
inline D3DRMPROJECTIONTYPE Translate(ProjectionType tglProjectionType)
{
	D3DRMPROJECTIONTYPE projectionType;
	switch (tglProjectionType) {
	case Perspective:
		projectionType = D3DRMPROJECT_PERSPECTIVE;
		break;
	case Orthographic:
		projectionType = D3DRMPROJECT_ORTHOGRAPHIC;
		break;
	default:
		projectionType = D3DRMPROJECT_PERSPECTIVE;
		break;
	}
	return projectionType;
}

// Yes this function serves no purpose, originally they intended it to
// convert from doubles to floats but ended up using floats throughout
// the software stack.
/**
 * @brief Converts Tgl FloatMatrix4 to D3DRMMATRIX4D (no-op except for typing) [AI]
 * @param tglMatrix4x4 Input matrix (float) [AI]
 * @param rD3DRMMatrix4x4 Output matrix [AI]
 * @return Pointer to output matrix [AI]
 */
inline D3DRMMATRIX4D* Translate(FloatMatrix4& tglMatrix4x4, D3DRMMATRIX4D& rD3DRMMatrix4x4)
{
	for (int i = 0; i < (sizeof(rD3DRMMatrix4x4) / sizeof(rD3DRMMatrix4x4[0])); i++) {
		for (int j = 0; j < (sizeof(rD3DRMMatrix4x4[0]) / sizeof(rD3DRMMatrix4x4[0][0])); j++) {
			rD3DRMMatrix4x4[i][j] = D3DVAL(tglMatrix4x4[i][j]);
		}
	}
	return &rD3DRMMatrix4x4;
}

// FUNCTION: BETA10 0x1016fba0
/**
 * @brief Converts Tgl float vector to D3DVECTOR [AI]
 * @param tglVector An array of 3 floats (x, y, z) [AI]
 * @param rD3DVector D3D vector to output to [AI]
 * @return Pointer to filled D3DVECTOR [AI]
 */
inline D3DVECTOR* Translate(const float tglVector[3], D3DVECTOR& rD3DVector)
{
	rD3DVector.x = D3DVAL(tglVector[0]);
	rD3DVector.y = D3DVAL(tglVector[1]);
	rD3DVector.z = D3DVAL(tglVector[2]);

	return &rD3DVector;
}

// FUNCTION: BETA10 0x1016fd80
/**
 * @brief Maps Tgl LightType to D3DRMLIGHTTYPE [AI]
 * @param tglLightType Tgl light type [AI]
 * @return Matching Direct3D light type [AI]
 */
inline D3DRMLIGHTTYPE Translate(LightType tglLightType)
{
	D3DRMLIGHTTYPE lightType;

	// ??? use lookup table
	switch (tglLightType) {
	case Ambient:
		lightType = D3DRMLIGHT_AMBIENT;
		break;
	case Point:
		lightType = D3DRMLIGHT_POINT;
		break;
	case Spot:
		lightType = D3DRMLIGHT_SPOT;
		break;
	case Directional:
		lightType = D3DRMLIGHT_DIRECTIONAL;
		break;
	case ParallelPoint:
		lightType = D3DRMLIGHT_PARALLELPOINT;
		break;
	default:
		lightType = D3DRMLIGHT_AMBIENT;
		break;
	}

	return lightType;
}

// SYNTHETIC: LEGO1 0x100a16d0
// SYNTHETIC: BETA10 0x10169aa0
// TglImpl::RendererImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a22c0
// SYNTHETIC: BETA10 0x1016b700
// TglImpl::DeviceImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a23a0
// SYNTHETIC: BETA10 0x1016b810
// TglImpl::ViewImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a2480
// SYNTHETIC: BETA10 0x1016a2c0
// TglImpl::GroupImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a2560
// SYNTHETIC: BETA10 0x1016b920
// TglImpl::CameraImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a2640
// SYNTHETIC: BETA10 0x1016ba30
// TglImpl::LightImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a2720
// SYNTHETIC: BETA10 0x1016b5f0
// TglImpl::MeshBuilderImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a2800
// SYNTHETIC: BETA10 0x1016b4e0
// TglImpl::TextureImpl::`scalar deleting destructor'

// SYNTHETIC: LEGO1 0x100a3d80
// SYNTHETIC: BETA10 0x1016fa90
// TglImpl::MeshImpl::`scalar deleting destructor'

// SYNTHETIC: BETA10 0x10169960
// ViewportAppData::`scalar deleting destructor'

// GLOBAL: LEGO1 0x100dd1e0
// IID_IDirect3DRMMeshBuilder

} /* namespace TglImpl */