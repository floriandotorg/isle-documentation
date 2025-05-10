#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

// Note: virtual function overloads appear in the virtual table
// in reverse order of appearance.

/**
 * @brief Matrix-like wrapper of 4x4 float array, with no methods. [AI]
 * @details [AI] Used as a POD type for passing or storing 4x4 matrices. Its real role is for reinterpretation or passing untyped matrix data.
 */
struct UnknownMatrixType {
	float m_data[4][4]; ///< [AI] Raw matrix data storage (row-major 4x4 floats).
};

/**
 * @brief 4x4 Matrix class with virtual interface for manipulation and transformation. [AI]
 * @details [AI] Abstracts a 4x4 matrix (typically for geometric use, such as transformations in 3D graphics). Provides various matrix operations, including assignment, translation, scaling, rotation, product (multiplication), identity creation, conversion to and from quaternion, and data access. Designed for polymorphic use with virtual methods, which is important for engine extensibility.
 */
// VTABLE: LEGO1 0x100d4350
// VTABLE: BETA10 0x101b8340
// SIZE 0x08
class Matrix4 {
protected:
	/**
	 * @brief Pointer to 4x4 float array, owns or refers to matrix data. [AI]
	 */
	float (*m_data)[4];

public:
	/**
	 * @brief Constructs a Matrix4 object referring to the given 4x4 float array. [AI]
	 * @param p_data Pointer to a 4x4 array of floats used as matrix data. [AI]
	 */
	Matrix4(float (*p_data)[4]) { SetData(p_data); }

	/**
	 * @brief Set the matrix elements from a 4x4 float array. [AI]
	 * @param p_data Pointer to an external 4x4 float data array. [AI]
	 */
	inline virtual void Equals(float (*p_data)[4]);                                           // vtable+0x04

	/**
	 * @brief Copies the matrix from another Matrix4. [AI]
	 * @param p_matrix Reference to another matrix to copy from. [AI]
	 */
	inline virtual void Equals(const Matrix4& p_matrix);                                      // vtable+0x00

	/**
	 * @brief Set this matrix instance to use/point to a new 4x4 data block. [AI]
	 * @param p_data Pointer to a new 4x4 float array. [AI]
	 */
	inline virtual void SetData(float (*p_data)[4]);                                          // vtable+0x0c

	/**
	 * @brief Copies the matrix data from a raw UnknownMatrixType instance. [AI]
	 * @param p_matrix Source UnknownMatrixType containing a 4x4 float array. [AI]
	 */
	inline virtual void SetData(UnknownMatrixType& p_matrix);                                 // vtable+0x08

	/**
	 * @brief Gets modifiable access to the 4x4 float matrix. [AI]
	 * @return Pointer to the 4x4 float array used by the Matrix4. [AI]
	 */
	inline virtual float (*GetData())[4];                                                     // vtable+0x14

	/**
	 * @brief Gets read-only access to the 4x4 float matrix data. [AI]
	 * @return Const pointer to the 4x4 float array used by the Matrix4. [AI]
	 */
	inline virtual float (*GetData() const)[4];                                               // vtable+0x10

	/**
	 * @brief Accesses an individual element of the matrix in writable form. [AI]
	 * @param p_row Row index (0-3). [AI]
	 * @param p_col Column index (0-3). [AI]
	 * @return Pointer to the float element at the specified row and column. [AI]
	 */
	inline virtual float* Element(int p_row, int p_col);                                      // vtable+0x1c

	/**
	 * @brief Accesses an individual element in read-only form. [AI]
	 * @param p_row Row index. [AI]
	 * @param p_col Column index. [AI]
	 * @return Const pointer to the float element at the specified row/col. [AI]
	 */
	inline virtual const float* Element(int p_row, int p_col) const;                          // vtable+0x18

	/**
	 * @brief Sets every element of the matrix to zero. [AI]
	 */
	inline virtual void Clear();                                                              // vtable+0x20

	/**
	 * @brief Sets this matrix to identity (diagonal 1, others 0). [AI]
	 */
	inline virtual void SetIdentity();                                                        // vtable+0x24

	/**
	 * @brief Assign/copy another matrix's values into this one. [AI]
	 * @param p_matrix Source matrix to assign from. [AI]
	 */
	inline virtual void operator=(const Matrix4& p_matrix);                                   // vtable+0x28

	/**
	 * @brief In-place matrix addition with external float[4][4]. [AI]
	 * @param p_data Flat pointer to matrix to sum. [AI]
	 * @return Reference to the modified matrix. [AI]
	 */
	inline virtual Matrix4& operator+=(float (*p_data)[4]);                                   // vtable+0x2c

