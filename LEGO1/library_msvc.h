#ifdef 0
// For LEGO1 symbols only

// aka `operator new`
// LIBRARY: LEGO1 0x10086240
// ??2@YAPAXI@Z
/// @brief [AI] Standard memory allocation operator used to allocate memory for objects in the LEGO1 codebase. Usually maps directly to C++'s operator new. [AI]
/// @details [AI] This function is used throughout the game for dynamic memory allocation. [AI]

// aka `operator delete`
// LIBRARY: LEGO1 0x10086260
// ??3@YAXPAX@Z
/// @brief [AI] Standard memory deallocation operator used to free objects in the LEGO1 codebase. Maps to operator delete. [AI]
/// @details [AI] Deallocates memory previously allocated with operator new or malloc. [AI]

// LIBRARY: LEGO1 0x1008a090
// _malloc
/// @brief [AI] Allocates a block of memory of the specified size. Corresponds to the standard C malloc. [AI]
/// @param size Number of bytes to allocate. [AI]

// LIBRARY: LEGO1 0x1008a100
// _calloc
/// @brief [AI] Allocates and zero-initializes an array. Corresponds to the standard C calloc function. [AI]
/// @param num Number of elements to allocate. [AI]
/// @param size Size in bytes of each element. [AI]

// LIBRARY: LEGO1 0x1008a1c0
// _free
/// @brief [AI] Deallocates a memory block previously allocated with malloc/calloc/realloc. [AI]
/// @param ptr Pointer to memory block to free. [AI]

// LIBRARY: LEGO1 0x1008b020
// LIBRARY: BETA10 0x100f8d20
// ___CxxFrameHandler
/// @brief [AI] Exception handler for C++ frame-based exceptions. Used by the MSVC runtime for exception processing. [AI]

// LIBRARY: LEGO1 0x1008b24c
// __global_unwind2
/// @brief [AI] Performs global stack unwinding for structured exception handling. [AI]

// LIBRARY: LEGO1 0x1008b28e
// __local_unwind2
/// @brief [AI] Performs local stack unwinding to clean up stack frames for structured exception handling. [AI]

// LIBRARY: LEGO1 0x1008b319
// __NLG_Notify1
/// @brief [AI] Supports non-local goto and exception unwinding notifications in the MSVC runtime. [AI]

// LIBRARY: LEGO1 0x1008b322
// __NLG_Notify
/// @brief [AI] Used internally for non-local goto/unwinding notifications. [AI]

// LIBRARY: LEGO1 0x1008b340
// __FPinit
/// @brief [AI] Initializes the floating point unit control state for the process/thread. [AI]

// LIBRARY: LEGO1 0x1008b3dc
// __CIacos
/// @brief [AI] Computes the arc-cosine of a value. Internal C runtime intrinsic. [AI]

// LIBRARY: LEGO1 0x1008b400
// _atol
/// @brief [AI] Converts a string to a long integer. Standard C atol. [AI]

// LIBRARY: LEGO1 0x1008b4b0
// _atoi
/// @brief [AI] Converts a string to an integer. Standard C atoi. [AI]

// LIBRARY: LEGO1 0x1008b4c0
// _strtok
/// @brief [AI] Tokenizes a string using given delimiters, modifies original string. Standard C strtok. [AI]

// LIBRARY: LEGO1 0x1008b5a0
// _sprintf
/// @brief [AI] Formats and stores a series of characters and values in a string. Standard C sprintf. [AI]

// LIBRARY: LEGO1 0x1008b608
// LIBRARY: BETA10 0x100f9660
// __ftol
/// @brief [AI] Converts a floating point number to a long integer. Used for internal floating-point conversions. [AI]

// LIBRARY: LEGO1 0x1008b630
// _srand
/// @brief [AI] Sets the seed for the random number generator. Standard C srand. [AI]

// LIBRARY: LEGO1 0x1008b640
// _rand
/// @brief [AI] Returns a pseudo-random number. Standard C rand. [AI]

// LIBRARY: LEGO1 0x1008b670
// __purecall
/// @brief [AI] Called when a pure virtual function is called. Indicates a programming error in abstract base classes. [AI]

// LIBRARY: LEGO1 0x1008b680
// _strncmp
/// @brief [AI] Compares up to the first N characters of two strings. Standard C strncmp. [AI]

// LIBRARY: LEGO1 0x1008b6c0
// _atof
/// @brief [AI] Converts a string to a floating-point value. Standard C atof. [AI]

// LIBRARY: LEGO1 0x1008b730
// _fprintf
/// @brief [AI] Writes formatted output to a stream. Standard C fprintf. [AI]

// LIBRARY: LEGO1 0x1008b780
// _fwrite
/// @brief [AI] Writes data to a stream, non-thread-safe version. Standard C fwrite. [AI]

// LIBRARY: LEGO1 0x1008b7c0
// __fwrite_lk
/// @brief [AI] Writes data to a stream with locking for thread-safety. Internal CRT implementation. [AI]

// LIBRARY: LEGO1 0x1008b950
// _fread
/// @brief [AI] Reads data from a stream, non-thread-safe version. Standard C fread. [AI]

