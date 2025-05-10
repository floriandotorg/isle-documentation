#ifndef MXUTILITIES_H
#define MXUTILITIES_H

#include "mxtypes.h"

#include <string.h>

class MxDSFile;
class MxDSObject;
class MxDSAction;
class MxCompositePresenterList;
class MxPresenter;

/**
 * @brief Returns the absolute value of a value. [AI]
 * @details [AI] Templated utility function to compute the absolute value for any arithmetic type.
 * @tparam T [AI] Any type supporting comparison and negation.
 * @param p_t [AI] Value to compute the absolute value of.
 * @return Absolute value of p_t. [AI]
 */
template <class T>
inline T Abs(T p_t)
{
	return p_t < 0 ? -p_t : p_t;
}

/**
 * @brief Returns the minimum of two values. [AI]
 * @details [AI] Templated utility function to select the smaller of two values.
 * @tparam T [AI] Any type supporting comparison.
 * @param p_t1 [AI] First value.
 * @param p_t2 [AI] Second value.
 * @return Smallest of p_t1 and p_t2. [AI]
 */
template <class T>
inline T Min(T p_t1, T p_t2)
{
	return p_t1 < p_t2 ? p_t1 : p_t2;
}

/**
 * @brief Returns the maximum of two values. [AI]
 * @details [AI] Templated utility function to select the greater of two values.
 * @tparam T [AI] Any type supporting comparison.
 * @param p_t1 [AI] First value.
 * @param p_t2 [AI] Second value.
 * @return Largest of p_t1 and p_t2. [AI]
 */
template <class T>
inline T Max(T p_t1, T p_t2)
{
	return p_t1 > p_t2 ? p_t1 : p_t2;
}

/**
 * @brief Reads a value of type T from a memory buffer and advances the pointer. [AI]
 * @details [AI] Used for deserialization from a byte buffer, e.g. for loading chunked SI data.
 * @tparam T [AI] Type to extract.
 * @param p_source [AI] Reference to pointer in buffer to read from. Will be incremented by sizeof(T).
 * @param p_dest [AI] Destination to store the extracted value.
 */
template <class T>
inline void GetScalar(MxU8*& p_source, T& p_dest)
{
	p_dest = *(T*) p_source;
	p_source += sizeof(T);
}

/**
 * @brief Reads a single value from a pointer and advances the pointer. [AI]
 * @details [AI] Convenience version for types already aligned in memory.
 * @tparam T [AI] Type to extract.
 * @param p_source [AI] Reference to pointer to T to read from. Increments pointer by one element.
 * @return The extracted value. [AI]
 */
template <class T>
inline T GetScalar(T*& p_source)
{
	T val = *p_source;
	p_source += 1;
	return val;
}

/**
 * @brief Reads a double-precision value from memory and advances the pointer. [AI]
 * @details [AI] Specialized for double reads, as some SI chunks may pack doubles specially.
 * @tparam T [AI] Target type to store the double into (usually double).
 * @param p_source [AI] Reference to pointer in buffer, will be incremented by sizeof(double).
 * @param p_dest [AI] Destination to store the value.
 */
template <class T>
inline void GetDouble(MxU8*& p_source, T& p_dest)
{
	p_dest = *(double*) p_source;
	p_source += sizeof(double);
}

/**
 * @brief Extracts a string from a buffer and assigns it using a setter function on an object. [AI]
 * @details [AI] Reads a NUL-terminated string, uses p_setter member function to consume it, then advances buffer pointer past string.
 * @tparam T [AI] Type of the object with the setter member function.
 * @param p_source [AI] Reference to buffer pointer, advanced past the string.
 * @param p_dest [AI] The string pointer assigned by the setter.
 * @param p_obj [AI] Object to call member function on.
 * @param p_setter [AI] Member function accepting a const char* as parameter. Typically sets a property on the object.
 */
template <class T>
inline void GetString(MxU8*& p_source, char*& p_dest, T* p_obj, void (T::*p_setter)(const char*))
{
	(p_obj->*p_setter)((char*) p_source);
	p_source += strlen(p_dest) + 1;
}

