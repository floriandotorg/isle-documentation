#ifndef VECTOR_H
#define VECTOR_H

#include "compat.h"

// Note: virtual function overloads appear in the virtual table
// in reverse order of appearance.

// VTABLE: LEGO1 0x100d4288
// VTABLE: BETA10 0x101b8440
// SIZE 0x08
/**
 * @brief [AI] Represents a 2D mathematical vector with floating-point coordinates. Provides a flexible base class for 2D, 3D, and 4D specialization. Vector data may be shared externally via an internal pointer rather than fixed storage.
 * @details [AI] Vector2 supports polymorphic math (addition, subtraction, multiplication, division, dot product, etc.) through its overridden virtual member functions evaluated per element or for the whole structure. All operations can be dispatched either by a scalar, vector, or float pointer. Serves as a base for Vector3 and Vector4 to provide extensible vector algebra. The memory pointed to by m_data is not owned by Vector2; it is provided and managed externally. 
 */
class Vector2 {
protected:
	/**
	 * @brief [AI] Adds the values pointed to by p_value to this vector.
	 * @param p_value Pointer to an array containing values to add. [AI]
	 */
	inline virtual void AddImpl(const float* p_value);                      // vtable+0x04
	
	/**
	 * @brief [AI] Adds a scalar value to every element of this vector.
	 * @param p_value The value to add to each coordinate. [AI]
	 */
	inline virtual void AddImpl(float p_value);                             // vtable+0x00
	
	/**
	 * @brief [AI] Subtracts the vector specified by p_value from this vector.
	 * @param p_value Pointer to array to subtract. [AI]
	 */
	inline virtual void SubImpl(const float* p_value);                      // vtable+0x08
	
	/**
	 * @brief [AI] Multiplies this vector by another vector (per element).
	 * @param p_value Pointer to the vector to multiply with. [AI]
	 */
	inline virtual void MulImpl(const float* p_value);                      // vtable+0x10
	
	/**
	 * @brief [AI] Multiplies this vector by a scalar value.
	 * @param p_value Scalar multiplier. [AI]
	 */
	inline virtual void MulImpl(const float& p_value);                      // vtable+0x0c
	
	/**
	 * @brief [AI] Divides this vector by a scalar value.
	 * @param p_value Scalar divisor. [AI]
	 */
	inline virtual void DivImpl(const float& p_value);                      // vtable+0x14

	/**
	 * @brief [AI] Computes the dot product of two arrays interpreted as vectors.
	 * @param p_a Pointer to the first vector. [AI]
	 * @param p_b Pointer to the second vector. [AI]
	 * @return The computed dot product. [AI]
	 */
	inline virtual float DotImpl(const float* p_a, const float* p_b) const; // vtable+0x18

	/**
	 * @brief [AI] Set the internal data pointer to external storage.
	 * @param p_data Data pointer to use for this vector. [AI]
	 */
	inline virtual void SetData(float* p_data);                             // vtable+0x1c

	/**
	 * @brief [AI] Assigns values from provided array to this vector.
	 * @param p_data Pointer to array to copy from. [AI]
	 */
	inline virtual void EqualsImpl(const float* p_data);                    // vtable+0x20

	/**
	 * @brief [AI] Pointer to externally provided float storage (owned elsewhere).
	 */
	float* m_data; // 0x04

public:
	/**
	 * @brief [AI] Construct a 2D vector using an external float buffer.
	 * @param p_data Pointer to two floats that represent initial vector values; the data is used by reference. [AI]
	 */
	Vector2(float* p_data) { SetData(p_data); }

	/**
	 * @brief [AI] Construct a 2D vector from a (likely constant) array of floats without copying (just pointer assignment).
	 * @param p_data Pointer to two floats (const) to use for vector data. [AI]
	 * @attention [AI] The pointer is cast to non-const. Used in legacy code; may allow accidental mutation of const data in practice. [AI]
	 */
	Vector2(const float* p_data) { m_data = (float*) p_data; }

	/**
	 * @brief [AI] Retrieves the mutable in-memory data pointer for this vector.
	 * @return Pointer to internal vector storage. [AI]
	 */
	inline virtual float* GetData();                                        // vtable+0x28

	/**
	 * @brief [AI] Retrieves the immutable data pointer for this vector.
	 * @return Const pointer to internal storage. [AI]
	 */
	inline virtual const float* GetData() const;                            // vtable+0x24

	/**
	 * @brief [AI] Zeros all elements (sets all coordinates to 0.0).
	 */
	inline virtual void Clear();                                            // vtable+0x2c

