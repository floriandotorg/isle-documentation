#ifndef MXBITSET_H
#define MXBITSET_H

#pragma warning(disable : 4237)

#include "mxtypes.h"

#include <assert.h>
#include <limits.h> // CHAR_BIT

/**
 * @brief Templated fixed-size bitset for bit manipulation. [AI]
 * @details [AI] Provides a simple implementation similar to std::bitset, optimized for small fixed sizes with basic bit flipping and testing operations. The number of bits is set at compile time via the template argument N. [AI]
 * 
 * @tparam N Number of bits in the set. [AI]
 */
template <size_t N>
class MxBitset {
public:
	/**
	 * @brief Constructs an empty MxBitset with all bits cleared. [AI]
	 * @details [AI] Constructor initializes internal storage and ensures all bits are set to the value zero using the Tidy() function. [AI]
	 */
	MxBitset() { Tidy(); }

	// SIZE 0x08
	/**
	 * @brief Proxy class to reference a single bit within the MxBitset. [AI]
	 * @details [AI] Provides a reference-like object returned from operator[] to allow mutation and inspection of individual bits. [AI]
	 */
	class Reference {
		friend class MxBitset<N>;

	public:
		/**
		 * @brief Flips the referenced bit (inverts its value). [AI]
		 * @return Reference& Reference to this proxy (facilitates chaining). [AI]
		 */
		Reference& Flip()
		{
			m_bitset->Flip(m_offset);
			return (*this);
		}

		/**
		 * @brief Returns true if the referenced bit is not set. [AI]
		 * @return bool TRUE if the bit is 0, FALSE if 1. [AI]
		 */
		bool operator~() const { return (!m_bitset->Test(m_offset)); }

		/**
		 * @brief Implicit conversion to bool representing the referenced bit. [AI]
		 * @return bool TRUE if the bit is set, FALSE otherwise. [AI]
		 */
		operator bool() const { return (m_bitset->Test(m_offset)); }

	private:
		/**
		 * @brief Constructs a Reference to a specific bit in the given bitset. [AI]
		 * @param p_bitset Reference to the parent MxBitset. [AI]
		 * @param p_offset Bit position within the bitset. [AI]
		 */
		Reference(MxBitset<N>& p_bitset, size_t p_offset) : m_bitset(&p_bitset), m_offset(p_offset) {}
		MxBitset<N>* m_bitset; ///< [AI] Pointer to the parent MxBitset. [AI]
		size_t m_offset;       ///< [AI] Bit position within the bitset. [AI]
	};

	/**
	 * @brief Provides a reference-like object for a specific bit. [AI]
	 * @param p_bit Bit index to access [AI]
	 * @return Reference Proxy to the requested bit, which can be flipped or tested. [AI]
	 */
	Reference operator[](size_t p_bit) { return (Reference(*this, p_bit)); }

	/**
	 * @brief Flips (toggles) a single bit at the given position. [AI]
	 * @details [AI] If out of range, triggers an assertion failure (Xran). [AI]
	 * @param p_bit Bit index to flip [AI]
	 * @return MxBitset<N>& Reference to this bitset (enables chaining). [AI]
	 */
	MxBitset<N>& Flip(size_t p_bit)
	{
		if (N <= p_bit) {
			Xran();
		}
		m_blocks[p_bit / e_bitsPerBlock] ^= 1 << p_bit % e_bitsPerBlock;
		return (*this);
	}

	/**
	 * @brief Counts the number of set bits. [AI]
	 * @details [AI] Not implemented in debug builds, always returns zero. [AI]
	 * @return size_t Always 0; stub function. [AI]
	 */
	size_t Count()
	{
		// debug only, intentionally unimplemented
		return 0;
	}

	/**
	 * @brief Tests if the given bit is set (1) or not (0). [AI]
	 * @details [AI] If out of range, triggers an assertion (Xran). [AI]
	 * @param p_bit Bit index to test [AI]
	 * @return bool TRUE if the bit is set, FALSE if not. [AI]
	 */
	bool Test(MxU32 p_bit)
	{
		if (p_bit >= N) {
			Xran();
		}

		return (m_blocks[p_bit / e_bitsPerBlock] & (1 << p_bit % e_bitsPerBlock)) != 0;
	}

	/**
	 * @brief Returns the number of bits (N) this bitset manages. [AI]
	 * @return MxU32 Number of bits [AI]
	 */
	MxU32 Size() const { return N; }

private:
	/**
	 * @brief Fills all underlying bit blocks with a given value or clears all bits if default. [AI]
	 * @details [AI] Used in construction and resetting; fills all blocks with p_value, trims extra bits if nonzero. [AI]
	 * @param p_value Value to assign each block (defaults to 0). [AI]
	 */
	void Tidy(MxU32 p_value = 0)
	{
		for (MxS32 i = e_blocksRequired; i >= 0; --i) {
			m_blocks[i] = p_value;
		}

		// No need to trim if all bits were zeroed out
		if (p_value != 0) {
			Trim();
		}
	}

	/**
	 * @brief Trims off unused bits in the last storage block. [AI]
	 * @details [AI] If N is not a multiple of e_bitsPerBlock, masks off upper unused bits. [AI]
	 */
	void Trim()
	{
		if (N % e_bitsPerBlock != 0) {
			m_blocks[e_blocksRequired] &= ((1 << (N % e_bitsPerBlock)) - 1);
		}
	}

	/**
	 * @brief Triggers an assertion for out-of-bounds accesses. [AI]
	 * @details [AI] Used when bit index is out of range; assertion message is intentionally always false. [AI]
	 */
	void Xran() { assert("invalid MxBitset<N> position" == NULL); }

	/**
	 * @brief Constants defining storage parameters for MxBitset. [AI]
	 * @details [AI] Used internally: bits per block and number of required blocks based on template N. [AI]
	 */
	// Not a real enum. This is how STL BITSET defines these constants.
	enum {
		e_bitsPerBlock = CHAR_BIT * sizeof(MxU32), ///< [AI] Number of bits per underlying storage block (MxU32). [AI]
		e_blocksRequired = N == 0 ? 0 : (N - 1) / e_bitsPerBlock ///< [AI] Number of blocks required for N bits. [AI]
	};

	MxU32 m_blocks[e_blocksRequired + 1]; ///< [AI] Array of storage blocks holding the bit values. [AI]
};

#endif // MXBITSET_H