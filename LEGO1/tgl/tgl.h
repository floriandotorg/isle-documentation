#ifndef _tgl_h
#define _tgl_h

#include "tglvector.h"

#include <d3d.h>
#include <ddraw.h>
#include <windows.h>

namespace Tgl
{

/**
 * @enum ColorModel
 * @brief [AI] Represents available color models for rendering. Not used in the shipped game; exact semantics are inferred. [AI]
 * @details [AI] Includes ramp-based or true RGB color models (possibly for palette vs. truecolor rendering). [AI]
 */
enum ColorModel {
	// Note: Not used in shipped game, no way to verify contents.
	Ramp, ///< [AI] Uses a color ramp (palette/indexed color). [AI]
	RGB   ///< [AI] Uses direct RGB color values. [AI]
};

/**
 * @enum ShadingModel
 * @brief [AI] Represents shading models available for rendering geometry. [AI]
 * @details [AI] Determines the type of lighting and surface shading calculation performed (e.g., wireframe, flat, Gouraud, or Phong shading). [AI]
 */
enum ShadingModel {
	Wireframe,      ///< [AI] No shading; renders only mesh edges. [AI]
	UnlitFlat,      ///< [AI] Flat shading without lighting calculations. [AI]
	Flat,           ///< [AI] Flat shaded, possibly single color per polygon with lighting. [AI]
	Gouraud,        ///< [AI] Gouraud (vertex-interpolated) shading. [AI]
	Phong           ///< [AI] Phong (pixel-level) shading, if supported. [AI]
};

/**
 * @enum LightType
 * @brief [AI] Types of lights supported in the renderer. [AI]
 * @details [AI] Used to define the nature and behavior of a light source—ambient, point, spot, directional, or parallel point. [AI]
 */
enum LightType {
	Ambient,        ///< [AI] Non-directional lighting applied equally everywhere. [AI]
	Point,          ///< [AI] Light emitted from a point in all directions. [AI]
	Spot,           ///< [AI] Light that emits a cone-shaped beam from a point. [AI]
	Directional,    ///< [AI] Parallel light rays, such as sunlight. [AI]
	ParallelPoint   ///< [AI] Similar to point, but with parallel rays. [AI]
};

/**
 * @enum ProjectionType
 * @brief [AI] Projection modes for camera/view transforms. [AI]
 * @details [AI] Determines whether the scene is rendered with perspective or orthographic projection. [AI]
 */
enum ProjectionType {
	Perspective,    ///< [AI] Distant objects appear smaller. [AI]
	Orthographic    ///< [AI] Objects keep constant size regardless of distance. [AI]
};

/**
 * @enum TextureMappingMode
 * @brief [AI] Methods for mapping textures onto geometry. [AI]
 * @details [AI] Affects perspective correction when rendering textured geometry. [AI]
 */
enum TextureMappingMode {
	Linear,             ///< [AI] Linear interpolation (faster, less accurate). [AI]
	PerspectiveCorrect  ///< [AI] Perspective-correct mapping (higher quality). [AI]
};

/**
 * @enum MaterialMode
 * @brief [AI] Determines how material properties are sourced for a group/mesh.
 * @details [AI] Specifies if the group's material will be inherited or specified explicitly; inferred from assembly, not present in leaked Tgl code. [AI]
 */
enum MaterialMode {
	FromParent, ///< [AI] Inherit material from parent. [AI]
	FromFrame,  ///< [AI] Use material from the current frame. [AI]
	FromMesh,   ///< [AI] Use material specified at the mesh level. [AI]
};

/**
 * @struct PaletteEntry
 * @brief [AI] Represents a single color entry in a palette. [AI]
 * @details [AI] Holds RGB components as unsigned bytes. [AI]
 */
struct PaletteEntry {
	unsigned char m_red;   ///< [AI] Red component. [AI]
	unsigned char m_green; ///< [AI] Green component. [AI]
	unsigned char m_blue;  ///< [AI] Blue component. [AI]
};

/**
 * @struct DeviceDirect3DCreateData
 * @brief [AI] Contains Direct3D-specific data needed to create a rendering device. [AI]
 * @details [AI] Holds pointers to the Direct3D interfaces for device creation. [AI]
 */
struct DeviceDirect3DCreateData {
	IDirect3D2* m_pDirect3D;           ///< [AI] Direct3D interface pointer. [AI]
	IDirect3DDevice2* m_pDirect3DDevice; ///< [AI] Direct3D device interface pointer. [AI]
};

/**
 * @struct DeviceDirectDrawCreateData
 * @brief [AI] Contains DirectDraw-specific params for creating a rendering device. [AI]
 * @details [AI] Holds pointers to DirectDraw interfaces, buffers, and windowing info. [AI]
 */
struct DeviceDirectDrawCreateData {
	const GUID* m_driverGUID;        ///< [AI] GUID of the DirectDraw driver to use. [AI]
	HWND m_hWnd;                     ///< [AI] Window handle for display output. [AI]
	IDirectDraw* m_pDirectDraw;      ///< [AI] DirectDraw interface pointer. [AI]
	IDirectDrawSurface* m_pFrontBuffer; ///< [AI] Primary output surface. [AI]
	IDirectDrawSurface* m_pBackBuffer; ///< [AI] Secondary (offscreen) buffer for flipping/rendering. [AI]