	/**
	 * @brief [AI] Compute the dot product of the two float arrays interpreted as vectors of 2 elements.
	 * @param p_a Pointer to first vector data. [AI]
	 * @param p_b Pointer to second vector data. [AI]
	 * @return Dot product. [AI]
	 */
	inline virtual float Dot(const float* p_a, const float* p_b) const;     // vtable+0x3c

	/**
	 * @brief [AI] Compute the dot product of two Vector2 objects.
	 * @param p_a First vector. [AI]
	 * @param p_b Second vector. [AI]
	 * @return Dot product. [AI]
	 */
	inline virtual float Dot(const Vector2& p_a, const Vector2& p_b) const; // vtable+0x38

	/**
	 * @brief [AI] Compute the dot product given a pointer and a Vector2 (second param).
	 * @param p_a First array pointer. [AI]
	 * @param p_b Second vector. [AI]
	 * @return Dot product. [AI]
	 */
	inline virtual float Dot(const float* p_a, const Vector2& p_b) const;   // vtable+0x34

	/**
	 * @brief [AI] Compute the dot product given a Vector2 (first param) and a pointer (second param).
	 * @param p_a First vector. [AI]
	 * @param p_b Second array pointer. [AI]
	 * @return Dot product. [AI]
	 */
	inline virtual float Dot(const Vector2& p_a, const float* p_b) const;   // vtable+0x30

	/**
	 * @brief [AI] Compute the squared length (magnitude^2) of the vector.
	 * @return Squared length. [AI]
	 */
	inline virtual float LenSquared() const;                                // vtable+0x40

	/**
	 * @brief [AI] Scales the vector so its norm is 1 (unit vector). Returns 0 if successful, nonzero on failure (e.g. if length is 0).
	 * @return Unitization status. [AI]
	 */
	inline virtual int Unitize();                                           // vtable+0x44

	/**
	 * @brief [AI] In-place add a scalar to all coordinates.
	 * @param p_value Scalar to add. [AI]
	 */
	inline virtual void operator+=(float p_value);                          // vtable+0x50

	/**
	 * @brief [AI] In-place add vector elements via float pointer.
	 * @param p_other Pointer to 2 floats. [AI]
	 */
	inline virtual void operator+=(const float* p_other);                   // vtable+0x4c

	/**
	 * @brief [AI] In-place add another Vector2.
	 * @param p_other Other vector to add. [AI]
	 */
	inline virtual void operator+=(const Vector2& p_other);                 // vtable+0x48

	/**
	 * @brief [AI] In-place subtraction of vector pointed to by p_other.
	 * @param p_other Data to subtract. [AI]
	 */
	inline virtual void operator-=(const float* p_other);                   // vtable+0x58

	/**
	 * @brief [AI] In-place subtraction of another Vector2.
	 * @param p_other Vector to subtract. [AI]
	 */
	inline virtual void operator-=(const Vector2& p_other);                 // vtable+0x54

	/**
	 * @brief [AI] In-place per-element multiplication of this vector by another array.
	 * @param p_other Pointer to 2 floats. [AI]
	 */
	inline virtual void operator*=(const float* p_other);                   // vtable+0x64

	/**
	 * @brief [AI] In-place per-element multiplication by another Vector2.
	 * @param p_other Second vector (rhs). [AI]
	 */
	inline virtual void operator*=(const Vector2& p_other);                 // vtable+0x60

	/**
	 * @brief [AI] In-place multiplication by a scalar.
	 * @param p_value Scalar multiplier. [AI]
	 */
	inline virtual void operator*=(const float& p_value);                   // vtable+0x5c

	/**
	 * @brief [AI] In-place scalar division.
	 * @param p_value Scalar divisor. [AI]
	 */
	inline virtual void operator/=(const float& p_value);                   // vtable+0x68

	/**
	 * @brief [AI] Assigns this vector's elements from a pointer to two floats.
	 * @param p_other Pointer to source array. [AI]
	 */
	inline virtual void operator=(const float* p_other);                    // vtable+0x70

	/**
	 * @brief [AI] Assigns this vector's elements from another Vector2.
	 * @param p_other Source vector. [AI]
	 */
	inline virtual void operator=(const Vector2& p_other);                  // vtable+0x6c

	// SYNTHETIC: LEGO1 0x10010be0
	// SYNTHETIC: BETA10 0x100121e0
	// Vector3::operator=

	// SYNTHETIC: BETA10 0x1004af40
	// Vector4::operator=

	/**
	 * @brief [AI] Accesses the idx-th float in the vector (0 or 1).
	 * @param idx Index of the float (0 or 1). [AI]
	 * @return Reference to the value at index. [AI]
	 */
	float& operator[](int idx) { return m_data[idx]; }

	/**
	 * @brief [AI] Const version of the index operator.
	 * @param idx Index to access (0 or 1). [AI]
	 * @return Const reference to value at index. [AI]
	 */
	const float& operator[](int idx) const { return m_data[idx]; }
};

