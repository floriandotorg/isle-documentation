#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "vector.h"

#include <math.h>
#include <memory.h>

/**
 * @fn void Vector2::AddImpl(const float* p_value)
 * @brief [AI] Adds a 2D float array to the vector data in-place. This is used for vector addition with an array.
 * @param p_value Pointer to a float array containing the values to add.
 * @details [AI] Each component of the input array is added to the corresponding component of the vector. The length must be 2.
 */
void Vector2::AddImpl(const float* p_value);

/**
 * @fn void Vector2::AddImpl(float p_value)
 * @brief [AI] Adds a scalar value to both components of the vector.
 * @param p_value The scalar value to add.
 * @details [AI] The scalar is added to both x and y components.
 */
void Vector2::AddImpl(float p_value);

/**
 * @fn void Vector2::SubImpl(const float* p_value)
 * @brief [AI] Subtracts a 2D float array from the vector data in-place.
 * @param p_value Pointer to a float array containing the values to subtract.
 * @details [AI] Each component of the input array is subtracted from the corresponding component of the vector. The length must be 2.
 */
void Vector2::SubImpl(const float* p_value);

/**
 * @fn void Vector2::MulImpl(const float* p_value)
 * @brief [AI] Multiplies the vector by another 2D float array component-wise.
 * @param p_value Pointer to a float array containing the values to multiply by.
 * @details [AI] Each component of the vector is multiplied by the corresponding component in the input array.
 */
void Vector2::MulImpl(const float* p_value);

/**
 * @fn void Vector2::MulImpl(const float& p_value)
 * @brief [AI] Multiplies both components of the vector by a scalar.
 * @param p_value The scalar value to multiply by.
 * @details [AI] Both components are multiplied by the scalar.
 */
void Vector2::MulImpl(const float& p_value);

/**
 * @fn void Vector2::DivImpl(const float& p_value)
 * @brief [AI] Divides both components of the vector by a scalar.
 * @param p_value The scalar value to divide by.
 * @details [AI] Both components are divided by the scalar. No zero check.
 */
void Vector2::DivImpl(const float& p_value);

/**
 * @fn float Vector2::DotImpl(const float* p_a, const float* p_b) const
 * @brief [AI] Computes the dot product of two 2D float arrays.
 * @param p_a Pointer to first 2D float array.
 * @param p_b Pointer to second 2D float array.
 * @return The resulting dot product.
 * @details [AI] Calculates and returns p_a[0]*p_b[0] + p_a[1]*p_b[1].
 */
float Vector2::DotImpl(const float* p_a, const float* p_b) const;

/**
 * @fn void Vector2::SetData(float* p_data)
 * @brief [AI] Sets the internal data pointer of the vector to the provided memory.
 * @param p_data Pointer to external float array to use as vector data.
 * @details [AI] Allows reusing memory or pointing to external data.
 */
void Vector2::SetData(float* p_data);

/**
 * @fn void Vector2::EqualsImpl(const float* p_data)
 * @brief [AI] Copies the values from a float array into the vector's data.
 * @param p_data Pointer to float array containing the values to copy.
 * @details [AI] Uses memcpy for fast assignment of both vector components.
 */
void Vector2::EqualsImpl(const float* p_data);

/**
 * @fn float* Vector2::GetData()
 * @brief [AI] Returns a modifiable pointer to the underlying vector data.
 * @return Pointer to internal float array representing the vector.
 * @details [AI] This pointer refers to the vector's storage of x and y.
 */
float* Vector2::GetData();

/**
 * @fn const float* Vector2::GetData() const
 * @brief [AI] Returns a read-only pointer to the underlying vector data.
 * @return Constant pointer to internal float array.
 * @details [AI] Allows access to internal representation for read-only purposes.
 */
const float* Vector2::GetData() const;

/**
 * @fn void Vector2::Clear()
 * @brief [AI] Sets both components of the vector to zero.
 * @details [AI] Uses memset to zero the vector.
 */
void Vector2::Clear();

/**
 * @fn float Vector2::Dot(const float* p_a, const float* p_b) const
 * @brief [AI] Computes the dot product of two 2D float arrays.
 * @param p_a Pointer to first 2D float array.
 * @param p_b Pointer to second 2D float array.
 * @return Result of dot product calculation.
 * @details [AI] Forwards to DotImpl.
 */
float Vector2::Dot(const float* p_a, const float* p_b) const;

/**
 * @fn float Vector2::Dot(const Vector2& p_a, const Vector2& p_b) const
 * @brief [AI] Computes the dot product between two Vector2 objects.
 * @param p_a The first vector.
 * @param p_b The second vector.
 * @return Result of dot product.
 * @details [AI] Uses internal data arrays of the Vector2 instances.
 */
