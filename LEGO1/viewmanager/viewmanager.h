#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "decomp.h"
#include "realtime/realtimeview.h"
#include "viewroi.h"

#include <d3drm.h>

// VTABLE: LEGO1 0x100dbd88
// SIZE 0x1bc
/**
 * @brief [AI] Manages all ViewROI objects that are rendered in a given scene, handles frustum culling, LOD management, and visibility determination for 3D ROI objects. Coordinates detail level based on view parameters and maintains view transformation matrices for efficient rendering.
 * @details [AI] ViewManager is responsible for controlling the rendering of all 3D real-time object instances (ROIs) in the current scene. It maintains a collection of ViewROI objects, calculates visibility based on the camera's frustum, manages geometric detail levels according to projected object size and LOD thresholds, and applies transformations for the scene's camera (point-of-view) parameters. It provides utility for picking ROI objects using screen coordinates and is tightly bound to the Direct3DRM retained mode pipeline.
 */
class ViewManager {
public:
	/**
	 * @brief [AI] Bit flags used internally by ViewManager to track various states or trigger needed calculations (such as view or frustum updates).
	 */
	enum Flags {
		c_bit1 = 0x01, ///< [AI] Used to signals a pending operation (exact purpose is contextually flagged during update routines).
		c_bit2 = 0x02, ///< [AI] Indicates the need to update view transformation matrices.
		c_bit3 = 0x04, ///< [AI] Indicates the need to recalculate frustum parameters (e.g., due to a resolution or frustum change).
		c_bit4 = 0x08  ///< [AI] Signals that the frustum parameters/planes are valid and up to date.
	};

	/**
	 * @brief [AI] Constructs the ViewManager with the renderer, scene group, and initial point-of-view. Initializes transformation matrices and internal state.
	 * @param pRenderer [AI] Pointer to the renderer (Direct3DRM abstraction) to use for view operations.
	 * @param scene [AI] The top-level scene group for geometry association and manipulation.
	 * @param point_of_view [AI] The initial camera reference used for setting up the view transformation.
	 */
	ViewManager(Tgl::Renderer* pRenderer, Tgl::Group* scene, const OrientableROI* point_of_view);

	/**
	 * @brief [AI] Destroys the ViewManager including detaching the current POV source and releasing Direct3DRM objects.
	 */
	virtual ~ViewManager();

	/**
	 * @brief [AI] Removes a single ViewROI from the managed ROI list, also detaching any associated LOD data from the scene and handling recursively any compound child ROIs.
	 * @param p_roi [AI] The ViewROI instance to remove.
	 */
	void Remove(ViewROI* p_roi);

	/**
	 * @brief [AI] Recursively removes all ViewROI objects. If called with NULL, purges all managed ROI objects in the scene.
	 * @param p_roi [AI] If NULL, removes all; otherwise recursively removes the given ROI and children.
	 */
	void RemoveAll(ViewROI* p_roi);

	/**
	 * @brief [AI] Determines if a bounding box is (partially) inside the camera's view frustum using frustum-plane testing.
	 * @param p_bounding_box [AI] Axis-aligned bounding box to test.
	 * @return [AI] TRUE if any part of the bounding box is within the current frustum, otherwise FALSE.
	 */
	unsigned int IsBoundingBoxInFrustum(const BoundingBox& p_bounding_box);

	/**
	 * @brief [AI] Based on computed LOD, updates the scene to show the correct mesh for a given ROI, removing or replacing representations as required.
	 * @param p_roi [AI] The ROI for which to update level-of-detail.
	 * @param p_und [AI] Target LOD index.
	 */
	void UpdateROIDetailBasedOnLOD(ViewROI* p_roi, int p_und);

	/**
	 * @brief [AI] Removes the currently active LOD detail from the rendering scene for the given ROI and detaches it from the top-level scene group.
	 * @param p_roi [AI] The target ROI.
	 */
	void RemoveROIDetailFromScene(ViewROI* p_roi);

	/**
	 * @brief [AI] Sets the OrientableROI to use as the camera's point-of-view; updates the transformation matrix accordingly.
	 * @param point_of_view [AI] The OrientableROI representing the camera.
	 */
	void SetPOVSource(const OrientableROI* point_of_view);

	/**
	 * @brief [AI] Computes the projected area of a bounding sphere onto the camera's viewing plane (used for LOD calculation).
	 * @param p_bounding_sphere [AI] The bounding sphere to project.
	 * @return [AI] The ratio of the sphere's projected area to the view area at unit distance.
	 */
	float ProjectedSize(const BoundingSphere& p_bounding_sphere);

	/**
	 * @brief [AI] Using a screen coordinate and viewport, finds the ViewROI (if any) under the given coordinates by querying Direct3DRM's pick pipeline.
	 * @param p_view [AI] Pointer to the Tgl view (Direct3DRM viewport abstraction).
	 * @param x [AI] Screen-space X coordinate.
	 * @param y [AI] Screen-space Y coordinate.
	 * @return [AI] The ROI at the specified location, or NULL if none found.
	 */
	ViewROI* Pick(Tgl::View* p_view, unsigned long x, unsigned long y);

	/**
	 * @brief [AI] Sets the viewport resolution and marks the frustum as needing recalculation.
	 * @param width [AI] The width of the view area in pixels.
	 * @param height [AI] The height of the view area in pixels.
	 */
	void SetResolution(int width, int height);