// VTABLE: LEGO1 0x100d4518
// VTABLE: BETA10 0x101b8398
// SIZE 0x08
/**
 * @brief [AI] 3D vector class, providing vector and cross-product operations in 3D space. Inherits from Vector2 to add the third coordinate and cross product facilities.
 * @details [AI] Only adds methods specific to 3D (e.g., cross-product), all storage uses the (externally managed) m_data float pointer from Vector2.
 */
class Vector3 : public Vector2 {
protected:
	/**
	 * @copydoc Vector2::AddImpl(const float*)
	 */
	inline void AddImpl(const float* p_value) override;                      // vtable+0x04

	/**
	 * @copydoc Vector2::AddImpl(float)
	 */
	inline void AddImpl(float p_value) override;                             // vtable+0x00

	/**
	 * @copydoc Vector2::SubImpl(const float*)
	 */
	inline void SubImpl(const float* p_value) override;                      // vtable+0x08

	/**
	 * @copydoc Vector2::MulImpl(const float*)
	 */
	inline void MulImpl(const float* p_value) override;                      // vtable+0x10
	
	/**
	 * @copydoc Vector2::MulImpl(const float&)
	 */
	inline void MulImpl(const float& p_value) override;                      // vtable+0x0c

	/**
	 * @copydoc Vector2::DivImpl(const float&)
	 */
	inline void DivImpl(const float& p_value) override;                      // vtable+0x14

	/**
	 * @copydoc Vector2::DotImpl(const float*, const float*)
	 */
	inline float DotImpl(const float* p_a, const float* p_b) const override; // vtable+0x18

	/**
	 * @copydoc Vector2::EqualsImpl(const float*)
	 */
	inline void EqualsImpl(const float* p_data) override;                    // vtable+0x20

	/**
	 * @brief [AI] Assigns this vector to the cross product of p_a and p_b.
	 * @param p_a Pointer to first 3-element vector. [AI]
	 * @param p_b Pointer to second 3-element vector. [AI]
	 */
	inline virtual void EqualsCrossImpl(const float* p_a, const float* p_b); // vtable+0x74

public:
	/**
	 * @brief [AI] Construct a 3D vector pointing at external data storage.
	 * @param p_data Pointer to at least 3 floats for component values. [AI]
	 */
	Vector3(float* p_data) : Vector2(p_data) {}

	// Hack: Some code initializes a Vector3 from a (most likely) const float* source.
	// Example: LegoCameraController::GetWorldUp
	// Vector3 however is a class that can mutate its underlying source, making
	// initialization with a const source fundamentally incompatible.

	/**
	 * @brief [AI] Construct a 3D vector from const float* (pointer is cast to non-const in base).
	 * @param p_data Source array pointer (only cast, never copied). [AI]
	 * @attention [AI] Legal in codebase but dangerous if const storage is used elsewhere! [AI]
	 */
	Vector3(const float* p_data) : Vector2(p_data) {}

	/**
	 * @brief [AI] Sets every coordinate (x, y, z) to zero.
	 */
	inline void Clear() override;                                            // vtable+0x2c

	/**
	 * @brief [AI] Computes the squared magnitude (x^2 + y^2 + z^2) of this vector.
	 * @return Squared length. [AI]
	 */
	inline float LenSquared() const override;                                // vtable+0x40

	/**
	 * @brief [AI] Sets this vector to be the cross product of p_a and p_b.
	 * @param p_a First operand. [AI]
	 * @param p_b Second operand. [AI]
	 */
	inline virtual void EqualsCross(const Vector3& p_a, const Vector3& p_b); // vtable+0x80

	/**
	 * @brief [AI] Sets this vector to be the cross product of p_a and p_b, with b as a pointer.
	 * @param p_a Vector3 operand. [AI]
	 * @param p_b Pointer operand. [AI]
	 */
	inline virtual void EqualsCross(const Vector3& p_a, const float* p_b);   // vtable+0x7c

	/**
	 * @brief [AI] Sets this vector to be the cross product of p_a and p_b, with a as a pointer.
	 * @param p_a Pointer operand. [AI]
	 * @param p_b Vector3 operand. [AI]
	 */
	inline virtual void EqualsCross(const float* p_a, const Vector3& p_b);   // vtable+0x78

	/**
	 * @brief [AI] Fills all coordinates with p_value.
	 * @param p_value Fill value. [AI]
	 */
	inline virtual void Fill(const float& p_value);                          // vtable+0x84

	friend class Mx3DPointFloat;
};

