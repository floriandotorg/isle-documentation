#ifdef 0

// LIBRARY: ISLE 0x402f10
// ?shi_New@@YAPAXKIPAU_SHI_Pool@@@Z
/// @brief [AI] Allocates a new memory block with given size and alignment from a specified memory pool. [AI]
/// @param size The size of the block to allocate. [AI]
/// @param alignment Alignment requirement for the new block. [AI]
/// @param pool Pointer to the SHI_Pool structure representing the memory pool to allocate from. [AI]
/// @return Pointer to allocated memory block or NULL on failure. [AI]

// LIBRARY: ISLE 0x402fb0
// _MemInitDefaultPool@0
/// @brief [AI] Initializes the default memory pool for heap allocations. [AI]
/// @details [AI] This function is typically called during application startup to establish a memory pool from which allocations can be made. [AI]

// LIBRARY: ISLE 0x403020
// _shi_call_new_handler_msc
/// @brief [AI] Invokes the global new handler (Microsoft C runtime). [AI]
/// @details [AI] This is used when a memory allocation fails, giving the program a chance to recover or terminate gracefully. [AI]

// LIBRARY: ISLE 0x403050
// _MemPoolShrink@4
/// @brief [AI] Shrinks the memory pool to release unused memory. [AI]
/// @param pool Pointer to the memory pool to shrink. [AI]

// LIBRARY: ISLE 0x403180
// _MemPoolPreAllocate@12
/// @brief [AI] Pre-allocates memory blocks within a pool up to a certain size. [AI]
/// @param pool Pointer to the memory pool. [AI]
/// @param numBlocks Number of blocks to pre-allocate. [AI]
/// @param blockSize Size of each block. [AI]

// LIBRARY: ISLE 0x403300
// @_shi_initPageHeaders@4
/// @brief [AI] Initializes page headers for a given memory pool. [AI]
/// @param pool Pointer to the pool whose page headers will be initialized. [AI]

// LIBRARY: ISLE 0x403570
// @shi_allocPageHeader@4
/// @brief [AI] Allocates a page header from the pool. [AI]
/// @param pool Pointer to the memory pool. [AI]
/// @return Pointer to the new page header structure. [AI]

// LIBRARY: ISLE 0x4035a0
// @shi_freePageHeader@8
/// @brief [AI] Frees a page header within a given memory pool. [AI]
/// @param pool Pointer to memory pool. [AI]
/// @param pageHeader Pointer to the page header to free. [AI]

// LIBRARY: ISLE 0x403750
// @_shi_deletePage@8
/// @brief [AI] Deletes a page from the memory pool and frees all associated memory. [AI]
/// @param pool Pointer to memory pool. [AI]
/// @param page Pointer to the page to delete. [AI]

// LIBRARY: ISLE 0x403830
// @_shi_allocExternal@12
/// @brief [AI] Allocates external memory from the operating system, bypassing internal pool. [AI]
/// @param size Size of memory to allocate. [AI]
/// @param alignment Alignment requirement. [AI]
/// @param attribution Categorization for tracking purposes. [AI]
/// @return Pointer to allocated memory region or NULL. [AI]

// LIBRARY: ISLE 0x403a50
// @_shi_initPageVariable@8
/// @brief [AI] Initializes a variable-size page within the memory pool. [AI]
/// @param pool Pointer to pool. [AI]
/// @param page Pointer to page structure. [AI]

// LIBRARY: ISLE 0x403b00
// _MemAllocPtr@12
/// @brief [AI] Allocates a pointer-sized memory block from a memory pool. [AI]
/// @param pool Pointer to pool. [AI]
/// @param requestedSize Size to allocate. [AI]
/// @param flags Possible allocation flags. [AI]
/// @return Pointer to the allocated memory or NULL. [AI]

// LIBRARY: ISLE 0x403d60
// @_shi_allocVar@12
/// @brief [AI] Allocates a variable-sized block from the memory pool. [AI]
/// @param pool Pointer to pool. [AI]
/// @param size Size to allocate. [AI]
/// @param attribution For tracking the allocation source. [AI]