	// These have possibly been removed in the shipped game
	// (Put them back if we can verify when we find a callsite
	// which constructs this type)
	// IDirectDrawPalette* m_pPalette;
	// int m_isFullScreen;
};

/**
 * @enum Result
 * @brief [AI] Result type used throughout the Tgl API to report operation success or failure. [AI]
 * @details [AI] Standardizes error handling in the Tgl API. [AI]
 */
enum Result {
	Error = 0,    ///< [AI] Operation failed. [AI]
	Success = 1   ///< [AI] Operation succeeded. [AI]
};

/**
 * @brief [AI] Returns whether a Tgl::Result indicates success. [AI]
 * @param result Result to test. [AI]
 * @return int Returns 1 if the result is Tgl::Success, 0 otherwise. [AI]
 */
inline int Succeeded(Result result)
{
	return (result == Success);
}

// Forward declarations
class Renderer;    ///< [AI] Main interface to renderers; factory for scene elements. [AI]
class Object;      ///< [AI] Base for all Tgl objects. [AI]
class Device;      ///< [AI] Represents a rendering device/context. [AI]
class View;        ///< [AI] Represents a camera viewport with rendering state. [AI]
class Light;       ///< [AI] Abstracts a scene light. [AI]
class Camera;      ///< [AI] Abstracts a viewpoint/camera in the 3D world. [AI]
class Group;       ///< [AI] Hierarchical scene graph node/group. [AI]
class Mesh;        ///< [AI] Renderable 3D mesh. [AI]
class Texture;     ///< [AI] Texture resource. [AI]
class MeshBuilder; ///< [AI] Utility for mesh data construction and conversion. [AI]

// VTABLE: LEGO1 0x100db980
// VTABLE: BETA10 0x101c3148
/**
 * @class Object
 * @brief [AI] Base class for all objects in the Tgl API. [AI]
 * @details [AI] Provides destruction and a type-erased pointer for implementation data. [AI]
 */
class Object {
public:
	/**
	 * @brief [AI] Destructor; releases resources. [AI]
	 */
	virtual ~Object() {}

	/**
	 * @brief [AI] Returns a pointer to internal/implementation data, if any. [AI]
	 * @return void* Pointer to implementation data. [AI]
	 */
	virtual void* ImplementationDataPtr() = 0;

	// SYNTHETIC: BETA10 0x10169b50
	// Tgl::Object::Object

