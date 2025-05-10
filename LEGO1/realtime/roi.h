#ifndef ROI_H
#define ROI_H

// ROI stands for Real-time Object Instance.

#include "compat.h"
#include "decomp.h"
#include "lodlist.h"
#include "mxgeometry/mxgeometry3d.h"
#include "mxstl/stlcompat.h"

/*
 * A simple bounding box object with Min and Max accessor methods.
 */
// SIZE 0x28
/**
 * @brief [AI] Represents an axis-aligned bounding box in 3D space, using minimum and maximum points.
 * @details [AI] Used for fast collision and intersection tests for objects in the game world.
 */
class BoundingBox {
public:
	/**
	 * @brief [AI] Const accessor for the minimum corner of the bounding box.
	 * @return Reference to the minimum point [AI]
	 */
	const Vector3& Min() const { return min; }
	/**
	 * @brief [AI] Non-const accessor for the minimum corner of the bounding box.
	 * @return Reference to the minimum point [AI]
	 */
	Vector3& Min() { return min; }
	/**
	 * @brief [AI] Const accessor for the maximum corner of the bounding box.
	 * @return Reference to the maximum point [AI]
	 */
	const Vector3& Max() const { return max; }
	/**
	 * @brief [AI] Non-const accessor for the maximum corner of the bounding box.
	 * @return Reference to the maximum point [AI]
	 */
	Vector3& Max() { return max; }

private:
	Mx3DPointFloat min; ///< [AI] Minimum corner (lowest x, y, z) [AI]
	Mx3DPointFloat max; ///< [AI] Maximum corner (highest x, y, z) [AI]
};

/*
 * A simple bounding sphere object with center and radius accessor methods.
 */
// SIZE 0x18
/**
 * @brief [AI] Represents a bounding sphere in 3D space with center and radius.
 * @details [AI] Used for fast object intersection tests, e.g. for culling or selecting objects in the world.
 */
class BoundingSphere {
public:
	/**
	 * @brief [AI] Const accessor for the center of the sphere.
	 * @return Reference to the center point [AI]
	 */
	const Vector3& Center() const { return center; }
	/**
	 * @brief [AI] Non-const accessor for the center of the sphere.
	 * @return Reference to the center point [AI]
	 */
	Vector3& Center() { return center; }
	/**
	 * @brief [AI] Const accessor for the sphere radius.
	 * @return Reference to the radius value [AI]
	 */
	const float& Radius() const { return radius; }
	/**
	 * @brief [AI] Non-const accessor for the sphere radius.
	 * @return Reference to the radius value [AI]
	 */
	float& Radius() { return radius; }

	// SYNTHETIC: BETA10 0x1001fb90
	// BoundingSphere::operator=

private:
	Mx3DPointFloat center; ///< [AI] Center of the sphere [AI]
	float radius;          ///< [AI] Radius of the sphere [AI]
};

/*
 * Abstract base class representing a single LOD version of
 * a geometric object.
 */
// VTABLE: LEGO1 0x100dbd90
// SIZE 0x04
/**
 * @brief [AI] Abstract base class for a Level-of-Detail (LOD) variant of a geometric object.
 * @details [AI] Used in LOD systems for 3D world objects, providing geometric information for rendering or picking.
 */
class LODObject {
public:
	// LODObject();

	// FUNCTION: LEGO1 0x100a6f00
	virtual ~LODObject() {}

	/**
	 * @brief [AI] Returns the average polygon area for this LOD. [AI]
	 */
	virtual double AveragePolyArea() const = 0; // vtable+0x04
	/**
	 * @brief [AI] Returns the number of vertices for this LOD. [AI]
	 */
	virtual int NVerts() const = 0;             // vtable+0x08
	/**
	 * @brief [AI] Returns the number of polygons for this LOD. [AI]
	 */
	virtual int NumPolys() const = 0;           // vtable+0x0c
	/**
	 * @brief [AI] Unknown method related to the LOD. [AI_UNKNOWN] [AI]
	 */
	virtual float VTable0x10() = 0;             // vtable+0x10

	// SYNTHETIC: LEGO1 0x100a6f10
	// LODObject::`scalar deleting destructor'
};

/*
 * A CompoundObject is simply a set of ROI objects which
 * all together represent a single object with sub-parts.
 */
/**
 * @brief [AI] Typedef for a collection of ROI pointers representing compound objects with multiple sub-ROIs. [AI]
 * @details [AI] Used when an object is constructed from several sub-parts, like a vehicle made of several ROI elements.
 */
class ROI;
// typedef std::set<ROI*, std::less<const ROI*> > CompoundObject;
typedef list<ROI*> CompoundObject;