/**
 * @brief Computes intersection of two rectangles and modifies their positions and dimensions to the intersection area. [AI]
 * @details [AI] Used to find overlapping portions when rendering or handling collision/visibility in 2D screen/UI contexts. Modifies parameters in-place.
 * @param p_rect1Width [AI] Width of first rectangle.
 * @param p_rect1Height [AI] Height of first rectangle.
 * @param p_rect2Width [AI] Width of second rectangle.
 * @param p_rect2Height [AI] Height of second rectangle.
 * @param p_rect1Left [AI] Pointer to X of top-left of first rectangle (modified to intersection).
 * @param p_rect1Top [AI] Pointer to Y of top-left of first rectangle (modified to intersection).
 * @param p_rect2Left [AI] Pointer to X of top-left of second rectangle (modified to intersection).
 * @param p_rect2Top [AI] Pointer to Y of top-left of second rectangle (modified to intersection).
 * @param p_width [AI] Pointer to width of the intersection area.
 * @param p_height [AI] Pointer to height of the intersection area.
 * @return TRUE if the rectangles intersect, FALSE otherwise. [AI]
 */
MxBool GetRectIntersection(
	MxS32 p_rect1Width,
	MxS32 p_rect1Height,
	MxS32 p_rect2Width,
	MxS32 p_rect2Height,
	MxS32* p_rect1Left,
	MxS32* p_rect1Top,
	MxS32* p_rect2Left,
	MxS32* p_rect2Top,
	MxS32* p_width,
	MxS32* p_height
);

/**
 * @brief Parses an SI source filename and normalizes it for use in the engine. [AI]
 * @details [AI] Removes any disk designator (e.g., 'C:') and ".si" extension, and makes string lowercase.
 * @param p_output [AI] Output buffer for source name.
 * @param p_input [AI] Input filename (may include drive, extension, etc.).
 */
void MakeSourceName(char*, const char*);

/**
 * @brief Displays or logs an error message using the current user message handler, or aborts on error status if none is set. [AI]
 * @details [AI] If the callback is not set and status is non-zero, aborts process. Otherwise, invokes callback.
 * @param p_message [AI] Null-terminated error message.
 * @param p_status [AI] Status code or severity.
 */
void OmniError(const char* p_message, MxS32 p_status);

/**
 * @brief Sets the callback to handle user messages, such as errors or logs, for the OMNI engine. [AI]
 * @details [AI] The callback is a function pointer invoked by OmniError.
 * @param p_omniUserMessage [AI] Callback function accepting a string message and status integer.
 */
void SetOmniUserMessage(void (*p_omniUserMessage)(const char*, MxS32));

/**
 * @brief Determines if a presenter exists within a composite presenter hierarchy. [AI]
 * @details [AI] Searches recursively within all composite presenters for an exact pointer match or type match.
 * @param p_presenterList [AI] Reference to list of composite presenters.
 * @param p_presenter [AI] Presenter to look for.
 * @return TRUE if found, FALSE otherwise. [AI]
 */
MxBool ContainsPresenter(MxCompositePresenterList& p_presenterList, MxPresenter* p_presenter);

/**
 * @brief Recursively sets or clears flags for an MxDSAction and all sub-actions if applicable. [AI]
 * @details [AI] If the object is a MxDSMultiAction, recurses into its action list, updating flags for all contained actions.
 * @param p_action [AI] The root action to update.
 * @param p_newFlags [AI] Flags to set or clear.
 * @param p_setFlags [AI] TRUE to set bits, FALSE to clear bits in the action's flags.
 */
void FUN_100b7220(MxDSAction* p_action, MxU32 p_newFlags, MxBool p_setFlags); ///< [AI_SUGGESTED_NAME: SetActionFlagsRecursive]

/**
 * @brief Searches p_string for a key command and copies its associated value to p_output. [AI]
 * @details [AI] For commands like "foo:123, bar:456", if p_command is "bar" then p_output becomes "456". Used in config or SI parsing.
 * @param p_output [AI] Buffer for found value.
 * @param p_command [AI] Key to search for.
 * @param p_string [AI] String to search in.
 * @return TRUE if key is found, FALSE otherwise. [AI]
 */
MxBool KeyValueStringParse(char*, const char*, const char*);

// TEMPLATE: BETA10 0x1012dfd0
// ?Max@@YAHHH@Z

// TEMPLATE: BETA10 0x1012dff0
// ?Min@@YAHHH@Z

#endif // MXUTILITIES_H