	// SYNTHETIC: LEGO1 0x100a2250
	// SYNTHETIC: BETA10 0x10169cb0
	// Tgl::Object::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100db948
// VTABLE: BETA10 0x101c3110
/**
 * @class Renderer
 * @brief [AI] Main interface/factory for rendering resources and scene graphs. [AI]
 * @details [AI] Instantiated to provide devices, views, geometries, textures, lights, and cameras. [AI]
 */
class Renderer : public Object {
public:
	/**
	 * @brief [AI] Creates a rendering device using DirectDraw parameters. [AI]
	 * @param param Creation parameters (DirectDraw). [AI]
	 * @return Device* Device object or nullptr on failure. [AI]
	 */
	virtual Device* CreateDevice(const DeviceDirectDrawCreateData&) = 0;

	/**
	 * @brief [AI] Creates a rendering device using Direct3D parameters. [AI]
	 * @param param Creation parameters (Direct3D). [AI]
	 * @return Device* Device object or nullptr on failure. [AI]
	 */
	virtual Device* CreateDevice(const DeviceDirect3DCreateData&) = 0;

	/**
	 * @brief [AI] Creates a rendering view associated with the given device and camera. [AI]
	 * @param device Rendering device. [AI]
	 * @param camera Associated camera. [AI]
	 * @param x View X position. [AI]
	 * @param y View Y position. [AI]
	 * @param width Viewport width. [AI]
	 * @param height Viewport height. [AI]
	 * @return View* View object or nullptr. [AI]
	 */
	virtual View* CreateView(
		const Device*,
		const Camera*,
		unsigned long x,
		unsigned long y,
		unsigned long width,
		unsigned long height
	) = 0;

	/**
	 * @brief [AI] Creates a new camera. [AI]
	 * @return Camera* Newly created camera. [AI]
	 */
	virtual Camera* CreateCamera() = 0;

	/**
	 * @brief [AI] Creates a new light of the given type and color. [AI]
	 * @param type Type of light. [AI]
	 * @param r Red value. [AI]
	 * @param g Green value. [AI]
	 * @param b Blue value. [AI]
	 * @return Light* Created light object. [AI]
	 */
	virtual Light* CreateLight(LightType, float r, float g, float b) = 0;

	/**
	 * @brief [AI] Creates a new group (scene graph node), optionally parented. [AI]
	 * @param pParent Optional parent group (may be nullptr). [AI]
	 * @return Group* New group object. [AI]
	 */
	virtual Group* CreateGroup(const Group* pParent = 0) = 0;

	/**
	 * @brief [AI] Creates a new mesh builder. [AI]
	 * @return MeshBuilder* For mesh creation and construction. [AI]
	 */
	virtual MeshBuilder* CreateMeshBuilder() = 0;

	/**
	 * @brief [AI] Creates a new texture from raw texel buffer and optional palette. [AI]
	 * @param width Texture width. [AI]
	 * @param height Texture height. [AI]
	 * @param bitsPerTexel Bit depth of each texel. [AI]
	 * @param pTexels Texel buffer. [AI]
	 * @param pTexelsArePersistent Whether texels are persistent in memory. [AI]
	 * @param paletteEntryCount Size of the palette. [AI]
	 * @param pEntries Palette entries. [AI]
	 * @return Texture* Created texture. [AI]
	 */
	virtual Texture* CreateTexture(
		int width,
		int height,
		int bitsPerTexel,
		const void* pTexels,
		int pTexelsArePersistent,
		int paletteEntryCount,
		const PaletteEntry* pEntries
	) = 0;

	/**
	 * @brief [AI] Creates an (empty) texture. [AI]
	 * @return Texture* Created texture object. [AI]
	 */
	virtual Texture* CreateTexture() = 0;