// LIBRARY: LEGO1 0x1008b990
// __fread_lk
/// @brief [AI] Reads data from a stream with locking for thread-safety. Internal CRT implementation. [AI]

// LIBRARY: LEGO1 0x1008bbd0
// _fclose
/// @brief [AI] Closes an open file. Standard C fclose. [AI]

// LIBRARY: LEGO1 0x1008bc10
// __fclose_lk
/// @brief [AI] Closes an open file with lock protection. Internal CRT version of fclose. [AI]

// LIBRARY: LEGO1 0x1008bc70
// __cinit
/// @brief [AI] Initializes the C runtime library before main() is called. [AI]

// LIBRARY: LEGO1 0x1008bca0
// __exit
/// @brief [AI] Terminates the process immediately. Equivalent to exit(). [AI]

// LIBRARY: LEGO1 0x1008bcc0
// __cexit
/// @brief [AI] Terminates the C runtime environment and the process. Invoked for cleanup and exit. [AI]

// LIBRARY: LEGO1 0x1008bdd0
// _ftell
/// @brief [AI] Returns the current file position of a stream. Standard C ftell. [AI]

// LIBRARY: LEGO1 0x1008be00
// __ftell_lk
/// @brief [AI] ftell with locking for thread safety. [AI]

// LIBRARY: LEGO1 0x1008bfb0
// __fsopen
/// @brief [AI] Opens a file stream with extra sharing options for the C runtime. [AI]

// LIBRARY: LEGO1 0x1008bff0
// _fopen
/// @brief [AI] Opens a file for reading, writing, or both. Standard C fopen. [AI]

// LIBRARY: LEGO1 0x1008c010
// _strncpy
/// @brief [AI] Copies a fixed number of characters from one string to another. Standard C strncpy. [AI]

// LIBRARY: LEGO1 0x1008c110
// __strcmpi
/// @brief [AI] Compares two strings case-insensitively. [AI]

// LIBRARY: LEGO1 0x1008c1e0
// __spawnl
/// @brief [AI] Creates and executes a new process. Standard C spawnl. [AI]

// LIBRARY: LEGO1 0x1008c200
// _sscanf
/// @brief [AI] Reads formatted input from a string. Standard C sscanf. [AI]

// LIBRARY: LEGO1 0x1008c250
// ??_L@YGXPAXIHP6EX0@Z1@Z
/// @brief [AI] Internal CRT function used for array destruction/unwinding during exception handling. [AI]

// LIBRARY: LEGO1 0x1008c2e0
// ??_M@YGXPAXIHP6EX0@Z@Z
/// @brief [AI] Internal CRT function for array construction with exception support. [AI]

// LIBRARY: LEGO1 0x1008c370
// ?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z
/// @brief [AI] Helper for proper array element destruction in exception handling contexts. [AI]

// LIBRARY: LEGO1 0x1008c410
// _strlwr
/// @brief [AI] Converts a string to lowercase. Non-standard but commonly available. [AI]

// LIBRARY: LEGO1 0x1008c570
// _access
/// @brief [AI] Checks user permissions for a file. Standard POSIX-style access. [AI]

// LIBRARY: LEGO1 0x1008c5c0
// _fseek
/// @brief [AI] Moves file position to a specific location in a stream. Standard C fseek. [AI]

// LIBRARY: LEGO1 0x1008c600
// __fseek_lk
/// @brief [AI] fseek with locking for thread-safety. [AI]

// LIBRARY: LEGO1 0x1008c6a0
// _isdigit
/// @brief [AI] Checks if a character is a numeric digit. Standard C isdigit. [AI]

// LIBRARY: LEGO1 0x1008c6d0
// _isspace
/// @brief [AI] Checks if a character is whitespace. Standard C isspace. [AI]

// LIBRARY: LEGO1 0x1008c700
// __CRT_INIT@12
/// @brief [AI] CRT initialization function, called upon DLL/process attach/detach. [AI]

// LIBRARY: LEGO1 0x1008c920
// __amsg_exit
/// @brief [AI] Outputs runtime error message and terminates. Internal error handling function. [AI]

// LIBRARY: LEGO1 0x1008c980
// __except_handler3
/// @brief [AI] Structured exception handler (SEH) for MSVC C runtime. [AI]

// LIBRARY: LEGO1 0x1008ca60
// _abort
/// @brief [AI] Abnormal program termination, standard abort(). [AI]

// LIBRARY: LEGO1 0x1008ca80
// ___InternalCxxFrameHandler
/// @brief [AI] Internal C++ exception handler used in MSVC for frame-based exception dispatch. [AI]

// LIBRARY: LEGO1 0x1008cf60
// ___FrameUnwindToState
/// @brief [AI] Unwinds stack frames up to a specific state for exception handling. [AI]

// LIBRARY: LEGO1 0x1008d4f0
// __CallSettingFrame@12
/// @brief [AI] Helper to call a function with a specific frame setting, supporting SEH. [AI]

// LIBRARY: LEGO1 0x1008d540
// __mtinit
/// @brief [AI] Initializes multi-threading support in CRT. [AI]

// LIBRARY: LEGO1 0x1008d5a0
// __mtterm
/// @brief [AI] Terminates multi-threading support in CRT. [AI]

