#ifdef 0
// For ISLE symbols only

// aka `operator new`
// LIBRARY: ISLE 0x402f80
// ??2@YAPAXI@Z
/// @brief [AI] Operator new for allocating memory blocks. ISLE runtime memory allocation. [AI]
/// @details [AI] This is the global operator new for the ISLE executable. Used for normal heap allocation in C++ object creation. [AI]

// aka `operator delete`
// LIBRARY: ISLE 0x402fa0
// ??3@YAXPAX@Z
/// @brief [AI] Operator delete for deallocating memory blocks. ISLE runtime memory deallocation. [AI]
/// @details [AI] This is the global operator delete for the ISLE executable. Used for standard object destruction and heap freeing. [AI]

// LIBRARY: ISLE 0x406dd0
// _malloc
/// @brief [AI] C-runtime style memory allocation function. [AI]

// LIBRARY: ISLE 0x406f00
// _free
/// @brief [AI] C-runtime style memory deallocation function. [AI]

// LIBRARY: ISLE 0x407ec0
// ___CxxFrameHandler
/// @brief [AI] C++ exception stack frame handler for structured exception handling (SEH). [AI]

// LIBRARY: ISLE 0x4080ec
// __global_unwind2
/// @brief [AI] Unwinds the stack during C++ exception propagation. [AI]

// LIBRARY: ISLE 0x40812e
// __local_unwind2
/// @brief [AI] Unwinds local (function-level) stack frames for SEH. [AI]

// LIBRARY: ISLE 0x4081b9
// __NLG_Notify1
/// @brief [AI] Notification handler for non-local goto in exception handling. [AI]

// LIBRARY: ISLE 0x4081c2
// __NLG_Notify
/// @brief [AI] System notification for non-local goto during control transfer (exception unwinding). [AI]

// LIBRARY: ISLE 0x4081e0
// _srand
/// @brief [AI] Sets the seed for the standard pseudo-random number generator. [AI]

// LIBRARY: ISLE 0x4081f0
// _rand
/// @brief [AI] Generates pseudo-random numbers. [AI]

// LIBRARY: ISLE 0x408220
// _atol
/// @brief [AI] Converts a string to a long integer. [AI]

// LIBRARY: ISLE 0x4082d0
// _atoi
/// @brief [AI] Converts a string to an int. [AI]

// LIBRARY: ISLE 0x408490
// __amsg_exit
/// @brief [AI] Outputs a runtime library diagnostic message and terminates the process. [AI]

// LIBRARY: ISLE 0x4084c0
// ?_query_new_handler@@YAP6AHI@ZXZ
/// @brief [AI] Queries the global new handler function pointer. [AI]

// LIBRARY: ISLE 0x4084d0
// ?_query_new_mode@@YAHXZ
/// @brief [AI] Queries the global new allocation mode for memory allocation. [AI]

// LIBRARY: ISLE 0x4085c0
// _sprintf
/// @brief [AI] Formatted string output to buffer. [AI]

// LIBRARY: ISLE 0x408630
// _abort
/// @brief [AI] Abnormal program termination. [AI]

// LIBRARY: ISLE 0x408650
// ___InternalCxxFrameHandler
/// @brief [AI] Internal exception frame handler used by the C++ runtime. [AI]

// LIBRARY: ISLE 0x408b30
// ___FrameUnwindToState
/// @brief [AI] Performs stack unwinding to a particular frame or state, for SEH. [AI]

// LIBRARY: ISLE 0x4090c0
// __CallSettingFrame@12
/// @brief [AI] Calls a function as part of C++ exception frame setup. [AI]

// LIBRARY: ISLE 0x409110
// __mtinit
/// @brief [AI] Initializes multithreading support in the C runtime library. [AI]

// LIBRARY: ISLE 0x409170
// __initptd
/// @brief [AI] Initializes per-thread data for the C runtime. [AI]

// LIBRARY: ISLE 0x409190
// __getptd
/// @brief [AI] Gets the per-thread data structure pointer for CRT. [AI]

// LIBRARY: ISLE 0x409200
// __isctype
/// @brief [AI] Configuration for ctype functions (e.g., isalpha, isdigit). [AI]

// LIBRARY: ISLE 0x4092e0
// ?terminate@@YAXXZ
/// @brief [AI] Called on unhandled C++ exception; terminates the process. [AI]

