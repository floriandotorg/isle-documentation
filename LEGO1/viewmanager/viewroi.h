#ifndef VIEWROI_H
#define VIEWROI_H

#include "decomp.h"
#include "realtime/orientableroi.h"
#include "tgl/tgl.h"
#include "viewlodlist.h"

/**
 * @brief [AI] ViewROI objects represent viewable and placeable objects in the scene, each holding their own transformation and geometry group for rendering.
 * @details [AI] ViewROI is derived from OrientableROI and serves as a specialized ROI (Real-time Object Instance) that maintains a reference to a group of renderable geometry (Tgl::Group) and its LODs via a ViewLODList. Used for any entity or collection of objects manipulated by the view/render manager. The class manages reference counting for its LOD list and owns its geometry group, cleaning up on destruction.
 */
class ViewROI : public OrientableROI {
public:
	/**
	 * @brief [AI] Constructs a ViewROI with the specified renderer and LOD list.
	 * @param pRenderer [AI] The Tgl::Renderer used to create the geometry group.
	 * @param lodList [AI] The list of Level of Details for this object; will have its reference count managed.
	 * @details [AI] Initializes the geometry field via the renderer, and sets the internal unknown field to -1.
	 */
	ViewROI(Tgl::Renderer* pRenderer, ViewLODList* lodList)
	{
		SetLODList(lodList);
		geometry = pRenderer->CreateGroup();
		m_unk0xe0 = -1;
	}

	/**
	 * @brief [AI] Destructor cleans up internal geometry and releases LOD list reference.
	 * @details [AI] Calls SetLODList(0) to decrease the reference of the current LOD list, then deletes the geometry group.
	 */
	~ViewROI() override
	{
		// SetLODList() will decrease refCount of LODList
		SetLODList(0);
		delete geometry;
	}

	/**
	 * @brief [AI] Sets the ViewLODList for this ROI, managing reference counting.
	 * @param lodList [AI] The new ViewLODList to set for this ROI.
	 * @details [AI] Decreases the reference count of the current LOD list (if any), sets the new list, and increases its reference count.
	 */
	void SetLODList(ViewLODList* lodList)
	{
		// ??? inherently type unsafe - kind of... because, now, ROI
		//     does not expose SetLODs() ...
		// solution: create pure virtual LODListBase* ROI::GetLODList()
		// and let derived ROI classes hold the LODList

		if (lods) {
			reinterpret_cast<ViewLODList*>(lods)->Release();
		}

		lods = lodList;

		if (lods) {
			reinterpret_cast<ViewLODList*>(lods)->AddRef();
		}
	}

	/**
	 * @brief [AI] Returns the intrinsic importance of this ROI, used for LOD or sorting.
	 * @details [AI] This value is used to determine level of detail or culling priority.
	 * @return [AI] The intrinsic importance scalar.
	 */
	float IntrinsicImportance() const override;                  // vtable+0x04

	/**
	 * @brief [AI] Updates internal state, potentially related to animation or LOD switching (exact purpose unclear).
	 * @details [AI] Calls parent's method and synchronizes transformation to geometry.
	 * @note [AI] Name from vtable; specific purpose unknown. [AI_SUGGESTED_NAME: UpdateInternalState]
	 */
	void VTable0x1c() override;                                  // vtable+0x1c

	/**
	 * @brief [AI] Sets the local transformation; propagates to the underlying geometry group.
	 * @param p_transform [AI] The new local-to-world transformation matrix.
	 * @details [AI] After updating its own matrix, updates the Tgl::Group to match the new transformation.
	 */
	void SetLocalTransform(const Matrix4& p_transform) override; // vtable+0x20

	/**
	 * @brief [AI] Updates an internal transformation, synchronizing ROI and geometry.
	 * @param p_transform [AI] Matrix to apply as a secondary or derived transformation.
	 * @details [AI] Similar to SetLocalTransform, provided for derived class or specialized transformation. [AI_SUGGESTED_NAME: ApplyExtraTransform]
	 */
	void VTable0x24(const Matrix4& p_transform) override;        // vtable+0x24

	/**
	 * @brief [AI] Returns a pointer to this ROI's Tgl::Group geometry for rendering and manipulation.
	 * @details [AI] The Tgl::Group acts as the root for all renderable geometry in this ROI. 
	 * @return [AI] Pointer to the modifiable geometry group.
	 */
	virtual Tgl::Group* GetGeometry();                           // vtable+0x30

	/**
	 * @brief [AI] Returns a const pointer to this ROI's Tgl::Group geometry.
	 * @return [AI] Const pointer to the geometry group.
	 */
	virtual const Tgl::Group* GetGeometry() const;               // vtable+0x34

	/**
	 * @brief [AI] Gets the value of an internal state field at offset 0xe0.
	 * @details [AI] The usage of the field is unknown, possibly a rendering or animation state.
	 * @return [AI] Integer value of m_unk0xe0.
	 */
	int GetUnknown0xe0() { return m_unk0xe0; }

	/**
	 * @brief [AI] Sets the value of the internal state field at offset 0xe0.
	 * @param p_unk0xe0 [AI] New value for m_unk0xe0.
	 */
	void SetUnknown0xe0(int p_unk0xe0) { m_unk0xe0 = p_unk0xe0; }

	/**
	 * @brief [AI] Sets the global flag g_unk101013d8 and returns its previous value.
	 * @param p_flag [AI] The flag value to set.
	 * @return [AI] The previous value of the global flag.
	 * @details [AI] Utility for toggling a static/global rendering or logic state across ViewROI.
	 */
	static undefined SetUnk101013d8(undefined p_flag);

protected:
	/**
	 * @brief [AI] Updates object's and geometry's world transformation based on parent's world matrix.
	 * @param parent2world [AI] The parent's world transformation matrix.
	 * @details [AI] Ensures both internal state and geometry group match the new world location/orientation.
	 */
	void UpdateWorldData(const Matrix4& parent2world) override; // vtable+0x28

	/**
	 * @brief [AI] Root group for all geometry/renderable objects for this ROI.
	 */
	Tgl::Group* geometry; // 0xdc

	/**
	 * @brief [AI] Unidentified state integer, typically initialized to -1.
	 * @details [AI] Usage unclear; may control ROI behavior or rendering modes. [AI_SUGGESTED_NAME: internalState]
	 */
	int m_unk0xe0;        // 0xe0
};

// SYNTHETIC: LEGO1 0x100aa250
// ViewROI::`scalar deleting destructor'

#endif // VIEWROI_H