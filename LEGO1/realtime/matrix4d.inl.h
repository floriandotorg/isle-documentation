#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "matrix.h"

#include <math.h>
#include <memory.h>

/**
 * @brief [AI] Copies a 4x4 matrix from an external float array to the internal matrix data.
 * @param p_data 4x4 float array (column-major order) to copy into this matrix. [AI]
 * @details [AI] Performs a memory copy of the input data to the matrix's internal storage.
 */
void Matrix4::Equals(float (*p_data)[4]);

/**
 * @brief [AI] Copies the values from another Matrix4 into this matrix.
 * @param p_matrix Source matrix to copy from. [AI]
 * @details [AI] Uses memcpy for efficient copying of the matrix data.
 */
void Matrix4::Equals(const Matrix4& p_matrix);

/**
 * @brief [AI] Sets the internal matrix storage pointer to the given array. (No copy: shallow set) [AI]
 * @param p_data Pointer to the new 4x4 float array to use as matrix data. [AI]
 * @details [AI] This does not copy the values. Use with care regarding data ownership.
 */
void Matrix4::SetData(float (*p_data)[4]);

/**
 * @brief [AI] Sets the internal matrix storage pointer from an UnknownMatrixType. (No copy: shallow set) [AI]
 * @param p_matrix Source unknown matrix type whose internal data will be used for this matrix. [AI]
 * @details [AI] This operation sets the internal data pointer directly.
 */
void Matrix4::SetData(UnknownMatrixType& p_matrix);

/**
 * @brief [AI] Returns a pointer to the raw 4x4 float matrix data. [AI]
 * @return Pointer to the 4x4 array of floats representing the matrix data. [AI]
 */
float (*Matrix4::GetData())[4];

/**
 * @brief [AI] Const overload for retrieving matrix data pointer.
 * @return Const pointer to the 4x4 float matrix data. [AI]
 */
float (*Matrix4::GetData() const)[4];

/**
 * @brief [AI] Returns a pointer to the element at (row, col) in the matrix. [AI]
 * @param p_row Row index (0-3). [AI]
 * @param p_col Column index (0-3). [AI]
 * @return Pointer to the specific float element within the matrix. [AI]
 */
float* Matrix4::Element(int p_row, int p_col);

/**
 * @brief [AI] Const overload. Returns a pointer to the (row, col) element in the matrix. [AI]
 * @param p_row Row index (0-3). [AI]
 * @param p_col Column index (0-3). [AI]
 * @return Const pointer to the matrix element at specified row/column. [AI]
 */
const float* Matrix4::Element(int p_row, int p_col) const;

/**
 * @brief [AI] Sets all matrix elements to zero. [AI]
 * @details [AI] Effectively zeros out the entire matrix.
 */
void Matrix4::Clear();

/**
 * @brief [AI] Sets this matrix to the identity matrix. [AI]
 * @details [AI] Clears the matrix and sets the main diagonal to 1.
 */
void Matrix4::SetIdentity();

/**
 * @brief [AI] Assigns all values from another matrix to this one.
 * @param p_matrix Source matrix whose values will be copied. [AI]
 * @details [AI] Equivalent to Equals(const Matrix4&).
 */
void Matrix4::operator=(const Matrix4& p_matrix);

/**
 * @brief [AI] Adds all corresponding elements of a float[4][4] to this matrix.
 * @param p_data Source float[4][4] whose elements are added to the matrix. [AI]
 * @return Reference to this matrix, after addition. [AI]
 * @details [AI] Adds raw values in-place compared to array-style addition.
 */
Matrix4& Matrix4::operator+=(float (*p_data)[4]);

/**
 * @brief [AI] Adds a translation vector to the translation row of the matrix (usually row 3). [AI]
 * @param p_x X component of translation. [AI]
 * @param p_y Y component of translation. [AI]
 * @param p_z Z component of translation. [AI]
 * @details [AI] Adjusts only the translation part of the matrix.
 */