	/**
	 * @brief [AI] Sets the default number of shades to generate for textures. [AI]
	 * @param count Number of shades. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTextureDefaultShadeCount(unsigned long) = 0;

	/**
	 * @brief [AI] Sets the default number of colors to use for textures (likely palette size). [AI]
	 * @param count Color count. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTextureDefaultColorCount(unsigned long) = 0;

	// SYNTHETIC: BETA10 0x10169ae0
	// Tgl::Renderer::Renderer

	// SYNTHETIC: LEGO1 0x100a1770
	// SYNTHETIC: BETA10 0x10169b80
	// Tgl::Renderer::~Renderer

	// SYNTHETIC: LEGO1 0x100a17c0
	// SYNTHETIC: BETA10 0x10169be0
	// Tgl::Renderer::`scalar deleting destructor'
};

/**
 * @brief [AI] Instantiates and returns a new Tgl::Renderer implementation. [AI]
 * @return Renderer* New renderer or nullptr on error. [AI]
 */
Renderer* CreateRenderer();

// VTABLE: LEGO1 0x100db9b8
// VTABLE: BETA10 0x101c32b0
/**
 * @class Device
 * @brief [AI] Represents a rendering device/context for the Tgl renderer. [AI]
 * @details [AI] Controls low-level rendering device state and update flow. [AI]
 */
class Device : public Object {
public:
	/**
	 * @brief [AI] Gets the output width in pixels. [AI]
	 * @return Current device width. [AI]
	 */
	virtual unsigned long GetWidth() = 0;

	/**
	 * @brief [AI] Gets the output height in pixels. [AI]
	 * @return Current device height. [AI]
	 */
	virtual unsigned long GetHeight() = 0;

	/**
	 * @brief [AI] Sets the color model for rendering. [AI]
	 * @param model Desired color model. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetColorModel(ColorModel) = 0;

	/**
	 * @brief [AI] Sets the shading model (e.g., Gouraud, flat). [AI]
	 * @param shadingModel Desired shading type. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetShadingModel(ShadingModel) = 0;

	/**
	 * @brief [AI] Specifies the number of shades for rendering (possibly for palette/ramp mode). [AI]
	 * @param count Shade count. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetShadeCount(unsigned long) = 0;

	/**
	 * @brief [AI] Enables/disables dithering in the renderer. [AI]
	 * @param on Boolean-like toggle; nonzero to enable. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetDither(int) = 0;

	/**
	 * @brief [AI] Performs a device update/synchronization. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Update() = 0;

	/**
	 * @brief [AI] Handles window activation events (e.g., WM_ACTIVATE). [AI]
	 * @param wParam Window activation state. [AI]
	 */
	virtual void HandleActivate(WORD) = 0;

	/**
	 * @brief [AI] Handles window repaint events (e.g., WM_PAINT) with a device context. [AI]
	 * @param hdc Device context handle. [AI]
	 */
	virtual void HandlePaint(HDC) = 0;

	// SYNTHETIC: BETA10 0x1016b740
	// Tgl::Device::Device

	// SYNTHETIC: LEGO1 0x100a2350
	// SYNTHETIC: BETA10 0x1016b7b0
	// Tgl::Device::~Device