float Vector2::Dot(const Vector2& p_a, const Vector2& p_b) const;

/**
 * @fn float Vector2::Dot(const float* p_a, const Vector2& p_b) const
 * @brief [AI] Computes the dot product of a float array and a Vector2.
 * @param p_a Float array representing a 2D vector.
 * @param p_b Vector2 instance.
 * @return Result of dot product.
 * @details [AI] Uses input array and vector's data.
 */
float Vector2::Dot(const float* p_a, const Vector2& p_b) const;

/**
 * @fn float Vector2::Dot(const Vector2& p_a, const float* p_b) const
 * @brief [AI] Computes the dot product of a Vector2 and a float array.
 * @param p_a Vector2 instance.
 * @param p_b Float array representing 2D data.
 * @return Result of dot product.
 * @details [AI] Uses vector's data and input array.
 */
float Vector2::Dot(const Vector2& p_a, const float* p_b) const;

/**
 * @fn float Vector2::LenSquared() const
 * @brief [AI] Returns the squared Euclidean length of the vector.
 * @return The sum of squares of the x and y values.
 * @details [AI] Useful for distance comparisons without sqrt.
 */
float Vector2::LenSquared() const;

/**
 * @fn int Vector2::Unitize()
 * @brief [AI] Normalizes the vector to have unit length (if length > 0).
 * @return 0 on success, -1 if length is zero.
 * @details [AI] Divides components by the vector's length. Safe against zero division.
 */
int Vector2::Unitize();

/**
 * @fn void Vector2::operator+=(float p_value)
 * @brief [AI] Adds a scalar to both components of the vector.
 * @param p_value The scalar value to add.
 * @details [AI] In-place modification.
 */
void Vector2::operator+=(float p_value);

/**
 * @fn void Vector2::operator+=(const float* p_other)
 * @brief [AI] Adds values from an array to the vector in-place.
 * @param p_other Pointer to float array (length 2).
 * @details [AI] Both vector components are incremented.
 */
void Vector2::operator+=(const float* p_other);

/**
 * @fn void Vector2::operator+=(const Vector2& p_other)
 * @brief [AI] Adds another Vector2 to this vector in-place.
 * @param p_other Vector2 instance to add.
 * @details [AI] Component-wise addition.
 */
void Vector2::operator+=(const Vector2& p_other);

/**
 * @fn void Vector2::operator-=(const float* p_other)
 * @brief [AI] Subtracts values from an array from the vector in-place.
 * @param p_other Pointer to float array (length 2).
 * @details [AI] Component-wise subtraction.
 */
void Vector2::operator-=(const float* p_other);

/**
 * @fn void Vector2::operator-=(const Vector2& p_other)
 * @brief [AI] Subtracts another Vector2 from this vector in-place.
 * @param p_other Vector2 instance to subtract.
 * @details [AI] Component-wise subtraction.
 */
void Vector2::operator-=(const Vector2& p_other);

/**
 * @fn void Vector2::operator*=(const float* p_other)
 * @brief [AI] Multiplies this vector component-wise by values from an array.
 * @param p_other Pointer to float array (length 2).
 * @details [AI] In-place multiplication.
 */
void Vector2::operator*=(const float* p_other);

/**
 * @fn void Vector2::operator*=(const Vector2& p_other)
 * @brief [AI] Multiplies this vector component-wise by another Vector2.
 * @param p_other The Vector2 instance to multiply by.
 * @details [AI] In-place multiplication.
 */
void Vector2::operator*=(const Vector2& p_other);

/**
 * @fn void Vector2::operator*=(const float& p_value)
 * @brief [AI] Multiplies both components by a scalar value.
 * @param p_value Scalar multiplier.
 * @details [AI] In-place scaling.
 */
void Vector2::operator*=(const float& p_value);

/**
 * @fn void Vector2::operator/=(const float& p_value)
 * @brief [AI] Divides both components of the vector by a scalar value.
 * @param p_value Scalar divisor.
 * @details [AI] In-place division, no zero check.
 */
void Vector2::operator/=(const float& p_value);

/**
 * @fn void Vector2::operator=(const float* p_other)
 * @brief [AI] Assigns vector values from a float array (length 2).
 * @param p_other Pointer to the values array.
 * @details [AI] Assignment occurs with memcpy.
 */
void Vector2::operator=(const float* p_other);

/**
 * @fn void Vector2::operator=(const Vector2& p_other)
 * @brief [AI] Assigns vector values from another Vector2.
 * @param p_other The Vector2 to copy from.
 * @details [AI] Copies both x and y components.
 */
void Vector2::operator=(const Vector2& p_other);

#endif // VECTOR2D_H
