#ifndef MXMATRIX_H
#define MXMATRIX_H

#include "realtime/matrix4d.inl.h"

// VTABLE: LEGO1 0x100d4300
// VTABLE: BETA10 0x101b82e0
// SIZE 0x48

/**
 * @class MxMatrix
 * @brief [AI] Represents a 4x4 transformation matrix, specialized for the LEGO Island engine and derived from Matrix4. [AI]
 * @details [AI] MxMatrix is an engine-specific wrapper for 4x4 matrices, providing convenient constructors and assignment operators to interoperate with both generic Matrix4 and other MxMatrix instances. It is used for world transforms, camera transforms, and other spatial calculations within the game engine. Its underlying storage is a float 4x4 array.
 * @ingroup Math [AI]
 */
class MxMatrix : public Matrix4 {
public:
	/**
	 * @brief [AI] Default constructor. Initializes the matrix storage and sets identity.
	 * @details [AI] Calls the base Matrix4 constructor with the address of this matrix's underlying storage (m_elements), ensuring all matrix operations operate on this data. Starts as an identity matrix.
	 */
	MxMatrix() : Matrix4(m_elements) {}

	/**
	 * @brief [AI] Copy constructor from another MxMatrix.
	 * @param p_matrix Source MxMatrix to copy. [AI]
	 * @details [AI] Initializes matrix storage as in the default constructor and then copies all elements from the given MxMatrix.
	 */
	MxMatrix(const MxMatrix& p_matrix) : Matrix4(m_elements) { Equals(p_matrix); }

	/**
	 * @brief [AI] Constructor from a generic Matrix4.
	 * @param p_matrix Source Matrix4 to copy. [AI]
	 * @details [AI] Initializes matrix storage and copies the elements from another Matrix4. Provides interoperability with generic matrix math in the engine.
	 */
	MxMatrix(const Matrix4& p_matrix) : Matrix4(m_elements) { Equals(p_matrix); }

	/**
	 * @brief [AI] Subscript operator for access to individual rows of the matrix.
	 * @param idx Row index (0-3). [AI]
	 * @return Pointer to the first element of the row. [AI]
	 * @details [AI] Allows access as m[i][j] where 'i' selects the row and 'j' the column. [AI]
	 */
	float* operator[](int idx) { return m_data[idx]; }

	/**
	 * @brief [AI] Const version of subscript operator.
	 * @param idx Row index (0-3). [AI]
	 * @return Const pointer to the row. [AI]
	 * @details [AI]
	 */
	const float* operator[](int idx) const { return m_data[idx]; }

	/**
	 * @brief [AI] Assignment operator from a generic Matrix4. [AI]
	 * @param p_matrix Source Matrix4. [AI]
	 * @details [AI] Overridden from base, copies all matrix values from a Matrix4 into this MxMatrix.
	 */
	void operator=(const Matrix4& p_matrix) override { Equals(p_matrix); } // vtable+0x28

	/**
	 * @brief [AI] Assignment operator from another MxMatrix. [AI]
	 * @param p_matrix Source MxMatrix. [AI]
	 * @details [AI] Copies all matrix elements from another MxMatrix.
	 */
	virtual void operator=(const MxMatrix& p_matrix) { Equals(p_matrix); } // vtable+0x48

private:
	/**
	 * @brief [AI] Underlying float storage for matrix elements. [AI]
	 * @details [AI] 4x4 array holding the values of the transformation matrix. This buffer is passed to the Matrix4 parent class for operations.
	 */
	float m_elements[4][4]; // 0x08 [AI]
};

// Must be included here (not before MxMatrix) for correct ordering in binary.
// FromQuaternion and ToQuaternion in Matrix4 depend on Vector4.
// There's a chance they included mxgeometry4d.h after including this somewhere.
#include "realtime/vector4d.inl.h"

#endif // MXMATRIX_H