// LIBRARY: LEGO1 0x1008d5d0
// __initptd
/// @brief [AI] Initializes per-thread data in CRT. [AI]

// LIBRARY: LEGO1 0x1008d5f0
// __getptd
/// @brief [AI] Retrieves pointer to the calling thread's data. [AI]

// LIBRARY: LEGO1 0x1008d660
// __freeptd
/// @brief [AI] Frees thread-local CRT data. [AI]

// LIBRARY: LEGO1 0x1008dd90
// __cintrindisp2
/// @brief [AI] CRT internal dispatcher for C intrinsic routines. [AI]

// LIBRARY: LEGO1 0x1008e000
// __isctype
/// @brief [AI] Checks the character type using locale-based classification. [AI]

// LIBRARY: LEGO1 0x1008e0a0
// __allmul
/// @brief [AI] Multiplies two 64-bit integer values. Used for 32/64 bit math support in CRT. [AI]

// LIBRARY: LEGO1 0x1008e0e0
// __flsbuf
/// @brief [AI] Fills output buffer and flushes if necessary for buffered streams. [AI]

// LIBRARY: LEGO1 0x1008e230
// __output
/// @brief [AI] Internal output formatting routine for CRT. [AI]

// LIBRARY: LEGO1 0x1008ecf0
// __fltin2
/// @brief [AI] Converts string to floating-point value. Used internally for number parsing. [AI]

// LIBRARY: LEGO1 0x1008ed90
// __mtinitlocks
/// @brief [AI] Initializes CRT locking structures for multi-threading. [AI]

// LIBRARY: LEGO1 0x1008edc0
// __mtdeletelocks
/// @brief [AI] Deletes CRT lock structures used for thread safety. [AI]

// LIBRARY: LEGO1 0x1008ee30
// __lock
/// @brief [AI] Locks CRT data structures to ensure thread safety. [AI]

// LIBRARY: LEGO1 0x1008eea0
// __unlock
/// @brief [AI] Unlocks CRT data structures. [AI]

// LIBRARY: LEGO1 0x1008eec0
// __lock_file
/// @brief [AI] Locks a file stream for thread-safety in I/O operations. [AI]

// LIBRARY: LEGO1 0x1008ef00
// __lock_file2
/// @brief [AI] Secondary file stream lock for CRT file I/O. [AI]

// LIBRARY: LEGO1 0x1008ef30
// __unlock_file
/// @brief [AI] Unlocks a file stream in CRT for I/O. [AI]

// LIBRARY: LEGO1 0x1008ef70
// __unlock_file2
/// @brief [AI] Secondary unlock for file stream in CRT. [AI]

// LIBRARY: LEGO1 0x1008efa0
// __stbuf
/// @brief [AI] Sets up the internal buffer for a FILE structure, used by CRT. [AI]

// LIBRARY: LEGO1 0x1008f040
// __ftbuf
/// @brief [AI] Manages temporary buffer for file I/O. [AI]

// LIBRARY: LEGO1 0x1008f080
// __write
/// @brief [AI] Low-level write for CRT file descriptors. [AI]

// LIBRARY: LEGO1 0x1008f100
// __write_lk
/// @brief [AI] Low-level write with locking (thread-safe) for CRT file descriptors. [AI]

// LIBRARY: LEGO1 0x1008f340
// __flush
/// @brief [AI] Flushes buffers for output streams in CRT. [AI]

// LIBRARY: LEGO1 0x1008f490
// __filbuf
/// @brief [AI] Fills input buffer for file stream in CRT. [AI]

// LIBRARY: LEGO1 0x1008f590
// __read
/// @brief [AI] Low-level read for CRT file descriptors. [AI]

// LIBRARY: LEGO1 0x1008f610
// __read_lk
/// @brief [AI] Low-level read (thread-safe) with locking for CRT file descriptors. [AI]

// LIBRARY: LEGO1 0x1008f840
// __ioinit
/// @brief [AI] Initializes CRT stream/file I/O structures. [AI]

// LIBRARY: LEGO1 0x1008fa20
// __ioterm
/// @brief [AI] Terminates/cleans up CRT file I/O structures. [AI]

// LIBRARY: LEGO1 0x1008fb20
// __close
/// @brief [AI] Low-level close for CRT file descriptor. [AI]

// LIBRARY: LEGO1 0x1008fb90
// __close_lk
/// @brief [AI] Low-level close with locking (thread-safe) for CRT file descriptor. [AI]

// LIBRARY: LEGO1 0x1008fc20
// __freebuf
/// @brief [AI] Frees a buffer used by FILE streams. [AI]

// LIBRARY: LEGO1 0x1008fc90
// __chkstk
/// @brief [AI] Checks and grows the stack as needed to prevent stack overflow. [AI]

// LIBRARY: LEGO1 0x1008fcc0
// __lseek
/// @brief [AI] Sets file position for a file descriptor. [AI]

// LIBRARY: LEGO1 0x1008fd40
// __lseek_lk
/// @brief [AI] Sets file position with locking for CRT file descriptor. [AI]

// LIBRARY: LEGO1 0x1008fdd0
// __dosmaperr
/// @brief [AI] Maps DOS error codes to C runtime error codes. [AI]

// LIBRARY: LEGO1 0x1008fe50
// __errno
/// @brief [AI] Returns pointer to the current thread's errno value. [AI]