void Matrix4::TranslateBy(const float& p_x, const float& p_y, const float& p_z);

/**
 * @brief [AI] Sets the translation portion of the matrix to specified values. [AI]
 * @param p_x X translation value. [AI]
 * @param p_y Y translation value. [AI]
 * @param p_z Z translation value. [AI]
 * @details [AI] Directly writes the values rather than incrementing (see TranslateBy).
 */
void Matrix4::SetTranslation(const float& p_x, const float& p_y, const float& p_z);

/**
 * @brief [AI] Multiplies two 4x4 float matrices, storing result in this matrix. [AI]
 * @param p_a Pointer to first operand 4x4 matrix. [AI]
 * @param p_b Pointer to second operand 4x4 matrix. [AI]
 * @details [AI] Standard matrix multiplication: this = p_a * p_b.
 */
void Matrix4::Product(float (*p_a)[4], float (*p_b)[4]);

/**
 * @brief [AI] Multiplies two Matrix4 objects and stores result in this matrix.
 * @param p_a First operand matrix. [AI]
 * @param p_b Second operand matrix. [AI]
 * @details [AI] Internally calls Product() with their data pointers.
 */
void Matrix4::Product(const Matrix4& p_a, const Matrix4& p_b);

/**
 * @brief [AI] Converts this rotation/transform matrix to a quaternion.
 * @param p_outQuat Output quaternion (Vector4 format: x,y,z,w), filled by the function. [AI]
 * @details [AI] Handles both general and edge cases for numerical consistency.
 * Assumes the matrix represents a rotation. [AI]
 */
void Matrix4::ToQuaternion(Vector4& p_outQuat);

/**
 * @brief [AI] Sets this matrix from a quaternion representing rotation. [AI]
 * @param p_vec Quaternion (Vector4, x,y,z,w) to construct a rotation matrix. [AI]
 * @return 0 on success, -1 on failure (e.g., input is not a unit quaternion). [AI]
 */
int Matrix4::FromQuaternion(const Vector4& p_vec);

/**
 * @brief [AI] Scales the matrix by the given x, y, z factors along each respective axis. [AI]
 * @param p_x Scaling factor for X dimension. [AI]
 * @param p_y Scaling factor for Y dimension. [AI]
 * @param p_z Scaling factor for Z dimension. [AI]
 * @details [AI] Multiplies the respective matrix columns by the factors.
 */
void Matrix4::Scale(const float& p_x, const float& p_y, const float& p_z);

/**
 * @brief [AI] Rotates the matrix around the X axis by the specified angle (in radians). [AI]
 * @param p_angle Angle in radians to rotate. [AI]
 * @details [AI] Modifies relevant elements in place using the rotation formula.
 */
void Matrix4::RotateX(const float& p_angle);

/**
 * @brief [AI] Rotates the matrix around the Y axis by the specified angle (in radians). [AI]
 * @param p_angle Angle in radians. [AI]
 */
void Matrix4::RotateY(const float& p_angle);

/**
 * @brief [AI] Rotates the matrix around the Z axis by the specified angle (in radians). [AI]
 * @param p_angle Angle in radians. [AI]
 */
void Matrix4::RotateZ(const float& p_angle);

/**
 * @brief [AI] Calculates the inverse of this matrix and stores it in p_mat. [AI]
 * @param p_mat Reference to output matrix that receives the inverse. [AI]
 * @return 0 for success, -1 if the matrix is singular (non-invertible). [AI]
 * @details [AI] Uses partial pivoting and Gaussian elimination for inversion.
 */
int Matrix4::BETA_1005a590(Matrix4& p_mat);

/**
 * @brief [AI] Swaps two matrix rows. [AI]
 * @param p_d1 First row to swap. [AI]
 * @param p_d2 Second row to swap. [AI]
 * @details [AI] Used primarily by matrix inversion algorithms for row operations.
 */
void Matrix4::Swap(int p_d1, int p_d2);

#endif // MATRIX4D_H
