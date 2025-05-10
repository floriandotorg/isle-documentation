#ifndef REALTIME_H
#define REALTIME_H

#include "matrix.h"
#include "roi.h"

/// @brief [AI] Normalizes the given 3D vector, storing the result in the destination (dst) array. [AI]
/// @details [AI] NORMVEC3(dst, src) calculates the length of 'src', and divides each component of 'src' by its length, writing the normalized vector into 'dst'. [AI]
#define NORMVEC3(dst, src)                                                                                             \
	{                                                                                                                  \
		double len = sqrt(NORMSQRD3(src));                                                                             \
		VDS3(dst, src, len);                                                                                           \
	}

/// @brief [AI] Computes a transformation matrix based on a position, direction, and up vector. [AI]
/// @param p_posVec World position vector (translation) to use for transformation. [AI]
/// @param p_dirVec World direction vector (Z axis of the matrix). This will be normalized. [AI]
/// @param p_upVec World up vector (Y axis of the matrix). This will be normalized and orthogonalized. [AI]
/// @param p_outMatrix Output parameter to receive the resulting 4x4 transformation matrix, built from the supplied vectors. [AI]
/// @details [AI] The resulting matrix is suitable for orienting/repositioning an object in 3D space: the direction is used for the forward axis, up for vertical axis, and the function ensures all axes are orthogonal and normalized. [AI]
void CalcLocalTransform(const Vector3& p_posVec, const Vector3& p_dirVec, const Vector3& p_upVec, Matrix4& p_outMatrix);

/// @brief [AI] Computes the world-space bounding box and bounding sphere for an ROI using a modeling sphere and a transformation matrix. [AI]
/// @param modelling_sphere The source bounding sphere describing the object in its local/model space. [AI]
/// @param local2world Transformation matrix converting local coordinates to world coordinates. [AI]
/// @param[out] BoundingBox Output axis-aligned bounding box computed in world space. [AI]
/// @param[out] BoundingSphere Output bounding sphere transformed to world space. [AI]
/// @details [AI] Helper utility for ROI (Real-time Object Instance) classes, typically used in update_world_bounding_volumes() to create world-space volumes for culling or collision, by transforming an existing modeling sphere. [AI]
void CalcWorldBoundingVolumes(const BoundingSphere& modelling_sphere, const Matrix4& local2world, BoundingBox&, BoundingSphere&);

#endif // REALTIME_H