// LIBRARY: LEGO1 0x1008fe60
// ___doserrno
/// @brief [AI] Returns DOS-specific error code for last operation. [AI]

// LIBRARY: LEGO1 0x1008fe70
// __openfile
/// @brief [AI] Opens a file given a filename and mode, low-level CRT utility. [AI]

// LIBRARY: LEGO1 0x10090080
// __getstream
/// @brief [AI] Allocates and returns a FILE structure for CRT use. [AI]

// LIBRARY: LEGO1 0x100901f0
// __tolower_lk
/// @brief [AI] Converts character to lowercase with locking, locale-aware. [AI]

// LIBRARY: LEGO1 0x100902e0
// __spawnve
/// @brief [AI] Creates a new process, passing an environment array (variant of spawn). [AI]

// LIBRARY: LEGO1 0x10090580
// __input
/// @brief [AI] Reads formatted or string input from input stream, CRT internal. [AI]

// LIBRARY: LEGO1 0x100912e0
// ?terminate@@YAXXZ
/// @brief [AI] Terminates the process, MSVC++ internal terminate handler. [AI]

// LIBRARY: LEGO1 0x10091360
// ?_inconsistency@@YAXXZ
/// @brief [AI] Handler invoked when runtime detects CRT state inconsistency. [AI]

// LIBRARY: LEGO1 0x100913e0
// ___crtLCMapStringA
/// @brief [AI] Locale-aware string mapping/conversion utility. [AI]

// LIBRARY: LEGO1 0x10091640
// __heap_init
/// @brief [AI] Initializes the CRT heap memory manager. [AI]

// LIBRARY: LEGO1 0x10091680
// __heap_term
/// @brief [AI] Terminates CRT heap; cleans up memory management structures. [AI]

// LIBRARY: LEGO1 0x100916c0
// __setenvp
/// @brief [AI] Sets up environment variable array in CRT. [AI]

// LIBRARY: LEGO1 0x100917b0
// __setargv
/// @brief [AI] Sets up argv array for the process in CRT. [AI]

// LIBRARY: LEGO1 0x10091a20
// __setmbcp
/// @brief [AI] Sets up the multi-byte code page in the CRT locale. [AI]

// LIBRARY: LEGO1 0x10091d30
// ___initmbctable
/// @brief [AI] Initializes multi-byte character classification tables. [AI]

// LIBRARY: LEGO1 0x10091d40
// ___crtGetEnvironmentStringsA
/// @brief [AI] Retrieves environment strings in ANSI format. [AI]

// LIBRARY: LEGO1 0x10091ed0
// ___set_app_type
/// @brief [AI] Sets the application type (console/GUI) for CRT. [AI]

// LIBRARY: LEGO1 0x10091ef0
// __FF_MSGBANNER
/// @brief [AI] Prints runtime error banner. [AI]

// LIBRARY: LEGO1 0x10091f30
// __NMSG_WRITE
/// @brief [AI] Writes a runtime error message to standard output or log. [AI]

// LIBRARY: LEGO1 0x10092130
// _raise
/// @brief [AI] Raises a signal in the process. Standard C raise(). [AI]

// LIBRARY: LEGO1 0x10092310
// _siglookup
/// @brief [AI] Looks up signal descriptions/handlers in the CRT. [AI]

// LIBRARY: LEGO1 0x100928c0
// __fptrap
/// @brief [AI] Floating-point exception trap/handler for CRT. [AI]

// LIBRARY: LEGO1 0x100928d0
// __ZeroTail
/// @brief [AI] Sets the tail portion of a floating-point array to zero. [AI]

// LIBRARY: LEGO1 0x10092940
// __IncMan
/// @brief [AI] Increments floating-point mantissa. Used in extended-precision arithmetic. [AI]

// LIBRARY: LEGO1 0x100929b0
// __RoundMan
/// @brief [AI] Rounds floating-point mantissa for CRT math library. [AI]

// LIBRARY: LEGO1 0x10092a60
// __CopyMan
/// @brief [AI] Copies floating-point mantissa arrays. [AI]

// LIBRARY: LEGO1 0x10092a80
// __FillZeroMan
/// @brief [AI] Fills floating-point mantissa arrays with zero. [AI]

// LIBRARY: LEGO1 0x10092a90
// __IsZeroMan
/// @brief [AI] Checks if a floating-point mantissa array is all zero. [AI]

// LIBRARY: LEGO1 0x10092ab0
// __ShrMan
/// @brief [AI] Performs bitwise right-shift on floating-point mantissas. [AI]

// LIBRARY: LEGO1 0x10092b60
// __ld12cvt
/// @brief [AI] Converts an internal CRT 12-byte long double into other representations. [AI]

// LIBRARY: LEGO1 0x10092d30
// __ld12tod
/// @brief [AI] Converts CRT long double (12 byte) to double. [AI]

// LIBRARY: LEGO1 0x10093037
// __trandisp2
/// @brief [AI] CRT internal dispatcher for floating-point or transcendental math functions. [AI]

// LIBRARY: LEGO1 0x10093480
// ___crtGetStringTypeA
/// @brief [AI] Determines string type/classification with locale support. [AI]