	// SYNTHETIC: LEGO1 0x100a28e0
	// SYNTHETIC: BETA10 0x1016bbc0
	// Tgl::Device::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dba28
// VTABLE: BETA10 0x101c32e0
/**
 * @class View
 * @brief [AI] Represents a rendering viewport and drawing context. [AI]
 * @details [AI] Manages camera, lights, projection parameters, picking, and frame rendering. [AI]
 */
class View : public Object {
public:
	/**
	 * @brief [AI] Adds a light to the view for rendering. [AI]
	 * @param light Light to add. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Add(const Light*) = 0;

	/**
	 * @brief [AI] Removes a light from the view. [AI]
	 * @param light Light to remove. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Remove(const Light*) = 0;

	/**
	 * @brief [AI] Sets the camera used by the view. [AI]
	 * @param camera Camera to use for rendering. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetCamera(const Camera*) = 0;

	/**
	 * @brief [AI] Sets projection type for the view (e.g., perspective/orthographic). [AI]
	 * @param pType Projection type. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetProjection(ProjectionType) = 0;

	/**
	 * @brief [AI] Sets front and back clipping planes and view field in degrees. [AI]
	 * @param frontClippingDistance Near/far plane distances and field of view (degrees). [AI]
	 * @param backClippingDistance [AI]
	 * @param degrees [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetFrustrum(float frontClippingDistance, float backClippingDistance, float degrees) = 0;

	/**
	 * @brief [AI] Sets the background color for the view. [AI]
	 * @param r Red. [AI]
	 * @param g Green. [AI]
	 * @param b Blue. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetBackgroundColor(float r, float g, float b) = 0;

	/**
	 * @brief [AI] Retrieves the current background color. [AI]
	 * @param r Pointer to red value. [AI]
	 * @param g Pointer to green value. [AI]
	 * @param b Pointer to blue value. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result GetBackgroundColor(float* r, float* g, float* b) = 0;

	/**
	 * @brief [AI] Clears the current contents of the view. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Clear() = 0;

	/**
	 * @brief [AI] Renders a group hierarchy to the view. [AI]
	 * @param group Scene/group to render. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Render(const Group*) = 0;

	/**
	 * @brief [AI] Forces update/redraw of a region in the view. [AI]
	 * @param x Left of update region. [AI]
	 * @param y Top of update region. [AI]
	 * @param width Width of region. [AI]
	 * @param height Height of region. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result ForceUpdate(unsigned long x, unsigned long y, unsigned long width, unsigned long height) = 0;

	/**
	 * @brief [AI] Transforms a world-space position to screen coordinates. [AI]
	 * @param world Input [x,y,z] position in world coordinates. [AI]
	 * @param screen Output [x,y,z,1/w] in screen space. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result TransformWorldToScreen(const float world[3], float screen[4]) = 0;

	/**
	 * @brief [AI] Converts screen coordinate back to world position. [AI]
	 * @param screen Input [x,y,z,w] in screen space. [AI]
	 * @param world Output [x,y,z] in world space. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result TransformScreenToWorld(const float screen[4], float world[3]) = 0;

	/**
	 * @brief [AI] Picks the group under screen coordinates, searching specific group trees. [AI]
	 * @param x X coordinate (view coords). [AI]
	 * @param y Y coordinate (view coords). [AI]
	 * @param ppGroupsToPickFrom Array of candidate groups to test for picking. [AI]
	 * @param groupsToPickFromCount Number of candidate groups. [AI]
	 * @param rppPickedGroups Output array; hierarchy from root to leaf group picked (may contain nullptr for misses). [AI]
	 * @param rPickedGroupCount Output; number of elements in rppPickedGroups. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Pick(
		unsigned long x,
		unsigned long y,
		const Group** ppGroupsToPickFrom,
		int groupsToPickFromCount,
		const Group**& rppPickedGroups,
		int& rPickedGroupCount
	) = 0;

	// SYNTHETIC: BETA10 0x1016b850
	// Tgl::View::View

	// SYNTHETIC: LEGO1 0x100a2430
	// SYNTHETIC: BETA10 0x1016b8c0
	// Tgl::View::~View

	// SYNTHETIC: LEGO1 0x100a2950
	// SYNTHETIC: BETA10 0x1016bc00
	// Tgl::View::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dbae8
// VTABLE: BETA10 0x101c3320
/**
 * @class Camera
 * @brief [AI] Represents a viewpoint in the 3D scene. [AI]
 * @details [AI] Manages camera transformations in the scene graph. [AI]
 */
class Camera : public Object {
public:
	/**
	 * @brief [AI] Sets the transformation matrix for the camera. [AI]
	 * @param mat Reference to transformation matrix. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTransformation(FloatMatrix4&) = 0;

	// SYNTHETIC: BETA10 0x1016b960
	// Tgl::Camera::Camera

	// SYNTHETIC: LEGO1 0x100a25f0
	// SYNTHETIC: BETA10 0x1016b9d0
	// Tgl::Camera::~Camera

	// SYNTHETIC: LEGO1 0x100a2a30
	// SYNTHETIC: BETA10 0x1016bc40
	// Tgl::Camera::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dbb08
// VTABLE: BETA10 0x101c3330
/**
 * @class Light
 * @brief [AI] Represents a source of lighting in the 3D scene. [AI]
 * @details [AI] Configures transform and color for different light types. [AI]
 */
class Light : public Object {
public:
	/**
	 * @brief [AI] Sets the transformation matrix for the light source. [AI]
	 * @param mat Reference to transformation matrix. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTransformation(FloatMatrix4&) = 0;

	/**
	 * @brief [AI] Sets the light's color. [AI]
	 * @param r Red. [AI]
	 * @param g Green. [AI]
	 * @param b Blue. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetColor(float r, float g, float b) = 0;

	// SYNTHETIC: BETA10 0x1016ba70
	// Tgl::Light::Light

	// SYNTHETIC: LEGO1 0x100a26d0
	// SYNTHETIC: BETA10 0x1016bae0
	// Tgl::Light::~Light

	// SYNTHETIC: LEGO1 0x100a2aa0
	// SYNTHETIC: BETA10 0x1016bc80
	// Tgl::Light::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dbbb0
// VTABLE: BETA10 0x101c3360
/**
 * @class Mesh
 * @brief [AI] Represents a renderable 3D mesh. [AI]
 * @details [AI] Allows setting color, texture, shading and provides clone operations. [AI]
 */
class Mesh : public Object {
public:
	/**
	 * @brief [AI] Sets the color and transparency for the mesh. [AI]
	 * @param r Red. [AI]
	 * @param g Green. [AI]
	 * @param b Blue. [AI]
	 * @param a Alpha (opacity). [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetColor(float r, float g, float b, float a) = 0;

	/**
	 * @brief [AI] Sets the texture to use. [AI]
	 * @param pTexture Texture object. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTexture(const Texture*) = 0;

	/**
	 * @brief [AI] Retrieves the currently set texture. [AI]
	 * @param pTexture Reference to pointer to texture (output). [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result GetTexture(Texture*&) = 0;

	/**
	 * @brief [AI] Sets how texture coordinates are mapped (linear or perspective correct). [AI]
	 * @param mode Mapping mode. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTextureMappingMode(TextureMappingMode) = 0;

	/**
	 * @brief [AI] Sets the mesh's shading model (e.g., Gouraud, Phong). [AI]
	 * @param m Shading model. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetShadingModel(ShadingModel) = 0;

	/**
	 * @brief [AI] Performs a deep clone—copying all mesh and group data. [AI]
	 * @param builder Mesh builder to use. [AI]
	 * @return Mesh* New, separate mesh object. [AI]
	 */
	virtual Mesh* DeepClone(MeshBuilder*) = 0;

