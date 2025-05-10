#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "vector.h"

#include <math.h>
#include <memory.h>

/**
 * @brief [AI] Implements vector addition for Vector4 using a float array as input.
 * 
 * This method adds the elements of p_value (assumed to be an array of at least four floats)
 * to this vector's components, modifying all four entries including the w component.
 * Calls Vector3::AddImpl for the first three elements and adds the fourth explicitly.
 *
 * @param p_value Pointer to an array of four floats to add to the vector components. [AI]
 */
void Vector4::AddImpl(const float* p_value);

/**
 * @brief [AI] Adds a scalar value to all four components of the vector.
 *
 * Each component (x, y, z, w) has p_value added to it.
 * 
 * @param p_value Scalar value to add to each component. [AI]
 */
void Vector4::AddImpl(float p_value);

/**
 * @brief [AI] Subtracts the elements of a float array from the vector's components.
 * 
 * Performs component-wise subtraction for x,y,z (via Vector3::SubImpl) and then subtracts the fourth element from w.
 *
 * @param p_value Array of at least four floats to subtract. [AI]
 */
void Vector4::SubImpl(const float* p_value);

/**
 * @brief [AI] Multiplies each component of the vector by the corresponding element of p_value.
 * 
 * Multiplies x, y, z using Vector3::MulImpl and multiplies w by p_value[3].
 *
 * @param p_value Pointer to an array of four floats for component-wise multiplication. [AI]
 */
void Vector4::MulImpl(const float* p_value);

/**
 * @brief [AI] Multiplies all components of the vector by a scalar.
 *
 * Each component (x, y, z, w) is multiplied by p_value.
 * 
 * @param p_value Scalar multiplier. [AI]
 */
void Vector4::MulImpl(const float& p_value);

/**
 * @brief [AI] Divides all components of the vector by a scalar value.
 *
 * Each component (x, y, z, w) is divided by p_value.
 * 
 * @param p_value Scalar divisor. [AI]
 */
void Vector4::DivImpl(const float& p_value);

/**
 * @brief [AI] Calculates the dot product for two float[4] arrays as if they are 4D vectors.
 *
 * The dot product includes all four components.
 *
 * @param p_a First operand, array of 4 floats. [AI]
 * @param p_b Second operand, array of 4 floats. [AI]
 * @return The scalar dot product of the two input vectors. [AI]
 */
float Vector4::DotImpl(const float* p_a, const float* p_b) const;

/**
 * @brief [AI] Sets the vector's components to those in a float[4] array.
 * 
 * Performs a memcpy for all four components.
 * 
 * @param p_data Pointer to an array of four floats to copy from. [AI]
 */
void Vector4::EqualsImpl(const float* p_data);

/**
 * @brief [AI] Sets the vector as a matrix product of a 4D vector with a 4x4 matrix (column-major).
 * 
 * The product is:
 * m_data[i] = sum_over_j(p_vec[j] * p_mat[j*4 + i])
 * 
 * @param p_vec The 4D input vector as an array. [AI]
 * @param p_mat The 4x4 matrix as a flat array of 16 floats (column-major order). [AI]
 */
void Vector4::SetMatrixProduct(const float* p_vec, const float* p_mat);

/**
 * @brief [AI] Sets this vector as the product of another Vector4 and a 4x4 matrix.
 *
 * Calls SetMatrixProduct with the internal data of p_a.
 * 
 * @param p_a The input Vector4. [AI]
 * @param p_b Pointer to a flat array of 16 floats representing a 4x4 matrix. [AI]
 */
void Vector4::SetMatrixProduct(const Vector4& p_a, const float* p_b);

/**
 * @brief [AI] Sets all four components of the vector to zero.
 *
 * Uses memset to set all data entries to 0.
 */
void Vector4::Clear();

/**
 * @brief [AI] Computes the squared length (norm) of the Vector4.
 * 
 * Returns x^2 + y^2 + z^2 + w^2.
 *
 * @return Squared length of the vector. [AI]
 */
float Vector4::LenSquared() const;

/**
 * @brief [AI] Sets all components of the vector to the given value.
 * 
 * Fills x, y, z, w with p_value.
 *
 * @param p_value The value to assign to all components. [AI]
 */
void Vector4::Fill(const float& p_value);

/**
 * @brief [AI] Normalizes the vector as a quaternion.
 * 
 * If x, y, z components' squared length is nonzero, the quaternion is normalized:
 * - w is set to cos(theta)
 * - (x, y, z) is scaled based on sin(theta)/sqrt(length)
 * If not, returns -1 as error.
 *
 * @details [AI] This is useful for ensuring a quaternion used for rotations is normalized.
 * 
 * @return 0 if succeeded, -1 if cannot normalize due to zero length of spatial part. [AI]
 */
int Vector4::NormalizeQuaternion();

/**
 * @brief [AI] Sets this vector to the Hamilton product of two quaternions (Vector4s).
 *
 * The result is the quaternion multiplication of p_a and p_b, written into this.
 * Uses Vector3 cross product for the vector part and a combination of scalar and vector terms for the real part.
 *
 * @param p_a Left operand quaternion. [AI]
 * @param p_b Right operand quaternion. [AI]
 * @return Always returns 0. [AI]
 */
int Vector4::EqualsHamiltonProduct(const Vector4& p_a, const Vector4& p_b);

#endif // VECTOR4D_H