// LIBRARY: LEGO1 0x100935b0
// __getbuf
/// @brief [AI] Allocates a buffer for file I/O operations. [AI]

// LIBRARY: LEGO1 0x10093600
// __isatty
/// @brief [AI] Checks if file descriptor refers to a terminal device. [AI]

// LIBRARY: LEGO1 0x10093630
// _wctomb
/// @brief [AI] Converts a wide character to a multibyte sequence. [AI]

// LIBRARY: LEGO1 0x10093690
// __wctomb_lk
/// @brief [AI] Thread-safe version of wctomb, uses locks. [AI]

// LIBRARY: LEGO1 0x10093730
// __aulldiv
/// @brief [AI] Divides two unsigned 64-bit integers. [AI]

// LIBRARY: LEGO1 0x100937a0
// __aullrem
/// @brief [AI] Returns the remainder of two unsigned 64-bit integers. [AI]

// LIBRARY: LEGO1 0x10093820
// ___strgtold12
/// @brief [AI] Converts string to CRT long double (12 bytes). [AI]

// LIBRARY: LEGO1 0x10093f70
// __alloc_osfhnd
/// @brief [AI] Allocates a new operating system file handle. [AI]

// LIBRARY: LEGO1 0x100940b0
// __set_osfhnd
/// @brief [AI] Sets an existing OS file handle into the CRT file handle table. [AI]

// LIBRARY: LEGO1 0x10094160
// __free_osfhnd
/// @brief [AI] Releases an operating system file handle managed by CRT. [AI]

// LIBRARY: LEGO1 0x10094200
// __get_osfhandle
/// @brief [AI] Retrieves the raw OS file handle associated with a CRT file descriptor. [AI]

// LIBRARY: LEGO1 0x10094250
// __lock_fhandle
/// @brief [AI] Locks a CRT file handle for thread-safe operations. [AI]

// LIBRARY: LEGO1 0x100942c0
// __unlock_fhandle
/// @brief [AI] Unlocks a CRT file handle, enabling other threads to access it. [AI]

// LIBRARY: LEGO1 0x100943a0
// __sopen
/// @brief [AI] Opens a file with sharing modes. CRT version of sopen. [AI]

// LIBRARY: LEGO1 0x10095820
// __mbsrchr
/// @brief [AI] Searches for the last occurrence of a character in a multibyte string. [AI]

// LIBRARY: LEGO1 0x100958b0
// __mbschr
/// @brief [AI] Searches for first occurrence of a character in a multibyte string. [AI]

// LIBRARY: LEGO1 0x10095f90
// _mbtowc
/// @brief [AI] Converts a multibyte string to a wide character. [AI]

// LIBRARY: LEGO1 0x10095ff0
// __mbtowc_lk
/// @brief [AI] Thread-safe version of mbtowc for CRT. [AI]

// LIBRARY: LEGO1 0x10096190
// ___sbh_new_region
/// @brief [AI] Allocates a new region for the small-block heap implementation in CRT. [AI]

// LIBRARY: LEGO1 0x10096300
// ___crtMessageBoxA
/// @brief [AI] Displays a message box with CRT-specific customization. [AI]

// LIBRARY: LEGO1 0x10096490
// ___addl
/// @brief [AI] Adds two multi-precision values, used for CRT math support. [AI]

// LIBRARY: LEGO1 0x100964c0
// ___add_12
/// @brief [AI] Adds two 12-byte long double values. [AI]

// LIBRARY: LEGO1 0x10096530
// ___shl_12
/// @brief [AI] Logical left shift of 12-byte CRT long double. [AI]

// LIBRARY: LEGO1 0x10096570
// ___shr_12
/// @brief [AI] Logical right shift of 12-byte CRT long double. [AI]

// LIBRARY: LEGO1 0x100965b0
// ___mtold12
/// @brief [AI] Converts CRT decimal representation to long double (12 byte). [AI]

// LIBRARY: LEGO1 0x10097190
// ___ld12mul
/// @brief [AI] Multiplies two CRT 12-byte long double values. [AI]

// LIBRARY: LEGO1 0x10097440
// ___multtenpow12
/// @brief [AI] Multiplies a CRT 12-byte long double by a power of 10. [AI]

// LIBRARY: LEGO1 0x100974c0
// __chsize_lk
/// @brief [AI] Changes the size of a file with locking for thread safety. [AI]

// LIBRARY: LEGO1 0x100977c0
// _itoa
/// @brief [AI] Converts an integer to a string. Standard C itoa. [AI]

// LIBRARY: LEGO1 0x10097ad0
// _strrchr
/// @brief [AI] Returns pointer to the last occurrence of a character in a string. Standard C strrchr. [AI]

// LIBRARY: LEGO1 0x10097b10
// _strchr
/// @brief [AI] Returns pointer to the first occurrence of a character in a string. Standard C strchr. [AI]

// LIBRARY: LEGO1 0x10097d70
// __setmode_lk
/// @brief [AI] Sets mode of a CRT file descriptor with locking for thread safety. [AI]

// LIBRARY: LEGO1 0x100d1ed0
// LIBRARY: BETA10 0x1018ec70
// _strnicmp
/// @brief [AI] Case-insensitive comparison of the first N chars of two strings. [AI]