// LIBRARY: ISLE 0x403ef0
// @_shi_allocBlock@12
/// @brief [AI] Allocates a fixed-size block from the pool. [AI]
/// @param pool Pointer to pool. [AI]
/// @param size Size of block. [AI]
/// @param blockType Block type or tag. [AI]
/// @return Pointer to allocated block. [AI]

// LIBRARY: ISLE 0x4040c0
// _MemFreePtr@4
/// @brief [AI] Frees a memory block previously allocated by the memory pool. [AI]
/// @param ptr Pointer to the memory block to be freed. [AI]

// LIBRARY: ISLE 0x404170
// @_shi_freeVar@4
/// @brief [AI] Frees a variable-sized memory block from the pool. [AI]
/// @param blockPtr Pointer to the block. [AI]

// LIBRARY: ISLE 0x404260
// _MemReAllocPtr@12
/// @brief [AI] Reallocates a previously allocated memory block to a new size. [AI]
/// @param pool Pointer to the pool. [AI]
/// @param ptr Pointer to the existing memory block. [AI]
/// @param newSize New size for the memory block. [AI]
/// @return Pointer to reallocated memory. [AI]

// LIBRARY: ISLE 0x4043b0
// @_shi_resizeAny@16
/// @brief [AI] Resizes any memory block (fixed or variable size) in pool. [AI]
/// @param pool Pointer to pool. [AI]
/// @param ptr Pointer to block. [AI]
/// @param newSize Size to resize to. [AI]
/// @param flags Control flags. [AI]

// LIBRARY: ISLE 0x404650
// @_shi_resizeVar@8
/// @brief [AI] Resizes a variable-sized memory block. [AI]
/// @param ptr Pointer to memory block. [AI]
/// @param newSize New desired size. [AI]

// LIBRARY: ISLE 0x404820
// _MemSizePtr@4
/// @brief [AI] Gets the size of an allocated memory block. [AI]
/// @param ptr Pointer to memory block. [AI]
/// @return Size in bytes. [AI]

// LIBRARY: ISLE 0x4048d0
// @shi_findAllocAddress@4
/// @brief [AI] Finds the base allocation address for a given pointer (internal tracking). [AI]
/// @param ptr Address within the allocated range. [AI]
/// @return Base address of the allocation. [AI]

// LIBRARY: ISLE 0x404910
// @_shi_sysAlloc@8
/// @brief [AI] Allocates memory using system API (i.e., OS-specific allocator). [AI]
/// @param size Number of bytes to allocate. [AI]
/// @param attrib For tracking/allocation tagging. [AI]

// LIBRARY: ISLE 0x4049a0
// @_shi_sysFree@4
/// @brief [AI] Frees memory using the system-level allocator. [AI]
/// @param ptr Pointer to memory block. [AI]

// LIBRARY: ISLE 0x404a00
// @_shi_sysRealloc@12
/// @brief [AI] Reallocates memory via the system allocator. [AI]
/// @param ptr Existing block. [AI]
/// @param newSize New size. [AI]
/// @param attrib For allocation tracking. [AI]
/// @return Reallocated memory pointer. [AI]

// LIBRARY: ISLE 0x404ab0
// @_shi_sysResize@12
/// @brief [AI] Requests a change in allocation size from the system allocator. [AI]
/// @param ptr Memory block. [AI]
/// @param newSize New size. [AI]
/// @param attrib Tracking value. [AI]

// LIBRARY: ISLE 0x404b90
// @_shi_sysSize@4
/// @brief [AI] Gets the size of a memory block from the system allocator. [AI]
/// @param ptr Target block. [AI]
/// @return Size in bytes. [AI]

// LIBRARY: ISLE 0x404bd0
// @_shi_sysAllocNear@4
/// @brief [AI] Allocates a memory block near a given address (for locality or OS mapping optimization). [AI]
/// @param nearPtr Base address for proximity. [AI]

