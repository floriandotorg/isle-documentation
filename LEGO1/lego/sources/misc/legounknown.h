#ifndef __LEGOUNKNOWN_H
#define __LEGOUNKNOWN_H

#include "legotypes.h"
#include "mxgeometry/mxgeometry3d.h"

class Matrix4;

// SIZE 0x50
/**
 * @brief Opaque Bezier curve utility used for actor or path position interpolation. [AI]
 * @details [AI] 
 * This class appears to be a helper for handling cubic Bezier curves or Hermite splines in 3D,
 * storing up to four control points. Its methods are used to set up the curve with the required 
 * endpoints/tangents and to evaluate positions and directions along the curve.
 * Used for path or animation interpolation. [AI]
 */
class LegoUnknown {
public:
	/**
	 * @brief [AI] Constructs the LegoUnknown object, clearing the internal control points.
	 */
	LegoUnknown();

	/**
	 * @brief [AI] Destructor (no-op).
	 */
	~LegoUnknown();

	/**
	 * @brief [AI] Configure internal curve control points. [AI]
	 * @details [AI] 
	 * Assigns the control points for a cubic spline or Bezier curve, given four 3D points:
	 *   - `p_point1`: The curve start point
	 *   - `p_point2`: Outgoing tangent or first control handle
	 *   - `p_point3`: Curve end point
	 *   - `p_point4`: Incoming tangent or last control handle
	 * The method builds the internal polynomial coefficients required for evaluation. [AI]
	 * @param p_point1 Start point of the curve [AI]
	 * @param p_point2 Outgoing tangent or handle at the start [AI]
	 * @param p_point3 End point of the curve [AI]
	 * @param p_point4 Incoming tangent or handle at the end [AI]
	 */
	void FUN_1009a140(
		const Vector3& p_point1,
		const Vector3& p_point2,
		const Vector3& p_point3,
		const Vector3& p_point4
	);

	/**
	 * @brief [AI] Evaluates the curve and its tangent at `p_f1` and computes the local orthonormal frame. [AI]
	 * @details [AI] 
	 * Given a parameter `p_f1` between 0 and 1, this method calculates:
	 *   - The position and tangent on the curve,
	 *   - Optionally inverts the tangent if `p_und` is set,
	 *   - Builds a local coordinate system based on the tangent and a reference vector `p_v`,
	 *   - Outputs these (position and orthonormal frame) into a `Matrix4` as basis vectors.
	 * Returns FAILURE if vectors cannot be normalized.
	 * @param p_f1 Parameter along the curve, in [0,1]. [AI]
	 * @param p_mat Matrix output: built up with the resulting position (column 3) and basis vectors. [AI]
	 * @param p_v Reference up-direction vector to use for frame computation. [AI]
	 * @param p_und If true, reverses the curve tangent. [AI]
	 * @return Returns SUCCESS if basis computation succeeds, FAILURE otherwise. [AI]
	 */
	LegoResult FUN_1009a1e0(float p_f1, Matrix4& p_mat, Vector3& p_v, LegoU32 p_und);

private:
	/// @brief [AI] Curve polynomial coefficients or control vectors, as 3D points. [AI]
	Mx3DPointFloat m_unk0x00[4]; // 0x00 [AI]
};

#endif // __LEGOUNKNOWN_H