// LIBRARY: LEGO1 0x100d1fd0
// _strupr
/// @brief [AI] Converts a string to uppercase. Non-standard, but provided on many platforms. [AI]

// LIBRARY: LEGO1 0x100d2130
// _vsprintf
/// @brief [AI] Prints formatted data from a variable argument list to a string. [AI]

// LIBRARY: LEGO1 0x100d21c2
// __CIpow
/// @brief [AI] Calculates power of a value (CRT intrinsic for pow()). [AI]

// LIBRARY: LEGO1 0x100d21f0
// _strstr
/// @brief [AI] Finds the first occurrence of a substring in a string. Standard C strstr. [AI]

// LIBRARY: LEGO1 0x100d2270
// __beginthreadex
/// @brief [AI] Begins a new thread with extended options in the CRT, Windows-specific. [AI]

// GLOBAL: LEGO1 0x100daab8
// ___lookuptable
/// @brief [AI] Lookup table used by runtime for various operations. [AI]

// GLOBAL: LEGO1 0x100f0000
// ___xc_a
/// @brief [AI] Start pointer for C++ static constructor section. [AI]

// GLOBAL: LEGO1 0x100f0020
// ___xc_z
/// @brief [AI] End pointer for C++ static constructor section. [AI]

// GLOBAL: LEGO1 0x100f0024
// ___xi_a
/// @brief [AI] Start pointer for CRT C initializers. [AI]

// GLOBAL: LEGO1 0x100f0030
// ___xi_z
/// @brief [AI] End pointer for CRT C initializers. [AI]

// GLOBAL: LEGO1 0x100fc8bc
// __NLG_Destination
/// @brief [AI] Global variable related to non-local goto/exception destination in CRT. [AI]

// GLOBAL: LEGO1 0x100fc8f0
// __iob
/// @brief [AI] Global array of FILE structures for stdin, stdout, stderr. [AI]

// GLOBAL: LEGO1 0x100fcb70
// __cflush
/// @brief [AI] Flushes the C runtime output buffer. [AI]

// GLOBAL: LEGO1 0x100fcb74
// __umaskval
/// @brief [AI] Value of the file creation mask (umask) for CRT. [AI]

// GLOBAL: LEGO1 0x100fcb78
// __osver
/// @brief [AI] Operating system version, as detected by CRT. [AI]

// GLOBAL: LEGO1 0x100fcb7c
// __winver
/// @brief [AI] Windows version as detected by CRT. [AI]

// GLOBAL: LEGO1 0x100fcb80
// __winmajor
/// @brief [AI] Windows major version, for CRT and compatibility checks. [AI]

// GLOBAL: LEGO1 0x100fcb84
// __winminor
/// @brief [AI] Windows minor version, for CRT and compatibility checks. [AI]

// GLOBAL: LEGO1 0x100fcb88
// ___argc
/// @brief [AI] Argument count passed to main(), CRT provided. [AI]

// GLOBAL: LEGO1 0x100fcb8c
// ___argv
/// @brief [AI] Argument vector passed to main(), CRT provided. [AI]

// GLOBAL: LEGO1 0x100fcb94
// __environ
/// @brief [AI] Current environment variables as a vector of strings. [AI]

// GLOBAL: LEGO1 0x100fcba4
// __pgmptr
/// @brief [AI] Path to the program executable as known by CRT. [AI]

// GLOBAL: LEGO1 0x100fcbb0
// __C_Termination_Done
/// @brief [AI] Boolean indicating if C termination has already been performed. [AI]

// GLOBAL: LEGO1 0x100fcf04
// __aenvptr
/// @brief [AI] Pointer to argument environment array in CRT. [AI]

// GLOBAL: LEGO1 0x100fcf10
// ___error_mode
/// @brief [AI] CRT error reporting mode global variable. [AI]

// GLOBAL: LEGO1 0x100fcf14
// ___app_type
/// @brief [AI] CRT application type (console or GUI). [AI]

// GLOBAL: LEGO1 0x100fcf20
// ___tlsindex
/// @brief [AI] Index for accessing thread-local storage in CRT. [AI]

// GLOBAL: LEGO1 0x100fcf60
// __OP_ACOSjmptab
/// @brief [AI] Jump table for CRT implementation of acos() and related math functions. [AI]

// GLOBAL: LEGO1 0x100fcff0
// __pctype
/// @brief [AI] Character type classification table used by CRT for locale/ctype. [AI]

// GLOBAL: LEGO1 0x100fd1fc
// ___mb_cur_max
/// @brief [AI] Current max size of multibyte character, locale-dependent. [AI]

// GLOBAL: LEGO1 0x100fd200
// ___decimal_point
/// @brief [AI] Character used as the decimal point for the locale. [AI]

// GLOBAL: LEGO1 0x100fd210
// ___nullstring
/// @brief [AI] Pointer to an empty null-terminated string used by CRT. [AI]

// GLOBAL: LEGO1 0x100fd214
// ___wnullstring
/// @brief [AI] Pointer to an empty wide null-terminated string. [AI]

// GLOBAL: LEGO1 0x100fd218
// __locktable
/// @brief [AI] Table of CRT locks for threads, synchronizing access to global data. [AI]