// LIBRARY: ISLE 0x404bf0
// @_shi_sysFreeNear@4
/// @brief [AI] Frees a memory block allocated near a specific address. [AI]
/// @param nearPtr Target memory block address. [AI]

// LIBRARY: ISLE 0x404c10
// @_shi_sysValidatePtr@12
/// @brief [AI] Validates a pointer to ensure it is safe for use, possibly checking for corruption or out-of-bounds access. [AI]
/// @param ptr Pointer to validate. [AI]
/// @param size Expected size. [AI]
/// @param flags Validation flags. [AI]

// LIBRARY: ISLE 0x404d10
// @_shi_sysValidateFunction@4
/// @brief [AI] Validates a function pointer or registration, for system-level integrity. [AI]
/// @param funcptr The function pointer to validate. [AI]

// LIBRARY: ISLE 0x405300
// @_shi_sysAllocPool@12
/// @brief [AI] Allocates a new memory pool using system allocator. [AI]
/// @param config Pool configuration. [AI]
/// @param attrib Tracking or categorization. [AI]
/// @param callback Optional callback for pool events. [AI]

// LIBRARY: ISLE 0x405520
// @_shi_sysResizePool@16
/// @brief [AI] Resizes a system-level memory pool. [AI]
/// @param pool The memory pool to resize. [AI]
/// @param newSize The desired new pool size. [AI]
/// @param attrib Tracking/categorization. [AI]
/// @param callback Pool resize callback or context. [AI]

// LIBRARY: ISLE 0x405690
// @_shi_sysFreePage@4
/// @brief [AI] Frees a system-allocated memory page. [AI]
/// @param page Pointer to page to free. [AI]

// LIBRARY: ISLE 0x4057b0
// @_shi_sysSizePage@4
/// @brief [AI] Gets the size of a system-allocated memory page. [AI]
/// @param page Pointer to memory page. [AI]
/// @return Size of the page in bytes. [AI]

// LIBRARY: ISLE 0x4057e0
// @_shi_sysSizePool@8
/// @brief [AI] Gets the size of a system memory pool. [AI]
/// @param pool The memory pool. [AI]
/// @param attrib For filtering, tracking, or context. [AI]

// LIBRARY: ISLE 0x405800
// @_shi_registerShared@16
/// @brief [AI] Registers a block of shared memory or resource within the allocator. [AI]
/// @param base Base address. [AI]
/// @param size Size of memory. [AI]
/// @param tag Registration tag. [AI]
/// @param attrib Tracking or sharing flags. [AI]

// LIBRARY: ISLE 0x405a00
// @_shi_unregisterShared@8
/// @brief [AI] Unregisters a previously registered shared resource. [AI]
/// @param base Base address. [AI]
/// @param tag Registration tag. [AI]

// LIBRARY: ISLE 0x405b20
// @_shi_getNextPool@4
/// @brief [AI] Gets the next pool in an internal linked list or registry. [AI]
/// @param pool Current pool. [AI]
/// @return Pointer to the next memory pool. [AI]

// LIBRARY: ISLE 0x405b30
// @shi_delNextPool@4
/// @brief [AI] Removes the next pool from the internal pool list. [AI]
/// @param pool Current pool. [AI]

// LIBRARY: ISLE 0x405d30
// @shi_createAndEnterMutexShr@12
/// @brief [AI] Creates and enters a mutex for synchronizing access to a shared resource or pool. [AI]
/// @param mutexPtr Pointer to receive the new mutex. [AI]
/// @param pool Affected pool. [AI]
/// @param flags Mutex creation flags. [AI]

// LIBRARY: ISLE 0x405e20
// @shi_termPoolMutexShr@4
/// @brief [AI] Terminates (frees or destroys) a pool mutex previously created for synchronization. [AI]
/// @param mutexPtr Pointer to mutex to terminate. [AI]