/*
 * A ROIList is a list of ROI objects.
 */
/**
 * @brief [AI] Typedef for a list of ROI pointers. [AI]
 * @details [AI] Used to store multiple real-time object instance (ROI) pointers for batch operations or LOD selection.
 */
typedef vector<const ROI*> ROIList;

/*
 * A simple list of integers.
 * Returned by RealtimeView::SelectLODs as indices into an ROIList.
 */
/**
 * @brief [AI] Typedef for a list of integer indices, e.g. for LOD selection results. [AI]
 * @details [AI] Used as indices into ROI lists, e.g. RealtimeView::SelectLODs returns indices corresponding to selected LODs for each ROI.
 */
typedef vector<int> IntList;

// VTABLE: LEGO1 0x100dbc38
// SIZE 0x10
/**
 * @brief [AI] Abstract base class for Real-time Object Instances (ROI) in the world.
 * @details [AI] Handles the basic properties and methods for game engine objects placed in the 3D world, including LODs, compound structure, and visibility. Subclasses provide transformations and geometry.
 */
class ROI {
public:
	/**
	 * @brief [AI] Constructs an empty ROI, initially visible with no LOD or compound object assigned. [AI]
	 */
	ROI()
	{
		comp = 0;
		lods = 0;
		m_visible = true;
	}
	/**
	 * @brief [AI] Destroys the ROI and asserts that 'comp' and 'lods' are managed/deleted by derived types. [AI]
	 */
	virtual ~ROI()
	{
		// if derived class set the comp and lods, it should delete them
		assert(!comp);
		assert(!lods);
	}
	/**
	 * @brief [AI] Returns the intrinsic importance (used for LOD selection, culling etc). Pure virtual.
	 */
	virtual float IntrinsicImportance() const = 0;                    // vtable+0x04
	/**
	 * @brief [AI] Returns the object's world-space velocity as a pointer to float values. Pure virtual.
	 * @return Pointer to float array (typically 3 floats for velocity) [AI]
	 */
	virtual const float* GetWorldVelocity() const = 0;                // vtable+0x08
	/**
	 * @brief [AI] Returns the world-space bounding box of the object. Pure virtual.
	 */
	virtual const BoundingBox& GetWorldBoundingBox() const = 0;       // vtable+0x0c
	/**
	 * @brief [AI] Returns the world-space bounding sphere of the object. Pure virtual.
	 */
	virtual const BoundingSphere& GetWorldBoundingSphere() const = 0; // vtable+0x10

	/**
	 * @brief [AI] Returns the LOD list associated with this ROI, or NULL if not set. [AI]
	 */
	const LODListBase* GetLODs() const { return lods; }
	/**
	 * @brief [AI] Returns the LODObject at the specified index. Asserts that LODs are present. [AI]
	 * @param i Index of the LOD to return. [AI]
	 */
	const LODObject* GetLOD(int i) const
	{
		assert(lods);
		return (*lods)[i];
	}
	/**
	 * @brief [AI] Returns the number of available LODs for this ROI. [AI]
	 */
	int GetLODCount() const { return lods ? lods->Size() : 0; }

	/**
	 * @brief [AI] Returns the pointer to the compound object structure, or NULL if not present. [AI]
	 */
	// FUNCTION: BETA10 0x10027110
	const CompoundObject* GetComp() const { return comp; }

	/**
	 * @brief [AI] Returns the visibility flag; true if visible, false if hidden. [AI]
	 */
	// FUNCTION: BETA10 0x10049e10
	unsigned char GetVisibility() { return m_visible; }

	/**
	 * @brief [AI] Sets the visibility flag to the provided value. [AI]
	 * @param p_visible Set true to make visible, false to hide. [AI]
	 */
	// FUNCTION: BETA10 0x10011720
	void SetVisibility(unsigned char p_visible) { m_visible = p_visible; }

	// SYNTHETIC: LEGO1 0x100a5d60
	// ROI::`scalar deleting destructor'

protected:
	CompoundObject* comp;    ///< [AI] List of sub-ROIs composing this ROI (compound object), or NULL. [AI]
	LODListBase* lods;       ///< [AI] Pointer to list of LODObject instances, or NULL if not set. [AI]
	unsigned char m_visible; ///< [AI] Visibility flag: nonzero = visible. [AI]
};

// TEMPLATE: LEGO1 0x10084930
// list<ROI *,allocator<ROI *> >::~list<ROI *,allocator<ROI *> >

// SYNTHETIC: LEGO1 0x100a5d50
// ROI::~ROI

#endif // ROI_H