// GLOBAL: LEGO1 0x100fd2d8
// __stdbuf
/// @brief [AI] Default buffers used by stdin, stdout, stderr. [AI]

// GLOBAL: LEGO1 0x100fd2e0
// ___badioinfo
/// @brief [AI] Array of invalid or default CRT IOINFO structures. [AI]

// GLOBAL: LEGO1 0x100fd478
// ___lc_handle
/// @brief [AI] Locale handle value for CRT. [AI]

// GLOBAL: LEGO1 0x100fd490
// ___lc_codepage
/// @brief [AI] Locale codepage value for CRT. [AI]

// GLOBAL: LEGO1 0x100fd624
// ?__pInconsistency@@3P6AXXZA
/// @brief [AI] Pointer to CRT inconsistency handler. [AI]

// GLOBAL: LEGO1 0x100fd638
// __mbctype
/// @brief [AI] Table identifying multibyte character types. [AI]

// GLOBAL: LEGO1 0x100fd73c
// ___mbcodepage
/// @brief [AI] Current multibyte codepage for CRT locale. [AI]

// GLOBAL: LEGO1 0x100fd740
// ___mblcid
/// @brief [AI] Multibyte locale identifier. [AI]

// GLOBAL: LEGO1 0x100fd748
// ___mbulinfo
/// @brief [AI] Pointer to extended unicode/multibyte locale info. [AI]

// GLOBAL: LEGO1 0x100fd8e8
// __adbgmsg
/// @brief [AI] Address of debug message buffer in CRT. [AI]

// GLOBAL: LEGO1 0x100fd910
// __XcptActTab
/// @brief [AI] Table of exception action pointers in CRT. [AI]

// GLOBAL: LEGO1 0x100fd988
// __First_FPE_Indx
/// @brief [AI] Index of first floating-point exception handler. [AI]

// GLOBAL: LEGO1 0x100fd98c
// __Num_FPE
/// @brief [AI] Number of floating-point exception handlers registered. [AI]

// GLOBAL: LEGO1 0x100fda10
// __commode
/// @brief [AI] Global variable controlling file commit mode (binary/text, etc). [AI]

// GLOBAL: LEGO1 0x100fe250
// ___small_block_heap
/// @brief [AI] Pointer to the CRT small-block heap info, for small allocations. [AI]

// GLOBAL: LEGO1 0x100feb58
// __matherr_flag
/// @brief [AI] CRT math error handling flag. [AI]

// GLOBAL: LEGO1 0x100feb7c
// __fmode
/// @brief [AI] Default file mode for opened files (text/binary). [AI]

// GLOBAL: LEGO1 0x101028da
// __OP_POWjmptab
/// @brief [AI] CRT jump table implementation for pow() and related math operations. [AI]

// GLOBAL: LEGO1 0x1010292a
// __OP_LOG10jmptab
/// @brief [AI] CRT jump table for log10() and related logarithm calculations. [AI]

// GLOBAL: LEGO1 0x1010294a
// __OP_LOGjmptab
/// @brief [AI] CRT jump table for log() and related logarithm calculations. [AI]

// GLOBAL: LEGO1 0x1010296a
// __OP_EXPjmptab
/// @brief [AI] CRT jump table for exp() and related exponential functions. [AI]

// GLOBAL: LEGO1 0x101095f8
// __crtheap
/// @brief [AI] Pointer/reference to CRT's process heap. [AI]

// GLOBAL: LEGO1 0x101095fc
// ___setlc_active
/// @brief [AI] CRT flag for active locale setting. [AI]

// GLOBAL: LEGO1 0x10109600
// ___unguarded_readlc_active
/// @brief [AI] CRT flag for unguarded locale reads. [AI]

// GLOBAL: LEGO1 0x10109610
// ___pioinfo
/// @brief [AI] Array of CRT IOINFO (file info structures). [AI]

// GLOBAL: LEGO1 0x10109710
// __nhandle
/// @brief [AI] Count of CRT file handles opened. [AI]

// GLOBAL: LEGO1 0x10109714
// __acmdln
/// @brief [AI] Stored process command line string. [AI]

// GLOBAL: LEGO1 0x10109718
// __pRawDllMain
/// @brief [AI] Pointer to the process DLL entrypoint function. [AI]

// GLOBAL: LEGO1 0x10109724
// ___piob
/// @brief [AI] Pointer to an array of FILE structures used by CRT. [AI]

// GLOBAL: LEGO1 0x1010a730
// __nstream
/// @brief [AI] Number of streams available/allotted in CRT. [AI]

// LIBRARY: BETA10 0x100f9060
// _assert
/// @brief [AI] Checks a condition and terminates the program if false, printing an error message. [AI]

// LIBRARY: BETA10 0x100fa2fa
// _acos
/// @brief [AI] Calculates arc-cosine of a value. Standard math library function. [AI]

// LIBRARY: BETA10 0x100f9a50
// _sin
/// @brief [AI] Calculates sine of a value (argument in radians). [AI]

// LIBRARY: BETA10 0x100f9a5a
// _cos
/// @brief [AI] Calculates cosine of a value (argument in radians). [AI]

// LIBRARY: BETA10 0x100f95d0
// _sqrt
/// @brief [AI] Calculates the square root of a value. [AI]