// LIBRARY: ISLE 0x405e40
// @shi_enterPoolMutexShr@4
/// @brief [AI] Enters a mutex for a pool to provide exclusive access. [AI]
/// @param mutexPtr Target mutex. [AI]

// LIBRARY: ISLE 0x405e60
// @shi_leavePoolMutexShr@4
/// @brief [AI] Releases exclusive access to a pool mutex previously entered. [AI]
/// @param mutexPtr Target mutex. [AI]

// LIBRARY: ISLE 0x405e80
// __shi_enterCriticalSection@0
/// @brief [AI] Enters a global critical section for thread synchronization. [AI]

// LIBRARY: ISLE 0x405ea0
// __shi_leaveCriticalSection@0
/// @brief [AI] Leaves a global critical section, re-enabling concurrent access. [AI]

// LIBRARY: ISLE 0x405ec0
// __shi_createAndEnterMutex
/// @brief [AI] Creates and enters a non-shared mutex for local thread synchronization. [AI]

// LIBRARY: ISLE 0x405ef0
// _shi_enterPoolMutexSafely
/// @brief [AI] Safely enters a pool mutex, handling race conditions or contention properly. [AI]

// LIBRARY: ISLE 0x405fd0
// _shi_enterPoolInitMutexReader
/// @brief [AI] Enters a reader-specific initialization mutex for pools, for read access. [AI]

// LIBRARY: ISLE 0x406060
// _shi_leavePoolInitMutexReader
/// @brief [AI] Leaves the reader-specific initialization mutex for pools. [AI]

// LIBRARY: ISLE 0x406090
// _shi_enterPoolInitMutexWriter
/// @brief [AI] Enters a writer-specific initialization mutex for pools, for write access. [AI]

// LIBRARY: ISLE 0x406160
// _shi_leavePoolInitMutexWriter
/// @brief [AI] Leaves the writer-specific initialization mutex for pools. [AI]

// LIBRARY: ISLE 0x406180
// _shi_isNT
/// @brief [AI] Checks if the current OS is Windows NT. [AI]
/// @return TRUE if OS is Windows NT, FALSE otherwise. [AI]

// LIBRARY: ISLE 0x4061b0
// _MemPoolInit@4
/// @brief [AI] Initializes a given memory pool for allocations. [AI]
/// @param pool Pointer to pool to initialize. [AI]

// LIBRARY: ISLE 0x406520
// _MemPoolSetPageSize@8
/// @brief [AI] Sets the page size within a memory pool. [AI]
/// @param pool Memory pool pointer. [AI]
/// @param pageSize Size of each page in bytes. [AI]

// LIBRARY: ISLE 0x406630
// _MemPoolSetBlockSizeFS@8
/// @brief [AI] Sets the fixed-size block size for allocations within the pool. [AI]
/// @param pool Memory pool pointer. [AI]
/// @param blockSize Block size in bytes. [AI]

// LIBRARY: ISLE 0x406710
// @_shi_poolFree@8
/// @brief [AI] Frees an entire memory pool and all contained allocations. [AI]
/// @param pool Pool to free. [AI]
/// @param flags Control flags for free operation. [AI]

// LIBRARY: ISLE 0x4068c0
// @_shi_invokeErrorHandler1@8
/// @brief [AI] Invokes the registered error handler for memory or allocation errors. [AI]
/// @param errorCode Identifies error type. [AI]
/// @param param Additional context. [AI]

// LIBRARY: ISLE 0x406be0
// _MemErrorUnwind@0
/// @brief [AI] Unwinds the memory pool or heap state on allocation failure, possibly rolling back allocations. [AI]

// LIBRARY: ISLE 0x406c30
// _MemDefaultErrorHandler@4
/// @brief [AI] The default error handler invoked when memory allocation problems occur. [AI]
/// @param errorCode Error code identifying the error. [AI]

// LIBRARY: ISLE 0x406cb0
// @_shi_taskRemovePool@4
/// @brief [AI] Removes a pool from the current task or thread context. [AI]
/// @param pool Pool to remove. [AI]