	/**
	 * @brief [AI] Performs a shallow clone—new wrapper, same mesh data. [AI]
	 * @param builder Mesh builder to use. [AI]
	 * @return Mesh* Mesh sharing data with original. [AI]
	 */
	virtual Mesh* ShallowClone(MeshBuilder*) = 0;

	// SYNTHETIC: BETA10 0x1016fad0
	// Tgl::Mesh::Mesh

	// SYNTHETIC: LEGO1 0x100a3e10
	// SYNTHETIC: BETA10 0x1016fb40
	// Tgl::Mesh::~Mesh

	// SYNTHETIC: LEGO1 0x100a3e60
	// SYNTHETIC: BETA10 0x1016fbe0
	// Tgl::Mesh::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dbaa0
// VTABLE: BETA10 0x101c3188
/**
 * @class Group
 * @brief [AI] Scene graph node for parental transforms/color/material/texture; can hold meshes or other groups. [AI]
 * @details [AI] Provides hierarchical operations and bounds calculation for a group and its children. [AI]
 */
class Group : public Object {
public:
	/**
	 * @brief [AI] Sets the group's transformation matrix. [AI]
	 * @param mat Transformation. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTransformation(FloatMatrix4&) = 0;

	/**
	 * @brief [AI] Sets color (and alpha) for all geometry in the group. [AI]
	 * @param r Red. [AI]
	 * @param g Green. [AI]
	 * @param b Blue. [AI]
	 * @param a Alpha. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetColor(float r, float g, float b, float a) = 0;

	/**
	 * @brief [AI] Sets a texture for the entire group. [AI]
	 * @param pTexture Texture object. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTexture(const Texture*) = 0;

	/**
	 * @brief [AI] Gets the group's texture (if any). [AI]
	 * @param pTexture Output pointer to texture. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result GetTexture(Texture*&) = 0;

	/**
	 * @brief [AI] Sets material mode for the group (e.g., inherit vs. explicit). [AI]
	 * @param mode Material mode. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetMaterialMode(MaterialMode) = 0;

	/**
	 * @brief [AI] Adds a child group to this group. [AI]
	 * @param group Group to add. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Add(const Group*) = 0;

	/**
	 * @brief [AI] Adds a mesh builder's mesh to the group. [AI]
	 * @param builder Mesh builder providing mesh. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Add(const MeshBuilder*) = 0;

	/**
	 * @brief [AI] Removes a child group from this group. [AI]
	 * @param group Group to remove. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Remove(const Group*) = 0;

	/**
	 * @brief [AI] Removes a mesh builder's mesh from group. [AI]
	 * @param builder Mesh builder providing mesh. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Remove(const MeshBuilder*) = 0;

	/**
	 * @brief [AI] Removes all children and meshes from the group. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result RemoveAll() = 0;

	/**
	 * @brief [AI] Computes an axis-aligned bounding box for the group in world space. [AI]
	 * @param pMin Output min corner. [AI]
	 * @param pMax Output max corner. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Bounds(D3DVECTOR*, D3DVECTOR*) = 0;

	// SYNTHETIC: BETA10 0x1016a300
	// Tgl::Group::Group

	// SYNTHETIC: LEGO1 0x100a2510
	// SYNTHETIC: BETA10 0x1016a370
	// Tgl::Group::~Group

	// SYNTHETIC: LEGO1 0x100a29c0
	// SYNTHETIC: BETA10 0x1016a3d0
	// Tgl::Group::`scalar deleting destructor'
};

/**
 * @class MeshBuilder
 * @brief [AI] Builder class for assembling mesh data and extracting mesh objects. [AI_SUGGESTED_NAME: MeshBuilder]
 * @details [AI] Not present in original leaked Tgl code; inferred as a mesh construction/conversion utility for geometry. [AI]
 */
class MeshBuilder : public Object {
public:
	/**
	 * @brief [AI] Creates a mesh from supplied geometry data. [AI]
	 * @param faceCount Number of triangular faces. [AI]
	 * @param vertexCount Number of vertices. [AI]
	 * @param pPositions Vertex positions (array of [3] floats per vertex). [AI]
	 * @param pNormals Vertex normals (array of [3] floats per vertex). [AI]
	 * @param pTextureCoordinates Array of [2] float texture coords per vertex. [AI]
	 * @param pFaceIndices Indices (vertex indices) for each face, [3] per face. [AI]
	 * @param pTextureIndices Per-face per-corner texture indices. [AI]
	 * @param shadingModel Shading style for new mesh. [AI]
	 * @return Mesh* Created mesh object. [AI]
	 */
	virtual Mesh* CreateMesh(
		unsigned long faceCount,
		unsigned long vertexCount,
		float (*pPositions)[3],
		float (*pNormals)[3],
		float (*pTextureCoordinates)[2],
		unsigned long (*pFaceIndices)[3],
		unsigned long (*pTextureIndices)[3],
		ShadingModel shadingModel
	) = 0;