// LIBRARY: ISLE 0x409360
// ?_inconsistency@@YAXXZ
/// @brief [AI] Notified on detected runtime inconsistency or corruption. [AI]

// LIBRARY: ISLE 0x4093e0
// __cinit
/// @brief [AI] Initializes C runtime data or tables. [AI]

// LIBRARY: ISLE 0x409410
// _exit
/// @brief [AI] Standard program exit, flushes streams and terminates process. [AI]

// LIBRARY: ISLE 0x409430
// __exit
/// @brief [AI] Lower-level variant of program exit/termination. [AI]

// LIBRARY: ISLE 0x409550
// __XcptFilter
/// @brief [AI] Structured exception filter function, used by C++ runtime. [AI]

// LIBRARY: ISLE 0x4096d0
// __ismbblead
/// @brief [AI] Multi-byte (DBCS) lead byte test: locale support. [AI]

// LIBRARY: ISLE 0x409730
// __setenvp
/// @brief [AI] Setup and initialize process environment pointer list. [AI]

// LIBRARY: ISLE 0x409820
// __setargv
/// @brief [AI] Setup and initialize program command-line arguments list. [AI]

// LIBRARY: ISLE 0x409a90
// ___crtGetEnvironmentStringsA
/// @brief [AI] Returns ANSI environment strings array pointer. [AI]

// LIBRARY: ISLE 0x409c20
// __setmbcp
/// @brief [AI] Configure multi-byte code page in runtime. [AI]

// LIBRARY: ISLE 0x409f30
// ___initmbctable
/// @brief [AI] Initializes multi-byte character table for CRT. [AI]

// LIBRARY: ISLE 0x409f40
// __ioinit
/// @brief [AI] Initializes low-level I/O subsystem in CRT. [AI]

// LIBRARY: ISLE 0x40a120
// __heap_init
/// @brief [AI] Allocates and initializes process heap. [AI]

// LIBRARY: ISLE 0x40a160
// __FF_MSGBANNER
/// @brief [AI] Displays CRT error message banner. [AI]

// LIBRARY: ISLE 0x40a1a0
// __NMSG_WRITE
/// @brief [AI] Outputs CRT runtime message (error or status) to console. [AI]

// LIBRARY: ISLE 0x40a3a0
// __mtinitlocks
/// @brief [AI] Initialize locking resources for multithreading safety. [AI]

// LIBRARY: ISLE 0x40a3d0
// __lock
/// @brief [AI] Locks a CRT resource for thread safety. [AI]

// LIBRARY: ISLE 0x40a440
// __unlock
/// @brief [AI] Unlocks a CRT resource. [AI]

// LIBRARY: ISLE 0x40a540
// __flsbuf
/// @brief [AI] Flushes (writes) a buffer for file output. [AI]

// LIBRARY: ISLE 0x40a690
// __output
/// @brief [AI] Handles low-level formatted output to files or streams. [AI]

// LIBRARY: ISLE 0x40b090
// _write_multi_char
/// @brief [AI] Outputs (writes) a repeated character sequence to file/stream. [AI]

// LIBRARY: ISLE 0x40b0d0
// _write_string
/// @brief [AI] Outputs a string to a file or device. [AI]

// LIBRARY: ISLE 0x40b150
// _raise
/// @brief [AI] Raises a signal or exception in the process. [AI]

// LIBRARY: ISLE 0x40b780
// ___crtGetStringTypeA
/// @brief [AI] Gets string character type information for ANSI strings (locale-sensitive). [AI]

// LIBRARY: ISLE 0x40b8b0
// ___sbh_new_region
/// @brief [AI] Allocates a new region in the small block heap. [AI]

// LIBRARY: ISLE 0x40ba20
// ___crtMessageBoxA
/// @brief [AI] Displays an ANSI message box dialog window (CRT utility). [AI]

// LIBRARY: ISLE 0x40bac0
// _strncpy
/// @brief [AI] Copies N characters from source to destination C string. [AI]

// LIBRARY: ISLE 0x40bcb0
// __write
/// @brief [AI] Low-level write operation for files/handles. [AI]

// LIBRARY: ISLE 0x40bd30
// __write_lk
/// @brief [AI] Locked write operation for file/handle, thread-safe. [AI]

// LIBRARY: ISLE 0x40bf30
// __lseek
/// @brief [AI] Low-level seek operation for random access in files. [AI]