	/**
	 * @brief [AI] Sets the projection frustum parameters and marks the frustum as needing recalculation.
	 * @param fov [AI] Field of view in degrees.
	 * @param front [AI] Near plane Z position.
	 * @param back [AI] Far plane Z position.
	 */
	void SetFrustrum(float fov, float front, float back);

	/**
	 * @brief [AI] Recursively traverses and updates the visibility and LOD detail of a ROI and its children, based on projected size and thresholds.
	 * @param p_roi [AI] The starting ROI for recursive update.
	 * @param p_und [AI] LOD index, or -1 to auto-calculate, or -2 to hide.
	 */
	inline void ManageVisibilityAndDetailRecursively(ViewROI* p_roi, int p_und);

	/**
	 * @brief [AI] Performs the per-frame update: applies frustum/view updates if needed and recurses the ROI graph for visibility/LOD/detail management.
	 * @param p_previousRenderTime [AI] Time mark of the previous render.
	 * @param [unused] [AI] Unused parameter.
	 */
	void Update(float p_previousRenderTime, float);

	/**
	 * @brief [AI] Computes frustum planes and transformed corner positions for the current camera/view, updating internal matrices.
	 * @return [AI] 0 if successful, -1 if height/front parameters are invalid.
	 */
	inline int CalculateFrustumTransformations();

	/**
	 * @brief [AI] Updates the transformation matrices using the current POV and frustum edges, recalculating plane normals and D terms for culling.
	 */
	void UpdateViewTransformations();

	/**
	 * @brief [AI] Determines the LOD level index for a ROI based on projected size and user-defined/scene parameters.
	 * @param p_und1 [AI] Projected size value.
	 * @param p_und2 [AI] LOD threshold.
	 * @param p_roi [AI] Target ROI.
	 * @return [AI] The determined LOD index.
	 */
	inline static int CalculateLODLevel(float p_und1, float p_und2, ViewROI* p_roi);

	/**
	 * @brief [AI] Checks whether the given ROI should be considered visible at any LOD, including compound sub-ROIs.
	 * @param p_roi [AI] The object to check.
	 * @return [AI] 1 if visible, 0 otherwise.
	 */
	inline static int IsROIVisibleAtLOD(ViewROI* p_roi);

	/**
	 * @brief [AI] Returns the internal CompoundObject list of all managed ViewROI objects for iteration or queries.
	 * @return [AI] Reference to the internal ROI container.
	 */
	const CompoundObject& GetROIs() { return rois; }

	/**
	 * @brief [AI] Adds a ViewROI object to the list of managed ROI objects.
	 * @param p_roi [AI] The ROI to add.
	 */
	void Add(ViewROI* p_roi) { rois.push_back(p_roi); }

	// SYNTHETIC: LEGO1 0x100a6000
	// ViewManager::`scalar deleting destructor'

private:
	Tgl::Group* scene;              ///< [AI] Pointer to the main scene node/group for adding and removing geometry. Geometry groups and meshbuilders for ROIs are attached here.
	CompoundObject rois;            ///< [AI] Container of top-level ROI objects managed and processed for rendering.
	RealtimeView rt_view;           ///< [AI] Stores real-time rendering parameters and tracks frame/user LOD overrides.
	ROIList visible_rois;           ///< [AI] List of ROI objects determined visible in the current frustum pass.
	float prev_render_time;         ///< [AI] Stores timing information for previous frame (used in animation or update calculations).
	float view_area_at_one;         ///< [AI] Area of view plane at a distance of one unit (used for LOD/projected size calculations).
	unsigned int flags;             ///< [AI] Bitmask for internal state (see enum Flags).
	float width;                    ///< [AI] Viewport width (pixels/units).
	float height;                   ///< [AI] Viewport height.
	float view_angle;               ///< [AI] Field of view (radians).
	MxMatrix pov;                   ///< [AI] Current view (camera) transformation matrix (position + orientation).
	float front;                    ///< [AI] Near plane Z value of frustum.
	float back;                     ///< [AI] Far plane Z value of frustum.
	float frustum_vertices[8][3];   ///< [AI] The 8 corners of the frustum in local space.
	float transformed_points[8][3]; ///< [AI] The 8 corners of the frustum after all world/view transformations.
	float frustum_planes[6][4];     ///< [AI] The 6 frustum culling planes, each as a (a,b,c,d) plane equation in camera/world space.
	IDirect3DRM2* d3drm;            ///< [AI] Pointer to the Direct3DRM2 interface for scene and geometry operations.
	IDirect3DRMFrame2* frame;       ///< [AI] The root Direct3DRM frame for the managed scene.
	float seconds_allowed;          ///< [AI] Timing threshold, used in projected size and LOD visibility cutoff (to skip too small/insignificant objects).
};

// TEMPLATE: LEGO1 0x10022030
// list<ROI *,allocator<ROI *> >::insert

// TEMPLATE: LEGO1 0x100a6020
// List<ROI *>::~List<ROI *>

// TEMPLATE: LEGO1 0x100a6070
// Vector<ROI const *>::~Vector<ROI const *>

// TEMPLATE: LEGO1 0x100a6f80
// vector<ROI const *,allocator<ROI const *> >::~vector<ROI const *,allocator<ROI const *> >

#endif // VIEWMANAGER_H
