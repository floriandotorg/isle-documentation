#ifndef MXMEMORYPOOL_H
#define MXMEMORYPOOL_H

#include "decomp.h"
#include "mxbitset.h"
#include "mxdebug.h"
#include "mxtypes.h"

#include <assert.h>

/**
 * @brief [AI] Fixed-size memory pool template for fast allocation and deallocation.
 * 
 * [AI] The MxMemoryPool class manages a pool of buffers of a fixed block size and count, providing fast and efficient memory
 * allocation and release. Internally, a bitset keeps track of used/free blocks and returns pointers to available blocks on request.
 *
 * @tparam BS [AI] Block size, in kilobytes (each allocation is BS*1024 bytes)
 * @tparam NB [AI] Number of blocks in the pool
 */
template <size_t BS, size_t NB>
class MxMemoryPool {
public:
	/**
	 * @brief [AI] Constructor. Initializes an empty pool with the specified block size.
	 * @details [AI] The actual allocation is deferred until Allocate is called.
	 */
	MxMemoryPool() : m_pool(NULL), m_blockSize(BS) {}

	/**
	 * @brief [AI] Destructor. Destroys the memory pool and releases its memory.
	 */
	~MxMemoryPool() { delete[] m_pool; }

	/**
	 * @brief [AI] Allocates the memory pool according to template parameters.
	 * 
	 * @return SUCCESS if allocation succeeded; FAILURE otherwise. [AI]
	 * @details [AI] Allocates a contiguous memory block sufficient for NB blocks of BS*1024 bytes each.
	 *               Panics if called more than once or with zero block size/count.
	 */
	MxResult Allocate();

	/**
	 * @brief [AI] Gets a pointer to the next available block in the memory pool.
	 * @return Pointer to available memory block, or NULL if all are in use. [AI]
	 * @details [AI] Scans the block reference bitset for a free block, marks it as used and returns pointer to its start.
	 */
	MxU8* Get();

	/**
	 * @brief [AI] Releases the block at the given pointer back into the pool.
	 * @param p_buf Pointer within the memory pool to be released. [AI]
	 * @details [AI] Calculates the block index from the pointer, marks it as free in the block reference bitset.
	 */
	void Release(MxU8* p_buf);

	/**
	 * @brief [AI] Returns the number of blocks in the pool.
	 * @return Number of blocks managed by the pool (usually NB). [AI]
	 * @details [AI] Returns the size reported by the MxBitset managing block references.
	 */
	MxU32 GetPoolSize() const { return m_blockRef.Size(); }

private:
	MxU8* m_pool;            ///< @brief [AI] Pointer to the start of the pool's memory buffer.
	MxU32 m_blockSize;       ///< @brief [AI] Block size in kilobytes (as given by BS).
	MxBitset<NB> m_blockRef; ///< @brief [AI] Bitset tracking which blocks are currently allocated.
};

template <size_t BS, size_t NB>
MxResult MxMemoryPool<BS, NB>::Allocate()
{
	assert(m_pool == NULL);
	assert(m_blockSize);
	assert(m_blockRef.Size());

	m_pool = new MxU8[GetPoolSize() * m_blockSize * 1024];
	assert(m_pool);

	return m_pool ? SUCCESS : FAILURE;
}

template <size_t BS, size_t NB>
MxU8* MxMemoryPool<BS, NB>::Get()
{
	assert(m_pool != NULL);
	assert(m_blockSize);
	assert(m_blockRef.Size());

	for (MxU32 i = 0; i < GetPoolSize(); i++) {
		if (!m_blockRef[i]) {
			m_blockRef[i].Flip();

			MxTrace("Get> %d pool: busy %d blocks\n", m_blockSize, m_blockRef.Count());

			return &m_pool[i * m_blockSize * 1024];
		}
	}

	return NULL;
}

template <size_t BS, size_t NB>
void MxMemoryPool<BS, NB>::Release(MxU8* p_buf)
{
	assert(m_pool != NULL);
	assert(m_blockSize);
	assert(m_blockRef.Size());

	MxU32 i = (MxU32) (p_buf - m_pool) / (m_blockSize * 1024);

	assert(i >= 0 && i < GetPoolSize());
	assert(m_blockRef[i]);

	if (m_blockRef[i]) {
		m_blockRef[i].Flip();
	}

	MxTrace("Release> %d pool: busy %d blocks\n", m_blockSize, m_blockRef.Count());
}

// TEMPLATE: BETA10 0x101464a0
// MxMemoryPool<64,22>::MxMemoryPool<64,22>

// TEMPLATE: LEGO1 0x100b9100
// TEMPLATE: BETA10 0x10146590
// MxMemoryPool<64,22>::~MxMemoryPool<64,22>

// TEMPLATE: BETA10 0x101465c0
// MxMemoryPool<128,2>::MxMemoryPool<128,2>

// TEMPLATE: LEGO1 0x100b9110
// TEMPLATE: BETA10 0x101466b0
// MxMemoryPool<128,2>::~MxMemoryPool<128,2>

// TEMPLATE: BETA10 0x10146780
// MxMemoryPool<64,22>::Allocate

// TEMPLATE: BETA10 0x101468a0
// MxMemoryPool<64,22>::GetPoolSize

// TEMPLATE: BETA10 0x101468d0
// MxMemoryPool<128,2>::Allocate

// TEMPLATE: BETA10 0x101469f0
// MxMemoryPool<128,2>::GetPoolSize

// TEMPLATE: BETA10 0x10158610
// MxMemoryPool<64,22>::Release

// TEMPLATE: BETA10 0x101589e0
// MxMemoryPool<128,2>::Release

// TEMPLATE: BETA10 0x10158e50
// MxMemoryPool<64,22>::Get

// TEMPLATE: BETA10 0x10158f90
// MxMemoryPool<128,2>::Get

#endif // MXMEMORYPOOL_H