// LIBRARY: ISLE 0x40bfb0
// __lseek_lk
/// @brief [AI] Locked file seek operation, thread-safe. [AI]

// LIBRARY: ISLE 0x40c040
// __getbuf
/// @brief [AI] Gets (allocates or retrieves) a buffer for file operations. [AI]

// LIBRARY: ISLE 0x40c090
// __isatty
/// @brief [AI] Determines whether a file descriptor refers to a terminal device. [AI]

// LIBRARY: ISLE 0x40c0c0
// _wctomb
/// @brief [AI] Converts a wide character to a multibyte character (locale conversion). [AI]

// LIBRARY: ISLE 0x40c120
// __wctomb_lk
/// @brief [AI] Thread-safe wide char to multibyte conversion. [AI]

// LIBRARY: ISLE 0x40c1c0
// __aulldiv
/// @brief [AI] 64-bit unsigned integer division operation. [AI]

// LIBRARY: ISLE 0x40c230
// __aullrem
/// @brief [AI] 64-bit unsigned integer remainder/modulo operation. [AI]

// LIBRARY: ISLE 0x40c2b0
// __dosmaperr
/// @brief [AI] Maps low-level OS error codes to CRT error codes. [AI]

// LIBRARY: ISLE 0x40c330
// __errno
/// @brief [AI] Returns the thread-local error number variable pointer. [AI]

// LIBRARY: ISLE 0x40c340
// ___doserrno
/// @brief [AI] Returns last DOS/OS error code. [AI]

// LIBRARY: ISLE 0x40c710
// __get_osfhandle
/// @brief [AI] Retrieves the OS file handle for a CRT file descriptor. [AI]

// LIBRARY: ISLE 0x40c760
// __lock_fhandle
/// @brief [AI] Locks a file handle for thread-safe file operations. [AI]

// LIBRARY: ISLE 0x40c7d0
// __unlock_fhandle
/// @brief [AI] Unlocks a previously-locked file handle. [AI]

// LIBRARY: ISLE 0x40c810
// __fptrap
/// @brief [AI] Handles floating-point exceptions or traps. [AI]

// GLOBAL: ISLE 0x40f448
// ___lookuptable
/// @brief [AI] Lookup table for C runtime or application-internal use. [AI]

// GLOBAL: ISLE 0x410000
// ___xc_a
/// @brief [AI] Start of constructor function table (.CRT$XCA) for static objects. [AI]

// GLOBAL: ISLE 0x410008
// ___xc_z
/// @brief [AI] End of constructor function table (.CRT$XCZ) for static objects. [AI]

// GLOBAL: ISLE 0x41000c
// ___xi_a
/// @brief [AI] Start of initializer function table (.CRT$XIA) for CRT init routines. [AI]

// GLOBAL: ISLE 0x410018
// ___xi_z
/// @brief [AI] End of initializer function table (.CRT$XIZ). [AI]

// GLOBAL: ISLE 0x41068c
// __NLG_Destination
/// @brief [AI] Non-local goto destination for SEH and exception handling. [AI]

// GLOBAL: ISLE 0x41069c
// __aenvptr
/// @brief [AI] Pointer to application environment table. [AI]

// GLOBAL: ISLE 0x4106a8
// ___error_mode
/// @brief [AI] Global error mode status variable. [AI]

// GLOBAL: ISLE 0x4106ac
// ___app_type
/// @brief [AI] Variable indicating type of application (GUI/console). [AI]

// GLOBAL: ISLE 0x4106c0
// ___tlsindex
/// @brief [AI] Index for Thread-Local Storage slot (CRT use). [AI]

// GLOBAL: ISLE 0x4106c8
// __pctype
/// @brief [AI] Character classification table pointer for locale functions. [AI]

// GLOBAL: ISLE 0x4108d4
// ___mb_cur_max
/// @brief [AI] Max length of a multibyte character for current locale. [AI]

// GLOBAL: ISLE 0x4108e0
// ?__pInconsistency@@3P6AXXZA
/// @brief [AI] Function pointer for inconsistency handler, called on CRT error. [AI]

// GLOBAL: ISLE 0x4108e8
// __osver
/// @brief [AI] Stores the Windows OS version for runtime environment. [AI]

