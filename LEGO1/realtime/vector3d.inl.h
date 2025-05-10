#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "vector2d.inl.h"

/// @brief Computes the cross product of two 3D vectors represented as float arrays, stores the result in this vector. [AI]
/// @param p_a Pointer to the first input vector (float[3]). [AI]
/// @param p_b Pointer to the second input vector (float[3]). [AI]
void Vector3::EqualsCrossImpl(const float* p_a, const float* p_b);

/// @brief Sets this vector to the cross product of two Vector3 objects. [AI]
/// @param p_a First input vector. [AI]
/// @param p_b Second input vector. [AI]
void Vector3::EqualsCross(const Vector3& p_a, const Vector3& p_b);

/// @brief Sets this vector to the cross product of a Vector3 and a float array. [AI]
/// @param p_a Input Vector3. [AI]
/// @param p_b Pointer to the second input vector (float[3]). [AI]
void Vector3::EqualsCross(const Vector3& p_a, const float* p_b);

/// @brief Sets this vector to the cross product of a float array and a Vector3. [AI]
/// @param p_a Pointer to the first input vector (float[3]). [AI]
/// @param p_b Input Vector3. [AI]
void Vector3::EqualsCross(const float* p_a, const Vector3& p_b);

/// @brief Adds a float array (size 3) component-wise to this vector. [AI]
/// @param p_value Pointer to float array to add (float[3]). [AI]
void Vector3::AddImpl(const float* p_value);

/// @brief Adds a scalar value to each component of this vector. [AI]
/// @param p_value Scalar value to add. [AI]
void Vector3::AddImpl(float p_value);

/// @brief Subtracts a float array (size 3) component-wise from this vector. [AI]
/// @param p_value Pointer to float array to subtract (float[3]). [AI]
void Vector3::SubImpl(const float* p_value);

/// @brief Multiplies this vector component-wise by a float array (size 3). [AI]
/// @param p_value Pointer to float array to multiply (float[3]). [AI]
void Vector3::MulImpl(const float* p_value);

/// @brief Multiplies each component of this vector by a scalar value. [AI]
/// @param p_value Scalar value to multiply. [AI]
void Vector3::MulImpl(const float& p_value);

/// @brief Divides each component of this vector by a scalar value. [AI]
/// @param p_value Scalar value to divide. [AI]
void Vector3::DivImpl(const float& p_value);

/// @brief Computes the dot product of two float arrays representing 3D vectors. [AI]
/// @param p_a Pointer to the first vector (float[3]). [AI]
/// @param p_b Pointer to the second vector (float[3]). [AI]
/// @return Dot product of the two vectors. [AI]
float Vector3::DotImpl(const float* p_a, const float* p_b) const;

/// @brief Sets the internal data of this vector to the contents of the provided float array. [AI]
/// @param p_data Pointer to float array (float[3]) to copy. [AI]
void Vector3::EqualsImpl(const float* p_data);

/// @brief Sets all three components of this vector to zero. [AI]
void Vector3::Clear();

/// @brief Computes the squared length of this vector (avoids sqrt for efficiency). [AI]
/// @return Squared length of the vector. [AI]
float Vector3::LenSquared() const;

/// @brief Sets each component of this vector to the given scalar value. [AI]
/// @param p_value Value to set for all components. [AI]
void Vector3::Fill(const float& p_value);

#endif // VECTOR3D_H