// VTABLE: LEGO1 0x100d45a0
// VTABLE: BETA10 0x101bac38
// SIZE 0x08
/**
 * @brief [AI] A four-dimensional vector, supporting operations relevant for matrix and quaternion math (homogeneous coordinates). Inherits from Vector3.
 * @details [AI] Adds 4D-specific functions: matrix product, quaternion normalization, and quaternion Hamilton products. Facilitates 3D transformations and animation math.
 */
class Vector4 : public Vector3 {
protected:
	/**
	 * @copydoc Vector2::AddImpl(const float*)
	 */
	inline void AddImpl(const float* p_value) override;                      // vtable+0x04

	/**
	 * @copydoc Vector2::AddImpl(float)
	 */
	inline void AddImpl(float p_value) override;                             // vtable+0x00

	/**
	 * @copydoc Vector2::SubImpl(const float*)
	 */
	inline void SubImpl(const float* p_value) override;                      // vtable+0x08

	/**
	 * @copydoc Vector2::MulImpl(const float*)
	 */
	inline void MulImpl(const float* p_value) override;                      // vtable+0x10

	/**
	 * @copydoc Vector2::MulImpl(const float&)
	 */
	inline void MulImpl(const float& p_value) override;                      // vtable+0x0c

	/**
	 * @copydoc Vector2::DivImpl(const float&)
	 */
	inline void DivImpl(const float& p_value) override;                      // vtable+0x14

	/**
	 * @copydoc Vector2::DotImpl(const float*, const float*)
	 */
	inline float DotImpl(const float* p_a, const float* p_b) const override; // vtable+0x18
	
	/**
	 * @copydoc Vector2::EqualsImpl(const float*)
	 */
	inline void EqualsImpl(const float* p_data) override;                    // vtable+0x20

public:
	/**
	 * @brief [AI] Constructs a Vector4 using external float storage.
	 * @param p_data Pointer to at least 4 floats. [AI]
	 */
	Vector4(float* p_data) : Vector3(p_data) {}

	/**
	 * @brief [AI] Constructs a Vector4 using a const float pointer (pointer is reinterpreted as mutable).
	 * @param p_data Const pointer to at least 4 floats. [AI]
	 * @attention [AI] Used in legacy code and for complicated construction scenarios. [AI]
	 */
	Vector4(const float* p_data) : Vector3(p_data) {}

	/**
	 * @brief [AI] Sets all four components to zero.
	 */
	inline void Clear() override;                                                     // vtable+0x2c

	/**
	 * @brief [AI] Computes the squared magnitude of the 4D vector.
	 * @return Squared length. [AI]
	 */
	inline float LenSquared() const override;                                         // vtable+0x40

	/**
	 * @brief [AI] Fill all four floats with p_value.
	 * @param p_value The value to assign everywhere. [AI]
	 */
	inline void Fill(const float& p_value) override;                                  // vtable+0x84

	/**
	 * @brief [AI] Set this vector to the result of a matrix-vector product: result = p_mat * p_vec.
	 * @param p_vec Pointer to the input vector (length 4). [AI]
	 * @param p_mat Pointer to 4x4 matrix (row-major). [AI]
	 */
	inline virtual void SetMatrixProduct(const float* p_vec, const float* p_mat);     // vtable+0x8c

	/**
	 * @brief [AI] Set this vector to result of matrix-vector product with source given as Vector4, matrix as pointer.
	 * @param p_a Vector4 to multiply. [AI]
	 * @param p_b Matrix pointer. [AI]
	 */
	inline virtual void SetMatrixProduct(const Vector4& p_a, const float* p_b);       // vtable+0x88

	/**
	 * @brief [AI] Normalize this quaternion (interpreted as vector) in place. Result is 0 if success.
	 * @return Status code. [AI]
	 */
	inline virtual int NormalizeQuaternion();                                         // vtable+0x90

	/**
	 * @brief [AI] Set this vector to the Hamilton product of two quaternion Vector4s.
	 * @param p_a First quaternion as Vector4. [AI]
	 * @param p_b Second quaternion as Vector4. [AI]
	 * @return Status/result code. [AI]
	 */
	inline virtual int EqualsHamiltonProduct(const Vector4& p_a, const Vector4& p_b); // vtable+0x94

	/**
	 * @brief [AI] Indexes 0-3: returns reference to the fast access coordinate.
	 * @param idx 0-based index. [AI]
	 */
	float& operator[](int idx) { return m_data[idx]; }

	/**
	 * @brief [AI] Const version for coordinate access (0...3).
	 * @param idx Coordinate index. [AI]
	 */
	const float& operator[](int idx) const { return m_data[idx]; }

	friend class Mx4DPointFloat;
};

#ifdef COMPAT_MODE
#include "vector2d.inl.h"
#include "vector3d.inl.h"
#include "vector4d.inl.h"
#endif

#endif // VECTOR_H