	/**
	 * @brief [AI] Gets the bounding box for the constructed mesh geometry. [AI]
	 * @param min Output min x,y,z. [AI]
	 * @param max Output max x,y,z. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result GetBoundingBox(float min[3], float max[3]) const = 0;

	/**
	 * @brief [AI] Makes a copy of the mesh builder instance (deep copy). [AI]
	 * @return MeshBuilder* Cloned mesh builder. [AI]
	 */
	virtual MeshBuilder* Clone() = 0;

	// SYNTHETIC: BETA10 0x1016b630
	// Tgl::MeshBuilder::MeshBuilder

	// SYNTHETIC: LEGO1 0x100a27b0
	// SYNTHETIC: BETA10 0x1016b6a0
	// Tgl::MeshBuilder::~MeshBuilder

	// SYNTHETIC: LEGO1 0x100a2b10
	// SYNTHETIC: BETA10 0x1016bb80
	// Tgl::MeshBuilder::`scalar deleting destructor'
};

// VTABLE: LEGO1 0x100dbb68
// VTABLE: BETA10 0x101c3280
/**
 * @class Texture
 * @brief [AI] Represents a GPU or system memory texture for use in rendering. [AI]
 * @details [AI] Allows uploading texel data, palette control, and buffer retrieval. [AI]
 */
class Texture : public Object {
public:
	/**
	 * @brief [AI] Sets the texture image data (texels and size). [AI]
	 * @param width Texture width. [AI]
	 * @param height Texture height. [AI]
	 * @param bitsPerTexel Texel bit depth. [AI]
	 * @param pTexels Pointer to texel buffer. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetTexels(int width, int height, int bitsPerTexel, void* pTexels) = 0;

	/**
	 * @brief [AI] Fills lines of texel data in the image buffer. [AI]
	 * @param y Starting row. [AI]
	 * @param height Number of rows. [AI]
	 * @param pBuffer Pointer to data buffer. [AI]
	 */
	virtual void FillRowsOfTexture(int y, int height, void* pBuffer) = 0;

