#ifndef MXQUATERNION_H
#define MXQUATERNION_H

#include "mxgeometry4d.h"

// SIZE 0x34

/**
 * @brief Quaternion interpolation utility for 4D transformations, supporting quaternion start/end points and spherical interpolation. [AI] 
 * 
 * Handles the conversion of 4x4 transformation matrices to quaternion representations, as well as interpolation (slerp) between two quaternions.
 * Used for smooth rotation transitions in animations or transformations. Can also convert results back to matrix form. [AI]
 */
class MxQuaternionTransformer {
public:
	/// @brief Interpolation state flags. [AI]
	enum {
		c_startSet = 0x01, ///< Start quaternion has been set. [AI]
		c_endSet = 0x02    ///< End quaternion has been set. [AI]
	};

	/**
	 * @brief Default constructor; flags zeroed, state unset. [AI]
	 */
	MxQuaternionTransformer() : m_flags(0) {}

	/**
	 * @brief Ensures shortest path interpolation by potentially flipping the end quaternion's sign. [AI]
	 * 
	 * If the direction from start to end quaternion is longer than the opposite direction, the end quaternion is negated.
	 * This ensures proper spherical interpolation (prevents spinning the "long way" around the sphere). Returns 0 on success, -1 if neither start or end are set. [AI]
	 */
	inline long NormalizeDirection();

	/**
	 * @brief Sets start and end quaternions by converting two matrices to quaternion form. [AI]
	 *
	 * Equivalent to calling SetStart followed by SetEnd. [AI]
	 * @param p_m1 Matrix to use as start quaternion. [AI]
	 * @param p_m2 Matrix to use as end quaternion. [AI]
	 */
	inline void SetStartEnd(Matrix4& p_m1, Matrix4& p_m2);

	/**
	 * @brief Sets the start quaternion from a matrix. [AI]
	 * @param p_m Matrix representing the start orientation. [AI]
	 */
	inline void SetStart(Matrix4& p_m);

	/**
	 * @brief Sets the end quaternion from a matrix. [AI]
	 * @param p_m Matrix representing the end orientation. [AI]
	 */
	inline void SetEnd(Matrix4& p_m);

	/**
	 * @brief Sets the start quaternion from a 4D vector. [AI]
	 * @param p_v Vector representing the start quaternion (x, y, z, w). [AI]
	 */
	inline void SetStart(Vector4& p_v);

	/**
	 * @brief Sets the end quaternion from a 4D vector. [AI]
	 * @param p_v Vector representing the end quaternion (x, y, z, w). [AI]
	 */
	inline void SetEnd(Vector4& p_v);

	/**
	 * @brief Interpolates between start and end quaternions using spherical interpolation (slerp) and produces a 4x4 matrix. [AI]
	 * 
	 * @param p_matrix Matrix to receive the interpolated transformation. [AI]
	 * @param p_f Interpolation parameter between 0.0f (start) and 1.0f (end). [AI]
	 * @return 0 if successful, -1 if interpolation failed (e.g., neither start nor end set). [AI]
	 */
	inline int InterpolateToMatrix(Matrix4& p_matrix, float p_f);

	/**
	 * @brief Retrieves the stored start and end quaternions as 4D vectors. [AI] 
	 * 
	 * @param p_startQuat Returned start quaternion. [AI]
	 * @param p_endQuat Returned end quaternion. [AI]
	 */
	void GetQuat(Vector4& p_startQuat, Vector4& p_endQuat) const
	{
		p_startQuat = m_startQuat;
		p_endQuat = m_endQuat;
	}

	/**
	 * @brief Returns current flag state indicating which ends are set. [AI]
	 */
	undefined4 GetFlags() const { return m_flags; }

private:
	/**
	 * @brief Performs internal slerp or direct interpolation between two quaternions based on set flags. [AI]
	 *
	 * Handles various cases: start only, end only, or both set. For both set, performs normalized spherical interpolation (slerp); properly handles the edge case of almost opposite quaternions. [AI]
	 *
	 * @param p_v Output interpolated quaternion as a 4D vector. [AI]
	 * @param p_f Interpolation factor between 0 (start) and 1 (end). [AI]
	 * @return 0 on success, -1 if interpolation is not possible with current flags. [AI]
	 */
	inline int Interpolate(Vector4& p_v, float p_f);

	Mx4DPointFloat m_startQuat; ///< Start orientation as quaternion. [AI]
	Mx4DPointFloat m_endQuat;   ///< End orientation as quaternion. [AI]
	MxU32 m_flags;              ///< Bitflags tracking which quaternions are set. [AI]
};

#endif // MXQUATERNION_H