// GLOBAL: ISLE 0x4108ec
// __winver
/// @brief [AI] Stores the Windows version for runtime environment. [AI]

// GLOBAL: ISLE 0x4108f0
// __winmajor
/// @brief [AI] Major version of Windows. [AI]

// GLOBAL: ISLE 0x4108f4
// __winminor
/// @brief [AI] Minor version of Windows. [AI]

// GLOBAL: ISLE 0x4108f8
// ___argc
/// @brief [AI] Number of command-line arguments. [AI]

// GLOBAL: ISLE 0x4108fc
// ___argv
/// @brief [AI] Pointer to command-line argument array. [AI]

// GLOBAL: ISLE 0x410904
// __environ
/// @brief [AI] Pointer to process environment variables. [AI]

// GLOBAL: ISLE 0x410914
// __pgmptr
/// @brief [AI] Pointer to full path of the running program. [AI]

// GLOBAL: ISLE 0x410928
// __XcptActTab
/// @brief [AI] Table of actions or handlers for process exceptions. [AI]

// GLOBAL: ISLE 0x4109a0
// __First_FPE_Indx
/// @brief [AI] First index for floating-point exception information. [AI]

// GLOBAL: ISLE 0x4109a4
// __Num_FPE
/// @brief [AI] Number of floating-point exception entries. [AI]

// GLOBAL: ISLE 0x4109b8
// __mbctype
/// @brief [AI] Multibyte character type information table for locales. [AI]

// GLOBAL: ISLE 0x410abc
// ___mbcodepage
/// @brief [AI] Current multibyte codepage identifier. [AI]

// GLOBAL: ISLE 0x410ac0
// ___mblcid
/// @brief [AI] Multibyte locale identifier for current process. [AI]

// GLOBAL: ISLE 0x410ac8
// ___mbulinfo
/// @brief [AI] Pointer to multibyte locale info structure. [AI]

// GLOBAL: ISLE 0x410bd0
// ___badioinfo
/// @brief [AI] Pointer to CRT I/O structures for bad file descriptors. [AI]

// GLOBAL: ISLE 0x410c88
// __adbgmsg
/// @brief [AI] Pointer to CRT debug message buffer. [AI]

// GLOBAL: ISLE 0x410c90
// __locktable
/// @brief [AI] Table of lock objects for CRT resource synchronization. [AI]

// GLOBAL: ISLE 0x410d50
// __newmode
/// @brief [AI] Runtime allocation mode for operator new; affects allocation error handling. [AI]

// GLOBAL: ISLE 0x410d54
// ___nullstring
/// @brief [AI] Pointer to global null/empty string (ANSI). [AI]

// GLOBAL: ISLE 0x410d58
// ___wnullstring
/// @brief [AI] Pointer to global null/empty string (wide char). [AI]

// GLOBAL: ISLE 0x410d90
// ___lc_codepage
/// @brief [AI] Locale code page for current C runtime. [AI]

// GLOBAL: ISLE 0x410d98
// ___small_block_heap
/// @brief [AI] Pointer/structure for the CRT small block heap. [AI]

// GLOBAL: ISLE 0x411850
// __cflush
/// @brief [AI] Flushes C-streams and buffered output. [AI]

// XGLOBAL ISLE 0x4125f8
// ?_pnhHeap@@3P6AHI@ZA
/// @brief [AI] Pointer to the process heap new handler function. [AI]

// GLOBAL: ISLE 0x412888
// ___setlc_active
/// @brief [AI] CRT flag indicating whether locale has been set/activated. [AI]

// GLOBAL: ISLE 0x41288c
// ___unguarded_readlc_active
/// @brief [AI] CRT flag for unguarded locale reading. [AI]

// GLOBAL: ISLE 0x4138a4
// __crtheap
/// @brief [AI] Pointer to CRT process heap. [AI]

// GLOBAL: ISLE 0x4138b0
// ___pioinfo
/// @brief [AI] File descriptor information array for CRT. [AI]

// GLOBAL: ISLE 0x4139b0
// __nhandle
/// @brief [AI] Number of open handles/file descriptors. [AI]

// GLOBAL: ISLE 0x4139bc
// __FPinit
/// @brief [AI] Floating-point environment initialization table. [AI]

// GLOBAL: ISLE 0x4139c0
// __acmdln
/// @brief [AI] Pointer to process command-line string. [AI]

#endif