	/**
	 * @brief [AI] Notifies of changes to texels or palette. [AI]
	 * @param texelsChanged Nonzero if the texel data has changed. [AI]
	 * @param paletteChanged Nonzero if the palette has changed. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result Changed(int texelsChanged, int paletteChanged) = 0;

	/**
	 * @brief [AI] Retrieves texture buffer and palette for external access. [AI]
	 * @param pWidth Output width. [AI]
	 * @param pHeight Output height. [AI]
	 * @param pDepth Output bits-per-texel. [AI]
	 * @param ppBuffer Output pointer to texture buffer. [AI]
	 * @param pPaletteSize Output palette entry count. [AI]
	 * @param ppPalette Output pointer to palette data. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result GetBufferAndPalette(
		int* pWidth,
		int* pHeight,
		int* pDepth,
		void** ppBuffer,
		int* pPaletteSize,
		PaletteEntry** ppPalette
	) = 0;

	/**
	 * @brief [AI] Assigns a palette to the texture. [AI]
	 * @param entryCount Number of palette entries. [AI]
	 * @param pEntries Palette entries. [AI]
	 * @return Result Success or Error. [AI]
	 */
	virtual Result SetPalette(int entryCount, PaletteEntry* pEntries) = 0;

	// SYNTHETIC: BETA10 0x1016b520
	// Tgl::Texture::Texture

	// SYNTHETIC: LEGO1 0x100a2890
	// SYNTHETIC: BETA10 0x1016b590
	// Tgl::Texture::~Texture

	// SYNTHETIC: LEGO1 0x100a2b80
	// SYNTHETIC: BETA10 0x1016bb40
	// Tgl::Texture::`scalar deleting destructor'
};

} // namespace Tgl

#endif /* _tgl_h */