// LIBRARY: ISLE 0x406d50
// @_shi_getCurrentThreadContext@8
/// @brief [AI] Gets the current thread context for allocator management. [AI]
/// @param threadId OS thread identifier. [AI]
/// @param outContext Output pointer for context. [AI]

// LIBRARY: ISLE 0x406db0
// @_shi_deleteThreadContext@8
/// @brief [AI] Deletes the current thread's allocation context when finished. [AI]
/// @param threadId OS thread identifier. [AI]
/// @param context Context pointer to be deleted. [AI]

// LIBRARY: ISLE 0x406e40
// _calloc
/// @brief [AI] Replacement for standard calloc, allocates and zeroes memory. [AI]

// LIBRARY: ISLE 0x406ea0
// _realloc
/// @brief [AI] Replacement for standard realloc, resizes an allocated memory block. [AI]

// LIBRARY: ISLE 0x406f10
// __expand
/// @brief [AI] Expands memory block in-place if possible. [AI]

// LIBRARY: ISLE 0x406f50
// __heapadd
/// @brief [AI] Adds memory region to the process heap. [AI]

// LIBRARY: ISLE 0x406f60
// __heapwalk
/// @brief [AI] Walks all allocated and free blocks in the process heap. [AI]

// LIBRARY: ISLE 0x406ff0
// __heapused
/// @brief [AI] Reports used vs. free heap memory statistics. [AI]

// LIBRARY: ISLE 0x407020
// __heapmin
/// @brief [AI] Minimizes the process heap, returning unused memory to OS. [AI]

// LIBRARY: ISLE 0x407040
// __msize
/// @brief [AI] Gets the size of a memory block allocated by malloc-family. [AI]

// LIBRARY: ISLE 0x407050
// __heapchk
/// @brief [AI] Checks the integrity of the process heap structures. [AI]

// LIBRARY: ISLE 0x407080
// __heapset
/// @brief [AI] Fills the heap with a given byte value for debugging. [AI]

// LIBRARY: ISLE 0x407090
// @_shi_sysReportError@16
/// @brief [AI] Reports an error relating to system-level memory management. [AI]
/// @param errorCode Error code. [AI]
/// @param what Operation or context. [AI]
/// @param details Further detail. [AI]
/// @param severity Error severity. [AI]

// LIBRARY: ISLE 0x407110
// _MemPoolSize@4
/// @brief [AI] Gets the current allocated size (in bytes) in a pool. [AI]
/// @param pool Memory pool. [AI]

// LIBRARY: ISLE 0x4071a0
// _MemPoolWalk@8
/// @brief [AI] Walks through every allocation/block in the given pool, for debugging or reporting purposes. [AI]
/// @param pool Memory pool. [AI]
/// @param callback Callback to invoke for each block. [AI]

// LIBRARY: ISLE 0x407240
// @_shi_walkPool@16
/// @brief [AI] Walks the allocations in the memory pool, invoking handler for each. [AI]
/// @param pool Pool to walk. [AI]
/// @param walkCallback Handler to call for each allocation. [AI]
/// @param context Opaque context for the callback. [AI]
/// @param attrib Additional filter or category info. [AI]

// LIBRARY: ISLE 0x407540
// @shi_isBlockInUseSmall@8
/// @brief [AI] Checks if a fixed-size (small) memory block is in use. [AI]
/// @param pool Pool pointer. [AI]
/// @param block Block pointer to check. [AI]

// LIBRARY: ISLE 0x407800
// @_shi_isBlockInUseFS@12
/// @brief [AI] Checks if a block in a fixed-size pool is in use. [AI]
/// @param pool Pool pointer. [AI]
/// @param block Block pointer. [AI]
/// @param flags Check flags. [AI]

// LIBRARY: ISLE 0x407880
// _MemPoolCheck@4
/// @brief [AI] Checks the integrity of the memory pool structures. [AI]
/// @param pool Memory pool to check. [AI]