	/**
	 * @brief Applies translation by amounts along X, Y, Z axes. [AI]
	 * @param p_x Amount to translate along X. [AI]
	 * @param p_y Amount to translate along Y. [AI]
	 * @param p_z Amount to translate along Z. [AI]
	 */
	inline virtual void TranslateBy(const float& p_x, const float& p_y, const float& p_z);    // vtable+0x30

	/**
	 * @brief Overwrites the translation part of the matrix (last column). [AI]
	 * @param p_x New translation X. [AI]
	 * @param p_y New translation Y. [AI]
	 * @param p_z New translation Z. [AI]
	 */
	inline virtual void SetTranslation(const float& p_x, const float& p_y, const float& p_z); // vtable+0x34

	/**
	 * @brief Multiplies two 4x4 float matrices, storing result in this. [AI]
	 * @param p_a First matrix operand (left-hand side). [AI]
	 * @param p_b Second matrix operand (right-hand side). [AI]
	 */
	inline virtual void Product(float (*p_a)[4], float (*p_b)[4]);                            // vtable+0x3c

	/**
	 * @brief Multiplies two Matrix4s, storing result in this matrix. [AI]
	 * @param p_a First operand Matrix4. [AI]
	 * @param p_b Second operand Matrix4. [AI]
	 */
	inline virtual void Product(const Matrix4& p_a, const Matrix4& p_b);                      // vtable+0x38

	/**
	 * @brief Converts the 3x3 rotation part of this matrix to a quaternion (Vector4). [AI]
	 * @param p_resultQuat Reference to destination quaternion (Vector4). [AI]
	 */
	inline virtual void ToQuaternion(Vector4& p_resultQuat);                                  // vtable+0x40

	/**
	 * @brief Initializes the matrix from a quaternion (Vector4). [AI]
	 * @param p_vec Quaternion as Vector4. [AI]
	 * @return 0 on failure, nonzero on success. [AI]
	 */
	inline virtual int FromQuaternion(const Vector4& p_vec);                                  // vtable+0x44

	/**
	 * @brief Applies scaling factors along X, Y, and Z axes. [AI]
	 * @param p_x Scale factor for X axis. [AI]
	 * @param p_y Scale factor for Y axis. [AI]
	 * @param p_z Scale factor for Z axis. [AI]
	 */
	inline void Scale(const float& p_x, const float& p_y, const float& p_z);                  // [AI]

	/**
	 * @brief Applies a rotation (in radians or degrees, depending on implementation) about the X axis. [AI]
	 * @param p_angle Angle of rotation (in radians/degrees as used in implementation). [AI]
	 */
	inline void RotateX(const float& p_angle);                                                // [AI]

	/**
	 * @brief Applies a rotation (in radians or degrees, depending on implementation) about the Y axis. [AI]
	 * @param p_angle Angle of rotation. [AI]
	 */
	inline void RotateY(const float& p_angle);                                                // [AI]

	/**
	 * @brief Applies a rotation (in radians or degrees) about the Z axis. [AI]
	 * @param p_angle Angle of rotation. [AI]
	 */
	inline void RotateZ(const float& p_angle);                                                // [AI]

	/**
	 * @brief [AI] Appears to perform some operation using another matrix, but function/purpose unknown.
	 * @param p_mat Reference to another Matrix4. [AI]
	 * @return Possibly an error code or count. [AI]
	 */
	inline int BETA_1005a590(Matrix4& p_mat);                                                 // [AI_UNKNOWN]

	/**
	 * @brief Swaps the data between two rows/columns (presumably). [AI]
	 * @param p_d1 First index (row/column). [AI]
	 * @param p_d2 Second index (row/column). [AI]
	 */
	inline void Swap(int p_d1, int p_d2);                                                     // [AI]

	/**
	 * @brief Array subscript operator for modifiable row access. [AI]
	 * @param idx Row index (0-3). [AI]
	 * @return Pointer to the row's float array. [AI]
	 */
	float* operator[](int idx) { return m_data[idx]; }

	/**
	 * @brief Const array subscript operator for readonly row access. [AI]
	 * @param idx Row index (0-3). [AI]
	 * @return Const pointer to the row's float data. [AI]
	 */
	const float* operator[](int idx) const { return m_data[idx]; }
};

#ifdef COMPAT_MODE
#include "matrix4d.inl.h"
#endif

#endif // MATRIX_H