// LIBRARY: BETA10 0x100f9780
// strlen
/// @brief [AI] Returns length of a null-terminated string. [AI]

// LIBRARY: BETA10 0x100fa200
// strcpy
/// @brief [AI] Copies a source string to a destination buffer. [AI]

// LIBRARY: BETA10 0x100f8a88
// ??2@YAPAXI@Z
/// @brief [AI] Beta10 library: memory allocation operator, equivalent to new. [AI]

// LIBRARY: BETA10 0x100f9420
// memcpy
/// @brief [AI] Copies memory from a source buffer to destination buffer. [AI]

// LIBRARY: BETA10 0x100faa00
// memcmp
/// @brief [AI] Compares two buffers of memory. [AI]

// LIBRARY: BETA10 0x100fb080
// _stricmp
/// @brief [AI] Performs a case-insensitive comparison of two strings. [AI]

// LIBRARY: BETA10 0x100fb050
// fopen
/// @brief [AI] Opens a file (Beta10 CRT implementation). [AI]

// LIBRARY: BETA10 0x100fae70
// fprintf
/// @brief [AI] Prints formatted output to a file stream. [AI]

// LIBRARY: BETA10 0x100fad10
// fclose
/// @brief [AI] Closes a file (Beta10 CRT implementation). [AI]

// LIBRARY: BETA10 0x100fe5a0
// abort
/// @brief [AI] Aborts the program (Beta10 CRT implementation). [AI]

// LIBRARY: BETA10 0x100fa0e0
// atof
/// @brief [AI] Converts string to floating-point number. [AI]

// LIBRARY: BETA10 0x1005a9c0
// fabs
/// @brief [AI] Returns the absolute value of a floating-point number. [AI]

// LIBRARY: BETA10 0x1005a9f0
// fabsf
/// @brief [AI] Returns the absolute value of a single-precision floating-point number. [AI]

// LIBRARY: BETA10 0x100f9bb0
// _fabs
/// @brief [AI] Returns the absolute value of a floating-point number. [AI]

// LIBRARY: BETA10 0x100f9570
// memset
/// @brief [AI] Sets memory to a given value (fills a buffer). [AI]

// LIBRARY: BETA10 0x100ff82b
// __ctrandisp1
/// @brief [AI] CRT internal dispatcher for certain math routines. [AI]

// LIBRARY: BETA10 0x100f8a92
// operator delete
/// @brief [AI] Beta10 library: memory deallocation operator, equivalent to delete. [AI]

// LIBRARY: BETA10 0x1018ed70
// _strupr
/// @brief [AI] Converts a string to uppercase, Beta10 implementation. [AI]

// LIBRARY: BETA10 0x100f9690
// sprintf
/// @brief [AI] Formats output and stores it in a string buffer. [AI]

// LIBRARY: BETA10 0x100fb150
// _spawnl
/// @brief [AI] Starts a new process, Beta10 implementation (CRT). [AI]

// LIBRARY: BETA10 0x1001d1a0
// `vector constructor iterator'
/// @brief [AI] CRT utility for constructing vector/array elements, supporting exceptions. [AI]

// LIBRARY: BETA10 0x100f8ad0
// strcmp
/// @brief [AI] Compares two strings lexicographically, Beta10 implementation. [AI]

// LIBRARY: BETA10 0x100f9610
// rand
/// @brief [AI] Returns pseudo-random number, Beta10 version. [AI]

// LIBRARY: BETA10 0x100f9b90
// _purecall
/// @brief [AI] Beta10: called by CRT when pure virtual called. [AI]

// LIBRARY: BETA10 0x100fca70
// _amsg_exit
/// @brief [AI] Displays CRT runtime error message and terminates. [AI]

// LIBRARY: BETA10 0x1010ab30
// _FF_MSGBANNER
/// @brief [AI] Displays CRT message banner (Beta10 CRT implementation). [AI]

// LIBRARY: BETA10 0x1010ab90
// _NMSG_WRITE
/// @brief [AI] Writes CRT error message (Beta10 CRT implementation). [AI]

// LIBRARY: BETA10 0x100fbdb0
// _exit
/// @brief [AI] Terminates the process immediately, Beta10 C runtime. [AI]

// GLOBAL: BETA10 0x101faf70
// _aexit_rtn
/// @brief [AI] Function pointer for cleanup at exit, Beta10 CRT. [AI]

// LIBRARY: BETA10 0x10100bf0
// _CrtDbgReport
/// @brief [AI] CRT debug reporting function for debugging CRT issues. [AI]

// GLOBAL: BETA10 0x101faf74
// __error_mode
/// @brief [AI] Global variable: current error mode for CRT, Beta10. [AI]

// GLOBAL: BETA10 0x101faf78
// __app_type
/// @brief [AI] Global variable: application type for CRT, Beta10. [AI]

// GLOBAL: LEGO1 0x100db6e0
// GUID_SysKeyboard
/// @brief [AI] GUID for DirectInput system keyboard device, used for identifying the keyboard device in DirectInput operations. [AI]

// Cannot be handled right now due to anonymous pointer in struct
// // GLOBAL: LEGO1 0x10098f80
// c_dfDIKeyboard

#endif