// LIBRARY: ISLE 0x407b20
// _MemCheckPtr@8
/// @brief [AI] Checks if a given memory pointer is valid within the allocator. [AI]
/// @param pool Memory pool. [AI]
/// @param ptr Memory pointer to check. [AI]

// LIBRARY: ISLE 0x4084e0
// __except_handler3
/// @brief [AI] SEH (Structured Exception Handling) handler implementation (MSVC internal). [AI]

// GLOBAL: ISLE 0x40f0a0
// _szLibName
/// @brief [AI] Library name string. [AI]

// GLOBAL: ISLE 0x4102f4
// ?_new_handler@@3P6AXXZA
/// @brief [AI] Pointer to the standard C++ new handler function. [AI]

// GLOBAL: ISLE 0x4102fc
// _MemDefaultPool
/// @brief [AI] Pointer to the default memory pool for allocations. [AI]

// GLOBAL: ISLE 0x41031c
// __shi_compactPoolFn
/// @brief [AI] Compact pool callback function pointer for internal management. [AI]

// GLOBAL: ISLE 0x410320
// __shi_compactPageFn
/// @brief [AI] Callback for compacting individual memory pages. [AI]

// GLOBAL: ISLE 0x410324
// _MemDefaultPoolFlags
/// @brief [AI] Flags controlling default memory pool behavior. [AI]

// GLOBAL: ISLE 0x41032c
// __shi_mutexGlobalInit
/// @brief [AI] Global initialization flag/mutex for allocator system. [AI]

// GLOBAL: ISLE 0x410330
// __shi_mutexMovInit
/// @brief [AI] Initialization status or reference count for moveable pool mutex structure. [AI]

// GLOBAL: ISLE 0x410334
// __shi_mutexMovLockCount
/// @brief [AI] Lock count for moveable pool mutex. [AI]

// GLOBAL: ISLE 0x410338
// _shi_initPoolReaders
/// @brief [AI] Readers initialization flag for pool access. [AI]

// GLOBAL: ISLE 0x41033c
// _shi_eventInitPool
/// @brief [AI] Pool initialization event handle or flag. [AI]

// GLOBAL: ISLE 0x410340
// _shi_mutexMovShr
/// @brief [AI] Shared moveable pool mutex handle or structure. [AI]

// GLOBAL: ISLE 0x410368
// _shi_deferFreePools
/// @brief [AI] List of pools pending deferred freeing. [AI]

// GLOBAL: ISLE 0x410378
// __shi_poolTerminating
/// @brief [AI] Flag indicating pool system is terminating. [AI]

// GLOBAL: ISLE 0x41037c
// _MemDefaultPoolBlockSizeFS
/// @brief [AI] Block size for fixed-size allocations in the default pool. [AI]

// GLOBAL: ISLE 0x410380
// _MemDefaultPoolPageSize
/// @brief [AI] Page size for allocations in the default pool. [AI]

// GLOBAL: ISLE 0x410384
// _SmartHeap_malloc
/// @brief [AI] Function pointer to custom malloc implementation (SmartHeap). [AI]

// GLOBAL: ISLE 0x4105b0
// __shi_TaskRecord
/// @brief [AI] Per-task or per-thread tracking record for pool usage. [AI]

// GLOBAL: ISLE 0x4125f8
// ?_pnhHeap@@3P6AHI@ZA
/// @brief [AI] Pointer to the heap's new handler routine (for __msize, etc). [AI]

// GLOBAL: ISLE 0x412830
// __shi_mutexMov
/// @brief [AI] Mutex (possibly moveable) for synchronization of pool access. [AI]

// GLOBAL: ISLE 0x412850
// _shi_mutexPoolSynch
/// @brief [AI] Mutex for synchronous pool operation, ensuring exclusive access. [AI]

// GLOBAL: ISLE 0x412870
// __shi_mutexGlobal
/// @brief [AI] Global mutex for system-wide allocator synchronization. [AI]

#endif
